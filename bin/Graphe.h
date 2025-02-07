/*************************************************************************
        Graphe  -  génère un fichier .dot compatible avec GraphViz
                             -------------------
    début                : 24/01/2025
    auteur               : Lilas DUREUIL
*************************************************************************/

//-------- Interface de la classe <Graphe> (fichier Graphe.h) ------------
#if ! defined ( GRAPHE_H )
#define GRAPHE_H

//-------------------------------------------------------- Include système
using namespace std;
#include <unordered_map>

//------------------------------------------------------------------ Types
typedef unordered_map<string, pair<unordered_map<string, int>, int >> Statistiques;

//------------------------------------------------------------------------
// Rôle de la classe <Graphe>
// La classe Graphe permet de créer un fichier .dot, et d'y insérer chaque
// URL comme un nœud et chaque requête d'une URL à une autre comme une
// arrête dirigée et pondérée.
//------------------------------------------------------------------------

class Graphe 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void toDot ( const string nom = "graphe.dot" ) const;
    // Mode d'emploi : À partir de l'objet invoquant la méthode, crée un fichier
    // .dot correspondant au graphe associé aux statistiques.

//------------------------------------------------- Surcharge d'opérateurs
    Graphe & operator = ( const Graphe & unGraphe );
    // Mode d'emploi : Surcharge de l'opérateur d'affectation permettant de
    // copier un graphe dans un autre.

//-------------------------------------------- Constructeurs - destructeur

    Graphe ( const Graphe& unGraphe );
    // Mode d'emploi : Construit un objet de type Graphe par copie de unGraphe.

    Graphe ( const Statistiques & desStats );
    // Mode d'emploi : Construit un objet de type Graphe à partir des 
    // statistiques associés à un fichier de log.

    virtual ~Graphe ( );
    // Mode d'emploi : Détruit un objet Graphe.

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    Statistiques stats;

};

#endif // GRAPHE_H

