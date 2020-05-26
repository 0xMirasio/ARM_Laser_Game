BE CHTI Poncetta Thibault et Moënne-Loccoz Célestin

Objectif 4 : Projet final

Vérification de la validité du programme :

-ouvrez le dossier "Projet final" puis ouvrez Project.uvprojx avec keil uVision
-compilez l'ensemble du projet grâce à l'option "Rebuild"
-lancez le débogage
- une fenêtre Logic analyser devrait être ouverte, avec le signal TIM3_CCR3. 
(si ce n'est pas le cas  : menu "View > "Analysis Window" >"Logic analyser" > Setup > ajoutez le signal via "New (insert)" puis écrire "TIM3_CCR3"
-Fermez la fenêtre de Setup via "Close"
-Faites un clic droit dans la fenêtre Logic Analyser, choisir l'option : "Analog"
-allez dans l'onglet "view">"Watch window">"Watch 1" pour ouvrir la watch window
-cliquez sur le "+" à gauche de la variable "etat" pour afficher les valeurs du son/ position | variable "score" pour afficher les scores
-lancez l'exécution du programme
-atendez quelque secondes que le signal soit envoyé et des sons soit éxecutés.
