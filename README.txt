Ce projet contient plusieurs fichiers essentiels :

  - principal.c :  fichier principal du programme en C, fait les appel des fonctions ASM et sauvegarde les résultats.
  - calcul_dft.s : fichier ASM contenant les fonctions pour calculer la DFT
  - tab-cos-sin.s/tab-signal.s :  fichier ASM contenant les valeurs pour les signaux ou la table cos/sin.
  
  pour observez les différentes DFT en simulation de 0 à 63, placez un point d'arret dans principal.c à la ligne 11
  Créer une watch windows et rentrer l'expresssion "dft_res", la valeur sera sauvegardé dans le tableau à chaque itération.
  
  
  pour utilisez d'autre campagne de test, il suffit de modifier le fichier tab-signal.s et observez le retour des valeurs de la dft
  
