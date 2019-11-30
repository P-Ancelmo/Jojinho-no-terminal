typedef struct
{
  char nome [41]
  double hptemp; //com redução de dano em double, hp precisa ser também
  int hp;
  int drop;
  int elemento;
  int tipo; //mob - miniBoss - Boss
  int ataque;
}inimigo;

typedef struct
{
  char nome [21]
  struct stats;
  struct inventario;
  int xp;
  int xpmax;
  int lvl;
  int x;
  int y;
}personagem;

typedef struct
{
  int esquivar; // Chance de desviar de um ataque
  float duplo; // Chance de aplicar um ataque duplo
  float crit; // Chance de aplicar um ataque crítico
  int defesa; // Fórmula: Dano recebido = Defesa / Defesa + 5
  double defesatemp; // Fórmula: Dano recebido = defesatemp / defesatemp + 4 (Para lutas)
  int hp; //Sugestão: 20 hp inicial
  int hptemp;
}stats;

// Idea: Defesatemp decai um ponto até se igular a defesa.

typedef struct
{
  int magiaatk [4];
  int magiadef [4];
  int tunica;
  int varinha;
}inventario;

typedef struct
{
  int tipo; //se são de ataque ou defesa (0 ou 1)
  int elemento; //qual elemento da magia (0-3)
  int lvl; //entre 0 e 3
  int dano;
  int defesa;
}magia;

typedef struct
{
  int destino; //para qual mundo vai (0 ou 1)
  int origem; //de qual mundo parte (0-3)
}portal;

typedef struct
{
  char nome [41]
  int raridade; // 1 = Normal (Azul) // 2 = Épico (Roxo) // 3 = Lendário (Dourado)
  int hp; // + Vida
  float defesa; // + Defesa
  float esquivar; // + Chance de desviar de um ataque
  char lore[150];
}tunica;

typedef struct
{
  char nome[41];
  int raridade; // 0 = Normal (Verde) // 1 = Mágico (Azul) // 2 = Épico (Roxo) // 3 = Lendário (Dourado)
  float dano; // + Dano
  float crit; // + Chance de crítico
  float duplo; // + Chance de ataque duplo
  char lore[150];
}varinha;

//CALCULOS DE stats EXTRA
personagem.stats.defesa
personagem.stats.crit
personagem.stats.esquivar
personagem.stats.duplo
personagem.stats.hp

// TODOS OS ITENS

inimigo mob[16]
magia ataque[12];
magia defesa[12];
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

vect[5].nome = "Varinha de Carmichael";
vect[5].raridade = 2;
vect[5].dano = 0;
vect[5].crit = 56.1;
vect[5].duplo = 11.05;
vect[5].lore = "Ainda é possível ouvir os gritos de Fermat ecoando pela aura desse artefato.";

vect[6].nome = "Hipercubo de Karnaugh";
vect[6].raridade = 2;
vect[6].dano = 3;
vect[6].crit = 0;
vect[6].duplo = 28;
vect[6].lore = "Armazena conhecimento aplicado de uma antiga civilização avançada: os booleanos.";

vect[7].nome = "Cetro de Ritchie";
vect[7].raridade = 3;
vect[7].dano = 10;
vect[7].crit = 45;
vect[7].duplo = 20;
vect[7].lore = "Emana uma aura nunca antes vista.";

vect[8].nome = "Orbe Abeliano";
vect[8].raridade = 3;
vect[8].dano = 5;
vect[8].crit = 100;
vect[8].duplo = 10;
vect[8].lore = "Forjado por forças entrópicas, independe de qualquer ordem.";

vect[9].nome = "Cajado da Recursão";
vect[9].raridade = 3;
vect[9].dano = 8;
vect[9].crit = 10;
vect[9].duplo = 100;
vect[9].lore = "Golpe em dobro. Sempre.";

tunica vet[9];

vet[0].nome = "";
vet[0].raridade = 1;
vet[0].hp = 8;
vet[0].defesa = 10;
vet[0].esquivar = 100;
vet[0].lore = "Golpe em dobro. Sempre.";
