# Jeu du Pendu

Ce dépôt contient le code source d'un jeu du Pendu écrit en C.

## Prérequis et Configuration

1. **Organisation des fichiers** : placez tous les fichiers dans un même dossier.
2. **Configuration du dictionnaire** : dans le fichier `dico.c`, renseignez le chemin (absolu ou relatif) vers le fichier `dico.txt`.

   ```c
   int piocherMot(char *motPioche)
   {
       const char chemin[] = "Chemin vers le fichier dico.txt";
   // ...


3. **Configuration des assets textuels** : Dans le fichier `pendu.c`, renseignez le chemin vers `intro.txt` et `potence.txt`.

```c
void intro()
{
    FILE *fichier = NULL;
    char chaine[TAILLE_MAX/10] = {0};
    const char chemin[] = "Chemin vers le fichier intro.txt";
// ...

void potence()
{
    FILE* fichier = NULL;
    char chaine[TAILLE_MAX/10] = {0};
    const char chemin[] = "Chemin vers le fichier potence.txt";
// ...

```



## Compilation

Pour compiler le jeu et générer l'exécutable, ouvrez votre terminal dans le dossier du projet et utilisez la commande suivante :

```bash
gcc -o pendu pendu.c dico.c

```

## Exécution

Une fois la compilation terminée, l'exécutable `pendu` doit se trouver dans le même dossier que les autres fichiers source. Pour lancer le jeu, exécutez la commande :

```bash
./pendu

```

**Exemple d'affichage en cours de partie :**

```text
FEUILLETISE-AIS

Il vous reste 4 essais.

Saisir une lettre sauf o, n, g, m :

```

