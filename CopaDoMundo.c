#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>


struct paises{
    char nomePais[20];
    char grupo;
    struct paises *prox, *ant;
    struct jogadores *jog;

}paises;

struct jogadores {
    char nomeJogador[20];
    char posicao[20];
    char time[20];
    struct paises *pais;
    struct jogadores *pEsquerda, *pDireita;
}jogadores;

//variavel global
int countGlobal=0;
int contadorJog =0;
int encontrouJog =0;
int podeInserir=0;
int podeModificar=0;

void inserePais(struct paises **inicio, struct paises **fim, char nome[], char grupo){

    struct paises * ptaux = (struct paises *) malloc ( sizeof ( struct paises ));

        strcpy(ptaux->nomePais,nome);
        ptaux->grupo = grupo;
        ptaux->jog = NULL;

        if (* inicio == NULL || strcmp((* inicio )->nomePais,nome)>0 )
        {
        ptaux -> prox =* inicio ;
        ptaux -> ant = NULL ;
        if (* inicio != NULL ) (* inicio )-> ant = ptaux ;
        else * fim = ptaux ;
        * inicio = ptaux ;
        return ;
		}
        struct paises * ptaux2 =* inicio ;
        while ( ptaux2 -> prox != NULL && strcmp(ptaux2 ->prox ->nomePais,nome)<0 ) ptaux2 = ptaux2 -> prox ;
        ptaux -> prox =ptaux2 -> prox ;
        ptaux -> ant = ptaux2 ;
        ptaux2 -> prox = ptaux ;
        if (ptaux -> prox == NULL ) // inserção no final da lista
        (* fim )= ptaux ;
        else
        ptaux ->prox -> ant = ptaux ;
        return ;

}

struct jogadores *inserirJogadores(struct jogadores *pRaiz, char nome[], char posicao[], char time[], char pais[], struct paises *paisNodo){

    if (pRaiz == NULL){
        pRaiz = (struct jogadores *) malloc(sizeof(struct jogadores));
        pRaiz->pEsquerda = NULL;
        pRaiz->pDireita = NULL;

        strcpy(pRaiz->nomeJogador, nome);
        strcpy(pRaiz->posicao, posicao);
        strcpy(pRaiz->time, time);

        //vincula o jogador ao país
        pRaiz->pais = paisNodo;

        return pRaiz;
    }

   else if (strcmp(nome, pRaiz->nomeJogador) <= 0 ) {
                pRaiz->pEsquerda =inserirJogadores(pRaiz->pEsquerda, nome, posicao, time, pais, paisNodo);
    }

   else if (strcmp(nome, pRaiz->nomeJogador) > 0 ) {
                pRaiz->pDireita = inserirJogadores(pRaiz->pDireita, nome, posicao, time, pais, paisNodo);
    }

    return pRaiz;
}

void escrevePaises(struct paises *inicio){

    struct paises *inic = inicio;

    if(inic == NULL){
        printf("Lista vazia\n");
        return;
    }

    while (inic){
      printf("Pais: %s - Grupo: %c\n",inic->nomePais, inic->grupo);
      inic=inic->prox;
    }
}

int mostraJogadores(struct jogadores *raiz){

    if(raiz == NULL ) {
        return;
    }
    mostraJogadores(raiz->pEsquerda);
    printf ("\n%s - %s - %s - %s",raiz->nomeJogador, raiz->posicao, raiz->time, raiz->pais->nomePais);
    mostraJogadores(raiz->pDireita);

    return contadorJog++;

}

void mostraJogadoresPais(struct paises *inicio, char pais[]){
    struct paises *ptaux = inicio;
    while(strcmp(ptaux->nomePais, pais) != 0 && ptaux != NULL) ptaux = ptaux->prox;

    //encontrou selecao
    if(ptaux != NULL){
        if(ptaux->jog == NULL){
            printf ("\nSelecao sem jogadores cadastrados");
            return;
        }
        else{
            printf("\nSelecao: %s \n", ptaux->nomePais);
            mostraJogadores(ptaux->jog);
            printf("\n");
        }
    }
    return;
}

