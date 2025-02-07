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
- faire le manuel d'utilisation
- vérifier la cohérence avec le guide de style

à tester (faire des mini-fichier de log) :
tester la lecture du fichier log :
- 01 : fichier log sans ligne
- 02 : fichier log inexistant
- 03 : tester les lignes mal formées

tester -t
- 04 : avec des lignes à extraire
- 05 : avec des lignes à extraire + ligne avec l'heure d'après/avant
- 06 : avec toutes les lignes à extraire + une heure avec un seul digit
- 07 : avec aucune lignes à extraire
- 08 : avec une heure invalide en option

tester -e
- 09 : avec des lignes à supprimer
- 10 : avec aucune lignes à supprimer
- 11 : avec toutes les lignes à supprimer

tester -g
- 12 : fichier .dot correct produit 
- 13 : g avec un nom de graphe ne terminant pas par .dot 
- 14 : g sans nom de graphe 

tester -ub
- 15 : donner un url de début différent de celui par défaut 
- 16 : donner une url de début mal formée

tester le top 10
- 17 : fichier log avec - de 10 cibles différentes
- 18 : ficher log avec + de 10 cibles différentes
- 19 : fichier log avec le même nombre de consultations

tester la robustesse
- 20 : donner une option inexistante
- 21 : donner toutes les options
