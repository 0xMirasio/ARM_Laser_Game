BE CHTI Poncetta Thibault et Moënne-Loccoz Célestin

Objectif 2 :

Vérification de la validité du programme :

-ouvrez le dossier "DFT_EN_REEL" puis ouvrez Project.uvprojx avec keil
-ouvrez le fichier "principal.c"
-scrollez pour vous placer dans la zone "IMPORTANT : paramétrage de la trame de signaux"
-vérifiez que la ligne "int trame = 0x33;" est décommentée
-compilez l'ensemble du projet grâce à l'option "Rebuild"
-lancez le débogage
-allez dans l'onglet "view">"Watch window">"Watch 1" pour ouvrir la watch window
-cliquez sur le "+" à gauche de la variable "score" pour afficher la valeur de toutes les cases du tableau
-lancez l'exécution du programme
-atendez une vingtaine de secondes pour être sûr que tous les tirs aient été réalisés
-arrêtez l'exécution du programme, puis vérifiez que les valeurs dans le tableau "score" sont 1, 2, 3, 4, 5, 0
-quittez le debogage
-replacez-vous dans la zone "IMPORTANT : paramétrage de la trame de signaux"
-commentez la ligne "int trame = 0x33;" et décommentez la ligne "int trame = 0x52"
-recompilez grâce à l'option "Rebuild"
-répétez le processus, puis vérifiez, après une vingtaine de secondes d'exécution du programme, que les valeurs dans
 le tableau "score" sont 1, 2, 3, 4, 5, 15