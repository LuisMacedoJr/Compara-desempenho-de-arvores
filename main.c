#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <ctype.h>
#include "arvores.h"

int main(int argc, char *argv[]){

    setlocale(LC_ALL,"");

    clock_t startMontagemAbp, endMontagemAbp, startConsultaAbp, endConsultaAbp;
    clock_t startMontagemAvl, endMontagemAvl, startConsultaAvl, endConsultaAvl;
    clock_t startMontagemSplay, endMontagemSplay, startConsultaSplay, endConsultaSplay;

    FILE* jogosSteam;
    FILE* listaJogador;
    FILE* saida;

    char* palavra, linha[1000];
    float tempoDeJogo;

    // Variáveis utilizadas na ABP
    double tempoTotalABP = 0;
    int numeroDeJogosABP = 0, comparacoesABP = 0, numeroDeNodosABP = 0, alturaABP;
    
    
    // Variáveis utilizadas na AVL
    double tempoTotalAVL = 0;
    int comparacoesAVL = 0, alturaAVL, numeroDeRotacoesAVL = 0, ok;

    // Variáveis utilizadas na Splay
    double tempoTotalASp = 0;
    int comparacoesASp = 0, alturaASp, numeroDeRotacoesASp = 0;

    //separadores para leitura de arquivos
    char separador[]= {",\t\r\n\v\f"};

    Nodo* ABP = CriaArvore();
    Nodo* AVL = CriaArvore();
    Nodo* ASp = CriaArvore();

    if (argc!=4){
        printf("Número incorreto de parâmetros.\n Para chamar o programa digite: tempoJogos <arq_entrada> <arq_saida>\n");
        return 1;
    }
    else {
        jogosSteam = fopen(argv[1], "r");
        listaJogador = fopen(argv[2], "r");
        if (jogosSteam == NULL || listaJogador == NULL){
            printf("Erro ao abrir o arquivo %s ou %s", argv[1], argv[2]);
            return 1;
        }
        else {
            saida = fopen (argv[3], "w");
            
            //Leitura e inserção do arquivo de origem .csv
            startMontagemAbp = clock();
            while (fgets(linha,1000,jogosSteam)){
                palavra = StringMinusculo(strtok(linha,separador));
                tempoDeJogo = (float)atof(strtok(NULL,separador));
                InsereABP(palavra, tempoDeJogo, &ABP);
                numeroDeNodosABP++;
            }
            endMontagemAbp = clock();

            jogosSteam = fopen(argv[1], "r");

            startMontagemAvl = clock();
            while (fgets(linha,1000,jogosSteam)){
                palavra = StringMinusculo(strtok(linha,separador));
                tempoDeJogo = (float)atof(strtok(NULL,separador));
                AVL = InsereAVL(palavra, tempoDeJogo, AVL, &ok, &numeroDeRotacoesAVL);
            }
            endMontagemAvl = clock();

            jogosSteam = fopen(argv[1], "r");

            startMontagemSplay = clock();
            while (fgets(linha,1000,jogosSteam)){
                palavra = StringMinusculo(strtok(linha,separador));
                tempoDeJogo = (float)atof(strtok(NULL,separador));

                ASp = InsereSplay(ASp, palavra, tempoDeJogo, &numeroDeRotacoesASp);
            }
            endMontagemSplay = clock();


            startConsultaAbp = clock();
            //Leitura da lista do jogador e consulta nas arvores
            while (fgets(linha, 1000, listaJogador)){
                palavra = StringMinusculo(strtok(linha,separador));
                tempoTotalABP += TempoNodoArvore(ABP, palavra, &comparacoesABP);
            }
            endConsultaAbp = clock();

            listaJogador = fopen(argv[2], "r");

            startConsultaAvl = clock();
            while (fgets(linha, 1000, listaJogador)){
                palavra = StringMinusculo(strtok(linha,separador));
                tempoTotalAVL += TempoNodoArvore(AVL, palavra, &comparacoesAVL); //usada para atualizar as comparações AVL
            }
            endConsultaAvl = clock();

            listaJogador = fopen(argv[2], "r");

            startConsultaSplay = clock();
            while (fgets(linha, 1000, listaJogador)){
                palavra = StringMinusculo(strtok(linha,separador));
                ConsultaNodo(ASp, palavra, &numeroDeRotacoesASp, &comparacoesASp); //usada para atualizar as comparações Splay
            }
            endConsultaSplay = clock();

            alturaABP = AlturaABP(ABP);
            alturaAVL = AlturaABP(AVL);
            alturaASp = AlturaABP(ASp);

            float milisegundosAbp = (float)((endMontagemAbp - startMontagemAbp) + (endConsultaAbp - startConsultaAbp)) / CLOCKS_PER_SEC * 1000;
            float milisegundosAvl = (float)((endMontagemAvl - startMontagemAvl) + (endConsultaAvl - startConsultaAvl)) / CLOCKS_PER_SEC * 1000;
            float milisegundosSplay = (float)((endMontagemSplay - startMontagemSplay) + (endConsultaSplay - startConsultaSplay)) / CLOCKS_PER_SEC * 1000;

            //Escrita dos dados no arquivo de saida
            fprintf(saida, "Tempo total estimado: %.2lf horas\n", tempoTotalABP);
            fprintf(saida, "Numero de Nodos: %d\n", numeroDeNodosABP);

            fprintf(saida, "\n======== ESTATÍSTICAS ABP ===========\n");
            fprintf(saida, "Altura: %d\n", alturaABP);
            fprintf(saida, "Rotações: 0\n");
            fprintf(saida, "Comparações: %d\n", comparacoesABP);
            fprintf(saida, "Tempo de execução: %.2fms\n", milisegundosAbp);
            
            fprintf(saida, "\n======== ESTATÍSTICAS AVL ===========\n");
            fprintf(saida, "Altura: %d\n", alturaAVL);
            fprintf(saida, "Rotações: %d\n", numeroDeRotacoesAVL);
            fprintf(saida, "Comparações: %d\n", comparacoesAVL);
            fprintf(saida, "Tempo de execução: %.2fms\n", milisegundosAvl);


            fprintf(saida, "\n======== ESTATÍSTICAS Splay ===========\n");
            fprintf(saida, "Altura: %d\n", alturaASp);
            fprintf(saida, "Rotações: %d\n", numeroDeRotacoesASp);
            fprintf(saida, "Comparações: %d\n", comparacoesASp);
            fprintf(saida, "Tempo de execução: %.2fms\n", milisegundosSplay);


        }

        fclose(jogosSteam);
        fclose(listaJogador);
        fclose(saida);
        return 0;
    }
}