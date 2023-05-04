#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "timeUpdate.h"

// Funcao interna que atualiza o timer conforme as jogadas
void updateTime(State_t* states, Sounds_t* sounds)
{
    FILE* Orgarq;
    FILE* Newarq;
    int WrittenScoreEASY, WrittenScoreMEDIUM, WrittenScoreHARD;
    char* line;

    // Se o tempo chegou a zero, mas fiz um match
    if (states->timeState == TIME_STOP && states->time > 0)
        states->timeState = TIME_RUNNING;
        
    // Depois de todos os estados da gameplay checados, atualiza o tempo
    if (states->timeState == TIME_RUNNING)
        states->time -= 0.016;  // 1/60, a cada 60 rodadas, passa 1 segundo

    if (states->time <= 0)
        states->timeState = TIME_STOP;

    if (states->timeState == TIME_STOP)
    {
        states->time = 0;    // Zera para nao desenhar na tela '0.1' ou '0.2'

        if (states->gameplayState == IDLE || states->gameplayState == SELECTING)
        {
            states->gameState = GAME_OVER;

            // Para a musica
            al_stop_sample_instance(sounds->SongInstance);

            Orgarq = fopen(PATH_TO_SCOREBOARD , "r");
            Newarq = fopen(PATH_TO_TEMP , "w");

            line = malloc(sizeof(char) * 16);

            // Testa se o arquivo abre
            if (!Orgarq)
            {
                printf("can not open target file\n");
                exit(1);
            }

            // Testa se o arquivo abre
            if (!Newarq)
            {
                printf("can not open target file\n");
                exit(1);
            }

            // Le valores dos scores guardados
            fgets(line, 16, Orgarq);
            WrittenScoreHARD = atoi(line);
            fgets(line, 16, Orgarq);
            WrittenScoreMEDIUM = atoi(line);
            fgets(line, 16, Orgarq);
            WrittenScoreEASY = atoi(line);

            // Verifica qual dificuldade estou jogando e escreve em
            // um arquivo novo se o score foi maior
            if (states->gameDifficulty == EASY)
            {
                if (states->score > WrittenScoreEASY)
                {
                    states->recordState = BEATEN;
                    WrittenScoreEASY = states->score;
                }
            }
            else if (states->gameDifficulty == MEDIUM)
            {
                if (states->score > WrittenScoreMEDIUM)
                {
                    states->recordState = BEATEN;
                    WrittenScoreMEDIUM = states->score;
                }
            }
            else if (states->gameDifficulty == HARD)    
            {
                if (states->score > WrittenScoreHARD)
                {
                    states->recordState = BEATEN;
                    WrittenScoreHARD = states->score;
                }
            }

            // Imprime os valores no arquivo novo temporario
            fprintf (Newarq, "%d\n", WrittenScoreHARD);
            fprintf (Newarq, "%d\n", WrittenScoreMEDIUM);
            fprintf (Newarq, "%d", WrittenScoreEASY);


            fclose(Orgarq);
            fclose(Newarq);
            free(line);

            // Deleta o antigo e renomeia o temporario
            remove(PATH_TO_SCOREBOARD);
            rename(PATH_TO_TEMP, PATH_TO_SCOREBOARD);
        }
    }
}