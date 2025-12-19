#include "event.h"
#include "ui_event.h"
#include "evenement.h"
#include "connection.h"
#include "mainwindow.h"
#include "sponsor.h"
#include "participant.h"
#include "employe.h"
#include "matriel.h"
#include <QDebug>
#include <QMessageBox>
#include <QDate>
#include <QRegularExpressionValidator>
#include <QHeaderView>
#include <QSqlError>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QFile>
#include <QTextDocument>
#include <QPageSize>
#include <QVBoxLayout>
#include <QLabel>
#include <QtCharts>
#include <QTextEdit>

Event::Event(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Event)
    , meteoAssistant(new MeteoAssistant(this))
{
    ui->setupUi(this);

    // Ensure the table view exists in the UI
    if (ui->tableView_evenment) {
        ui->tableView_evenment->horizontalHeader()->setStretchLastSection(true);
        ui->tableView_evenment->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView_evenment->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableView_evenment->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }

    // Connecter les signaux de l'assistant météo
    connect(meteoAssistant, &MeteoAssistant::analyseTerminee,
            this, &Event::onAnalyseMeteoTerminee);
    connect(meteoAssistant, &MeteoAssistant::erreurAnalyse,
            this, &Event::onErreurMeteo);

    // Connect Logout button to back function
    if (ui->pushButton_56) {
        connect(ui->pushButton_56, &QPushButton::clicked, this, &Event::on_backButton_clicked);
    }

    rafraichirTableEvenements();
    installerValidationsEvenements();
}

Event::~Event()
{
    delete ui;
}

void Event::installerValidationsEvenements()
{
    if(ui->nomevent) ui->nomevent->setMaxLength(100);
    if(ui->heureevent) ui->heureevent->setMaxLength(10);
    if(ui->respevent) ui->respevent->setMaxLength(100);
    if(ui->statutevent) ui->statutevent->setMaxLength(50);
    if(ui->rmqevent) ui->rmqevent->setMaxLength(200);
}

