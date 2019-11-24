#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define altura 20
#define largura 20
#define nMapas 3

typedef struct _tile {
    char colisao;
    char cor;
    char sprite;
} tile;

tile mapa[nMapas][altura][largura];
char mapaAtual[altura][largura];
int x = 0, y = 0, z = 0;
char input;

void printarMapa(){
    for (int i = 0; i < altura; i++){
        for (int j = 0; j < largura; j++){
            printf("%c ", mapaAtual[i][j]);
        }
        printf("\n");
    }
}

void carregarMapa(int n){
    for (int i = 0; i < altura; i++){
        for (int j = 0; j < largura; j++){
            mapaAtual[i][j] = mapa[n][i][j].sprite;
        }
    }
}

void atualizarPosicao(){
    carregarMapa(z);
    mapaAtual[y][x] = 'P';
}

void criarMapa0(){
    for (int j = 5; j < 15; j++){
        mapa[0][5][j].sprite = 'X';
        mapa[0][5][j].colisao = 's';
    }
}

void criarMapa(int n){
    for (int i = 0; i < altura; i++){
        for (int j = 0; j < largura; j++){
            mapa[n][i][j].sprite = (char)254u;
            mapa[n][i][j].colisao = 'n';
        }
    }

    switch(n){
        case 0:
            criarMapa0();
            break;
    }
}

void andar(){
    scanf("%c", &input);
    switch(input) {
        case 'w':
            if (y != 0 && mapa[z][y - 1][x].colisao == 'n'){
                y -= 1;
            }
            break;
        case 'a':
            if (x != 0 && mapa[z][y][x - 1].colisao == 'n'){
                x -= 1;
            }
            break;
        case 's':
            if (y != altura - 1 && mapa[z][y + 1][x].colisao == 'n'){
                y += 1;
            }
            break;
        case 'd':
            if (x != largura - 1 && mapa[z][y][x + 1].colisao == 'n'){
                x += 1;
            }
            break;
    }
}



void update(){
    while(1){
        andar();
        atualizarPosicao();
        system("cls");
        printarMapa();
    }
}

int main(void){
    criarMapa(z);
    atualizarPosicao();
    printarMapa();
    update();
}
