#include "employe.h"
#include "ui_employe.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QRegularExpression>
#include <QPixmap>
#include <QPalette>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QGroupBox>
#include <QDateEdit>
#include <QSplitter>
#include <QTextEdit>
#include <QFont>
#include <QFrame>
#include <QScrollArea>
#include <QDateTime>
#include <algorithm>

// ========================================
// CONSTRUCTEUR ET DESTRUCTEUR
// ========================================

Employe::Employe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Employe)
{
    ui->setupUi(this);

    // Afficher tous les employés initialement
    ui->tabMAT->setModel(afficher());

    // Appliquer l'image de fond
    QPixmap bkgnd(":/images/rs/background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    // Connexions manuelles des boutons
    connect(ui->statistiquesButton, &QPushButton::clicked, this, &Employe::on_statistiquesButton_clicked);
    connect(ui->assignationAutoButton, &QPushButton::clicked, this, &Employe::on_assignationAutoButton_clicked);
    connect(ui->congesButton, &QPushButton::clicked, this, &Employe::on_congesButton_clicked);
}

Employe::~Employe()
{
    delete ui;
}

// ========================================
// NAVIGATION
// ========================================

void Employe::on_backButton_clicked()
{
    MainWindow *mw = new MainWindow();
    mw->show();
    this->close();
}

// ========================================
// OPÉRATIONS CRUD - AJOUT
// ========================================

bool Employe::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYE (ID_EMPLOYE, NOM, POSTE, EMAIL, STATUT_DEM)"
                  "VALUES (:id, :nom, :poste, :email, :statut)");
    query.bindValue(":id", ui->idE->text().trimmed());
    query.bindValue(":nom", ui->nom->text().trimmed());
    query.bindValue(":poste", ui->poste->text().trimmed());
    query.bindValue(":email", ui->email->text().trimmed());
    query.bindValue(":statut", ui->statut_dem->text().trimmed());

    return query.exec();
}

void Employe::on_ajoutMat_clicked()
{
    QString id = ui->idE->text().trimmed();
    QString nom = ui->nom->text().trimmed();
    QString poste = ui->poste->text().trimmed();
    QString email = ui->email->text().trimmed();
    QString statut = ui->statut_dem->text().trimmed();

    // Validation
    if (id.isEmpty() || nom.isEmpty() || poste.isEmpty() || email.isEmpty() || statut.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Tous les champs doivent être remplis !");
        return;
    }

    if (id.length() < 6) {
        QMessageBox::warning(this, "Erreur", "L'ID doit contenir au moins 6 caractères !");
        return;
    }

    if (statut.toLower() != "passe" && statut.toLower() != "en attente") {
        QMessageBox::warning(this, "Erreur", "Le statut doit être 'passe' ou 'en attente' !");
        return;
    }

    QRegularExpression emailRegex(R"((\w+)(\.?\w*)@(\w+)\.(\w+))");
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Adresse email invalide !");
        return;
    }

    // Ajout
    if (ajouter()) {
        QMessageBox::information(this, "Succès", "Employé ajouté avec succès !");
        ui->tabMAT->setModel(afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de l'ajout.");
    }
}

// ========================================
// OPÉRATIONS CRUD - MODIFICATION
// ========================================

bool Employe::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYE SET NOM = :nom, POSTE = :poste, EMAIL = :email, STATUT_DEM = :statut "
                  "WHERE ID_EMPLOYE = :id");
    query.bindValue(":id", ui->idE->text().trimmed());
    query.bindValue(":nom", ui->nom->text().trimmed());
    query.bindValue(":poste", ui->poste->text().trimmed());
    query.bindValue(":email", ui->email->text().trimmed());
    query.bindValue(":statut", ui->statut_dem->text().trimmed());

    return query.exec();
}

void Employe::on_modifierMat_clicked()
{
    QString id = ui->idE->text().trimmed();
    QString nom = ui->nom->text().trimmed();
    QString poste = ui->poste->text().trimmed();
    QString email = ui->email->text().trimmed();
    QString statut = ui->statut_dem->text().trimmed();

    // Validation
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "ID est obligatoire pour la modification !");
        return;
    }

    if (id.length() < 6) {
        QMessageBox::warning(this, "Erreur", "L'ID doit contenir au moins 6 caractères !");
        return;
    }

    if (statut.toLower() != "passe" && statut.toLower() != "en attente") {
        QMessageBox::warning(this, "Erreur", "Le statut doit être 'passe' ou 'en attente' !");
        return;
    }

    QRegularExpression emailRegex(R"((\w+)(\.?\w*)@(\w+)\.(\w+))");
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Adresse email invalide !");
        return;
    }

    if (modifier()) {
        QMessageBox::information(this, "Succès", "Employé modifié avec succès !");
        ui->tabMAT->setModel(afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la modification.");
    }
}

// ========================================
// OPÉRATIONS CRUD - SUPPRESSION
// ========================================

bool Employe::supprimer()
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYE WHERE ID_EMPLOYE = :id");
    query.bindValue(":id", ui->idMAT_Delete->text().trimmed());
    return query.exec();
}

void Employe::on_supprimerMat_clicked()
{
    QString id = ui->idMAT_Delete->text().trimmed();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID à supprimer !");
        return;
    }

    if (supprimer()) {
        QMessageBox::information(this, "Succès", "Employé supprimé avec succès !");
        ui->tabMAT->setModel(afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression.");
    }
}

// ========================================
// OPÉRATIONS CRUD - AFFICHAGE
// ========================================

void Employe::on_afficherMar_clicked()
{
    ui->tabMAT->setModel(afficher());
}

QSqlQueryModel* Employe::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EMPLOYE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("POSTE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("STATUT_DEM"));
    return model;
}

// ========================================
// OPÉRATIONS CRUD - RECHERCHE
// ========================================

QSqlQueryModel* Employe::rechercher()
{
    QString id = ui->recherch_id->text().trimmed();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID pour la recherche !");
        return afficher();
    }

    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE WHERE ID_EMPLOYE LIKE :id");
    query.bindValue(":id", "%" + id + "%");
    query.exec();
    model->setQuery(query);
    return model;
}

void Employe::on_rechID_clicked()
{
    ui->tabMAT->setModel(rechercher());
}

// ========================================
// STATISTIQUES GRAPHIQUES
// ========================================

