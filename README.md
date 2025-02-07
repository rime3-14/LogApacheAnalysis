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
- faire en sorte que lorsque le fichier n'existe pas, l'errorcode du main est 1

TODO de lilas:
- Tester si datalog est vide : s'il l'est, message approprié ("aucune ligne extraite"), sinon, traitements ! (tests 1, 7 et 11)
- Modifier main pour que -t 7 soit transformé en -t 07, ou noter que ça marche exclusivement avec 2 digits
- En profiter pour traiter les lettres qui font fail les stoi ?
- Demander à Rime/Rida de faire le manuel d'utilisation (+ de vérifier la cohérence avec le guide de style ?)

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
