#include "structs.h"
//#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*
Como agora temos 2 cores pra cada ponto, background e foreground, precisamos dobrar o número de
códigos referentes as cores.
*/
#define PRETO_INTENSO_BG "\e[0;100m"
#define BLINK_BG "\x1b[5m"
#define DEFAULT_BG "\x1b[49m"
#define AMARELO_FG "\x1b[33m"
#define AMARELO_BG "\x1b[43m"
#define AZUL_FG "\x1b[34m"
#define AZUL_BG "\x1b[44m"
#define AZUL_CLARO_BG "\x1b[104m"
#define CIANO_FG "\x1b[36m"
#define CIANO_BG "\x1b[46m"
#define CINZA_CLARO_FG "\x1b[90m"
#define CINZA_CLARO_BG "\x1b[100m"
#define MAGENTA_FG "\x1b[35m"
#define MAGENTA_BG "\x1b[45m"
#define MAGENTAC "\x1b[95m"
#define PRETO_FG "\x1b[30m"
#define PRETO_BG "\x1b[40m"
#define VERMELHO_FG "\x1b[31m"
#define VERMELHO_BG "\x1b[41m"
#define VERMELHO_CLARO_BG "\x1b[101m"
#define VERDE_FG "\x1b[0;32m"
#define VERDE_CLARO_FG "\x1b[92m"
#define VERDE_CLARO_BG "\x1b[102m"
#define VERDE_BG "\x1b[42m"
#define MARROM_BG "\033[48;5;94m" // BG \033[48;5;<>m FG \033[38;5;<>m;
#define TERRA_FG "\033[38;5;130m"
#define LARANJA_FG "\033[38;5;202m"
#define VERMELHO2_BG "\033[48;5;160m"
#define BRANCO_FG "\033[38;5;15m"
#define AZUL2_BG "\033[48;5;68m"
#define RESET "\x1b[0m"
#define PROBABILIDADE 20
#define ALTURA 21
#define LARGURA 21
#define ALTURAMAX 40
#define LARGURAMAX 40
#define MAPAS 4
PERSONAGEM eu;
PORTAL portais[3];
char direcao, lixo[40];
PONTO mapa[MAPAS][ALTURAMAX][LARGURAMAX];
int i, j, k;
int b=0, c=0, a = ALTURA, l = LARGURA;
INIMIGO inimigo[MAPAS][10]; int quantInimigos[MAPAS] = {0, 0, 0, 0};
//declaração das funçoes pq vou usá-las depois
void printarMapa(int m);
void inicializaPortal();
void tile(int m);
void inicializaMapa();
void procedural(int k);

PONTO pGrama = {.cor_FG = VERDE_FG, .cor_BG = VERDE_CLARO_BG, .carac = '^', .colisao = 0};
PONTO pGrama2 = {.cor_FG = VERDE_FG, .cor_BG = VERDE_CLARO_BG, .carac = ' ', .colisao = 0};
PONTO pArvore = {.cor_FG = CINZA_CLARO_FG, .cor_BG = VERDE_BG, .carac = '|', .colisao = 1};
PONTO pArvore2 = {.cor_FG = VERDE_FG, .cor_BG = VERDE_CLARO_BG, .carac = '*', .colisao = 1};
PONTO pAgua = {.cor_FG = AZUL_FG, .cor_BG = AZUL_CLARO_BG, .carac = '~', .colisao = 1};
PONTO pMadeira = {.cor_FG = CINZA_CLARO_FG, .cor_BG = AMARELO_BG, .carac = '/', .colisao = 0};
PONTO pTerra = {.cor_FG = TERRA_FG, .cor_BG = MARROM_BG, .carac = '*', .colisao = 0};
PONTO pTerra2 = {.cor_FG = TERRA_FG, .cor_BG = MARROM_BG, .carac = ' ', .colisao = 0};
PONTO pFogo = {.cor_FG = LARANJA_FG, .cor_BG = MARROM_BG, .carac = '?', .colisao = 1};
PONTO pLava = {.cor_FG = LARANJA_FG, .cor_BG = VERMELHO2_BG, .carac = '~', .colisao = 1};
PONTO pGelo = {.cor_FG = AZUL_FG, .cor_BG = AZUL2_BG, .carac = '/', .colisao = 0};
PONTO pChao = {.cor_FG = PRETO_FG, .cor_BG = CINZA_CLARO_BG, .carac = '@', .colisao = 0};
PONTO pBuraco = {.cor_FG = PRETO_FG, .cor_BG = PRETO_BG, .carac = ' ', .colisao = 1};
/*
PONTO pTerra;
PONTO pFogo;
PONTO pMontanha;
PONTO pGelo;
PONTO pChao;
PONTO pBuraco; */




