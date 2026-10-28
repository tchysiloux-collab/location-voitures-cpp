# Guide complet pour expliquer le code

Ce document sert de fiche de secours pour presenter le projet devant un professeur.

Quand on me demande : **« A quoi sert ce code ? »**, je peux utiliser les reponses ci-dessous.

---

## 1. Vue generale du projet

Le projet est un programme C++ qui gere une agence de location de voitures.

Les classes sont organisees en trois groupes :

```text
Objets principaux : Voiture, Client, Facture
Classes de gestion : GestionVoitures, GestionClients, GestionFactures
Coordination : Agence
Fonctions communes : Utils
Lancement : main
```

Chaque classe a une responsabilite precise. Cela evite de mettre tout le code dans un seul fichier.

Le programme utilise des fichiers texte :

```text
voitures.txt   : voitures enregistrees
clients.txt    : clients enregistres
factures.txt   : locations et factures
```

Le chauffeur n'est pas une classe. C'est seulement une option de location avec un prix de 5 000 FCFA par jour.

---

## 2. Comment lire un fichier C++

### Les fichiers `.h`

Un fichier `.h` presente une classe :

- son nom ;
- ses attributs ;
- ses fonctions.

Il ne contient generalement pas le fonctionnement detaille.

### Les fichiers `.cpp`

Un fichier `.cpp` contient le fonctionnement des fonctions declarees dans le `.h`.

Exemple :

```cpp
// Client.h
class Client
{
public:
    string getNom() const;
};
```

```cpp
// Client.cpp
string Client::getNom() const
{
    return nom;
}
```

Reponse a donner :

> Le fichier `.h` decrit la classe et le fichier `.cpp` contient le code de ses fonctions.

### Les inclusions

```cpp
#include "Client.h"
#include <iostream>
using namespace std;
```

- `#include "Client.h"` permet d'utiliser la classe Client ;
- `<iostream>` donne acces a `cin` et `cout` ;
- `using namespace std` permet d'ecrire `string` au lieu de `std::string`.

### La protection contre les inclusions multiples

```cpp
#ifndef CLIENT_H
#define CLIENT_H

class Client
{
};

#endif
```

Cette protection evite que le meme fichier `.h` soit inclus plusieurs fois par erreur.

---

## 3. main.cpp

Code :

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

- `#include "Agence.h"` inclut la classe principale ;
- `int main()` est le point de depart du programme ;
- `Agence agence;` cree un objet de la classe Agence ;
- `agence.demarrer();` lance le programme ;
- `return 0;` indique que le programme s'est termine correctement.

Reponse courte :

> `main.cpp` ne contient pas toute la logique. Il cree l'objet Agence et lui demande de demarrer.

---

## 4. Classe Voiture

### Fichiers

- `Voiture.h` : description de la classe ;
- `Voiture.cpp` : code des fonctions.

### Role

La classe `Voiture` represente une voiture que l'agence peut louer.

### Attributs

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

- `id` : numero unique de la voiture ;
- `marque` : marque, par exemple Toyota ;
- `modele` : modele de la voiture ;
- `annee` : annee de fabrication ;
- `immatriculation` : plaque ;
- `couleur` : couleur ;
- `prixJour` : prix de location par jour ;
- `statut` : `Disponible`, `Louee` ou `Maintenance`.

`private` protege ces informations. Elles sont utilisees avec des getters et des setters.

### Constructeur

```cpp
Voiture::Voiture()
{
    id = 0;
    annee = 0;
    prixJour = 0;
    statut = "Disponible";
}
```

Le constructeur est appele automatiquement quand une voiture est creee. Il donne des valeurs de depart.

### Getters et setters

```cpp
int Voiture::getId() const
{
    return id;
}

void Voiture::setId(int nouvelId)
{
    id = nouvelId;
}
```

`getId` lit l'identifiant. `setId` modifie l'identifiant.

`const` signifie que `getId` ne modifie pas la voiture.

### Saisie

