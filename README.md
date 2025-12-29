## Projet Option Pricer
### Description

Ce projet implémente un moteur de pricing d’options financières en C++.
Il permet de calculer le prix de différents types d’options à l’aide de méthodes analytiques et numériques.

### Options supportées

- Option européenne
  - Modèle de Black–Scholes
  - Méthode de Monte Carlo
- Option asiatique

- Option barrière
- Option digitale

Les paramètres des options (maturité, volatilité, taux, etc.) sont définis dans le fichier main.cpp.

Structure du projet
```
.
├── CMakeLists.txt        # Configuration CMake
├── README.md             # Documentation du projet
├── include/              # Fichiers d'en-tête (.hpp)
├── src/                  # Implémentations (.cpp)
├── main.cpp              # Point d’entrée du programme
└── build/                # Dossier de compilation
```

- include/ contient les définitions des options et des pricers
- src/ contient les implémentations des modèles de pricing
- main.cpp est le point d’entrée du programme
- build/ contient tous les fichiers générés par CMake

### Prérequis

Compilateur C++ compatible C++17 \
CMake version ≥ 3.x \
Système Linux, macOS ou Windows.

### Compilation

Le projet utilise CMake pour la génération des fichiers de build.
Étapes de compilation

Depuis la racine du projet :

```
cd build 
cmake .. 
make     
```

Ces commandes :
1. Génèrent les fichiers de configuration adaptés à votre système
2. Compilent le projet
3. Créent un exécutable nommé option_pricer

### Exécution

Une fois la compilation terminée, exécutez le programme avec :
./option_pricer

Le programme affichera le prix des différentes options calculé selon les paramètres définis dans main.cpp.

### Personnalisation
Pour tester différents scénarios : 
1. Modifiez les paramètres des options dans main.cpp 
2. Recompilez le projet si nécessaire 
3. Relancez l’exécutable