void detalhesMapa(int k){
  int p; int q;
    switch(k) {
      case 0:
        for (p = 0; p < ALTURAMAX; p++){
          mapa[k][p][18] = pAgua;
          mapa[k][p][19] = pAgua;
          mapa[k][p][20] = pAgua;
        }
        for (p = 18; p <= 20; p++){
          mapa[k][7][p] = pGrama;
        }
        for (p = 27; p < LARGURAMAX; p++)
            mapa[k][25][p] = pGrama;
        for (p = LARGURAMAX - 3; p < LARGURAMAX; p++){
            mapa[k][24][p] = pGrama;
            mapa[k][25][p] = pGrama;
            mapa[k][26][p] = pGrama;
        }
        break;
      case 1:
        for (p = 16; p < 27; p++){ // m = 21
            for (q = ALTURAMAX - 11; q < ALTURAMAX; q++) // m = -6
                mapa[k][q][p] = pLava;
        }
        for (p = ALTURAMAX - 11; p < ALTURAMAX - 6; p++)
                mapa[k][p][21] = pTerra;
        for (p = ALTURAMAX - 7; p <= ALTURAMAX - 5; p++){
            for (q = 20; q <= 22; q++){
                mapa[k][p][q] = pTerra;
            }
        }
        mapa[k][ALTURAMAX - 12][21] = pTerra;
        break;

      case 2:
        for (p = 1; p < ALTURAMAX - 1; p++){
            for (q = 1; q < 5; q++)
            mapa[k][p][q] = pAgua;
        }
        for (p = 1; p < LARGURAMAX - 1; p++){
            for (q = 1; q < 5; q++)
            mapa[k][q][p] = pAgua;
        }
        for (p = 1; p < ALTURAMAX - 1; p++){
            for (q = LARGURAMAX - 5; q < LARGURAMAX - 1; q++)
            mapa[k][p][q] = pAgua;
        }
        for (p = 1; p < LARGURAMAX - 1; p++){
            for (q = ALTURAMAX - 5; q < ALTURAMAX - 1; q++)
            mapa[k][q][p] = pAgua;
        }
        for (p = 1; p < ALTURAMAX - 1; p++){
            for (q = 1; q < LARGURAMAX; q = q+3)
            mapa[k][p][q] = pAgua;
        }
        mapa[k][25][13] = pGelo;
        mapa[k][9][16] = pGelo;
        mapa[k][15][19] = pGelo;
        mapa[k][11][22] = pGelo;
        mapa[k][29][25] = pGelo;
        mapa[k][1][27] = pGelo;
        mapa[k][2][27] = pGelo;
        mapa[k][3][27] = pGelo;
        mapa[k][4][27] = pGelo;
        mapa[k][17][12] = pAgua;
        mapa[k][20][14] = pAgua;
        mapa[k][27][14] = pAgua;
        mapa[k][18][20] = pAgua;
        mapa[k][18][22] = pAgua;
        mapa[k][19][24] = pAgua;
        mapa[k][20][25] = pAgua;
        mapa[k][21][25] = pAgua;
        mapa[k][ALTURAMAX - 2][29] = pGelo;
        mapa[k][ALTURAMAX - 3][29] = pGelo;
        mapa[k][ALTURAMAX - 4][29] = pGelo;
        mapa[k][ALTURAMAX - 5][29] = pGelo;
        mapa[k][ALTURAMAX - 8][31] = pGelo;
        mapa[k][12][1] = pGelo;
        mapa[k][12][2] = pGelo;
        mapa[k][13][1] = pGelo;
        mapa[k][13][2] = pGelo;
        mapa[k][14][1] = pGelo;
        mapa[k][14][2] = pGelo;
        mapa[k][1][LARGURAMAX - 2] = pGelo; //PORTAL
        break;
      case 3:
        for (p = 0; p < LARGURAMAX; p++){
            for (q = 0; q < 15; q++)
                mapa[k][q][p] = pBuraco;
            for (q = 24; q < ALTURAMAX; q++)
                mapa[k][q][p] = pBuraco;
        }
        break;
    }
}


