/*
    ========================================================
    GESTION D'UNE AGENCE DE LOCATION DE VOITURES
    Version orientee objet (POO)
    ========================================================
    Classes utilisees :
      - Voiture, Client, Facture              (les "objets metier")
      - GestionVoitures, GestionClients,
        GestionFactures                       (gerent chacune une liste)
      - Agence                                (chef d'orchestre du programme)

    Bibliotheques utilisees : iostream, string, vector, fstream, iomanip
    ========================================================
*/

#include "Agence.h"

int main()
{
    Agence agence;
    agence.demarrer();
    return 0;
}
