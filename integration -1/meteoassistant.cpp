#include "meteoassistant.h"
#include <QUrlQuery>
#include <QDebug>
#include <QtMath>

MeteoAssistant::MeteoAssistant(QObject *parent)
    : QObject(parent), networkManager(new QNetworkAccessManager(this))
{
    connect(networkManager, &QNetworkAccessManager::finished,
            this, &MeteoAssistant::onMeteoRecue);
}

MeteoAssistant::~MeteoAssistant()
{
}

void MeteoAssistant::analyserMeteoEvenement(const QString &remarque, const QDate &date,
                                            const QString &heure, const QString &nomevent)
{
    if (!estEvenementExterieur(remarque)) {
        return;
    }

    current_remarque = remarque;
    current_date = date;
    current_heure = heure;
    current_nomevent = nomevent;

    QString urlString = "https://api.open-meteo.com/v1/forecast";
    QUrl url(urlString);
    QUrlQuery query;

    query.addQueryItem("latitude", QString::number(LATITUDE));
    query.addQueryItem("longitude", QString::number(LONGITUDE));
    query.addQueryItem("hourly", "temperature_2m,precipitation_probability,"
                                 "precipitation,wind_speed_10m,weather_code");
    query.addQueryItem("timezone", "Africa/Tunis");
    query.addQueryItem("forecast_days", "16");

    url.setQuery(query);

    QNetworkRequest request(url);
    networkManager->get(request);

    qDebug() << "Requête météo envoyée pour:" << nomevent;
}

bool MeteoAssistant::estEvenementExterieur(const QString &remarque) const
{
    QString rmq = remarque.toLower();

    QStringList motsExterieur = {
        "dehors", "extérieur", "exterieur", "plein air", "jardin", "parc",
        "terrasse", "outdoor", "plage", "piscine", "montagne", "camping",
        "pique-nique", "randonnée", "balade", "sport", "football", "tennis"
    };

    for (const QString &mot : motsExterieur) {
        if (rmq.contains(mot)) {
            return true;
        }
    }
    return false;
}

QString MeteoAssistant::getCategorieEvenement(const QString &remarque,
                                              const QString &nomevent) const
{
    QString text = (remarque + " " + nomevent).toLower();

    if (text.contains("enfant") || text.contains("bébé") || text.contains("école") ||
        text.contains("anniversaire enfant") || text.contains("bebe")) {
        return "groupe_sensible";
    }

    if (text.contains("sport") || text.contains("match") || text.contains("course") ||
        text.contains("marathon") || text.contains("football")) {
        return "sport";
    }

    if (text.contains("mariage") || text.contains("cérémonie") ||
        text.contains("réception") || text.contains("gala")) {
        return "formel";
    }

    if (text.contains("pique-nique") || text.contains("barbecue") ||
        text.contains("détente") || text.contains("plage")) {
        return "detente";
    }

    return "general";
}

MeteoData MeteoAssistant::extraireMeteoData(const QJsonObject &hourlyData, int index) const
{
    MeteoData data;

    QJsonArray times = hourlyData["time"].toArray();
    QJsonArray temps = hourlyData["temperature_2m"].toArray();
    QJsonArray precip_prob = hourlyData["precipitation_probability"].toArray();
    QJsonArray precip = hourlyData["precipitation"].toArray();
    QJsonArray wind = hourlyData["wind_speed_10m"].toArray();
    QJsonArray weather_codes = hourlyData["weather_code"].toArray();

    if (index >= times.size()) {
        return data;
    }

    QString timeStr = times[index].toString();
    QDateTime dt = QDateTime::fromString(timeStr, Qt::ISODate);
    data.date = dt.date();
    data.heure = dt.time();

    data.temperature = temps[index].toDouble();
    data.precipitation_probability = precip_prob[index].toInt();
    data.precipitation = precip[index].toDouble();
    data.wind_speed = wind[index].toDouble();
    data.weather_code = weather_codes[index].toInt();
    data.weather_description = getWeatherDescription(data.weather_code);

    return data;
}

