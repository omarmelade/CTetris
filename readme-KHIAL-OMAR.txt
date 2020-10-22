### KHIAL OMAR TP2
### INFO504

###### TETRIS SIMPLIFIE ######

0. Après avoir créé mon .h, j'y ai defini toutes mes structures.
	J'ai également defini mes procedure et fonctions.

1. initialiseGrille fonctionne et met tout les elements du tableau a ' '.

2. lireCase, lit la case via les coordonnées passée en paramètre.

3. caseEstVide, renvoie 1 si la case spécifié est vide et 0 si elle est occupée.

4. printseparator et printcarriage sont des procedure qui affiche une ligne de tiret
	et un retour chariot, cela a été fait pour rendre plus lisible l'affichage.
	
5. afficheBasGrille, affiche le bas de ma grille donc, les pipes de fin 
	et les chiffres des unités et des dixaines.
	
6. afficheGrille, affiche toute la grille avec les chiffre et les pipes.

7. affichePiece affiche une pièce dans le bon ordre avec la fleche 
	qui indique la colonne de gauche.
	
8. generePiece "genere" des pieces

9. ecrireCase ecrit un caractère dans une case de la grille et affiche un erreur si cela n'est pas possible.

10.1 premiereLineVideColonne renvoie la premiere case vide de la colonne passée en parametre
	cela me permet de simplifié le code de hauteurPlat

11. hauteurPlat fonctionne dans certains cas, et renvoie la hauteur max pour la position de la piece.
	j'ai un soucis dans cette fonction, je n'arrive pas a regler le soucis des espaces dans une colonne
	si il y'a de la place mais pas assez pour la piece il vas separer la piece en morceaux.

12. hauteurExacte n'as pas été menée a son terme car je n'étais pas satisfait de hauteurPlat.

13. supprimeLigne ne fonctionne pas et je l'ai ecrite en y pensant mais sans la tester.

14. ecrirePiece ne verifie pas si la piece a de la place pour être entiere, ce qui cause le soucis decris dans 
	la section 11, la piece se separe en morceaux.


15. main, lance le jeu de manière correct, je n'ai pas enlevé tout mes tests, j'ai essayé d'y integré des verifications
	conscient qu'elle n'y avait pas leurs place mais voulant debugger au maximum mon code.

PS : J'ai manqué de temps pour faire ce TP, cumulant les cours et un job étudiant je vous fait part,
	de ma frustration quand j'ai du rendre ce TP sans avoir pu m'y mettre a fond. Je suis conscient qu'il est compliqué
	de prendre ma situation en compte mais maintenant vous en avez connaissance.