void inicializaMapa()
{
  for(k = 0; k < MAPAS; k++)
  {
    for(i = 0; i < ALTURAMAX; i++)
    {
      for(j = 0; j < LARGURAMAX; j++)
      {
        inicializaPortal();
        switch (k) {
          case 0:
            mapa[k][i][j] = pGrama;
            break;
          case 1:
            mapa[k][i][j] = pTerra;
            break;
          case 2:
            mapa[k][i][j] = pGelo;
            break;
          case 3:
            mapa[k][i][j] = pChao;
            break;
        }
      procedural(k);
      }
    detalhesMapa(k);
    }
  }
}



void animPortal(int xp, int yp, int m){
    int disX, disY, dis;
    disX = xp - c;
    disX = disX > LARGURA/2 ? disX : LARGURA - disX;
    disY = yp - b;
    disY = disY > ALTURA/2 ? disY  : ALTURA - disY;
    dis = disX > disY ? disX : disY;
    int r = dis + dis/2 - 1;
    int fase = 0;
    while(r != dis + dis/2)
    {
        for (int i = b; i < a; i++){
            for (int j = c; j < l; j++){
                if ((i - yp)*(i - yp) + (j - xp)*(j - xp) < r*r)
                {
                    //printf("c%d -- l%d\n",c,l );

                    //tile(m);
                    inicializaPortal();

                    printf("%s%s%c "RESET,mapa[m][i][j].cor_FG, mapa[m][i][j].cor_BG,mapa[m][i][j].carac);
                    //printarMapa(m);
                }
                else
                    printf("  ");
            }
            printf("\n");
        }
        //printf("r%d\nd%d\na%d\nb%d\n",r,dis,a,b);
        if (r == 0){
            fase = 1;
            //printf("x%d\n", eu.x);
            if(eu.x == portais[m].x && eu.y == portais[m].y)
              m++;
            else
              if(eu.x == portais[m-1].x && eu.y == portais[m-1].y)
                m--;


        }
        if (fase == 0){
            r--;

        }
        else if (fase == 1){
            r++;
        }
        system("sleep 0.07");
        system("cls");
    }
}

void criarInimigo(int zi, int xi, int yi){
    if (quantInimigos[zi] < 10){
    inimigo[zi][quantInimigos[zi]].x = xi;     //x inicial
    inimigo[zi][quantInimigos[zi]].y = yi;     //y inicial
    quantInimigos[zi]++;
  }
}


void spawnInimigo(int mundo){
  if (quantInimigos[mundo] < 10) {
    srand(clock());
    int chance = rand() % 100;
    if (chance < 4){ //5% de chance
      int si = rand() % ALTURA + b;
      int sj = rand() % LARGURA + c;
      if (mapa[mundo][si][sj].colisao == 0){
        criarInimigo(mundo, sj, si);
      }
    }
  }
}



void andarInimigo(int mundo, int index, int tentativas){
    srand(clock());
    int rand1 = rand() % 2; // 0 = x, 1 = y
    int rand2 = rand() % 2; // 0 = ++, 1 = --
    int andou = 0;
    if (rand1 == 0){
        if (rand2 == 0){
            if (inimigo[mundo][index].x != LARGURAMAX - 1 && mapa[mundo][inimigo[mundo][index].y][inimigo[mundo][index].x+1].colisao == 0){
                inimigo[mundo][index].x++;
                andou = 1;
            }
        }
        else if (rand2 == 1){
            if (inimigo[mundo][index].x != 0 && mapa[mundo][inimigo[mundo][index].y][inimigo[mundo][index].x-1].colisao == 0){
                inimigo[mundo][index].x--;
                andou = 1;
            }
        }
    }
    else if (rand1 == 1){
        if (rand2 == 0){
            if (inimigo[mundo][index].y != ALTURAMAX - 1 && mapa[mundo][inimigo[mundo][index].y+1][inimigo[mundo][index].x].colisao == 0){
                inimigo[mundo][index].y++;
                andou = 1;
            }
        }
        else if (rand2 == 1){
            if (inimigo[mundo][index].y != 0 && mapa[mundo][inimigo[mundo][index].y-1][inimigo[mundo][index].x].colisao == 0){
                inimigo[mundo][index].y--;
                andou = 1;
            }
        }
    }
    if (andou == 0){
      if (tentativas != 10){
        tentativas++;
        andarInimigo(mundo, index, tentativas);
      }
    }
}



