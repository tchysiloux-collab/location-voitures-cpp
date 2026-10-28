#include "Chauffeur.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
using namespace std;

Chauffeur::Chauffeur()
{
    id = 0;
    prixJour = 0;
    disponibilite = "Disponible";
}

// ----- Getters -----
int Chauffeur::getId() const { return id; }
string Chauffeur::getNom() const { return nom; }
string Chauffeur::getPrenom() const { return prenom; }
string Chauffeur::getTelephone() const { return telephone; }
string Chauffeur::getPermis() const { return permis; }
double Chauffeur::getPrixJour() const { return prixJour; }
string Chauffeur::getDisponibilite() const { return disponibilite; }
string Chauffeur::getNomComplet() const { return prenom + " " + nom; }

// ----- Setters -----
void Chauffeur::setId(int nouvelId) { id = nouvelId; }
void Chauffeur::setNom(string nouveauNom) { nom = nouveauNom; }
void Chauffeur::setPrenom(string nouveauPrenom) { prenom = nouveauPrenom; }
void Chauffeur::setTelephone(string nouveauTel) { telephone = nouveauTel; }
void Chauffeur::setPermis(string nouveauPermis) { permis = nouveauPermis; }
void Chauffeur::setPrixJour(double nouveauPrix) { prixJour = nouveauPrix; }
void Chauffeur::setDisponibilite(string nouvelleDispo) { disponibilite = nouvelleDispo; }

// ----- Comportements -----
void Chauffeur::saisir()
{
    string ligne;

    cout << "Nom : ";
    getline(cin, nom);

    cout << "Prenom : ";
    getline(cin, prenom);

    cout << "Telephone : ";
    getline(cin, telephone);

    cout << "Numero de permis : ";
    getline(cin, permis);

    cout << "Prix par jour (FCFA) : ";
    getline(cin, ligne);
    prixJour = lireDouble(ligne, 0.0);

    disponibilite = "Disponible";
}

void Chauffeur::afficherLigne() const
{
    cout << left << setw(4) << id << setw(12) << nom << setw(12) << prenom
         << setw(14) << telephone << setw(14) << permis
         << setw(12) << fixed << setprecision(0) << prixJour
         << setw(12) << disponibilite << "\n";
}

void Chauffeur::sauvegarder(ofstream &fichier) const
{
    fichier << id << "\n";
    fichier << nom << "\n";
    fichier << prenom << "\n";
    fichier << telephone << "\n";
    fichier << permis << "\n";
    fichier << prixJour << "\n";
    fichier << disponibilite << "\n";
    fichier << "---\n";
}

void Chauffeur::chargerDepuisLigne(string ligneId, ifstream &fichier)
{
    string ligne;
    id = lireEntier(ligneId, 0);
    getline(fichier, nom);
    getline(fichier, prenom);
    getline(fichier, telephone);
    getline(fichier, permis);
    getline(fichier, ligne); prixJour = lireDouble(ligne, 0.0);
    getline(fichier, disponibilite);
}
