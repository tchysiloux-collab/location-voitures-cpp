#include "Voiture.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
using namespace std;

Voiture::Voiture()
{
    id = 0;
    annee = 0;
    prixJour = 0;
    statut = "Disponible";
}

// ----- Getters -----
int Voiture::getId() const { return id; }
string Voiture::getMarque() const { return marque; }
string Voiture::getModele() const { return modele; }
int Voiture::getAnnee() const { return annee; }
string Voiture::getImmatriculation() const { return immatriculation; }
string Voiture::getCouleur() const { return couleur; }
double Voiture::getPrixJour() const { return prixJour; }
string Voiture::getStatut() const { return statut; }

// ----- Setters -----
void Voiture::setId(int nouvelId) { id = nouvelId; }
void Voiture::setMarque(string nouvelleMarque) { marque = nouvelleMarque; }
void Voiture::setModele(string nouveauModele) { modele = nouveauModele; }
void Voiture::setAnnee(int nouvelleAnnee) { annee = nouvelleAnnee; }
void Voiture::setImmatriculation(string nouvelleImmat) { immatriculation = nouvelleImmat; }
void Voiture::setCouleur(string nouvelleCouleur) { couleur = nouvelleCouleur; }
void Voiture::setPrixJour(double nouveauPrix) { prixJour = nouveauPrix; }
void Voiture::setStatut(string nouveauStatut) { statut = nouveauStatut; }

// ----- Comportements -----
void Voiture::saisir()
{
    string ligne;

    cout << "Marque : ";
    getline(cin, marque);

    cout << "Modele : ";
    getline(cin, modele);

    cout << "Annee : ";
    getline(cin, ligne);
    annee = lireEntier(ligne, 0);

    cout << "Immatriculation : ";
    getline(cin, immatriculation);

    cout << "Couleur : ";
    getline(cin, couleur);

    cout << "Prix par jour (FCFA) : ";
    getline(cin, ligne);
    prixJour = lireDouble(ligne, 0.0);

    statut = "Disponible";
}

void Voiture::afficherLigne() const
{
    cout << left << setw(4) << id
         << setw(12) << marque
         << setw(12) << modele
         << setw(6) << annee
         << setw(12) << immatriculation
         << setw(10) << couleur
         << setw(12) << fixed << setprecision(0) << prixJour
         << setw(12) << statut << "\n";
}

void Voiture::sauvegarder(ofstream &fichier) const
{
    fichier << id << "\n";
    fichier << marque << "\n";
    fichier << modele << "\n";
    fichier << annee << "\n";
    fichier << immatriculation << "\n";
    fichier << couleur << "\n";
    fichier << prixJour << "\n";
    fichier << statut << "\n";
    fichier << "---\n";
}

void Voiture::chargerDepuisLigne(string ligneId, ifstream &fichier)
{
    string ligne;
    id = lireEntier(ligneId, 0);
    getline(fichier, marque);
    getline(fichier, modele);
    getline(fichier, ligne); annee = lireEntier(ligne, 0);
    getline(fichier, immatriculation);
    getline(fichier, couleur);
    getline(fichier, ligne);
    string ligneSuivante;
    getline(fichier, ligneSuivante);

    if (ligneSuivante == "Disponible" || ligneSuivante == "Louee" || ligneSuivante == "Maintenance")
    {
        prixJour = lireDouble(ligne, 0.0);
        statut = ligneSuivante;
    }
    else
    {
        prixJour = lireDouble(ligneSuivante, 0.0);
        getline(fichier, statut);
    }
}
