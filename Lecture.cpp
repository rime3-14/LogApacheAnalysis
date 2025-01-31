#include "Lecture.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

bool Lecture::Readfile(const string &fileName, vector<string> &mots) {
    std::ifstream file(fileName);  // Ouvrir le fichier
    if (!file) {
        cerr << "Erreur d'ouverture du fichier !" << endl;
        return false;
    }

    int i = 0;
    char c;
    string ligne;
    getline(file, ligne);
    while (i < 11) {
        string mot;
        for (size_t j = 0; j < ligne.size(); ++j) {
            c = ligne[j];

            // Cas spécial : Si on est à l'indice 3, on ajoute tout entre "[" et "]"
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

            // Cas spécial : Si on est à l'indice 10, on ajoute tout entre '"' et '"'
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

    file.close();  // Fermer le fichier
    return true;  // Retourner vrai si tout s'est bien passé
}