// includes systèmes
#include <iostream>
using namespace std;

// includes personnel
#include "Graphe.h"

// lire le log
#include <vector>
#include <string>

// stocker le compte des allers d'un referer à une cible
#include <unordered_map>
#include <utility>

// top 10
#include <set>

// autre
#include <cstring>

// Fonction temporaire pour tester sans avoir la classe de lecture de log faite
bool readFile(const string &fileName, vector<string> &line) {
    line = {"192.168.0.0", "-", "-", "[08/Sep/2012:11:16:02 +0200]", "GET", "/temps/4IF16.html", "HTTP/1.1", "200", "12106", "http://intranet-if.insa-lyon.fr/temps/4IF15.html", "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:14.0) Gecko/20100101 Firefox/14.0.1"};
    return true;
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Utilisation: ./analog [options] nomfichier.log" << endl;
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
    vector<string> line;
    while (readFile(log_name, line)) {
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

        if (g) {
            graphe graph;

            // referer et cible de la requête
            string referer = line[5];
            string cible = line[9];

            // élément du graph
            graph[cible].first[referer]++;  // incrémente le nombre de requête avec le même referer et cible
                                            // acceder avec [start] créé la pair si elle n'existe pas et initilise l'int à 0
            graph[cible].second++;  //incrémente le nombre de requête avec le même referer
        }   

        // affiche la ligne
        if (out_line) {
            cout << line[0] << " " << line[1] << " " << line[2] << " " << line[3] << " \"" << line[4] << " " << line[5] << " " << line[6] << "\" " << line[7] << "" << line[8] << " \"" << line[9] << "\" \"" << line[10] << "\"" << endl;
            return 0;
        }

    }

    return 0;
}