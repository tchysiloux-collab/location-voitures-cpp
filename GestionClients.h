#ifndef GESTIONCLIENTS_H
#define GESTIONCLIENTS_H

#include <vector>
#include <string>
#include "Client.h"
using namespace std;

// Classe qui gere la liste des clients
class GestionClients
{
    private:
        vector<Client> clients;
        string nomFichier;

    public:
        GestionClients();

        void charger();
        void sauvegarder();

        int nouvelId() const;
        int trouverIndex(int id) const;
        bool existe(int id) const;
        Client& obtenir(int id);

        int total() const;

        void afficherEntetes() const;
        void ajouter();
        void afficherTous() const;
        void afficherTousTrieParNom() const;
        void rechercher() const;
        void modifier();
        void supprimer();
        void menu();
};

#endif