void Employe::on_statistiquesButton_clicked()
{
    afficherStatistiques();
}

void Employe::afficherStatistiques()
{
    // Créer une fenêtre de dialogue pour les graphiques
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Statistiques des Employés");
    dialog->resize(900, 600);

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);

    // ===== GRAPHIQUE 1 : Répartition par Poste (Barres) =====
    QBarSet *barSet = new QBarSet("Nombre d'employés");
    QStringList postes;
    QSqlQuery query;

    query.exec("SELECT POSTE, COUNT(*) FROM EMPLOYE GROUP BY POSTE ORDER BY POSTE");
    while (query.next()) {
        postes << query.value(0).toString();
        *barSet << query.value(1).toInt();
    }

    QBarSeries *barSeries = new QBarSeries();
    barSeries->append(barSet);
    barSet->setColor(QColor(41, 128, 185)); // Bleu

    QChart *barChart = new QChart();
    barChart->addSeries(barSeries);
    barChart->setTitle("Répartition des Employés par Poste");
    barChart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(postes);
    barChart->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Nombre d'employés");
    axisY->setLabelFormat("%d");
    barChart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);

    QChartView *barChartView = new QChartView(barChart);
    barChartView->setRenderHint(QPainter::Antialiasing);
    barChartView->setMinimumHeight(250);

    // ===== GRAPHIQUE 2 : Répartition par Statut (Camembert) =====
    QPieSeries *pieSeries = new QPieSeries();

    query.exec("SELECT STATUT_DEM, COUNT(*) FROM EMPLOYE GROUP BY STATUT_DEM");
    while (query.next()) {
        QString statut = query.value(0).toString();
        int count = query.value(1).toInt();
        QPieSlice *slice = pieSeries->append(statut + " (" + QString::number(count) + ")", count);
        slice->setLabelVisible(true);
    }

    // Couleurs personnalisées
    QList<QPieSlice*> slices = pieSeries->slices();
    if (slices.size() > 0) slices[0]->setColor(QColor(46, 204, 113)); // Vert
    if (slices.size() > 1) slices[1]->setColor(QColor(241, 196, 15)); // Jaune

    QChart *pieChart = new QChart();
    pieChart->addSeries(pieSeries);
    pieChart->setTitle("Répartition par Statut de Demande");
    pieChart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *pieChartView = new QChartView(pieChart);
    pieChartView->setRenderHint(QPainter::Antialiasing);
    pieChartView->setMinimumHeight(250);

    // Ajouter les graphiques au layout
    mainLayout->addWidget(barChartView);
    mainLayout->addWidget(pieChartView);

    dialog->setLayout(mainLayout);
    dialog->exec();
}
// ========================================
// ASSIGNATION AUTOMATIQUE
// Copiez ce code dans employe.cpp APRÈS les statistiques
// ========================================

void Employe::on_assignationAutoButton_clicked()
{
    afficherAssignationAuto();
}

double Employe::calculerScore(int tachesEnCours, int tachesReussies,
                              double moyennePerf, bool posteCorrespond)
{
    double score = 0.0;

    // 1. Disponibilité (40 points max)
    if (tachesEnCours == 0) {
        score += 40.0;
    } else if (tachesEnCours <= 2) {
        score += 30.0;
    } else if (tachesEnCours <= 4) {
        score += 20.0;
    } else {
        score += 10.0;
    }

    // 2. Expérience (30 points max)
    if (tachesReussies >= 20) {
        score += 30.0;
    } else if (tachesReussies >= 10) {
        score += 25.0;
    } else if (tachesReussies >= 5) {
        score += 20.0;
    } else if (tachesReussies > 0) {
        score += 15.0;
    } else {
        score += 10.0;
    }

    // 3. Performance (20 points max)
    if (moyennePerf > 0) {
        score += (moyennePerf / 10.0) * 20.0;
    } else {
        score += 10.0;
    }

    // 4. Correspondance du poste (10 points bonus)
    if (posteCorrespond) {
        score += 10.0;
    }

    return score;
}

QList<EmployeScore> Employe::calculerScoresEmployes(const QString &posteRequis)
{
    QList<EmployeScore> employes;

    QSqlQuery query;
    query.prepare("SELECT "
                  "e.ID_EMPLOYE, "
                  "e.NOM, "
                  "e.POSTE, "
                  "COUNT(CASE WHEN t.STATUT = 'En cours' THEN 1 END) as TACHES_EN_COURS, "
                  "COUNT(CASE WHEN h.STATUT_COMPLETION = 'Réussi' THEN 1 END) as TACHES_REUSSIES, "
                  "ROUND(AVG(NVL(h.NOTE_PERFORMANCE, 5)), 2) as MOYENNE_PERFORMANCE "
                  "FROM EMPLOYE e "
                  "LEFT JOIN TACHE t ON e.ID_EMPLOYE = t.ID_EMPLOYE_ASSIGNE AND t.STATUT = 'En cours' "
                  "LEFT JOIN HISTORIQUE_ASSIGNATION h ON e.ID_EMPLOYE = h.ID_EMPLOYE "
                  "WHERE e.STATUT_DEM = 'passe' "
                  "GROUP BY e.ID_EMPLOYE, e.NOM, e.POSTE "
                  "ORDER BY e.ID_EMPLOYE");

    if (query.exec()) {
        while (query.next()) {
            EmployeScore emp;
            emp.id = query.value(0).toString();
            emp.nom = query.value(1).toString();
            emp.poste = query.value(2).toString();
            emp.tachesEnCours = query.value(3).toInt();
            emp.tachesReussies = query.value(4).toInt();
            emp.moyennePerformance = query.value(5).toDouble();

            // Déterminer la disponibilité
            if (emp.tachesEnCours == 0) {
                emp.disponibilite = "Disponible";
            } else if (emp.tachesEnCours <= 2) {
                emp.disponibilite = "Peu occupé";
            } else if (emp.tachesEnCours <= 4) {
                emp.disponibilite = "Moyennement occupé";
            } else {
                emp.disponibilite = "Très occupé";
            }

            // Calculer le score total
            bool posteCorrespond = (posteRequis.isEmpty() ||
                                    emp.poste.toLower() == posteRequis.toLower());
            emp.scoreTotal = calculerScore(emp.tachesEnCours, emp.tachesReussies,
                                           emp.moyennePerformance, posteCorrespond);

            employes.append(emp);
        }
    }

    // Trier par score décroissant
    std::sort(employes.begin(), employes.end(),
              [](const EmployeScore &a, const EmployeScore &b) {
                  return a.scoreTotal > b.scoreTotal;
              });

    return employes;
}