int verificaSelecao(struct paises *ini, char selecao[]){

    struct paises *ptaux = ini;
    while(ptaux != NULL){
        if(strcmp(ptaux->nomePais, selecao) == 0) return 1;
        ptaux = ptaux->prox;
    }

    return 0;
}

int verificaJogadorInsercao(struct jogadores *raiz, char nome[]){

    if(raiz == NULL) return 0; //pode inserir
    else if(strcmp(raiz->nomeJogador, nome) == 0){
            podeInserir = 1;
            return;
    }

    verificaJogadorInsercao(raiz->pEsquerda, nome);
    verificaJogadorInsercao(raiz->pDireita, nome);

    return;

}

int verificaJogadorModificao(struct jogadores *raiz, char nome[]){

    if(raiz == NULL) return 0; //pode inserir
    else if(strcmp(raiz->nomeJogador, nome) == 0){
            podeModificar = 1;
            return;
    }

    verificaJogadorModificao(raiz->pEsquerda, nome);
    verificaJogadorModificao(raiz->pDireita, nome);

    return;
}

void verificaJogadorPrinta(struct jogadores *raiz, char nome[]){

    if(raiz == NULL) return; //pode inserir
    else if(strcmp(raiz->nomeJogador, nome) == 0){
        printf("\nNome: %s - Posicao: %s - Clube: %s - ",raiz->nomeJogador,raiz->posicao,raiz->time);
        encontrouJog = 1;
        return;
    }

    verificaJogadorPrinta(raiz->pEsquerda, nome);
    verificaJogadorPrinta(raiz->pDireita, nome);

    return;
}


void pesquisaJogadores(char nomejogador[], struct paises *inicio)
{
    struct paises *ptaux = inicio;
    encontrouJog =0;
    while(ptaux != NULL && !encontrouJog){
        verificaJogadorPrinta(ptaux->jog, nomejogador);
        if(encontrouJog){
                printf("Pais: %s\n",ptaux->nomePais);
                return;
        }
        ptaux = ptaux->prox;
    }

    if(!encontrouJog) printf("\nJogador nao convocado\n");

    return;
}

void verificaGoleiros(struct jogadores *raiz){

    if(raiz == NULL) return;
    else if(strcmp(raiz->posicao, "Goleiro") == 0){
        countGlobal++;
        printf("\nNome: %s - Clube: %s - Pais: %s\n",raiz->nomeJogador,raiz->time, raiz->pais);
    }

    verificaGoleiros(raiz->pEsquerda);
    verificaGoleiros(raiz->pDireita);

    return;
}


void goleiros(struct paises *inicio)
{
    struct paises *ptaux = inicio;
    int encontrou = 0;
    while(ptaux != NULL){
        verificaGoleiros(ptaux->jog);
        ptaux = ptaux->prox;
    }

    printf("\nTotal de Goleiros na Copa: %d",countGlobal);

    return;

}

struct jogadores *modificaJogador(struct jogadores *pRaiz, char nome[], char posicao[], char time[], struct paises *inicio)
{

	if(strcmp(pRaiz->nomeJogador, nome) == 0){
        strcpy(pRaiz->posicao,posicao);
        strcpy(pRaiz->time, time);
        return pRaiz;

	}
    else if (strcmp(nome, pRaiz->nomeJogador) < 0 ) {
                pRaiz->pEsquerda =modificaJogador(pRaiz->pEsquerda, nome, posicao, time, inicio);
    }

    else if (strcmp(nome, pRaiz->nomeJogador) > 0 ) {
                pRaiz->pDireita = modificaJogador(pRaiz->pDireita, nome, posicao, time, inicio);
    }

	return pRaiz;
}

void procuraJogadorLetra(struct jogadores *raiz, char letra){


    if(raiz == NULL) return;
    else if(raiz->nomeJogador[0] == letra){
        printf("\nNome: %s - Clube: %s - Pais: %s\n",raiz->nomeJogador,raiz->time, raiz->pais);
    }

    procuraJogadorLetra(raiz->pEsquerda, letra);
    procuraJogadorLetra(raiz->pDireita, letra);

    return;
}

