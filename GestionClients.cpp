#include "GestionClients.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
using namespace std;

GestionClients::GestionClients()
{
    nomFichier = "clients.txt";
}

void GestionClients::sauvegarder()
{
    ofstream fichier(nomFichier.c_str());
    for (int i = 0; i < (int)clients.size(); i++)
        clients[i].sauvegarder(fichier);
    fichier.close();
}

void GestionClients::charger()
{
    clients.clear();
    ifstream fichier(nomFichier.c_str());
    if (!fichier) return;

    string ligne;
    while (getline(fichier, ligne))
    {
        if (ligne.empty()) continue;
        Client c;
        c.chargerDepuisLigne(ligne, fichier);
        clients.push_back(c);
    }
    fichier.close();
}

int GestionClients::nouvelId() const
{
    int maxId = 0;
    for (int i = 0; i < (int)clients.size(); i++)
        if (clients[i].getId() > maxId) maxId = clients[i].getId();
    return maxId + 1;
}

int GestionClients::trouverIndex(int id) const
{
    for (int i = 0; i < (int)clients.size(); i++)
        if (clients[i].getId() == id) return i;
    return -1;
}

bool GestionClients::existe(int id) const
{
    return trouverIndex(id) != -1;
}

Client& GestionClients::obtenir(int id)
{
    int idx = trouverIndex(id);
    if (idx == -1)
    {
        static Client vide;
        return vide;
    }
    return clients[idx];
}

int GestionClients::total() const
{
    return clients.size();
}

void GestionClients::afficherEntetes() const
{
    cout << left << setw(4) << "ID" << setw(12) << "Nom" << setw(12) << "Prenom"
         << setw(14) << "Telephone" << setw(22) << "Email" << setw(14) << "Permis" << "\n";
}

void GestionClients::ajouter()
{
    Client c;
    c.setId(nouvelId());
    cout << "\n===== AJOUTER UN CLIENT =====\n";
    cout << "ID attribue : " << c.getId() << "\n";
    c.saisir();

    clients.push_back(c);
    sauvegarder();
    cout << "\nClient ajoute avec succes.\n";
}

void GestionClients::afficherTous() const
{
    cout << "\n===== LISTE DES CLIENTS =====\n\n";
    if (clients.empty())
    {
        cout << "Aucun client enregistre.\n";
        return;
    }
    afficherEntetes();
    cout << "--------------------------------------------------------------------------------\n";
    for (int i = 0; i < (int)clients.size(); i++)
        clients[i].afficherLigne();
}

void GestionClients::afficherTousTrieParNom() const
{
    cout << "\n===== CLIENTS ENREGISTRES (tri par nom) =====\n\n";
    if (clients.empty())
    {
        cout << "Aucun client enregistre.\n";
        return;
    }

    vector<Client> clientsTries = clients;
    for (int i = 0; i < (int)clientsTries.size() - 1; i++)
    {
        for (int j = i + 1; j < (int)clientsTries.size(); j++)
        {
            bool nomsDansLeMauvaisOrdre = clientsTries[i].getNom() > clientsTries[j].getNom();
            bool memesNoms = clientsTries[i].getNom() == clientsTries[j].getNom();
            bool prenomsDansLeMauvaisOrdre = clientsTries[i].getPrenom() > clientsTries[j].getPrenom();

            if (nomsDansLeMauvaisOrdre || (memesNoms && prenomsDansLeMauvaisOrdre))
            {
                Client temporaire = clientsTries[i];
                clientsTries[i] = clientsTries[j];
                clientsTries[j] = temporaire;
            }
        }
    }

    afficherEntetes();
    cout << "--------------------------------------------------------------------------------\n";
    for (int i = 0; i < (int)clientsTries.size(); i++)
    {
        cout << left << setw(4) << clientsTries[i].getId()
             << setw(12) << clientsTries[i].getNom()
             << setw(12) << clientsTries[i].getPrenom()
             << setw(14) << clientsTries[i].getTelephone()
             << setw(22) << clientsTries[i].getEmail()
             << setw(14) << clientsTries[i].getPermis() << "\n";
    }
}

void GestionClients::rechercher() const
{
    string ligne;
    cout << "\nID du client a rechercher : ";
    getline(cin, ligne);
    int id = lireEntier(ligne, -1);

    int idx = trouverIndex(id);
    if (idx == -1)
    {
        cout << "Aucun client trouve avec cet ID.\n";
        return;
    }
    cout << "\n===== CLIENT TROUVE =====\n";
    afficherEntetes();
    clients[idx].afficherLigne();
}

void GestionClients::modifier()
{
    string ligne;
    cout << "\nID du client a modifier : ";
    getline(cin, ligne);
    int id = lireEntier(ligne, -1);

    int idx = trouverIndex(id);
    if (idx == -1)
    {
        cout << "Aucun client trouve avec cet ID.\n";
        return;
    }

    cout << "\n===== MODIFIER LE CLIENT (ID " << id << ") =====\n";
    clients[idx].saisir();
    clients[idx].setId(id);

    sauvegarder();
    cout << "\nClient modifie avec succes.\n";
}

void GestionClients::supprimer()
{
    string ligne;
    cout << "\nID du client a supprimer : ";
    getline(cin, ligne);
    int id = lireEntier(ligne, -1);

    int idx = trouverIndex(id);
    if (idx == -1)
    {
        cout << "Aucun client trouve avec cet ID.\n";
        return;
    }
    clients.erase(clients.begin() + idx);
    sauvegarder();
    cout << "\nClient supprime avec succes.\n";
}

void GestionClients::menu()
{
    string ligne;
    int choix;
    do
    {
        cout << "\n===== GESTION DES CLIENTS =====\n\n";
        cout << "1. Ajouter un client\n";
        cout << "2. Afficher tous les clients\n";
        cout << "3. Rechercher un client\n";
        cout << "4. Modifier un client\n";
        cout << "5. Supprimer un client\n";
        cout << "0. Retour\n";
        cout << "\nVotre choix : ";
        choix = lireChoix();

        switch (choix)
        {
            case 1: ajouter(); break;
            case 2: afficherTous(); break;
            case 3: rechercher(); break;
            case 4: modifier(); break;
            case 5: supprimer(); break;
            case 0: break;
            default: cout << "Choix invalide.\n";
        }

        if (choix != 0)
            pauseMenu();

    } while (choix != 0);
}
