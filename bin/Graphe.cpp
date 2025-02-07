/*************************************************************************
Graphe  -  génère un fichier .dot compatible avec GraphViz
                             -------------------
    début                : 24/01/2025
    auteur               : Lilas DUREUIL
*************************************************************************/

//------- Réalisation de la classe <Graphe> (fichier Graphe.cpp) ---------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <fstream>

//------------------------------------------------------ Include personnel
#include "Graphe.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Graphe::toDot ( const string nom ) const
// Algorithme :
//
{
    // Instanciation et ouverture du ficher de sortie .dot
    ofstream fichier;
    fichier.open( nom );

    // Création d'une table des correspondances entre numéro de nœud et URL
    unordered_map<string, int> correspondances;

    // Remplissage du fichier
    fichier << "digraph {" << endl;

    int nextIndex = 0; // Numéro du prochain nœud à ajouter au .dot
    int indexHit; // Numéros de nœud du hit et du referer
    int indexRef;
    unordered_map<string, int>::iterator itCorrHit; // Itérateurs dans la map des correspondances
    unordered_map<string, int>::iterator itCorrRef;

     // Parcours du graphe pour ajouter ses nœuds et arrêtes au fichier
    for (graphe::const_iterator itGrHit = graph.cbegin ( ) ; itGrHit != graph.cend ( ) ; ++itGrHit ) {
        for (unordered_map<string, int>::const_iterator itGrRef = itGrHit->second.first.cbegin ( ) ; itGrRef != itGrHit->second.first.cend ( ) ; ++itGrRef ) {
            
            // Recherche des numéros de nœuds correspondants au hit et au referer
            itCorrHit = correspondances.find ( (*itGrHit).first );
            itCorrRef = correspondances.find ( (*itGrRef).first );
            
            // Si une recherche échoue, on ajoute le nœud correspondant à la map des correspondances et au .dot
            if (itCorrHit == correspondances.end ( )) {
                correspondances.insert( pair<string, int>( (*itGrHit).first, nextIndex ));
                indexHit = nextIndex++;
                fichier << "node" << indexHit << " [label=\"" << (*itGrHit).first << "\"];" << endl;
            } else {
                indexHit = (*itCorrHit).second; // Sinon, on récupère le numéro de nœud dans les correspondances
            }

            if (itCorrRef == correspondances.end ( )) {
                correspondances.insert( pair<string, int>( (*itGrRef).first, nextIndex ));
                indexRef = nextIndex++;
                fichier << "node" << indexRef << " [label=\"" << (*itGrRef).first << "\"];" << endl;
            } else {
                indexRef = (*itCorrRef).second;
            }

            // Ajout de l'arrête au .dot
            fichier << "node" << indexRef << " -> node" << indexHit << " [label=\"" << (*itGrRef).second << "\"];" << endl;
        }
    }

    fichier << "}";

    cout << "Dot-file " << nom << " generated" << endl;

    // Fermeture du fichier redirection.txt
    fichier.close ( );

} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs
Graphe & Graphe::operator = ( const Graphe & unGraphe )
// Algorithme :
//
{
    graph = unGraphe.graph; // Deep copy du graph de unGraphe
    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Graphe::Graphe ( const Graphe & unGraphe )
// Algorithme :
//
{
#if MAP
    cout << "Appel au constructeur de copie de <Graphe>" << endl;
#endif
    graph = unGraphe.graph; // Deep copy du graph de unGraphe
} //----- Fin de Graphe (constructeur de copie)


Graphe::Graphe ( const graphe & unGraphe )
// Algorithme : Construit un objet de classe à partir d'un
// objet de type graphe
{
#if MAP
    cout << "Appel au constructeur de <Graphe>" << endl;
#endif
    graph = unGraphe;
} //----- Fin de Graphe


Graphe::~Graphe ( )
// Algorithme : Les libérations mémoire des objets Graphe 
// sont toutes réalisées automatiquement.
{
#if MAP
    cout << "Appel au destructeur de <Graphe>" << endl;
#endif
} //----- Fin de ~Graphe