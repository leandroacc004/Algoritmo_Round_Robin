// Online C compiler to run C program online
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Se le pasa una lista y un numero n, para buscar en la lista, retorna numero
// minimo
int minimo(int lista[], int n) {
  int minimo = lista[0];
  for (int i = 1; i < n; i++) {
    if (lista[i] < minimo) {
      minimo = lista[i];
    }
  }
  return minimo; // Valor
}

// retorna numero maximo
int maximo(int lista[], int n) {
  int maximo = lista[0];
  for (int i = 1; i < n; i++) {
    if (lista[i] > maximo) {
      maximo = lista[i];
    }
  }
  return maximo;
}

// Retorna la posición de un valor
int *posiciones(int *lista, int tamano, int valor, int *numPosiciones) {
  int *posiciones; // Puntero para almacenar las posiciones
  int contador = 0;
  // Contar cuántas veces aparece el valor en la lista
  for (int i = 0; i < tamano; i++) {
    if (lista[i] == valor) {
      contador++;
    }
  }
  if (contador > 0) {
    // Asignar memoria para almacenar las posiciones encontradas
    posiciones = (int *)calloc(contador, sizeof(int));
    if (posiciones == NULL) {
      printf("Error de asignacion de memoria.\n");
      exit(EXIT_FAILURE);
    }
    // Almacenar las posiciones de los valores iguales al valor dado
    contador = 0;
    for (int i = 0; i < tamano; i++) {
      if (lista[i] == valor) {
        posiciones[contador] = i;
        contador++;
      }
    }
  }
  *numPosiciones = contador; // Guardar la cantidad de posiciones encontradas
  return posiciones;         // Retornar el puntero con las posiciones
}

int *tiempo_llegada_minimo(int lista_llegada[], int tiempo_espera[], int n,
                           int *num_posiciones) {
  int contador = 0;
  int max = maximo(tiempo_espera, n);
  int numPosiciones;
  int *puntero_t_espera = posiciones(tiempo_espera, n, max, &numPosiciones);
  int num = numPosiciones;
  // creando una lista para almacenar posiciones con tiempo de espera maximo
  int posiciones_t_espera[num];
  for (int i = 0; i < num; i++) {
    // printf("Valores: %d\n", puntero_t_espera[i]);
    posiciones_t_espera[i] = puntero_t_espera[i];
  }
  // printf("Lista: %d\n", posiciones_t_espera[0]);
  // fin función
  free(puntero_t_espera);
  int min = lista_llegada[posiciones_t_espera[0]];
  for (int i = 0; i < num; i++) {
    if (lista_llegada[posiciones_t_espera[i]] <= min) {
      min = lista_llegada[posiciones_t_espera[i]];
    }
  }
  int k = 0;
  for (int i = 0; i < num; i++) {
    if (lista_llegada[posiciones_t_espera[i]] == min) {
      k++;
    }
  }
  int *posiciones_tiempo_llegada;
  posiciones_tiempo_llegada = (int *)calloc(k, sizeof(int));
  int j = 0;
  for (int i = 0; i < num; i++) {
    if (lista_llegada[posiciones_t_espera[i]] == min) {
      posiciones_tiempo_llegada[j] = posiciones_t_espera[i];
      contador++;
      j++;
    }
  }
  *num_posiciones = contador; // Guardar la cantidad de posiciones encontradas
  return posiciones_tiempo_llegada; // retorna puntero con posiciones
}

int prioridad_minima(int lista_prioridad[], int posiciones_t_llegada[],
                     int longitud) {
  int min = lista_prioridad[posiciones_t_llegada[0]];
  int posicion = 0;

  for (int i = 0; i < longitud; i++) {
    if (lista_prioridad[posiciones_t_llegada[i]] < min) {
      min = lista_prioridad[posiciones_t_llegada[i]];
      posicion = i;
    }
  }
  int posi_prioridad_minima = posiciones_t_llegada[posicion];
  return posi_prioridad_minima; // Retorna la posición del proceso con menor
                                // tiempo de llegada y menor prioridad
}

