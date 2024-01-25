#include "keyboard.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define VAZIO 0
#define PAREDE 10
#define BOMBA 11
#define BANDEIRA 12

#define ALT 12
#define LAR 14

FILE *fpm;
FILE *fps;

typedef struct {
int id;
char nome[50];
int mapa[LAR][ALT];
int masc[LAR][ALT];
int numero_de_bombas;
} save;

typedef struct {
int id;
char nome[50];
int mapa[LAR][ALT];
int masc[LAR][ALT];
int numero_de_bombas;
} personalizado;

typedef struct {
int mapa[LAR][ALT];
int masc[LAR][ALT];
} sergio;

void mostrarTitulo(void);
void zerarMatriz(int matriz[LAR][ALT]);
void preencherBombasMatriz(int matriz[LAR][ALT]);
void adicionarNumeros(int matriz[LAR][ALT]);
void preencherMascara(int masc[LAR][ALT]);
void mostrarMatriz(int matriz[LAR][ALT], int x, int y);
void atribuirDirecao(char tecla, int *x, int *y);
void liberarPosicoes(int x, int y, int masc[LAR][ALT], int mat[LAR][ALT]);
void atribuirJogada(char enter, int x, int y, int masc[LAR][ALT], int mat[LAR][ALT]);
int perder (int x, int y, int masc[LAR][ALT]);
int ganhar (int x, int y, int masc[LAR][ALT], int mat[LAR][ALT]);
void criar_mapa(void);

void mostrarTitulo(void) {
  system("clear");
  printf("------------------------------------------\n");
  printf("-------------- CAMPO MINADO --------------\n");
  printf("------------------------------------------\n");
}

void mostrarComandosERegras(void) {
  printf("\n- Pressione Enter na posição desejada para liberá-la");
  printf("\n- Pressione 'f' na posição desejada para posicionar uma bandeira");
  printf("\n- Pressione 's' para salvar o jogo e voltar ao menu");
  printf("\n- Use os direcionais para mover o cursor");
  printf("\n- Caso você libere uma bomba, perderá!");
  printf("\n- Marque todas as bombas com bandeiras para ganhar!\n\n");
}

void mostrarComandosMaker(void) {
  printf("\n- Pressione 'p' para colocar uma parede");
  printf("\n- Pressione 'b' para colocar uma bomba");
  printf("\n- Pressione enter quando tiver terminado seu mapa");
}

void zerarMatriz(int matriz[LAR][ALT]) {
  for (int a = 0; a < LAR; a++) {
    for (int b = 0; b < ALT; b++) {
      matriz[a][b] = VAZIO;
    }
  }
}

void preencherBombasMatriz(int matriz[LAR][ALT]) {
  srand(time(NULL));
  int a, b, c;
  zerarMatriz(matriz);

  a = 0;
  while (a < 12) {
    b = rand() % LAR;
    c = rand() % ALT;
    if (matriz[b][c] == 0) {
      matriz[b][c] = BOMBA;
      a++;
    }
  }
}

void adicionarNumeros(int matriz[LAR][ALT]) {
  for (int a = 0; a < LAR; a++) {
    for (int b = 0; b < ALT; b++) {
      if (matriz[a][b] == BOMBA) {
        for (int c = -1; c <= 1; c++) {
          for (int d = -1; d <= 1; d++) {
            int x = a + c;
            int y = b + d;
            if (x >= 0 && x < LAR && y >= 0 && y < ALT) {
              if (matriz[x][y] != BOMBA) {
                matriz[x][y]++;
              }
            }
          }
        }
      }
    }
  }
}

void preencherMascara(int masc[LAR][ALT]) {
  for (int a = 0; a < LAR; a++) {
    for (int b = 0; b < ALT; b++) {
      masc[a][b] = PAREDE;
    }
  }
}

