Paramètres:
    - $./analog [options] nomfichier.log  -->  Par défaut
    - -g nomfichier.dot  -->  Cette option permet de produire un fichier au format GraphViz du graphe analysé
    - -e  -->  Cette option permet d’exclure tous les documents qui ont une extension de type image, css ou javascript.
    - -t heure  -->  Cette option permet de ne prendre en compte que les hits qui sont dans le créneau horaire correspondant à l’intervalle [heure, heure+1[.

Génération de statistique:
    - affichage top 10 des documents les plus consultés dans la console

création de fichier dot pour créer un graph avec GraphViz

Lire un fichier de log apache (doivent être réutilisable pour obtenir d'autres informations)

Faire un framework de test
    - dire ce qu'on test (description) --> prendre des parties du fichier log pas l'entièreté
    - le résultat atendu (std.out, stderr.out, *.outfile, Returncode)
    - dire si le résultat obtenu est le même que celui attendu (dans la console)