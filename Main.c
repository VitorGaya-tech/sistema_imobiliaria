/*	Projeto AC2 - Imobiliária
-	Implementação da Arvore binária para cadastro de Imóveis
-	Gabriel Baldi Gomes dos Santos 		RA- 235452
-	Jean Luca Novaes Gomes 		   		RA- 236999
-	Vitor Jacomini Gaya 				RA- 235265
-	André Vinícius Siqueira 			RA- 236811
-	Ultima alteração: 04/05/2025
*/

#include "ArvoreBin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int recebe_int(){
	printf(" Numero desejado: \n");
	return scanf("%i");
}

void mostrar_imovel(Imovel i){
		printf("-------------------------------------------------------\nINFORMACOES DO IMOVEL\n Código: %d Proprietário: %s\n Num. Quartos: %i  Situacao: %c\n Num de vagas: %i    Suites: %i \n Valor: R$ %.2f\n", 
		i.codigo, i.proprietario, i.quartos, i.tipo, i.garagem, i.suites, i.valor );
}

Imovel receber_imovel(int ID) {
    Imovel i;
    i.codigo = ID;
    printf("Proprietário: "); 
    fflush(stdin);
	fgets(i.proprietario , sizeof(i.proprietario ), stdin);
	i.proprietario[strcspn(i.proprietario, "\n")] = '\0';
    printf("Tipo (V/L): "); 
	scanf(" %c", &i.tipo);
    fflush(stdin);
    printf("Quantidade de vagas: ");
	scanf("%d", &i.garagem);
	fflush(stdin);
	printf("Quartos: ");
	scanf("%d", &i.quartos);
	fflush(stdin);
	printf("Suites: ");
	scanf("%d", &i.suites);
	fflush(stdin);
    printf("Valor: "); 
	scanf("%f", &i.valor);
	fflush(stdin);
    return i;
}


int main() {
    Arvore raiz = criar_arvore();
    int opcao, codigo;
    int ID = 31;
    preencher_30_imoveis(&raiz);
    do {
        printf("\n1. Inserir\n2. Buscar\n3. Remover por codigo\n4. Listar\n5. Buscar por qnt quartos\n6. Busca por valor\n7. Busca por nome\n8. Busca por tipo \n9. Busca por filtro \n0. Sair\nEscolha: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: inserir(&raiz, receber_imovel(ID)); 
				ID++;
				break;
				
            case 2: {
                printf("Código: "); 
				scanf("%d", &codigo);
                No *n = buscar(raiz, codigo);
	                if (n != NULL) 
						mostrar_imovel(n->dado);
	                else 
						printf("Não encontrado!\n");
                break;
            }
            
            case 3: {
                printf("Código: "); 
				scanf("%d", &codigo);
                Arvore alvo = buscar(raiz, codigo);
					if(alvo != NULL){
					printf("Imovel Removido: \n");
					mostrar_imovel(alvo->dado);
					remover(&raiz, alvo->dado );
					}
					else
					printf("Imovel não encontrado: \n");
                break;
            }
            
            case 4: 
				inorder(raiz); 
				break;
            
            case 5: {
				int quartos;
				printf(" Numero desejado: \n");
				scanf("%i", &quartos);
				fflush(stdin);
				busca_por_quartos(raiz, quartos);
				break;
			}
			
			case 6: {
				float max;
				printf(" Valor Maximo: \n");
				scanf("%f", &max);
				fflush(stdin);
				busca_por_valor(raiz, max);
				break;
			}
			
			case 7: {
				char nome[100];
				printf("Qual o nome do proprietario? \n");
				fflush(stdin);
				fgets(nome, sizeof(nome),stdin);
				nome[strcspn(nome, "\n")] = '\0';
				busca_por_nome(raiz, nome);
				break;
			}
			
			case 8: {
				char tipo;
				printf(" Tipo desejado (V/L): \n");
				scanf("%c", &tipo);
				fflush(stdin);
				busca_por_quartos(raiz, tipo);
				break;
			}
			case 9: {
				busca_por_filtro(raiz);
				break;
			}
            	
            	
        }
    } while (opcao != 0);
    
    destruir_arvore(&raiz);
    return 0;
}