void Event::rafraichirTableEvenements()
{
    Evenement evenement;
    QSqlQueryModel *model = evenement.AfficherEvenements();
    if (model) {
        if (model->lastError().isValid()) {
            QMessageBox::critical(this, "Erreur SQL", model->lastError().text());
        }
        if(ui->tableView_evenment) {
            ui->tableView_evenment->setModel(model);
            ui->tableView_evenment->resizeColumnsToContents();
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible de créer le modèle de données");
    }
}

void Event::rechercherEvenements(const QString &searchText)
{
    if (searchText.trimmed().isEmpty()) {
        rafraichirTableEvenements();
        return;
    }
    Evenement evenement;
    QSqlQueryModel *model = evenement.RechercherEvenements(searchText);
    if (model) {
        if (model->lastError().isValid()) {
            QMessageBox::critical(this, "Erreur SQL", model->lastError().text());
        }
        if(ui->tableView_evenment) {
            ui->tableView_evenment->setModel(model);
            ui->tableView_evenment->resizeColumnsToContents();
        }
    }
}

void Event::on_rechercherevent_textChanged(const QString &text)
{
    rechercherEvenements(text);
}

void Event::on_pdf_clicked()
{
    exporterPDF();
}

void Event::on_btnAjouterEvenement_clicked()
{
    QString nomevent = ui->nomevent->text().trimmed();
    QDate datevent = ui->dateevent->date();
    QString heure = ui->heureevent->text().trimmed();
    QString responsable = ui->respevent->text().trimmed();
    QString statut = ui->statutevent->text().trimmed();
    QString remarque = ui->rmqevent->text().trimmed();

    if (nomevent.isEmpty()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Le nom de l'événement est obligatoire."));
        return;
    }
    if (responsable.isEmpty()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Le responsable est obligatoire."));
        return;
    }
    if (statut.isEmpty()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Le statut est obligatoire."));
        return;
    }

    Evenement evenement(0, nomevent, datevent, heure, responsable, statut, remarque);
    if (evenement.AjouterEvenement()) {
        QMessageBox::information(this, tr("Succès"), tr("Événement ajouté avec succès."));
        rafraichirTableEvenements();
        ui->nomevent->clear();
        ui->dateevent->setDate(QDate::currentDate());
        ui->heureevent->clear();
        ui->respevent->clear();
        ui->statutevent->clear();
        ui->rmqevent->clear();
        ui->selectedidevent->clear();
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de l'ajout de l'événement."));
    }
}

void Event::on_tableView_evenment_clicked(const QModelIndex &index)
{
    if (!index.isValid()) return;

    QString id = ui->tableView_evenment->model()->data(
                                                    ui->tableView_evenment->model()->index(index.row(), 0)).toString();
    ui->selectedidevent->setText(id);

    QString nom = ui->tableView_evenment->model()->data(
                                                     ui->tableView_evenment->model()->index(index.row(), 1)).toString();
    QString dateStr = ui->tableView_evenment->model()->data(
                                                         ui->tableView_evenment->model()->index(index.row(), 2)).toString();
    QDate date = QDate::fromString(dateStr, "dd/MM/yyyy");
    QString heure = ui->tableView_evenment->model()->data(
                                                       ui->tableView_evenment->model()->index(index.row(), 3)).toString();
    QString resp = ui->tableView_evenment->model()->data(
                                                      ui->tableView_evenment->model()->index(index.row(), 4)).toString();
    QString statut = ui->tableView_evenment->model()->data(
                                                        ui->tableView_evenment->model()->index(index.row(), 5)).toString();
    QString rmq = ui->tableView_evenment->model()->data(
                                                     ui->tableView_evenment->model()->index(index.row(), 6)).toString();

    ui->nomevent->setText(nom);
    ui->dateevent->setDate(date);
    ui->heureevent->setText(heure);
    ui->respevent->setText(resp);
    ui->statutevent->setText(statut);
    ui->rmqevent->setText(rmq);
}

void Event::on_btnModifierEvenement_clicked()
{
    QString id_text = ui->selectedidevent->text().trimmed();
    if (id_text.isEmpty()) {
        QMessageBox::warning(this, tr("Attention"), tr("Veuillez sélectionner un événement."));
        return;
    }

    int id = id_text.toInt();
    QString nomevent = ui->nomevent->text().trimmed();
    QDate datevent = ui->dateevent->date();
    QString heure = ui->heureevent->text().trimmed();
    QString responsable = ui->respevent->text().trimmed();
    QString statut = ui->statutevent->text().trimmed();
    QString remarque = ui->rmqevent->text().trimmed();

    if (nomevent.isEmpty() || responsable.isEmpty() || statut.isEmpty()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Champs obligatoires manquants."));
        return;
    }

    Evenement evenement(id, nomevent, datevent, heure, responsable, statut, remarque);
    if (evenement.ModifierEvenement()) {
        QMessageBox::information(this, tr("Succès"), tr("Événement modifié avec succès."));
        rafraichirTableEvenements();
        ui->nomevent->clear();
        ui->dateevent->setDate(QDate::currentDate());
        ui->heureevent->clear();
        ui->respevent->clear();
        ui->statutevent->clear();
        ui->rmqevent->clear();
        ui->selectedidevent->clear();
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de la modification."));
    }
}

void Event::on_btnSupprimerEvenement_clicked()
{
    QString id_text = ui->selectedidevent->text().trimmed();
    if (id_text.isEmpty()) {
        QMessageBox::warning(this, tr("Attention"), tr("Veuillez sélectionner un événement."));
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation",
                                                              "Supprimer cet événement?",
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        Evenement evenement;
        if (evenement.SupprimerEvenement(id_text)) {
            QMessageBox::information(this, tr("Succès"), tr("Événement supprimé."));
            rafraichirTableEvenements();
            ui->nomevent->clear();
            ui->dateevent->setDate(QDate::currentDate());
            ui->heureevent->clear();
            ui->respevent->clear();
            ui->statutevent->clear();
            ui->rmqevent->clear();
            ui->selectedidevent->clear();
        } else {
            QMessageBox::critical(this, tr("Erreur"), tr("Échec de la suppression."));
        }
    }
}

// ==================== FONCTIONNALITÉ MÉTÉO ====================

void Event::on_btnAnalyserMeteo_clicked()
{
    QString remarque = ui->rmqevent->text().trimmed();
    QDate date = ui->dateevent->date();
    QString heure = ui->heureevent->text().trimmed();
    QString nomevent = ui->nomevent->text().trimmed();

    if (remarque.isEmpty()) {
        QMessageBox::information(this, "Information",
                                 "Veuillez saisir une remarque pour analyser la météo.\n\n"
                                 "Exemple: 'dehors', 'extérieur', 'plein air', 'jardin', etc.");
        return;
    }

    if (nomevent.isEmpty()) {
        QMessageBox::warning(this, "Attention",
                             "Veuillez saisir le nom de l'événement.");
        return;
    }

    if (date < QDate::currentDate()) {
        QMessageBox::warning(this, "Attention",
                             "La date de l'événement est dans le passé.\n"
                             "Veuillez choisir une date future.");
        return;
    }

    QString rmqLower = remarque.toLower();
    bool isExterieur = rmqLower.contains("dehors") || rmqLower.contains("extérieur") ||
                       rmqLower.contains("exterieur") || rmqLower.contains("plein air") ||
                       rmqLower.contains("jardin") || rmqLower.contains("parc") ||
                       rmqLower.contains("terrasse") || rmqLower.contains("plage");

    if (!isExterieur) {
        QMessageBox::information(this, "Information",
                                 "Cette fonctionnalité analyse la météo pour les événements en extérieur.\n\n"
                                 "Ajoutez un mot-clé comme 'dehors', 'extérieur', 'plein air' dans la remarque.");
        return;
    }

    QMessageBox *loadingBox = new QMessageBox(this);
    loadingBox->setWindowTitle("Analyse en cours");
    loadingBox->setText("🌤️ Analyse météo en cours...\n\n"
                        "Consultation des prévisions météorologiques...");
    loadingBox->setStandardButtons(QMessageBox::NoButton);
    loadingBox->setModal(true);
    loadingBox->show();

    meteoAssistant->analyserMeteoEvenement(remarque, date, heure, nomevent);
}

void Event::onAnalyseMeteoTerminee(const MeteoRecommendation &recommendation)
{
    QList<QMessageBox*> messageBoxes = findChildren<QMessageBox*>();
    for (QMessageBox *box : messageBoxes) {
        if (box->windowTitle() == "Analyse en cours") {
            box->close();
            box->deleteLater();
        }
    }

    QDialog *resultDialog = new QDialog(this);
    resultDialog->setWindowTitle("🌤️ Analyse Météo - " + ui->nomevent->text());
    resultDialog->setMinimumSize(700, 600);
    resultDialog->setStyleSheet(
        "QDialog { background-color: #f0f4f8; }"
        "QTextEdit { "
        "   padding: 20px; "
        "   font-family: 'Segoe UI', Arial, sans-serif; "
        "   font-size: 13px; "
        "   line-height: 1.6; "
        "   color: #000000; "
        "}"
        "QPushButton { "
        "   padding: 12px 25px; "
        "   font-size: 14px; "
        "   border-radius: 5px; "
        "   font-weight: bold; "
        "}"
        "QPushButton#btnAccepter { background-color: #4CAF50; color: white; }"
        "QPushButton#btnGarder { background-color: #2196F3; color: white; }"
        "QPushButton#btnFermer { background-color: #607D8B; color: white; }"
        "QPushButton:hover { opacity: 0.85; }"
        );

    QVBoxLayout *layout = new QVBoxLayout(resultDialog);

    QLabel *titleLabel = new QLabel("🌤️ ANALYSE MÉTÉOROLOGIQUE DÉTAILLÉE");
    titleLabel->setStyleSheet(
        "font-size: 18px; "
        "font-weight: bold; "
        "color: #1976D2; "
        "padding: 15px; "
        "background-color: white; "
        "border-radius: 8px; "
        "border-bottom: 3px solid #1976D2;"
        );
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    QTextEdit *messageText = new QTextEdit();
    messageText->setPlainText(recommendation.message);
    messageText->setReadOnly(true);
    messageText->setStyleSheet(
        "background-color: white; "
        "border-radius: 8px; "
        "border: 2px solid #e0e0e0; "
        "color: #000000;"
        );
    layout->addWidget(messageText);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    if (!recommendation.is_current_date_ok && !recommendation.alternative_date.isNull()) {
        QPushButton *btnAccepter = new QPushButton("✅ Accepter la date suggérée");
        btnAccepter->setObjectName("btnAccepter");
        btnAccepter->setCursor(Qt::PointingHandCursor);

        QPushButton *btnGarder = new QPushButton("📅 Garder la date originale");
        btnGarder->setObjectName("btnGarder");
        btnGarder->setCursor(Qt::PointingHandCursor);

        connect(btnAccepter, &QPushButton::clicked, [this, recommendation, resultDialog]() {
            ui->dateevent->setDate(recommendation.alternative_date);
            ui->heureevent->setText(recommendation.alternative_time.toString("HH:mm"));

            QMessageBox::information(this, "✅ Date mise à jour",
                                     QString("La date a été mise à jour au :\n\n"
                                             "📅 %1\n"
                                             "🕐 %2")
                                         .arg(recommendation.alternative_date.toString("dddd dd MMMM yyyy"))
                                         .arg(recommendation.alternative_time.toString("HH:mm")));
            resultDialog->accept();
        });

        connect(btnGarder, &QPushButton::clicked, [resultDialog]() {
            resultDialog->accept();
        });

        buttonLayout->addWidget(btnAccepter);
        buttonLayout->addWidget(btnGarder);
    } else {
        QPushButton *btnFermer = new QPushButton("Fermer");
        btnFermer->setObjectName("btnFermer");
        btnFermer->setCursor(Qt::PointingHandCursor);
        connect(btnFermer, &QPushButton::clicked, resultDialog, &QDialog::accept);
        buttonLayout->addWidget(btnFermer);
    }

    layout->addLayout(buttonLayout);

    QLabel *noteLabel = new QLabel(
        "💡 Note : Cette analyse utilise les prévisions météo en temps réel "
        "pour la région de Kélibia, Tunisie. Les prévisions sont mises à jour "
        "régulièrement.");
    noteLabel->setWordWrap(true);
    noteLabel->setStyleSheet(
        "font-size: 11px; "
        "color: #666; "
        "padding: 12px; "
        "background-color: #fff3cd; "
        "border-radius: 5px; "
        "border: 1px solid #ffc107;"
        );
    layout->addWidget(noteLabel);

    resultDialog->setLayout(layout);
    resultDialog->exec();
    resultDialog->deleteLater();
}

void Event::onErreurMeteo(const QString &message)
{
    QList<QMessageBox*> messageBoxes = findChildren<QMessageBox*>();
    for (QMessageBox *box : messageBoxes) {
        if (box->windowTitle() == "Analyse en cours") {
            box->close();
            box->deleteLater();
        }
    }

    QMessageBox::warning(this, "Erreur d'analyse météo",
                         "Impossible d'analyser la météo :\n\n" + message +
                             "\n\nVérifiez votre connexion internet.");
}

// ==================== FIN FONCTIONNALITÉ MÉTÉO ====================
// ==================== PDF, STATISTIQUES, EXPORT ICS ====================

void Event::exporterPDF()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exporter en PDF"),
                                                    "evenements.pdf", tr("Fichiers PDF (*.pdf)"));
    if (fileName.isEmpty()) return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);

    QString html = "<html><head><meta charset='UTF-8'><style>";
    html += "body { font-family: Arial, sans-serif; margin: 20px; }";
    html += "h1 { color: #2c3e50; text-align: center; border-bottom: 3px solid #3498db; padding-bottom: 10px; }";
    html += "table { width: 100%; border-collapse: collapse; margin-top: 20px; }";
    html += "th { background-color: #3498db; color: white; padding: 12px; text-align: left; }";
    html += "td { padding: 10px; border-bottom: 1px solid #ddd; }";
    html += "tr:nth-child(even) { background-color: #f2f2f2; }";
    html += ".footer { margin-top: 30px; text-align: center; font-size: 10px; color: #7f8c8d; }";
    html += ".info { background-color: #ecf0f1; padding: 10px; border-radius: 5px; margin-bottom: 20px; }";
    html += "</style></head><body>";

    html += "<h1>Liste des Événements</h1>";
    html += "<div class='info'><strong>Date d'export:</strong> " + QDate::currentDate().toString("dd/MM/yyyy");
    html += "<br><strong>Nombre total:</strong> " + QString::number(ui->tableView_evenment->model()->rowCount()) + "</div>";

    html += "<table><thead><tr><th>ID</th><th>Nom</th><th>Date</th><th>Heure</th>";
    html += "<th>Responsable</th><th>Statut</th><th>Remarque</th></tr></thead><tbody>";

    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->tableView_evenment->model());
    if (model) {
        for (int row = 0; row < model->rowCount(); ++row) {
            html += "<tr>";
            for (int col = 0; col < model->columnCount(); ++col) {
                html += "<td>" + model->data(model->index(row, col)).toString() + "</td>";
            }
            html += "</tr>";
        }
    }
    html += "</tbody></table>";
    html += "<div class='footer'><p>Document généré automatiquement - © 2025</p></div></body></html>";

    QTextDocument document;
    document.setHtml(html);
    document.print(&printer);

    QMessageBox::information(this, tr("Succès"), tr("PDF exporté avec succès !\n\nFichier: ") + fileName);
}

