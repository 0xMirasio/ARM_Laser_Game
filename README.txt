
BE CHTI Poncetta Thibault et Moënne-Loccoz Célestin

Objectif 3 : Génération de son

Vérification de la validité du programme :

-ouvrez le dossier "Génération du son" puis ouvrez Project.uvprojx avec keil uVision
-compilez l'ensemble du projet grâce à l'option "Rebuild"
-lancez le débogage
- une fenêtre Logic analyser devrait être ouverte, avec le signal TIM3_CCR3. 
(si ce n'est pas le cas  : menu "View > "Logic analyser" > Setup > ajoutez signal :TIM3_CCR3 puis clique droit, choisir l'option : "State"
-allez dans l'onglet "view">"Watch window">"Watch 1" pour ouvrir la watch window
-cliquez sur le "+" à gauche de la variable "etat" pour afficher les valeurs du son/ position ...
-lancez l'exécution du programme
-atendez quelque secondes pour que le son s'éxécute
Vous pourrez observez la valeur du son traité dans le logic analyser.
