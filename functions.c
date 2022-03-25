#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 9875
#define HOST "127.0.0.1"
#define MAX 250

// Partie variables
char array_game[MAX][MAX] = {0};
int i,j,lines,columns,counter;
int input_x_beg = 0, input_y = 0, input_x_end = 0, input_y_end = 0;
int direction, continue_task = 0;
int number_of_boats = 5;
int correct = 0; //Valeur binaire : 0 = c'est bon, 1 = problème
char tmp[500] = {0};
char tempo[500] = {0};
int verifyArena;

// Partie prototype
void create_arena(int lines, int columns);
void show_arena(int lines, int columns);
void generate_arena (int lines, int columns, int number_of_boats);
void serveur();
void client();


void create_arena(int lines, int columns) {

    counter = 1;

    puts("La configuration du plateau est terminée. Elle ressemble à ceci : ");
        for (i = 0; i <= lines; i++) {
        for (j = 0; j < columns; j++) {

            //COMPTEUR DE LIGNES
            if (j == 0 && counter <= lines) {
                printf("%d°|",counter);
            }
            if(j == 0 && counter > lines) {
                printf("0°|");
            }
            //COMPTEUR DE LIGNES

            //ARèNE DE JEU

            //TRANSCRIPTION DES LIGNES ET DES COLONNES EN CARACTERES
            if(i < lines) {
                array_game[i][j] = 'x';
                printf("  %c",array_game[i][j]);

                if (j == columns-1) {
                    puts("\n");
                    counter += 1;
                }
            //TRANSCRIPTION DES LIGNES ET DES COLONNES EN CARACTERES
            } else {
                //PRINT DE LA DERNIERE COLONNE DE REPERE
                if (j < 9) {
                printf("  %d",j+1);
                } else {
                    printf(" %d",j+1);
                }
            }   //PRINT DE LA DERNIERE COLONNE DE REPERE
            //ARèNE DE JEU
        }    
    }
    puts("");
}

void show_arena(int lines, int columns) {

    counter = 1;

    puts("Votre tableau ressemble à ceci : ");
        for (i = 0; i <= lines; i++) {
        for (j = 0; j < columns; j++) {

            //COMPTEUR DE LIGNES
            if (j == 0 && counter <= lines) {
                printf("%d°|",counter);
            }
            if(j == 0 && counter > lines) {
                printf("0°|");
            }
            //COMPTEUR DE LIGNES

            //ARèNE DE JEU

            //TRANSCRIPTION DES LIGNES ET DES COLONNES EN CARACTERES
            if(i < lines) {
                printf("  %c",array_game[i][j]);
                

                if (j == columns-1) {
                    puts("\n");
                    counter += 1;
                }
            //TRANSCRIPTION DES LIGNES ET DES COLONNES EN CARACTERES
            } else {
                //PRINT DE LA DERNIERE COLONNE DE REPERE
                if (j < 9) {
                printf("  %d",j+1);
                } else {
                    printf(" %d",j+1);
                }
            }   //PRINT DE LA DERNIERE COLONNE DE REPERE
            //ARèNE DE JEU
        }    
    }
    puts("");
}

