#include "Facture.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
using namespace std;

Facture::Facture()
{
    id = 0;
    idClient = 0;
    idVoiture = 0;
    avecChauffeur = false;
    nombreJours = 0;
    prixVoitureJour = 0;
    prixChauffeurJour = 0;
    totalVoiture = 0;
    totalChauffeur = 0;
    fraisSupp = 0;
    montantTotal = 0;
    statutLocation = "En cours";
}

// ----- Getters -----
int Facture::getId() const { return id; }
int Facture::getIdClient() const { return idClient; }
string Facture::getNomClient() const { return nomClient; }
int Facture::getIdVoiture() const { return idVoiture; }
string Facture::getVoitureInfo() const { return voitureInfo; }
bool Facture::getAvecChauffeur() const { return avecChauffeur; }
string Facture::getDateDebut() const { return dateDebut; }
string Facture::getDateFin() const { return dateFin; }
int Facture::getNombreJours() const { return nombreJours; }
double Facture::getPrixVoitureJour() const { return prixVoitureJour; }
double Facture::getPrixChauffeurJour() const { return prixChauffeurJour; }
double Facture::getTotalVoiture() const { return totalVoiture; }
double Facture::getTotalChauffeur() const { return totalChauffeur; }
double Facture::getFraisSupp() const { return fraisSupp; }
double Facture::getMontantTotal() const { return montantTotal; }
string Facture::getStatutLocation() const { return statutLocation; }

void Facture::setId(int nouvelId) { id = nouvelId; }

// ----- Comportements -----
void Facture::definirLocation(int idC, string nomC, int idV, string infoV,
                               bool avecCh, string debut, string fin, int jours,
                               double prixVJour, double prixChJour)
{
    idClient = idC;
    nomClient = nomC;
    idVoiture = idV;
    voitureInfo = infoV;
    avecChauffeur = avecCh;
    dateDebut = debut;
    dateFin = fin;
    nombreJours = jours;
    prixVoitureJour = prixVJour;
    prixChauffeurJour = prixChJour;

    totalVoiture = prixVoitureJour * nombreJours;
    totalChauffeur = 0;
    if (avecChauffeur)
        totalChauffeur = prixChauffeurJour * nombreJours;
    fraisSupp = 0;
    montantTotal = totalVoiture + totalChauffeur + fraisSupp;
    statutLocation = "En cours";
}

void Facture::ajouterFraisSupplementaires(double frais)
{
    fraisSupp = frais;
    montantTotal += frais;
}

void Facture::terminerLocation()
{
    statutLocation = "Terminee";
}

void Facture::afficherLigne() const
{
    cout << left << setw(6) << id << setw(16) << nomClient << setw(18) << voitureInfo
         << setw(9) << nombreJours
         << fixed << setprecision(0)
         << setw(12) << montantTotal << setw(18) << statutLocation << "\n";
}

void Facture::afficherDetail() const
{
    cout << "\n===== DETAIL DE LA FACTURE N. " << id << " =====\n\n";
    cout << "Client              : " << nomClient << " (ID " << idClient << ")\n";
    cout << "Voiture             : " << voitureInfo << " (ID " << idVoiture << ")\n";
    cout << "Avec chauffeur      : ";
    if (avecChauffeur)
        cout << "Oui\n";
    else
        cout << "Non\n";
    if (avecChauffeur)
        cout << "Prix chauffeur/jour : " << prixChauffeurJour << " FCFA\n";
    cout << "Date de debut       : " << dateDebut << "\n";
    cout << "Date de fin         : " << dateFin << "\n";
    cout << "Nombre de jours     : " << nombreJours << "\n";

    cout << fixed << setprecision(0);
    cout << "\nPrix voiture/jour   : " << prixVoitureJour << " FCFA\n";
    cout << "Total voiture       : " << totalVoiture << " FCFA\n";
    if (avecChauffeur)
        cout << "Total chauffeur     : " << totalChauffeur << " FCFA\n";
    cout << "Frais supp.         : " << fraisSupp << " FCFA\n";
    cout << "\nMONTANT TOTAL       : " << montantTotal << " FCFA\n";
    cout << "Statut location     : " << statutLocation << "\n";
}

void Facture::sauvegarder(ofstream &fichier) const
{
    fichier << id << "\n";
    fichier << idClient << "\n";
    fichier << nomClient << "\n";
    fichier << idVoiture << "\n";
    fichier << voitureInfo << "\n";
    if (avecChauffeur)
        fichier << "Oui\n";
    else
        fichier << "Non\n";
    fichier << dateDebut << "\n";
    fichier << dateFin << "\n";
    fichier << nombreJours << "\n";
    fichier << prixVoitureJour << "\n";
    fichier << prixChauffeurJour << "\n";
    fichier << totalVoiture << "\n";
    fichier << totalChauffeur << "\n";
    fichier << fraisSupp << "\n";
    fichier << montantTotal << "\n";
    fichier << statutLocation << "\n";
    fichier << "---\n";
}

void Facture::chargerDepuisLigne(string ligneId, ifstream &fichier)
{
    string ligne;
    id = lireEntier(ligneId, 0);
    getline(fichier, ligne); idClient = lireEntier(ligne, 0);
    getline(fichier, nomClient);
    getline(fichier, ligne); idVoiture = lireEntier(ligne, 0);
    getline(fichier, voitureInfo);
    getline(fichier, ligne); avecChauffeur = (ligne == "Oui");
    getline(fichier, dateDebut);
    getline(fichier, dateFin);
    getline(fichier, ligne); nombreJours = lireEntier(ligne, 0);
    getline(fichier, ligne); prixVoitureJour = lireDouble(ligne, 0.0);
    getline(fichier, ligne); prixChauffeurJour = lireDouble(ligne, 0.0);
    getline(fichier, ligne); totalVoiture = lireDouble(ligne, 0.0);
    getline(fichier, ligne); totalChauffeur = lireDouble(ligne, 0.0);
    getline(fichier, ligne); fraisSupp = lireDouble(ligne, 0.0);
    getline(fichier, ligne); montantTotal = lireDouble(ligne, 0.0);
    getline(fichier, ligne);
    if (ligne == "En cours" || ligne == "Terminee")
        statutLocation = ligne;
    else
    {
        getline(fichier, ligne); // ancienne ligne reste a payer
        getline(fichier, ligne); // ancienne ligne statut paiement
        getline(fichier, statutLocation);
    }
}
