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
#include <sstream>
#include <string>
#include <vector>

//------------------------------------------------------ Include personnel
#include "Lecture.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int Lecture::Readfile(vector<string> &mots)
// Algorithme : Lit une ligne du file, extrait les mots et les ajoute à un vecteur.
//
{
    // Lire la ligne complète depuis le fichier
    string ligne;
    if (!getline(file, ligne)) {
        return -1;  // Fin de fichier ou erreur de lecture
    }

    //0: IP, 1: anonyme, 2: anonyme
    istringstream line(ligne);
    string ip, userLogname, authenticatedUser;
    if (!(line >> ip >> userLogname >> authenticatedUser)) {
        cerr << "Erreur: Log incomplet" << endl;
        return 0;
    }
    mots.push_back(ip);
    mots.push_back(userLogname);
    mots.push_back(authenticatedUser);


    // 3: date et heure
    size_t posDateDeb = ligne.find('[');
    size_t posDateFin = ligne.find(']', posDateDeb);
    if (posDateDeb == string::npos || posDateFin == string::npos) {
        cerr << "Erreur: Mauvais format de date" << endl;
        return 0;
    }
    string datetime = ligne.substr(posDateDeb + 1, posDateFin - posDateDeb - 1);
    mots.push_back(datetime);


    // 4: type d'action, 5: URL, 6: protocole
    size_t posReqDeb = ligne.find('"', posDateFin);
    size_t posReqFin = ligne.find('"', posReqDeb + 1);
    if (posReqDeb == string::npos || posReqFin == string::npos) {
        cerr << "Erreur: Requête HTTP incomplète" << endl;
        return 0;
    }
    string requete = ligne.substr(posReqDeb + 1, posReqFin - posReqDeb - 1);
    // La requête doit contenir trois éléments : méthode, URL et protocole
    istringstream lineReq(requete);
    string methode, url, protocole;
    if (!(lineReq >> methode >> url >> protocole)) {
        cerr << "Erreur: Requête HTTP incomplète" << endl;
        return 0;
    }
    // Vérifier que l'URL n'est pas absente
    if(url.empty()) {
        cerr << "Erreur: URL absente" << endl;
        return 0;
    }
    mots.push_back(methode);
    mots.push_back(url);
    mots.push_back(protocole);


    // 7: return code, 8: taille de réponse
    istringstream lineRest(ligne.substr(posReqFin + 1));
    string codeRetourStr, tailleRepStr;
    if (!(lineRest >> codeRetourStr >> tailleRepStr)) {
        cerr << "Erreur: Log incomplet" << endl;
        return 0;
    }
    // Vérifier que le return code est numérique
    try {
        size_t pos;
        stoi(codeRetourStr, &pos);
        if (pos != codeRetourStr.size())
            throw invalid_argument("Caractère non numérique");
    } catch (exception&) {
        cerr << "Erreur: Code de retour invalide" << endl;
        return 0;
    }
    // Vérifier que la taille de réponse est numérique
    try {
        size_t pos;
        stoi(tailleRepStr, &pos);
        if (pos != tailleRepStr.size())
            throw invalid_argument("Caractère non numérique");
    } catch (exception&) {
        cerr << "Erreur: Taille de réponse invalide" << endl;
        return 0;
    }
    mots.push_back(codeRetourStr);
    mots.push_back(tailleRepStr);


    // 9: referer
    size_t posRefererDeb = ligne.find('"', posReqFin + 1);
    size_t posRefererFin = ligne.find('"', posRefererDeb + 1);
    if (posRefererDeb == string::npos || posRefererFin == string::npos || posRefererDeb > posReqFin + 16) {  // longueur de " 200 1000000 "-""
        cerr << "Erreur: Referer mal formé" << endl;
        return 0;
    }
    string referer = ligne.substr(posRefererDeb + 1, posRefererFin - posRefererDeb - 1);
    mots.push_back(referer);


    // 10: User-Agent
    size_t posUADeb = ligne.find('"', posRefererFin + 1);
    size_t posUAFin = ligne.find('"', posUADeb + 1);
    if (posUADeb == string::npos || posUAFin == string::npos) {
        cerr << "Erreur: User-Agent mal formé" << endl;
        return 0;
    }
    string userAgent = ligne.substr(posUADeb + 1, posUAFin - posUADeb - 1);
    mots.push_back(userAgent);


    return 1;
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
