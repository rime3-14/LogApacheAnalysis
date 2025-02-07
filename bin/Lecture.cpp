/*************************************************************************
                Lecture  -  Gestion de la lecture d'un fichier
                             -------------------
    Début                : 31/01/2025
    Copyright            : (C) 2025 by Rida Bindech
                           (C) 2025 by Enzo Dos Anjos
    E-mail               : rida.bindech@insa-lyon.fr
                           enzo.dosanjos@insa-lyon.fr
*************************************************************************/

//------ Réalisation de la classe <Lecture> (fichier Lecture.cpp) --------

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

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int Lecture::Readfile(vector<string> &infosRequete)
// Algorithme : Utilise la méthode find pour traiter les lignes mal formées.
{
    // Lecture d'une ligne complète depuis le fichier
    string ligne;

    if (!getline(file, ligne)) 
    {
        return -1;  // Fin de fichier ou erreur de lecture
    }

    // Récupération des champs 0: IP, 1: anonyme, et 2: anonyme
    istringstream fluxLigne(ligne); // Extraction des 3 champs
    string ip;
    string userLogname;
    string authenticatedUser;

    if (!(fluxLigne >> ip >> userLogname >> authenticatedUser)) 
    {
        cerr << "Erreur: Log incomplet" << endl;
        return 0;
    }

    infosRequete.push_back(ip);
    infosRequete.push_back(userLogname);
    infosRequete.push_back(authenticatedUser);


    // Récupération du champ 3: date et heure
    size_t posDateDeb = ligne.find('[');
    size_t posDateFin = ligne.find(']', posDateDeb);

    if (posDateDeb == string::npos || posDateFin == string::npos) 
    {
        cerr << "Erreur: Mauvais format de date" << endl;
        return 0;
    }

    string dateTime = ligne.substr(posDateDeb + 1, posDateFin - posDateDeb - 1);
    infosRequete.push_back(dateTime);


    // Récupération des champs 4: type d'action, 5: URL, et 6: protocole
    size_t posReqDeb = ligne.find('"', posDateFin);
    size_t posReqFin = ligne.find('"', posReqDeb + 1);

    if (posReqDeb == string::npos || posReqFin == string::npos) 
    {
        cerr << "Erreur: Requête HTTP incomplète" << endl;
        return 0;
    }
    string requete = ligne.substr(posReqDeb + 1, posReqFin - posReqDeb - 1);

    // La requête doit contenir trois éléments : méthode, URL et protocole
    istringstream fluxLigneReq(requete);
    string methode;
    string url;
    string protocole;

    if (!(fluxLigneReq >> methode >> url >> protocole)) 
    {
        cerr << "Erreur: Requête HTTP incomplète" << endl;
        return 0;
    }

    // Vérifier que l'URL n'est pas absente
    if(url.empty()) 
    {
        cerr << "Erreur: URL absente" << endl;
        return 0;
    }

    infosRequete.push_back(methode);
    infosRequete.push_back(url);
    infosRequete.push_back(protocole);


    // Récupération des champs 7: return code, et 8: taille de réponse
    istringstream fluxLigneRest(ligne.substr(posReqFin + 1));
    string codeRetourStr;
    string tailleRepStr;

    if (!(fluxLigneRest >> codeRetourStr >> tailleRepStr)) 
    {
        cerr << "Erreur: Log incomplet" << endl;
        return 0;
    }

    try // Vérifier que le return code est numérique
    {
        size_t pos;
        stoi(codeRetourStr, &pos);
        if (pos != codeRetourStr.size())
            throw invalid_argument("Caractère non numérique");
    } 
    catch (exception&) 
    {
        cerr << "Erreur: Code de retour invalide" << endl;
        return 0;
    }

    // Vérifier que la taille de réponse est numérique
    if (tailleRepStr == "-") // Traiter le cas où il n'y a pas eu de transfert
    {
        tailleRepStr = '0';
    }

    try 
    {
        size_t pos;
        stoi(tailleRepStr, &pos);
        if (pos != tailleRepStr.size())
            throw invalid_argument("Caractère non numérique");
    } 
    catch (exception&) 
    {
        cerr << "Erreur: Taille de réponse invalide" << endl;
        return 0;
    }

    infosRequete.push_back(codeRetourStr);
    infosRequete.push_back(tailleRepStr);


    // Récupération du champ 9: referer
    size_t posRefererDeb = ligne.find('"', posReqFin + 1);
    size_t posRefererFin = ligne.find('"', posRefererDeb + 1);

    if (posRefererDeb == string::npos || posRefererFin == string::npos 
          || posRefererDeb > posReqFin + 16) // longueur de " 200 1000000 "-""
    {  
        cerr << "Erreur: Referer mal formé" << endl;
        return 0;
    }

    string referer = ligne.substr(posRefererDeb + 1, posRefererFin - posRefererDeb - 1);
    infosRequete.push_back(referer);


    // Récupération du champ 10: User-Agent
    size_t posUADeb = ligne.find('"', posRefererFin + 1);
    size_t posUAFin = ligne.find('"', posUADeb + 1);

    if (posUADeb == string::npos || posUAFin == string::npos) 
    {
        cerr << "Erreur: User-Agent mal formé" << endl;
        return 0;
    }

    string userAgent = ligne.substr(posUADeb + 1, posUAFin - posUADeb - 1);
    infosRequete.push_back(userAgent);


    return 1;
} //----- Fin de Readfile


//------------------------------------------------- Surcharge d'opérateurs
Lecture & Lecture::operator = (const Lecture &unLecture)
{
    if (this != &unLecture) 
    {
        // Fermer le fichier actuel s'il est ouvert
        if (file.is_open()) 
        {
            file.close();
        }

        // Copier le nom du fichier
        fileName = unLecture.fileName;

        // Réouvrir le fichier avec le nouveau nom
        file.open(fileName);
        if (!file) 
        {
            cerr << "Erreur d'ouverture du fichier dans l'opérateur =" << endl;
        }
    }

    return *this;  // Retourner l'objet courant
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Lecture::Lecture(const string &name) :fileName(name)
{
#if MAP
    cout << "Appel au constructeur de <Lecture>" << endl;
#endif

    file.open(fileName);

    if (!file) 
    {
        throw runtime_error("Erreur d'ouverture du fichier : " + fileName);
    }
} //----- Fin de Lecture


Lecture::Lecture(const Lecture &unLecture) :fileName(unLecture.fileName)
{
#if MAP
    cout << "Appel au constructeur de copie de <Lecture>" << endl;
#endif

    file.open(fileName);

    if (!file) 
    {
        throw runtime_error("Erreur d'ouverture du fichier : " + fileName);
    }
} //----- Fin de Lecture (constructeur de copie)


Lecture::~Lecture()
// Algorithme : Ferme le fichier lors de la destruction de l'objet.
{
#if MAP
    cout << "Appel au destructeur de <Lecture>" << endl;
#endif

    if (file.is_open()) 
    {
        file.close();  // Fermer le fichier si ouvert
    }
} //----- Fin de ~Lecture
