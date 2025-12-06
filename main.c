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

    clock_t start, end;

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
    char separador[]= {",\n\t"};

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
            start = clock();

            //Leitura e inserção do arquivo de origem .csv
            while (fgets(linha,1000,jogosSteam)){
                palavra = StringMinusculo(strtok(linha,separador));
                tempoDeJogo = (float)atof(strtok(NULL,separador));
                InsereABP(palavra, tempoDeJogo, &ABP);
                numeroDeNodosABP++;
                AVL = InsereAVL(palavra, tempoDeJogo, AVL, &ok, &numeroDeRotacoesAVL);
                ASp = InsereSplay(ASp, palavra, tempoDeJogo, &numeroDeRotacoesASp);
            }

            printf("Arvore gerada com sucesso\n");

            //Leitura da lista do jogador e consulta nas arvores
            while (fgets(linha, 1000, listaJogador)){
                palavra = StringMinusculo(strtok(linha,separador));
                tempoTotalABP += TempoNodoArvore(ABP, palavra, &comparacoesABP);
                numeroDeJogosABP++;
                tempoTotalAVL += TempoNodoArvore(AVL, palavra, &comparacoesAVL); //usada para atualizar as comparações AVL
                ConsultaNodo(ASp, palavra, &numeroDeRotacoesASp, &comparacoesASp); //usada para atualizar as comparações Splay
            }

            alturaABP = AlturaABP(ABP);
            alturaAVL = AlturaABP(AVL);
            alturaASp = AlturaABP(ASp);

            //Escrita dos dados no arquivo de saida
            fprintf(saida, "Tempo total estimado: %.0lf horas\n", tempoTotalABP);
            fprintf(saida, "\n======== ESTATÍSTICAS ABP ===========\n");
            fprintf(saida, "Numero de Nodos: %d\n", numeroDeNodosABP);
            fprintf(saida, "Altura: %d\n", alturaABP);
            fprintf(saida, "Rotações: 0\n");
            fprintf(saida, "Comparações: %d\n", comparacoesABP);
            
            fprintf(saida, "\n======== ESTATÍSTICAS AVL ===========\n");
            fprintf(saida, "Altura: %d\n", alturaAVL);
            fprintf(saida, "Rotações: %d\n", numeroDeRotacoesAVL);
            fprintf(saida, "Comparações: %d\n", comparacoesAVL);

            fprintf(saida, "\n======== ESTATÍSTICAS Splay ===========\n");
            fprintf(saida, "Altura: %d\n", alturaASp);
            fprintf(saida, "Rotações: %d\n", numeroDeRotacoesASp);
            fprintf(saida, "Comparações: %d\n", comparacoesASp);

            end = clock();
            float milisegundos = (float)(end - start) / CLOCKS_PER_SEC * 1000;
            printf("Tempo: %.5f ms\n", milisegundos);
        }

        fclose(jogosSteam);
        fclose(listaJogador);
        fclose(saida);
        return 0;
    }
}