bool MeteoAssistant::estMeteoConvenable(const MeteoData &meteo,
                                        const QString &categorie) const
{
    if (categorie == "groupe_sensible") {
        return meteo.precipitation_probability < 15 &&
               meteo.precipitation < 0.1 &&
               meteo.wind_speed < 20 &&
               meteo.temperature >= 18 && meteo.temperature <= 28 &&
               (meteo.weather_code == 0 || meteo.weather_code == 1);
    }

    if (categorie == "sport") {
        return meteo.precipitation_probability < 20 &&
               meteo.precipitation < 0.2 &&
               meteo.wind_speed < 30 &&
               meteo.temperature >= 15 && meteo.temperature <= 30;
    }

    if (categorie == "formel") {
        return meteo.precipitation_probability < 10 &&
               meteo.precipitation < 0.1 &&
               meteo.wind_speed < 25 &&
               (meteo.weather_code == 0 || meteo.weather_code == 1 ||
                meteo.weather_code == 2);
    }

    return meteo.precipitation_probability < 30 &&
           meteo.precipitation < 1.0 &&
           meteo.wind_speed < 35;
}

MeteoRecommendation MeteoAssistant::trouverMeilleureDate(
    const QJsonObject &weatherData,
    const QDate &dateOriginale,
    const QTime &heureOriginale,
    const QString &categorie) const
{
    MeteoRecommendation rec;
    rec.is_current_date_ok = false;

    QJsonObject hourly = weatherData["hourly"].toObject();
    QJsonArray times = hourly["time"].toArray();

    int targetHour = heureOriginale.hour();
    QDate today = QDate::currentDate();

    int originalIndex = -1;
    for (int i = 0; i < times.size(); i++) {
        QString timeStr = times[i].toString();
        QDateTime dt = QDateTime::fromString(timeStr, Qt::ISODate);

        if (dt.date() == dateOriginale && dt.time().hour() == targetHour) {
            originalIndex = i;
            break;
        }
    }

    if (originalIndex != -1) {
        rec.current_weather = extraireMeteoData(hourly, originalIndex);
        rec.is_current_date_ok = estMeteoConvenable(rec.current_weather, categorie);
    }

    if (!rec.is_current_date_ok) {
        double meilleurScore = -1;
        int meilleurIndex = -1;

        for (int i = 0; i < times.size(); i++) {
            QString timeStr = times[i].toString();
            QDateTime dt = QDateTime::fromString(timeStr, Qt::ISODate);

            if (dt.date() <= dateOriginale) {
                continue;
            }

            if (dt.date() < today) {
                continue;
            }

            if (qAbs(dt.time().hour() - targetHour) <= 2) {
                MeteoData meteo = extraireMeteoData(hourly, i);

                if (estMeteoConvenable(meteo, categorie)) {
                    int joursDecalage = dateOriginale.daysTo(dt.date());

                    double score = 100.0 - (joursDecalage - 1) * 3
                                   - meteo.precipitation_probability
                                   - qAbs(meteo.wind_speed) / 2;

                    if (score > meilleurScore) {
                        meilleurScore = score;
                        meilleurIndex = i;
                    }
                }
            }
        }

        if (meilleurIndex != -1) {
            rec.alternative_weather = extraireMeteoData(hourly, meilleurIndex);
            rec.alternative_date = rec.alternative_weather.date;
            rec.alternative_time = rec.alternative_weather.heure;
        }
    }

    return rec;
}

QString MeteoAssistant::getWeatherDescription(int weatherCode) const
{
    switch (weatherCode) {
    case 0: return "Ciel dégagé";
    case 1: return "Principalement dégagé";
    case 2: return "Partiellement nuageux";
    case 3: return "Couvert";
    case 45:
    case 48: return "Brouillard";
    case 51:
    case 53:
    case 55: return "Bruine";
    case 61: return "Pluie légère";
    case 63: return "Pluie modérée";
    case 65: return "Pluie forte";
    case 71:
    case 73:
    case 75: return "Neige";
    case 80:
    case 81:
    case 82: return "Averses";
    case 95: return "Orage";
    case 96:
    case 99: return "Orage violent";
    default: return "Temps variable";
    }
}

