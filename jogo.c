#include "combate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*
Como agora temos 2 cores pra cada ponto, background e foreground, precisamos dobrar o número de
códigos referentes as cores.

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
*/
#define AZUL2_BG "\033[48;5;68m"
#define TERRA_FG "\033[38;5;130m"
#define MARROM_BG "\033[48;5;94m"
#define LARANJA_FG "\033[38;5;202m"
#define LARANJA_BG "\033[48;5;202m"
#define VERMELHO2_BG "\033[48;5;160m"
#define BRANCO_FG "\033[38;5;15m"
INIMIGO inimigos[MAPAS][10]; int quantInimigos[MAPAS] = {0, 0, 0, 0};
INIMIGO boss[4];
int bau;
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
PONTO pBau0 = {.cor_FG = BRANCO_FG, .cor_BG = VERDE_CLARO_BG, .carac = '&', .colisao = 4};
PONTO pBau1 = {.cor_FG = BRANCO_FG, .cor_BG = MARROM_BG, .carac = '&', .colisao = 4};
PONTO pBau2 = {.cor_FG = BRANCO_FG, .cor_BG = AZUL2_BG, .carac = '&', .colisao = 4};

void animVitoria(int m){
    int cont = 0;
    while(cont < 500){
        for (i = 0; i < ALTURA; i++){
            for (j = 0; j < LARGURA; j++){
                mapa[m][i][j].carac = ' ';
                srand(clock());
                int ale = rand() % 3;
                    switch(ale){
                        case 0:
                            stpcpy(mapa[m][i][j].cor_BG, VERDE_CLARO_BG);
                            break;
                        case 1:
                            stpcpy(mapa[m][i][j].cor_BG, LARANJA_BG);
                            break;
                        case 2:
                            stpcpy(mapa[m][i][j].cor_BG, AZUL_CLARO_BG);
                            break;
                    }
                printf("%s%s%c %s", mapa[m][i][j].cor_FG, mapa[m][i][j].cor_BG, mapa[m][i][j].carac, RESET);
            }
        printf("\n");
        }
        system("clear");
        system("clear");
        cont++;
    }
    system("clear");
    system("clear");
    printf("%s%sY \n", RESET, LARANJA_FG);
    system("sleep 1.0");
    printf("%s%sO \n", RESET, VERDE_CLARO_FG);
    system("sleep 1.0");
    printf("%s%sU \n", RESET, AZUL_FG);
    system("sleep 1.0");
    printf("%s%s  \n", RESET, VERMELHO_FG);
    system("sleep 1.0");
    printf("%s%sW \n", RESET, VERDE_FG);
    system("sleep 1.0");
    printf("%s%sI \n", RESET, MAGENTA_FG);
    system("sleep 1.0");
    printf("%s%sN \n", RESET, AZUL_FG);
    system("sleep 1.0");
    printf("%s%s! \n", RESET, BRANCO_FG);
    system("sleep 1.0");
    exit(0);
}


void inicializaGrupo()
{
  stpcpy(grupo[0].nome, "Curandeiro");
  stpcpy(grupo[1].nome, "Guerreiro");
  stpcpy(grupo[2].nome, "Mago");
  grupo[0].defesa = 7;
  grupo[0].estatos.hp = 55;
  grupo[0].estatos.hpmax = 55;
  grupo[1].ataque = 8;
  grupo[1].defesa = 19;
  grupo[1].estatos.hp = 200;
  grupo[1].estatos.hpmax = 200;
  grupo[2].ataque = 15;
  grupo[2].defesa = 7;
  grupo[2].estatos.hp = 70;
  grupo[2].estatos.hpmax = 70;
  for(int i = 0; i < 3; i++)
  {
      grupo[i].xp = 0;
      grupo[i].xpmax = 100;
      grupo[i].estatos.cura = 1;
      grupo[i].estatos.buff = 1;
      grupo[i].lvl = 1;
  }
}


