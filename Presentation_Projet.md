# Presentation du projet : gestion d'une agence de location de voitures

## 1. Introduction

Mon projet est une application C++ qui permet de gerer une agence de location de voitures.

Le programme permet de :

- ajouter et gerer les voitures ;
- ajouter et gerer les clients ;
- creer une nouvelle location ;
- proposer une location avec ou sans chauffeur ;
- calculer le prix de la location ;
- afficher une facture ;
- enregistrer le retour d'une voiture ;
- afficher des statistiques ;
- sauvegarder les donnees dans des fichiers texte.

Le programme fonctionne dans la console avec un menu principal.

## 2. Les classes du projet

Le projet contient les classes suivantes :

- `Voiture` : represente une voiture ;
- `Client` : represente un client ;
- `Facture` : represente une facture de location ;
- `GestionVoitures` : gere la liste des voitures ;
- `GestionClients` : gere la liste des clients ;
- `GestionFactures` : gere la liste des factures ;
- `Agence` : coordonne tout le programme.

Il n'y a plus de classe `Chauffeur`. Le chauffeur est seulement une option de location. Si le client choisit oui, le programme ajoute un prix fixe de 5 000 FCFA par jour.

## 2 bis. Fiche rapide de chaque classe

### Classe Voiture

Fichiers : `Voiture.h` et `Voiture.cpp`.

Role : representer une voiture disponible a la location.

Donnees principales : identifiant, marque, modele, annee, immatriculation, couleur, prix par jour et statut.

Fonctions principales :

- `saisir` : demande les informations de la voiture ;
- `afficherLigne` : affiche la voiture dans un tableau ;
- `sauvegarder` : enregistre la voiture dans `voitures.txt` ;
- `chargerDepuisLigne` : recupere une voiture depuis le fichier ;
- les getters : lisent les informations ;
- les setters : modifient les informations.

### Classe Client

Fichiers : `Client.h` et `Client.cpp`.

Role : representer la personne qui loue une voiture.

Donnees principales : identifiant, nom, prenom, telephone, email et permis.

Fonctions principales :

- `saisir` : demande les informations du client ;
- `afficherLigne` : affiche le client ;
- `sauvegarder` : enregistre le client dans `clients.txt` ;
- `chargerDepuisLigne` : lit le client depuis le fichier ;
- `getNomComplet` : rassemble le prenom et le nom ;
- les getters et setters : lisent ou modifient les informations.

### Classe Facture

Fichiers : `Facture.h` et `Facture.cpp`.

Role : enregistrer une location et calculer son montant.

Donnees principales : client, voiture, dates, nombre de jours, prix de la voiture, option chauffeur, frais supplementaires et montant total.

Fonctions principales :

- `definirLocation` : enregistre les informations d'une location ;
- `ajouterFraisSupplementaires` : ajoute les frais du retour ;
- `terminerLocation` : termine la location ;
- `afficherLigne` : affiche un resume ;
- `afficherDetail` : affiche toute la facture ;
- `sauvegarder` et `chargerDepuisLigne` : gerent le fichier `factures.txt`.

La classe ne gere pas le paiement. Elle calcule seulement le montant de la location.

### Classe GestionVoitures

Fichiers : `GestionVoitures.h` et `GestionVoitures.cpp`.

Role : gerer plusieurs objets `Voiture` dans une liste.

Fonctions principales : ajouter, afficher, rechercher, modifier, supprimer, charger, sauvegarder et afficher les voitures disponibles.

### Classe GestionClients

Fichiers : `GestionClients.h` et `GestionClients.cpp`.

Role : gerer plusieurs objets `Client` dans une liste.

Fonctions principales : ajouter, afficher, rechercher, modifier, supprimer, trier les clients, charger et sauvegarder.

### Classe GestionFactures

Fichiers : `GestionFactures.h` et `GestionFactures.cpp`.

Role : gerer plusieurs objets `Facture` dans une liste.

Fonctions principales : ajouter, afficher, rechercher, afficher le detail, supprimer, charger, sauvegarder et calculer le chiffre d'affaires.

### Classe Agence

Fichiers : `Agence.h` et `Agence.cpp`.

Role : coordonner les classes de gestion et afficher le menu principal.

Fonctions principales :

- `demarrer` : charge les donnees et lance le menu ;
- `nouvelleLocation` : cree une location ;
- `retourVoiture` : enregistre le retour ;
- `statistiques` : affiche les statistiques ;
- `menuPrincipal` : affiche les choix du programme.

### Fichier Utils

Fichiers : `Utils.h` et `Utils.cpp`.

