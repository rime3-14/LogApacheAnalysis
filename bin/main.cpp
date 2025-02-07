/*************************************************************************
    début                : 24/01/2025
    e-mail               : enzo.dos-anjos@insa-lyon.fr
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
int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Utilisation: ./analog [options] nomfichier.log" << endl;
        return 1;
    }

    // Flags
    bool g = false;
    bool e = false;
    bool t = false;

    // Variables
    string log_name = argv[argc-1];
    string graph_file_name;
    string debut_url = "http://intranet-if.insa-lyon.fr";
    string heure;
    bool out_line;

    // Objet de type utilisateur graphe, pour créer le graphe et le top 10
    graphe data_log;

    // Vérification des options
    for (int i = 1; i < argc - 1; i++) {
       if (strcmp(argv[i], "-g") == 0) {
            // Vérification du nom du graphe si ce n'est pas le nom du fichier log ou l'option suivante qui a été pris
            if (++i == argc-1 || strstr(argv[i], "-") == argv[i]) {
                cerr << "Erreur : Le nom du fichier graphe n'a pas été donné" << endl;
                return 1;
            }

            graph_file_name = argv[i];

            if (graph_file_name.size() < 4 || graph_file_name.substr(graph_file_name.size() - 4) != ".dot") {
                cerr << "Erreur : Le nom du fichier graphe est invalide (doit terminer par .dot)" << endl;
                return 1;
            }

            g = true;

        } else if (strcmp(argv[i], "-e") == 0) {
            e = true;
            
        } else if (strcmp(argv[i], "-t") == 0) {
            i++;
            for (char c : string(argv[i])) {
                if (!isdigit(c)) {
                    cerr << "Erreur : l'heure n'est pas numérique" << endl;
                    return 1;
                }
            }

            heure = argv[i];

            if (stoi(heure) < 0 || stoi(heure) > 24) {
                cerr << "Erreur : Veuillez entrer une heure valide" << endl;
                return 1;
            }

            t = true;
            
        } else if (strcmp(argv[i], "-ub") == 0) {
            debut_url = argv[++i];

            // Vérification de la validité du nouvel URL
            if (debut_url.substr(0, 4) != "http") {
                cerr << "Erreur : Veuillez entrer un début d'url à retirer valide" << endl;
                return 1;
            }

        } else {
            cerr << "Erreur : Option inconnue donnée ( " << argv[i] << " )" << endl;
            return 1;
        }
    }
    
    // Construction d'un objet lecture qui lit les lignes du fichier log une par une, tant qu'il n'y a pas d'erreur ou de EOF
    Lecture* lecture = nullptr;  // Déclare un pointeur vers Lecture
    try {
        lecture = new Lecture(log_name);  // Alloue dynamiquement l'objet (nécessaire pour utiliser try sans construire d'objet avant)
    } catch (const runtime_error &e) {
        cerr << e.what() << endl;
        return 1;
    }

    int resLecture;  // Retour de la fonction Readfile, correspondant aux codes erreurs de la lecture d'une ligne
    vector<string> line;

    while ((resLecture = lecture->Readfile(line)) >= 0) {
        if (resLecture == 1) {
            out_line = true;  // Variable permettant d'ignorer ou non la ligne, selon les options sélectionnées

            // Troncature du début de l'URL correspondant au site parcouru
            size_t debut_url_start = line[9].find(debut_url);
            if (debut_url_start != string::npos) {
                line[9].erase(debut_url_start, debut_url.size());
            }

            // Filtrage des lignes ayant pour cible un fichier image, CSS ou Javascript
            if (e) {
                string url = line[5];
                if (url.size() >= 4) {
                    string extension4 = url.substr(url.size() - 4);
                    string extension3 = url.substr(url.size() - 3);
                    if (extension4 == ".jpg" || extension4 == ".ico" || extension4 == ".png" || 
                        extension4 == ".gif" || extension4 == ".css" || extension3 == ".js") {
                        
                        out_line = false;
                    }
                }
            }

            // Filtrage des lignes ayant une heure différente de celle considérée
            if (t) {
                string timestamp = line[3];
                size_t pos = timestamp.find(':');
                string logHour = timestamp.substr(pos + 1, 2);
                if (stoi(logHour) != stoi(heure)) {
                    out_line = false;
                }
            } 

            if (out_line) {
                // Récupération des données de création du graphe et du Top10

                // Récupération du referer et de la cible de la requête
                string cible = line[5];
                string referer = line[9];

                // Élément du graphe
                data_log[cible].first[referer]++;  // Incrémentation du nombre de requête ayant les mêmes referer et cible
                                                   // Accéder avec [start] crée la paire si elle n'existe pas et initilise l'int à 0
                data_log[cible].second++;  // Incrémentation du nombre de requêtes avec le même referer
            }
        }

        line.clear();
    }


    if (!data_log.empty()) {
        if (g) {
            Graphe graph(data_log); // Création d'un objet de la classe Graphe à partir du graphe data_log
            graph.toDot(graph_file_name); // Création et remplissage du fichier .dot 
        }

        // Affichage du Top10
        multimap<int, string> top10;  // Tri automatique par ordre croissant des clés par nombre de hits

        for (auto it = data_log.begin(); it != data_log.end(); ++it) {
            int nb_requetes = it->second.second; // Nombre total de requêtes vers la cible

            top10.insert({nb_requetes, it->first});

            // Si plus de 10 éléments, supprime le plus petit
            if (top10.size() > 10) {
                top10.erase(top10.begin());
            }
        }

        // Affichage du Top10 par ordre décroissant
        for (auto it = top10.rbegin(); it != top10.rend(); ++it) {
            cout << it->second << " (" << it->first << " hits)" << endl;
        }
    } else {
        cout << "Aucune ligne n'a été extraite du fichier de log" << endl;
    }

    delete lecture;  // Libère la mémoire allouée dynamiquement
    return 0;
}