void detalhesMapa(int k){
    //BOSS 0: X = 38, Y = 25
    //BOSS 1: X = 21, Y = 34
    //BOSS 2: X = 1, Y = 13
    //BOSS FINAL: X = 1, Y = 19
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
        mapa[k][39][0] = pBau0;

        mapa[k][25][38].carac = 'B';
        stpcpy(mapa[k][25][38].cor_FG, BRANCO_FG);
        mapa[k][25][38].colisao = 1;
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
        mapa[k][2][37] = pBau1;

        mapa[k][34][21].carac = 'B';
        stpcpy(mapa[k][34][21].cor_FG, BRANCO_FG);
        mapa[k][34][21].colisao = 1;
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
        mapa[k][5][33] = pBau2;

        mapa[k][13][1].carac = 'B';
        stpcpy(mapa[k][13][1].cor_FG, BRANCO_FG);
        mapa[k][13][1].colisao = 1;

        break;
      case 3:
        for (p = 0; p < LARGURAMAX; p++){
            for (q = 0; q < 15; q++)
                mapa[k][q][p] = pBuraco;
            for (q = 24; q < ALTURAMAX; q++)
                mapa[k][q][p] = pBuraco;
        }
        for (p = 0; p < ALTURAMAX; p++){
            mapa[k][p][38] = pChao;
            mapa[k][p][39] = pChao;
        }
        mapa[k][19][1].carac = 'B';
        stpcpy(mapa[k][19][1].cor_FG, BRANCO_FG);
        mapa[k][19][1].colisao = 1;
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
        system("clear");
        fflush(stdin);
        fflush(stdin);
    }

}

void criarInimigo(int zi, int xi, int yi){


    if (quantInimigos[zi] < 10){
    inimigos[zi][quantInimigos[zi]].x = xi;     //x inicial
    inimigos[zi][quantInimigos[zi]].y = yi;     //y inicial
    inimigos[zi][quantInimigos[zi]].elemento = zi+1;
    inimigos[zi][quantInimigos[zi]].tipo = 0;
    inimigos[zi][quantInimigos[zi]].classe = 5;
    inimigos[zi][quantInimigos[zi]].classe = 5;
    inimigos[zi][quantInimigos[zi]].ataque = 10 + 3 * zi;
    inimigos[zi][quantInimigos[zi]].defesa = 10 + 3 * zi;
    inimigos[zi][quantInimigos[zi]].hp = 90 + 15*zi;
    if(zi+1 == 1)
      stpcpy(inimigos[zi][quantInimigos[zi]].nome, "Elemental de Terra");
    if(zi+1 == 2)
      stpcpy(inimigos[zi][quantInimigos[zi]].nome, "Elemental de Fogo");
    if(zi+1 == 3)
      stpcpy(inimigos[zi][quantInimigos[zi]].nome, "Elemental de Água");

    quantInimigos[zi]++;
  }
}

/*
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
*/