Role : regrouper les petites fonctions utilisees dans plusieurs fichiers.

Fonctions : `lireEntier`, `lireDouble`, `lireChoix` et `pauseMenu`.

## 3. Le role des fichiers .h et .cpp

Chaque classe est generalement separee en deux fichiers.

### Le fichier .h

Le fichier `.h` contient la description de la classe :

- le nom de la classe ;
- les variables ;
- les fonctions disponibles.

Exemple dans `Client.h` :

```cpp
class Client
{
private:
    int id;
    string nom;

public:
    Client();
    int getId() const;
    string getNom() const;
};
```

### Le fichier .cpp

Le fichier `.cpp` contient le code des fonctions declarees dans le `.h`.

Exemple dans `Client.cpp` :

```cpp
#include "Client.h"

int Client::getId() const
{
    return id;
}

string Client::getNom() const
{
    return nom;
}
```

La ligne `#include "Client.h"` permet d'utiliser la classe `Client` dans `Client.cpp`.

`Client::getNom` signifie que la fonction `getNom` appartient a la classe `Client`.

## 4. Le fichier main.cpp

Le fichier `main.cpp` lance le programme.

```cpp
#include "Agence.h"

int main()
{
    Agence agence;
    agence.demarrer();
    return 0;
}
```

Explication :

- `#include "Agence.h"` inclut la description de la classe `Agence` ;
- `Agence agence;` cree un objet `Agence` ;
- `agence.demarrer();` demarre le programme ;
- `return 0;` indique que le programme s'est termine correctement.

## 5. La classe Voiture

La classe `Voiture` represente une voiture de l'agence.

Ses informations sont :

```cpp
private:
    int id;
    string marque;
    string modele;
    int annee;
    string immatriculation;
    string couleur;
    double prixJour;
    string statut;
```

Explication :

- `id` : identifiant de la voiture ;
- `marque` : marque de la voiture ;
- `modele` : modele de la voiture ;
- `annee` : annee de fabrication ;
- `immatriculation` : numero de la plaque ;
- `couleur` : couleur de la voiture ;
- `prixJour` : prix de location par jour ;
- `statut` : Disponible, Louee ou Maintenance.

La fonction `saisir` demande les informations a l'utilisateur :

```cpp
void Voiture::saisir()
{
    cout << "Marque : ";
    getline(cin, marque);

    cout << "Modele : ";
    getline(cin, modele);

    cout << "Prix par jour (FCFA) : ";
    getline(cin, ligne);
    prixJour = lireDouble(ligne, 0.0);
}
```

La fonction `afficherLigne` affiche une voiture dans un tableau.

La fonction `sauvegarder` ecrit la voiture dans `voitures.txt`.

La fonction `chargerDepuisLigne` lit une voiture depuis le fichier.

## 6. La classe Client

La classe `Client` represente une personne qui loue une voiture.

Ses informations sont :

```cpp
private:
    int id;
    string nom;
    string prenom;
    string telephone;
    string email;
    string permis;
```

La fonction `saisir` demande les informations du client.

La fonction `getNom` lit le nom :

```cpp
string Client::getNom() const
{
    return nom;
}
```

La fonction `setNom` modifie le nom :

```cpp
void Client::setNom(string nouveauNom)
{
    nom = nouveauNom;
}
```

## 7. Les getters et les setters

Un getter sert a lire une information privee.

```cpp
string getNom() const;
```

Un setter sert a modifier une information privee.

```cpp
void setNom(string nouveauNom);
```

Les variables sont dans `private` pour proteger les donnees.

On ne fait pas directement :

```cpp
client.nom = "Diallo";
```

On utilise plutot :

```cpp
client.setNom("Diallo");
cout << client.getNom();
```

Explication des mots importants :

- `private` : accessible seulement dans la classe ;
- `public` : accessible depuis les autres parties du programme ;
- `const` : la fonction ne modifie pas l'objet ;
- `string` : type utilise pour du texte ;
- `double` : type utilise pour un nombre decimal ;
- `void` : la fonction ne renvoie pas de valeur.

## 8. La classe Facture

La classe `Facture` represente la location et son prix.

Elle contient notamment :

- le client ;
- la voiture ;
- la date de debut ;
- la date de fin ;
- le nombre de jours ;
- le prix de la voiture ;
- le choix avec ou sans chauffeur ;
- le prix du chauffeur si le client choisit oui ;
- les frais supplementaires ;
- le montant total ;
- le statut de la location.

La classe ne gere pas les paiements.

