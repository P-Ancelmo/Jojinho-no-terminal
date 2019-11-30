void inimigo(int mob);
{
  double danofinal;
  danofinal = mob[mob].ataque * personagem.stats.tempdef/personagem.stats.tempdef+5;
  personagem.stats.hptemp -= danofinal;
  printf(“Golpe Inimigo ! %d !\n“, dano*peso);
}

void defender(int mob);
{
  float peso;
  if((escolha == 1 && mob[mob].elemento == 3) || (escolha == 2 && mob[mob].elemento == 1) || (escolha == 3 && mob[mob].elemento == 2)) //vantagens
  {
    peso = 1.5;
  }
  if((escolha == 3 && mob[mob].elemento == 1) || (escolha == 1 && mob[mob].elemento == 2) || (escolha == 2 && mob[mob].elemento == 3)) //desvantagens
  {
    peso = 0.5;
  }
  if((escolha == 1 && mob[mob].elemento == 1) || (escolha == 2 && mob[mob].elemento == 2) || (escolha == 3 && mob[mob].elemento == 3) || (escolha == 0 && mob[mob].elemento == 1) || (escolha == 0 && mob[mob].elemento == 2) || (escolha == 0 && mob[mob].elemento == 3)
  {
    peso = 1.0;
  }
  personagem.stats.defesatemp = personagem.stats.defesa + (defesa[personagem.inventario.magiadef[escolha]].defesa*peso);
}

void atacar(int mob);
{
  float peso;
  double dado, dano = 0, danofinal = 0;
  if((escolha == 1 && mob[mob].elemento == 3) || (escolha == 2 && mob[mob].elemento == 1) || (escolha == 3 && mob[mob].elemento == 2)) //vantagens
  {
    peso = 1.5;
  }
  if((escolha == 3 && mob[mob].elemento == 1) || (escolha == 1 && mob[mob].elemento == 2) || (escolha == 2 && mob[mob].elemento == 3)) //desvantagens
  {
    peso = 0.5;
  }
  if((escolha == 1 && mob[mob].elemento == 1) || (escolha == 2 && mob[mob].elemento == 2) || (escolha == 3 && mob[mob].elemento == 3) || (escolha == 0 && mob[mob].elemento == 1) || (escolha == 0 && mob[mob].elemento == 2) || (escolha == 0 && mob[mob].elemento == 3)
  {
    peso = 1.0;
  }
  dado = rand() % 100.00; //rand crítico
  if((100.00 - personagem.stats.crit) =< dado =< 100.00)
  {
    danofinal += dano * 1.5 * peso;
    printf(“Golpe Crítico ! %d !\n“, dano*1.5*peso);
  }
  else
  {
    danofinal += dano*peso;
    printf(“Golpe Comum ! %d !\n“, dano*peso);
  }
  dado = rand() % 100.00;
  if((100.00 - personagem.stats.duplo) =< dado =< 100.00)
  {
    dado = rand() % 100.00;
    if((100.00 - personagem.stats.crit) =< dado =< 100.00)
    {
      danofinal += dano * 1.5 * peso;
      printf(“Golpe Extra Crítico ! %d !\n“, dano*1.5*peso);
    }
    else
    {
      danofinal += dano * peso;
      printf(“Golpe Extra ! %d !\n“, dano);
    }
  }
  printf(“Dano Total Causado: %d \n“, danofinal);
  mob[mob].hptemp -= danofinal;
}

void listardefesas();
{
  printf(“Magia de Defesas:\n”);
  if(ataque[personagem.inventario.magiadef[0]].lvl != 0)
  {
    printf(“Neutra [0]\n”);
  }
  if(ataque[personagem.inventario.magiadef[1]].lvl != 0)
  {
    printf(“Terra [1]\n”);
  }
  if(ataque[personagem.inventario.magiadef[2]].lvl != 0)
  {
    printf(“Fogo [2]\n”);
  }
  if(ataque[personagem.inventario.magiadef[3]].lvl != 0)
  {
    printf(“Água [3]\n”);
  }
}

void listarataques();
{
  printf(“Magia de Ataques:\n”);
  if(ataque[personagem.inventario.magiaatk[0]].lvl != 0)
  {
    printf(“Neutra [0]\n”);
  }
  if(ataque[personagem.inventario.magiaatk[1]].lvl != 0)
  {
    printf(“Terra [1]\n”);
  }
  if(ataque[personagem.inventario.magiaatk[2]].lvl != 0)
  {
    printf(“Fogo [2]\n”);
  }
  if(ataque[personagem.inventario.magiaatk[3]].lvl != 0)
  {
    printf(“Água [3]\n”);
  }
}

void combate(int mob);
{
  while(personagem.stats.hptemp != 0)
  {
    if(personagem.stats.def != personagem.stats.tempdef)
    {
      personagem.stats.tempdef = (personagem.stats.tempdef - personagem.stats.def) - 1;
    }
    int escolha;
    printf(“Defender [0] ou Atacar [1]?\n”);
    scanf(“%d”, &escolha);
    while(escolha != 0 && escolha != 1)
    {
        printf(“Tipo de ataque inexistente. Tente denovo !\n”);
        scanf(“%d”, &escolha);
    }
    if(escolha == 0);
    {
      listardefesas();
      scanf(“%d”, &escolha);
      while(escolha != 0 && escolha != 1 && escolha != 2 && escolha != 3)
      {
          printf(“Tipo de ataque inexistente. Tente denovo !\n”);
          scanf(“%d”, &escolha);
      }
      while(defesa[personagem.inventario.magiadef[escolha]].lvl == 0)
      {
          printf(“Magia Trancada. Tente outra !\n”);
          scanf(“%d”, &escolha);
      }
      defender(mob[mob]);
    }
    if(escolha == 1);
    {
      listarataques();
      scanf(“%d”, &escolha);
      while(escolha != 0 && escolha != 1 && escolha != 2 && escolha != 3)
      {
          printf(“Tipo de ataque inexistente. Tente denovo !\n”);
          scanf(“%d”, &escolha);
      }
      while(ataque[personagem.inventario.magiaatk[escolha]].lvl == 0)
      {
          printf(“Magia Trancada. Tente outra !\n”);
          scanf(“%d”, &escolha);
      }
      atacar(mob[mob]);
    }
    if(mob[mob].hptemp == 0)
    {
      loot(mob[mob]);
      break;
    }
    else
    {
      inimigo(mob[mob]);
      if(personagem.stats.hptemp == 0);
      {
        printf(“Seu personagem foi morto em combate.\n”);
        menu(); //time.h para contar um tempinho e depois ir ao menu?
        break;
      }
    }
  }
}
