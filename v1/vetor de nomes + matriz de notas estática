#include <stdio.h>
#include <string.h>
#define MAX_PESSOAS 30
#define QTD_PREF 6

// Protótipo das Funções
void cadastro(int qtdCadastro, char nomes[MAX_PESSOAS][50], float notas[][QTD_PREF], int *j);
void exibir(char nomes[MAX_PESSOAS][50], float notas[][QTD_PREF], int qtdCadastro);

void main() 
{
	char nomes[MAX_PESSOAS][50];
	float notas[MAX_PESSOAS][QTD_PREF];
	int escolha, qtdCadastro, quant = 0; // Variáveis da função cadastro
	
	// mostrando as opções de funções para o usuário
    while (escolha != 0)
    {
	    printf("\n========================================\n\tSistema de Afinidades\n========================================\n\n");
	    printf("1 - Cadastrar pessoas\n2 - Exibir pessoas e preferências\n3 - Buscar pessoa pelo nome\n4 - Comparar duas pessoas\n");
	    printf("5 - Encontrar pessoa mais semelhante\n6 - Exibir ranking de afinidade\n7 - Analisar preferências de duas pessoas\n0 - Encerrar\n\n");

        printf("Opcao: ");
	    scanf("%d", &escolha);

        switch (escolha)
        {
            case 1:
                printf("Quantas pessoas deseja cadastrar: ");
		        scanf("%d", &qtdCadastro);

                // Validação se o número informado de pessoas é permitido
                if((1<=qtdCadastro)&&(qtdCadastro<=MAX_PESSOAS))
		        {
			        // Chamando função de cadastro
			        cadastro(qtdCadastro, nomes, notas, &quant);
			       printf("valor de quant: %i", quant);
		        }
		        else
		        {
			        printf("O numero de pessoas informado excede o limite do cadastro. \n");
		        }
                break;
            case 2:
				exibir(nomes, notas, quant);
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
        }
    }
}

void cadastro(int qtdCadastro, char nomes[MAX_PESSOAS][50], float notas[][QTD_PREF], int *j)
{
	int i;

	for(i=0;i<qtdCadastro;i++)
	{
		printf("Forneca o Nome: ");         
		scanf("%s", &nomes[*j]);
		printf("Nota para Música: ");
		scanf("%f", &notas[*j][0]);
		printf("Nota para Cinema: ");
		scanf("%f", &notas[*j][1]);
		printf("Nota para Jogos: ");
		scanf("%f", &notas[*j][2]);
		printf("Nota para Esportes: ");
		scanf("%f", &notas[*j][3]);
		printf("Nota para Leitura: ");
		scanf("%f", &notas[*j][4]);
		printf("Nota para Programação: ");
		scanf("%f", &notas[*j][5]);
		
		printf("%i", *j);
		(*j)++;
    }
}

void exibir(char nomes[MAX_PESSOAS][50], float notas[][QTD_PREF], int qtdCadastro)
{
    
	int i;

	printf("\n			PREFERÊNCIAS\n\n");
	printf("		 0   1   2   3   4   5\n");
	printf("		MUS CIN JOG ESP LEI PROG\n\n");

	for(i=0;i<qtdCadastro;i++)
	{
		printf("Pessoa %d - %s %.1f %.1f %.1f %.1f %.1f %.1f\n", i, nomes[i], notas[i][0], notas[i][1], notas[i][2], notas[i][3], notas[i][4], notas[i][5]);
	}
}