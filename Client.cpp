#include "Client.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
using namespace std;

Client::Client()
{
    id = 0;
}

// ----- Getters -----
int Client::getId() const { return id; }
string Client::getNom() const { return nom; }
string Client::getPrenom() const { return prenom; }
string Client::getTelephone() const { return telephone; }
string Client::getEmail() const { return email; }
string Client::getPermis() const { return permis; }
string Client::getNomComplet() const { return prenom + " " + nom; }

// ----- Setters -----
void Client::setId(int nouvelId) { id = nouvelId; }
void Client::setNom(string nouveauNom) { nom = nouveauNom; }
void Client::setPrenom(string nouveauPrenom) { prenom = nouveauPrenom; }
void Client::setTelephone(string nouveauTel) { telephone = nouveauTel; }
void Client::setEmail(string nouvelEmail) { email = nouvelEmail; }
void Client::setPermis(string nouveauPermis) { permis = nouveauPermis; }

// ----- Comportements -----
void Client::saisir()
{
    cout << "Nom : ";
    getline(cin, nom);

    cout << "Prenom : ";
    getline(cin, prenom);

    cout << "Telephone : ";
    getline(cin, telephone);

    cout << "Email : ";
    getline(cin, email);

    cout << "Numero de permis : ";
    getline(cin, permis);
}

void Client::afficherLigne() const
{
    cout << left << setw(4) << id << setw(12) << nom << setw(12) << prenom
         << setw(14) << telephone << setw(22) << email << setw(14) << permis << "\n";
}

void Client::sauvegarder(ofstream &fichier) const
{
    fichier << id << "\n";
    fichier << nom << "\n";
    fichier << prenom << "\n";
    fichier << telephone << "\n";
    fichier << email << "\n";
    fichier << permis << "\n";
    fichier << "---\n";
}

void Client::chargerDepuisLigne(string ligneId, ifstream &fichier)
{
    id = lireEntier(ligneId, 0);
    getline(fichier, nom);
    getline(fichier, prenom);
    getline(fichier, telephone);
    getline(fichier, email);
    getline(fichier, permis);
}
