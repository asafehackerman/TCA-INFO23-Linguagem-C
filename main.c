#include "campo_minado.h"

int main(void) {
  int a, b, fim_sistema = 0, fim_jogo = 0, fim_mapa = 0, x = 0, y = 0, flag = 0, id;
  personalizado guarda_mapa, joga_mapa;
  save guarda_save, joga_save, guarda_save_save;
  sergio ale;
  int sla;
  int nao_tenho_mais_ideia_de_nome = 0;

  guarda_mapa.numero_de_bombas = 0;
  
  // Começa o sistema
  while (fim_sistema == 0) {
    mostrarTitulo();
    printf("\n1) Jogo Novo");
    printf("\n2) Continuar Jogo Salvo");
    printf("\n3) Criar Mapa");
    printf("\n0) Sair");
    printf("\n\n> ");
    fflush(stdin);
    scanf("%i", &a);
    getch();

    switch (a) {
      case 1: // Jogar
        mostrarTitulo();
        printf("\n1) Jogar (Mapa Aleatório)");
        printf("\n2) Jogar (Mapa Personalizado)");
        printf("\n\n> ");
        fflush(stdin);
        scanf("%i", &b);
        getch();

        if (b == 1) { // mapa aleatório
          preencherBombasMatriz(ale.mapa);
          adicionarNumeros(ale.mapa);
          preencherMascara(ale.masc);
          fim_jogo = 0;
          while (fim_jogo == 0) {
            system("clear");
            mostrarComandosERegras();
            mostrarMatriz(ale.masc, x, y);
            
            // jogada
            char tecla = getTecla();
            // libera posição
            if (tecla == '\n') {
              atribuirJogada(tecla, x, y, ale.masc, ale.mapa);
            // coloca bandeira 
            } else if (tecla == 'f') {
              ale.masc[y][x] = BANDEIRA;
            } 
            // salva o jogo
            else if (tecla == 's') {
                system("clear");
                printf("\n\nDigite o nome do seu mapa (limite de 50 caracteres)");
                printf("\n> ");
                fflush(stdin);
                gets(guarda_save.nome);
                guarda_save.id = getSaveId(guarda_save);
                SalvarJogo(ale.mapa, ale.masc, guarda_save);
                printf("\n\nMapa salvo com sucesso!");
                fflush(stdout);
                sleep(3);
                fim_jogo++;
            }
            // move o cursor
            else {
              atribuirDirecao(tecla, &x, &y);
            }
            // verifica vitória
            int vitoria = ganhar(x, y, ale.masc, ale.mapa);
            // atribui vitória
            if (vitoria) {
              system("clear");
              printf("\n\n🎉🎊🎉🎊 PARABÉNS!! 🎉🎊🎉🎊\n");
              printf("🎉🎊🎉🎊 Você Venceu!! 🎉🎊🎉🎊\n\n\n");
              mostrarMatrizSemCursor(ale.mapa);
              fflush(stdout);
              sleep(5);
              fim_jogo++;
            }
            // verifica derrota
            int derrota = perder(x, y, ale.masc);
            // atribui derrota
            if (derrota) {
              system("clear");
              printf("\n\n💥🔥💥🔥 KABOOOOOOM!!!! 💥🔥💥🔥\n");
              printf("🔥💥🔥💥 Você Perdeu!! 🔥💥🔥💥\n\n\n");
              mostrarMatrizSemCursorExplodida(ale.mapa);
              fflush(stdout);
              sleep(3);
              fim_jogo++;
            }
          }
        }
        
        else if (b == 2) { // mapa personalizado
          nao_tenho_mais_ideia_de_nome = 0;
          while (nao_tenho_mais_ideia_de_nome == 0) {
            system("clear");
            exibirMapas(guarda_mapa);
            printf("\n\nDigite o ID do mapa que você quer jogar: ");
            scanf("%i", &id);
            getchar();
            nao_tenho_mais_ideia_de_nome = pegarMapaPorID(guarda_mapa, &joga_mapa, id);
          }
          fim_jogo = 0;
          x = y = 0;  // Inicialize as posições do cursor
          while (fim_jogo == 0) {
            system("clear");
            printf("\n\nNúmero de bombas: %i", joga_mapa.numero_de_bombas);
            mostrarComandosERegras();
            mostrarMatriz(joga_mapa.masc, x, y);

            // jogada
            char tecla = getTecla();

            // libera posição
            if (tecla == '\n') {
                atribuirJogada(tecla, x, y, joga_mapa.masc, joga_mapa.mapa);
            }
            // coloca bandeira
            else if (tecla == 'f') {
                joga_mapa.masc[y][x] = BANDEIRA;
            }
            // salva o jogo
            else if (tecla == 's') {
                system("clear");
                printf("\n\nDigite o nome do seu save (limite de 50 caracteres)");
                printf("\n> ");
                fflush(stdin);
                gets(guarda_save.nome);
                guarda_save.id = getSaveId(guarda_save);
                guarda_save.numero_de_bombas = joga_mapa.numero_de_bombas;
                SalvarJogo(joga_mapa.mapa, joga_mapa.masc, guarda_save);
                printf("\n\nMapa salvo com sucesso!");
                fflush(stdout);
                sleep(3);
                fim_jogo++;
            }
            // move o cursor
            else {
                atribuirDirecao(tecla, &x, &y);
            }

            // verifica vitória
            int vitoria = ganharPersonalizado(x, y, joga_mapa.masc, joga_mapa.mapa, joga_mapa.numero_de_bombas);

            // atribui vitória
            if (vitoria) {
              fim_jogo++;  // Termina o loop
              system("clear");
              printf("\n\n🎉🎊🎉🎊 PARABÉNS!! 🎉🎊🎉🎊\n");
              printf("🎉🎊🎉🎊 Você Venceu!! 🎉🎊🎉🎊\n\n\n");
              mostrarMatrizSemCursor(joga_mapa.mapa);
              fflush(stdout);
              sleep(3);
            }

            // verifica derrota
            int derrota = perder(x, y, joga_mapa.masc);

            // atribui derrota
            if (derrota) {
                fim_jogo++;  // Termina o loop
                system("clear");
                printf("\n\n💥🔥💥🔥 KABOOOOOOM!!!! 💥🔥💥🔥\n");
                printf("🔥💥🔥💥 Você Perdeu!! 🔥💥🔥💥\n\n\n");
                mostrarMatrizSemCursorExplodida(joga_mapa.mapa);
                fflush(stdout);
                sleep(3);
            }
          }
        }

        else { // inválido
          system("clear");
          printf("\nOpção inválida");
          fflush(stdout);
          sleep(2);
        }
      break;
      case 2: // Continuar nos saves
        nao_tenho_mais_ideia_de_nome = 0;
        while (nao_tenho_mais_ideia_de_nome == 0) {
          system("clear");
          exibirSaves(guarda_save);
          printf("\n\nDigite o ID do save que você quer jogar: ");
          scanf("%i", &id);
          getchar();
          nao_tenho_mais_ideia_de_nome = pegarSavePorID(guarda_save, &joga_save, id);
        }
        fim_jogo = 0;
        x = y = 0;  // Inicialize as posições do cursor
        while (fim_jogo == 0) {
          system("clear");
          printf("\n\nNúmero de bombas: %i", joga_save.numero_de_bombas);
          mostrarComandosERegras();
          mostrarMatriz(joga_save.masc, x, y);

          // jogada
          char tecla = getTecla();

          // libera posição
          if (tecla == '\n') {
            atribuirJogada(tecla, x, y, joga_save.masc, joga_save.mapa);
          }
            
          // coloca bandeira
          else if (tecla == 'f') {
            joga_save.masc[y][x] = BANDEIRA;
          }
      
          // salva o jogo
          else if (tecla == 's') {
            system("clear");
            printf("\n\nDigite o nome do seu save (limite de 50 caracteres)");
            printf("\n> ");
            fflush(stdin);
            gets(guarda_save.nome);
            guarda_save.id = getSaveId(guarda_save);
            guarda_save.numero_de_bombas = joga_save.numero_de_bombas;
            SalvarJogo(joga_save.mapa, joga_save.masc, guarda_save);
            printf("\n\nMapa salvo com sucesso!");
            fflush(stdout);
            sleep(3);
            fim_jogo++;
          }
           
          // move o cursor
          else {
            atribuirDirecao(tecla, &x, &y);
          }

          // verifica vitória
          int vitoria = ganharPersonalizado(x, y, joga_save.masc, joga_save.mapa, joga_save.numero_de_bombas);

          // atribui vitória
          if (vitoria) {
            fim_jogo++;  // Termina o loop
            system("clear");
            printf("\n\n🎉🎊🎉🎊 PARABÉNS!! 🎉🎊🎉🎊\n");
            printf("🎉🎊🎉🎊 Você Venceu!! 🎉🎊🎉🎊\n\n\n");
            mostrarMatrizSemCursor(joga_save.mapa);
            fflush(stdout);
            sleep(3);
          }

          // verifica derrota
          int derrota = perder(x, y, joga_save.masc);

          // atribui derrota
          if (derrota) {
              fim_jogo++;  // Termina o loop
              system("clear");
              printf("\n\n💥🔥💥🔥 KABOOOOOOM!!!! 💥🔥💥🔥\n");
              printf("🔥💥🔥💥 Você Perdeu!! 🔥💥🔥💥\n\n\n");
              mostrarMatrizSemCursorExplodida(joga_save.mapa);
              fflush(stdout);
              sleep(3);
          }
        }
      break;
      case 3: // Criar mapa
        mostrarTitulo();
        exibirMapas(guarda_mapa);
        printf("\n\nDigite o nome do seu mapa (limite de 50 caracteres)");
        printf("\n> ");
        fflush(stdin);
        gets(guarda_mapa.nome);
        zerarMatriz(guarda_mapa.mapa);
        fim_mapa = 0;
        guarda_mapa.numero_de_bombas = 0;
        x = y = 0;  // Reiniciar a posição do cursor
        while (fim_mapa == 0) {
            system("clear");
            mostrarComandosMaker();
            printf("\n\n\n");
            mostrarMatriz(guarda_mapa.mapa, x, y);
          
  
            // captura a tecla
            char tecla = getTecla();
            if (tecla == '\n') { // termina a criação do mapa
                system("clear");
                adicionarNumeros(guarda_mapa.mapa); // coloca a verificação dos números
                preencherMascara(guarda_mapa.masc);
                mostrarMatrizSemCursor(guarda_mapa.mapa); // mostra a matriz, mas sem o cursor
                guarda_mapa.id = getMapaId(guarda_mapa);
                guarda_mapa.numero_de_bombas = NumeroBombas(guarda_mapa.mapa, guarda_mapa.numero_de_bombas);
                printf("\n\nNúmero de bombas: %i", guarda_mapa.numero_de_bombas);
                fflush(stdout);
                sleep(5); // espera por 5 segundos
                fim_mapa++;
            } else if (tecla == 'b') { // coloca bomba
                guarda_mapa.mapa[y][x] = BOMBA;
            } else if (tecla == 'p') { // coloca parede
                guarda_mapa.mapa[y][x] = VAZIO;
            } else { // se move pelo mapa
                atribuirDirecao(tecla, &x, &y);
            }
          }
        cadastrar_mapa(guarda_mapa);
        fflush(stdout);
        sleep(2);
      break;

      case 0: // Sair
        system("clear");
        printf("\n\t\tObrigado por jogar!");
        printf("\n\t\t\t\tMade by Asafe");
        return 0;
      break;
      default: // Opção Inválida
        system("clear");
        printf("\nOpção inválida");
        fflush(stdout);
        sleep(2);
      break;
    }
  }
  return 0;
}