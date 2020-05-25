BE CHTI Poncetta Thibault et Moënne-Loccoz Célestin

Etape 1.1 : génération d'un signal carré en ASM
Un signal carré est généré tout les 100ms

-ouvrez le dossier "E1 - Signal carre" puis ouvrez Project.uvprojx avec keil uVision
-compilez l'ensemble du projet grâce à l'option "Rebuild"
-lancez le débogage
- une fenêtre Logic analyser devrait être ouverte, avec le signal à observez. 
(si ce n'est pas le cas  : menu "View > "Logic analyser" > Setup > ajoutez signal :GPIOB_BSRR puis clique droit, choisir l'option : "State"
-lancez l'exécution du programme
-atendez quelque secondes pour que le signal s'éxécute
Vous pourrez observez la valeur du son traité dans le logic analyser.

Etape 2.1 : Calcul de Sin^2 + cos^2 : fonction test_trigo dans le fichier signal.s appelée dans le fichier principal.c en passant l'index de l'angle voulu (entre 0 et 63) et un pointeur sur la variable dans laquelle le cosinus au carré + le sinus au carré doit être stocké)

-ouvrez le dossier "E2 - Calcul trigo" puis ouvrez Project.uvprojx avec keil uVision
-compilez l'ensemble du projet grâce à l'option "Rebuild"
-lancez le débogage
-lancez l'exécution du programme
Vous pourrez observez la valeur du calcul dans la fenêtre Call Stack + Locals.


Des readme sont disponibles dans :

L'objectif 1 : DFT Simulation est dans la branche obj1
L'ojectif 2 : DFT Réel est dans la branche obj2
L'objectif 3 : Génération de son est dans la brancge obj3
L'objectif 4 : Projet Final est dans obj4

