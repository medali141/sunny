#ifndef METEOASSISTANT_H
#define METEOASSISTANT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QString>

// Structure pour stocker les données météo
struct MeteoData {
    QDate date;
    QTime heure;
    double temperature;
    int precipitation_probability;
    double precipitation;
    double wind_speed;
    QString weather_description;
    int weather_code;
    bool is_suitable;
};

// Structure pour une recommandation
struct MeteoRecommendation {
    bool is_current_date_ok;
    QString message;
    QString explanation;
    QDate alternative_date;
    QTime alternative_time;
    MeteoData current_weather;
    MeteoData alternative_weather;
};

class MeteoAssistant : public QObject
{
    Q_OBJECT

public:
    explicit MeteoAssistant(QObject *parent = nullptr);
    ~MeteoAssistant();

    void analyserMeteoEvenement(const QString &remarque, const QDate &date,
                                const QString &heure, const QString &nomevent);

signals:
    void analyseTerminee(const MeteoRecommendation &recommendation);
    void erreurAnalyse(const QString &message);

private slots:
    void onMeteoRecue(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkManager;

    QString current_remarque;
    QDate current_date;
    QString current_heure;
    QString current_nomevent;

    bool estEvenementExterieur(const QString &remarque) const;
    QString getCategorieEvenement(const QString &remarque, const QString &nomevent) const;
    MeteoData extraireMeteoData(const QJsonObject &hourlyData, int index) const;
    bool estMeteoConvenable(const MeteoData &meteo, const QString &categorie) const;
    MeteoRecommendation trouverMeilleureDate(const QJsonObject &weatherData,
                                             const QDate &dateOriginale,
                                             const QTime &heureOriginale,
                                             const QString &categorie) const;
    QString getWeatherDescription(int weatherCode) const;
    QString getEmojiMeteo(int weatherCode) const;
    QString getEmojiPluie(int percentage) const;
    QString getEmojiVent(double windSpeed) const;
    QString getEmojiTemperature(double temp) const;
    QString genererMessage(const MeteoRecommendation &rec, const QString &categorie) const;

    const double LATITUDE = 36.8474;
    const double LONGITUDE = 11.0939;
};

#endif // METEOASSISTANT_H