void atualizarInimigo(int mundo){
    for (i = 0; i < quantInimigos[mundo]; i++){
        switch(mundo){
          case 0:
            mapa[mundo][inimigo[mundo][i].y][inimigo[mundo][i].x] = pGrama;
            break;
          case 1:
            mapa[mundo][inimigo[mundo][i].y][inimigo[mundo][i].x] = pTerra2;
            break;
          case 2:
            mapa[mundo][inimigo[mundo][i].y][inimigo[mundo][i].x] = pGelo;
            break;
          case 3:
            mapa[mundo][inimigo[mundo][i].y][inimigo[mundo][i].x] = pChao;
            break;
        }
        andarInimigo(mundo, i, 0);
        mapa[mundo][inimigo[mundo][i].y][inimigo[mundo][i].x].carac = 'X';
        mapa[mundo][inimigo[mundo][i].y][inimigo[mundo][i].x].colisao = 1;
    }
}


void procedural(int k)
{
  int ale;
  //srand(clock());
  ale = rand()%100;
  if (portais[k].x != j && portais[k].y != i && eu.x != j && eu.y != i && portais[k].x++ != j && portais[k].y++ != i && portais[k-1].x++ != j && portais[k-1].y++ != i)
  {
    switch (k) {
      case 0:
          if (i < 4 || i > ALTURAMAX - 4 || j < 4 || j > LARGURAMAX - 4){
            if (ale < 40)
                mapa[k][i][j] = pArvore;
          }
          if (j > LARGURAMAX - 5){
            if (ale < 90)
                mapa[k][i][j] = pArvore;
          }
          if (j > LARGURAMAX - 10){
            if (ale < 75)
                mapa[k][i][j] = pArvore;
          }
          if (j > LARGURAMAX - 15){
            if (ale < 40)
                mapa[k][i][j] = pArvore;
          }
          if (ale < 10)
            mapa[k][i][j] = pArvore;
          if (ale > 10 && ale < 20)
            mapa[k][i][j] = pArvore2;
          break;
      case 1:
          if (ale > 60 && ale < 100)
            mapa[k][i][j] = pFogo;
          break;
      case 2:
          if(0)
            mapa[k][i][j] = pFogo;
            break;
      case 3:
            if (ale < 15)
                mapa[k][i][j] = pBuraco;
            break;
    }
  }
}


//funcâo do programa do André
void inicializarPlayer(){
  eu.x = 10;
  eu.y = 10;
  eu.estatos.hp = 20;
  eu.xp = 0;
}

//funcâo do programa do André
void printarStatus(int m){
  printf(MAGENTAC"HP: %d/20    "RESET, eu.estatos.hp);
  printf(MAGENTAC"XP: %.2f/200    "RESET, eu.xp);
  printf(MAGENTAC"Mundo %d\n"RESET, m);
}

//função pra controlar o personagem com validações de colisão e já como parallax
void controla(int m)
{
  scanf("%c", &direcao);
  gets(lixo);
  //printf("%c\n", direcao);
  switch(direcao)
  {
    case 'a':
      if(eu.x != 0 && mapa[m][eu.y][eu.x-1].colisao != 1)
      {
        eu.x--;
        //printf("x%d\n", eu.x);
        if(eu.x < (LARGURAMAX -(LARGURA/2))-1)
        {
          if(l > 0 && l > LARGURA)
            l--;
          //printf("l%d\n", l);
          if(c > 0)
            c--;
          //printf("c%d\n", c);
          }
      }
      break;
    case 'd':
      if(eu.x != LARGURAMAX-1 && mapa[m][eu.y][eu.x+1].colisao !=1)
      {
        eu.x++;
        //printf("x%d\n", eu.x);
        if(eu.x >= (LARGURA/2)+1)
        {
          if(l < LARGURAMAX)
            l++;
          //printf("l%d\n", l);
          if(c < LARGURAMAX && l - c > 21)
            c++;
          //printf("c%d\n", c);
        }
      }
      break;
    case 'w':
      if(eu.y != 0 && mapa[m][eu.y-1][eu.x].colisao !=1)
      {
        eu.y--;
        //printf("y%d\n", eu.y);
        if(eu.y < (ALTURAMAX-(ALTURA/2))-1)
        {
          if(a > 0 && a > ALTURA)
            a--;
          //printf("a%d\n", a);
          if(b > 0)
            b--;
          //printf("b%d\n", b);
        }
      }
      break;
    case 's':
    if(eu.y != ALTURAMAX-1 && mapa[m][eu.y+1][eu.x].colisao !=1)
    {
      eu.y++;
      //printf("y%d\n", eu.y);
      if(eu.y >= (ALTURA/2)+1)
      {
        if(a < ALTURAMAX)
          a++;
        //printf("a%d\n", a);
        if(b < ALTURAMAX && a - b > 21)
          b++;
        //printf("b%d\n", b);
      }
    }
  }
}