Le client paie apres l'affichage de la facture, mais le programme ne demande pas le montant paye et ne calcule pas le reste a payer.

## 9. Le calcul de la facture

Le prix de la voiture est calcule comme ceci :

```cpp
totalVoiture = prixVoitureJour * nombreJours;
```

Si le client choisit un chauffeur :

```cpp
totalChauffeur = 0;

if (avecChauffeur)
    totalChauffeur = prixChauffeurJour * nombreJours;
```

Le prix du chauffeur est fixe a 5 000 FCFA par jour dans `Agence.cpp`.

Le montant total est calcule ainsi :

```cpp
montantTotal = totalVoiture + totalChauffeur + fraisSupp;
```

Exemple :

```text
Prix voiture : 20 000 FCFA par jour
Nombre de jours : 3
Chauffeur : oui
Prix chauffeur : 5 000 FCFA par jour
Frais supplementaires : 2 000 FCFA

Total voiture = 20 000 x 3 = 60 000 FCFA
Total chauffeur = 5 000 x 3 = 15 000 FCFA
Montant total = 60 000 + 15 000 + 2 000
Montant total = 77 000 FCFA
```

## 10. La nouvelle location

La fonction `nouvelleLocation` se deroule comme ceci :

1. afficher les clients ;
2. choisir un client ;
3. verifier que le client existe ;
4. afficher les voitures disponibles ;
5. choisir une voiture ;
6. verifier que la voiture est disponible ;
7. saisir la date de debut ;
8. saisir la date de fin ;
9. demander si le client veut un chauffeur ;
10. ajouter 5 000 FCFA par jour si la reponse est oui ;
11. calculer la facture ;
12. enregistrer la facture ;
13. changer le statut de la voiture en `Louee`.

Extrait important :

```cpp
cout << "Voulez-vous un chauffeur ? (1 = Oui, 2 = Non) : ";
getline(cin, ligne);
int choixChauffeur = lireEntier(ligne, 0);

bool avecChauffeur = false;
if (choixChauffeur == 1)
    avecChauffeur = true;
```

Puis le prix est choisi :

```cpp
double prixChauffeurJour = 0;

if (avecChauffeur)
    prixChauffeurJour = 5000;
```

## 11. Le retour d'une voiture

Lors du retour :

1. l'utilisateur saisit l'identifiant de la voiture ;
2. le programme cherche la location en cours ;
3. l'utilisateur saisit l'etat de la voiture ;
4. l'utilisateur saisit le carburant ;
5. l'utilisateur saisit les dommages eventuels ;
6. l'utilisateur saisit les frais supplementaires ;
7. la voiture redevient disponible ;
8. les frais sont ajoutes a la facture ;
9. la location devient terminee.

Extrait :

```cpp
gestionVoitures.changerStatut(idVoiture, "Disponible");
facture.ajouterFraisSupplementaires(fraisSupp);
facture.terminerLocation();
```

## 12. Les classes de gestion

### GestionVoitures

Cette classe gere la liste des voitures.

```cpp
vector<Voiture> voitures;
```

Elle permet de :

- ajouter une voiture ;
- afficher les voitures ;
- rechercher une voiture ;
- modifier une voiture ;
- supprimer une voiture ;
- afficher les voitures disponibles ;
- charger et sauvegarder les voitures.

### GestionClients

Cette classe gere la liste des clients.

```cpp
vector<Client> clients;
```

Elle permet d'ajouter, afficher, rechercher, modifier, supprimer, charger et sauvegarder les clients.

### GestionFactures

Cette classe gere la liste des factures.

```cpp
vector<Facture> factures;
```

Elle permet d'ajouter, afficher, rechercher, supprimer, charger et sauvegarder les factures.

## 13. La classe Agence

La classe `Agence` est la classe qui coordonne le programme.

Elle contient les trois classes de gestion :

```cpp
GestionVoitures gestionVoitures;
GestionClients gestionClients;
GestionFactures gestionFactures;
```

Elle contient les operations principales :

- `demarrer` ;
- `nouvelleLocation` ;
- `retourVoiture` ;
- `statistiques` ;
- `menuPrincipal`.

Au demarrage :

```cpp
void Agence::demarrer()
{
    gestionVoitures.charger();
    gestionClients.charger();
    gestionFactures.charger();

    menuPrincipal();
}
```

Le programme charge les donnees, puis affiche le menu principal.

## 14. Les principes de la programmation orientee objet

### 1. Les classes

Une classe est un modele. Elle decrit les informations et les fonctions d'un objet.

Exemple : `Voiture` est le modele d'une voiture.

### 2. Les objets

