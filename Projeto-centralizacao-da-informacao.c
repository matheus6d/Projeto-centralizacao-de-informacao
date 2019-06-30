#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <locale.h> //Biblioteca acento 

typedef struct sPost{
	
	char titulo[50], descricao[5000];
	
}Post;

typedef struct sCelula {
	
	Post info;
	struct sCelula *ant;
	struct sCelula *prox;
	
}Celula;

int inicializar(Celula** lista){
	
	(*lista)= NULL;
}
	
int listaVazia(Celula** lista){
	
	if ((*lista) == NULL)
		return 1;
	return 0;
}
	
Celula *criarNo(){
	
	return (Celula*)malloc(sizeof(Celula));
}

int InserirOrdenado(Celula **lista, Post d){
	
	Celula *no, *aux;
	no= criarNo();       //cria celula
		if(no==NULL){	// verifica se foi criada/alocado
			printf ("Erro ao alocar!");
			return 0;
		}
		
	no->info = d; //Atribui ao campo info os dados da struct 
	
	aux= (*lista); 
	
		if (listaVazia(lista)){  //Caso a lista esteja vazia
			
			(*lista)= no;
			no->ant= no;
			no->prox= no;
			
		} else {  //Caso não esteja vazia
		
			do {
				
			aux= aux->prox; //incrementa o auxiliar para que possa percorrer toda a lista até achar o local de inserir 
			
					no->ant= aux->ant;
					no->prox= aux;
					no->ant->prox= no;
					aux->ant= no;
					return 1;
			
				
			} while (aux != (*lista)); 
		
				if (aux == (*lista)){ // Se aux == lista, se insere no fim e o ponteiro lista passa a apontar para o novo elemento
					no->ant= aux;
					no->prox= aux->prox;
					aux->prox->ant= no;
					aux->prox= no;
					(*lista)= no;
				} 				
		}	
		
	return 1;
}

Celula* PesquisarElemento(Celula **lista, char titulo[]){
	
 		if (listaVazia(lista))
 			return NULL;
		 			
	Celula* aux = (*lista)->prox;//pega a primeira celula
	
		do {
			if (strcmp(titulo, aux->info.titulo) == 0){	//caso a palavra procurada seja a mesma que contida no campo info da celula apontada pelo auxiliar	
			return aux;
			}
		
			aux= aux->prox; 
		
		}while(aux != (*lista)->prox); 
		
	return 0;
}

void ExibirUnico(Celula **lista, char nomePostagem[]){
	
	Celula* aux = PesquisarElemento(lista, nomePostagem); //Função pesquisar retorna o elemento
		
		if(aux == NULL){ //Caso a postagem pesquisada não exista
			printf ("\n        !!! ATENCAO: Postagem não encontrada !!!");
			return;
		}
		
	printf ("\n");
	printf (" -- Titulo: %s\n", aux->info.titulo);
	printf (" Descricao: %s\n", aux->info.descricao);			
	
}

void ExibirTudo(Celula **lista){
	
	Celula *aux;
		
		if (listaVazia(lista)){
			printf ("\n!!! ATENCAO: Nao ha elementos para exibir, lista vazia !!!");
			return;
		}
			
	aux= (*lista)->prox;
		
		do{
		
			printf ("\n");
			printf (" -- Titulo: %s\n", aux->info.titulo);
			printf (" Descricao: %s\n", aux->info.descricao);		
			aux= aux->prox;
				
		}while(aux != (*lista)->prox);	
		
		printf("\n    --= Todos as POSTAGENS exibidas com SUCESSO! =-- ");	
}

int RemoverElemento(Celula **lista, Post d){
	
	
	 	if (listaVazia(lista)){ //Verificação da lista vazia
	 		printf ("\n        !!! ATENCAO: Postagem nao encontrada !!!");
	 		return 0;
	 	}
	 	
	 
	 Celula *aux = (*lista)->prox; //pega a primeira celula
	 
	 	if (aux == (*lista)){ 
	 		
	 		if (strcmp(d.titulo, aux->info.titulo) == 0){ 
				
			(*lista) = NULL;
			free(aux);
			return 1;
		
			}
		}
	
		do {
			
			if (strcmp(d.titulo, aux->info.titulo) == 0){
			
				aux->ant->prox= aux->prox;
				aux->prox->ant= aux->ant;
			
				if(aux == (*lista)){
					(*lista) = aux->ant;
				}
				
				free(aux);
				return 1;
			}
					
			aux = aux->prox;
			
		}while(aux != (*lista)->prox);
	
}

void PostagemDeDestaque(Celula **lista, char titulo[]){
	
		if (listaVazia(lista)){
			printf ("\n        !!! ATENCAO: Postagem nao encontrada !!!");
			return;
		}
	
	Celula* aux = PesquisarElemento(lista, titulo);  //Função pesquisar retorna o elemento

		if(aux == NULL){ //Caso a postagem pesquisada não exista
			printf ("\n        !!! ATENCAO: Postagem nao encontrada !!!");
			return;
		}	
			
		if (aux == (*lista)){ //Caso o elemento pesquisado seja o ultimo da lista 
			
			(*lista)= (*lista)->ant; //se passa o ponteiro lista para seu anterior, fazendo dele o novo ultimo elemento
			
		}else{ //Caso não seja o ultimo elemento
				aux->prox->ant = aux -> ant;
				aux->ant->prox = aux->prox;
				aux->prox = (*lista)->prox;
				aux->ant=(*lista);
				(*lista)->prox->ant = aux;
				(*lista)->prox=aux;
		}	
		printf("\n        --= POSTAGEM destacada com SUCESSO! =-- ");
}

