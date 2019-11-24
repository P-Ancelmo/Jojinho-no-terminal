#include "structs.h"
//#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define AMARELO "\x1b[33m"
#define AZUL "\x1b[34m"
#define CIANO "\x1b[36m"
#define MAGENTA "\x1b[35m"
#define MAGENTAC "\x1b[95m"
#define PRETO "\x1b[30m"
#define VERMELHO "\x1b[31m"
#define VERDE "\e[0;32m"
#define RESET "\x1b[0m"
#define PROBABILIDADE 20
#define ALTURA 20
#define LARGURA 20
PONTO mapa[4][ALTURA][LARGURA];
PERSONAGEM eu;
PORTAL portais[3];
char direcao, lixo[40];
char cores[4][9] = {VERDE, AZUL, VERMELHO, PRETO};
int x, i, j;


void controla(int m)
{
  scanf("%c", &direcao);
  switch (direcao) {
    case 'a':
      if(eu.x != 0 && mapa[m][eu.y][eu.x-1].colisao != 1)
        eu.x--;
      break;
    case 'w':
      if(eu.y != 0 && mapa[m][eu.y-1][eu.x].colisao != 1)
        eu.y--;
      break;
    case 's':
      if(eu.y != ALTURA-1 && mapa[m][eu.y+1][eu.x].colisao != 1)
        eu.y++;
      break;
    case 'd':
      if(eu.x != LARGURA-1 && mapa[m][eu.y][eu.x+1].colisao != 1)
        eu.x++;
      break;
  }
}

void inicializaMapa()
{
  for(x = 0; x < 4; x++)
  {
    for(i = 0; i < ALTURA; i++)
    {
      for(j = 0; j < LARGURA; j++)
      {
        if(mapa[x][i][j].colisao == 1)
          mapa[x][i][j].carac = '|';
        else
          mapa[x][i][j].carac = '*';
        switch (x) {
          case 0:
            stpcpy(mapa[x][i][j].cor, VERDE);
            break;
          case 1:
            stpcpy(mapa[x][i][j].cor, AZUL);
            break;
          case 2:
            stpcpy(mapa[x][i][j].cor, VERMELHO);
            break;
          case 3:
            stpcpy(mapa[x][i][j].cor, PRETO);
            break;
        }
      }
    }
  }
}

void porMapa(int m)
{
  while(1)
  {

    for(i = 0; i < ALTURA; i++)
    {
      for(j = 0; j < LARGURA; j++)
      {
        if(j == eu.x && i == eu.y)
        {
          mapa[m][i][j].carac = 'P';
          stpcpy(mapa[m][i][j].cor, CIANO);
        }
        switch (m) {
          case 0:
            printf("%s%c "RESET,mapa[m][i][j].cor,mapa[m][i][j].carac);
            break;
          case 1:
            printf("%s%c "RESET,mapa[m][i][j].cor,mapa[m][i][j].carac);
            break;
          case 2:
            printf("%s%c "RESET,mapa[m][i][j].cor,mapa[m][i][j].carac);
            break;
          case 3:
            printf("%s%c "RESET,mapa[m][i][j].cor,mapa[m][i][j].carac);
            break;
        }
        if(j == eu.x && i == eu.y)
        {
          mapa[m][i][j].carac = '*';
          stpcpy(mapa[m][i][j].cor, cores[m]);
        }
      }
      printf("\n");
    }
    printf(MAGENTAC"HP: %d/20    "RESET, eu.estatos.hp);
    printf(MAGENTAC"XP: %.2f/200    "RESET, eu.xp);
    printf(MAGENTAC"Mundo %d\n"RESET, m+1);
    controla(m);
    system("clear");
  }
}

int main()
{
  eu.x = 0;
  eu.y = 0;
  eu.estatos.hp = 20;
  eu.xp = 0;
  mapa[0][0][1].colisao = 1;
  inicializaMapa();
  porMapa(0);
  return 0;
}
