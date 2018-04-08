# Projet logiciel du semestre 4

Membres du groupe :

	* KAJAK Rémi
	* KINZI Erick
	* MAROUF Taous
	* NOUVELIERE Benjamin

Programme développé : Picross
Description : 

Le Picross est un jeu de réflexion. Une grille de taille fixe contient N cases vides. Selon les nombres indiqués sur les côtés gauche et haut), le joueur doit cocher les bnnes cases afin de compléter correctement cette grille.
Le remplissage des cases en fonction des nombres dépend de deux règles :

	* Un nombre indique un groupe de cases remplies et adjacentes sur une ligne ou une colonne. Il ne peut pas y en avoir plus ou moins que ce nombre.
	* Chaque nombre correspond à un groupe de cases, aussi bien horizontalement que verticalement. Chaque groupe est séparé par un espace d'au moins une case vide.

Généralement, un dessin (ou un motif, du moins) se forme au fur et mesure que la grille est complétée. Cela aide aussi le joueur à déterminer la forme finale ainsi que le placement des cases restantes.

# Instructions pour les démonstrations

Vous trouverez plusieurs exécutables présents à la racine du répertoire. Les fichiers "demo\_cases" et "demo\_generation\_v1" sont des tests unitaires des fichiers éponymes. Pour les re-générer, exécutez les makefiles "makefile\_Case" et "makefile\_gen" ; attention avec ce dernier : comme "generation.c" possède deux versions différentes pour la génération de données, veillez à (dé)commenter les bonnes sections dans le main du fichier.

La commande à utiliser est "make -f <makefile\_nom>".

L'exécutable "demo\_terminal" permet de jouer à la version en mode console du Picross. Pour re-générer l'exécutable, appliquez la commande cité précédemment au fichier "makefile\_terminal".

Pour générer l'exécutable de l'interface graphique, voici les commandes à entrer dans le terminal :

- gcc picross\_sdl.c sdl2-config --cflags --libs -lSDL2\_ttf
- ./a.out

# Explications du Picross en mode terminal

Au lancement du jeu, la fenêtre du terminal est nettoyée et la partie se lance automatiquement. Dans cette version, les cases peuvent prendre trois états :

* 0 -> Blanche	=> Case vide
* 1 -> Noire	=> Case cochée
* 2 -> Croix	=> Case assurément vide (pour permettre les suppositions)

Vous devez résoudre les six puzzles proposés dans cette première version (sans solveur) :

* À chaque tour, le jeu vous demande deux coordonnées x et y, respectivement pour une ligne et une colonne ;
  => En cas d'erreur de saisie pour l'une ou pour l'autre, le programme bloquera le tour jusqu'à ce qu'elles soient correctes.

* Une fois vos choix effectués, vous pouvez valider votre grille avec les coordonnées -1 et -1 ;

* Le programme vous renverra soit un message de félicitation pour avoir résolu le puzzle, soit un message d'erreur avec le nombre de mauvaises cases cochées ;
  => Dans les deux cas, vous pouvez choisir de quitter la partie (et donc le programme) ou de continuer à jouer.

* Le jeu se termine automatiquement si vous résolvez tous les puzzles !
