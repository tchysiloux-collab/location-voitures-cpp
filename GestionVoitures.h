#ifndef GESTIONVOITURES_H
#define GESTIONVOITURES_H

#include <vector>
#include <string>
#include "Voiture.h"
using namespace std;

// Classe qui gere la liste des voitures (ajout, recherche, fichier, menu...)
class GestionVoitures
{
    private:
        vector<Voiture> voitures;
        string nomFichier;

    public:
        GestionVoitures();

        void charger();
        void sauvegarder();

        int nouvelId() const;
        int trouverIndex(int id) const;
        bool existe(int id) const;
        bool estDisponible(int id) const;

        Voiture& obtenir(int id);                    // reference vers la voiture (doit exister)
        void changerStatut(int id, string nouveauStatut);

        int compterDisponibles() const;
        int compterLouees() const;
        int compterMaintenance() const;
        int total() const;

        // Operations et menu
        void afficherEntetes() const;
        void ajouter();
        void afficherToutes() const;
        void rechercher() const;
        void modifier();
        void supprimer();
        void afficherDisponibles() const;
        void afficherMaintenance() const;
        void menu();
};

#endif
