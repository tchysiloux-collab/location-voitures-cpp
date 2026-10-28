#include "GestionFactures.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
using namespace std;

GestionFactures::GestionFactures()
{
    nomFichier = "factures.txt";
}

void GestionFactures::sauvegarder()
{
    ofstream fichier(nomFichier.c_str());
    for (int i = 0; i < (int)factures.size(); i++)
        factures[i].sauvegarder(fichier);
    fichier.close();
}

void GestionFactures::charger()
{
    factures.clear();
    ifstream fichier(nomFichier.c_str());
    if (!fichier) return;

    string ligne;
    while (getline(fichier, ligne))
    {
        if (ligne.empty()) continue;
        Facture f;
        f.chargerDepuisLigne(ligne, fichier);
        getline(fichier, ligne); // ligne "---"
        factures.push_back(f);
    }
    fichier.close();
}

int GestionFactures::nouvelId() const
{
    int maxId = 0;
    for (int i = 0; i < (int)factures.size(); i++)
        if (factures[i].getId() > maxId) maxId = factures[i].getId();
    return maxId + 1;
}

int GestionFactures::trouverIndex(int id) const
{
    for (int i = 0; i < (int)factures.size(); i++)
        if (factures[i].getId() == id) return i;
    return -1;
}

int GestionFactures::trouverIndexActivePourVoiture(int idVoiture) const
{
    for (int i = 0; i < (int)factures.size(); i++)
        if (factures[i].getIdVoiture() == idVoiture && factures[i].getStatutLocation() == "En cours")
            return i;
    return -1;
}

void GestionFactures::ajouter(Facture f)
{
    factures.push_back(f);
    sauvegarder();
}

Facture& GestionFactures::obtenirParIndex(int index)
{
    return factures[index];
}

double GestionFactures::chiffreAffairesTotal() const
{
    double total = 0;
    for (int i = 0; i < (int)factures.size(); i++)
        total += factures[i].getMontantTotal();
    return total;
}

int GestionFactures::total() const
{
    return factures.size();
}

void GestionFactures::afficherEntetes() const
{
    cout << left << setw(6) << "ID" << setw(16) << "CLIENT" << setw(18) << "VOITURE"
            << setw(9) << "JOURS" << setw(12) << "TOTAL" << setw(18) << "STATUT" << "\n";
}

void GestionFactures::afficherToutes() const
{
    cout << "\n===== LISTE DES FACTURES =====\n\n";
    if (factures.empty())
    {
        cout << "Aucune facture enregistree.\n";
        return;
    }
    afficherEntetes();
    cout << "--------------------------------------------------------------------------------\n";
    for (int i = 0; i < (int)factures.size(); i++)
        factures[i].afficherLigne();
}

void GestionFactures::rechercher() const
{
    string ligne;
    cout << "\nID de la facture a rechercher : ";
    getline(cin, ligne);
    int id = lireEntier(ligne, -1);

    int idx = trouverIndex(id);
    if (idx == -1)
    {
        cout << "Aucune facture trouvee avec cet ID.\n";
        return;
    }
    cout << "\nFacture N. " << factures[idx].getId() << " - " << factures[idx].getNomClient()
            << " - " << factures[idx].getVoitureInfo() << " - Statut : " << factures[idx].getStatutLocation() << "\n";
}

void GestionFactures::afficherDetail() const
{
    string ligne;
    cout << "\nID de la facture : ";
    getline(cin, ligne);
    int id = lireEntier(ligne, -1);

    int idx = trouverIndex(id);
    if (idx == -1)
    {
        cout << "Aucune facture trouvee avec cet ID.\n";
        return;
    }
    factures[idx].afficherDetail();
}

void GestionFactures::supprimer()
{
    string ligne;
    cout << "\nID de la facture a supprimer : ";
    getline(cin, ligne);
    int id = lireEntier(ligne, -1);

    int idx = trouverIndex(id);
    if (idx == -1)
    {
        cout << "Aucune facture trouvee avec cet ID.\n";
        return;
    }
    factures.erase(factures.begin() + idx);
    sauvegarder();
    cout << "\nFacture supprimee avec succes.\n";
}

void GestionFactures::menu()
{
    string ligne;
    int choix;
    do
    {
        cout << "\n===== FACTURES =====\n\n";
        cout << "1. Afficher toutes les factures\n";
        cout << "2. Rechercher une facture\n";
        cout << "3. Afficher le detail d'une facture\n";
        cout << "4. Supprimer une facture\n";
        cout << "0. Retour\n";
        cout << "\nVotre choix : ";
        choix = lireChoix();

        switch (choix)
        {
            case 1: afficherToutes(); break;
            case 2: rechercher(); break;
            case 3: afficherDetail(); break;
            case 4: supprimer(); break;
            case 0: break;
            default: cout << "Choix invalide.\n";
        }

        if (choix != 0)
            pauseMenu();

    } while (choix != 0);
}
