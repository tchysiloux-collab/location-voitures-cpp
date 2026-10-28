#ifndef GESTIONFACTURES_H
#define GESTIONFACTURES_H

#include <vector>
#include <string>
#include "Facture.h"
using namespace std;

// Classe qui gere la liste des factures
class GestionFactures
{
    private:
        vector<Facture> factures;
        string nomFichier;

    public:
        GestionFactures();

        void charger();
        void sauvegarder();

        int nouvelId() const;
        int trouverIndex(int id) const;
        int trouverIndexActivePourVoiture(int idVoiture) const;

        void ajouter(Facture f);
        Facture& obtenirParIndex(int index);   // acces direct (utilise pour le retour de voiture)

        double chiffreAffairesTotal() const;
        int total() const;

        void afficherEntetes() const;
        void afficherToutes() const;
        void rechercher() const;
        void afficherDetail() const;
        void supprimer();
        void menu();
};

#endif