void menu(){
	
	printf ("\n                 ------------=== MENU ===------------\n");
	printf ("                    Escolha umas das opções abaixo:\n");		
	printf ("\n                    [1] Escrever uma postagem");
	printf ("\n                    [2] Remover uma postagem");			
	printf ("\n                    [3] Pesquisar uma postagem");
	printf ("\n                    [4] Exibir todas as postagens");
	printf ("\n                    [5] Selecionar postagem de destaque");
	printf ("\n                    [6] Informações do projeto");
	printf ("\n                    [7] Sair do sistema");
	
}

void informacao(){
	
	printf ("\n\n      ---====  INFORMACOES DO PROJETO  ====---\n\n");
   	printf ("              -== Sobre o projeto: ==-\n");
   	printf ("   Esse  sistema  tem  como objetivo ser  uma plataforma\n");
   	printf ("   de centralização das informações da Universidade\n");
   	printf ("   Federal de Viçosa campus Rio Paranaíba!\n");
   			
   	printf ("              -== Sobre o sistema: ==-\n");
   	printf ("               --Desenvolvido por:--\n");
   	printf ("          Diego Willian Lima Queiroz - 5222\n");
   	printf ("          Matheus Medeiros Santana - 5188\n");
   	printf ("            --Professor orientador:--\n");
   	printf ("                  Joao Batista");
	
}

int main(){
	
	setlocale(LC_ALL, "Portuguese"); //Faz alterar a linguagem para portugues
	system("mode con: cols=75 lines=40"); //Redimensiona o tamanho da tela de execução
	system("color 70");//muda a cor
	
	Celula *ptr;
	Post d;
	inicializar(&ptr);
	int num;
	
	printf("\n"); 
	printf("  =====================================================================\n");
	printf("  ||                     SEJA BEM VINDO(A) AO                         || \n");
	printf("  ||         PCI - Plataforama de centralização de informação         || \n");
	printf("  =====================================================================\n");
	
		Post e;//Exemplos de postagens do programa
		Post f;
		Post g;
		
		strcpy(e.titulo, "Exemplo 3");
		strcpy(e.descricao, "Lorem Ipsum é simplesmente uma simulação de texto da indústria tipográfica e de impressos, e vem sendo utilizado desde o século XVI, quando um impressor desconhecido pegou uma bandeja de tipos e os embaralhou para fazer um livro de modelos de tipos.");

		InserirOrdenado(&ptr,e);
		
		strcpy(f.titulo, "Exemplo 2");
		strcpy(f.descricao, "Lorem Ipsum é simplesmente uma simulação de texto da indústria tipográfica e de impressos, e vem sendo utilizado desde o século XVI, quando um impressor desconhecido pegou uma bandeja de tipos e os embaralhou para fazer um livro de modelos de tipos.");

		InserirOrdenado(&ptr,f);
		
		strcpy(g.titulo, "Exemplo 1");
		strcpy(g.descricao, "Lorem Ipsum é simplesmente uma simulação de texto da indústria tipográfica e de impressos, e vem sendo utilizado desde o século XVI, quando um impressor desconhecido pegou uma bandeja de tipos e os embaralhou para fazer um livro de modelos de tipos.");

		InserirOrdenado(&ptr,g);
		
		
		do{
		
		do{
			menu();
			fflush(stdin);
			printf("\n\n           --> Digite uma opcao do MENU: ");
			scanf ("%d", &num);
			fflush(stdin);
			
		}while(num<0 || num>7);
		
			switch (num){
			
   				case 1:

					printf("\n\n      ---====  CADASTRAR NOVA POSTAGEM  ====---\n\n");	
   					printf(" - Titulo: ");		
					fflush(stdin);
					gets(d.titulo);
					printf(" - Descricao: ");
					fflush(stdin);
					gets(d.descricao);
		
   					InserirOrdenado(&ptr, d);
   					printf("\n      --= POSTAGEM realizada com SUCESSO! =-- ");
   					num=0;
   					break;
   			
  				case 2:
  					printf("\n\n      ---====  REMOVER POSTAGEM CADASTRADA ====---\n\n");
  					printf (" - Digite o TITULO da postagem a ser removida: ");
					fflush(stdin);
					gets(d.titulo);
					
						if(RemoverElemento(&ptr, d) == 1)
							printf("\n      --= POSTAGEM removida com SUCESSO! =-- ");
						else 
							printf("\n      --= POSTAGEM nao encontrada =-- ");
					num = 0;
   					break;

  				case 3:
  					printf("\n\n      ---====  PESQUISAR POSTAGEM DESEJADA  ====---\n\n");
  					printf (" - Digite o NOME da postagem a ser pesquisada: ");
					fflush(stdin);
					gets(d.titulo);
					
  					ExibirUnico(&ptr, d.titulo);
  					num=0;
  					break;

				case 4:
					printf("\n\n      ---====  EXIBIR TODAS AS POSTAGENS  ====---\n\n");
					
					ExibirTudo(&ptr);
					num=0;
   					break;
   		
   				case 5:
   					printf("\n\n      ---====  SELECIONAR POSTAGEM DE DESTAQUE  ====---\n\n");
   					printf (" - Digite o NOME da postagem a ser destacada: ");
					fflush(stdin);
					gets(d.titulo);
					
					PostagemDeDestaque(&ptr, d.titulo); 
					num=0;
					break;
		   
   				case 6:
   					informacao();
   					num=0;
   					break;
   			
   				case 7:
		 		  exit(1);
		 		  num=0;
		  			 break;
		   	
  				default:
  					printf ("\n        !!! ATENCAO: Opção invalida, tente novamente !!!");
  					num=0;
  					break;
  			}
  			
		}while(num != '7');
		
	return 0;
}