QString MeteoAssistant::getEmojiMeteo(int weatherCode) const
{
    switch (weatherCode) {
    case 0: return "☀️";
    case 1: return "🌤️";
    case 2: return "⛅";
    case 3: return "☁️";
    case 45:
    case 48: return "🌫️";
    case 51:
    case 53:
    case 55: return "🌦️";
    case 61: return "🌧️";
    case 63: return "🌧️";
    case 65: return "⛈️";
    case 71:
    case 73:
    case 75: return "❄️";
    case 80:
    case 81:
    case 82: return "🌧️";
    case 95: return "⚡";
    case 96:
    case 99: return "⛈️";
    default: return "🌤️";
    }
}

QString MeteoAssistant::getEmojiPluie(int percentage) const
{
    if (percentage >= 70) return "☔";
    else if (percentage >= 40) return "🌧️";
    else if (percentage >= 20) return "🌦️";
    else return "✅";
}

QString MeteoAssistant::getEmojiVent(double windSpeed) const
{
    if (windSpeed >= 40) return "💨💨";
    else if (windSpeed >= 25) return "💨";
    else return "🍃";
}

QString MeteoAssistant::getEmojiTemperature(double temp) const
{
    if (temp >= 30) return "🔥";
    else if (temp >= 25) return "☀️";
    else if (temp >= 20) return "🌡️";
    else if (temp >= 15) return "🌤️";
    else if (temp >= 10) return "❄️";
    else return "🥶";
}