//inicializa o mapa


void tiraP(int m)
{
  if(eu.x == j && eu.y == i)
  {
    switch (m){
      case 0:
        mapa[m][i][j] = pGrama;
        break;
      case 1:
        mapa[m][i][j] = pTerra2;
        break;
      case 2:
        mapa[m][i][j] = pGelo;
        break;
      case 3:
        mapa[m][i][j] = pChao;
        break;
    }
  }
}

//pontos especiais no mapa


/*void tile(int m)
{
  for(int i = 0; i< ALTURAMAX; i++)
  {
    for(int j = 0; j < LARGURAMAX; j++)
    {
      if(i % 4 == 0 && j % 5 != 0){
        stpcpy(mapa[m][i][j].cor_BG, AZUL_BG);
        mapa[m][i][j].carac = '*';
        mapa[m][i][j].colisao = 1;
      }
      //cria uma ponte já com a agua de j==11 até j==14  com i==10
      if(i == 10 && (j > 10 && j < 15))
      {
        stpcpy(mapa[m][i][j].cor_BG, AMARELO_BG);
        mapa[m][i][j].carac = ' ';
        stpcpy(mapa[m][i+1][j].cor_BG, AZUL_BG);
        mapa[m][i+1][j].carac = '~';
        mapa[m][i+1][j].colisao = 1;
        stpcpy(mapa[m][i-1][j].cor_BG, AZUL_BG);
        mapa[m][i-1][j].carac = '~';
        mapa[m][i-1][j].colisao = 1;
      }

      //printa onde o personagem tá
      if(eu.x == j && eu.y == i)
      {
        mapa[m][i][j].carac = 'P';
        mapa[m][i][j].colisao = 1;
        stpcpy(mapa[m][i][j].cor_FG, RESET);
      }
    }
  }
  spawnInimigo(m);
  atualizarInimigo(m);
}*/

void tile(int m)
{
  mapa[m][eu.y][eu.x].carac = 'P';
  if (mapa[m][eu.y][eu.x].colisao != 2)
    mapa[m][eu.y][eu.x].colisao = 3;
  stpcpy(mapa[m][eu.y][eu.x].cor_FG, RESET);

  spawnInimigo(m);
  atualizarInimigo(m);
}

//inicializa os portais com a posição no mapa, origem, destino, cor e caracter
void inicializaPortal()
{
  //portais[0].x = 2; portais[0].y = 13;
  //portais[0].origem = 0; portais[0].destino = 1;
  for(int q = 0; q < 4; q++)
  {
    switch(q) {
      case 0:
        portais[q].x = 11; portais[q].y = 10;
        portais[q].origem = 0; portais[q].destino = 1;
        mapa[q][portais[q].y][portais[q].x].carac = 'O';
        mapa[q][portais[q].y][portais[q].x].colisao = 2;
        stpcpy(mapa[q][portais[q].y][portais[q].x].cor_FG, AMARELO_FG);
        stpcpy(mapa[q][portais[q].y][portais[q].x].cor_BG, mapa[q][0][0].cor_BG);
        break;
      case 1:
        portais[q].x = 11; portais[q].y = 12;
        portais[q].origem = 1; portais[q].destino = 2;
        mapa[q][portais[q].y][portais[q].x].carac = 'O';
        mapa[q][portais[q].y][portais[q].x].colisao = 2;
        stpcpy(mapa[q][portais[q].y][portais[q].x].cor_FG, AMARELO_FG);
        mapa[q][portais[q-1].y][portais[q-1].x].carac = 'O';
        stpcpy(mapa[q][portais[q-1].y][portais[q-1].x].cor_FG, AMARELO_FG);
        break;
      case 2:
        portais[q].x = 11; portais[q].y = 14;
        portais[q].origem = 2; portais[q].destino = 3;
        mapa[q][portais[q].y][portais[q].x].carac = 'O';
        mapa[q][portais[q].y][portais[q].x].colisao = 2;
        stpcpy(mapa[q][portais[q].y][portais[q].x].cor_FG, AMARELO_FG);
        mapa[q][portais[q-1].y][portais[q-1].x].carac = 'O';
        stpcpy(mapa[q][portais[q-1].y][portais[q-1].x].cor_FG, AMARELO_FG);
        break;
      case 3:
        portais[3].origem = 3;
        mapa[q][portais[q-1].y][portais[q-1].x].carac = 'O';
        mapa[q][portais[q].y][portais[q].x].colisao = 2;
        stpcpy(mapa[q][portais[q-1].y][portais[q-1].x].cor_FG, AMARELO_FG);
        break;
    }
  }
  /*portais[0].x = 2; portais[0].y = 13;
  portais[0].origem = 0; portais[0].destino = 1;*/
}

