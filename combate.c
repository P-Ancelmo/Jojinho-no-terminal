#include "structs.h"
#include "globais_define.h"
//#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

double proteger(INIMIGO inimigo);
double defender(INIMIGO inimigo);

void atkInimigo(INIMIGO inimigo)
{
  double danofinal;
  double tempdef, tempatk;
  int ale;
  srand(clock());
  do {
    ale = rand()%3;
  } while(grupo[ale].estatos.hp <= 0);

  if(escolha[1][0]==3)
    ale=1;
  tempatk = proteger(inimigo);
  tempdef = grupo[ale].defesa + (grupo[ale].defesa*defender(inimigo));
  danofinal = tempatk *tempdef/tempdef+5;
  grupo[ale].estatos.hp -= danofinal;
  printf("O(A) %s dá %.2f de dano no %s \n",inimigo.nome,danofinal, grupo[ale].nome);
  if(grupo[ale].estatos.hp < 0)
    grupo[ale].estatos.hp=0;
  printf("%s fica com %d de HP\n",grupo[ale].nome, grupo[ale].estatos.hp);
}

void suporte()
{
  int opc;
  if(escolha[0][0]==1)
  {
    do
    {
      //printf("%d\n",escolha[0][0]);
      printf("Escolha um aliado para abençoar [1-Guerreiro ou 2-Mago]:");
      scanf("%d", &opc);
      if(opc!=1 && opc!=2)
      {
        //system("clear");
        printf("Aliado inválido!\n");
      }
    }while(opc!=1 && opc!=2);
  grupo[opc].ataque += grupo[opc].ataque/2;
  //printf("<=%d\n", opc);
  }
  if(escolha[0][0]==2)
  {
    inimigo.ataque-=inimigo.ataque*0.2;
  }
  if(escolha[0][0]==3)
  {
    do
    {
      printf("Escolha um aliado para abençoar [1-Guerreiro ou 2-Mago]:");
      scanf("%d", &opc);
      if(opc!=1 && opc!=2)
      {
        //system("clear");
        printf("Aliado inválido!\n");
      }
    }while(opc!=1 && opc!=2);
    grupo[opc].defesa += grupo[opc].defesa/2;
  }
  if(escolha[0][0]==4)
    inimigo.defesa-=inimigo.defesa/2;
  if(escolha[0][1]==1)
  {
    do
    {
      printf("Escolha um aliado para abençoar [0-Healer, 1-Guerreiro ou 2-Mago]:");
      scanf("%d", &opc);
      if(opc!=1 && opc!=2 && opc !=0)
      {
        //system("clear");
        printf("Aliado inválido!\n");
      }
    }while(opc!=1 && opc!=2 && opc!=0);
    grupo[opc].estatos.hp += grupo[opc].estatos.hp+(grupo[opc].lvl);
    if(grupo[opc].estatos.hp > grupo[opc].estatos.hpmax)
      grupo[opc].estatos.hp = grupo[opc].estatos.hpmx;
  }
  if(escolha[0][1]==2)
  {
    do
    {
      printf("Escolha um aliado para abençoar [1-Guerreiro ou 2-Mago]:");
      scanf("%d", &opc);
      if(opc!=1 && opc!= 2 && opc !=0 && grupo[opc].estatos.hp!=0)
      {
        //system("clear");
        printf("Aliado inválido!\n");
      }
    }while(opc!=1 && opc!=2);
    grupo[opc].estatos.hp = grupo[opc].estatos.hp*(0.1*grupo[opc].lvl);
  }
}

double proteger(INIMIGO inimigo)
{
  if(escolha[1][1] == 2)
    return (inimigo.ataque - (inimigo.ataque/10));
  else
    return inimigo.ataque;
}