void pesquisaJogadoresLetra(struct paises *inicio, char letra){

    struct paises *ptaux = inicio;
    while(ptaux != NULL){
        procuraJogadorLetra(ptaux->jog, letra);
        ptaux = ptaux->prox;
    }

}

void removeEnter(char string[]){

    int i;
    while(string[i]!='\0' && string[i]!='\n'){
        i++;
    }
    string[i]='\0';
}

int existePais(struct paises *inicio,char nomePais[]){

    struct paises *ptaux = inicio;
    int encontrou = 0;
    while(ptaux != NULL && !encontrou){
        if(strcmp(ptaux->nomePais, nomePais) == 0) encontrou = 1;
        ptaux = ptaux->prox;
    }

    return encontrou;

}

void menu(){
    printf("1 - Inserir jogador\n");
    printf("2 - Modificar jogador\n");
    printf("3 - Remover jogador - NAO IMPLEMENTADA\n");
    printf("4 - Pesquisar jogador\n");
    printf("5 - Exibir todos jogadores\n");
    printf("6 - Exibir jogadores de um pais\n");
    printf("7 - Exibir goleiros da copa\n");
    printf("8 - Pesquisar pela primeira letra\n");
    printf("9 - Mostrar todos paises\n");
    printf("A - Cadastrar selecoes\n");
    printf("0 - Sair");
}


