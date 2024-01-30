typedef struct{
  char nome[41];
  int raridade; // 0 = Normal (Verde) // 1 = Mágico (Azul) // 2 = Épico (Roxo) // 3 = Lendário (Dourado)
  int dano; // + Dano
  int crit; // + Chance de crítico
  int duplo; // + Chance de ataque duplo
  char lore[150];
}VARINHA;

typedef struct
{
  char nome[41];
  int raridade; // 0 = Normal (Verde) // 1 = Mágico (Azul) // 2 = Épico (Roxo) // 3 = Lendário (Dourado)
  int dano; // + Dano
  int crit; // + Chance de crítico
  int duplo; // + Chance de ataque duplo
  char lore[150];
}ESPADA;

typedef struct
{
  char nome[41];
  int raridade; // 0 = Normal (Verde) // 1 = Mágico (Azul) // 2 = Épico (Roxo) // 3 = Lendário (Dourado)
  float cura;
  float buff;
  float vida;
  char lore[150];
}ARTEFATO;

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
	int vivo;
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
  int cura;
  int buff;
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