void mostrarMatriz(int matriz[LAR][ALT], int x, int y) {
  for (int a = 0; a < ALT; a++) {
    for (int b = 0; b < LAR; b++) {
      if (a == x && b == y) {
        printf("❌");
      } else {
        switch (matriz[b][a]) {
        case VAZIO:
          printf("⬜");
          break;
        case PAREDE:
          printf("⬛");
          break;
        case BOMBA:
          printf("💣");
          break;
        case BANDEIRA:
          printf("🚩");
          break;
        case 1:
          printf("1️⃣ ");
          break;
        case 2:
          printf("2️⃣ ");
          break;
        case 3:
          printf("3️⃣ ");
          break;
        case 4:
          printf("4️⃣ ");
          break;
        case 5:
          printf("5️⃣ ");
          break;
        case 6:
          printf("6️⃣ ");
          break;
        case 7:
          printf("7️⃣ ");
          break;
        case 8:
          printf("8️⃣ ");
          break;
        }
      }
    }
    printf("\n");
  }
}

void mostrarMatrizSemCursor(int matriz[LAR][ALT]) {
  for (int a = 0; a < ALT; a++) {
    for (int b = 0; b < LAR; b++) {
      switch (matriz[b][a]) {
      case VAZIO:
        printf("⬜");
        break;
      case PAREDE:
        printf("⬛");
        break;
      case BOMBA:
        printf("💣");
        break;
      case BANDEIRA:
        printf("🚩");
      break;
      case 1:
        printf("1️⃣ ");
      break;
      case 2:
        printf("2️⃣ ");
      break;
      case 3:
        printf("3️⃣ ");
      break;
      case 4:
        printf("4️⃣ ");
      break;
      case 5:
        printf("5️⃣ ");
      break;
      case 6:
        printf("6️⃣ ");
      break;
      case 7:
        printf("7️⃣ ");
      break;
      case 8:
        printf("8️⃣ ");
      break;
      }
    }
    printf("\n");
  }
}

void mostrarMatrizSemCursorExplodida(int matriz[LAR][ALT]) {
  for (int a = 0; a < ALT; a++) {
    for (int b = 0; b < LAR; b++) {
      switch (matriz[b][a]) {
      case VAZIO:
        printf("⬜");
        break;
      case PAREDE:
        printf("⬛");
        break;
      case BOMBA:
        printf("💥");
        break;
      case BANDEIRA:
        printf("🚩");
      break;
      case 1:
        printf("1️⃣ ");
      break;
      case 2:
        printf("2️⃣ ");
      break;
      case 3:
        printf("3️⃣ ");
      break;
      case 4:
        printf("4️⃣ ");
      break;
      case 5:
        printf("5️⃣ ");
      break;
      case 6:
        printf("6️⃣ ");
      break;
      case 7:
        printf("7️⃣ ");
      break;
      case 8:
        printf("8️⃣ ");
      break;
      }
    }
    printf("\n");
  }
}

void atribuirDirecao(char tecla, int *x, int *y) {
  switch (tecla) {
  case '^':
    if (*x > 0) {
      *x = *x - 1;
    }
    break;

  case '|':
    if (*x < ALT - 1) {
      *x = *x + 1;
    }
    break;

  case '>':
    if (*y < LAR - 1) {
      *y = *y + 1;
    }
    break;

  case '<':
    if (*y > 0) {
      *y = *y - 1;
    }
    break;
  }
}

void liberarPosicoes(int x, int y, int masc[LAR][ALT], int mat[LAR][ALT]) {
  if (mat[x][y] == VAZIO) {
    for (int a = -1; a <= 1; a++) {
      for (int b = -1; b <= 1; b++) {
        int newX = x + a;
        int newY = y + b;

        if (newX >= 0 && newX < LAR && newY >= 0 && newY < ALT) {
          if (masc[newX][newY] == PAREDE) {
            masc[newX][newY] = mat[newX][newY];
            liberarPosicoes(newX, newY, masc, mat);
          }
        }
      }
    }
  }
}

void atribuirJogada(char enter, int x, int y, int masc[LAR][ALT], int mat[LAR][ALT]){
   masc[y][x] = mat[y][x];
   if (mat[y][x] == VAZIO){
     liberarPosicoes(y, x, masc, mat);
   }
}

