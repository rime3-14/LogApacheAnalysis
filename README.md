### Paramètres:
- $./analog [options] nomfichier.log  -->  Par défaut
- -g nomfichier.dot  -->  Cette option permet de produire un fichier au format GraphViz du graphe analysé
- -e  -->  Cette option permet d’exclure tous les documents qui ont une extension de type image, css ou javascript.
- -t heure  -->  Cette option permet de ne prendre en compte que les hits qui sont dans le créneau horaire correspondant à l’intervalle [heure, heure+1[.
- ub debutUrl  -->  Cette option permet de changer l'url du site dans lequel les passages sont fait. Par défaut à http://intranet-if.insa-lyon.fr

### Génération de statistique:
- affichage top 10 des documents les plus consultés dans la console

### création de fichier dot pour créer un graph avec GraphViz

### Lire un fichier de log apache (doivent être réutilisable pour obtenir d'autres informations)

### Faire un framework de test
- dire ce qu'on test (description) --> prendre des parties du fichier log pas l'entièreté
- le résultat atendu (std.out, stderr.out, *.outfile, Returncode)
- dire si le résultat obtenu est le même que celui attendu (dans la console)

todo :
- deep copy du graphe?
- vérifier les lignes mal formée dans le readFile


à tester (faire des mini-fichier de log) :
tester la lecture du fichier log :
- fichier log sans ligne
- fichier log inexistant
- tester les lignes mal formées

tester -t
- avec des lignes à extraire
- avec des lignes à extraire + ligne avec l'heure d'après/avant
- avec toutes les lignes à extraire
- avec aucune lignes à extraire
- avec une heure invalide en option

tester -e
- avec des lignes à supprimer
- avec aucune lignes à supprimer
- avec toutes les lignes à supprimer

tester -g
- fichier .dot correct produit

tester -ub
- donner un url de début différent de celui par défaut
- donner une url de début mal formée

tester le top 10
- fichier log avec - de 10 lignes
- ficher log avec + de 10 lignes
- fichier log avec le même nombre de consultations

tester la robustesse
- donner une option inexistante
- donner toutes les options
