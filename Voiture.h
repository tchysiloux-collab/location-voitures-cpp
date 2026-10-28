#ifndef VOITURE_H
#define VOITURE_H

#include <string>
#include <fstream>
using namespace std;

// Classe qui représente une voiture de l'agence
class Voiture
{
    private:
        int id;
        string marque;
        string modele;
        int annee;
        string immatriculation;
        string couleur;
        double prixJour;
        string statut; // "Disponible", "Louee", "Maintenance"

    public:
        Voiture();

        // ----- Getters -----
        int getId() const;
        string getMarque() const;
        string getModele() const;
        int getAnnee() const;
        string getImmatriculation() const;
        string getCouleur() const;
        double getPrixJour() const;
        string getStatut() const;

        // ----- Setters -----
        void setId(int nouvelId);
        void setMarque(string nouvelleMarque);
        void setModele(string nouveauModele);
        void setAnnee(int nouvelleAnnee);
        void setImmatriculation(string nouvelleImmat);
        void setCouleur(string nouvelleCouleur);
        void setPrixJour(double nouveauPrix);
        void setStatut(string nouveauStatut);

        // ----- Comportements -----
        void saisir();                          // demande les infos au clavier
        void afficherLigne() const;              // affiche une ligne de tableau
        void sauvegarder(ofstream &fichier) const;
        void chargerDepuisLigne(string ligneId, ifstream &fichier);
};

#endif
