

typedef struct  {
	char cor_FG[12];
	char cor_BG[12];
	char carac;
	int colisao;// 1 - sim 0 - não
}PONTO;

typedef struct
{
  char nome [41];
	int classe; // 1 - ENT 2 - Draconato 3 - Sereia 4 - Dragão 5 -elementais 6- bruxo
  double hptemp; //com redução de dano em double, hp precisa ser também
  int hp;
  int drop;
  char elemento;
  int tipo; //mob - miniBoss - Boss
  int ataque;
  int defesa;
	int x;
	int y;
	int z;
}INIMIGO;

// que tal tirar defesa?

typedef struct{
	int x;
	int y;
} POSICAO;

typedef struct
{
  int esquivar; // Chance de desviar de um ataque
  int duplo; // Chance de aplicar um ataque duplo
  int crit; // Chance de aplicar um ataque crítico
	float ataque;
  float defesa; // Fórmula: Dano recebido = Defesa / Defesa + 5
  int defesatemp; // Fórmula: Dano recebido = defesatemp / defesatemp + 4 (Para lutas)
  int hp; //Sugestão: 20 hp inicial
	int hpmax;
  int hptemp;
}STATS;

// Idea: Defesatemp decai um ponto até se igular a defesa.

typedef struct
{
  int magia [4];
  int tunica;
  int varinha;
}INVENTARIO;

typedef struct
{
  char nome [21];
  STATS estatos;
  INVENTARIO inventario;
	float ataque;
	float defesa;
 	float xp;
  int xpmax;
  int lvl;
  int x;
  int y;
	int z;
}PERSONAGEM;

typedef struct
{
	char nome[41];

	int tipo;//
	int elemento; //qual elemento da magia (0-3)
  int lvl; //entre 1 e 3
  int vantagem; //contra quem possui bônus
  int desvantagem; //contra quem possui redução
  int dano;
}MAGIA;

typedef struct
{
	int x;
	int y;
  int destino; //para qual mundo vai (0 ou 1)
  int origem; //de qual mundo parte (0-3)
}PORTAL;

typedef struct
{
  char nome [41];
  int raridade; // 1 = Normal (Azul) // 2 = Épico (Roxo) // 3 = Lendário (Dourado)
  int hp; // + Vida
  int defesa; // + Defesa
  int esquivar; // + Chance de desviar de um ataque
  char lore[150];
}TUNICA;

typedef struct
{
  char nome[41];
  int raridade; // 0 = Normal (Verde) // 1 = Mágico (Azul) // 2 = Épico (Roxo) // 3 = Lendário (Dourado)
  int dano; // + Dano
  int crit; // + Chance de crítico
  int duplo; // + Chance de ataque duplo
  char lore[150];
}VARINHA;

// TODOS OS ITENS
/*
varinha vect[10];
vect[0].nome = "Galho Regular";
vect[0].raridade = 0;
vect[0].dano = 0;
vect[0].crit = 0;
vect[0].duplo = 0;
vect[0].lore = "Aclamado pelos arcanos por sua leveza, trata-se de um artefato extraordinariamente normal.";

vect[1].nome = "Cajado de Silverfield";
vect[1].raridade = 1;
vect[1].dano = 2;
vect[1].crit = 0;
vect[1].duplo = 0;
vect[1].lore = "Proveniente das florestas coníferas, possui adornos selados do raríssimo integrálio.";

vect[2].nome = "Varinha dos Ventos Uivantes";
vect[2].raridade = 1;
vect[2].dano = 0;
vect[2].crit = 0;
vect[2].duplo = 15;
vect[2].lore = "O portador promove um agitadíssimo baile entre as árvores, que chacoalham freneticamente.";

vect[3].nome = "Prisma Cristalino";
vect[3].raridade = 1;
vect[3].dano = 0;
vect[3].crit = 20;
vect[3].duplo = 0;
vect[3].lore = "Seu formato único permite a concretização da ruína de qualquer infortunado.";

vect[4].nome = "Bastão de Euclides";
vect[4].raridade = 2;
vect[4].dano = 4;
vect[4].crit = 25;
vect[4].duplo = 0;
vect[4].lore = "Uma vez, perguntaram a um sábio: 'Qual é o número mais poderoso?' E ele respondeu: '2.6'.";
*/
//#include "structs.h"
