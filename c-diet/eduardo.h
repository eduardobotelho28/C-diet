
//calcula a taxa metabólica basal do indivíduo de acordo com as informações passadas e retorna um float.
float calculaTaxaMetabolicaBasal (float peso, float altura, int idade, char sexo);

//funcao simples que faz uma conversão retornando um float.
float converteAtvdFisica (int opcao);

//funcao simples que faz uma conversão retorando um int.
int converteObjetivo (int opcao);

//calcula o gasto calorico do indivíduo e manda para a funçao "periodização". também faz a alocacao de memoria para o ponteiro calorias.
void calculaCalorias (float tmb, float atvd, float caloriasPeloObjetivo, int objetivo, float **calorias, int semanas);

//apenas faz o printf das opções de atividade fisica.
void printaAtividadeFisica();

//faz a periodização por semanas, de acordo com a quantidade de semanas escolhidas pelo usuário. (recursiva)
void periodizacao(int objetivo, float *calorias, float caloriaInicial, int semana, int semanas);

//mostra o resultado final pro usuário, manipulando o ponteiro calorias e o vetor de strings.
void resultadoFinal (float *calorias, char meses[12][15], int semanas);

//salva as semanas e as calorias do usuário dentro de um arquivo, criando tipo um banco de dados.
void salvarDados(float *calorias, int semanas, const char *nomeArquivo);