```cpp
cout << "Marque : ";
getline(cin, marque);
```

`cout` affiche une question et `getline` lit la reponse.

Pour un nombre :

```cpp
cout << "Prix par jour : ";
getline(cin, ligne);
prixJour = lireDouble(ligne, 0.0);
```

La saisie est d'abord du texte. `lireDouble` transforme ce texte en nombre decimal.

### Affichage

```cpp
cout << left << setw(4) << id
     << setw(12) << marque
     << setw(12) << modele;
```

- `cout` affiche ;
- `left` aligne a gauche ;
- `setw` reserve une largeur pour chaque colonne.

### Sauvegarde

```cpp
fichier << id << "\n";
fichier << marque << "\n";
fichier << modele << "\n";
fichier << prixJour << "\n";
fichier << statut << "\n";
```

Chaque information est ecrite sur une ligne dans `voitures.txt`.

### Chargement

```cpp
getline(fichier, marque);
getline(fichier, modele);
getline(fichier, ligne);
prixJour = lireDouble(ligne, 0.0);
```

Le programme lit les lignes du fichier et remet les valeurs dans l'objet voiture.

---

## 5. Classe Client

### Role

La classe `Client` represente la personne qui loue une voiture.

### Attributs

```cpp
private:
    int id;
    string nom;
    string prenom;
    string telephone;
    string email;
    string permis;
```

Ce sont les informations personnelles du client.

### Saisie

```cpp
void Client::saisir()
{
    cout << "Nom : ";
    getline(cin, nom);

    cout << "Prenom : ";
    getline(cin, prenom);
}
```

La fonction demande les valeurs et les place dans les attributs.

### Nom complet

```cpp
string Client::getNomComplet() const
{
    return prenom + " " + nom;
}
```

Cette fonction rassemble le prenom, un espace et le nom.

Si le prenom est `Awa` et le nom est `Diallo`, le resultat est `Awa Diallo`.

### Sauvegarde

```cpp
fichier << id << "\n";
fichier << nom << "\n";
fichier << prenom << "\n";
fichier << telephone << "\n";
fichier << email << "\n";
fichier << permis << "\n";
```

Les informations sont enregistrees dans `clients.txt`.

---

## 6. Classe Facture

### Role

La classe `Facture` represente une location et calcule son montant.

Elle ne gere pas le paiement. Elle affiche le montant a payer, mais ne demande pas combien le client a paye.

### Attributs principaux

```cpp
int idClient;
string nomClient;
int idVoiture;
string voitureInfo;
bool avecChauffeur;
string dateDebut;
string dateFin;
int nombreJours;
double prixVoitureJour;
double prixChauffeurJour;
double totalVoiture;
double totalChauffeur;
double fraisSupp;
double montantTotal;
string statutLocation;
```

### Enregistrement de la location

```cpp
idClient = idC;
nomClient = nomC;
idVoiture = idV;
dateDebut = debut;
dateFin = fin;
nombreJours = jours;
prixVoitureJour = prixVJour;
```

Chaque ligne place un parametre dans l'attribut correspondant.

### Calcul de la voiture

```cpp
totalVoiture = prixVoitureJour * nombreJours;
```

Le prix journalier est multiplie par le nombre de jours.

### Calcul du chauffeur

```cpp
totalChauffeur = 0;

if (avecChauffeur)
    totalChauffeur = prixChauffeurJour * nombreJours;
```

Si le client choisit sans chauffeur, le total est zero. Sinon, le prix de 5 000 FCFA par jour est ajoute.

### Montant total

```cpp
montantTotal = totalVoiture + totalChauffeur + fraisSupp;
```

Le montant comprend la voiture, le chauffeur eventuel et les frais supplementaires.

Exemple :

```text
20 000 x 3 jours = 60 000 FCFA pour la voiture
5 000 x 3 jours = 15 000 FCFA pour le chauffeur
2 000 FCFA de frais
Total = 77 000 FCFA
```