int main(){

    struct paises *inicio = NULL;
    struct paises *fim = NULL;
    char resp;

    struct jogadores *raiz = (struct jogadores *)malloc(sizeof(struct jogadores *));
    raiz = NULL;

    /*CARGA INICIAL DE PAISES*/
    inserePais(&inicio,&fim,"Brasil",'E');
    inserePais(&inicio,&fim,"Argentina",'C');
    inserePais(&inicio,&fim,"Alemanha",'F');
    inserePais(&inicio,&fim,"Belgica",'H');
    inserePais(&inicio,&fim,"Uruguai",'A');
    inserePais(&inicio,&fim,"Espanha",'B');

    struct paises *ini = inicio; //mantem valor original do inicio

    /*CARGA DE JOGADORES*/
    struct paises *ptaux2 = inicio;
    while(strcmp(ptaux2->nomePais, "Brasil") != 0) ptaux2 = ptaux2->prox;
    //recebe pointer
    ptaux2->jog = inserirJogadores(ptaux2->jog, "Neymar", "Atacante", "PSG", "Brasil", ptaux2);
    //precisa jogar no pais que o pointer pertence
     while(strcmp(inicio->nomePais, "Brasil") != 0) inicio = inicio->prox;
    inicio->jog = ptaux2->jog;
    inicio = ini;
    ptaux2 = inicio;

    while(strcmp(ptaux2->nomePais, "Argentina") != 0) ptaux2 = ptaux2->prox;
    ptaux2->jog = inserirJogadores(ptaux2->jog, "Messi", "Meia-Atacante", "Barcelona", "Argentina", ptaux2);
    while(strcmp(inicio->nomePais, "Argentina") != 0) inicio = inicio->prox;
    inicio->jog = ptaux2->jog;
    inicio = ini;
    ptaux2 = inicio;

    while(strcmp(ptaux2->nomePais, "Brasil") != 0) ptaux2 = ptaux2->prox;
    ptaux2->jog = inserirJogadores(ptaux2->jog, "Coutinho", "Meio-Campo", "Barcelona", "Brasil", ptaux2);
    while(strcmp(inicio->nomePais, "Brasil") != 0) inicio = inicio->prox;
    inicio->jog = ptaux2->jog;

    inicio = ini;
    ptaux2 = inicio;

    while(strcmp(ptaux2->nomePais, "Alemanha") != 0) ptaux2 = ptaux2->prox;
    ptaux2->jog = inserirJogadores(ptaux2->jog, "Hummels", "Zagueiro", "Bayern de Munique", "Alemanha", ptaux2);
    while(strcmp(inicio->nomePais, "Alemanha") != 0) inicio = inicio->prox;
    inicio->jog = ptaux2->jog;

    inicio = ini;
    ptaux2 = inicio;

    while(strcmp(ptaux2->nomePais, "Alemanha") != 0) ptaux2 = ptaux2->prox;
    ptaux2->jog = inserirJogadores(ptaux2->jog, "Kross", "Meio-Campo", "Real Madrid", "Alemanha", ptaux2);
    while(strcmp(inicio->nomePais, "Alemanha") != 0) inicio = inicio->prox;
    inicio->jog = ptaux2->jog;

    inicio = ini;
    ptaux2 = inicio;

	while(strcmp(ptaux2->nomePais, "Uruguai") != 0) ptaux2 = ptaux2->prox;
    ptaux2->jog = inserirJogadores(ptaux2->jog, "Muslera", "Goleiro", "Galatasaray", "Uruguai", ptaux2);
    while(strcmp(inicio->nomePais, "Uruguai") != 0) inicio = inicio->prox;
    inicio->jog = ptaux2->jog;

    inicio = ini;
    ptaux2 = inicio;

	while(strcmp(ptaux2->nomePais, "Uruguai") != 0) ptaux2 = ptaux2->prox;
    ptaux2->jog = inserirJogadores(ptaux2->jog, "Suarez", "Atacante", "Barcelona", "Uruguai", ptaux2);
    while(strcmp(inicio->nomePais, "Uruguai") != 0) inicio = inicio->prox;
    inicio->jog = ptaux2->jog;

    inicio = ini;
    ptaux2 = inicio;

	while(strcmp(ptaux2->nomePais, "Espanha") != 0) ptaux2 = ptaux2->prox;
    ptaux2->jog = inserirJogadores(ptaux2->jog, "Isco", "Meio-Campo", "Real Madrid", "Espanha", ptaux2);
    while(strcmp(inicio->nomePais, "Espanha") != 0) inicio = inicio->prox;
    inicio->jog = ptaux2->jog;

    inicio = ini;
    ptaux2 = inicio;

	while(strcmp(ptaux2->nomePais, "Brasil") != 0) ptaux2 = ptaux2->prox;
    ptaux2->jog = inserirJogadores(ptaux2->jog, "Alisson", "Goleiro", "Roma", "Brasil", ptaux2);
    while(strcmp(inicio->nomePais, "Brasil") != 0) inicio = inicio->prox;
    inicio->jog = ptaux2->jog;

    inicio = ini;
    ptaux2 = inicio;

	while(strcmp(ptaux2->nomePais, "Belgica") != 0) ptaux2 = ptaux2->prox;
    ptaux2->jog = inserirJogadores(ptaux2->jog, "Hazard", "Ponta", "Chelsea", "Belgica", ptaux2);
    while(strcmp(inicio->nomePais, "Belgica") != 0) inicio = inicio->prox;
    inicio->jog = ptaux2->jog;

    inicio = ini;
    ptaux2 = inicio;


    struct paises *ptaux = ini;
    menu();
    printf("\nDigite sua opcao: ");
    resp=getch();
    fflush(stdin);

    while(resp == 'A' || (resp>='1') && (resp<='9')){
        switch(resp){
        case '1': printf("\nDigite a selecao do jogador: ");
                  char selecao[25];
                  gets(selecao);
                  if(verificaSelecao(inicio, selecao)){
                    printf("\nDigite o nome do jogador: ");
                    char nome[25];
                    gets(nome);
                    struct paises *p = inicio;
                    while(strcmp(p->nomePais,selecao) != 0) p = p->prox;
                    podeInserir = 0;
                    verificaJogadorInsercao(p->jog, nome);
                    if(!podeInserir){
                            printf("\nDigite a posicao: ");
                            char posicao[25];
                            gets(posicao);
                            printf("\nDigite o clube em que joga: ");
                            char clube[25];
                            gets(clube);

                            struct paises *ptaux2 = inicio;
                            while(strcmp(ptaux2->nomePais, selecao) != 0) ptaux2 = ptaux2->prox;
                            ptaux2->jog = inserirJogadores(ptaux2->jog, nome, posicao, clube, selecao, ptaux2);
                            //precisa jogar no pais que o pointer pertence
                            while(strcmp(inicio->nomePais, selecao) != 0) inicio = inicio->prox;
                            inicio->jog = ptaux2->jog;
                            inicio = ini;
                            ptaux2 = inicio;
                            printf("Jogador inserido com sucesso!");
                    }
                    else printf("Jogador ja cadastrado para selecao.\n");
                    break;

                  }
                  else printf("Selecao nao esta na copa.\n");
                  break;

        case '2': printf("\nDigite a selecao do jogador: ");
                  char selecao2[25];
                  gets(selecao2);
                  if(verificaSelecao(inicio, selecao2)){
                    printf("\nDigite o nome do jogador: ");
                    char nome[25];
                    gets(nome);
                    struct paises *p = inicio;
                    while(strcmp(p->nomePais,selecao2) != 0) p = p->prox;
                    podeModificar = 0;
                    verificaJogadorModificao(p->jog, nome);
                    if(podeModificar){
                            printf("\nDigite a nova posicao: ");
                            char posicao[25];
                            gets(posicao);
                            printf("\nDigite o novo clube em que joga: ");
                            char clube[25];
                            gets(clube);

                            struct paises *ptaux3 = inicio;
                            while(strcmp(ptaux3->nomePais, selecao2) != 0) ptaux3 = ptaux3->prox;
                            ptaux3->jog = modificaJogador(ptaux3->jog, nome, posicao, clube, ptaux3);
                            //precisa jogar no pais que o pointer pertence
                            while(strcmp(inicio->nomePais, selecao2) != 0) inicio = inicio->prox;
                            inicio->jog = ptaux3->jog;
                            inicio = ini;
                            ptaux3 = inicio;
                            printf("Jogador modificado com sucesso!\n");
                    }
                    else printf("Jogador nao existe.\n");
                  }
                  else printf("Selecao nao esta na copa.\n");
                  break;

        case '4': printf("\nDigite o jogador: ");
                  char nomeJog[25];
                  fflush(stdin);
                  gets(nomeJog);
                  encontrouJog = 0;
                  pesquisaJogadores(nomeJog, ini);
                  break;

        case '5': ptaux = ini;
                  contadorJog=0;
                  while(ptaux != NULL){
                       printf("\nSelecao: %s", ptaux->nomePais);
                       mostraJogadores(ptaux->jog);
                       ptaux = ptaux->prox;
                       printf("\n");
                   }
                   printf("\nTotal jogadores: %d",contadorJog);
                break;

        case '6': printf("\nDigite a selecao: ");
                  char selecao3[25];
                  gets(selecao3);
                  contadorJog=0;
                  if(verificaSelecao(inicio, selecao3)){
                     mostraJogadoresPais(inicio, selecao3);
                     printf("\nNumero de jogadores da selecao: %d\n", contadorJog);
                  }
                  else printf("\nSelecao nao esta na copa.");
                  break;

        case '7': countGlobal = 0;
                  goleiros(inicio);
                  break;

        case '8': printf("\nDigite a letra a pesquisar: ");
                  fflush(stdin);
                  char letra;
                  scanf("%c", &letra);
                  removeEnter(letra);
                  pesquisaJogadoresLetra(inicio, letra);
                  break;

        case '9': printf("\n");
                  escrevePaises(inicio);
                  break;

        case 'A': printf("\nDigite o nome do pais:");
                  char nomePais[25];                  gets(nomePais);
                  if(!existePais(inicio, nomePais)){
                    printf("\nDigite o grupo do pais: ");
                    fflush(stdin);
                    char grupoPais;
                    scanf("%c", &grupoPais);
                    removeEnter(grupoPais);
                    inserePais(&inicio, &fim, nomePais, grupoPais);
                    printf("\nPais cadastrado com sucesso!");
                  }
                  else printf("\nSelecao ja esta na cadastrada na Copa!\n");
                  break;

        }

        printf("\n");
        menu();
  		fflush(stdin);
  		printf("\nDigite sua opcao:\n");
		resp=getch();

    }

}
