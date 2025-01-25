/*************************************************************************
Graphe  -  génère un fichier .dot compatible avec GraphViz
                             -------------------
    début                : 24/01/2025
    auteur               : Lilas DUREUIL
*************************************************************************/

//---------- Interface de la classe <Graphe> (fichier Graphe.h) ----------------
#if ! defined ( GRAPHE_H )
#define GRAPHE_H

//-------------------------------------------------------- Include système
using namespace std;
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef unordered_map<string, pair<unordered_map<string, int>, int >> graphe; 

//------------------------------------------------------------------------
// Rôle de la classe <Graphe>
//
//
//------------------------------------------------------------------------

class Graphe 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void toDot ( const string nom = "graphe.dot" ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    Graphe & operator = ( const Graphe & unGraphe );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur

    Graphe ( const Graphe& unGraphe );
    // Mode d'emploi :
    //
    // Contrat :
    //

    Graphe ( graphe * const unGraphe );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Graphe ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    graphe * graph;
    vector<string> correspondances;

};

//-------------------------------- Autres définitions dépendantes de <Graphe>

#endif // GRAPHE_H

