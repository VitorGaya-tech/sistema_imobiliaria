/*	Projeto AC2 - Imobiliária
-	Aplicação da Arvore binária para cadastro de Imóveis
-	Gabriel Baldi Gomes dos Santos 		RA- 235452
-	Jean Luca Novaes Gomes 		   		RA- 236999
-	Vitor Jacomini Gaya 				RA- 235265
-	André Vinícius Siqueira 			RA- 236811
-	Ultima alteração: 04/05/2025
*/
#include "ArvoreBin.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// Cria árvore vazia
Arvore criar_arvore() { 
	return NULL; 
}

// Destrói a árvore (postorder)
void destruir_arvore(Arvore *raiz) {
    if (*raiz) {
        destruir_arvore(&(*raiz)->esq);
        destruir_arvore(&(*raiz)->dir);
        free(*raiz);
        *raiz = NULL;
    }
}

// Auxiliar: cria um nó
Arvore criar_no(Imovel imovel) {
    No *novo = malloc(sizeof(No));
    if (novo) {
        novo->dado = imovel;
        novo->esq = novo->dir = NULL;
    }
    return novo;
}

// Compara dois imóveis (para ordenação)
int comparar(Imovel a, Imovel b) {
    // Primeira Comparação (só ocorre uma vez):
	// Quando o imóvel for venda, retorna -1, caso contrario retorna 1
	if (a.tipo != b.tipo){
		if(a.tipo == 'V')
			return -1;
		else
			return 1;
	}
	// Segunda comparação:
	// Quando o numero de quartos da raiz for maior que o do imovel, retorna -1, caso contrario retorna 1	
    if (a.quartos != b.quartos){
		if(a.quartos < b.quartos)
			return -1;
		else
			return 1;
	}
	// Ultima comparação por valor: 
	// Quando valor_raiz > valor_imovel, retorna -1, caso contrario retorna 1
    if (a.valor != b.valor){
		if(a.valor < b.valor)
			return -1;
		else
			return 1;
	}
	// Verifica se os códigos são diferentes
	if(a.codigo != b.codigo){
		if(a.codigo < b.codigo)
			return -1;
		else
			return 1;
	}
	
  printf("Imóvel ja existente! \n");	
  return 0;
}

// Insere um imóvel (ordem- tipo / quartos / valor / código)
void inserir(Arvore *raiz, Imovel novo) {
    // Quando encontrar o local para o nó
	if (*raiz == NULL) {
        *raiz = criar_no(novo);
    } else {
        int cmp = comparar(novo, (*raiz)->dado);
        // Se for negativo, o caminho é sempre pra esquerda
		if (cmp < 0) 
			inserir(&(*raiz)->esq, novo);
        // Se for positivo, o caminho é sempre pra direita
		else if (cmp > 0) 
			inserir(&(*raiz)->dir, novo);
    }
}

// Busca por código
 Arvore buscar(Arvore raiz, int codigo) {
    // Se não tem nada na árvore, ou não encontrou o código.
	if (raiz == NULL) 
		return NULL;
    // Se o codigo de onde estou bater com codigo buscado, retorna a raiz
	if (codigo == raiz->dado.codigo) 
		return raiz;
	// Vai buscar na esquerda;
    No *esq = buscar(raiz->esq, codigo);
    // Enquanto não achar o código ou chegar num beco sem saida, vai indo pra esquerda
	if(esq != NULL)
		return esq;
	// Não tem mais como ir pra esquerda, vai pra direita	
	else 
		return buscar(raiz->dir, codigo);
}

// Remove um nó
void remover(Arvore *raiz, Imovel alvo) {
    // Não encontrou
	if (raiz == NULL) 
		return;

    int cmp = comparar(alvo, (*raiz)->dado);
	// Se a comparação for negativa, sempre pra esquerda
    if (cmp < 0) {
        remover(&(*raiz)->esq, alvo);
    } 
	// Se positiva sempre pra direita
	else if (cmp > 0) {
        remover(&(*raiz)->dir, alvo);
    } 
	//Aqui ele achou
	else {
        No *temp = *raiz;
        
        // Se tiver 0 ou 1 filho na esquerda
        if ((*raiz)->esq == NULL) {
        	//Sobe a subárvore direita no lugar do alvo
            *raiz = (*raiz)->dir;
            free(temp);
        } 
		// Se tiver 0 ou 1 filho na direita
		else if ((*raiz)->dir == NULL) {
			//Sobe a subárvore esquerda no lugar do alvo
            *raiz = (*raiz)->esq;
            free(temp);
        } else {
           // Se tiver os 2 filhos - encontrar sucessor in-order (menor da subárvore direita)
            // Cria um auxiliar pra percorrer, iniciando no filho direito do alvo
			No *sucessor = (*raiz)->dir;
			// Vai sempre pra esquerda, até achar o filho com a menor diferença.
            while (sucessor->esq != NULL) {
                sucessor = sucessor->esq;
            }
            // Copia no lugar do alvo esse filho "de menor diferença"
            (*raiz)->dado = sucessor->dado;
            // Remove esse filho
            remover(&(*raiz)->dir, sucessor->dado);
        }
    }
}

