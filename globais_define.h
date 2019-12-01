//#include "structs.h"
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
#define RESET "\x1b[0m"
#define PROBABILIDADE 20
#define ALTURA 21
#define LARGURA 21
#define ALTURAMAX 40
#define LARGURAMAX 40
#define MAPAS 4
PERSONAGEM eu, grupo[3];
PORTAL portais[3];
char direcao, lixo[40];
PONTO mapa[MAPAS][ALTURAMAX][LARGURAMAX];
int i, j, k;
int b=0, c=0, a = ALTURA, l = LARGURA;
int escolha[3][2];
INIMIGO inimigo;
MAGIA ataques[3][4];
MAGIA defesas[3][4];
