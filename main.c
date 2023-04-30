#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "main.h"

int parseLine(char source[], string cible[])
{
    int i = 0, n = 0;
    while (source[i] != ':')
        i++;
    i++;
    int j = i;
    while (source[i] != '\n')
    {
        if (source[i] == ',')
        {
            memcpy(&cible[n], &source[j], i - j);
            n++;
            j = i + 1;
        }
        i++;
    }
    return n;
}

int main(void)
{
    const int SIZETAB = 150;
    char source[150] = {};
    Action_t *actions = malloc(sizeof(Action_t) * SIZETAB);
    Init_t *init = malloc(sizeof(Init_t) * SIZETAB);
    memset(init, 0, sizeof(Init_t) * SIZETAB);
    memset(actions, 0, sizeof(Action_t) * SIZETAB);
    int i;

    FILE *monflux = fopen("school.txt", "r");

    if (monflux == NULL)
    {
        printf("Erreur de fichier: \n");
        exit(0);
    }

    // Lire les débuts (start)
    fgets(source, 100, monflux);
    init->nbStart = parseLine(source, init->start);
    for (i = 0; i < init->nbStart; i++)
        printf("start : %s\n", init->start[i]);

    // Lire les fins (finish)
    fgets(source, 100, monflux);
    init->nbFinish = parseLine(source, init->finish);
    for (i = 0; i < init->nbFinish; i++)
        printf("finish : %s\n", init->finish[i]);

    // Lire les étapes
    actions->nbActions = 0;

    while (fgets(source, 100, monflux) != NULL)
    {
        fgets(source, 100, monflux); // passer la ligne "****"
        printf("\n");
        string preconds[] = {""};
        parseLine(source, preconds);
        strcpy(actions[actions->nbActions].action, preconds[0]);
        printf("action : %s\n", actions[actions->nbActions].action);

        // Lire les différentes préconditions (preconds) d'une étape
        fgets(source, 100, monflux);
        actions[actions->nbActions].nbPreconds = parseLine(source, actions[actions->nbActions].preconds);
        for (i = 0; i < actions[actions->nbActions].nbPreconds; i++)
            printf("precond : %s\n", actions[actions->nbActions].preconds[i]);

        // Lire l'addition (add) d'une étape
        fgets(source, 100, monflux);
        string add[] = {""};
        parseLine(source, add);
        strcpy(actions[actions->nbActions].add, add[0]);
        printf("add : %s\n", actions[actions->nbActions].add);

        // Lire la suppression (supp) d'une étape
        fgets(source, 100, monflux);
        string supp[] = {""};
        parseLine(source, supp);
        strcpy(actions[actions->nbActions].supp, supp[0]);
        printf("supp : %s\n", actions[actions->nbActions].supp);

        actions->nbActions++;
    }
    printf("\n");
    for (i = 0; i < init->nbStart; i++)
    {
        printf("Start: %s\n", init->start[i]);
    }
    fclose(monflux);
    free(init);
    free(actions);
}