void andarInimigo(int mundo, int index, int tentativas){
    srand(clock());
    int rand1 = rand() % 2; // 0 = x, 1 = y
    int rand2 = rand() % 2; // 0 = ++, 1 = --
    int andou = 0;
    if (rand1 == 0){
        if (rand2 == 0){
            if (inimigos[mundo][index].x != LARGURAMAX - 1 && mapa[mundo][inimigos[mundo][index].y][inimigos[mundo][index].x+1].colisao == 0){
                inimigos[mundo][index].x++;
                andou = 1;
            }
        }
        else if (rand2 == 1){
            if (inimigos[mundo][index].x != 0 && mapa[mundo][inimigos[mundo][index].y][inimigos[mundo][index].x-1].colisao == 0){
                inimigos[mundo][index].x--;
                andou = 1;
            }
        }
    }
    else if (rand1 == 1){
        if (rand2 == 0){
            if (inimigos[mundo][index].y != ALTURAMAX - 1 && mapa[mundo][inimigos[mundo][index].y+1][inimigos[mundo][index].x].colisao == 0){
                inimigos[mundo][index].y++;
                andou = 1;
            }
        }
        else if (rand2 == 1){
            if (inimigos[mundo][index].y != 0 && mapa[mundo][inimigos[mundo][index].y-1][inimigos[mundo][index].x].colisao == 0){
                inimigos[mundo][index].y--;
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
            mapa[mundo][inimigos[mundo][i].y][inimigos[mundo][i].x] = pGrama;
            break;
          case 1:
            mapa[mundo][inimigos[mundo][i].y][inimigos[mundo][i].x] = pTerra2;
            break;
          case 2:
            mapa[mundo][inimigos[mundo][i].y][inimigos[mundo][i].x] = pGelo;
            break;
          case 3:
            mapa[mundo][inimigos[mundo][i].y][inimigos[mundo][i].x] = pChao;
            break;
        }
        andarInimigo(mundo, i, 0);
        mapa[mundo][inimigos[mundo][i].y][inimigos[mundo][i].x].carac = 'X';
        mapa[mundo][inimigos[mundo][i].y][inimigos[mundo][i].x].colisao = 1;
        stpcpy(mapa[mundo][inimigos[mundo][i].y][inimigos[mundo][i].x].cor_FG, BRANCO_FG);
    }
}



void inicializarInimigo(){
    criarInimigo(0, 6, 15);
    criarInimigo(0, 23, 23);
    criarInimigo(0, 17, 7);
    criarInimigo(0, 8, 32);
    criarInimigo(1, 17, 5);
    criarInimigo(1, 31, 10);
    criarInimigo(1, 38, 1);
    criarInimigo(1, 5, 15);
    criarInimigo(1, 5, 37);
    criarInimigo(2, 11, 21);
    criarInimigo(2, 14, 12);
    criarInimigo(2, 21, 23);
    criarInimigo(2, 27, 10);
    criarInimigo(2, 33, 15);
    //BOSS 0: X = 38, Y = 25
    //BOSS 1: X = 21, Y = 34
    //BOSS 2: X = 1, Y = 13
    //BOSS FINAL: X = 1, Y = 19
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
        //mapa[1][4][34] = pTerra;
        mapa[k][3][35] = pGrama;
  //mapa[2][5][28] = pGelo;
          break;
      case 1:
          if (ale > 60 && ale < 100)
            mapa[k][i][j] = pFogo;
            mapa[k][4][34] = pTerra;
        //mapa[0][3][35] = pGrama;
        //mapa[2][5][28] = pGelo;
          break;
      case 2:
          if(0)
            mapa[k][i][j] = pFogo;
        mapa[1][4][34] = pTerra;
  mapa[0][3][35] = pGrama;
  mapa[2][5][28] = pGelo;
            break;
      case 3:
            if (ale < 15)
                mapa[k][i][j] = pBuraco;
            mapa[1][4][34] = pTerra;
  mapa[0][3][35] = pGrama;
  mapa[2][5][28] = pGelo;
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
  printf(MAGENTAC"HP: C%d/%d G%d/%d M%d/%d "RESET, grupo[0].estatos.hp,grupo[0].estatos.hpmax,grupo[1].estatos.hp, grupo[1].estatos.hpmax,grupo[2].estatos.hp, grupo[2].estatos.hpmax);
  printf(MAGENTAC"XP: %.f/%.2d "RESET, grupo[0].xp,grupo[0].xpmax);
  printf(MAGENTAC"Mundo %d\n"RESET, m);
}

void checarBau(int m){
    if (mapa[m][eu.y][eu.x].colisao == 4){
        //pegarBau(m);
        bau = m+1;
    }
    else bau = 0;
}

void printarBau(){
    if (bau != 0){
        printf("[Tesouro] Acaba de encontrar um(a) %s.\n", artefatos[bau].nome);
        printf("Classe: Curandeiro\n");
        printf("Multiplicador de cura: %.0f%%\n", artefatos[bau].cura*100 - 100);
        printf("Multiplicador de buff: %.0f%%\n", artefatos[bau].buff*100 - 100);
        printf("Multiplicador de vida: %.0f%%\n", artefatos[bau].vida*100 - 100);
        printf("%s\n", artefatos[bau].lore);
        grupo[0].estatos.hp *= artefatos[bau].vida;
        grupo[0].estatos.cura *= artefatos[bau].cura;
        grupo[0].estatos.buff *= artefatos[bau].buff;

    }
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
        checarBau(m);
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
        checarBau(m);
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
        checarBau(m);
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
      checarBau(m);
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
  stpcpy(mapa[m][eu.y][eu.x].cor_FG, BRANCO_FG);

  //spawnInimigo(m);
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
        portais[q].x = 11; portais[q].y = 30;
        portais[q].origem = 1; portais[q].destino = 2;
        mapa[q][portais[q].y][portais[q].x].carac = 'O';
        mapa[q][portais[q].y][portais[q].x].colisao = 2;
        stpcpy(mapa[q][portais[q].y][portais[q].x].cor_FG, AMARELO_FG);
        mapa[q][portais[q-1].y][portais[q-1].x].carac = 'O';
        stpcpy(mapa[q][portais[q-1].y][portais[q-1].x].cor_FG, AMARELO_FG);
        break;
      case 2:
        portais[q].x = 38; portais[q].y = 1;
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
    stpcpy(mapa[*q][eu.y][eu.x].cor_FG, BRANCO_FG);

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
    stpcpy(mapa[*m][eu.y][eu.x].cor_FG, BRANCO_FG);
    return;
  }
}

