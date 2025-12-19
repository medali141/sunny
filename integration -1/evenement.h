#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QMap>

class Evenement
{
private:
    int IDEVENT;
    QString NOMEVENT;
    QDate DATEVENT;
    QString HEURE;
    QString RESPONSABLE;
    QString STATUT;
    QString REMARQUE;

public:
    // Constructors
    Evenement();
    Evenement(int idevent, const QString &nomevent, const QDate &datevent,
              const QString &heure, const QString &responsable,
              const QString &statut, const QString &remarque);

    // Getters
    int getIDEVENT() const { return IDEVENT; }
    QString getNOMEVENT() const { return NOMEVENT; }
    QDate getDATEVENT() const { return DATEVENT; }
    QString getHEURE() const { return HEURE; }
    QString getRESPONSABLE() const { return RESPONSABLE; }
    QString getSTATUT() const { return STATUT; }
    QString getREMARQUE() const { return REMARQUE; }

    // Setters
    void setIDEVENT(int id) { IDEVENT = id; }
    void setNOMEVENT(const QString &nom) { NOMEVENT = nom; }
    void setDATEVENT(const QDate &date) { DATEVENT = date; }
    void setHEURE(const QString &heure) { HEURE = heure; }
    void setRESPONSABLE(const QString &resp) { RESPONSABLE = resp; }
    void setSTATUT(const QString &statut) { STATUT = statut; }
    void setREMARQUE(const QString &rmq) { REMARQUE = rmq; }

    // CRUD Operations
    bool AjouterEvenement();
    QSqlQueryModel* AfficherEvenements();
    bool ModifierEvenement();
    bool SupprimerEvenement(const QString &IDEVENT);

    // Search Operation
    QSqlQueryModel* RechercherEvenements(const QString &searchText);

    // Statistique : Nombre d'événements par mois
    QMap<int, int> getStatistiquesParMois(int annee = 0);
};

#endif // EVENEMENT_H
