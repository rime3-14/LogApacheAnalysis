/*************************************************************************
                           Lecture  -  Gestion de la lecture d'un fichier
                             -------------------
    Début                : 31/01/2025
    Copyright            : (C) 2025 by Rida Bindech
    E-mail               : rida.bindech@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Lecture> (fichier Lecture.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <fstream>
#include <vector>

//------------------------------------------------------ Include personnel
#include "Lecture.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool Lecture::Readfile(vector<string> &mots)
// Algorithme : Lit une ligne du fichier, extrait les mots et les ajoute à un vecteur.
//
{
    mots.clear();  // Vider le vecteur avant de l'utiliser
    int i = 0;     // Compteur d'indices pour gérer les cas spéciaux
    char c;        // Variable pour stocker chaque caractère de la ligne
    string ligne;

    // Lire une ligne du fichier
    if (getline(file, ligne)) {
        // Parcours de la ligne caractère par caractère
        while (i < 11) {
            string mot;
            for (size_t j = 0; j < ligne.size(); ++j) {
                c = ligne[j];

                // Cas spécial pour l'indice 3 : ajouter tout ce qui se trouve entre "[" et "]"
                if (i == 3) {
                    if (c == '[') {
                        mot += c;
                        ++j;  // Passer au caractère suivant après "["
                        while (j < ligne.size() && ligne[j] != ']') {
                            mot += ligne[j];  // Ajouter tous les caractères jusqu'à ']'
                            ++j;
                        }
                        if (j < ligne.size() && ligne[j] == ']') {
                            mot += ligne[j];  // Ajouter le caractère ']' à la fin
                        }
                    } else {
                        mot += c;
                    }
                }

                // Cas spécial pour l'indice 10 : ajouter tout ce qui se trouve entre '"' et '"'
                else if (i == 10) {
                    if (c == '"') {
                        mot += c;
                        ++j;  // Passer au caractère suivant après '"'
                        while (j < ligne.size() && ligne[j] != '"') {
                            mot += ligne[j];  // Ajouter tous les caractères jusqu'à '"'
                            ++j;
                        }
                        if (j < ligne.size() && ligne[j] == '"') {
                            mot += ligne[j];  // Ajouter le caractère '"' à la fin
                        }
                    } else {
                        mot += c;
                    }
                }

                // Ajouter le caractère au mot normal
                else if (!isspace(c)) {
                    mot += c;  // Ajouter le caractère au mot
                }

                // Quand un espace est rencontré, ajouter le mot au vecteur
                if (isspace(c) || j == ligne.size() - 1) {
                    if (!mot.empty()) {
                        mot.erase(remove(mot.begin(), mot.end(), '"'), mot.end());  // Supprimer les guillemets
                        mots.push_back(mot);  // Ajouter le mot au vecteur
                        mot.clear();  // Réinitialiser le mot
                        i++; 
                    }
                }
            }
        }
        return true;
    }

    return false;  // Retourner faux si la ligne n'a pas pu être lue
} //----- Fin de Readfile


//------------------------------------------------- Surcharge d'opérateurs
Lecture & Lecture::operator = (const Lecture &unLecture)
// Algorithme : Assurer la gestion de l'auto-affectation et copier l'état d'un autre objet Lecture.
//
{
    if (this != &unLecture) {  // Vérifier l'auto-affectation
        // Fermer le fichier actuel s'il est ouvert
        if (file.is_open()) {
            file.close();
        }

        // Copier le nom du fichier
        fileName = unLecture.fileName;

        // Réouvrir le fichier avec le nouveau nom
        file.open(fileName);
        if (!file) {
            cerr << "Erreur d'ouverture du fichier dans l'opérateur =" << endl;
        }
    }
    return *this;  // Retourner l'objet courant
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Lecture::Lecture(const string &fileName) :fileName(fileName), file(fileName)
// Algorithme : Initialisation d'un objet Lecture avec un nom de fichier et ouverture du fichier.
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Lecture>" << endl;
#endif

    if (!file) {
        cerr << "Erreur d'ouverture du fichier !" << endl;
    }
} //----- Fin de Lecture


Lecture::Lecture(const Lecture &unLecture) :fileName(unLecture.fileName), file(unLecture.fileName)
// Algorithme : Constructeur de copie, initialise un objet Lecture avec un autre objet de même type.
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Lecture>" << endl;
#endif

    if (!file) {
        cerr << "Erreur d'ouverture du fichier !" << endl;
    }  
} //----- Fin de Lecture (constructeur de copie)


Lecture::~Lecture()
// Algorithme : Ferme le fichier lors de la destruction de l'objet.
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Lecture>" << endl;
#endif

    if (file.is_open()) {
        file.close();  // Fermer le fichier si ouvert
    }
} //----- Fin de ~Lecture


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