### Fin de location

```cpp
void Facture::terminerLocation()
{
    statutLocation = "Terminee";
}
```

Cette fonction change le statut de `En cours` a `Terminee`.

### Frais supplementaires

```cpp
void Facture::ajouterFraisSupplementaires(double frais)
{
    fraisSupp = frais;
    montantTotal += frais;
}
```

Au retour de la voiture, les frais sont ajoutes au montant total.

---

## 7. Classe GestionVoitures

### Role

`GestionVoitures` gere plusieurs objets `Voiture`.

```cpp
vector<Voiture> voitures;
```

`vector` est une liste qui peut contenir plusieurs voitures.

### Ajouter

```cpp
Voiture voiture;
voiture.setId(nouvelId());
voiture.saisir();
voitures.push_back(voiture);
sauvegarder();
```

Le programme cree une voiture, lui donne un identifiant, demande ses informations, l'ajoute a la liste et sauvegarde.

### Rechercher

```cpp
for (int i = 0; i < (int)voitures.size(); i++)
{
    if (voitures[i].getId() == id)
        return i;
}
return -1;
```

La boucle regarde les voitures une par une. Si elle trouve le bon identifiant, elle renvoie sa position. `-1` signifie « pas trouve ».

### Changer le statut

```cpp
int index = trouverIndex(id);
if (index != -1)
{
    voitures[index].setStatut(nouveauStatut);
    sauvegarder();
}
```

La voiture est recherchee, son statut est modifie, puis la nouvelle liste est sauvegardee.

### Menu

Le `switch` du menu appelle la bonne fonction selon le choix de l'utilisateur : ajouter, afficher, rechercher, modifier, supprimer ou afficher les disponibles.

---

## 8. Classe GestionClients

### Role

`GestionClients` gere tous les objets `Client`.

```cpp
vector<Client> clients;
```

### Ajouter un client

```cpp
Client client;
client.setId(nouvelId());
client.saisir();
clients.push_back(client);
sauvegarder();
```

Les cinq etapes sont : creer, identifier, remplir, ajouter a la liste et sauvegarder.

### Modifier

Le programme cherche l'index du client, appelle `saisir`, conserve son identifiant, puis sauvegarde.

### Supprimer

```cpp
clients.erase(clients.begin() + index);
```

Cette instruction retire le client situe a la position `index`.

### Tri

Le programme fait une copie de la liste et compare les noms avec des boucles. La liste originale n'est donc pas modifiee par l'affichage trie.

---

## 9. Classe GestionFactures

### Role

`GestionFactures` gere la liste des factures.

```cpp
vector<Facture> factures;
```

### Ajouter une facture

```cpp
factures.push_back(facture);
sauvegarder();
```

La facture est ajoutee puis enregistree dans `factures.txt`.

### Trouver une location en cours

Le programme compare l'identifiant de la voiture et le statut de la facture :

```cpp
if (factures[i].getIdVoiture() == idVoiture &&
    factures[i].getStatutLocation() == "En cours")
    return i;
```

La facture trouvee correspond donc a la voiture et n'est pas encore terminee.

### Chiffre d'affaires

```cpp
double total = 0;
for (int i = 0; i < (int)factures.size(); i++)
    total += factures[i].getMontantTotal();
return total;
```

Le programme additionne le montant de chaque facture.

---

## 10. Classe Agence

### Role

`Agence` coordonne les classes de gestion. Elle ne represente pas une voiture ou un client : elle dirige le fonctionnement general.

### Demarrage

```cpp
void Agence::demarrer()
{
    gestionVoitures.charger();
    gestionClients.charger();
    gestionFactures.charger();
    menuPrincipal();
}
```

Les donnees sont chargees avant l'affichage du menu.

### Nouvelle location

Les etapes sont :

1. choisir un client ;
2. verifier son existence ;
3. choisir une voiture disponible ;
4. saisir les dates ;
5. choisir avec ou sans chauffeur ;
6. calculer le prix ;
7. enregistrer la facture ;
8. mettre la voiture en statut `Louee`.