void Event::on_btnStatistiques_clicked()
{
    afficherStatistiquesParMois();
}

void Event::afficherStatistiquesParMois()
{
    QDialog *statsDialog = new QDialog(this);
    statsDialog->setWindowTitle("Statistiques des Événements par Mois");
    statsDialog->setMinimumSize(800, 500);
    statsDialog->setStyleSheet("background-color: #f5f6fa;");

    QVBoxLayout *layout = new QVBoxLayout(statsDialog);

    QLabel *titleLabel = new QLabel("Nombre d'Evenements par Mois - Annee " +
                                    QString::number(QDate::currentDate().year()));
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; "
                              "padding: 15px; background-color: white; border-radius: 8px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    Evenement e;
    QMap<int, int> stats = e.getStatistiquesParMois();

    QBarSet *set = new QBarSet("Evenements");
    set->setColor(QColor("#3498db"));

    QStringList mois;
    mois << "Jan" << "Fev" << "Mar" << "Avr" << "Mai" << "Jun"
         << "Jul" << "Aou" << "Sep" << "Oct" << "Nov" << "Dec";

    int maxVal = 0;
    for (int i = 1; i <= 12; i++) {
        *set << stats[i];
        if (stats[i] > maxVal) {
            maxVal = stats[i];
        }
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundBrush(QBrush(Qt::white));

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(mois);
    axisX->setTitleText("Mois");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, maxVal + 2);
    axisY->setLabelFormat("%d");
    axisY->setTitleText("Nombre d'evenements");
    axisY->setTickCount(maxVal + 3);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(750, 400);

    layout->addWidget(chartView);

    int total = 0;
    for (int i = 1; i <= 12; i++) {
        total += stats[i];
    }
    QLabel *totalLabel = new QLabel("Total des evenements cette annee: " + QString::number(total));
    totalLabel->setStyleSheet("font-size: 14px; color: #27ae60; padding: 10px; "
                              "background-color: white; border-radius: 5px;");
    totalLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(totalLabel);

    statsDialog->setLayout(layout);
    statsDialog->exec();
}

