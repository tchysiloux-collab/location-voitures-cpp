#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <fstream>
using namespace std;

// Classe qui représente un client de l'agence
class Client
{
    private:
        int id;
        string nom;
        string prenom;
        string telephone;
        string email;
        string permis;

    public:
        Client();

        // ----- Getters -----
        int getId() const;
        string getNom() const;
        string getPrenom() const;
        string getTelephone() const;
        string getEmail() const;
        string getPermis() const;
        string getNomComplet() const;

        // ----- Setters -----
        void setId(int nouvelId);
        void setNom(string nouveauNom);
        void setPrenom(string nouveauPrenom);
        void setTelephone(string nouveauTel);
        void setEmail(string nouvelEmail);
        void setPermis(string nouveauPermis);

        // ----- Comportements -----
        void saisir();
        void afficherLigne() const;
        void sauvegarder(ofstream &fichier) const;
        void chargerDepuisLigne(string ligneId, ifstream &fichier);
};

#endif
