/*	Projeto AC2 - Imobili�ria
-	Aplica��o da Arvore bin�ria para cadastro de Im�veis
-	Gabriel Baldi Gomes dos Santos 		RA- 235452
-	Jean Luca Novaes Gomes 		   		RA- 236999
-	Vitor Jacomini Gaya 				RA- 235265
-	Andr� Vin�cius Siqueira 			RA- 236811
-	Ultima altera��o: 04/05/2025
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct {
    char proprietario[100];
    int codigo;
    int quartos;
    int banheiros;
    int garagem;
    int suites;
    char tipo; // 'V' ou 'L'
    float valor;
} Imovel;

typedef struct no {
    Imovel dado;
    struct no *esq, *dir;
} No;

// �rvore � um ponteiro para n� (simplificado)
typedef No* Arvore;

// Fun��es b�sicas
Arvore criar_arvore();
void destruir_arvore(Arvore *raiz);

// Opera��es
void inserir(Arvore *raiz, Imovel novo);
No* buscar(Arvore raiz, int codigo);
void remover(Arvore *raiz, Imovel alvo);
void preencher_30_imoveis(Arvore *raiz);

// Buscas
void print_imovel(Arvore raiz);
void inorder(Arvore raiz);
void busca_por_quartos(Arvore raiz, int quartos);
void busca_por_valor(Arvore raiz, float max);
void busca_por_nome(Arvore raiz, char nome[100]);
void busca_por_tipo(Arvore raiz, char tipo);
void busca_por_vq(Arvore raiz, float valor, int quartos);
void busca_por_qt(Arvore raiz, char tipo, int quartos);
void busca_por_vt(Arvore raiz, char tipo, float valor);
void busca_completa(Arvore raiz, char tipo, float valor, int quartos);
void busca_por_filtro(Arvore raiz);

