#include "include.h"


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

        while (scanf("%d", &direction),direction != 1 && direction != 2) {
            puts("Je n'ai pas compris votre demande, réitérez avec 1 ou 2");
        }

        switch (direction) {
            case 1:
            printf("Indiquez le numéro de ligne où finit votre bateau %d : \n", number_of_boats);
            scanf("%d",&input_x_end);

            if (input_x_beg >= input_x_end && input_x_beg - input_x_end < 5) {
                for (i = input_x_end; i <= input_x_beg; i++) {
                    array_game[i-1][input_y-1] = 'O';    
                }
            } else if (input_x_beg <= input_x_end && input_x_end - input_x_beg < 5) {
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

            if (input_y >= input_y_end && input_y - input_y_end < 5) {
                for (i = input_y_end; i <= input_y; i++) {
                    array_game[input_x_beg-1][i-1] = 'O';    
                }
            } else if (input_y <= input_y_end && input_y_end - input_y < 5) {
                for (i = input_y; i <= input_y_end; i++) {
                    array_game[input_x_beg-1][i-1] = 'O';
                }
            } else {
                correct = 1;
            }
            break;
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

void rounds(int sd) {
    puts("Indiquez la ligne que vous souhaitez toucher");
    scanf("%d", &input_x_beg);
    puts("Indiquez la colonne que vous souhaitez toucher");
    scanf("%d", &input_y);

    printf("Vous avez décidé de toucher la colonne %d de la ligne %d.\n",input_y,input_x_beg);

    if (array_game[input_x_beg-1][input_y - 1] == 'O') {
        puts("Bateau coûlé");
        array_game[input_x_beg-1][input_y-1] = 'C'; 
    }   else {
        puts("Dans l'eau");
    }
}

void serveur() {

    struct sockaddr_in srv, client;
    int sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    srv.sin_port = htons(PORT);
    srv.sin_addr.s_addr = inet_addr(HOST);
    srv.sin_family = AF_INET;

    if (bind(sd, (struct sockaddr *) &srv, sizeof(struct sockaddr_in)) < 0) {
        perror("Erreur de la fonction bind()");
        exit(1);
    }

    puts("Serveur socket créé");
    puts("En attente d'une connexion client...");

    listen(sd, 1); //un client max

    int sz = sizeof(struct sockaddr_in);
    int clientSocket = accept(sd, (struct sockaddr *) &client, (socklen_t*) &sz);
    if (clientSocket == -1) {
        perror("Erreur fonction accept");
        exit(1);
    }

    printf("\e[1;1H\e[2J"); // clear terminal
    puts("Un client vient de se connecter au serveur");
    puts("En attente d'une action client...");
    

    char msgC[500] = {0};

    do
    {
        if (recv(clientSocket, msgC, 499, 0) == -1) {
            perror("Erreur dans la socket du client");
            exit(1);
        };
        if (strcmp(msgC, "exit") == 0) {
            puts("Fin de la connexion avec le client");
            exit(0);
        }
        if (strcmp(msgC, "start") == 0) {
            printf("\e[1;1H\e[2J"); // clear terminal
            puts("Veuillez indiquer le nombre de lignes et de colonnes du plateau (Entre 5 et 9");
            scanf("%d",&lines);
            scanf("%d",&columns);
            generate_arena(lines, columns, number_of_boats);
            if (verifyArena == 1) {
                strcpy(tempo,"La création du plateau est terminée, le jeu va pouvoir commencer.");

                //ENVOI DES DONNEES AU CLIENT
                send(clientSocket, tempo, 499, 0); //Confirmation fin de création du plateau
                send(clientSocket, array_game, sizeof(array_game), 0); //Envoi de l'intégralité du tableau vers le client
                send(clientSocket, &lines, 499, 0); //Envoi du nombre de lignes vers le client
                send(clientSocket, &columns, 499, 0); //Envoi du nombre de colonnes vers le client
                //ENVOI DES DONNEES AU CLIENT
                recv(clientSocket, array_game, sizeof(array_game), 0);
                show_arena(lines, columns);
                getchar();

                exit(0);
            }
        }
    } while (1);

}

void client() {
    char tmp[500] = {0};
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
    
    char sort[500] = "exit";
    char go[500] = "start";
    int ratio;
    
    do
    {
        puts("Veuillez entrer \"start\" pour lancer la partie ou \"exit\" pour quitter :");
        getchar();
        fgets(tmp, 499, stdin);

        tmp[strcspn(tmp, "\n")] = 0;
        sort[strcspn(sort, "\n")] = 0;
        if (strcmp(tmp, sort) == 0) {
            printf("\e[1;1H\e[2J");
            puts("Fin de connexion avec le serveur");
            exit(0);
        }

        go[strcspn(go, "\n")] = 0;
        if (strcmp(tmp,sort) == 0 || strcmp(tmp,go) == 0) {
            ratio = 667;
        }
        send(sd, tmp, 499, 0);
        puts("En attente de la création du plateau de jeu...");

        //RECEPTION DES DONNEES DU SERVEUR
        recv(sd, tempo, 499, 0);
        recv(sd,array_game, sizeof(array_game), 0);
        recv(sd, &lines, 499, 0);
        recv(sd, &columns, 499, 0);
        //RECEPTION DES DONNEES DU SERVEUR

        printf("\e[1;1H\e[2J"); // clear terminal
        printf("%s\n",tempo);

        for (int i = 0; i < 2; i++) {
        rounds(sd);
        send(sd, array_game, sizeof(array_game), 0);
        }
    } while (ratio != 667);
}