void Employe::afficherAssignationAuto()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Système d'Assignation Automatique");
    dialog->resize(1000, 600);

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);

    // En-tête
    QLabel *titleLabel = new QLabel(
        "<h2>🎯 Recommandation d'Assignation Intelligente</h2>");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    QLabel *descLabel = new QLabel(
        "Ce système analyse automatiquement tous les employés et recommande "
        "le meilleur candidat basé sur leur disponibilité, expérience et performance.");
    descLabel->setWordWrap(true);
    descLabel->setStyleSheet("padding: 10px; background-color: #e8f4f8; "
                             "border-radius: 5px; margin-bottom: 10px;");
    mainLayout->addWidget(descLabel);

    // Sélection du poste
    QGroupBox *filterGroup = new QGroupBox("Filtres de recherche");
    QHBoxLayout *filterLayout = new QHBoxLayout();

    QLabel *posteLabel = new QLabel("Poste requis :");
    QComboBox *posteCombo = new QComboBox();
    posteCombo->addItem("Tous les postes", "");

    QSqlQuery posteQuery("SELECT DISTINCT POSTE FROM EMPLOYE ORDER BY POSTE");
    while (posteQuery.next()) {
        QString poste = posteQuery.value(0).toString();
        posteCombo->addItem(poste, poste);
    }

    QPushButton *rechercherBtn = new QPushButton("Rechercher");
    rechercherBtn->setStyleSheet("background-color: #3498db; color: white; "
                                 "padding: 8px 20px; border-radius: 4px;");

    filterLayout->addWidget(posteLabel);
    filterLayout->addWidget(posteCombo);
    filterLayout->addWidget(rechercherBtn);
    filterLayout->addStretch();
    filterGroup->setLayout(filterLayout);
    mainLayout->addWidget(filterGroup);

    // Tableau des résultats
    QTableWidget *tableWidget = new QTableWidget();
    tableWidget->setColumnCount(8);
    tableWidget->setHorizontalHeaderLabels({
        "Rang", "ID", "Nom", "Poste", "Tâches en cours",
        "Tâches réussies", "Perf. Moy.", "Score Total"
    });

    tableWidget->horizontalHeader()->setStretchLastSection(false);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableWidget->setAlternatingRowColors(true);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    mainLayout->addWidget(tableWidget);

    // Label pour le meilleur employé
    QLabel *meilleurLabel = new QLabel();
    meilleurLabel->setStyleSheet("padding: 15px; background-color: #d5f4e6; "
                                 "border: 2px solid #27ae60; border-radius: 5px; "
                                 "font-weight: bold; font-size: 14px;");
    meilleurLabel->setWordWrap(true);
    mainLayout->addWidget(meilleurLabel);

    // Fonction pour charger les données
    auto chargerDonnees = [=]() {
        QString posteRequis = posteCombo->currentData().toString();
        QList<EmployeScore> employes = calculerScoresEmployes(posteRequis);

        tableWidget->setRowCount(employes.size());

        for (int i = 0; i < employes.size(); ++i) {
            const EmployeScore &emp = employes[i];

            QTableWidgetItem *rangItem = new QTableWidgetItem(QString::number(i + 1));
            rangItem->setTextAlignment(Qt::AlignCenter);
            if (i == 0) {
                rangItem->setBackground(QColor(46, 204, 113, 100));
                rangItem->setForeground(QColor(0, 100, 0));
            } else if (i == 1) {
                rangItem->setBackground(QColor(52, 152, 219, 100));
            } else if (i == 2) {
                rangItem->setBackground(QColor(241, 196, 15, 100));
            }
            tableWidget->setItem(i, 0, rangItem);

            tableWidget->setItem(i, 1, new QTableWidgetItem(emp.id));
            tableWidget->setItem(i, 2, new QTableWidgetItem(emp.nom));
            tableWidget->setItem(i, 3, new QTableWidgetItem(emp.poste));

            QTableWidgetItem *tachesItem = new QTableWidgetItem(
                QString::number(emp.tachesEnCours));
            tachesItem->setTextAlignment(Qt::AlignCenter);
            tableWidget->setItem(i, 4, tachesItem);

            QTableWidgetItem *reussiesItem = new QTableWidgetItem(
                QString::number(emp.tachesReussies));
            reussiesItem->setTextAlignment(Qt::AlignCenter);
            tableWidget->setItem(i, 5, reussiesItem);

            QTableWidgetItem *perfItem = new QTableWidgetItem(
                QString::number(emp.moyennePerformance, 'f', 2));
            perfItem->setTextAlignment(Qt::AlignCenter);
            tableWidget->setItem(i, 6, perfItem);

            QTableWidgetItem *scoreItem = new QTableWidgetItem(
                QString::number(emp.scoreTotal, 'f', 1));
            scoreItem->setTextAlignment(Qt::AlignCenter);
            scoreItem->setForeground(QColor(41, 128, 185));
            tableWidget->setItem(i, 7, scoreItem);
        }

        if (!employes.isEmpty()) {
            const EmployeScore &meilleur = employes.first();
            meilleurLabel->setText(QString(
                                       "✅ <b>RECOMMANDATION :</b> %1 (%2) est le candidat idéal "
                                       "avec un score de <b>%3/100</b><br>"
                                       "📊 Statut: %4 | Expérience: %5 tâches réussies | "
                                       "Performance moyenne: %6/10")
                                       .arg(meilleur.nom)
                                       .arg(meilleur.id)
                                       .arg(QString::number(meilleur.scoreTotal, 'f', 1))
                                       .arg(meilleur.disponibilite)
                                       .arg(meilleur.tachesReussies)
                                       .arg(QString::number(meilleur.moyennePerformance, 'f', 1)));
        } else {
            meilleurLabel->setText("⚠️ Aucun employé trouvé avec ces critères.");
        }
    };

    connect(rechercherBtn, &QPushButton::clicked, chargerDonnees);
    chargerDonnees();

    QPushButton *closeBtn = new QPushButton("Fermer");
    closeBtn->setStyleSheet("background-color: #95a5a6; color: white; "
                            "padding: 8px 30px; border-radius: 4px;");
    connect(closeBtn, &QPushButton::clicked, dialog, &QDialog::accept);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(closeBtn);
    mainLayout->addLayout(btnLayout);

    dialog->setLayout(mainLayout);
    dialog->exec();
}
// ========================================
// GESTION DES CONGÉS - FONCTIONS UTILITAIRES
// Copiez ce code dans employe.cpp APRÈS l'assignation automatique
// ========================================