Code du choix chauffeur :

```cpp
int choixChauffeur = lireEntier(ligne, 0);
bool avecChauffeur = false;

if (choixChauffeur == 1)
    avecChauffeur = true;
```

Code du prix :

```cpp
double prixChauffeurJour = 0;
if (avecChauffeur)
    prixChauffeurJour = 5000;
```

### Retour d'une voiture

Au retour, le programme :

- cherche la voiture ;
- cherche la facture en cours ;
- demande l'etat, le carburant et les dommages ;
- demande les frais supplementaires ;
- remet la voiture a `Disponible` ;
- termine la facture.

```cpp
gestionVoitures.changerStatut(idVoiture, "Disponible");
facture.ajouterFraisSupplementaires(fraisSupp);
facture.terminerLocation();
gestionFactures.sauvegarder();
```

### Menu principal

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

Chaque `case` correspond a une option affichee a l'utilisateur.

---

## 11. Utils.h et Utils.cpp

### Role

Ces fichiers contiennent des fonctions communes utilisees dans plusieurs classes.

`Utils.h` annonce les fonctions :

```cpp
int lireEntier(string texte, int defaut);
double lireDouble(string texte, double defaut);
int lireChoix();
void pauseMenu();
```

`Utils.cpp` contient leur fonctionnement.

### Conversion en entier

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

- `stringstream` lit un nombre dans une chaine ;
- `ss >> valeur` tente la conversion ;
- `ss.fail()` verifie l'erreur ;
- en cas d'erreur, la valeur par defaut est retournee.

### Lecture d'un choix

```cpp
int lireChoix()
{
    string ligne;
    getline(cin, ligne);
    return lireEntier(ligne, -1);
}
```

Le programme lit la ligne du menu et la transforme en entier.

### Pause

```cpp
void pauseMenu()
{
    cout << "Appuyez sur Entree pour continuer...";
    string ligne;
    getline(cin, ligne);
}
```

La fonction attend simplement une validation avec Entree.

---

## 12. Principes de la POO utilises

### Classe

Une classe est un modele qui regroupe des donnees et des fonctions.

### Objet

Un objet est une instance d'une classe :

```cpp
Voiture voiture;
Client client;
Facture facture;
```

### Encapsulation

Les attributs sont `private` et l'acces se fait avec des fonctions `public`, comme les getters et setters.

### Abstraction

Une classe cache les details inutiles. Par exemple, on appelle `charger()` sans voir toutes les instructions de lecture du fichier.

### Modularite

Le projet est divise en classes et fichiers. Chaque partie a un role precis.

Le projet n'utilise pas l'heritage et n'utilise pas de surcharge de fonctions.

---

## 13. Reponses tres courtes a memoriser

**A quoi sert une classe ?**

> Elle regroupe les informations et les fonctions d'un meme element.

**A quoi sert `private` ?**

> Il protege les attributs pour qu'ils ne soient pas modifies directement.

**A quoi sert un getter ?**

> Il permet de lire une information privee.

**A quoi sert un setter ?**

> Il permet de modifier une information privee.

**A quoi sert `const` ?**

> Il indique que la fonction ne modifie pas l'objet.

**A quoi sert `vector` ?**

> Il contient une liste de plusieurs objets.

**A quoi sert `&` dans `Voiture&` ?**

> La fonction travaille directement avec l'objet existant, sans creer une copie.

**A quoi sert `Agence` ?**

> Elle coordonne les classes de gestion et le menu principal.

**A quoi sert `Utils` ?**

> Il regroupe les petites fonctions communes de lecture et de conversion.

**Comment est calcule le prix ?**

> Prix de la voiture par jour multiplie par le nombre de jours, plus le chauffeur eventuel et les frais supplementaires.

**Le programme gere-t-il le paiement ?**

> Non. Il affiche le montant total, mais ne gere pas l'argent verse par le client.
