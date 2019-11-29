#include <stdio.h>
#include <string.h>
#include "structs.h"
MAGIA ataques[3][4];
MAGIA defesas[3][4];
int esc, esco[3];
PERSONAGEM grupo[3];

void iniciaAtaques()
{
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      ataques[i][j].lvl = 0;
      defesas[i][j].lvl = 0;
    }
  }
  ataques[0][0].lvl = 1;
  stpcpy(ataques[0][0].nome, "Ataque Basico");
  ataques[1][0].lvl = 1;
  ataques[2][0].lvl = 1;
  defesas[0][0].lvl = 1;
  defesas[1][0].lvl = 1;
  defesas[2][0].lvl = 1;
}

int atk(int i, int mob)
{
  printf("\nAtaques:\n");
  for(int j = 0; j < 4; j++)
  {
    printf("%d - ", j+1);
    if(ataques[i][j].lvl > 0)
      printf("%s\n", ataques[i][j].nome);
    else
      printf("\n");
  }
  scanf("%d", &esc);
  esco[i] = esc;
  return esc;
}

void def(int i)
{
  for(int j = 0; j < 4; j++)
  {
    printf("%d -", j);
    if(defesas[i][j].lvl > 0)
      printf("%s\n", defesas[i][j].nome);
  }
}

void combate()
{
  while(grupo.estatos.hp != 0)
  {

    printf("Guerreiro:\n1 - atk  2 - def\n");
    scanf("%d", &esc);
    switch (esc)
    {
      case 1:
        atk(0);
        if(inim.hp == 0)
          return
        break;
      case 2:
        def(0);
        break;
    }
    printf("Mago:\n1 - atk  2 - def\n");
    scanf("%d", &esc);
    switch (esc)
    {
      case 1:
        atk(1);
        break;
      case 2:
        def(1);
        break;
    }
    printf("Arqueiro:\n1 - atk  2 - def\n");
    scanf("%d", &esc);
    switch (esc)
    {
      case 1:
        atk(2);
        break;
      case 2:
        def(2);
        break;
    }
  }
}

int main()
{
  grupo.estatos.hp = 1;
  iniciaAtaques();
  combate();
}
