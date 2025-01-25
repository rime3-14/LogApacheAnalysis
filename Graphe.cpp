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

    // Redirection du stream buffer associé à l’objet cout sur le stream buffer associé
    // à l’objet fichier en conservant l’adresse de l’ancien stream buffer de cout
    streambuf *oldCoutBuffer = cout.rdbuf ( fichier.rdbuf( ) );

    // Affichage formaté avec cout, redirigé dans notre fichier à cause du changement de stream buffer
    cout << "digraph {" << endl;

    vector<string> correspondances;

     // Parcours du graphe pour ajouter ses arrêtes
    for (graphe::iterator it1 = (*graph).begin ( ) ; it1 != (*graph).end ( ) ; ++it1 ) {
        for (unordered_map<string, int>::iterator it2 = it1->second.first.begin ( ) ; it2 != it1->second.first.end ( ) ; ++it2 ) {
            // if A not in correspondances add A and node number, else find node number
            int indexA;

            vector<string>::iterator it_c = correspondances.begin ( );
            while ((it_c != correspondances.end ( )) && (*it_c != (*it1).first)) {
                ++it_c;
            }

            if (it_c == correspondances.end ( )) {
                indexA = correspondances.size ( );
                correspondances.push_back((*it1).first);
            } else {
                indexA = it_c - correspondances.begin ( );
            }

            cout << "node" << indexA << " [label=\"" << (*it1).first << "\"];" << endl;

            // if B not in correspondances add B and node number, else find node number
            int indexB;

            it_c = correspondances.begin ( );
            while ((it_c != correspondances.end ( )) && (*it_c != (*it2).first)) {
                ++it_c;
            }

            if (it_c == correspondances.end ( )) {
                indexB = correspondances.size ( );
                correspondances.push_back((*it2).first);
            } else {
                indexB = it_c - correspondances.begin ( );
            }

            cout << "node" << indexB << " [label=\"" << (*it2).first << "\"];" << endl;

            // add A -> B
            cout << "node" << indexA << " -> node" << indexB << " [label=\"" << (*it2).second << "\"];" << endl;
        }
    }

    cout << "}" << endl;

    // Restauration du stream buffer par défaut pour cout, c’est-à-dire la console 
    cout.rdbuf ( oldCoutBuffer);

    // Affichage formaté à l’aide de l’objet cout, à nouveau sur la console
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


Graphe::Graphe ( graphe * const unGraphe )
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