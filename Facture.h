#ifndef FACTURE_H
#define FACTURE_H

#include <string>
#include <fstream>
using namespace std;

// Classe qui représente une facture de location
class Facture
{
    private:
        int id;
        int idClient;
        string nomClient;
        int idVoiture;
        string voitureInfo;      // marque + modele
        bool avecChauffeur;
        string dateDebut;
        string dateFin;
        int nombreJours;
        double prixVoitureJour;
        double prixChauffeurJour;
        double totalVoiture;
        double totalChauffeur;
        double fraisSupp;
        double montantTotal;
        string statutLocation;   // "En cours", "Terminee"

    public:
        Facture();

        // ----- Getters -----
        int getId() const;
        int getIdClient() const;
        string getNomClient() const;
        int getIdVoiture() const;
        string getVoitureInfo() const;
        bool getAvecChauffeur() const;
        string getDateDebut() const;
        string getDateFin() const;
        int getNombreJours() const;
        double getPrixVoitureJour() const;
        double getPrixChauffeurJour() const;
        double getTotalVoiture() const;
        double getTotalChauffeur() const;
        double getFraisSupp() const;
        double getMontantTotal() const;
        string getStatutLocation() const;

        void setId(int nouvelId);

        // ----- Comportements -----
        // Enregistre les informations de la location et calcule les totaux
        void definirLocation(int idC, string nomC, int idV, string infoV,
                              bool avecCh, string debut, string fin, int jours,
                              double prixVJour, double prixChJour);

        void ajouterFraisSupplementaires(double frais);
        void terminerLocation();

        void afficherLigne() const;    // ligne de tableau
        void afficherDetail() const;   // detail complet

        void sauvegarder(ofstream &fichier) const;
        void chargerDepuisLigne(string ligneId, ifstream &fichier);
};

#endif
