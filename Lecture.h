/*************************************************************************
                           Lecture  -  Classe pour lire un fichier
                             -------------------
    Début                : 31-05-2025
    Copyright            : (C) 2025 by Rida Bindech
    E-mail               : rida.bindech@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Lecture> (fichier Lecture.h) ----------------
#if ! defined ( LECTURE_H )
#define LECTURE_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

using namespace std;

//------------------------------------------------------------------------
// Rôle de la classe <Lecture>
// Cette classe permet d'ouvrir et de lire un fichier ligne par ligne ou mot par mot.
// Elle stocke les données lues dans un vecteur de chaînes.
//
//------------------------------------------------------------------------

class Lecture
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
    bool Readfile(vector<string> &line);
    // Mode d'emploi :
    //  - Lire le fichier et stocker son contenu dans un vecteur de chaînes.
    // Contrat :
    //  - Le fichier doit être accessible en lecture.


//------------------------------------------------- Surcharge d'opérateurs
    Lecture & operator=(const Lecture &unLecture);
    // Mode d'emploi :
    //  - Permet d'affecter une instance de Lecture à une autre.
    // Contrat :
    //  - L'auto-affectation est gérée.


//-------------------------------------------- Constructeurs - destructeur
    Lecture(const string &fileName);
    // Mode d'emploi :
    //  - Construit un objet Lecture et ouvre un fichier donné en paramètre.
    // Contrat :
    //  - Le fichier doit exister et être lisible.

    Lecture(const Lecture &unLecture);
    // Mode d'emploi :
    //  - Copie un objet Lecture existant.
    // Contrat :
    //  - L'objet copié doit être valide.

    virtual ~Lecture();
    // Mode d'emploi :
    //  - Ferme le fichier si ouvert et libère les ressources.

//------------------------------------------------------------------ PRIVE
private:
//----------------------------------------------------- Attributs protégés
    std::fstream file; 
    std::string fileName;
};

//-------------------------------- Autres définitions dépendantes de <Lecture>

#endif // LECTURE_H
