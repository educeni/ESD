// v4
// Eduardo Ceni Paiva Santos
// Alexander Borges do Nascimento
// Gustavo Ricardo da Silva Vieira

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define QTD_PREF 6
#define TAM_NOME 50

typedef struct {
	char nome[50];
	float notas[QTD_PREF];
} Pessoa;

// Protótipo das funções
int cadastro(int qtdCadastro, Pessoa pessoas[], int *quant);
void exibir(Pessoa pessoas[], int qtdCadastro);
int buscarnome(char nomepesquisado[], Pessoa pessoas[], int qtdCadastro);
float calculaDistancia(Pessoa pessoas[], int pessoa1, int pessoa2);
void afinidade(Pessoa pessoas[], char nomepesquisado[], int qtdCadastro);
float Pessoamaissemelhante(Pessoa pessoas[], int verificaNome, int quant, int *nomeachado);
void analisePreferencia(Pessoa pessoas[], int pessoa1, int pessoa2);
float buscaNota(Pessoa pessoas[], int indiceNota, int pessoa);

int main()
{
	Pessoa *pessoas;

	float result;
	int escolha = -1;
	int qtdCadastro;
	int quant = 0;
	int verificaNome;
	int verificaNome2;
	int nomeachado;
	char nomepesquisado[TAM_NOME];
	char nomepesquisado2[TAM_NOME];

	pessoas = malloc(qtdCadastro * sizeof(Pessoa));
	if (pessoas == NULL)
	{
		printf("Erro ao alocar memoria.\n");
		return 1;
	}

	while (escolha != 0)
	{
		printf("\n========================================\n");
		printf("\tSistema de Afinidades\n");
		printf("========================================\n");
		printf("1 - Cadastrar pessoas\n");
		printf("2 - Exibir pessoas e preferencias\n");
		printf("3 - Buscar pessoa pelo nome\n");
		printf("4 - Comparar duas pessoas\n");
		printf("5 - Encontrar pessoa mais semelhante\n");
		printf("6 - Exibir ranking de afinidade\n");
		printf("7 - Analisar preferencia\n");
		printf("0 - Encerrar\n");
		printf("Opcao: ");
		scanf("%d", &escolha);

		switch (escolha)
		{
		case 1:
			printf("Quantas pessoas deseja cadastrar: ");
			scanf("%d", &qtdCadastro);
			if (quant == qtdCadastro)
			{
				printf("Todas as vagas ja foram preenchidas.\n");
			}
			else
			{
				cadastro(qtdCadastro, pessoas, &quant);
				printf("\nCadastro realizado com sucesso!\n");
			}
			break;
		case 2:
			if (quant > 0)
			{
				exibir(pessoas, quant);
			}
			else
			{
				printf("Nenhum cadastro registrado ainda.\n");
			}
			break;
		case 3:
			if (quant > 0)
			{
				printf("Me diga um nome: ");
				scanf("%49s", nomepesquisado);

				verificaNome = buscarnome(nomepesquisado, pessoas, quant);
				if (verificaNome != -1)
				{
					printf("%s foi encontrado no sistema.\n", nomepesquisado);
				}
				else
				{
					printf("Usuario nao encontrado.\n");
				}
			}
			else
			{
				printf("Nenhum cadastro registrado ainda.\n");
			}
			break;
		case 4:
			if (quant < 2)
			{
				printf("E necessario cadastrar pelo menos duas pessoas.\n");
				break;
			}
			printf("Forneca o nome da primeira pessoa: ");
			scanf("%49s", nomepesquisado);

			printf("Forneca o nome da segunda pessoa: ");
			scanf("%49s", nomepesquisado2);

			verificaNome = buscarnome(nomepesquisado, pessoas, quant);
			verificaNome2 = buscarnome(nomepesquisado2, pessoas, quant);

			if (verificaNome != -1 && verificaNome2 != -1)
			{
				result = calculaDistancia(pessoas, verificaNome, verificaNome2);

				printf("\n========================================\n");
				printf("COMPARACAO DE PERFIS\n");
				printf("========================================\n");
				printf("%s x %s\n", pessoas[verificaNome].nome, pessoas[verificaNome2].nome);
				printf("Distancia euclidiana: %.2f\n", result);
			}
			else
			{
				printf("Um ou mais nomes nao foram encontrados.\n");
			}
			break;
		case 5:
			if (quant < 2)
			{
				printf("E necessario cadastrar pelo menos duas pessoas.\n");
				break;
			}

			printf("Forneca o nome da pessoa: ");
			scanf("%49s", nomepesquisado);

			verificaNome = buscarnome(nomepesquisado, pessoas, quant);

			if (verificaNome != -1)
			{
				result = Pessoamaissemelhante(pessoas, verificaNome, quant, &nomeachado);

				printf("\n========================================\n");
				printf("PESSOA MAIS SEMELHANTE\n");
				printf("========================================\n");
				printf("A pessoa mais proxima de %s e %s\n", pessoas[verificaNome].nome, pessoas[nomeachado].nome);
				printf("Distancia: %.2f\n", result);
			}
			else
			{
				printf("Nome nao encontrado.\n");
			}
			break;
		case 6:
			if (quant < 2)
			{
				printf("E necessario cadastrar pelo menos duas pessoas.\n");
				break;
			}

			printf("Informe a pessoa de referencia: ");
			scanf("%49s", nomepesquisado);

			afinidade(pessoas, nomepesquisado, quant);
			break;
		case 7:
			if (quant < 2)
			{
				printf("E necessario cadastrar pelo menos duas pessoas.\n");
				break;
			}
			printf("Informe a primeira pessoa: ");
			scanf("%49s", nomepesquisado);

			printf("Informe a segunda pessoa: ");
			scanf("%49s", nomepesquisado2);

			verificaNome = buscarnome(nomepesquisado, pessoas, quant);
			verificaNome2 = buscarnome(nomepesquisado2, pessoas, quant);

			if (verificaNome != -1 && verificaNome2 != -1)
			{
				analisePreferencia(pessoas, verificaNome, verificaNome2);
			}
			else
			{
				printf("Um ou mais nomes nao foram encontrados.\n");
			}
			break;
		case 0:
			printf("\nEncerrando o sistema...\n");
			break;
		default:
			printf("Opcao invalida. Tente novamente.\n");
			break;
		}
	}
	free(pessoas);
	return 0;
}