void Employe::on_congesButton_clicked()
{
    afficherGestionConges();
}

int Employe::compterEmployesPresents(const QDate &dateDebut, const QDate &dateFin)
{
    QSqlQuery query;

    // Compter le nombre total d'employés actifs
    query.exec("SELECT COUNT(*) FROM EMPLOYE WHERE STATUT_DEM = 'passe'");
    int totalEmployes = 0;
    if (query.next()) {
        totalEmployes = query.value(0).toInt();
    }

    // Compter combien d'employés seront absents pendant cette période
    query.prepare(
        "SELECT COUNT(DISTINCT ID_EMPLOYE) FROM DEMANDE_CONGE "
        "WHERE STATUT = 'ACCEPTE' "
        "AND NOT (DATE_FIN < :debut OR DATE_DEBUT > :fin)"
        );
    query.bindValue(":debut", dateDebut.toString("yyyy-MM-dd"));
    query.bindValue(":fin", dateFin.toString("yyyy-MM-dd"));
    query.exec();

    int employesAbsents = 0;
    if (query.next()) {
        employesAbsents = query.value(0).toInt();
    }

    return totalEmployes - employesAbsents;
}

int Employe::getSoldeConges(const QString &idEmploye)
{
    QSqlQuery query;
    query.prepare(
        "SELECT JOURS_RESTANTS FROM SOLDE_CONGE "
        "WHERE ID_EMPLOYE = :id AND ANNEE = :annee"
        );
    query.bindValue(":id", idEmploye);
    query.bindValue(":annee", QDate::currentDate().year());
    query.exec();

    if (query.next()) {
        return query.value(0).toInt();
    }

    // Si pas de solde trouvé, initialiser avec 30 jours
    QSqlQuery insertQuery;
    insertQuery.prepare(
        "INSERT INTO SOLDE_CONGE (ID_SOLDE, ID_EMPLOYE, ANNEE, JOURS_ACQUIS, JOURS_PRIS, JOURS_RESTANTS) "
        "VALUES (:idSolde, :idEmp, :annee, 30, 0, 30)"
        );
    QString idSolde = "SC" + QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    insertQuery.bindValue(":idSolde", idSolde);
    insertQuery.bindValue(":idEmp", idEmploye);
    insertQuery.bindValue(":annee", QDate::currentDate().year());
    insertQuery.exec();

    return 30;
}

ResultatVerificationConge Employe::verifierDemandeConge(const QString &idEmploye,
                                                        const QDate &dateDebut,
                                                        const QDate &dateFin)
{
    ResultatVerificationConge resultat;
    resultat.estValide = false;

    // 1. Vérifier que l'employé existe
    QSqlQuery checkEmp;
    checkEmp.prepare("SELECT NOM FROM EMPLOYE WHERE ID_EMPLOYE = :id AND STATUT_DEM = 'passe'");
    checkEmp.bindValue(":id", idEmploye);
    checkEmp.exec();

    if (!checkEmp.next()) {
        resultat.message = "❌ Employé introuvable ou inactif !";
        resultat.employesPresents = 0;
        resultat.joursRestants = 0;
        return resultat;
    }

    QString nomEmploye = checkEmp.value(0).toString();

    // 2. Vérifier que les dates sont valides
    if (dateDebut < QDate::currentDate()) {
        resultat.message = "❌ La date de début ne peut pas être dans le passé !";
        resultat.employesPresents = 0;
        resultat.joursRestants = 0;
        return resultat;
    }

    if (dateFin < dateDebut) {
        resultat.message = "❌ La date de fin doit être après la date de début !";
        resultat.employesPresents = 0;
        resultat.joursRestants = 0;
        return resultat;
    }

    // 3. Calculer le nombre de jours demandés
    int nbJours = dateDebut.daysTo(dateFin) + 1;

    // 4. Vérifier le solde de congés
    int soldeRestant = getSoldeConges(idEmploye);
    resultat.joursRestants = soldeRestant;

    if (nbJours > soldeRestant) {
        resultat.message = QString("❌ Solde insuffisant ! Vous demandez %1 jours mais il vous reste %2 jours.")
                               .arg(nbJours).arg(soldeRestant);
        resultat.employesPresents = compterEmployesPresents(dateDebut, dateFin);
        return resultat;
    }

    // 5. Vérifier qu'il n'y a pas déjà une demande
    QSqlQuery checkDemande;
    checkDemande.prepare(
        "SELECT COUNT(*) FROM DEMANDE_CONGE "
        "WHERE ID_EMPLOYE = :id "
        "AND STATUT IN ('EN_ATTENTE', 'ACCEPTE') "
        "AND NOT (DATE_FIN < :debut OR DATE_DEBUT > :fin)"
        );
    checkDemande.bindValue(":id", idEmploye);
    checkDemande.bindValue(":debut", dateDebut.toString("yyyy-MM-dd"));
    checkDemande.bindValue(":fin", dateFin.toString("yyyy-MM-dd"));
    checkDemande.exec();

    if (checkDemande.next() && checkDemande.value(0).toInt() > 0) {
        resultat.message = "❌ Vous avez déjà une demande de congé pour cette période !";
        resultat.employesPresents = compterEmployesPresents(dateDebut, dateFin);
        return resultat;
    }

    // 6. RÈGLE MÉTIER : Vérifier le minimum de 3 employés présents
    int employesPresents = compterEmployesPresents(dateDebut, dateFin) - 1;
    resultat.employesPresents = employesPresents;

    if (employesPresents < 3) {
        resultat.message = QString(
                               "❌ CONGÉ REFUSÉ - Règle de présence minimale\n\n"
                               "Seulement %1 employé(s) serai(en)t présent(s) si votre congé est accepté.\n"
                               "⚠️ Minimum requis : 3 employés présents\n\n"
                               "Suggestion : Choisissez une autre période avec plus de disponibilités."
                               ).arg(employesPresents);
        return resultat;
    }

    // 7. Tout est OK !
    resultat.estValide = true;
    resultat.message = QString(
                           "👤 Employé : %1 (%2)\n"
                           "📅 Période : %3 au %4\n"
                           "📊 Durée : %5 jour(s)\n"
                           "💼 Employés présents : %6 employés\n"
                           "🏖️ Solde restant après : %7 jour(s)\n\n"
                           "Votre demande peut être enregistrée."
                           ).arg(nomEmploye)
                           .arg(idEmploye)
                           .arg(dateDebut.toString("dd/MM/yyyy"))
                           .arg(dateFin.toString("dd/MM/yyyy"))
                           .arg(nbJours)
                           .arg(employesPresents)
                           .arg(soldeRestant - nbJours);

    return resultat;
}

