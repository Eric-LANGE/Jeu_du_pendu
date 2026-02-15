/*

Jeu du Pendu.

main.c
------

Fonctions principales de gestion du jeu.

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include "dico.h"
#define TAILLE_MAX 1000


int gagne(char lettresTrue[], long tailleMot);

int rechercheLettre(char lettresTrue[],long tailleMot, int lettre, char motSecret[]);

void potence();

void delay(int milli_seconds);

void intro();

int lire(char *chaine, int longueur);

void viderBuffer();

//

int main() 

{

char saisie[3] = {0}; 
char motSecret[100] = {0}; // tableau de stockage du mot secret
char lettresFalse[100] = {0};
char *lettresTrue = NULL; // tableau des lettres trouvées
int coupsRestants = 8;  
long tailleMot = 0; // longueur du mot secret
int i = 0; 


system("clear");

intro();

printf("\a");

fflush(stdout);

delay(1200);




if (piocherMot(motSecret)) { // paramètre : un pointeur sur la zone en mémoire où sera écrit le mot secret
	
	exit(1);}

tailleMot = strlen(motSecret);

lettresTrue = malloc(tailleMot * sizeof(char)); // construction du tableau des lettres trouvées

if (lettresTrue == NULL) {

	exit(1);}
	

for(i = 0 ; i < tailleMot ; i++)
{
lettresTrue[i] = '-';
}


rechercheLettre(lettresTrue, tailleMot, motSecret[0], motSecret);


do

{
	
system("clear");

printf("\n");

for(i = 0 ; i < tailleMot ; i++)
{
printf("%c ",lettresTrue[i]);
}

printf("\n");



if (*lettresFalse)
{
	
	
	if (coupsRestants > 1) {
		printf("\nIl vous reste %d essais.\n\nSaisir une lettre sauf ", coupsRestants);}
	else {
		printf("\nIl vous reste 1 essai.\n\nSaisir une lettre sauf ");}
	
	for(i = 0 ; i < strlen(lettresFalse) ; i++)
		{
			printf("%c",tolower(lettresFalse[i]));
			if (i < strlen(lettresFalse)-1) {
			printf(", ");}
		}
		
		printf(" : ");
}
else
{

	
	if (coupsRestants > 1) {
								printf("\nIl vous reste %d essais.\n\nSaisir une lettre : ", coupsRestants);}
								else {
								printf("\nIl vous reste 1 essai.\n\nSaisir une lettre : ");}

}


lire(saisie, 3);


if (isalpha(*saisie) && (!rechercheLettre(lettresTrue, tailleMot, *saisie, motSecret)) && (strchr(lettresFalse, *saisie) == NULL))
{
	strcat(lettresFalse, saisie);
	coupsRestants--;
} 

} while (!isalpha(*saisie) || coupsRestants > 0 && !gagne(lettresTrue, tailleMot));


system("clear");


if (gagne(lettresTrue, tailleMot))
{
printf("\033[31m");
printf("BRAVO !!!");
printf("\n\n");
printf("Le mot secret etait : %s\n\n", motSecret);
} 
else
{
potence();
printf("\033[31m");
printf("\a");
printf("\a");
fflush(stdout);
delay(1500);
printf("PERDU !!!");
printf("\n\n");
printf("Le mot secret etait : %s\n\n", motSecret);

}

printf("\n");

free(lettresTrue);

return 0;

}


int gagne(char lettresTrue[], long tailleMot)
{
int i = 0;
int joueurGagne = 1;


for(i = 0 ; i < tailleMot ; i++)
{
if (lettresTrue[i] == '-') // s'il existe une lettre non decouverte
joueurGagne = 0;
}

return joueurGagne;

}


int rechercheLettre(char lettresTrue[],long tailleMot, int lettre, char motSecret[])
{
int i = 0;
int bonneLettre = 0;

for(i = 0 ; i < tailleMot ; i++)
{

if (lettre == motSecret[i]) // Si la lettre y est
{
bonneLettre = 1;
lettresTrue[i] = motSecret[i];
}
}

return bonneLettre;
}
  

int lire(char *chaine, int longueur)
{
char *positionEntree = NULL;
 
if (fgets(chaine, longueur, stdin) != NULL)
{
positionEntree = strchr(chaine, '\n');
if (positionEntree != NULL)
{
*positionEntree = '\0';
*chaine = toupper(*chaine); 
}
else
{
viderBuffer();
}
return 0;
}
else
{
viderBuffer();
return 1;
}
}


void viderBuffer()
{
int c = 0;
while (c != '\n' && c != EOF)
   {
c = getchar();
}
}


void intro()
{
FILE *fichier = NULL;
char chaine[TAILLE_MAX/10] = {0};
const char chemin[] = "Chemin vers le fichier intro.txt";

fichier = fopen(chemin, "r");
 
if (fichier != NULL)
{
while (fgets(chaine, TAILLE_MAX, fichier) != NULL)
{
printf("%s", chaine);
delay(300);
}

fclose(fichier);

} 
 
else
{
printf("\nImpossible d'ouvrir le fichier intro.txt\n");
}
}


void potence()
{
FILE* fichier = NULL;
char chaine[TAILLE_MAX/10] = {0};
const char chemin[] = "Chemin vers le fichier potence.txt";

fichier = fopen(chemin, "r");
 
if (fichier != NULL)
{
while (fgets(chaine, TAILLE_MAX, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
{
printf("%s", chaine); // On affiche la chaîne qu'on vient de lire
delay(300);
}
 
fclose(fichier);

printf("\n\n");
}

else
{
// On affiche un message d'erreur si on veut
printf("\nImpossible d'ouvrir le fichier potence.txt\n\n");
}
}


void delay(int milli_seconds) {
    struct timespec ts;
    ts.tv_sec = milli_seconds / 1000;
    ts.tv_nsec = (milli_seconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}
