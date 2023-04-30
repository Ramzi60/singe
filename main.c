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
    const int SIZETAB = 300;
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
    for (int g = 0; g < init->nbStart; g++)
        printf("start : %s\n", init->start[g]);

    // Lire les fins (finish)
    fgets(source, 100, monflux);
    init->nbFinish = parseLine(source, init->finish);
    for (int m = 0; m < init->nbFinish; m++)
        printf("finish : %s\n", init->finish[m]);

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
        for (int e = 0; e < actions[actions->nbActions].nbPreconds; e++)
            printf("precond : %s\n", actions[actions->nbActions].preconds[e]);

        // Lire l'addition (add) d'une étape
      fgets(source, 100, monflux);
  actions[actions->nbActions].nbAdd = parseLine(source, actions[actions->nbActions].add);
for (int n = 0; n < actions[actions->nbActions].nbAdd; n++)
    printf("add : %s\n", actions[actions->nbActions].add[n]);

        // Lire la suppression (supp) d'une étape
      fgets(source, 100, monflux);
  actions[actions->nbActions].nbSupp = parseLine(source, actions[actions->nbActions].supp);
for (int e = 0; e < actions[actions->nbActions].nbSupp; e++)
    printf("supp : %s\n", actions[actions->nbActions].supp[e]);
        actions->nbActions++;
    }
    int j;
    int resolved = 0;
    actions[actions->nbActions].validated = false;
    while (!resolved)
    {
      resolved = 1;
      
        for (i = 0; i < actions[i].nbActions; i++)
          {
          for (int f = 0; f < actions->nbAdd; f++){
            for (int b = 0; b < actions->nbSupp; b++){
            if (!actions[i].validated)
            {
                int allPrecondsSatisfied = 1;
                for (j = 0; j <= actions[i].nbPreconds; j++)
                {
                    int precondSatisfied = 0;
                    int k;
                    for (k = 0; k < init->nbStart; k++)
                    {
                        if (strcmp(actions[i].preconds[j], init->start[k]) == 0)
                        {
                            precondSatisfied = 1;
                            break;
                        }
                        else {
                          precondSatisfied = 0;
                        }
                    }
                    if (!precondSatisfied)
                    {
                        allPrecondsSatisfied = 0;
                        int l,o,w;
                       for (o = 0; o < actions->nbAdd; o++)
                         for (w = 0; w < actions->nbPreconds; w++)
                        for (l = 0; l < actions->nbActions; l++)
                          
                        {
                            if (strcmp(actions->add[f], actions[i].preconds[w]) == 0)
                            {
                              printf("preuve %s\n",init->start[i]);
                                int allPrecondsSatisfied2 = 1;
                                int m;
                                for (m = 0; m < actions[l].nbPreconds; m++)
                                {
                                    int precondSatisfied2 = 0;
                                    int n;
                                  printf("preuve %s\n",init->start[i]);
                                    for (n = 0; n < init->nbStart; n++)
                                    {
                                        if (strcmp(actions[l].preconds[m], init->start[n]) == 0)
                                        {
                                          printf("preuve %s\n",init->start[i]);
                                            precondSatisfied2 = 1;
                                            break;
                                        }
                                    }
                                    if (!precondSatisfied2)
                                    {
                                        allPrecondsSatisfied2 = 0;
                                        break;
                                    }
                                }
                                if (!allPrecondsSatisfied2)
                                {
                                  printf("preuve %s\n",init->start[i]);
                                    int p;
                                    for (p = 0; p < init->nbStart; p++)
                                    {
                                        if (strcmp(actions->add[f], init->start[p]) == 0)
                                        {
                                          printf("AKHAAA %s\n",init->start[i]);
                                            break;
                                          
                                        }
                                    }
                                    if (p == init->nbStart)
                                    {
                                        strcpy(init->start[init->nbStart],actions->add[f]);
                                        init->nbStart++;
                                        printf("preuve %s\n",init->start[i]);
                                        resolved = 0;
                                        break;
                                    }
                                }
                            }
                        }
                        if (!resolved)
                        {
                            break;
                        }
                    }
                  else {
                    allPrecondsSatisfied = 0;
                  }
                }
                if (!allPrecondsSatisfied)
                {
                    int q;
                    for (q = 0; q < init->nbStart; q++)
                    {
                        if (strcmp(actions->supp[b], init->start[q]) == 0)
                        { 
                            strcpy(init->start[q], "");
                            break;
                        }
                    }
                    for (int j = 0; j < actions->nbAdd; j++){
                      for (q = 0; q < init->nbStart; q++)
                    {
                        if (strcmp(actions->add[j], init->start[q]) == 0)
                        {
                            break;
                        }
                    }
                    }
                    if (q == init->nbStart)
                    {
                        strcpy(init->start[init->nbStart], actions->add[f]);
                        init->nbStart++;                   
                        resolved = 0;
                        break;
                    }
                }
            }
        }
        int r;
        for (r = 0; r < init->nbFinish; r++)
        {
            int finishSatisfied = 0;
            int s;
            for (s = 0; s < init->nbStart; s++)
            {
                if (strcmp(init->finish[r], init->start[s]) == 0)
                {
                    finishSatisfied = 1;
                    break;
                }
            }
            if (!finishSatisfied)
            {
                break;
            }
        }
        if (r == init->nbFinish)
        {
            break;
        }
          }
          }
    }
  //  for (int x = i; x < init->nbStart - 1; x++)
   // {
    //    strcpy(init->start[x], init->start[x + 2]);
   // }
   // init->nbStart--;

    printf("\n");
   for (i = 0; i < init->nbStart; i++)
    {
        printf("Start: %s\n", init->start[i]);
    }
    fclose(monflux);
    free(init);
    free(actions);
}