int cadastro(int qtdCadastro, Pessoa pessoas[], int *quant)
{
	int i, k;
	int quantidadeRestante;
	float nota;
	char *categorias[] = {"Musica","Cinema","Jogos","Esportes","Leitura","Programacao"};

	quantidadeRestante = qtdCadastro - *quant;
	for (i = 0; i < quantidadeRestante; i++)
	{
		printf("\nForneca o nome: ");
		scanf("%49s", pessoas[*quant].nome);

		for (k = 0; k < QTD_PREF; k++)
		{
			do
			{
				printf("Nota para %s: ", categorias[k]);
				scanf("%f", &nota);

				if (nota < 0 || nota > 10)
				{
					printf("Nota invalida! Deve ser entre 0 e 10.\n");
				}
			}
			while (nota < 0 || nota > 10);
			pessoas[*quant].notas[k] = nota;
		}
		(*quant)++;
	}
	return 1;
}

void exibir(Pessoa pessoas[], int qtdCadastro)
{
	int i;

	printf("\n========================================\n");
	printf("PREFERENCIAS CADASTRADAS\n");
	printf("========================================\n");

	for (i = 0; i < qtdCadastro; i++)
	{
		printf("\nPessoa %d\n", i + 1);
		printf("Nome: %s\n", pessoas[i].nome);
		printf("Musica: %.1f\n", pessoas[i].notas[0]);
		printf("Cinema: %.1f\n", pessoas[i].notas[1]);
		printf("Jogos: %.1f\n", pessoas[i].notas[2]);
		printf("Esportes: %.1f\n", pessoas[i].notas[3]);
		printf("Leitura: %.1f\n", pessoas[i].notas[4]);
		printf("Programacao: %.1f\n", pessoas[i].notas[5]);
		printf("----------------------------------------\n");
	}
}

int buscarnome(char nomepesquisado[], Pessoa pessoas[], int qtdCadastro)
{
	int i;

	for (i = 0; i < qtdCadastro; i++)
	{
		if (strcmp(nomepesquisado, pessoas[i].nome) == 0)
		{
			return i;
		}
	}
	return -1;
}

