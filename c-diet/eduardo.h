
//calcula a taxa metab�lica basal do indiv�duo de acordo com as informa��es passadas e retorna um float.
float calculaTaxaMetabolicaBasal (float peso, float altura, int idade, char sexo);

//funcao simples que faz uma convers�o retornando um float.
float converteAtvdFisica (int opcao);

//funcao simples que faz uma convers�o retorando um int.
int converteObjetivo (int opcao);

//calcula o gasto calorico do indiv�duo e manda para a fun�ao "periodiza��o". tamb�m faz a alocacao de memoria para o ponteiro calorias.
void calculaCalorias (float tmb, float atvd, float caloriasPeloObjetivo, int objetivo, float **calorias, int semanas);

//apenas faz o printf das op��es de atividade fisica.
void printaAtividadeFisica();

//faz a periodiza��o por semanas, de acordo com a quantidade de semanas escolhidas pelo usu�rio. (recursiva)
void periodizacao(int objetivo, float *calorias, float caloriaInicial, int semana, int semanas);

//mostra o resultado final pro usu�rio, manipulando o ponteiro calorias e o vetor de strings.
void resultadoFinal (float *calorias, char meses[12][15], int semanas);

//salva as semanas e as calorias do usu�rio dentro de um arquivo, criando tipo um banco de dados.
void salvarDados(float *calorias, int semanas, const char *nomeArquivo);

