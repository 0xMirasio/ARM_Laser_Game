BE CHTI Poncetta Thibault et Moënne-Loccoz Célestin

Objectif 4 : Projet final

Vérification de la validité du programme :

-ouvrez le dossier "Projet final" puis ouvrez Project.uvprojx avec keil uVision
-compilez l'ensemble du projet grâce à l'option "Rebuild"
-lancez le débogage
-une fenêtre Logic analyser devrait être ouverte, avec le signal TIM3_CCR3. 
(si ce n'est pas le cas  : menu "View > "Analysis Window" >"Logic analyser". Ouvrez ensuite Setup > ajoutez le signal via "New (insert)"
 puis écrire "TIM3_CCR3"
-Fermez la fenêtre de Setup via "Close"
-Faites un clic droit dans la fenêtre Logic Analyser, choisir l'option : "Analog"
-allez dans l'onglet "view">"Watch window">"Watch 1" pour ouvrir la watch window
-entrez l'expression "score", appuyez sur entrée, puis cliquez sur le "+" à gauche de "score" pour afficher les scores des joueurs
-lancez l'exécution du programme, attendez quelques secondes puis mettez en pause
-vous devriez pouvoir voir les scores augmenter dans la watch window, et certaines trames de son se lancer
-si vous lancez l'exécution assez longtemps, sachant que nous avons choisi une trame Ox33
 (uniquement le signal 1 avec une amplitude de 248, et un faible bruit) vous devriez voir les score 1, 2, 3, 4, 5 et 0
 sur la fenêtre logic analyser, vous devriez pouvoir compter 15 trames de son en tout
