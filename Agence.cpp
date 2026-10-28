#include "Agence.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ============================================================
// Calcul du nombre de jours (simplifie, sans <ctime>)
// On compare uniquement le numero du jour dans la date JJ/MM/AAAA.
// ============================================================

int Agence::extraireJour(string date) const
{
    string::size_type pos = date.find('/');
    if (pos == string::npos)
        return 1;
    string jourTexte = date.substr(0, pos);
    return lireEntier(jourTexte, 1);
}

int Agence::calculerNombreJours(string dateDebut, string dateFin) const
{
    int jourDebut = extraireJour(dateDebut);
    int jourFin = extraireJour(dateFin);
    int jours = jourFin - jourDebut;
    if (jours <= 0) jours = 1;
    return jours;
}

// ============================================================
// Demarrage : chargement des 4 fichiers puis lancement du menu
// ============================================================

void Agence::demarrer()
{
    gestionVoitures.charger();
    gestionClients.charger();
    gestionFactures.charger();

    menuPrincipal();
}

// ============================================================
// Nouvelle location
// ============================================================

void Agence::nouvelleLocation()
{
    string ligne;

    cout << "\n===== NOUVELLE LOCATION =====\n\n";

    if (gestionClients.total() == 0)
    {
        cout << "Aucun client enregistre. Enregistrez d'abord un client avant de louer une voiture.\n";
        return;
    }

    gestionClients.afficherTousTrieParNom();
    cout << "\nID du client : ";
    getline(cin, ligne);
    int idClient = lireEntier(ligne, -1);
    if (!gestionClients.existe(idClient))
    {
        cout << "Erreur : ce client n'existe pas.\n";
        return;
    }

    if (gestionVoitures.total() == 0)
    {
        cout << "Aucune voiture disponible. Ajoutez d'abord une voiture avant de louer.\n";
        return;
    }

    gestionVoitures.afficherDisponibles();
    cout << "\nID de la voiture : ";
    getline(cin, ligne);
    int idVoiture = lireEntier(ligne, -1);
    if (!gestionVoitures.existe(idVoiture))
    {
        cout << "Erreur : cette voiture n'existe pas.\n";
        return;
    }
    if (!gestionVoitures.estDisponible(idVoiture))
    {
        cout << "Erreur : cette voiture n'est pas disponible.\n";
        return;
    }

    cout << "\nDate de debut (JJ/MM/AAAA) : ";
    string dateDebut;
    getline(cin, dateDebut);

    cout << "Date de fin (JJ/MM/AAAA) : ";
    string dateFin;
    getline(cin, dateFin);

    int jours = calculerNombreJours(dateDebut, dateFin);

    cout << "\nVoulez-vous un chauffeur ? (1 = Oui, 2 = Non) : ";
    getline(cin, ligne);
    int choixChauffeur = lireEntier(ligne, 0);

    bool avecChauffeur = false;
    if (choixChauffeur == 1)
        avecChauffeur = true;

    Voiture &voiture = gestionVoitures.obtenir(idVoiture);
    Client &client = gestionClients.obtenir(idClient);

    double prixVoitureJour = voiture.getPrixJour();
    double prixChauffeurJour = 0;
    if (avecChauffeur)
        prixChauffeurJour = 5000;

    // Construction de la facture (la classe Facture calcule elle-meme les totaux)
    Facture facture;
    facture.setId(gestionFactures.nouvelId());
    facture.definirLocation(idClient, client.getNomComplet(), idVoiture,
                             voiture.getMarque() + " " + voiture.getModele(),
                             avecChauffeur,
                             dateDebut, dateFin, jours,
                             prixVoitureJour, prixChauffeurJour);

    // Recapitulatif
    cout << "\n===== RECAPITULATIF =====\n\n";
    cout << "Client              : " << client.getNomComplet() << "\n";
    cout << "Voiture             : " << voiture.getMarque() << " " << voiture.getModele() << "\n";
    cout << "Nombre de jours     : " << jours << "\n";
    cout << "Location chauffeur  : ";
    if (avecChauffeur)
        cout << "Oui\n";
    else
        cout << "Non\n";

    cout << fixed << setprecision(0);
    cout << "\nPrix voiture        : " << prixVoitureJour << " FCFA/jour\n";
    if (avecChauffeur)
        cout << "Prix chauffeur      : " << prixChauffeurJour << " FCFA/jour\n";

    cout << "\nTotal voiture       : " << facture.getTotalVoiture() << " FCFA\n";
    if (avecChauffeur)
        cout << "Total chauffeur     : " << facture.getTotalChauffeur() << " FCFA\n";
    cout << "\nTOTAL               : " << facture.getMontantTotal() << " FCFA\n";

    gestionFactures.ajouter(facture);

    gestionVoitures.changerStatut(idVoiture, "Louee");

    cout << "\nLocation enregistree. Facture N. " << facture.getId() << " creee.\n";
}