float calculaDistancia(Pessoa pessoas[], int pessoa1, int pessoa2)
{
	int j;
	float soma = 0;
	float diferenca;

	for (j = 0; j < QTD_PREF; j++)
	{
		diferenca = pessoas[pessoa1].notas[j] - pessoas[pessoa2].notas[j];
		soma += diferenca * diferenca;
	}
	return sqrt(soma);
}

float Pessoamaissemelhante(Pessoa pessoas[], int verificaNome, int quant, int *nomeachado)
{
	int i;
	float result;
	float proximo = FLT_MAX;

	for (i = 0; i < quant; i++)
	{
		if (verificaNome != i)
		{
			result = calculaDistancia(pessoas, verificaNome, i);
			printf("Distancia para %s: %.2f\n", pessoas[i].nome, result);

			if (result < proximo)
			{
				*nomeachado = i;
				proximo = result;
			}
		}
	}
	return proximo;
}

void afinidade(Pessoa pessoas[], char nomepesquisado[], int qtdCadastro)
{
	int *indices;
	float *distancias;
	int i, j;
	int result;
	int qtd = 0;
	int temp_indice;
	float temp_distancia;
	float distancia;

	result = buscarnome(nomepesquisado, pessoas, qtdCadastro);

	if (result == -1)
	{
		printf("Nome nao encontrado!\n");
		return;
	}
	indices = malloc((qtdCadastro - 1) * sizeof(int));
	distancias = malloc((qtdCadastro - 1) * sizeof(float));

	if (indices == NULL || distancias == NULL)
	{
		printf("Erro ao alocar memoria.\n");
		free(indices);
		free(distancias);
		return;
	}

	for (i = 0; i < qtdCadastro; i++)
	{
		if (i != result)
		{
			distancia = calculaDistancia(pessoas, result, i);
			distancias[qtd] = distancia;
			indices[qtd] = i;
			qtd++;
		}
	}

	for (i = 0; i < qtd - 1; i++)
	{
		for (j = 0; j < qtd - 1 - i; j++)
		{
			if (distancias[j] > distancias[j + 1])
			{
				temp_distancia = distancias[j];
				distancias[j] = distancias[j + 1];
				distancias[j + 1] = temp_distancia;

				temp_indice = indices[j];
				indices[j] = indices[j + 1];
				indices[j + 1] = temp_indice;
			}
		}
	}

	printf("\n========================================\n");
	printf("PERFIS MAIS PROXIMOS DE %s\n", pessoas[result].nome);
	printf("========================================\n");

	for (i = 0; i < qtd; i++)
	{
		printf("%d - %s - Distancia: %.2f\n", i + 1, pessoas[indices[i]].nome, distancias[i]);
	}
	free(indices);
	free(distancias);
}

float buscaNota(Pessoa pessoas[], int indiceNota, int pessoa)
{
	return pessoas[pessoa].notas[indiceNota];
}

void analisePreferencia(Pessoa pessoas[], int pessoa1, int pessoa2)
{
	float nota, nota2;
	float diferenca[QTD_PREF];
	float menorDif = FLT_MAX;
	float distancia;
	int i;

	char *categorias[] = {"Musica", "Cinema", "Jogos", "Esportes", "Leitura", "Programacao"};

	distancia = calculaDistancia(pessoas, pessoa1, pessoa2);

	printf("\n===============================================\n");
	printf("ANALISE DE PERFIS\n");
	printf("===============================================\n\n");

	printf("%s x %s\n\n", pessoas[pessoa1].nome, pessoas[pessoa2].nome);
	printf("Preferencia\t%s\t%s\tDiferenca\n", pessoas[pessoa1].nome, pessoas[pessoa2].nome);
	printf("-------------------------------------------------\n");

	for (i = 0; i < QTD_PREF; i++)
	{
		nota = buscaNota(pessoas, i, pessoa1);
		nota2 = buscaNota(pessoas, i, pessoa2);

		diferenca[i] = fabs(nota - nota2);

		if (diferenca[i] < menorDif)
		{
			menorDif = diferenca[i];
		}
		printf("%-15s %.1f\t%.1f\t%.1f\n", categorias[i], nota, nota2, diferenca[i]);
	}
	printf("-------------------------------------------------\n");
	printf("Distancia euclidiana: %.2f\n\n", distancia);
	printf("Preferencias mais semelhantes:\n");

	for (i = 0; i < QTD_PREF; i++)
	{
		if (diferenca[i] == menorDif)
		{
			printf("- %s\n", categorias[i]);
		}
	}
}
