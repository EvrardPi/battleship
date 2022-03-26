#include "functions.c"

int main() {

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