bool Employe::enregistrerDemandeConge(const QString &idEmploye,
                                      const QDate &dateDebut,
                                      const QDate &dateFin,
                                      const QString &statut,
                                      const QString &motif)
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO DEMANDE_CONGE "
        "(ID_DEMANDE, ID_EMPLOYE, DATE_DEBUT, DATE_FIN, STATUT, MOTIF_REFUS, DATE_TRAITEMENT) "
        "VALUES (:id, :emp, :debut, :fin, :statut, :motif, SYSDATE)"
        );

    QString idDemande = "DC" + QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    query.bindValue(":id", idDemande);
    query.bindValue(":emp", idEmploye);
    query.bindValue(":debut", dateDebut.toString("yyyy-MM-dd"));
    query.bindValue(":fin", dateFin.toString("yyyy-MM-dd"));
    query.bindValue(":statut", statut);
    query.bindValue(":motif", motif);

    return query.exec();
}

QSqlQueryModel* Employe::getSoldesConges()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(
        "SELECT "
        "    e.ID_EMPLOYE, "
        "    e.NOM, "
        "    e.POSTE, "
        "    NVL(sc.JOURS_RESTANTS, 30) as JOURS_RESTANTS, "
        "    NVL(sc.JOURS_PRIS, 0) as JOURS_PRIS "
        "FROM EMPLOYE e "
        "LEFT JOIN SOLDE_CONGE sc ON e.ID_EMPLOYE = sc.ID_EMPLOYE "
        "    AND sc.ANNEE = " + QString::number(QDate::currentDate().year()) + " "
                                                         "WHERE e.STATUT_DEM = 'passe' "
                                                         "ORDER BY JOURS_RESTANTS ASC"
        );

    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Poste");
    model->setHeaderData(3, Qt::Horizontal, "Jours Restants");
    model->setHeaderData(4, Qt::Horizontal, "Jours Pris");

    return model;
}

