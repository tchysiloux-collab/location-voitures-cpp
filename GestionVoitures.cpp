#include "GestionVoitures.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
using namespace std;

GestionVoitures::GestionVoitures()
{
    nomFichier = "voitures.txt";
}

void GestionVoitures::sauvegarder()
{
    ofstream fichier(nomFichier.c_str());
    for (int i = 0; i < (int)voitures.size(); i++)
        voitures[i].sauvegarder(fichier);
    fichier.close();
}

void GestionVoitures::charger()
{
    voitures.clear();
    ifstream fichier(nomFichier.c_str());
    if (!fichier) return;

    string ligne;
    while (getline(fichier, ligne))
    {
        if (ligne.empty()) continue;
        Voiture v;
        v.chargerDepuisLigne(ligne, fichier);
        getline(fichier, ligne); // ligne "---"
        voitures.push_back(v);
    }
    fichier.close();
}

int GestionVoitures::nouvelId() const
{
    int maxId = 0;
    for (int i = 0; i < (int)voitures.size(); i++)
        if (voitures[i].getId() > maxId) maxId = voitures[i].getId();
    return maxId + 1;
}

int GestionVoitures::trouverIndex(int id) const
{
    for (int i = 0; i < (int)voitures.size(); i++)
        if (voitures[i].getId() == id) return i;
    return -1;
}

bool GestionVoitures::existe(int id) const
{
    return trouverIndex(id) != -1;
}

bool GestionVoitures::estDisponible(int id) const
{
    int idx = trouverIndex(id);
    if (idx == -1) return false;
    return voitures[idx].getStatut() == "Disponible";
}

Voiture& GestionVoitures::obtenir(int id)
{
    int idx = trouverIndex(id);
    if (idx == -1)
    {
        static Voiture vide; // securite si l'id est introuvable
        return vide;
    }
    return voitures[idx];
}

void GestionVoitures::changerStatut(int id, string nouveauStatut)
{
    int idx = trouverIndex(id);
    if (idx != -1)
    {
        voitures[idx].setStatut(nouveauStatut);
        sauvegarder();
    }
}

int GestionVoitures::compterDisponibles() const
{
    int n = 0;
    for (int i = 0; i < (int)voitures.size(); i++)
        if (voitures[i].getStatut() == "Disponible") n++;
    return n;
}

int GestionVoitures::compterLouees() const
{
    int n = 0;
    for (int i = 0; i < (int)voitures.size(); i++)
        if (voitures[i].getStatut() == "Louee") n++;
    return n;
}

int GestionVoitures::compterMaintenance() const
{
    int n = 0;
    for (int i = 0; i < (int)voitures.size(); i++)
        if (voitures[i].getStatut() == "Maintenance") n++;
    return n;
}

int GestionVoitures::total() const
{
    return voitures.size();
}

// ----- Operations et menu -----

void GestionVoitures::afficherEntetes() const
{
        cout << left << setw(4) << "ID" << setw(12) << "Marque" << setw(12) << "Modele"
            << setw(6) << "Annee" << setw(12) << "Immat." << setw(10) << "Couleur"
            << setw(12) << "Prix/j" << setw(12) << "Statut" << "\n";
}

void GestionVoitures::ajouter()
{
    Voiture v;
    v.setId(nouvelId());
    cout << "\n===== AJOUTER UNE VOITURE =====\n";
    cout << "ID attribue : " << v.getId() << "\n";
    v.saisir();

    voitures.push_back(v);
    sauvegarder();
    cout << "\nVoiture ajoutee avec succes.\n";
}

void GestionVoitures::afficherToutes() const
{
    cout << "\n===== LISTE DES VOITURES =====\n\n";
    if (voitures.empty())
    {
        cout << "Aucune voiture enregistree.\n";
        return;
    }
    afficherEntetes();
    cout << "--------------------------------------------------------------------------------\n";
    for (int i = 0; i < (int)voitures.size(); i++)
        voitures[i].afficherLigne();
}

void GestionVoitures::rechercher() const
{
    string ligne;
    cout << "\nID de la voiture a rechercher : ";
    getline(cin, ligne);
    int id = lireEntier(ligne, -1);

    int idx = trouverIndex(id);
    if (idx == -1)
    {
        cout << "Aucune voiture trouvee avec cet ID.\n";
        return;
    }
    cout << "\n===== VOITURE TROUVEE =====\n";
    afficherEntetes();
    voitures[idx].afficherLigne();
}

void GestionVoitures::modifier()
{
    string ligne;
    cout << "\nID de la voiture a modifier : ";
    getline(cin, ligne);
    int id = lireEntier(ligne, -1);

    int idx = trouverIndex(id);
    if (idx == -1)
    {
        cout << "Aucune voiture trouvee avec cet ID.\n";
        return;
    }

    cout << "\n===== MODIFIER LA VOITURE (ID " << id << ") =====\n";
    string statutActuel = voitures[idx].getStatut();
    voitures[idx].saisir();          // redemande toutes les infos
    voitures[idx].setId(id);
    voitures[idx].setStatut(statutActuel); // on conserve le statut courant

    sauvegarder();
    cout << "\nVoiture modifiee avec succes.\n";
}

void GestionVoitures::supprimer()
{
    string ligne;
    cout << "\nID de la voiture a supprimer : ";
    getline(cin, ligne);
    int id = lireEntier(ligne, -1);

    int idx = trouverIndex(id);
    if (idx == -1)
    {
        cout << "Aucune voiture trouvee avec cet ID.\n";
        return;
    }
    voitures.erase(voitures.begin() + idx);
    sauvegarder();
    cout << "\nVoiture supprimee avec succes.\n";
}

void GestionVoitures::afficherDisponibles() const
{
    cout << "\n===== VOITURES DISPONIBLES =====\n\n";
    bool trouve = false;
    afficherEntetes();
    for (int i = 0; i < (int)voitures.size(); i++)
    {
        if (voitures[i].getStatut() == "Disponible")
        {
            voitures[i].afficherLigne();
            trouve = true;
        }
    }
    if (!trouve) cout << "Aucune voiture disponible pour le moment.\n";
}

void GestionVoitures::afficherMaintenance() const
{
    cout << "\n===== VOITURES EN MAINTENANCE =====\n\n";
    bool trouve = false;
    afficherEntetes();
    for (int i = 0; i < (int)voitures.size(); i++)
    {
        if (voitures[i].getStatut() == "Maintenance")
        {
            voitures[i].afficherLigne();
            trouve = true;
        }
    }
    if (!trouve) cout << "Aucune voiture en maintenance.\n";
}

void GestionVoitures::menu()
{
    string ligne;
    int choix;
    do
    {
        cout << "\n===== GESTION DES VOITURES =====\n\n";
        cout << "1. Ajouter une voiture\n";
        cout << "2. Afficher toutes les voitures\n";
        cout << "3. Rechercher une voiture\n";
        cout << "4. Modifier une voiture\n";
        cout << "5. Supprimer une voiture\n";
        cout << "6. Afficher les voitures disponibles\n";
        cout << "7. Afficher les voitures en maintenance\n";
        cout << "0. Retour\n";
        cout << "\nVotre choix : ";
        choix = lireChoix();

        switch (choix)
        {
            case 1: ajouter(); break;
            case 2: afficherToutes(); break;
            case 3: rechercher(); break;
            case 4: modifier(); break;
            case 5: supprimer(); break;
            case 6: afficherDisponibles(); break;
            case 7: afficherMaintenance(); break;
            case 0: break;
            default: cout << "Choix invalide.\n";
        }

        if (choix != 0)
            pauseMenu();

    } while (choix != 0);
}
