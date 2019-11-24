#include "structs.h"
//#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define AMARELO_FG "\x1b[33m"
#define AMARELO_BG "\x1b[43m"
#define AZUL_FG "\x1b[34m"
#define AZUL_BG "\x1b[44m"
#define CIANO_FG "\x1b[36m"
#define CIANO_BG "\x1b[46m"
#define MAGENTA_FG "\x1b[35m"
#define MAGENTA_BG "\x1b[45m"
#define MAGENTAC "\x1b[95m"
#define PRETO_FG "\x1b[30m"
#define PRETO_BG "\x1b[40m"
#define VERMELHO_FG "\x1b[31m"
#define VERMELHO_BG "\x1b[41m"
#define VERDE_FG "\x1b[0;32m"
#define VERDE_BG "\x1b[42m"
#define RESET "\x1b[0m"
#define PROBABILIDADE 20
#define ALTURA 20
#define LARGURA 20
#define MAPAS 4
PERSONAGEM eu;
PORTAL portais[3];
char direcao, lixo[40];
int x, i, j, k;
PONTO mapa[MAPAS][ALTURA][LARGURA];
PONTO mapaAtual[ALTURA][LARGURA];

void controla()
{
  scanf("%c", &direcao);
  switch (direcao) {
    case 'a':
      if(eu.x != 0 && mapaAtual[eu.y][eu.x-1].colisao != 1)
        eu.x--;
      break;
    case 'w':
      if(eu.y != 0 && mapaAtual[eu.y-1][eu.x].colisao != 1)
        eu.y--;
      break;
    case 's':
      if(eu.y != ALTURA-1 && mapaAtual[eu.y+1][eu.x].colisao != 1)
        eu.y++;
      break;
    case 'd':
      if(eu.x != LARGURA-1 && mapaAtual[eu.y][eu.x+1].colisao != 1)
        eu.x++;
      break;
  }
}

void limpar(){
        system("clear");
}

void inicializarPlayer(){
  eu.x = 0;
  eu.y = 0;
  eu.estatos.hp = 20;
  eu.xp = 0;
}

void inicializarMapas()
{
  for(k = 0; k < MAPAS; k++)
  {
    for(i = 0; i < ALTURA; i++)
    {
      for(j = 0; j < LARGURA; j++)
      {
        mapa[k][i][j].carac = '*';
        mapa[k][i][j].colisao = 0;
        stpcpy(mapa[k][i][j].cor_FG, PRETO_FG);
        switch(k)
        {
          case 0:
            stpcpy(mapa[k][i][j].cor_BG, VERDE_BG);
            break;
          case 1:
            stpcpy(mapa[k][i][j].cor_BG, AZUL_BG);
            break;
          case 2:
            stpcpy(mapa[k][i][j].cor_BG, VERMELHO_BG);
            break;
          case 3:
            stpcpy(mapa[k][i][j].cor_BG, PRETO_BG);
            break;
        }
      }
    }
  }
}

void printarMapa()
{
    for (int i = 0; i < ALTURA; i++)
    {
        for (int j = 0; j < LARGURA; j++)
        {
          printf("%s%s%c "RESET,mapaAtual[i][j].cor_FG, mapaAtual[i][j].cor_BG,mapaAtual[i][j].carac);
        }
        printf("\n");
    }
}

void printarStatus(){
  printf(MAGENTAC"HP: %d/20    "RESET, eu.estatos.hp);
  printf(MAGENTAC"XP: %.2f/200    "RESET, eu.xp);
  printf(MAGENTAC"Mundo %d\n"RESET, eu.z+1);
}

void carregarMapa(int n){
    for (int i = 0; i < ALTURA; i++){
        for (int j = 0; j < LARGURA; j++){
            mapaAtual[i][j] = mapa[n][i][j];
        }
    }
}
void atualizarMapa(){
    carregarMapa(eu.z);
    mapaAtual[eu.y][eu.x].carac = 'P';
}

void update(){
    while(1){
        controla();
        atualizarMapa();
        limpar();
        printarMapa();
    }
}

int main(void){
    limpar();
    inicializarPlayer(); printf("inicializarPlayer OK\n");
    inicializarMapas(); printf("inicializarMapas OK\n");
    atualizarMapa(); printf("atualizarMapa OK\n");
    printarMapa(); printf("PrintarMapa OK\n");
    printarStatus(); printf("printarStatus OK\n");
    update();
}