void Event::on_btnExportCalendar_clicked()
{
    exporterCalendrierICS();
}

void Event::exporterCalendrierICS()
{
    // Récupérer le modèle du tableau
    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->tableView_evenment->model());

    if (!model || model->rowCount() == 0) {
        QMessageBox::warning(this, tr("Attention"),
                             tr("Aucun événement à exporter."));
        return;
    }

    // Demander où sauvegarder le fichier
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Exporter tous les événements vers Calendrier"),
                                                    "tous_evenements.ics",
                                                    tr("Fichier iCalendar (*.ics)"));

    if (fileName.isEmpty()) {
        return;
    }

    // Début du fichier ICS
    QString icsContent;
    icsContent += "BEGIN:VCALENDAR\r\n";
    icsContent += "VERSION:2.0\r\n";
    icsContent += "PRODID:-//Sunny Desk//Event Manager//FR\r\n";
    icsContent += "CALSCALE:GREGORIAN\r\n";
    icsContent += "METHOD:PUBLISH\r\n";

    // Parcourir TOUS les événements du tableau
    int nombreExportes = 0;

    for (int row = 0; row < model->rowCount(); ++row) {
        // Récupérer les données de chaque événement
        QString id = model->data(model->index(row, 0)).toString();
        QString nomevent = model->data(model->index(row, 1)).toString();
        QString dateStr = model->data(model->index(row, 2)).toString();
        QString heure = model->data(model->index(row, 3)).toString();
        QString responsable = model->data(model->index(row, 4)).toString();
        QString statut = model->data(model->index(row, 5)).toString();
        QString remarque = model->data(model->index(row, 6)).toString();

        // Convertir la date (format dd/MM/yyyy -> QDate)
        QDate datevent = QDate::fromString(dateStr, "dd/MM/yyyy");
        if (!datevent.isValid()) {
            qDebug() << "Date invalide pour l'événement" << id << ":" << dateStr;
            continue; // Passer à l'événement suivant
        }

        // Convertir l'heure
        QTime timeEvent;
        if (!heure.isEmpty()) {
            timeEvent = QTime::fromString(heure, "HH:mm");
            if (!timeEvent.isValid()) {
                timeEvent = QTime::fromString(heure, "HH:mm:ss");
            }
            if (!timeEvent.isValid()) {
                timeEvent = QTime(9, 0); // Par défaut 9h00
            }
        } else {
            timeEvent = QTime(9, 0);
        }

        // Créer DateTime
        QDateTime dtStart(datevent, timeEvent);
        QDateTime dtEnd = dtStart.addSecs(3600); // +1 heure

        // Générer UID unique
        QString uid = QString("event-%1-%2@sunnydesk.com")
                          .arg(id)
                          .arg(QDateTime::currentDateTime().toSecsSinceEpoch());

        // Convertir au format iCalendar
        QString dtStartStr = dtStart.toString("yyyyMMdd'T'HHmmss");
        QString dtEndStr = dtEnd.toString("yyyyMMdd'T'HHmmss");
        QString dtStampStr = QDateTime::currentDateTime().toString("yyyyMMdd'T'HHmmss");

        // Ajouter l'événement au fichier ICS
        icsContent += "BEGIN:VEVENT\r\n";
        icsContent += "UID:" + uid + "\r\n";
        icsContent += "DTSTAMP:" + dtStampStr + "\r\n";
        icsContent += "DTSTART:" + dtStartStr + "\r\n";
        icsContent += "DTEND:" + dtEndStr + "\r\n";
        icsContent += "SUMMARY:" + nomevent + "\r\n";

        // Description avec toutes les infos
        QString description = "Responsable: " + responsable;
        if (!statut.isEmpty()) {
            description += " - Statut: " + statut;
        }
        if (!remarque.isEmpty()) {
            description += " - Remarque: " + remarque;
        }
        icsContent += "DESCRIPTION:" + description + "\r\n";

        icsContent += "ORGANIZER;CN=" + responsable + ":mailto:contact@sunnydesk.com\r\n";
        icsContent += "STATUS:CONFIRMED\r\n";
        icsContent += "END:VEVENT\r\n";

        nombreExportes++;
    }

    // Fin du fichier ICS
    icsContent += "END:VCALENDAR\r\n";

    // Écrire le fichier
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << icsContent;
        file.close();

        QMessageBox::information(this, tr("Succès"),
                                 tr("✅ %1 événement(s) exporté(s) avec succès !\n\n"
                                    "Fichier: %2\n\n"
                                    "Vous pouvez ouvrir ce fichier avec:\n"
                                    "- Google Calendar (via navigateur)\n"
                                    "- Microsoft Outlook\n"
                                    "- Calendrier Windows\n\n"
                                    "Tous vos événements seront ajoutés automatiquement !")
                                     .arg(nombreExportes)
                                     .arg(fileName));
    } else {
        QMessageBox::critical(this, tr("Erreur"),
                              tr("Impossible de créer le fichier:\n%1").arg(fileName));
    }
}

void Event::on_backButton_clicked()
{
    MainWindow *mw = new MainWindow();
    mw->show();
    this->close();
}

void Event::on_btnsponsor_clicked()
{
    Sponsor *sponsorWindow = new Sponsor();
    sponsorWindow->show();
    this->close();
}


void Event::on_btnevenement_clicked()
{
    // Already on Event page, no navigation needed
    // Could refresh the page or do nothing
}


void Event::on_btnparticipants_clicked()
{
    Participant *participantWindow = new Participant();
    participantWindow->show();
    this->close();
}


void Event::on_btnemploye_clicked()
{
    Employe *employeWindow = new Employe();
    employeWindow->show();
    this->close();
}


void Event::on_btnlogistique_clicked()
{
    Matriel *matrielWindow = new Matriel();
    matrielWindow->show();
    this->close();
}

