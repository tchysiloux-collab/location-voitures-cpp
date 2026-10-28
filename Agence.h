#ifndef AGENCE_H
#define AGENCE_H

#include <string>
#include "GestionVoitures.h"
#include "GestionClients.h"
#include "GestionFactures.h"
using namespace std;

// Classe principale : elle "possede" les 4 gestions et orchestre
// les operations qui touchent plusieurs classes a la fois
// (nouvelle location, retour de voiture, statistiques...)
class Agence
{
    private:
        GestionVoitures gestionVoitures;
        GestionClients gestionClients;
        GestionFactures gestionFactures;

        // Calcul simplifie du nombre de jours (sans <ctime>)
        int extraireJour(string date) const;
        int calculerNombreJours(string dateDebut, string dateFin) const;

    public:
        void demarrer();          // charge les 4 fichiers puis lance le menu
        void nouvelleLocation();
        void retourVoiture();
        void statistiques();
        void menuPrincipal();
};

#endif