void fisico(INIMIGO inimigo, INIMIGO *end)
{
  float peso=0;
  int dado;
  double dano = 0, danofinal = 0;

  srand(clock());

  if((escolha[1][0] == 1 && inimigo.classe == 2))
    peso = 0.5;

  if(escolha[1][0] == 1 && inimigo.classe!=4)
  {
    peso = 1;
  }
  if((escolha[1][0]==1 && inimigo.classe == 4) && (escolha[1][0] == 2 && ((inimigo.classe==1)||(inimigo.classe==3))) || (escolha[1][0] == 4 && ((inimigo.classe == 2))))
    peso=1.5;
  if(escolha[1][0] == 4 && (inimigo.classe!=2 || inimigo.classe != 4))
  {
    peso=2;
    grupo[1].estatos.hp-=grupo[1].estatos.hp*0.15;
  }

  danofinal=grupo[1].ataque+(grupo[1].ataque*peso);
  //printf("--%.2f\n", grupo[1].ataque);
  dado = rand() % 100; //rand crítico
  if((100.00 - grupo[1].estatos.crit) <= dado)
  {
    danofinal = grupo[1].ataque + (grupo[1].ataque* 1.5 * peso);
    printf("Golpe Crítico ! %.2f !\n", danofinal);
  }
  else
  {
    danofinal = grupo[1].ataque+(grupo[1].ataque*peso);
    printf("Dano do Guerreiro ! %.2f !\n", danofinal);
  }
  end->hp -= danofinal;
  double danoparcial=danofinal;
  dado = rand() % 100;
  if((100.00 - grupo[1].estatos.duplo) <= dado)
  {
    dado = rand() % 100;
    if((100.00 - grupo[1].estatos.crit) <= dado)
    {
      danofinal = (grupo[1].ataque+(grupo[1].ataque * 1.5 * peso));
      printf("Golpe Extra Crítico ! %.2f !\n", danofinal);
      end->hp -= danofinal;
    }
    else
    {
      danofinal = (grupo[1].ataque+(grupo[1].ataque * peso));
      printf("Golpe Extra ! %.2f !\n", danofinal);
      end->hp -= danofinal;
    }
  }
  if(danoparcial!=danofinal)
    printf("Dano Total do Guerreiro: %.2f \n", danoparcial+danofinal);
}

double defender(INIMIGO inimigo)
{
  //printf("Chamando defender\n");
  float peso=0;
  if(escolha[1][1]==2)
  {
    printf("%d\n", escolha[1][1]);
    if((escolha[2][1] == 1 && ((inimigo.classe == 5 && inimigo.elemento == 3) || (inimigo.classe == 3))) && (escolha[2][1] == 2 && ((inimigo.classe == 5 && inimigo.elemento == 1)||(inimigo.classe == 1))) && (escolha[2][1] == 3 && ((inimigo.classe == 5&&inimigo.elemento ==2) || (inimigo.classe == 2) || (inimigo.classe == 4)))) //vantagens
    {
      peso = 1.5;
    }
    if((escolha[2][1] == 1 && ((inimigo.classe == 5 && inimigo.elemento == 2) || (inimigo.classe == 1) || (inimigo.classe == 4))) && (escolha[2][1] == 2 && ((inimigo.classe==5 && inimigo.elemento == 3) || (inimigo.classe == 2) || (inimigo.classe == 3) || (inimigo.classe == 4)))||(escolha[2][1] == 3 &&((inimigo.classe==5&&inimigo.elemento==1)||(inimigo.classe==1)||(inimigo.classe==3)))) //desvantagens
    {
      peso = 0.5;
    }
    if(escolha[2][1]==inimigo.classe || escolha[2][1] == inimigo.elemento)
    {
      peso = 1.0;
    }
  }
  if(escolha[1][1]!=2 && escolha[1][0] == 0)
    printf("Não há escudo para encantar\n");
  return peso;
  }


  void atacar(INIMIGO inimigo, INIMIGO *end)
  {
    float peso=0;
    double dado, dano = 0, danofinal = 0;
    srand(clock());
    if((escolha[2][0] == 1 && inimigo.classe!=4) || (escolha[2][0]-1 == inimigo.classe) || (escolha[2][0]-1 == inimigo.elemento))
    {
      peso = 1.0;
    }
    if((escolha[2][0] == 1 && inimigo.classe == 4)||(escolha[2][0] == 2 && ((inimigo.classe == 5 && inimigo.elemento == 3) || (inimigo.classe == 2))) || (escolha[2][0] == 3 && ((inimigo.classe == 5 && inimigo.elemento == 1) || (inimigo.classe == 1))) || (escolha[2][0] == 4 && ((inimigo.classe == 5 && inimigo.elemento == 2) || (inimigo.classe == 2)))) //vantagens
    {
      peso = 1.5;
    }
    if((escolha[2][0] == 3 && ((inimigo.classe == 5 && inimigo.elemento == 3) || (inimigo.classe == 2) || (inimigo.classe == 3) || (inimigo.classe == 4))) || (escolha[2][0] == 2 && ((inimigo.classe == 5 && inimigo.elemento == 3) || (inimigo.classe == 1) || (inimigo.classe == 4))) || (escolha[2][0] == 4 && ((inimigo.classe == 5 && inimigo.elemento == 1) || (inimigo.classe == 1) || (inimigo.classe == 3) || (inimigo.classe == 4)))) //desvantagens
    {
      peso = 0.5;
    }

    danofinal = grupo[2].ataque+(grupo[2].ataque*peso);
    //printf("--%.2f\n", grupo[2].ataque);
    double danoparcial = danofinal;
    dado = rand() % 100; //rand crítico
    if((100.00 - grupo[2].estatos.crit) <= dado)
    {
      danofinal = grupo[2].ataque+(grupo[2].ataque*peso*1.5);
      printf("Dano Crítico do Mago ! %.2f !\n", danofinal);
    }
    else
    {
      danofinal = grupo[2].ataque+(grupo[2].ataque*peso);
      printf("Dano do Mago ! %.2f !\n", danofinal);
    }
    end->hp -= danofinal;
    dado = rand() % 100;
    if((100.00 -grupo[2].estatos.duplo) <= dado)
    {
      dado = rand() % 100;
      if((100.00 - grupo[2].estatos.crit) <= dado)
      {
        danofinal = (grupo[2].ataque+(grupo[2].ataque*peso*1.5));
        printf("Golpe Extra Crítico ! %.2f !\n", danofinal);
        end->hp -= danofinal;
      }
      else
      {
        danofinal = (grupo[2].ataque+(grupo[2].ataque*peso));
        printf("Golpe Extra ! %.2f !\n", danofinal);
        end->hp -= danofinal;
      }
    }
    if(danofinal!=danoparcial)
      printf("Dano Total Causado: %.2f \n", danofinal);
}