void generate_arena (int lines, int columns, int number_of_boats) {
    create_arena(lines, columns);
    puts ("");
    puts("Nous allons maintenant placer les bateaux dans ce plan de jeu.");
    while (number_of_boats >= 1) {
        correct = 0;
        printf("Vous avez le droit de poser encore %d bateaux\n",number_of_boats);
        printf("Indiquez le numéro de ligne d'où part votre bateau %d : \n", number_of_boats);
        scanf("%d",&input_x_beg);
        printf("Indiquez le numéro de colonne d'où part votre bateau %d : \n", number_of_boats);
        scanf("%d",&input_y);

        puts("Voulez-vous qu'il soit horizontal ou vertical ? 1 = vertical, 2 = horizontal");
        scanf("%d", &direction);

        switch (direction) {
            case 1:
            printf("Indiquez le numéro de ligne où finit votre bateau %d : \n", number_of_boats);
            scanf("%d",&input_x_end);

            if (input_x_beg > input_x_end && input_x_beg - input_x_end < 5) {
                for (i = input_x_end; i <= input_x_beg; i++) {
                    array_game[i-1][input_y-1] = 'O';    
                }
            } else if (input_x_beg < input_x_end && input_x_end - input_x_beg < 5) {
                for (i = input_x_beg; i <= input_x_end; i++) {
                    array_game[i-1][input_y-1] = 'O';
                }
            } else {
                correct = 1;
            }
            break;

            case 2:
            printf("Indiquez le numéro de colonne où finit votre bateau %d : \n", number_of_boats);
            scanf("%d",&input_y_end);

            if (input_y > input_y_end && input_y - input_y_end < 5) {
                for (i = input_y_end; i <= input_y; i++) {
                    array_game[input_x_beg-1][i-1] = 'O';    
                }
            } else if (input_y < input_y_end && input_y_end - input_y < 5) {
                for (i = input_y; i <= input_y_end; i++) {
                    array_game[input_x_beg-1][i-1] = 'O';
                }
            } else {
                correct = 1;
            }
            break;

            default:
            puts("Je n'ai pas compris votre demande, réitérez avec 1 ou 2");
        }
        if (correct == 0) {
        number_of_boats --;
        show_arena(lines, columns);
        } else {
            puts("Votre bateau ne respecte pas les règles imposées. Veuillez recommencer.");
        }
    }

    puts("Tous les bateaux ont été placés, le jeu va pouvoir commencer.");
    verifyArena = 1;
}

void serveur() {

    struct sockaddr_in srv, client;
    int sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    srv.sin_port = htons(PORT);
    srv.sin_addr.s_addr = inet_addr(HOST);
    srv.sin_family = AF_INET;

    if (bind(sd, (struct sockaddr *)&srv, sizeof(struct sockaddr_in)) < 0) {
        perror("Erreur de la fonction bind()");
        exit(1);
    }

    puts("Serveur socket créé");
    puts("En attente d'une connexion client...");

    listen(sd, 1); //deux clients max

    int sz = sizeof(struct sockaddr_in);
    int clientSocket = accept(sd, (struct sockaddr *) &client, (socklen_t*) &sz);
    if (clientSocket == -1) {
        perror("Erreur fonction accept");
        exit(1);
    }

    printf("\e[1;1H\e[2J"); // clear terminal
    puts("Un client vient de se connecter au serveur");
    puts("En attente d'une action client...");
    

    char ptdr[500] = {0};

    do
    {
        if (recv(clientSocket, ptdr, 499, 0) == -1) {
            perror("Erreur dans la socket du client");
            exit(1);
        };
        if (strcmp(ptdr, "exit") == 0) {
            puts("Fin de la connexion avec le client");
            exit(0);
        }
        if (strcmp(ptdr, "start") == 0) {
            printf("\e[1;1H\e[2J"); // clear terminal
            puts("Veuillez indiquer le nombre de lignes et de colonnes du plateau (Entre 5 et 9");
            scanf("%d",&lines);
            scanf("%d",&columns);
            generate_arena(lines, columns, number_of_boats);
        }
    } while (1);

    puts(ptdr);
}

void client() {

    struct sockaddr_in cl;
    int sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    cl.sin_port = htons(PORT);
    cl.sin_addr.s_addr = inet_addr(HOST);
    cl.sin_family = AF_INET;

    if (connect(sd, (struct sockaddr *) &cl, sizeof(struct sockaddr_in)) == -1) {
        perror("Erreur de la fonction connect");
    }

    printf("\e[1;1H\e[2J"); // clear terminal
    puts("Connexion au serveur établie");
    
    char tmp[500] = {0};
    char sort[500] = "exit";
    char go[500] = "start";
    int ratio;
    
    do
    {
        puts("Veuillez entrer \"start\" pour lancer la partie ou \"exit\" pour quitter :");
        fgets(tmp, 499, stdin);

        tmp[strcspn(tmp, "\n")] = 0;
        sort[strcspn(sort, "\n")] = 0;
        go[strcspn(go, "\n")] = 0;
        if (strcmp(tmp,sort) == 0 || strcmp(tmp,go) == 0) {
            ratio = 667;
        }
        send(sd, tmp, 499, 0);
    } while (ratio != 667);

    puts("En attente de la création du plateau de jeu...");

}