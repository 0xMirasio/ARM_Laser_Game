BE CHTI Poncetta Thibault et Moënne-Loccoz Célestin

Objectif 3 : Génération de son

Vérification de la validité du programme :

-ouvrez le dossier "Génération du son" puis ouvrez Project.uvprojx avec keil uVision
-compilez l'ensemble du projet grâce à l'option "Rebuild"
-lancez le débogage
- une fenêtre Logic analyser devrait être ouverte, avec le signal TIM3_CCR3. 
(si ce n'est pas le cas  : menu "View > "Analysis Window" >"Logic analyser" > Setup > ajoutez le signal via "New (insert)" puis écrire "TIM3_CCR3"
-Fermez la fenêtre de Setup via "Close"
-Faites un clic droit dans la fenêtre Logic Analyser, choisir l'option : "Analog"
-allez dans l'onglet "view">"Watch window">"Watch 1" pour ouvrir la watch window
-cliquez sur le "+" à gauche de la variable "etat" pour afficher les valeurs du son/ position ...
-lancez l'exécution du programme
-atendez quelque secondes pour que le son s'éxécute
Afin d'ajustez au mieux la fenêtre, vous pourrez par exemple vous placez entre 0s et 0.3s dans le logic analyser afin d'observez le son dans sa totalité. (dépend des sons)