// Preenche com 30 imóveis de exemplo
void preencher_30_imoveis(Arvore *raiz) {
	int i;
    Imovel exemplos[30] = {
        {"Ana Silva", 1, 2, 1, 1, 0, 'V', 250000.00},
        {"Carlos Oliveira", 2, 3, 2, 2, 1, 'L', 350000.00},
        {"Mariana Costa", 3, 1, 1, 0, 0, 'V', 180000.00},
        {"Pedro Santos", 4, 4, 3, 2, 2, 'V', 450000.00},
        {"Lucia Mendes", 5, 2, 1, 1, 0, 'V', 220000.00},
        {"Ricardo Alves", 6, 3, 2, 1, 1, 'V', 320000.00},
        {"Fernanda Lima", 7, 5, 4, 3, 2, 'V', 600000.00},
        {"Marcos Rocha", 8, 2, 1, 1, 0, 'V', 280000.00},
        {"Patricia Nunes", 9, 4, 2, 2, 1, 'V', 420000.00},
        {"João Pereira", 10, 1, 1, 0, 0, 'V', 150000.00},
        
        // Locação (L)
        {"Maria Souza", 11, 2, 1, 1, 0, 'L', 1200.00},
        {"Antonio Andrade", 12, 3, 2, 2, 1, 'L', 2500.00},
        {"Juliana Freitas", 13, 1, 1, 0, 0, 'L', 800.00},
        {"Roberto Campos", 14, 4, 3, 2, 2, 'L', 3500.00},
        {"Camila Teixeira", 15, 2, 1, 1, 0, 'L', 1500.00},
        {"Felipe Gonçalves", 16, 3, 2, 1, 1, 'L', 2200.00},
        {"Isabela Martins", 17, 5, 4, 3, 2, 'L', 4500.00},
        {"Gustavo Henrique", 18, 2, 1, 1, 0, 'L', 1800.00},
        {"Laura Beatriz", 19, 4, 2, 2, 1, 'L', 3200.00},
        {"Rodrigo Cardoso", 20, 1, 1, 0, 0, 'L', 900.00},
        
        // Mais imóveis para completar 30
        {"Sandra Vieira", 21, 3, 2, 1, 1, 'V', 380000.00},
        {"Leonardo Dias", 22, 2, 1, 1, 0, 'L', 1600.00},
        {"Vanessa Castro", 23, 4, 3, 2, 1, 'V', 480000.00},
        {"Eduardo Monteiro", 24, 1, 1, 0, 0, 'L', 950.00},
        {"Tatiana Ribeiro", 25, 3, 2, 2, 1, 'V', 390000.00},
        {"Bruno Carvalho", 26, 2, 1, 1, 0, 'L', 1400.00},
        {"Amanda Lopes", 27, 5, 3, 2, 2, 'V', 550000.00},
        {"Diego Moreira", 28, 1, 1, 0, 0, 'L', 850.00},
        {"Renata Barbosa", 29, 4, 2, 2, 1, 'V', 490000.00},
        {"Alexandre Cunha", 30, 3, 2, 1, 1, 'L', 2800.00},
       
	        
    };
	    for (i = 0; i < 30; i++) {
			inserir(raiz, exemplos[i]);}
}

// Lista todos (em-ordem)
void print_imovel(Arvore raiz){
	printf("-------------------------------------------------------\nINFORMACOES DO IMOVEL\n Código: %d Proprietário: %s\n Num. Quartos: %i  Situacao: %c\n Num de vagas: %i    Suites: %i \n Valor: R$ %.2f\n", 
	raiz->dado.codigo, raiz->dado.proprietario, raiz->dado.quartos, raiz->dado.tipo, raiz->dado.garagem, raiz->dado.suites, raiz->dado.valor );
}