Un objet est une utilisation concrete d'une classe.

```cpp
Voiture voiture;
Client client;
Facture facture;
```

### 3. L'encapsulation

L'encapsulation consiste a proteger les variables avec `private` et a utiliser des fonctions publiques pour y acceder.

Exemple :

```cpp
private:
    string nom;

public:
    string getNom() const;
    void setNom(string nouveauNom);
```

### 4. L'abstraction

Chaque classe cache les details inutiles.

Par exemple, dans le programme principal, on appelle :

```cpp
gestionVoitures.charger();
```

On n'a pas besoin de connaitre toutes les lignes qui ouvrent et lisent le fichier.

### 5. La modularite

Le programme est separe en plusieurs classes et plusieurs fichiers.

Chaque classe a un role precis. Cela facilite la lecture et les modifications.

Il n'y a pas d'heritage dans ce projet. Il n'y a pas non plus de surcharge de fonctions.

## 15. Les fichiers de sauvegarde

Les informations sont sauvegardees dans :

- `voitures.txt` ;
- `clients.txt` ;
- `factures.txt`.

Exemple :

```cpp
void Client::sauvegarder(ofstream &fichier) const
{
    fichier << id << "\n";
    fichier << nom << "\n";
    fichier << prenom << "\n";
}
```

Les donnees sont ecrites ligne par ligne.

La fonction `chargerDepuisLigne` lit les informations au lancement du programme.

## 16. Le fichier Utils.h et Utils.cpp

`Utils.h` contient les declarations des fonctions generales.

```cpp
int lireEntier(string texte, int defaut);
double lireDouble(string texte, double defaut);
int lireChoix();
void pauseMenu();
```

`Utils.cpp` contient le code de ces fonctions.

- `lireEntier` transforme un texte en entier ;
- `lireDouble` transforme un texte en nombre decimal ;
- `lireChoix` lit le choix d'un menu ;
- `pauseMenu` attend que l'utilisateur appuie sur Entree.

## 17. Conclusion a dire au professeur

Mon projet est une application de gestion de location de voitures realisee en C++.

J'ai utilise la programmation orientee objet pour separer les responsabilites :

- `Voiture` represente une voiture ;
- `Client` represente un client ;
- `Facture` represente une location et son montant ;
- les classes `Gestion...` gerent les listes ;
- `Agence` coordonne le fonctionnement general.

Les principes principaux utilises sont les classes, les objets, l'encapsulation, l'abstraction et la modularite.

Les informations sont sauvegardees dans des fichiers texte afin de rester disponibles apres la fermeture du programme.

Le programme ne gere pas les paiements et ne gere pas une liste de chauffeurs. Le chauffeur est seulement une option avec un prix fixe ajoute a la location.

## 18. Questions possibles du professeur

### Pourquoi utiliser une classe Voiture ?

Pour regrouper toutes les informations et les fonctions qui concernent une voiture.

### Pourquoi utiliser private ?

Pour proteger les donnees et obliger le programme a passer par des fonctions comme les getters et les setters.

### Pourquoi utiliser des fichiers .h et .cpp ?

Le fichier `.h` presente la classe et le fichier `.cpp` contient son fonctionnement. Cela rend le projet mieux organise.

### Comment est calcule le prix ?

Le prix de la voiture est multiplie par le nombre de jours. Si le client choisit un chauffeur, 5 000 FCFA par jour sont ajoutes. Les frais supplementaires sont ajoutes au retour.

### Pourquoi la classe Agence est-elle utile ?

Elle coordonne les autres classes et contient le menu principal. Elle evite de mettre tout le programme dans `main.cpp`.

### Le projet utilise-t-il l'heritage ?

Non. Le projet utilise surtout les classes, les objets, l'encapsulation, l'abstraction et la modularite.

## 19. Explication du code classe par classe

Cette partie explique ce que font les instructions importantes du programme.

### Voiture

Le constructeur prepare une nouvelle voiture :

```cpp
Voiture::Voiture()
{
    id = 0;
    annee = 0;
    prixJour = 0;
    statut = "Disponible";
}
```

Le constructeur est execute quand on cree une voiture. Il donne des valeurs initiales aux attributs.

La saisie lit les informations :

```cpp
cout << "Marque : ";
getline(cin, marque);

cout << "Prix par jour (FCFA) : ";
getline(cin, ligne);
prixJour = lireDouble(ligne, 0.0);
```

`cout` affiche une question. `getline` lit la reponse. `lireDouble` transforme le texte en nombre decimal.