void printPos(){
    printf("\nx = %d, y = %d\n", eu.x, eu.y);
}
/*
int checarCombate(int m){
    if (mapa[m][eu.y-1][eu.x-1].carac == 'X' || mapa[m][eu.y-1][eu.x].carac == 'X' || mapa[m][eu.y-1][eu.x+1].carac == 'X'
        || mapa[m][eu.y][eu.x-1].carac == 'X' || mapa[m][eu.y][eu.x].carac == 'X' || mapa[m][eu.y][eu.x+1].carac == 'X'
        || mapa[m][eu.y+1][eu.x-1].carac == 'X' || mapa[m][eu.y+1][eu.x].carac == 'X' || mapa[m][eu.y+1][eu.x+1].carac == 'X')
        {
            return 1;
        }
    else return 0;
} */

void tiraInimigo(INIMIGO inimigoMorto, int m, int indice){
    //printf("Tirando inimigo\n");
    inimigos[m][indice] = inimigos[m][quantInimigos[m]-1];
    quantInimigos[m]--;
    switch(m){
        case 0:
            mapa[m][inimigoMorto.y][inimigoMorto.x] = pGrama;
            break;
        case 1:
            mapa[m][inimigoMorto.y][inimigoMorto.x] = pTerra2;
            break;
        case 2:
            mapa[m][inimigoMorto.y][inimigoMorto.x] = pGelo;
            break;
    }
}

void tiraBoss(INIMIGO inimigoMorto, int m){
    //printf("Tirando inimigo\n");
    switch(m){
        case 0:
            mapa[m][inimigoMorto.y][inimigoMorto.x] = pGrama;
            break;
        case 1:
            mapa[m][inimigoMorto.y][inimigoMorto.x] = pTerra2;
            break;
        case 2:
            mapa[m][inimigoMorto.y][inimigoMorto.x] = pGelo;
            break;
    }
}

void lootBoss(int m)
{
    printf("\n");
    printf("[Guerreiro] NOVO ITEM >>> %s.\n", espadas[m+1].nome);
    printf("%s\n", espadas[m+1].lore);
    printf("\n");
    printf("[Mago] NOVO ITEM >>> %s.\n",varinhas[m+1].nome);
    printf("%s\n", varinhas[m+1].lore);
    grupo[1].ataque+= espadas[m+1].dano;
    printf("\n");
    printf("[Guerreiro] + %d de ataque.\n", espadas[m+1].dano);
    grupo[1].estatos.crit+= espadas[m+1].crit;
    printf("[Guerreiro] + %d de chance para critico.\n", espadas[m+1].crit);
    grupo[1].estatos.duplo+= espadas[m+1].duplo;
    printf("[Guerreiro] + %d de chance para golpe duplo.\n", espadas[m+1].duplo);
    printf("\n");
    grupo[2].ataque+= varinhas[m+1].dano;
    printf("[Mago] + %d de ataque.\n", varinhas[m+1].dano);
    grupo[2].estatos.crit+= varinhas[m+1].crit;
    printf("[Mago] + %d de chance para critico.\n", varinhas[m+1].crit);
    grupo[2].estatos.duplo+= varinhas[m+1].duplo;
    printf("[Mago] + %d de chance para golpe duplo.\n", varinhas[m+1].duplo);
}