void SalvarJogo(int mat_user[LAR][ALT], int masc_user[LAR][ALT], save guarda_save) {
  int a, b;
  fps = fopen("saves.bin", "a+");
  
  for (a=0;a<LAR;a++) {
    for (b=0;b<ALT;b++) {
      guarda_save.mapa[a][b] = mat_user[a][b];
      guarda_save.masc[a][b] = masc_user[a][b];
    }
  } fwrite(&guarda_save, sizeof(save), 1, fps);
  fclose(fps);
}

int perder (int x, int y, int masc[LAR][ALT]) {
  if (masc[y][x] == BOMBA) {
    return 1;
  }
  return 0;
}

int ganhar (int x, int y, int masc[LAR][ALT], int mat[LAR][ALT]) {
  int a, b, acertos = 0;
  for (a = 0; a < LAR; a++) {
    for (b = 0; b < ALT; b++) {
      if (masc[a][b] == BANDEIRA) {
        if (mat[a][b] == BOMBA) {
          acertos++;
          if (acertos == 12) {
            return 1;
          }
        }
      }
    }
  }
  return 0;
}

int ganharPersonalizado (int x, int y, int masc[LAR][ALT], int mat[LAR][ALT], int numero_de_bombas) {
  int a, b;
  for (a = 0; a < LAR; a++) {
    for (b = 0; b < ALT; b++) {
      if (masc[a][b] == BANDEIRA) {
        if (mat[a][b] == BOMBA) {
          numero_de_bombas--;
          if (numero_de_bombas == 0) {
            return 1;
          }
        }
      }
    }
  }
  return 0;
}

int getSaveId(save puts) {
  int a = 1;
  fps = fopen("saves.bin", "a+");
  while (fread(&puts, sizeof(save), 1, fps) == 1) {
    a++;
  } 
  fclose(fps);
  return a;
}

int getMapaId(personalizado guarda_mapa) {
    int a = 1;
    fpm = fopen("mapas.bin", "a+");

    if (fpm != NULL) {
        while (fread(&guarda_mapa, sizeof(personalizado), 1, fpm) == 1) {
            a++;
        }
        fclose(fpm);
    }

    return a;  // Incrementa o último ID lido para obter o próximo ID
}

void exibirSaves(save puts) {
  fps = fopen("saves.bin", "a+");
  if (fps != NULL) {
    while (fread(&puts, sizeof(save), 1, fps) == 1) {
      printf("\n%i) %s", puts.id, puts.nome);
    }
  }
  fclose(fps);
}

void exibirMapas(personalizado guarda_mapa) {
  fpm = fopen("mapas.bin", "a+");
  if (fpm != NULL) {
    while (fread(&guarda_mapa, sizeof(personalizado), 1, fpm) == 1) {
      printf("\n%i) %s", guarda_mapa.id, guarda_mapa.nome);
    }
  }
  fclose(fpm);
}

int NumeroBombas (int matriz[LAR][ALT], int numero_de_bombas) {
  int a, b;
  for (int a = 0; a < LAR; a++) {
    for (int b = 0; b < ALT; b++) {
      if (matriz[a][b] == BOMBA) {
        numero_de_bombas++;
      }
    }
  }
  return numero_de_bombas;
}

void cadastrar_mapa(personalizado m) {
  fpm = fopen("mapas.bin", "a+");
  fwrite(&m, sizeof(personalizado), 1, fpm);
  fclose(fpm);
}

int pegarMapaPorID (personalizado guarda_mapa, personalizado *joga_mapa, int id) {
  fpm = fopen("mapas.bin", "r");
  while (fread(&guarda_mapa, sizeof(personalizado), 1, fpm) == 1) {
    if (guarda_mapa.id == id) {
      *joga_mapa = guarda_mapa;
      return 1;
    }
  }
  if (id > guarda_mapa.id || id <= 0) {
    return 0;
  }
  fclose(fpm);
}

int pegarSavePorID (save guarda_save, save *joga_save, int id) {
  fps = fopen("saves.bin", "r");
  while (fread(&guarda_save, sizeof(save), 1, fps) == 1) {
    if (guarda_save.id == id) {
      *joga_save= guarda_save;
      return 1;
    }
  }
  if (id > guarda_save.id || id <= 0) {
    return 0;
  }
  fclose(fps);
}