QString MeteoAssistant::genererMessage(const MeteoRecommendation &rec,
                                       const QString &categorie) const
{
    QString message;

    if (rec.is_current_date_ok) {
        message = QString(
                      "✅ MÉTÉO FAVORABLE POUR VOTRE ÉVÉNEMENT !\n\n"
                      "📅 Date proposée : %1\n"
                      "🕐 Heure : %2\n\n"
                      "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
                      "📊 PRÉVISIONS MÉTÉO :\n"
                      "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n"
                      "%3 Conditions : %4\n\n"
                      "%5 Température : %6°C\n\n"
                      "%7 Pluie : %8%%\n\n"
                      "%9 Vent : %10 km/h\n\n"
                      "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n"
                      "👍 Les conditions sont idéales pour votre événement !\n"
                      )
                      .arg(rec.current_weather.date.toString("dddd dd MMMM yyyy"))
                      .arg(rec.current_weather.heure.toString("HH:mm"))
                      .arg(getEmojiMeteo(rec.current_weather.weather_code))
                      .arg(rec.current_weather.weather_description)
                      .arg(getEmojiTemperature(rec.current_weather.temperature))
                      .arg(rec.current_weather.temperature, 0, 'f', 1)
                      .arg(getEmojiPluie(rec.current_weather.precipitation_probability))
                      .arg(rec.current_weather.precipitation_probability)
                      .arg(getEmojiVent(rec.current_weather.wind_speed))
                      .arg(rec.current_weather.wind_speed, 0, 'f', 1);

        if (categorie == "groupe_sensible") {
            message += "\n👶 Parfait pour un événement avec des enfants : temps stable et température agréable.";
        }

    } else {
        message = QString(
                      "⚠️ MÉTÉO DÉFAVORABLE POUR LA DATE PROPOSÉE\n\n"
                      "📅 Votre date : %1\n"
                      "🕐 Votre heure : %2\n\n"
                      "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
                      "📊 PRÉVISIONS POUR VOTRE DATE :\n"
                      "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n"
                      "%3 Conditions : %4\n\n"
                      "%5 Température : %6°C\n\n"
                      "%7 Pluie : %8%% ⚠️\n\n"
                      "%9 Vent : %10 km/h\n\n"
                      "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n"
                      "❌ Conditions NON RECOMMANDÉES pour un événement en extérieur.\n\n"
                      )
                      .arg(rec.current_weather.date.toString("dddd dd MMMM yyyy"))
                      .arg(rec.current_weather.heure.toString("HH:mm"))
                      .arg(getEmojiMeteo(rec.current_weather.weather_code))
                      .arg(rec.current_weather.weather_description)
                      .arg(getEmojiTemperature(rec.current_weather.temperature))
                      .arg(rec.current_weather.temperature, 0, 'f', 1)
                      .arg(getEmojiPluie(rec.current_weather.precipitation_probability))
                      .arg(rec.current_weather.precipitation_probability)
                      .arg(getEmojiVent(rec.current_weather.wind_speed))
                      .arg(rec.current_weather.wind_speed, 0, 'f', 1);

        if (!rec.alternative_date.isNull()) {
            int soleilPourcentage = 100 - rec.alternative_weather.precipitation_probability;

            message += QString(
                           "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
                           "✨ SUGGESTION DE DATE ALTERNATIVE :\n"
                           "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n"
                           "📅 Date recommandée : %1\n"
                           "🕐 Heure recommandée : %2\n\n"
                           "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
                           "📊 PRÉVISIONS POUR LA DATE SUGGÉRÉE :\n"
                           "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n"
                           "%3 Conditions : %4\n\n"
                           "%5 Température : %6°C\n\n"
                           "☀️ Soleil : %7%% ✨\n\n"
                           "%8 Pluie : %9%% ✅\n\n"
                           "%10 Vent : %11 km/h ✅\n\n"
                           "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n"
                           "✅ CONDITIONS IDÉALES pour votre événement !\n"
                           )
                           .arg(rec.alternative_weather.date.toString("dddd dd MMMM yyyy"))
                           .arg(rec.alternative_weather.heure.toString("HH:mm"))
                           .arg(getEmojiMeteo(rec.alternative_weather.weather_code))
                           .arg(rec.alternative_weather.weather_description)
                           .arg(getEmojiTemperature(rec.alternative_weather.temperature))
                           .arg(rec.alternative_weather.temperature, 0, 'f', 1)
                           .arg(soleilPourcentage)
                           .arg(getEmojiPluie(rec.alternative_weather.precipitation_probability))
                           .arg(rec.alternative_weather.precipitation_probability)
                           .arg(getEmojiVent(rec.alternative_weather.wind_speed))
                           .arg(rec.alternative_weather.wind_speed, 0, 'f', 1);

            if (categorie == "groupe_sensible") {
                message += "\n👶 Recommandé pour les enfants : temps stable et sécuritaire.";
            }
        } else {
            message += "\n❌ Aucune date alternative favorable trouvée dans les 16 prochains jours.";
        }
    }

    return message;
}

void MeteoAssistant::onMeteoRecue(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        emit erreurAnalyse("Erreur lors de la récupération des données météo: " +
                           reply->errorString());
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (doc.isNull() || !doc.isObject()) {
        emit erreurAnalyse("Données météo invalides");
        reply->deleteLater();
        return;
    }

    QJsonObject weatherData = doc.object();

    QString categorie = getCategorieEvenement(current_remarque, current_nomevent);

    QTime heureEvent = QTime::fromString(current_heure, "HH:mm");
    if (!heureEvent.isValid()) {
        heureEvent = QTime(14, 0);
    }

    MeteoRecommendation rec = trouverMeilleureDate(weatherData, current_date,
                                                   heureEvent, categorie);

    rec.message = genererMessage(rec, categorie);
    rec.explanation = "Analyse basée sur les prévisions météo pour " + current_nomevent;

    emit analyseTerminee(rec);

    reply->deleteLater();
    qDebug() << "Analyse météo terminée pour:" << current_nomevent;
}