// ============================================================
// Retour d'une voiture
// ============================================================

void Agence::retourVoiture()
{
    string ligne;

    cout << "\n===== RETOUR D'UNE VOITURE =====\n\n";

    cout << "ID de la voiture : ";
    getline(cin, ligne);
    int idVoiture = lireEntier(ligne, -1);

    if (!gestionVoitures.existe(idVoiture))
    {
        cout << "Erreur : cette voiture n'existe pas.\n";
        return;
    }

    int idxFacture = gestionFactures.trouverIndexActivePourVoiture(idVoiture);
    if (idxFacture == -1)
    {
        cout << "Erreur : aucune location en cours pour cette voiture.\n";
        return;
    }

    cout << "Etat de la voiture : ";
    string etat;
    getline(cin, etat);

    cout << "Carburant : ";
    string carburant;
    getline(cin, carburant);

    cout << "Dommages eventuels : ";
    string dommages;
    getline(cin, dommages);

    cout << "Frais supplementaires : ";
    getline(cin, ligne);
    double fraisSupp = lireDouble(ligne, 0.0);

    // Mise a jour de la voiture
    gestionVoitures.changerStatut(idVoiture, "Disponible");

    // Mise a jour de la facture (frais supp., statut)
    Facture &facture = gestionFactures.obtenirParIndex(idxFacture);

    facture.ajouterFraisSupplementaires(fraisSupp);
    facture.terminerLocation();
    gestionFactures.sauvegarder();

    cout << "\n===== RETOUR ENREGISTRE =====\n";
    cout << "Etat              : " << etat << "\n";
    cout << "Carburant         : " << carburant << "\n";
    cout << "Dommages          : " << dommages << "\n";
    cout << fixed << setprecision(0);
    cout << "Frais supp.       : " << fraisSupp << " FCFA\n";
    cout << "Statut voiture    : Disponible\n";
    cout << "Montant total     : " << facture.getMontantTotal() << " FCFA\n";
}

// ============================================================
// Statistiques
// ============================================================

void Agence::statistiques()
{
    cout << "\n===== STATISTIQUES =====\n\n";
    cout << "Nombre total de voitures    : " << gestionVoitures.total() << "\n";
    cout << "Voitures disponibles        : " << gestionVoitures.compterDisponibles() << "\n";
    cout << "Voitures louees             : " << gestionVoitures.compterLouees() << "\n";
    cout << "Voitures en maintenance     : " << gestionVoitures.compterMaintenance() << "\n\n";

    cout << "Nombre total de clients     : " << gestionClients.total() << "\n";
    cout << "\n";

    cout << fixed << setprecision(0);
    cout << "Chiffre d'affaires total    : " << gestionFactures.chiffreAffairesTotal() << " FCFA\n";
}

// ============================================================
// Menu principal
// ============================================================

void Agence::menuPrincipal()
{
    string ligne;
    int choix;
    do
    {
        cout << "\n========================================\n";
        cout << "     GESTION LOCATION DE VOITURES\n";
        cout << "========================================\n\n";
        cout << "1. Gestion des voitures\n";
        cout << "2. Gestion des clients\n";
        cout << "3. Nouvelle location\n";
        cout << "4. Retour d'une voiture\n";
        cout << "5. Factures\n";
        cout << "6. Statistiques\n";
        cout << "0. Quitter\n";
        cout << "\nVotre choix : ";
        choix = lireChoix();

        switch (choix)
        {
            case 1: gestionVoitures.menu(); break;
            case 2: gestionClients.menu(); break;
            case 3:
                nouvelleLocation();
                pauseMenu();
                break;
            case 4:
                retourVoiture();
                pauseMenu();
                break;
            case 5: gestionFactures.menu(); break;
            case 6:
                statistiques();
                pauseMenu();
                break;
            case 0:
                cout << "\nAu revoir !\n";
                break;
            default:
                cout << "Choix invalide.\n";
                pauseMenu();
        }

    } while (choix != 0);
}