La sauvegarde ecrit la voiture ligne par ligne dans `voitures.txt` :

```cpp
fichier << id << "\n";
fichier << marque << "\n";
fichier << modele << "\n";
fichier << prixJour << "\n";
fichier << statut << "\n";
```

### Client

La fonction de saisie demande les informations personnelles :

```cpp
void Client::saisir()
{
    cout << "Nom : ";
    getline(cin, nom);

    cout << "Prenom : ";
    getline(cin, prenom);

    cout << "Telephone : ";
    getline(cin, telephone);
}
```

Chaque reponse est placee dans l'attribut correspondant.

La fonction suivante assemble le prenom et le nom :

```cpp
string Client::getNomComplet() const
{
    return prenom + " " + nom;
}
```

Par exemple, elle peut renvoyer `Ali Diallo`.

### Facture

La fonction `definirLocation` met les informations dans la facture :

```cpp
idClient = idC;
nomClient = nomC;
idVoiture = idV;
dateDebut = debut;
dateFin = fin;
nombreJours = jours;
prixVoitureJour = prixVJour;
```

Chaque ligne copie une valeur recue en parametre vers un attribut de la facture.

Le calcul principal est :

```cpp
totalVoiture = prixVoitureJour * nombreJours;

totalChauffeur = 0;
if (avecChauffeur)
    totalChauffeur = prixChauffeurJour * nombreJours;

montantTotal = totalVoiture + totalChauffeur + fraisSupp;
```

Le prix de la voiture est multiplie par le nombre de jours. Le prix du chauffeur est ajoute seulement si le client a choisi cette option. Ensuite, les frais supplementaires sont ajoutes.

Pour terminer la location :

```cpp
void Facture::terminerLocation()
{
    statutLocation = "Terminee";
}
```

Cette fonction change simplement le statut de la facture.

### GestionVoitures

Cette classe contient une liste de voitures :

```cpp
vector<Voiture> voitures;
```

La recherche d'une voiture se fait avec une boucle :

```cpp
for (int i = 0; i < (int)voitures.size(); i++)
{
    if (voitures[i].getId() == id)
        return i;
}
return -1;
```

La boucle regarde chaque voiture. Si l'identifiant correspond, elle renvoie sa position. `-1` signifie que la voiture n'existe pas.

Pour changer le statut :

```cpp
int index = trouverIndex(id);
if (index != -1)
{
    voitures[index].setStatut(nouveauStatut);
    sauvegarder();
}
```

Le programme trouve la voiture, change son statut et sauvegarde la liste.

### GestionClients

Cette classe contient une liste de clients :

```cpp
vector<Client> clients;
```

L'ajout suit cinq etapes :

```cpp
Client client;
client.setId(nouvelId());
client.saisir();
clients.push_back(client);
sauvegarder();
```

Le programme cree un client, lui donne un identifiant, demande ses informations, l'ajoute a la liste et sauvegarde le fichier.

### GestionFactures

Cette classe contient une liste de factures :

```cpp
vector<Facture> factures;
```

Pour ajouter une facture :

```cpp
void GestionFactures::ajouter(Facture facture)
{
    factures.push_back(facture);
    sauvegarder();
}
```

La facture est ajoutee a la liste, puis enregistree dans `factures.txt`.

Le chiffre d'affaires est obtenu en additionnant les montants :

```cpp
double total = 0;
for (int i = 0; i < (int)factures.size(); i++)
    total += factures[i].getMontantTotal();
return total;
```

### Agence

La classe `Agence` coordonne le programme :

```cpp
void Agence::demarrer()
{
    gestionVoitures.charger();
    gestionClients.charger();
    gestionFactures.charger();
    menuPrincipal();
}
```

Elle charge les donnees, puis lance le menu principal.

Le menu utilise `switch` :

```cpp
switch (choix)
{
    case 1: gestionVoitures.menu(); break;
    case 2: gestionClients.menu(); break;
    case 3: nouvelleLocation(); break;
    case 4: retourVoiture(); break;
    case 5: gestionFactures.menu(); break;
    case 6: statistiques(); break;
}
```

Chaque `case` correspond a une option du menu.

### Utils

`Utils.h` annonce les fonctions et `Utils.cpp` contient leur code.

```cpp
int lireEntier(string texte, int defaut)
{
    stringstream ss(texte);
    int valeur;
    ss >> valeur;

    if (ss.fail())
        return defaut;

    return valeur;
}
```

`stringstream` essaie de transformer le texte en entier. `ss.fail()` verifie si la conversion a echoue. En cas d'erreur, la valeur par defaut est renvoyee.
