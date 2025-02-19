#include "eduardo.h"
#include <stddef.h>
#include <stdio.h>

float calculaTaxaMetabolicaBasal (float peso, float altura, int idade, char sexo) {
	
	float tmb;
	
	if (sexo == 'm' || sexo == 'M') {
		tmb = 66 + (13.7*peso) + (5*altura) - (6.8*idade);
	}
	else if (sexo == 'f' || sexo == 'F') {
		tmb = 655 + (9.6*peso) + (1.8*altura) - (4.7*idade);
	}
	else {
		printf("Sexo não informado.");
	}
	
	return tmb;	
}

float converteAtvdFisica (int opcao) {
	
	switch (opcao) {
		
		case 1:
			return 1.2;
			break;
		
		case 2:
			return 1.375;
			break;
		
		case 3:
			return 1.55;
			break;
			
		case 4:
			return 1.725;
			break;
			
		case 5:
			return 1.9;
			break; 
	}
	
}

int converteObjetivo (int opcao) {
	
	if (opcao == 1) {
		return -200;
	}
	
	if (opcao == 2) {
		return 200;
	}
	
}

void calculaCalorias(float tmb, float atvd, float caloriasPeloObjetivo, int objetivo, float **calorias, int semanas) {
	
	//Calcula o gasto calorico e as calorias para a primeira semana.	
    float gastoCalorico, caloriaInicial;
    gastoCalorico = tmb * atvd;
    caloriaInicial = gastoCalorico + caloriasPeloObjetivo;

    // Alocação de memória para o array calorias
    *calorias = malloc(semanas * sizeof(float));
    if (*calorias == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }

	//começa a periodizacao
    periodizacao(objetivo, *calorias, caloriaInicial, 0, semanas);
}

void periodizacao(int objetivo, float *calorias, float caloriaAtual, int semana, int totalSemanas) {
	
	//codigo ficou um pouco complexo, o importante é saber que o ponteiro *calorias é um array levando o valor de calorias daquela semana (exemplo: calorias[2] == 1.220)
	//é recursiva
	//maximo de semanas é 48.
	//maximo de calorias a chegar é 50000
	//minimo de calorias é 1.100
	
    if (calorias == NULL) {
        printf("Erro: Ponteiro de calorias não inicializado.\n");
        return;
    }

    int maxSemanas = 48;
    float maxCaloriasObj2 = 5000.0;
    float minCaloriasObj1 = 1100.0;

    if (totalSemanas > maxSemanas) {
        printf("Erro: O número máximo de semanas permitido é 48.\n");
        return;
    }

    if (semana == totalSemanas) {
        return;  
    }

    if (semana == 0) {
        calorias[semana] = caloriaAtual;
    } else {
        if (objetivo == 1) {
            calorias[semana] = calorias[semana - 1] - (calorias[semana - 1] * 0.04);
            if (calorias[semana] < minCaloriasObj1) {
                calorias[semana] = minCaloriasObj1;
            }
        } else if (objetivo == 2) {
            calorias[semana] = calorias[semana - 1] + (calorias[semana - 1] * 0.02);
            if (calorias[semana] > maxCaloriasObj2) {
                calorias[semana] = maxCaloriasObj2;
                // Manter as mesmas calorias nas semanas seguintes
                int i;
                for (i = semana + 1; i < totalSemanas; i++) {
                    calorias[i] = maxCaloriasObj2;
                }
                return;  // Não é necessário calcular mais para as semanas seguintes
            }
        } else {
            printf("Erro: Objetivo inválido.\n");
            return;
        }
    }

    // Chamada recursiva para a próxima semana
    periodizacao(objetivo, calorias, calorias[semana], semana + 1, totalSemanas);
}


void printaAtividadeFisica () {
	printf ("\n");
	printf ("\n");
	printf ("Digite uma opcao de acordo com seu nivel de atividade fisica: \n");
	printf (" 1 --> Sedentario (pouco ou nenhum exercicio) \n");
	printf (" 2 --> Levemente ativo (exercicio leve 1 a 3 dias por semana) \n");
	printf (" 3 --> Moderadamente ativo (exercicio moderado, faz esportes 3 a 5 dias por semana) \n");
	printf (" 4 --> Altamente ativo (exercicio pesado de 5 a 6 dias por semana) \n");
	printf (" 5 --> Extremamente ativo (exercicio pesado diariamente e ate 2 vezes por dia) \n");
	printf ("\n");
}

void salvarDados(float *calorias, int semanas, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "a");  // Abre o arquivo no modo "append"
    if (arquivo == NULL) {
		fprintf(stderr, "Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Adiciona uma linha separadora
    fprintf(arquivo, "-----------------\n");

	int i;
    for (i = 0; i < semanas; i++) {
        fprintf(arquivo, "Semana %d: %.2f CALORIAS\n", i + 1, calorias[i]);
    }
    
    fclose(arquivo);
}

void resultadoFinal(float *calorias, char meses[][15], int semanas) {
    
    // Primeiro Loop (Semanas):
    int i;
    for (i = 0; i < semanas; i++) {
        printf("Semana %d: %.2f CALORIAS\n", i + 1, calorias[i]);
    }
    
    printf("------------------------------------ \n");
    
    // SEGUNDO Loop (Meses):
    int j;
    int mesesParaImprimir = (semanas + 3) / 4;  // Arredondamento para cima

    for (i = 0; i < mesesParaImprimir && i < 12; i++) {
        printf("EM %s: ", meses[i]);

        // Calcular a média das quatro semanas correspondentes ao mês
        float somaCalorias = 0.0;
        int inicioSemana = i * 4;
        int finalSemana = (i + 1) * 4 - 1;

        if (finalSemana >= semanas) {
            finalSemana = semanas - 1;  // Evitar acessar além do limite
        }

        for (j = inicioSemana; j <= finalSemana; j++) {
            somaCalorias += calorias[j];
        }

        // Imprimir a média
        if (inicioSemana <= finalSemana) {  // Evitar divisão por zero
            float mediaCalorias = somaCalorias / (finalSemana - inicioSemana + 1);
            printf("%.2f\n", mediaCalorias);
        } else {
            printf("N/A\n");
        }
    }
}




