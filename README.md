# udp-sort-boost

# Intro

Pour répondre à l'exercice 2: C/C++

# Contexte

Le truc marche (au moins chez moi ;)) mais je me sens obligé de m'excuser car
je n'ai pas suivi l'énoncé parfaitement.
Les programmes (clients et serveurs) fonctionnent et font ce qui est demandé
dans l'exercice. Cependant, malgré moults efforts de ma part, je ne suis pas
parvenu à implémenter la chose en utilisant soit libevent2 ou libev.
En effet, je n'ai pas de machine sous Linux à ma disposition maintenant et vu
le peu de temps que j'avais pour moi, j'ai préféré utiliser mon environement de
travail actuel (Windows 11 avec un environment de dev à base de LLVM de ma
conception sous msys2 avec neovim).
J'ai bien vu l'exemple de l'echo server UDP proposé avec libev et j'aurais bien
aimé me baser dessus. Mais je n'ai pas trouvé de port pour windows. Pas de
chance.
Il existe un port de libevent2 pour windows sur lequel j'ai commencé à
travailler, mais c'était vraiment galère et j'ai un peu perdu de temps dessus.
Par conséquent, j'ai décidé de répondre à l'exercice avec une stack plus
moderne en tirant profit de ce que C++(20) et Boost peuvent offrir.

# Composition du projet

C'est un projet CMake. Il y a des extras, c'est un template de projet sur
lequel je travaille et qui du coup expose des choses pas utiles dans le cadre
de cet exercice, mais il fait le job alors pourquoi pas.

# Prérequis

Alors il va falloir en plus de CMake, installer sur la machine quelques librairies:

- Boost
- fmt

La toolchain utilisée est LLVM avec Clang (je suis sur la version 16.0.5).
Ca devrait aussi marcher avec GCC et probablement avec MSVC aussi s'il supporte
les features de C++20 que j'ai utilisé (ranges, concepts)

# Build

Assez classique:

- Créer un répertoire `build` à la racine du projet.
- toujours à la racine du projet lancer la commande : `cmake -G <générateur> -S
  . -B build/` avec le générateur de votre choix (je recommande Ninja)
- Si ça passe lancer la commande (cette fois dans le repertoire `build`) `cmake --build .`
- Aller dans le répertoire `build/src`
- lancer UdpSortServer en arrière plan
- lancer UdpSortClient et lire l'affichage qu'il produit
- vous pouvez lancer UdpSortClient autant de fois que vous voulez pendant que
  UdpSortServer tourne.
