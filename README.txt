Ce projet contient plusieurs fichiers essentiels :
- principal.c :  fichier principal du programme en C, fait les appel des fonctions ASM et sauvegarde les résultats.
- calcul_dft.s : fichier ASM contenant les fonctions pour calculer la DFT
- tab-cos-sin.s/tab-signal.s :  fichier ASM contenant les valeurs pour les signaux ou la table cos/sin.

Etapes pour valider l'objectif :

-ouvrez le dossier "DFT-Simulation" puis ouvrez Project.uvprojx avec keil uVision
-compilez l'ensemble du projet grâce à l'option "Rebuild"
-lancez le débogage
-pour observez les différentes DFT en simulation de 0 à 63, placez un point d'arret dans principal.c à la ligne 10 (dft_res = dft(TabSig, i);)
-créer une watch windows (Menu "view" > "watch window" > "watch 1") et entrer l'expresssion "dft_res", les valeurs seront sauvegardées
 dans ce tableau à chaque itération.
-Au bout de 2 exécutions du programme, vous voyez la valeur 0x3FFFCDE5 à l'index 1 du tableau dft_res. Or, si vous ouvrez le fichier
 tab-signal.s, vous voyez à la ligne 7 "M2 0x3FFFCDE5 env 2^30". C'est bien la valeur que nous avons trouvée à l'index 1 du tableau dft_res.
-Enlevez le dernier point d'arrêt, et placez un point d'arrêt sur la ligne 13 (while(1) {})
-Continuez l'execution du programme, et regardez dans la watch window la dernière valeur du tableau dft_res, à l'index 63, vous voyez la valeur 0x3FFFD935
 ceci correspond à la valeur symétrique de celle à l'index k (pas exactement la même valeur, mais très proche en décimal)
  

Si vous voulez utilisez d'autre campagne de test, il suffit de modifier le fichier tab-signal.s et observez le retour des valeurs de la dft
Des fichiers de test sont disponibles dans /test_files
