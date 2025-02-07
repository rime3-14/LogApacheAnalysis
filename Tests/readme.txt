# Programme de tests automatiques - Mode d'emploi

-------------------------------------------------------------------------------
## test.sh [ répertoire [ fichier.csv ] ]

- `répertoire` indique le répertoire dans lequel se trouvent les fichiers de configuration du test.
- `fichier.csv` indique un fichier dans lequel les résultats des tests seront ajoutés.

En l'absence d'arguments, le script traitera le répertoire courant.

### Fichiers de configuration :
- `run` : fichier texte indiquant la ligne de commande à exécuter (obligatoire).
- `std.in` : fichier texte indiquant une entrée clavier à simuler (facultatif).
- `std.out` : fichier texte indiquant la sortie devant être produite (facultatif / validation*).
- `stderr.out` : fichier texte indiquant la sortie d'erreur devant être produite (facultatif / validation*).
- `description` : fichier texte donnant la description du test (facultatif).
- `returncode` : fichier texte contenant l'entier code retour attendu (facultatif / validation*).
- `*.outfile` : un ou plusieurs fichiers devant être produits par le programme (facultatif / validation*).
  Si le fichier s'appelle `exemple.txt.outfile`, il sera comparé à `exemple.txt`.

*Validation : le script va tester la conformité des résultats attendus et indiquera toute non-conformité détectée.

-------------------------------------------------------------------------------
## mktest.sh

Ce fichier cherche à valider tous les tests contenus dans les répertoires dont le nom commence par `Test`.

-------------------------------------------------------------------------------
## Liste des tests

### Tester la lecture du fichier log :
- **01** : fichier log sans ligne.
- **02** : fichier log inexistant.
- **03** : tester les lignes mal formées (7 erreurs possibles, les lignes sont ignorées).

### Tester `-t` :
- **04** : avec des lignes à extraire.
- **05** : avec des lignes à extraire + ligne avec l'heure d'après/avant.
- **06** : avec toutes les lignes à extraire + une heure avec un seul chiffre.
- **07** : avec aucune ligne à extraire.
- **08** : avec une heure invalide en option.

### Tester `-e` :
- **09** : avec des lignes à supprimer.
- **10** : avec aucune ligne à supprimer.
- **11** : avec toutes les lignes à supprimer.

### Tester `-g` :
- **12** : fichier `.dot` correct produit.
- **13** : option `-g` avec un nom de graphe ne terminant pas par `.dot`.
- **14** : option `-g` sans nom de graphe.

### Tester `-ub` :
- **15** : donner une URL de début différente de celle par défaut.
- **16** : donner une URL de début mal formée.

### Tester le top 10 :
- **17** : fichier log avec moins de 10 cibles différentes.
- **18** : fichier log avec plus de 10 cibles différentes.
- **19** : fichier log avec le même nombre de consultations pour plusieurs cibles.

### Tester la robustesse :
- **20** : donner une option inexistante.
- **21** : donner toutes les options.

-------------------------------------------------------------------------------

Ce framework de tests permet de valider le bon fonctionnement du programme et de détecter d'éventuelles erreurs en automatisant l'exécution et la vérification des résultats.