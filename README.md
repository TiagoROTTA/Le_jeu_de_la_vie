Ce projet implémente une version interactive et graphique du **Jeu de la vie** de Conway, avec des fonctionnalités supplémentaires comme les cellules obstacles et la gestion des itérations.

## Fonctionnalités
- **Deux modes d'affichage** :
  - Mode terminal (texte uniquement).
  - Mode graphique avec une interface utilisateur basée sur SFML.
- **Deux options d'initialisation** :
  - Lecture depuis un fichier source.
  - Configuration manuelle des cellules vivantes.
- **Gestion des obstacles** : Les obstacles restent immuables et ne suivent pas les règles classiques du jeu.
- **Toroïdalité** : Les bords de la grille se connectent (les cellules voisines sont calculées en boucle).
- Sauvegarde des états dans des fichiers lors de l'utilisation du mode terminal.

---

## Prérequis

1. **Compilateur C++** prenant en charge C++11 ou une version ultérieure.
2. **Bibliothèques externes** :
   - [SFML](https://www.sfml-dev.org/) pour l'interface graphique.
3. Un environnement compatible avec les commandes système (Linux, macOS, ou Windows avec adaptations).

---

## Installation

1. Clonez le projet :
   ```bash
   git clone <lien-du-repo>
   cd <nom-du-repo>
   ```
2. Installez SFML (si non déjà installé) :
   - Sur Linux (exemple pour Ubuntu) :
     ```bash
     sudo apt-get install libsfml-dev
     ```
   - Pour Windows ou macOS, suivez les instructions sur le [site officiel de SFML](https://www.sfml-dev.org/download.php).
3. Compilez le projet avec `g++` :
   ```bash
   g++ -std=c++11 -o Game main.cpp cell.cpp grid.cpp game.cpp GUI.cpp -lsfml-graphics -lsfml-window -lsfml-system
   ```

---

## Utilisation

1. Lancez le programme :
   ```bash
   ./Game
   ```
2. Suivez les instructions dans le terminal :
   - **Choix du mode d'affichage** : terminal ou interface graphique.
   - **Initialisation de la grille** :
     - Lecture depuis un fichier source.
     - Configuration manuelle en entrant les coordonnées des cellules vivantes.
3. Si vous utilisez le **mode graphique**, utilisez les raccourcis suivants :
   - `Espace` : Pause/Reprise.
   - `C` : Réinitialisation de la grille.
   - `Flèches Haut/Bas` : Modifier la vitesse.

---

## Structure du Projet

### Fichiers principaux
- **`main.cpp`** : Point d'entrée du programme.
- **`cell.hpp/cell.cpp`** : Classe `Cell` définissant les propriétés de chaque cellule (vivante ou obstacle).
- **`grid.hpp/grid.cpp`** : Classe `Grid` pour la gestion de la grille et des règles du jeu.
- **`game.hpp/game.cpp`** : Classe `Game` orchestrant les différentes étapes (initialisation, boucle principale).
- **`GUI.hpp/GUI.cpp`** : Interface graphique basée sur SFML.

---

## Exemple de fichier source pour initialisation

Pour utiliser un fichier source, le format doit être :
1. Première ligne : dimensions de la grille (Y X).
2. Les lignes suivantes représentent l'état des cellules :
   - `0` : Cellule morte.
   - `1` : Cellule vivante.
   - `2` : Cellule obstacle.

Exemple :
```
10 10
0 0 0 0 0 0 0 0 0 0
0 1 1 0 0 0 1 1 0 0
0 1 2 0 0 0 2 1 0 0
...
```
Voici une section à ajouter au **README** pour expliquer l'utilisation du script `genMatrix.sh` et comment personnaliser la grille générée :

---

## Génération de grilles avec `genMatrix.sh`

### Description
Le script `genMatrix.sh` permet de générer facilement un fichier texte contenant une grille de cellules pour le projet. La grille générée est initialisée avec des cellules mortes (`0`) et peut être modifiée pour inclure des cellules vivantes ou bloquées.

---

### Utilisation

1. Rendez le script exécutable :
   ```bash
   chmod +x genMatrix.sh
   ```

2. Lancez le script avec deux arguments : le nombre de lignes et de colonnes de la grille.
   Exemple pour une grille de 10x10 :
   ```bash
   ./genMatrix.sh 10 10
   ```

3. Le fichier généré sera nommé dynamiquement en fonction de la taille de la grille (par exemple, `grille_10x10.txt`).

4. Contenu d'une grille par défaut (exemple pour une grille 3x3) :
   ```
   # Grille de taille 3x3
   3 3
   0 0 0 
   0 0 0 
   0 0 0
   ```

---

### Modification manuelle de la grille
Une fois le fichier généré, vous pouvez modifier les cellules directement dans le fichier texte pour inclure des états spécifiques :
- `0` : Cellule morte (par défaut)
- `1` : Cellule vivante
- `2` : Cellule bloquée (ou tout autre état personnalisé selon votre projet)

Exemple d'une grille 3x3 modifiée :
```
# Grille de taille 3x3
3 3
0 1 0 
2 0 0 
0 0 1
```
---

## À Propos

Ce projet est une simulation du **Jeu de la Vie** intégrant une interface utilisateur pour une meilleure visualisation et manipulation des grilles.  
Inspiré par les travaux de John Horton Conway.
