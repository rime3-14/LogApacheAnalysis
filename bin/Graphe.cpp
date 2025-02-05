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
    ofstream fichier ( nom );

    fichier << "digraph {" << endl;

    unordered_map<string, int> correspondances;
    int next_index = 0;
    int indexA, indexB;
    unordered_map<string, int>::iterator it_A;
    unordered_map<string, int>::iterator it_B;

     // Parcours du graphe pour ajouter ses arrêtes
    for (graphe::const_iterator it1 = graph.cbegin ( ) ; it1 != graph.cend ( ) ; ++it1 ) {
        for (unordered_map<string, int>::const_iterator it2 = it1->second.first.cbegin ( ) ; it2 != it1->second.first.cend ( ) ; ++it2 ) {
            // if A not in correspondances add A and node number, else find node number

            it_A = correspondances.find ( (*it1).first );
            it_B = correspondances.find ( (*it2).first );
 
            if (it_A == correspondances.end ( )) {
                correspondances.insert( pair<string, int>( (*it1).first, next_index ));
                indexA = next_index++;
                fichier << "node" << indexA << " [label=\"" << (*it1).first << "\"];" << endl;
            } else {
                indexA = (*it_A).second;
            }

            if (it_B == correspondances.end ( )) {
                correspondances.insert( pair<string, int>( (*it2).first, next_index ));
                indexB = next_index++;
                fichier << "node" << indexB << " [label=\"" << (*it2).first << "\"];" << endl;
            } else {
                indexB = (*it_B).second;
            }

            // add A -> B
            fichier << "node" << indexB << " -> node" << indexA << " [label=\"" << (*it2).second << "\"];" << endl;
        }
    }

    fichier << "}" << endl;

    cout << "Dot-file " << nom << " generated" << endl;

    // Fermeture du fichier redirection.txt
    fichier.close ( );

} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs
Graphe & Graphe::operator = ( const Graphe & unGraphe )
// Algorithme :
//
{
    graph = unGraphe.graph; // Copie ou même objet ?
    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Graphe::Graphe ( const Graphe & unGraphe )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Graphe>" << endl;
#endif
    graph = unGraphe.graph; // Copie ou même objet ?
} //----- Fin de Graphe (constructeur de copie)


Graphe::Graphe ( const graphe & unGraphe )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Graphe>" << endl;
#endif
    graph = unGraphe;
} //----- Fin de Graphe


Graphe::~Graphe ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Graphe>" << endl;
#endif
} //----- Fin de ~Graphe