void inicializaMagias()
{
  for(int i = 0; i < 3; i++)
  {
    defesas[i][0].lvl = 1;
    ataques[i][0].lvl = 1;
  }
  //Guerreiro
  stpcpy(ataques[1][0].nome, "Ataque com espada");
  stpcpy(ataques[1][1].nome, "Coronhada");
  stpcpy(ataques[1][2].nome, "Rugir");
  stpcpy(ataques[1][3].nome, "Take down");
  //Mago
  stpcpy(ataques[2][0].nome, "Ataque neutro");
  stpcpy(ataques[2][1].nome, "Terra");
  stpcpy(ataques[2][2].nome, "Fogo");
  stpcpy(ataques[2][3].nome, "Água");

  stpcpy(defesas[2][0].nome, "Envelope de pedra");//defesa de agua
  stpcpy(defesas[2][1].nome, "Invólucro flamejante");//defesa de fogo
  stpcpy(defesas[2][2].nome, "Revestimento d'agua");

  //curandeiro
  stpcpy(ataques[0][0].nome, "Benção ofensiva");//buffa o ataque
  stpcpy(ataques[0][1].nome, "Maldição da fraqueza");//debuffa o atk do inimigo
  stpcpy(ataques[0][2].nome, "Benção defensiva");//buffa a defesa
  stpcpy(ataques[0][3].nome, "Maldição ao escudo");//debuffa a def do inimigo

  stpcpy(defesas[0][0].nome, "Luz curadoura");//cura um aliado
  stpcpy(defesas[0][1].nome, "Alvorada");//revive um aliado


}

void listardefesas(int i)
{
  int k;
  if(i == 0)
    k =2;
  if(i == 2)
    k=4;
  for(int j = 0; j < k; j++)
  {
    if(defesas[i][j].lvl != 0)
    {
      printf("%d- %s\n",j+1, defesas[i][j].nome);
    }
    else
      printf("%d- Habilidade bloqueada\n",j+1);
  }
  do {
    scanf("%d", &escolha[i][1]);
    if(defesas[i][escolha[i][1]-1].lvl == 0)
      printf("Habilidade bloqueada, escolha outra\n");
  } while(defesas[i][escolha[i][1]-1].lvl == 0);
}

void listarataques(int i)
{
  for(int j = 0; j < 4; j++)
  {
    if(ataques[i][j].lvl != 0)
    {
      printf("%d- %s\n",j+1, ataques[i][j].nome);
    }
    else
      printf("%d- Habilidade bloqueada\n", j+1);
  }
  do {
    scanf("%d", &escolha[i][0]);
    if(ataques[i][escolha[i][0]-1].lvl == 0)
      printf("Habilidade bloqueada, escolha outra\n");
  } while(ataques[i][escolha[i][0]-1].lvl == 0);
}