// Todas as buscas seguem o padrão in-order, alterando somente o que elas filtram.
void inorder(Arvore raiz) {
    if (raiz != NULL) {
        inorder(raiz->esq);
        print_imovel(raiz);
        inorder(raiz->dir);
    }
}

void busca_por_quartos(Arvore raiz, int quartos){
	if (raiz != NULL) {
        busca_por_quartos(raiz->esq, quartos);
	        if(raiz->dado.quartos == quartos){ 	
			print_imovel(raiz);
		}
        busca_por_quartos(raiz->dir, quartos);
    }
}

void busca_por_valor(Arvore raiz, float max){
	if (raiz != NULL) {
        busca_por_valor(raiz->esq, max);
	        if(raiz->dado.valor <= max){ 	
			print_imovel(raiz);
		}
        busca_por_valor(raiz->dir, max);
    }
}

void busca_por_nome(Arvore raiz, char nome[100]){
	if (raiz != NULL) {
        busca_por_nome(raiz->esq, nome);
	        if(strcmp(nome, raiz->dado.proprietario) == 0){ 	
			print_imovel(raiz);
		}
        busca_por_nome(raiz->dir, nome);
    }
}

void busca_por_tipo(Arvore raiz, char tipo){
	if (raiz != NULL) {
        busca_por_tipo(raiz->esq, tipo);
	        if(raiz->dado.tipo == tipo){ 	
			print_imovel(raiz);
		}
        busca_por_tipo(raiz->dir, tipo);
    }
}

void busca_por_vq(Arvore raiz, float valor, int quartos){
	if (raiz != NULL) {
        busca_por_vq(raiz->esq, valor, quartos);
	        if(raiz->dado.quartos == quartos && raiz->dado.valor <= valor){ 	
			print_imovel(raiz);
		}
        busca_por_vq(raiz->dir, valor, quartos);
    }
}

void busca_por_qt(Arvore raiz, char tipo, int quartos){
	if (raiz != NULL) {
        busca_por_qt(raiz->esq, tipo, quartos);
	        if(raiz->dado.quartos == quartos && raiz->dado.tipo == tipo){ 	
			print_imovel(raiz);
		}
        busca_por_qt(raiz->dir, tipo, quartos);
    }
}

void busca_por_vt(Arvore raiz, char tipo, float valor){
	if (raiz != NULL) {
        busca_por_vt(raiz->esq, tipo, valor);
	        if(raiz->dado.valor <= valor && raiz->dado.tipo == tipo){ 	
			print_imovel(raiz);
		}
        busca_por_vt(raiz->dir, tipo, valor);
    }
}

void busca_completa(Arvore raiz, char tipo, float valor, int quartos){
	if (raiz != NULL) {
        busca_completa(raiz->esq, tipo, valor, quartos);
	        if(raiz->dado.quartos == quartos && raiz->dado.tipo == tipo && raiz->dado.valor <= valor){ 	
			print_imovel(raiz);
		}
        busca_completa(raiz->dir, tipo, valor, quartos);
    }
}




void busca_por_filtro(Arvore raiz){
int quartos;
float valor;
char tipo;
	printf("Tipo: (V - Venda/ L - Locacao/ N - Não deseja aplicar esse filtro):"); 
	scanf(" %c", &tipo);
    fflush(stdin);
    printf("Qual o valor maximo? (Digite '-1' caso não deseje aplicar o filtro)");
	scanf("%f", &valor);
	fflush(stdin);
	printf("Quartos: (Digite '-1' caso não deseje aplicar o filtro)");
	scanf("%d", &quartos);
		if(tipo == 'N' || tipo == 'n'){
			if(quartos == -1){
				busca_por_valor(raiz, valor);
				return;
			}
			else if(valor == -1){
				busca_por_quartos(raiz, quartos);
				return;
			}
			else{
				busca_por_vq(raiz, valor, quartos);
				return;
			}
	
		}
		else{
			if(quartos == -1 && valor == -1){
				busca_por_tipo(raiz, tipo);
				return;
			}
			else if(valor == -1){
				busca_por_qt(raiz, tipo, quartos);
				return;
			}
			else if(quartos == -1){
				busca_por_vt(raiz, tipo, valor);
				return;
			}
			else
			busca_completa(raiz, tipo, valor, quartos);
			return;
		}
			
		}




