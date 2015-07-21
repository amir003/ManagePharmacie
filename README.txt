Programme version 1.0     02/05/2014
-----------------------------------------------------------------------------------------------------------------------
Comment lancer le programme ?
Utilisation du Makefile : -Commandes-

- make all : pour créer l'exécutable du Programme
- make clean : pour supprimer les fichiers temporaires
- make mrproper : pour préparer une reconstruction complète

 
Depuis le terminal, entrez le nom de l’exécutable suivi du nom de fichier à traiter ainsi : « ./Programme liste.txt »

------------------------------------------------------------------------------------------------------------------------

Remarques générales pour l'utilisation de ce programme:



- fichier liste.txt contenant les noms de médicaments doit être dans le même répertoire que le programme. 
- Le programme une fois lancé affiche un menu et il faut choisir le un élément du menu auquel un nombre est associé.
- L'interaction avec la base de données contenant les médicaments et leur effets secondaires se fait par le menu.
- Au cas ou un mauvais numéro est entré le programme envoie un message d'erreur et permet de sélectionner de nouveau un numéro.
- Pour quitter le programme: touche 9 OU Ctrl^C
- Marche avec système d'exploitation linux et mac, windows 
- compilateur 
------------------------------------------------------------------------------------------------------------------------

Problèmes possibles


- Lors de l’appel de l’option 7, un bug subsiste pour faire une recherche de médicament randomisée.