void escolhas(int i)
{
  int esc;
  if(i == 0)
  {
    do {
      printf("Clérigo HP: %d\n1- Suporte  2- Cura\n", grupo[0].estatos.hp);
      scanf("%d", &esc);
      //gets(lixo);
    } while(esc !=1 && esc!=2);
    if(esc == 1)
      listarataques(0);
    if(esc == 2)
      listardefesas(0);
    if(grupo[1].estatos.hp>0&&grupo[2].estatos.hp>0)
      suporte();
  }
  if(i == 1)
  {
    do {
      printf("Guerreiro HP: %d\n1- Ataque  2- Proteção\n",grupo[1].estatos.hp);
      scanf("%d", &esc);
    } while(esc !=1 && esc!=2);
    if(esc == 1)
      listarataques(i);
    if(esc==2)
    {
      escolha[1][1] = 2;
    }
  }
  if(i == 2)
  {
    inicio:
    do {
      printf("Mago HP: %d\n1- Ataque  2- Defesa\n", grupo[2].estatos.hp);
      scanf("%d", &esc);
    } while(esc !=1 && esc!=2);
    if(esc == 1)
      listarataques(i);
    if(esc ==2)
    {
      if(escolha[1][1]==2)
        listardefesas(i);
      if(escolha[1][1]!=2)
      {
        printf("Não há escudo para encantar\n");
        goto inicio;
      }
    }
  }
}

void upa(int i) {
  int esc;
  if(i == 0)
  {
    do{
    printf("Deseja aprender Suporte[1] ou Cura[2] ?\n");
    scanf("%d", &esc);
    }while(esc!=1 && esc!=2)
  }
  if(i == 2)
  {
    do{
    printf("Deseja aprender Ataque[1] ou Proteção[2] ?\n");
    scanf("%d", &esc);
  }while(esc!=1 && esc!=2)
  }
  printf("Qual dessas deseja aprender ?\n");
  for(int j = 0; j < 4; j++)
  {
    if(esc ==1){
      if(ataques[i][j].lvl == 0)
      {
        printf("%d- %s\n",j+1, ataques[i][j].nome);
      }
    }
    if(esc ==2)
    {
      if(defesas[i][j].lvl == 0)
      {
        printf("%d- %s\n",j+1, defesas[i][j].nome);
      }
    }
  }
  do {
    scanf("%d", &escolha[i][esc-1]);
    if(escolha[i][esc-1] > 4 && ataques[i][escolha[i][esc-1]-1].lvl != 0)
      printf("Habilidade inválida, escolha outra\n");
  } while(escolha[i][esc-1] > 4 && ataques[i][escolha[i][esc-1]-1].lvl != 0);

}

void combate(INIMIGO inimigo)
{
  int deftemp[3],atktemp[3],i;
  for(i = 0; i < 3; i++)
  {
    deftemp[i] = grupo[i].defesa;
    atktemp[i] = grupo[i].ataque;
  }
  while(grupo[1].estatos.hp > 0 || grupo[2].estatos.hp > 0)
  {
    for(int i = 0; i <3; i++)
    {
      escolha[i][0] = 0;
      escolha[i][1]=0;
      if(grupo[i].estatos.hp > 0)
        escolhas(i);
    }
    //suporte();
    if(inimigo.hp > 0)
    {
      //printf("%d\n", inimigo.hp);
      if(escolha[1][0]!=0)
        fisico(inimigo, &inimigo);
      if(escolha[2][0]!=0)
        atacar(inimigo, &inimigo);
      //defender(inimigo);
      atkInimigo(inimigo);

    }
    if(inimigo.hp <= 0)
    {
      printf("Você venceu a luta\n");
      for(int i = 0; i < 3; i++)
      {
        if(inimigo.tipo == 0)
          grupo[i].xp+=30;
        if(inimigo.tipo == 1)
          grupo[i].xp+=90;
        if(inimigo.tipo == 2)
          grupo[i].xp+=120;
        if(grupo[i].xp >=  grupo[i].xpmax)
        {
          grupo[i].lvl++;
          grupo[i].xp -= grupo[i].xpmax;
          upa(i);
        }
      }

      //loot();
      return;
    }
    else
    printf("HP inimigo: %d\n", inimigo.hp);
    for(i = 0; i < 3;i++)
    {
      grupo[i].ataque = atktemp[i];
      grupo[i].defesa = deftemp[i];
    }
    if(grupo[1].estatos.hp <= 0 && grupo[2].estatos.hp <= 0)
    {
      printf("Sua equipe foi morta pelo(a) %s\n", inimigo.nome);
      return;
    }

  }
  printf("Sua equipe foi morta pelo(a) %s\n", inimigo.nome);
}
