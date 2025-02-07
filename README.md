# Analyse de Logs Apache

## Description
Ce projet est un outil d'analyse des fichiers de logs Apache. Il permet d'extraire des statistiques utiles comme les 10 pages les plus visitées, et bien plus encore.

## Fonctionnalités
- Lecture de fichier de logs Apache
- Affichage du top 10 des documents les plus consultés dans la console
- Filtrage des logs selon différents critères (date et type de fichier)
- Génération d'un fichier dot pour avoir un graph avec GraphViz montrant les déplacements entre les documents du site

## Manuel d'utilisation
Pour utiliser la commande man analog et accéder au manuel d'utilisation dans la console, il faut réaliser au préalable les opérations suivantes dans le dossier LogApacheAnalysis :
- sudo cp Manuel /usr/local/share/man/man1/analog.1
- sudo mandb

## MAP
Pour activer la MAP, entrez les commandes suivantes dans le dossier bin :
- make cleanall
- make MAP=1