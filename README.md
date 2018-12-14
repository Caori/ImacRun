# ImacRun
Projet SI/C++ IMAC

Recréer un dossier ImacRun tout neuf de projet OpenGL sur sa machine (voir TP2 : http://igm.univ-mlv.fr/~biri/Enseignement/IMAC2/opengl-TPs/opengl.php?section=teaching&teaching=opengl&teaching_section=tds&td=td1#item1 ). Créer ImacRun-build à côté, faire cmake et make.

Prenez tout ce qu'il y a dans le dossier ImacRun et déplacez-le ailleurs pour l'instant.

Se placer dans le dossier maintenant vide ImacRun, faire :
git init
git remote add origin https://github.com/Caori/ImacRun
git pull origin master

J'ai mis un .gitignore pour les fichiers cmake et makefile pour que chacun garde la config spécifique à sa machine, quand vous ferez pull vous récupererez tout sauf ces fichiers (normalement).
Reprenez tous les fichiers makefile et cmake du projet que vous aviez déplacé avant et remettez-les aux bons endroits dans ImacRun (ou remplacez ceux existants si pour raison inconnue ils ont été pull sur votre machine).

Refaite un cmake et make et tester le code du dossier TP5.

Si tout marche bien vous n'aurez plus qu'à faire des push et pull à partir de maintenant et vous garderez toujours les fichiers cmake adaptés à votre machine.

UTILE : 

REGLES RELATIVES AU GIT
- ne jamais bosser diretement sur la branche master !
- se créer une branche personnelle avec git branch avant de commencer à modifier le code
- nommer sa branche de façon pertinente (classe qu'on est en train de créer, fonctionnalité qu'on développe, etc...)
- bien faire attention à pusher sur sa branche (git push origin nom_branche, pas master)
- à chaque itération (après le merge d'une branche personnelle avec la branche master, dupliquer le dossier contenant tout le projet. Appeler cette copie Projet_local par exemple. Supprimer tout ce qu'il y a dans ImacRun-build et les fichiers git. Refaire cmake. C'est dans ce dossier que vous ferez vos test et travaillerez, l'autre ne sert qu'à faire des push et pull avec git. Une fois que tout marche bien (test valgrind aussi), vous pourrez remplacer les fichiers du dossier Projet (git) par ceux que vous avez modifié dans Projet_local (ne pas oublier de re-tester le code dans Projet avant de push, on ne sait jamais).

Ne pas hésiter à me demander de l'aide sur ce sujet, j'ai l'habitude ^^