//função para teletransportar o personagem para o destino do portal
void portalVai(int *q)
{
  if(eu.x == portais[*q].x && eu.y == portais[*q].y)
  {

    animPortal(eu.x,eu.y,*q);
    eu.x++;
    if(eu.x >= (LARGURA/2)+1)
    {
      if(l < LARGURAMAX)
        l++;
      //printf("l%d\n", l);
      if(c < LARGURAMAX && l - c > 21)
      {
        c++;
        j++;
      }
      //printf("c%d\n", c);
      //tile(*q);

    }
    (*q)++;
    //animPortal(eu.x,eu.y,*q);

    mapa[*q][eu.y][eu.x].carac = 'P';
    mapa[*q][eu.y][eu.x].colisao = 3;
    stpcpy(mapa[*q][eu.y][eu.x].cor_FG, RESET);

    //printarMapa(portais[q].destino);
    //tile(portais[*q].origem);
  }

}

//teletransporta o personagem para a origem do portal (o mundo anterior ao que ele está)
void portalVem(int* m)
{
  if(eu.x == portais[*m-1].x && eu.y == portais[*m-1].y)
  {
    animPortal(eu.x,eu.y,*m);
    eu.x++;
    if(eu.x >= (LARGURA/2)+1)
    {
      if(l < LARGURAMAX)
        l++;
      //printf("l%d\n", l);
      if(c < LARGURAMAX && l - c > 21)
      {
        c++;
        j++;
      }
      //printf("c%d\n", c);
      //tile(*m);

    }

    (*m) = portais[(*m)-1].origem;

    mapa[*m][eu.y][eu.x].carac = 'P';
    mapa[*m][eu.y][eu.x].colisao = 3;
    stpcpy(mapa[*m][eu.y][eu.x].cor_FG, RESET);;
    return;
  }
}

//printa o mapa, dentro dele são chamadas as funções
void printarMapa(int m) {
  //inicializaMapa();

  while (1) {
    for(i = b; i < a; i++)
    {
      for(j = c; j < l; j++)
      {
        switch (m) {
          case 0:
            portalVai(&m);
            printf("%s%s%c "RESET,mapa[m][i][j].cor_FG, mapa[m][i][j].cor_BG,mapa[m][i][j].carac);
            break;
          case 1:
            portalVai(&m);
            portalVem(&m);
            printf("%s%s%c "RESET,mapa[m][i][j].cor_FG, mapa[m][i][j].cor_BG,mapa[m][i][j].carac);
            break;
          case 2:
            portalVai(&m);
            portalVem(&m);
            printf("%s%s%c "RESET,mapa[m][i][j].cor_FG, mapa[m][i][j].cor_BG,mapa[m][i][j].carac);
            break;
          case 3:
            portalVem(&m);
            printf("%s%s%c "RESET,mapa[m][i][j].cor_FG, mapa[m][i][j].cor_BG,mapa[m][i][j].carac);
            break;
        }
        tiraP(m);
      }
      printf("\n" );
    }
    printarStatus(m+1);
    controla(m);
    //tiraI(m);
    //a função inicializa mapa é chamada por causa do P que é printado, para voltar a ser *
    //inicializaMapa();
    tile(m);
    inicializaPortal();
    system("cls");
    system("cls");
  }
}

int main()
{
  inicializarPlayer();
  inicializaMapa();
  tile(0);
  //animPortal(eu.x, eu.y, 0);
  system("cls");
  printarMapa(0);
}
