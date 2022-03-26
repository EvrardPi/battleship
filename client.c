#include "functions.c"

int main() {

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
        fgets(tmp, 499, stdin);

        tmp[strcspn(tmp, "\n")] = 0;
        sort[strcspn(sort, "\n")] = 0;
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