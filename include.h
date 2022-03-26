#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <linux/limits.h>
#include <curl/curl.h>

#define PORT 9896
#define HOST "127.0.0.1"
#define MAX 250
#define log_file_path "log.txt"

// Partie variables
char array_game[MAX][MAX] = {0}; //Tableau de jeu
int i,j,lines,columns,counter; //Variables utilisées pour la création de l'arène de jeu
int input_x_beg = 0, input_y = 0, input_x_end = 0, input_y_end = 0; //Coordonées du bateau
int direction, continue_task = 0; //Sens du bateau
int number_of_boats = 5; //Nombre de bateaux maximum à placer
int correct = 0; //Valeur binaire : 0 = c'est bon, 1 = problème
char tempo[500] = {0};
int verifyArena; //Vérifie si l'arène de jeu est bien mise en place

//identifiant/mot de passe
char* login_id[100];
char* pwd[100]; 

//Vérif ID/Mot de passe
char* login_verify[100];
char* pwd_verify[100]; 

// Partie prototype de fonction
void create_arena(int lines, int columns);
void show_arena(int lines, int columns);
void generate_arena (int lines, int columns, int number_of_boats);
void serveur();
void client();