int main() {
  printf("\033[1;33m============ * * * * * *  =============\033[0m\n");
  printf("\033[1;33m======== SISTEMAS OPERATIVOS ==========\033[0m\n");
  printf("\033[1;33m==========  * * * * * * *  ============\033[0m\n");
  printf("\033[1;33m=======================================\033[0m\n");
  printf("\033[1;33m======== TRABAJO INTEGRADOR ===========\033[0m\n");
  printf("\033[1;33m=======================================\033[0m\n");
  printf("\033[1;33m============ INTEGRANTES: =============\033[0m\n");
  printf("\033[1;33m------- VILLANUEVA NAMOC, MARCO -------\033[0m\n");
  printf("\033[1;33m--------- OCHOA LAPA, RENATO ----------\033[0m\n");
  printf("\033[1;33m------- SANTIN VILCHEZ, RENATO --------\033[0m\n");
  printf("\033[1;33m------ CARAMANTIN CRUZ, LEANDRO -------\033[0m\n");
  printf("\033[1;33m=======================================\033[0m\n");

  int n;
  printf("Ingrese el número de procesos: ");
  scanf("%i", &n);
  printf("==========  * * * * * * *  ============\n");

  int quantum;
  printf("Ingresar el tamaño del quantum: ");
  scanf("%i", &quantum);

  int prioridad[n];
  int tiempo_llegada[n];
  int tiempo_cpu[n];

  for (int i = 0; i < n; i++) {
    printf("==========  * * * * * * *  ============\n");
    int letra = 65 + i;
    printf("\n---- Proceso %c ----\n", letra);

    printf("Prioridad: ");
    scanf("%i", &prioridad[i]);

    printf("Tiempo de llegada: ");
    scanf("%i", &tiempo_llegada[i]);

    printf("Tiempo de cpu: ");
    scanf("%i", &tiempo_cpu[i]);
  }
  printf("\n");
  printf("==========  * * * * * * * * * * *  ============\n");
  printf("==========  Algoritmo Round Robin  ============\n");
  printf("==========  * * * * * * * * * * *  ============\n");

  int X[n];
  int tiempo_espera[n];
  int tiempo_restante[n];
  // tiempo_restante = tiempo_cpu;

  int t_procesamiento_total = 0;
  int suma_tiempo_cpu = 0;
  for (int i = 0; i < n; i++) {
    suma_tiempo_cpu += tiempo_cpu[i];
    X[i] = 0;
    tiempo_espera[i] = 0;
    tiempo_restante[i] = tiempo_cpu[i];
  }

  char matriz[n]
             [suma_tiempo_cpu]; // Definir una matriz de 5 filas y 15 columnas

  // Inicializar la matriz con '0's
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 15; j++) {
      matriz[i][j] = '-';
    }
  }
  while (true) {
    bool hecho = true;
    for (int i = 0; i < n; i++) {
      if (tiempo_restante[i] > 0) {
        hecho = false;
      }
    }
    // pasarle n a la funcion de abajo
    int numPosiciones = 0;
    int *tiempo_llegada_min =
        tiempo_llegada_minimo(tiempo_llegada, tiempo_espera, n, &numPosiciones);
    int num = numPosiciones;
    int lista_pos_t_llegada[num];
    for (int i = 0; i < num; i++) {
      // printf("Posiciones tiempo de llegada min: %d\n",
      // tiempo_llegada_min[i]);
      lista_pos_t_llegada[i] = tiempo_llegada_min[i];
    }
    free(tiempo_llegada_min);
    // Puntero y posicion del menor tiempo de llegada
    int proceso = prioridad_minima(prioridad, lista_pos_t_llegada, num);
    // printf("La posición del tiempo de prioridad minimo es: %i\n",proceso);
    int z = 2;
    int lista[z];
    lista[0] = quantum;
    lista[1] = tiempo_restante[proceso];

    int t_procesamiento = minimo(lista, z);

    while (t_procesamiento > 0) {
      X[proceso]++;
      tiempo_restante[proceso]--;
      t_procesamiento_total++;
      matriz[proceso][t_procesamiento_total - 1] = 'X';
      for (int j = 0; j < n; j++) {
        if (j != proceso) {
          if (t_procesamiento_total > tiempo_llegada[j]) {
            if (tiempo_restante[j] > 0) {
              tiempo_espera[j]++;
              matriz[j][t_procesamiento_total - 1] = 'W';
            } else {
              matriz[j][t_procesamiento_total - 1] = '-';
            }
          }
        }
      }
      t_procesamiento--;
    }
    if (hecho == true) {
      break;
    }
  }

  printf("\n");

  float tiempo_retorno = 0;
  float tiempo_espera_total = 0;

  for (int i = 0; i < n; i++) {
    tiempo_retorno += (X[i] + tiempo_espera[i]);
    tiempo_espera_total += tiempo_espera[i];
  }

  float tiempo_retorno_promedio = tiempo_retorno / n;
  float tiempo_espera_promedio = tiempo_espera_total / n;
  float tiempo_servicio = tiempo_retorno_promedio - tiempo_espera_promedio;
  float TRN = tiempo_retorno_promedio / tiempo_servicio;

  printf("\033[1;32m\n=====================================\033[0m\n");
  printf("\033[1;32m========  VISUALIZACIÓN  ============\033[0m\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < suma_tiempo_cpu; j++) {
      printf("\033[1;32m%c\033[0m ", matriz[i][j]);
    }
    printf("\n");
  }
  printf("\033[1;32m\n======================================\033[0m\n");
  printf("\n");
  printf("\033[1;36m===========  RESULTADOS  =============\033[0m\n");
  printf("\033[1;36m>> El tiempo de retorno promedio es: %.4f\033[0m\n",
         tiempo_retorno_promedio);
  printf("\033[1;36m>> El tiempo de espera promedio es: %.4f\033[0m\n",
         tiempo_espera_promedio);
  printf("\033[1;36m>> El tiempo de servicio es: %.4f\033[0m\n",
         tiempo_servicio);
  printf("\033[1;36m>> El tiempo de retorno normalizado es: %.4f\033[0m\n",
         TRN);

  FILE *archivo; // Declara un puntero a tipo FILE
  archivo = fopen("archivo.txt", "w");

  fprintf(archivo, "============ * * * * * *  =============\n");
  fprintf(archivo, "======== SISTEMAS OPERATIVOS ==========\n");
  fprintf(archivo, "==========  * * * * * * *  ============\n");
  fprintf(archivo, "=======================================\n");
  fprintf(archivo, "======== TRABAJO INTEGRADOR ===========\n");
  fprintf(archivo, "=======================================\n");
  fprintf(archivo, "============ INTEGRANTES: =============\n");
  fprintf(archivo, "------- VILLANUEVA NAMOC, MARCO -------\n");
  fprintf(archivo, "--------- OCHOA LAPA, RENATO ----------\n");
  fprintf(archivo, "------- SANTIN VILCHEZ, RENATO --------\n");
  fprintf(archivo, "------ CARAMANTIN CRUZ, LEANDRO -------\n");
  fprintf(archivo, "=======================================\n");

  fprintf(archivo, "\nValores ingresados:\n");
  fprintf(archivo, "Número de procesos: %d\n", n);
  fprintf(archivo, "Tamaño del quantum: %d\n", quantum);
  fprintf(archivo, "Prioridades: ");
  for (int i = 0; i < n; i++) {
    fprintf(archivo, "%d ", prioridad[i]);
  }
  fprintf(archivo, "\nTiempos de llegada: ");
  for (int i = 0; i < n; i++) {
    fprintf(archivo, "%d ", tiempo_llegada[i]);
  }
  fprintf(archivo, "\nTiempos de CPU: ");
  for (int i = 0; i < n; i++) {
    fprintf(archivo, "%d ", tiempo_cpu[i]);
  }
  fprintf(archivo, "\n");
  fprintf(archivo, "==========  * * * * * * * * * * *  ============\n");
  fprintf(archivo, "==========  Algoritmo Round Robin  ============\n");
  fprintf(archivo, "==========  * * * * * * * * * * *  ============\n");
  fprintf(archivo, "\n=====================================\n");
  fprintf(archivo, "========  VISUALIZACION  ============\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < suma_tiempo_cpu; j++) {
      fprintf(archivo, "%c ", matriz[i][j]);
    }
    fprintf(archivo, "\n");
  }
  fprintf(archivo, "\n======================================\n");
  fprintf(archivo, "\n");
  fprintf(archivo, "===========  RESULTADOS  =============\n");
  fprintf(archivo, ">> El tiempo de retorno promedio es: %.4f\n",
          tiempo_retorno_promedio);
  fprintf(archivo, ">> El tiempo de espera promedio es: %.4f\n",
          tiempo_espera_promedio);
  fprintf(archivo, ">> El tiempo de servicio es: %.4f\n", tiempo_servicio);
  fprintf(archivo, ">> El tiempo de retorno normalizado es: %.4f\n", TRN);
  fclose(archivo);
  return 0;
}
