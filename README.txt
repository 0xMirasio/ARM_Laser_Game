BE CHTI Poncetta Thibault et Moënne-Loccoz Célestin

Etape 1.1 : signal carré OK
Etape 1.2 : passée à cause du travail à distance
Etape 1.3 : non réalisée (facultative)
Etape 2.1 : terminée (fonction test_trigo dans le fichier signal.s appelée dans le fichier principal.c en passant l'index de l'angle voulu (entre 0 et 63)
	    et un pointeur sur la variable dans laquelle le cosinus au carré + le sinus au carré doit être stocké)
Etape 2.2 : en cours, fonctions réalisées et fonctionnelles dans la logique (la nôtre en tout cas) mais renvoyant au final un mauvais résultat.
	    Il y a une fonction dft_re, une fonction dft_im et une fonction dft générale qui appelle les deux autres et fait la somme des carrés.
	    Les fonctions sont probablement pas assez optimisées, certaines mêmes boucles pourraient sûrement être réutilisées par dft_im, mais nous
	    voulions faire fonctionner le programme avant d'optimiser.