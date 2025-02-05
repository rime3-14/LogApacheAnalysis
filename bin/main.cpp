// includes systèmes
#include <iostream>
using namespace std;

// includes personnel
#include "Graphe.h"
#include "Lecture.h"

// lire le log
#include <vector>
#include <string>

// stocker le compte des allers d'un referer à une cible
#include <unordered_map>
#include <utility>

// top 10
#include <map>

// autre
#include <cstring>


int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Utilisation: ./analog [options] nomfichier.log" << endl;
        return 1;
    }

    // flags
    bool g = false;
    bool e = false;
    bool t = false;

    // variables
    string log_name = argv[argc-1];
    string graph_file_name;
    string debut_url = "http://intranet-if.insa-lyon.fr";
    string heure;

    // graph pour créer le graphe et le top 10
    graphe data_log;

    // vérifie les options
    for (int i = 1; i < argc - 1; i++) {
       if (strcmp(argv[i], "-g") == 0) {
            graph_file_name = argv[++i];
            g = true;

        } else if (strcmp(argv[i], "-e") == 0) {
            e = true;
            
        } else if (strcmp(argv[i], "-t") == 0) {
            heure = argv[++i];
            t = true;
            
        } else if (strcmp(argv[i], "-ub") == 0) {
            debut_url = argv[++i];
        }
    }
    
    // lit les lignes du fichier log une par une tant qu'il n'y a pas d'erreur ou de eof
    Lecture lecture(log_name);

    vector<string> line;
    while (lecture.Readfile(line)) {
        bool out_line = true;  // variable pour afficher ou nom la ligne

        // enlève le début de l'url correspondant au site que l'on parcours sur les urls qui l'ont
        size_t debut_url_start = line[9].find(debut_url);
        if (debut_url_start != string::npos) {
            line[9].erase(debut_url_start, debut_url.size());
        }

        // filtre les lignes ayant pour cible un fichier image, css ou javascript
        if (e) {
            string url = line[5];
            string extension4 = url.substr(url.size() - 4);
            string extension3 = url.substr(url.size() - 3);
            if (extension4 == ".jpg" || extension4 == ".ico" || extension4 == ".png" || 
                extension4 == ".gif" || extension4 == ".css" || extension3 == ".js") {  // trouver d'autre si nécessaire
                
                out_line = false;
            }
        }

        // filtre les lignes ayant une heure différente de celle donnée
        if (t) {
            string timestamp = line[3];
            size_t pos = timestamp.find(':');
            string logHour = timestamp.substr(pos + 1, 2);
            if (logHour != heure) {
                out_line = false;
            }
        } 

        if (out_line) {
            // récupère les données pour créer le graph et donner le top 10
            // referer et cible de la requête
            string cible = line[5];
            string referer = line[9];

            // élément du graph
            data_log[cible].first[referer]++;  // incrémente le nombre de requête avec le même referer et cible
                                            // acceder avec [start] créé la pair si elle n'existe pas et initilise l'int à 0
            data_log[cible].second++;  //incrémente le nombre de requête avec le même referer


            // affiche la ligne
            cout << line[0] << " " << line[1] << " " << line[2] << " " << line[3] << " \"" << line[4] << " " << line[5] << " " << line[6] << "\" " << line[7] << "" << line[8] << " \"" << line[9] << "\" \"" << line[10] << "\"" << endl;

            line.clear();
        }
    }

    if (g) {
        Graphe graph(data_log);
        graph.toDot(graph_file_name);
    }

    // Affichage du top 10
    multimap<int, string> top10;  // Trie automatiquement par ordre croissant des clés par nombre de requêtes

    for (auto it = data_log.begin(); it != data_log.end(); ++it) {
        int nb_requetes = it->second.second; // Nombre total de requêtes vers la cible

        top10.insert({nb_requetes, it->first});

        // Si plus de 10 éléments, supprime le plus petit
        if (top10.size() > 10) {
            top10.erase(top10.begin());
        }
    }

    // Affichage du top 10 en ordre décroissant
    for (auto it = top10.rbegin(); it != top10.rend(); ++it) {
        cout << it->second << " (" << it->first << " hits)" << endl;
    }


    return 0;
}