/*************************************************************************
                   Lecture  -  Classe pour lire un fichier
                             -------------------
    Début                : 31/01/2025
    Copyright            : (C) 2025 by Rida Bindech
                           (C) 2025 by Enzo Dos Anjos
    E-mail               : rida.bindech@insa-lyon.fr
                           enzo.dosanjos@insa-lyon.fr
*************************************************************************/

//------ Interface de la classe <Lecture> (fichier Lecture.h) ------------
#if ! defined ( LECTURE_H )
#define LECTURE_H

//------------------------------------------------------------------------
// Rôle de la classe <Lecture>
// Cette classe permet d'ouvrir un fichier de log et d'en extraire ligne
// par ligne les champs dans un vecteur de string.
//------------------------------------------------------------------------

//-------------------------------------------------------- Include système
using namespace std;
#include <fstream>

class Lecture
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
    int Readfile(vector<string> &line);
    // Mode d'emploi : Permet de lire une ligne du fichier de log et d'en 
    // stocker le contenu dans un vecteur de string.

//------------------------------------------------- Surcharge d'opérateurs
    Lecture & operator=(const Lecture &unLecture);
    // Mode d'emploi : Permet d'affecter une instance de Lecture à une autre.

//-------------------------------------------- Constructeurs - destructeur
    Lecture(const string &fileName);
    // Mode d'emploi : Construit un objet Lecture et ouvre un fichier donné 
    // en paramètre.

    Lecture(const Lecture &unLecture);
    // Mode d'emploi : Copie un objet Lecture existant.

    virtual ~Lecture();
    // Mode d'emploi : Ferme le fichier si ouvert pour détruire l'objet Lecture.

//------------------------------------------------------------------ PRIVE
private:
//----------------------------------------------------- Attributs protégés
    fstream file; 
    string fileName;

};

#endif // LECTURE_H
