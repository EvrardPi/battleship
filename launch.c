#include "functions.c"

int main()
{
    FILE *fptr = fopen(log_file_path, "r");
    char role;
    puts("Vous avez la possibilité de choisir entre le rôle de serveur ou le rôle de client ?");

    if (access(log_file_path, F_OK) == 0)
    {
        do {
            puts("Lequel choisissez-vous ?\n1 = admin\n2 = client");
            scanf("%c", &role);
            if (role == '1') break;
            if (role == '2') break;
        } while(true);

        if (role == '1')
        {
            puts("Indiquez le nom d'utilisateur admin");
            scanf("%s", login_id);
            puts("Indiquez le mot de passe administrateur");
            scanf("%s", pwd);
            fscanf(fptr, "%s", login_verify);
            fscanf(fptr, "%s", pwd_verify);

            if (*login_id == *login_verify && *pwd == *pwd_verify)
            {
                serveur();
            }
            else
            {
                puts("Login raté. Le code s'arrête.");
                exit(1);
            }
        }

        if (role == '2') {
            client();
        }
    }
    else
    {
        puts("Fichier d'enregistrement admin non trouvé, Le code s'arrête ici.");
        exit(1);
    }
}
