#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Film
{
    char titre[100];
    int annee;
};

int comparerAnnee(const void *a, const void *b)
{
    return ((struct Film *)a)->annee - ((struct Film *)b)->annee;
}

void afficherFilms(struct Film *films, int nombreFilms)
{
    for (int i = 0; i < nombreFilms; i++)
    {
        printf("Titre: %s Année de sortie: %d\n", films[i].titre, films[i].annee);
    }
}

void sauvegarderFilms(struct Film *films, int nombreFilms, const char *nomFichier)
{
    FILE *fichier = fopen(nomFichier, "w");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier en écriture");
        }

    for (int i = 0; i < nombreFilms; i++)
    {
        fprintf(fichier, "%s %d\n", films[i].titre, films[i].annee);
    }

    fclose(fichier);
}

int main()
{
    struct Film films[100];
    int nombreFilms = 0;

    FILE *fichier = fopen("films.txt", "r");
    if (fichier != NULL)
    {
        while (fscanf(fichier, "%s %d", films[nombreFilms].titre, &films[nombreFilms].annee) == 2)
        {
            nombreFilms++;
        }
        fclose(fichier);
    }

    while (1)
    {
        printf("1. Ajouter un film\n");
        printf("2. Afficher les films triés par année\n");
        printf("3. Quitter\n");

        int choix;
        printf("Choix: ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            printf("Entrer le titre du film: ");
            scanf("%s", films[nombreFilms].titre);
            printf("Entrer l'année de sortie du film: ");
            scanf("%d", &films[nombreFilms].annee);
            nombreFilms++;
            break;
        case 2:
            qsort(films, nombreFilms, sizeof(struct Film), comparerAnnee);
            afficherFilms(films, nombreFilms);
            sauvegarderFilms(films, nombreFilms, "films_tries.txt");
            break;
        case 3:
            sauvegarderFilms(films, nombreFilms, "films.txt");
            return 0;
        default:
            printf("Choix non valide. Veuillez entrer 1, 2, ou 3.\n");
        }
    }

    return 0;
}