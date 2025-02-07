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
- **09** : avec une heure non numérique en option.

### Tester `-e` :
- **10** : avec des lignes à ignorer.
- **11** : avec aucune ligne à ignorer.
- **12** : avec toutes les lignes à ignorer.

### Tester `-g` :
- **13** : fichier `.dot` correct produit.
- **14** : option `-g` avec un nom de graphe ne terminant pas par `.dot`.
- **15** : option `-g` sans nom de graphe + autre option après.
- **16** : option `-g` sans nom de graphe.

### Tester `-ub` :
- **17** : donner une URL de début différente de celle par défaut.
- **18** : donner une URL de début mal formée.

### Tester le top 10 :
- **19** : fichier log avec moins de 10 cibles différentes.
- **20** : fichier log avec plus de 10 cibles différentes.
- **21** : fichier log avec le même nombre de consultations pour plusieurs cibles.

### Tester la robustesse :
- **22** : donner une option inexistante.
- **23** : donner toutes les options.

-------------------------------------------------------------------------------

Ce framework de tests permet de valider le bon fonctionnement du programme et de détecter d'éventuelles erreurs en automatisant l'exécution et la vérification des résultats.