QSqlQueryModel* Employe::getHistoriqueConges()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(
        "SELECT "
        "    dc.ID_EMPLOYE, "
        "    e.NOM, "
        "    TO_CHAR(dc.DATE_DEBUT, 'DD/MM/YYYY') as DEBUT, "
        "    TO_CHAR(dc.DATE_FIN, 'DD/MM/YYYY') as FIN, "
        "    dc.NB_JOURS, "
        "    dc.STATUT, "
        "    dc.MOTIF_REFUS "
        "FROM DEMANDE_CONGE dc "
        "INNER JOIN EMPLOYE e ON dc.ID_EMPLOYE = e.ID_EMPLOYE "
        "ORDER BY dc.DATE_DEMANDE DESC "
        "FETCH FIRST 20 ROWS ONLY"
        );

    model->setHeaderData(0, Qt::Horizontal, "ID Employé");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Date Début");
    model->setHeaderData(3, Qt::Horizontal, "Date Fin");
    model->setHeaderData(4, Qt::Horizontal, "Nb Jours");
    model->setHeaderData(5, Qt::Horizontal, "Statut");
    model->setHeaderData(6, Qt::Horizontal, "Motif Refus");

    return model;
}

    // INTERFACE GRAPHIQUE - GESTIONNAIRE DE CONGÉS OPTION 4
    // Copiez CETTE FONCTION COMPLÈTE dans employe.cpp APRÈS les fonctions utilitaires
    // ========================================

    void Employe::afficherGestionConges()
{
    // Créer la fenêtre principale
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("🏖️ Gestionnaire de Congés Intelligent");
    dialog->resize(1200, 700);
    dialog->setStyleSheet("QDialog { background-color: #f5f7fa; }");

    QHBoxLayout *mainLayout = new QHBoxLayout(dialog);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(15, 15, 15, 15);

    // ============================================
    // PARTIE GAUCHE : FORMULAIRE (40%)
    // ============================================
    QWidget *leftWidget = new QWidget();
    leftWidget->setMaximumWidth(480);
    leftWidget->setStyleSheet("QWidget { background-color: white; border-radius: 10px; }");
    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->setSpacing(20);
    leftLayout->setContentsMargins(25, 25, 25, 25);

    // Titre
    QLabel *leftTitle = new QLabel("📝 NOUVELLE DEMANDE DE CONGÉ");
    leftTitle->setStyleSheet(
        "font-size: 16px; font-weight: bold; color: #2c3e50; "
        "padding: 10px; background-color: #ecf0f1; border-radius: 5px;");
    leftTitle->setAlignment(Qt::AlignCenter);
    leftLayout->addWidget(leftTitle);

    // Formulaire
    QWidget *formWidget = new QWidget();
    QVBoxLayout *formLayout = new QVBoxLayout(formWidget);
    formLayout->setSpacing(20);

    // ID Employé
    QLabel *lblID = new QLabel("👤 ID Employé :");
    lblID->setStyleSheet("font-weight: bold; color: #34495e; font-size: 13px;");
    QLineEdit *idInput = new QLineEdit();
    idInput->setPlaceholderText("Ex: EMP001");
    idInput->setStyleSheet(
        "QLineEdit { padding: 12px; font-size: 14px; border: 2px solid #bdc3c7; "
        "border-radius: 6px; background-color: #f8f9fa; }"
        "QLineEdit:focus { border-color: #3498db; background-color: white; }");
    formLayout->addWidget(lblID);
    formLayout->addWidget(idInput);

    // Date début
    QLabel *lblDebut = new QLabel("📅 Date début :");
    lblDebut->setStyleSheet("font-weight: bold; color: #34495e; font-size: 13px;");
    QDateEdit *dateDebutInput = new QDateEdit(QDate::currentDate());
    dateDebutInput->setCalendarPopup(true);
    dateDebutInput->setDisplayFormat("dd/MM/yyyy");
    dateDebutInput->setStyleSheet(
        "QDateEdit { padding: 12px; font-size: 14px; border: 2px solid #bdc3c7; "
        "border-radius: 6px; background-color: #f8f9fa; }"
        "QDateEdit:focus { border-color: #3498db; background-color: white; }");
    formLayout->addWidget(lblDebut);
    formLayout->addWidget(dateDebutInput);

    // Date fin
    QLabel *lblFin = new QLabel("📅 Date fin :");
    lblFin->setStyleSheet("font-weight: bold; color: #34495e; font-size: 13px;");
    QDateEdit *dateFinInput = new QDateEdit(QDate::currentDate().addDays(7));
    dateFinInput->setCalendarPopup(true);
    dateFinInput->setDisplayFormat("dd/MM/yyyy");
    dateFinInput->setStyleSheet(
        "QDateEdit { padding: 12px; font-size: 14px; border: 2px solid #bdc3c7; "
        "border-radius: 6px; background-color: #f8f9fa; }"
        "QDateEdit:focus { border-color: #3498db; background-color: white; }");
    formLayout->addWidget(lblFin);
    formLayout->addWidget(dateFinInput);

    leftLayout->addWidget(formWidget);

    // Bouton Vérifier
    QPushButton *verifierBtn = new QPushButton("🔍 VÉRIFIER LA DEMANDE");
    verifierBtn->setStyleSheet(
        "QPushButton { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "stop:0 #3498db, stop:1 #2980b9); color: white; font-weight: bold; "
        "padding: 15px; border-radius: 8px; font-size: 15px; border: none; }"
        "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "stop:0 #5dade2, stop:1 #3498db); }"
        "QPushButton:pressed { background-color: #2471a3; }");
    verifierBtn->setCursor(Qt::PointingHandCursor);
    verifierBtn->setMinimumHeight(50);
    leftLayout->addWidget(verifierBtn);

    // Zone de résultat
    QLabel *lblResultat = new QLabel("RÉSULTAT :");
    lblResultat->setStyleSheet("font-weight: bold; color: #34495e; font-size: 13px; margin-top: 10px;");
    leftLayout->addWidget(lblResultat);

    QTextEdit *resultatText = new QTextEdit();
    resultatText->setReadOnly(true);
    resultatText->setMaximumHeight(200);
    resultatText->setStyleSheet(
        "QTextEdit { background-color: #f8f9fa; border: 2px solid #ddd; "
        "border-radius: 8px; padding: 15px; font-size: 13px; }");
    resultatText->setPlaceholderText("Le résultat de la vérification s'affichera ici...");
    leftLayout->addWidget(resultatText);

    // Bouton Enregistrer
    QPushButton *enregistrerBtn = new QPushButton("✅ ENREGISTRER LA DEMANDE");
    enregistrerBtn->setStyleSheet(
        "QPushButton { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "stop:0 #27ae60, stop:1 #229954); color: white; font-weight: bold; "
        "padding: 15px; border-radius: 8px; font-size: 15px; border: none; }"
        "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "stop:0 #2ecc71, stop:1 #27ae60); }"
        "QPushButton:pressed { background-color: #1e8449; }"
        "QPushButton:disabled { background-color: #95a5a6; }");
    enregistrerBtn->setCursor(Qt::PointingHandCursor);
    enregistrerBtn->setMinimumHeight(50);
    enregistrerBtn->setEnabled(false);
    leftLayout->addWidget(enregistrerBtn);

    leftLayout->addStretch();

    // ============================================
    // PARTIE DROITE : ÉTAT DES CONGÉS (60%)
    // ============================================
    QWidget *rightWidget = new QWidget();
    rightWidget->setStyleSheet("QWidget { background-color: white; border-radius: 10px; }");
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);
    rightLayout->setSpacing(15);
    rightLayout->setContentsMargins(25, 25, 25, 25);

    // Titre
    QLabel *rightTitle = new QLabel("📊 ÉTAT DES CONGÉS - TOUS LES EMPLOYÉS");
    rightTitle->setStyleSheet(
        "font-size: 16px; font-weight: bold; color: #2c3e50; "
        "padding: 10px; background-color: #ecf0f1; border-radius: 5px;");
    rightTitle->setAlignment(Qt::AlignCenter);
    rightLayout->addWidget(rightTitle);

    // Zone scrollable
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet(
        "QScrollArea { border: none; background-color: transparent; }"
        "QScrollBar:vertical { background-color: #ecf0f1; width: 10px; border-radius: 5px; }"
        "QScrollBar::handle:vertical { background-color: #bdc3c7; border-radius: 5px; }"
        "QScrollBar::handle:vertical:hover { background-color: #95a5a6; }");

    QWidget *scrollContent = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent);
    scrollLayout->setSpacing(12);
    scrollLayout->setContentsMargins(0, 0, 10, 0);

    // Charger les données des employés
    QSqlQuery query;
    query.exec(
        "SELECT "
        "    e.ID_EMPLOYE, e.NOM, e.POSTE, "
        "    NVL(sc.JOURS_RESTANTS, 30) as JOURS_RESTANTS, "
        "    NVL(sc.JOURS_PRIS, 0) as JOURS_PRIS, "
        "    (SELECT TO_CHAR(MAX(dc.DATE_FIN), 'DD Mon') "
        "     FROM DEMANDE_CONGE dc "
        "     WHERE dc.ID_EMPLOYE = e.ID_EMPLOYE AND dc.STATUT = 'ACCEPTE' "
        "       AND dc.DATE_FIN < SYSDATE) as DERNIER_CONGE, "
        "    (SELECT TO_CHAR(MIN(dc.DATE_DEBUT), 'DD Mon') "
        "     FROM DEMANDE_CONGE dc "
        "     WHERE dc.ID_EMPLOYE = e.ID_EMPLOYE AND dc.STATUT = 'ACCEPTE' "
        "       AND dc.DATE_DEBUT > SYSDATE) as PROCHAIN_CONGE "
        "FROM EMPLOYE e "
        "LEFT JOIN SOLDE_CONGE sc ON e.ID_EMPLOYE = sc.ID_EMPLOYE "
        "    AND sc.ANNEE = " + QString::number(QDate::currentDate().year()) + " "
                                                         "WHERE e.STATUT_DEM = 'passe' "
                                                         "ORDER BY JOURS_RESTANTS ASC"
        );

    int employeCount = 0;
    while (query.next()) {
        employeCount++;

        QString idEmp = query.value(0).toString();
        QString nom = query.value(1).toString();
        QString poste = query.value(2).toString();
        int joursRestants = query.value(3).toInt();
        int joursPris = query.value(4).toInt();
        QString dernierConge = query.value(5).toString();
        QString prochainConge = query.value(6).toString();

        // Déterminer couleur et icône
        QString couleurBordure, couleurFond, iconeStatut, texteStatut;

        if (joursRestants > 15) {
            couleurBordure = "#27ae60";
            couleurFond = "#d5f4e6";
            iconeStatut = "✅";
            texteStatut = QString::number(joursRestants) + " jours disponibles - Bon solde";
        } else if (joursRestants >= 8) {
            couleurBordure = "#f39c12";
            couleurFond = "#fdebd0";
            iconeStatut = "⚠️";
            texteStatut = QString::number(joursRestants) + " jours disponibles - Solde moyen";
        } else {
            couleurBordure = "#e74c3c";
            couleurFond = "#fadbd8";
            iconeStatut = "🚨";
            texteStatut = QString::number(joursRestants) + " jours disponibles - Solde faible !";
        }

        // Créer la fiche employé
        QFrame *ficheEmploye = new QFrame();
        ficheEmploye->setStyleSheet(QString(
                                        "QFrame { background-color: %1; border-left: 5px solid %2; "
                                        "border-radius: 8px; padding: 15px; }"
                                        ).arg(couleurFond, couleurBordure));
        ficheEmploye->setFrameShape(QFrame::StyledPanel);

        QVBoxLayout *ficheLayout = new QVBoxLayout(ficheEmploye);
        ficheLayout->setSpacing(8);
        ficheLayout->setContentsMargins(10, 10, 10, 10);

        // Nom et Poste
        QLabel *lblNomPoste = new QLabel(QString("🎯 <b>%1</b> - %2").arg(nom, poste));
        lblNomPoste->setStyleSheet("font-size: 14px; color: #2c3e50; font-weight: bold;");
        ficheLayout->addWidget(lblNomPoste);

        // Statut du solde
        QLabel *lblStatut = new QLabel(QString("%1 <b>%2</b>").arg(iconeStatut, texteStatut));
        lblStatut->setStyleSheet("font-size: 13px; color: #34495e;");
        ficheLayout->addWidget(lblStatut);

        // Détails
        QString details;
        if (!dernierConge.isEmpty() && !prochainConge.isEmpty()) {
            details = QString("📅 Dernier : %1 | Prochain : %2").arg(dernierConge, prochainConge);
        } else if (!dernierConge.isEmpty()) {
            details = QString("📅 Dernier congé : %1").arg(dernierConge);
        } else if (!prochainConge.isEmpty()) {
            details = QString("📅 Prochain congé : %1").arg(prochainConge);
        } else {
            details = QString("💡 Congés utilisés : %1 jour(s)").arg(joursPris);
        }

        QLabel *lblDetails = new QLabel(details);
        lblDetails->setStyleSheet("font-size: 12px; color: #7f8c8d;");
        ficheLayout->addWidget(lblDetails);

        // ID
        QLabel *lblID = new QLabel(QString("<i>ID: %1</i>").arg(idEmp));
        lblID->setStyleSheet("font-size: 11px; color: #95a5a6;");
        ficheLayout->addWidget(lblID);

        scrollLayout->addWidget(ficheEmploye);
    }

    // Message si aucun employé
    if (employeCount == 0) {
        QLabel *noDataLabel = new QLabel(
            "⚠️ Aucun employé trouvé\n\nAjoutez des employés pour voir leurs congés.");
        noDataLabel->setAlignment(Qt::AlignCenter);
        noDataLabel->setStyleSheet("color: #7f8c8d; font-size: 14px; padding: 40px;");
        scrollLayout->addWidget(noDataLabel);
    }

    scrollLayout->addStretch();
    scrollContent->setLayout(scrollLayout);
    scrollArea->setWidget(scrollContent);
    rightLayout->addWidget(scrollArea);

    // ============================================
    // ASSEMBLAGE ET LOGIQUE
    // ============================================
    mainLayout->addWidget(leftWidget, 4);
    mainLayout->addWidget(rightWidget, 6);

    ResultatVerificationConge *dernierResultat = new ResultatVerificationConge();

    // Fonction de rafraîchissement
    auto rafraichirEtatConges = [scrollLayout, scrollContent]() {
        QLayoutItem *item;
        while ((item = scrollLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }

        QSqlQuery query;
        query.exec(
            "SELECT e.ID_EMPLOYE, e.NOM, e.POSTE, "
            "NVL(sc.JOURS_RESTANTS, 30) as JOURS_RESTANTS, "
            "NVL(sc.JOURS_PRIS, 0) as JOURS_PRIS, "
            "(SELECT TO_CHAR(MAX(dc.DATE_FIN), 'DD Mon') FROM DEMANDE_CONGE dc "
            " WHERE dc.ID_EMPLOYE = e.ID_EMPLOYE AND dc.STATUT = 'ACCEPTE' "
            " AND dc.DATE_FIN < SYSDATE) as DERNIER_CONGE, "
            "(SELECT TO_CHAR(MIN(dc.DATE_DEBUT), 'DD Mon') FROM DEMANDE_CONGE dc "
            " WHERE dc.ID_EMPLOYE = e.ID_EMPLOYE AND dc.STATUT = 'ACCEPTE' "
            " AND dc.DATE_DEBUT > SYSDATE) as PROCHAIN_CONGE "
            "FROM EMPLOYE e LEFT JOIN SOLDE_CONGE sc ON e.ID_EMPLOYE = sc.ID_EMPLOYE "
            "AND sc.ANNEE = " + QString::number(QDate::currentDate().year()) + " "
                                                             "WHERE e.STATUT_DEM = 'passe' ORDER BY JOURS_RESTANTS ASC"
            );

        while (query.next()) {
            QString idEmp = query.value(0).toString();
            QString nom = query.value(1).toString();
            QString poste = query.value(2).toString();
            int joursRestants = query.value(3).toInt();
            int joursPris = query.value(4).toInt();
            QString dernierConge = query.value(5).toString();
            QString prochainConge = query.value(6).toString();

            QString couleurBordure, couleurFond, iconeStatut, texteStatut;

            if (joursRestants > 15) {
                couleurBordure = "#27ae60"; couleurFond = "#d5f4e6"; iconeStatut = "✅";
                texteStatut = QString::number(joursRestants) + " jours disponibles - Bon solde";
            } else if (joursRestants >= 8) {
                couleurBordure = "#f39c12"; couleurFond = "#fdebd0"; iconeStatut = "⚠️";
                texteStatut = QString::number(joursRestants) + " jours disponibles - Solde moyen";
            } else {
                couleurBordure = "#e74c3c"; couleurFond = "#fadbd8"; iconeStatut = "🚨";
                texteStatut = QString::number(joursRestants) + " jours disponibles - Solde faible !";
            }

            QFrame *ficheEmploye = new QFrame();
            ficheEmploye->setStyleSheet(QString(
                                            "QFrame { background-color: %1; border-left: 5px solid %2; "
                                            "border-radius: 8px; padding: 15px; }"
                                            ).arg(couleurFond, couleurBordure));

            QVBoxLayout *ficheLayout = new QVBoxLayout(ficheEmploye);
            ficheLayout->setSpacing(8);

            QLabel *lblNomPoste = new QLabel(QString("🎯 <b>%1</b> - %2").arg(nom, poste));
            lblNomPoste->setStyleSheet("font-size: 14px; color: #2c3e50; font-weight: bold;");
            ficheLayout->addWidget(lblNomPoste);

            QLabel *lblStatut = new QLabel(QString("%1 <b>%2</b>").arg(iconeStatut, texteStatut));
            lblStatut->setStyleSheet("font-size: 13px; color: #34495e;");
            ficheLayout->addWidget(lblStatut);

            QString details;
            if (!dernierConge.isEmpty() && !prochainConge.isEmpty()) {
                details = QString("📅 Dernier : %1 | Prochain : %2").arg(dernierConge, prochainConge);
            } else if (!dernierConge.isEmpty()) {
                details = QString("📅 Dernier congé : %1").arg(dernierConge);
            } else if (!prochainConge.isEmpty()) {
                details = QString("📅 Prochain congé : %1").arg(prochainConge);
            } else {
                details = QString("💡 Congés utilisés : %1 jour(s)").arg(joursPris);
            }

            QLabel *lblDetails = new QLabel(details);
            lblDetails->setStyleSheet("font-size: 12px; color: #7f8c8d;");
            ficheLayout->addWidget(lblDetails);

            QLabel *lblID = new QLabel(QString("<i>ID: %1</i>").arg(idEmp));
            lblID->setStyleSheet("font-size: 11px; color: #95a5a6;");
            ficheLayout->addWidget(lblID);

            scrollLayout->addWidget(ficheEmploye);
        }
        scrollLayout->addStretch();
    };

    // Bouton Vérifier
    connect(verifierBtn, &QPushButton::clicked, [=]() mutable {
        QString id = idInput->text().trimmed();
        QDate debut = dateDebutInput->date();
        QDate fin = dateFinInput->date();

        if (id.isEmpty()) {
            resultatText->setHtml(
                "<div style='background-color: #fadbd8; border-left: 4px solid #e74c3c; "
                "padding: 15px; border-radius: 5px;'>"
                "<p style='color: #c0392b; font-weight: bold; margin: 0;'>❌ Veuillez entrer un ID employé !</p>"
                "</div>");
            enregistrerBtn->setEnabled(false);
            return;
        }

        *dernierResultat = verifierDemandeConge(id, debut, fin);

        if (dernierResultat->estValide) {
            resultatText->setHtml(
                "<div style='background-color: #d5f4e6; border-left: 4px solid #27ae60; "
                "padding: 15px; border-radius: 5px;'>"
                "<p style='color: #1e8449; font-weight: bold; font-size: 16px; margin: 0 0 10px 0;'>"
                "🟢 CONGÉ VALIDÉ</p>"
                "<pre style='font-family: Arial; font-size: 13px; white-space: pre-wrap; "
                "color: #155724; margin: 0;'>" + dernierResultat->message + "</pre></div>");
            enregistrerBtn->setEnabled(true);
        } else {
            resultatText->setHtml(
                "<div style='background-color: #fadbd8; border-left: 4px solid #e74c3c; "
                "padding: 15px; border-radius: 5px;'>"
                "<p style='color: #c0392b; font-weight: bold; font-size: 16px; margin: 0 0 10px 0;'>"
                "🔴 CONGÉ REFUSÉ</p>"
                "<pre style='font-family: Arial; font-size: 13px; white-space: pre-wrap; "
                "color: #721c24; margin: 0;'>" + dernierResultat->message + "</pre></div>");
            enregistrerBtn->setEnabled(false);
        }
    });

    // Bouton Enregistrer
    connect(enregistrerBtn, &QPushButton::clicked, [=]() {
        QString id = idInput->text().trimmed();
        QDate debut = dateDebutInput->date();
        QDate fin = dateFinInput->date();

        QString statut = dernierResultat->estValide ? "ACCEPTE" : "REFUSE";
        QString motif = dernierResultat->estValide ? "" : dernierResultat->message;

        if (enregistrerDemandeConge(id, debut, fin, statut, motif)) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Succès");
            msgBox.setText("✅ Demande de congé enregistrée avec succès !");
            msgBox.setInformativeText("Statut : " + statut);
            msgBox.setIcon(QMessageBox::Information);
            msgBox.exec();

            rafraichirEtatConges();

            idInput->clear();
            dateDebutInput->setDate(QDate::currentDate());
            dateFinInput->setDate(QDate::currentDate().addDays(7));
            resultatText->clear();
            enregistrerBtn->setEnabled(false);
        } else {
            QMessageBox::warning(dialog, "Erreur",
                                 "❌ Échec de l'enregistrement de la demande.");
        }
    });

    dialog->setLayout(mainLayout);
    dialog->exec();

    delete dernierResultat;
}
