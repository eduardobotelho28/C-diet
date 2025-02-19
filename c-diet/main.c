#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "eduardo.h"

int main(int argc, char *argv[]) {
	
	//definição das principais variáveis.//
	float peso, altura, tmb;
	float fatorAtvdFisica = 0, caloriasPeloObjetivo = 0;
	int   idade, qtdAtvdFisica, objetivo;
	float *calorias = NULL; 
	char  sexo;
	int   i; 
	char  meses[12][15] = {"Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
	//-------------------------------------------//
	
	printf ("Informe seu peso em KG: ");
	scanf  ("%f", &peso);
	printf ("Informe sua altura em centimetros: ");
	scanf  ("%f", &altura);
	printf ("Informe quantos anos voce tem: ");
	scanf  ("%i", &idade);
	printf ("Informe seu sexo (M - Masculino  F - Feminino): ");
	scanf  (" %c", &sexo);
	
	//calcula a tmb//
	tmb = calculaTaxaMetabolicaBasal(peso,altura,idade,sexo);
	
	//processo de conversão do fator Atividade fisica.
	printaAtividadeFisica();
	scanf ("%d", &qtdAtvdFisica);
	fatorAtvdFisica = converteAtvdFisica(qtdAtvdFisica);
	
	//processo de conversão das calorias a partir do objetivo do usuário
	printf ("Escolha o seu objetivo! 1- EMAGRECIMENTO 2- GANHO DE PESO \n");
	scanf  ("%d", &objetivo);
	caloriasPeloObjetivo = converteObjetivo(objetivo);
	
	int semanas;
	printf("Informe a quantidade de semanas desejada: ");
    scanf("%d", &semanas);

	//chamo as principais funções do programa//
    calculaCalorias(tmb, fatorAtvdFisica, caloriasPeloObjetivo, objetivo, &calorias, semanas);
    
    resultadoFinal(calorias, meses, semanas);
    
    salvarDados(calorias, semanas, "dados.txt");
    //---------------------------------------//
    
    free(calorias);
    
	return 0;
}
