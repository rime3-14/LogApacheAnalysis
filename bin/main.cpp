/*************************************************************************
                    Main  -  Gère les options donné eet l'affichage du top 10
                             -------------------
    Début                : 24-05-2025
    Copyright            : (C) 2025 by Enzo Dos Anjos
    E-mail               : enzo.dosanjos@insa-lyon.fr
*************************************************************************/

//-------------------------- Fichier main.cpp ----------------------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>

// Lecture des logs
#include <vector>
#include <string>

// Conteneur pour le nombre de trajets referer -> cible
#include <unordered_map>
#include <utility>

// Conteneur pour le Top10
#include <map>

//------------------------------------------------------ Include personnel
#include "Graphe.h"
#include "Lecture.h"

//---------------------------------------------------- Programme principal
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Utilisation: ./analog [options] nomfichier.log" << endl;
        return 1;
    }

    // Flags
    bool gFlag = false;  // option -g
    bool eFlag = false;  // option -e
    bool tFlag = false;  // option -t


    // Variables
    string logName = argv[argc-1];  // nom du fichier de log
    string graphFileName;  // nom du fichier graphe

    // début d'url à retirer correspondant au site parent des documents
    string debutUrl = "http://intranet-if.insa-lyon.fr";
    string heure;  // heure donné après l'option -t
    bool outLine;  // boolean déterminant si la ligne doit être ignoré ou non

    // Objet de type utilisateur graphe, pour créer le graphe et le top 10
    graphe dataLog;


    // Vérification des options
    for (int i = 1; i < argc - 1; i++)
    {
       if (strcmp(argv[i], "-g") == 0)
       {
            // Vérification du nom du graphe si ce n'est pas le nom du fichier 
            // log ou l'option suivante qui a été pris. La deuxième vérification
            // regarde si le char* d'après commence par "-"
            if (++i == argc-1 || string(argv[i]).substr(0, 1) == "-")
            {
                cerr << "Erreur : Le nom du fichier graphe n'a pas été donné" << 
                        endl;
                return 1;
            }

            graphFileName = argv[i];

            if (graphFileName.size() < 4 ||
                graphFileName.substr(graphFileName.size() - 4) != ".dot")
            {
                cerr << "Erreur : Le nom du fichier graphe est invalide"
                        "(doit terminer par .dot)" << endl;
                return 1;
            }

            gFlag = true;

        }
        else if (strcmp(argv[i], "-e") == 0)
        {
            eFlag = true;
            
        }
        else if (strcmp(argv[i], "-t") == 0)
        {
            if (++i == argc-1 || string(argv[i]).substr(0, 1) == "-")
            {
                cerr << "Erreur : L'heure n'a pas été donné" << endl;
                return 1;
            }

            for (char c : string(argv[i]))
            {
                if (!isdigit(c))
                {
                    cerr << "Erreur : l'heure n'est pas numérique" << endl;
                    return 1;
                }
            }

            heure = argv[i];

            if (stoi(heure) < 0 || stoi(heure) > 24)
            {
                cerr << "Erreur : Veuillez entrer une heure valide" << endl;
                return 1;
            }

            tFlag = true;
            
        }
        else if (strcmp(argv[i], "-ub") == 0)
        {
            if (++i == argc-1 || string(argv[i]).substr(0, 1) == "-")
            {
                cerr << "Erreur : L'Url de début à retirer n'a pas été donné" << 
                        endl;
                return 1;
            }

            debutUrl = argv[i];

            // Vérification de la validité du nouvel URL
            if (debutUrl.substr(0, 4) != "http")
            {
                cerr << "Erreur : Veuillez entrer un début d'url à retirer "
                        "valide" << endl;
                return 1;
            }

        }
        else
        {
            cerr << "Erreur : Option inconnue donnée ( " << argv[i] << " )" << 
                    endl;
            return 1;
        }
    }
    

    Lecture* lecture = nullptr;
    try
    {
        // Alloue dynamiquement l'objet (nécessaire pour utiliser try sans 
        // construire d'objet avant)
        lecture = new Lecture(logName);
    }
    catch (const runtime_error &e)
    {
        cerr << e.what() << endl;
        return 1;
    }

    // Retour de la fonction Readfile, correspondant aux codes erreurs
    int resLecture;
    vector<string> line;

    while ((resLecture = lecture->Readfile(line)) >= 0)
    {
        if (resLecture == 1)
        {
            outLine = true;

            // Troncature du début de l'URL correspondant au site parcouru
            size_t debutUrlStart = line[9].find(debutUrl);
            if (debutUrlStart != string::npos)
            {
                line[9].erase(debutUrlStart, debutUrl.size());
            }

            // Filtrage des lignes ayant pour cible un fichier image, CSS ou JS
            if (eFlag)
            {
                string cible = line[5];  
                if (cible.size() >= 4)
                {
                    string extension4 = cible.substr(cible.size() - 4);
                    string extension3 = cible.substr(cible.size() - 3);
                    if (extension4 == ".jpg" || extension4 == ".ico" ||
                        extension4 == ".png" || extension4 == ".gif" || 
                        extension4 == ".css" || extension3 == ".js") {
                        
                        outLine = false;
                    }
                }
            }

            // Filtrage des lignes ayant une heure différente de celle considérée
            if (tFlag)
            {
                string timestamp = line[3];
                size_t pos = timestamp.find(':');
                string logHour = timestamp.substr(pos + 1, 2);
                if (stoi(logHour) != stoi(heure))
                {
                    outLine = false;
                }
            } 

            // Récupération des données de création du graphe et du Top10
            if (outLine)
            {
                // Récupération du referer et de la cible de la requête
                string cible = line[5];
                string referer = line[9];


                // Élément du graphe

                // Incrémentation du nombre de requête ayant les mêmes referer
                // et cible. 
                // Accéder aux éléments avec [cible] crée la paire si elle 
                // n'existe pas et initilise l'int à 0.
                dataLog[cible].first[referer]++;  

                // Incrémentation du nombre de requêtes avec le même referer
                dataLog[cible].second++;
            }
        }

        line.clear();
    }


    if (!dataLog.empty())
    {
        if (gFlag)
        {
            // Création d'un objet de la classe Graphe à partir du graphe dataLog
            Graphe graph(dataLog); 

            // Création et remplissage du fichier .dot 
            graph.toDot(graphFileName);
        }

        // Affichage du Top10

        // Tri automatique par ordre croissant des clés par nombre de hits
        multimap<int, string> top10;

        for (auto it = dataLog.begin(); it != dataLog.end(); ++it)
        {
            // Nombre total de requêtes vers la cible
            int nbRequetes = it->second.second;

            top10.insert({nbRequetes, it->first});

            // Si plus de 10 éléments, supprime le plus petit
            if (top10.size() > 10)
            {
                top10.erase(top10.begin());
            }
        }

        // Affichage du Top10 par ordre décroissant
        for (auto it = top10.rbegin(); it != top10.rend(); ++it)
        {
            cout << it->second << " (" << it->first << " hits)" << endl;
        }
    }
    else
    {
        cout << "Aucune ligne n'a été extraite du fichier de log" << endl;
    }

    delete lecture;  // Libère la mémoire allouée dynamiquement
    return 0;
}