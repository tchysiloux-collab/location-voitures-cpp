#include "Utils.h"
#include <sstream>
#include <iostream>

int lireEntier(string texte, int defaut)
{
    if (texte.empty())
        return defaut;

    stringstream ss(texte);
    int valeur;
    ss >> valeur;
    if (ss.fail())
        return defaut;

    string reste;
    if (ss >> reste)
        return defaut;

    return valeur;
}

double lireDouble(string texte, double defaut)
{
    if (texte.empty())
        return defaut;

    stringstream ss(texte);
    double valeur;
    ss >> valeur;
    if (ss.fail())
        return defaut;

    string reste;
    if (ss >> reste)
        return defaut;

    return valeur;
}

int lireChoix()
{
    string ligne;
    getline(cin, ligne);
    return lireEntier(ligne, -1);
}

void pauseMenu()
{
    cout << "\nAppuyez sur Entree pour continuer...";
    string ligne;
    getline(cin, ligne);
}
