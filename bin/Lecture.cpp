/*************************************************************************
                           Lecture  -  Gestion de la lecture d'un file
                             -------------------
    Début                : 31/01/2025
    Copyright            : (C) 2025 by Rida Bindech
    E-mail               : rida.bindech@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Lecture> (file Lecture.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//------------------------------------------------------ Include personnel
#include "Lecture.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool Lecture::Readfile(vector<string> &mots)
// Algorithme : Lit une ligne du file, extrait les mots et les ajoute à un vecteur.
//
{
    // Lire une ligne du file
    string temp;
    int i;

    if (file.eof()) {
        return false;
    }

    for (i = 0; i < 3; i++) { // 0: IP, 1: anonyme, 2: anonyme
        if (getline(file, temp, ' ')) {
            mots.push_back(temp);

        } else {
            return false;
        }
    }

    getline(file, temp, ']'); // 3: date et heure
    mots.push_back(temp.substr(1));

    getline(file, temp, '"'); 

    for (i = 0; i < 2; i++) { // 4: type d'action, 5: URL
        getline(file, temp, ' ');
        mots.push_back(temp);
    }

    getline(file, temp, '"'); // 6: protocole
    mots.push_back(temp);

    getline(file, temp, ' ');
    for (i = 0; i < 2; i++) { // 7: return code, 8: taille réponse
        getline(file, temp, ' ');
        mots.push_back(temp);
    }

    for (i = 0; i < 2; i++) {
        getline(file, temp, '"');

        getline(file, temp, '"'); // 9: referer, 10: id navigateur
        mots.push_back(temp);
    }

    getline(file, temp);

    return true;
} //----- Fin de Readfile


//------------------------------------------------- Surcharge d'opérateurs
Lecture & Lecture::operator = (const Lecture &unLecture)
// Algorithme : Assurer la gestion de l'auto-affectation et copier l'état d'un autre objet Lecture.
//
{
    if (this != &unLecture) {  // Vérifier l'auto-affectation
        // Fermer le file actuel s'il est ouvert
        if (file.is_open()) {
            file.close();
        }

        // Copier le nom du file
        fileName = unLecture.fileName;

        // Réouvrir le file avec le nouveau nom
        file.open(fileName);
        if (!file) {
            cerr << "Erreur d'ouverture du file dans l'opérateur =" << endl;
        }
    }
    return *this;  // Retourner l'objet courant
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Lecture::Lecture(const string &fileName) :fileName(fileName)
// Algorithme : Initialisation d'un objet Lecture avec un nom de file et ouverture du file.
//
{
#if MAP
    cout << "Appel au constructeur de <Lecture>" << endl;
#endif

    file.open(fileName);

    if (!file) {
        cerr << "Erreur d'ouverture du fichier !" << endl;
    }
} //----- Fin de Lecture


Lecture::Lecture(const Lecture &unLecture) :fileName(unLecture.fileName)
// Algorithme : Constructeur de copie, initialise un objet Lecture avec un autre objet de même type.
//
{
#if MAP
    cout << "Appel au constructeur de copie de <Lecture>" << endl;
#endif

    file.open(fileName);
    if (!file) {
        cerr << "Erreur d'ouverture du fichier !" << endl;
    }  
} //----- Fin de Lecture (constructeur de copie)


Lecture::~Lecture()
// Algorithme : Ferme le file lors de la destruction de l'objet.
//
{
#if MAP
    cout << "Appel au destructeur de <Lecture>" << endl;
#endif

    if (file.is_open()) {
        file.close();  // Fermer le file si ouvert
    }
} //----- Fin de ~Lecture


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