void checarCombate(int m){
    int v;
    for (v = 0; v < quantInimigos[m]; v++){
        if (eu.x == inimigos[m][v].x || eu.x - 1 == inimigos[m][v].x || eu.x + 1 == inimigos[m][v].x){
            if (eu.y == inimigos[m][v].y || eu.y - 1 == inimigos[m][v].y || eu.y + 1 == inimigos[m][v].y){
                if (inimigos[m][v].hp > 0){
                    printf(VERDE_CLARO_FG"\n[Combate] Inimigo >>> %s\n"RESET,inimigos[m][v].nome );
                    combate(inimigos[m][v]);
                    tiraInimigo(inimigos[m][v], m, v);
                    printf("\nDigite <ENTER> para continuar.\n");
                }
            }
        }
    }
}

void checarBoss(int m){
        if (eu.x == boss[m].x || eu.x - 1 == boss[m].x || eu.x + 1 == boss[m].x){
            if (eu.y == boss[m].y || eu.y - 1 == boss[m].y || eu.y + 1 == boss[m].y){
                if (boss[m].vivo == 1){
                    printf(VERDE_CLARO_FG"\n[Combate] Inimigo >>> %s\n"RESET, boss[m].nome);
                    combate(boss[m]);
                    if(m == 3){
                        animVitoria(3);
                    }
                    else {
                        lootBoss(m);
                        tiraBoss(boss[m], m);
                        boss[m].vivo = 0;
                        printf("\nDigite <ENTER> para continuar.\n");
                    }
                }
            }

        }
}

void inicializarBoss(){
    for (i = 0; i < 4; i++){
        stpcpy(boss[i].nome, "Boss");
        boss[i].hp = 150 + (i+1) * 35;
        boss[i].tipo = 2;
        boss[i].ataque = 50 + 7 * (i+1);
        boss[i].defesa = 20 + 10*  (i+1);
        boss[i].vivo = 1;
        switch(i){
            case 0:
                boss[i].classe = 1;
                stpcpy(boss[i].nome, "Ent");
                boss[i].x = 38;
                boss[i].y = 25;
                break;
            case 1:
                boss[i].classe = 2;
                stpcpy(boss[i].nome, "Draconato");
                boss[i].x = 21;
                boss[i].y = 34;

                break;
            case 2:
                boss[i].classe = 3;
                stpcpy(boss[i].nome, "Sereia");
                boss[i].x = 1;
                boss[i].y = 13;
                break;
            case 3:
                boss[i].classe = 4;
                stpcpy(boss[i].nome, "Leviathan");
                boss[i].x = 1;
                boss[i].y = 19;
                boss[i].ataque+=10;
                boss[i].defesa += 15;
                break;
        }
    }
    //BOSS 0: X = 38, Y = 25
    //BOSS 1: X = 21, Y = 34
    //BOSS 2: X = 1, Y = 13
    //BOSS FINAL: X = 1, Y = 19

}




//printa o mapa, dentro dele são chamadas as funções
void printarMapa(int m) {
  //inicializaMapa();
  mapa[1][4][34].colisao = 0;// = pTerra;
  mapa[0][3][35].colisao = 0;// = pGrama;
  mapa[2][5][28].colisao = 0;// = pGelo;

  while (1) {
    for(i = b; i < a; i++)
    {
      for(j = c; j < l; j++)
      {
        mapa[1][4][34].colisao = 0;//pTerra;
        mapa[0][3][35].colisao = 0;// pGrama;
        mapa[2][5][28].colisao = 0;// = pGelo;
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
    //printarStatus(m+1);
    printarBau();
    //printPos();
    //animVitoria(0);
    checarCombate(m);
    checarBoss(m);
    controla(m);
    //tiraI(m);
    //a função inicializa mapa é chamada por causa do P que é printado, para voltar a ser *
    //inicializaMapa();
    tile(m);
    inicializaPortal();
    system("clear");
    system("clear");
    mapa[1][4][34].colisao = 0;// = pTerra;
    mapa[0][3][35].colisao = 0;// = pGrama;
    mapa[2][5][28].colisao = 0;// = pGelo;
  }
}

int main()
{
  inicializarPlayer();
  inicializaMagias();
  inicializaGrupo();
  inicializaMapa();
  inicializarInimigo();
  inicializarBoss();
  inicializaItens();
  tile(0);
  //animPortal(eu.x, eu.y, 0);
  system("clear");
  mapa[1][4][34] = pTerra;
  mapa[0][3][35] = pGrama;
  mapa[2][5][28] = pGelo;
  printarMapa(0);
}
