// Allan Ogawa - RA: 21105670-2
// ESoft - 3 semestre - 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define n 2400


//=====================================================================================================================
//==-----------------------------------------------------------------------------------------------------------------==
//== VARIAVEIS UNIVERSAIS  ============================================================================================
//==-----------------------------------------------------------------------------------------------------------------==
//=====================================================================================================================

FILE *arq;

struct estrutura{
	float dolar, real;     // preços em dolar e em real
	char  nome[200];       // nome do produto
	char  codigo[20];      // codigo usado no programa
	char  codigo2[20];	   // codigo usado no arquivo
	int   codigoint;       // codigo em int para classificacao
	int   editado = 0;     // editado = 0 - não houve edição
						   // editado = 1 - criado
						   // editado = 2 - editado
						   
} dados [n];

char  cabecalho[10] [200]; // cabeçalho do arquivo texto
float reais;               // constante da cotação definido pelo usuario
bool  entrada;             // entrada da tabela


//-- variaveis temporarias entre outros ----------------------
int  cont=0, tipodeclass=0;
int  x=0, y=0, z=0, del=0;
char codDel[n][20];


//=====================================================================================================================
//==-----------------------------------------------------------------------------------------------------------------==
//== PROCEDIMENTOS  ===================================================================================================
//==-----------------------------------------------------------------------------------------------------------------==
//=====================================================================================================================


//-- MENU -------------------------------------------------
void caixa         (char* a);
void cotacao       ();
void menuprincipal ();
void creditos      ();
void printdelay    (char* string,int tempo);

//-- CRUD -------------------------------------------------
void menuCRUD    ();
int  criarItem   ();
int  alterarItem ();			
int  deletarItem ();
void salvaTabela ();


//-- LEITURA ----------------------------------------------
void leitura      ();
void leituraedit  ();
void removeEspaco (char* string);


//-- PROCURA E TABELA -------------------------------------
int procura      ();
int stringColada (int n1, int n2, int x, int y, int tam);
int tabela       ();


//-- PREÇO ------------------------------------------------
int alteracaoPreco ();
int procuraPreco   ();


//-- CLASSIFICAÇÃO ----------------------------------------
void classificacao (int tipo);
void troca         (int a,int b);



//=====================================================================================================================
//==-----------------------------------------------------------------------------------------------------------------==
//== PROGRAMA PRINCIPAL ===============================================================================================
//==-----------------------------------------------------------------------------------------------------------------==
//=====================================================================================================================

int main (){
	
	cotacao ();
	leitura ();
	leituraedit ();
	if( entrada == false){
		caixa  ("ERRO     ");
		printf ("\n    !ERRO NO CARREGAMENTO DA TABELA!\n\n");
	}
	else{
		menuprincipal ();
		salvaTabela();
	}

	return 0;
}



//=====================================================================================================================
//==-----------------------------------------------------------------------------------------------------------------==
//== M E N U S  =======================================================================================================
//==-----------------------------------------------------------------------------------------------------------------==
//=====================================================================================================================


//===========================================================================================================
//== CAIXA USADA PARA POR O TITULO NOS MENUS ================================================================
void caixa (char* a){
	
	printf ("    ");
	
	for (x=0; x<28; x++)
		printf ("="); //linha 1 printa   ===============
		
	for (x=0; x<3; x++){
		if (x != 1){ // linha 2 e 4 printa   |          |
			printf ("\n%5c", '=');
			printf ("%27c",  '=');
		}
		else // linha 3 printa   |  (palavra)  |
			printf ("\n%5c%20s%7c", '=', a, '=');	
	}
	
	printf ("\n    ");
	
	for (x=0; x<28; x++) // linha 5 printa   ===============
		printf ("=");
		
	printf ("\n");
}


//===========================================================================================================
//== ENTRADA DA COTAÇÃO DE DOLAR PARA REAL ==================================================================
void cotacao (){
	
	caixa  ("COTACAO DO DOLAR");
	printf ("\n    QUAL E A COTACAO ATUAL DO DOLAR PARA REAIS? ");
	printf ("\n    (INSERIR APENAS NUMERO E PONTO)");
	printf ("\n    1 DOLAR = ");
	
	scanf  ("%f", &reais);
	fflush (stdin);
	system ("cls");
}


//===========================================================================================================
//== MENU PRINCIPAL =========================================================================================
void menuprincipal (){
	
	int opcao=999, saida=0;
	
	do{
		system ("cls");
		caixa  ("MENU PRINCIPAL");
		printf ("\n    COTACAO DO DOLAR PARA REAL: 1 DOLAR = %.2f REAIS \n", reais);
		printf ("\n    1 - CLASSIFICAR POR PRECO");
		printf ("\n    2 - CLASSIFICAR POR CODIGO");
		printf ("\n    3 - CLASSIFICAR POR NOME\n");
		
		printf ("\n    4 - MOSTRAR A TABELA");
		printf ("\n    5 - FAZER BUSCA POR CODIGO E/OU PALAVRA-CHAVE");
		printf ("\n    6 - FAZER BUSCA POR PRECO");
		printf ("\n    7 - FAZER ALTERACAO DE PRECO");
		printf ("\n    8 - C.R.U.D.");
		printf ("\n    9 - Creditos\n");
		printf ("\n    0 - SAIR \n");
		
		printf ("\n    DIGITE O QUE QUER FAZER: ");
		scanf  ("%d", &opcao);
		fflush (stdin);
		
		switch (opcao){			
			case 0:
				saida = 1;
				break;	
				
			case 1:
				if (tipodeclass != 1){
					classificacao (1);
					printf ("\n    >>CLASSIFICADO POR PRECO<<, ");
				}
				else
					printf ("\n    >>JA CLASSIFICADO POR PRECO<<, ");
					
				system ("pause");
				break;
				
			case 2:
				if (tipodeclass != 2){
					classificacao (2);
					printf ("\n    >>CLASSIFICADO POR CODIGO<<, ");
				}
				else
					printf ("\n    >>JA CLASSIFICADO POR CODIGO<<, ");
					
				system ("pause");
				break;
				
			case 3:
				if (tipodeclass != 0){
					classificacao (3);
					printf ("\n    >>CLASSIFICADO POR NOME<<, ");
				}
				else
					printf ("\n    >>JA CLASSIFICADO POR NOME<<, ");
					
				system ("pause");
				break;
				
			case 4:
				system ("cls");
				tabela ();
				
				break;
				
			case 5:
				system ("cls");
				procura ();
				
				break;
				
			case 6:
				system ("cls");
				procuraPreco ();
				
				break;
			
			case 7:
				system ("cls");
				alteracaoPreco ();
				
				break;
			
			case 8:
				system ("cls");
				menuCRUD ();
				
				break;
				
			case 9:
				system ("cls");
				creditos ();
				
				break;
		}
	} while (saida!=1);
}


//===========================================================================================================
//== CREDITOS DO PROGRAMA ===================================================================================
void creditos (){
	
	caixa ("CREDITOS   ");
	
	printdelay ("\n    Docente:      ",             40);
	printdelay ("Edson Alexandre Domingues Moreno", 60);

	printdelay ("\n    Aluno:        ", 40);
	printdelay ("Allan Ogawa",          60);
	
	printdelay ("\n    Ano:          ", 40);
	printdelay ("2022 - 3 Semestre",    60);
	
	printdelay ("\n    Universidade: ", 40);
	printdelay ("UniCesumar",           60);
	
	printdelay ("\n    Curso:        ",             40);
	printdelay ("Engenharia de Software - Noturno", 60);
	                              
	printf ("\n\n    ");
	system ("pause");
}


//===========================================================================================================
//== PRINTA TEXTO COM DELAY DEFINIDO PELO USER ==============================================================
void printdelay (char* string,int tempo){
	
	for (x=0; x<strlen(string); x++){
		printf ("%c", string[x]);
		_sleep (tempo);
	}
	
}



//=====================================================================================================================
//==-----------------------------------------------------------------------------------------------------------------==
//== C  R  U  D  ======================================================================================================
//==-----------------------------------------------------------------------------------------------------------------==
//=====================================================================================================================


//===========================================================================================================
//== MENU CRUD ==============================================================================================
void menuCRUD (){
	
	int opcao=999, saida=0;
	
	do{
		system ("cls");
		caixa  ("MENU C.R.U.D ");
		printf ("\n    COTACAO DO DOLAR PARA REAL: 1 DOLAR = %.2f REAIS \n", reais);
		printf ("\n    1 - CRIAR");
		printf ("\n    2 - ALTERAR");
		printf ("\n    3 - DELETAR");
		printf ("\n    4 - ATUALIZAR TABELA\n");
		printf ("\n    0 - VOLTAR\n");
		
		printf ("\n    DIGITE O QUE QUER FAZER: ");
		scanf  ("%d", &opcao);
		fflush (stdin);
		
		switch (opcao){
			case 0:
				saida = 1;
				break;	
				
			case 1:
				system ("cls");
				criarItem ();
				break;
				
			case 2:
				system ("cls");
				alterarItem ();
				break;
				
			case 3:
				system ("cls");
				deletarItem ();
				break;	
				
			case 4:
				printf ("    Atualizando...  ");
				salvaTabela ();
				system ("pause");
				break;
		}
	} while (saida!=1);
}


//===========================================================================================================
//== CRIAR NOVO ITEM ========================================================================================
int criarItem (){
	
	char  novocod[200], novonome[200], tmp[200];
	float novodolar, retorno;
	
	do{ //repetir se o codigo nao tiver tamanho entre 4 e 7, e/ou for existente na tabela 
		z = 0;
		caixa  ("CRIAR     ");
		printf ("\n    (Coloque 0 no CODIGO para retornar ao menu C.R.U.D.)");
		printf ("\n    (1U$=R$%.2f)",reais);
		printf ("\n\n    CODIGO(de 4 a 7 digitos): ");
		gets   (novocod);
		retorno = strcmp(novocod,"0");
		if (retorno == 0){
			return 0;
		}
		
		novocod[strlen(novocod)] = '\0';
		
		for (x=0; x<cont; x++){
			y = strcmp (novocod, dados[x].codigo);
			if (y==0)
				z++;
		}
		
		system ("cls");
		
	} while (z>0 || (strlen(novocod)<4 || strlen(novocod)>7) );

	caixa  ("CRIAR     ");
	printf ("\n\n    (1U$=R$%.2f)", reais);
	printf ("\n\n    CODIGO(de 4 a 7 digitos): %s", novocod);
	printf ("\n    NOME DO PRODUTO: ");
	gets   (novonome);
	novonome[strlen(novonome)] = '\0';
	
	system ("cls");
	caixa  ("CRIAR     ");
	printf ("\n\n    (1U$=R$%.2f)", reais);
	printf ("\n\n    CODIGO(de 4 a 7 digitos): %s", novocod);
	printf ("\n    NOME DO PRODUTO: %s", novonome);
	printf ("\n    VALOR DO PRODUTO(APENAS NUMEROS E PONTO): ");
	scanf  ("%f", &novodolar);
	fflush ( stdin);
	
	removeEspaco (novocod);
	removeEspaco (novonome);
	
	strcpy (dados[cont].codigo2, novocod);
	strcpy (tmp, novocod);
	
	if (strlen(dados[cont].codigo2) <= 6){ //se o codigo tiver tamanho entre 6 e 4, ele recebe um espaço no começo para mostar na tabela
		for (x=1; x<strlen(dados[cont].codigo2)+1; x++){
			dados[cont].codigo2[0] = ' ';
			dados[cont].codigo2[x] = tmp[x-1];
		}
		for (x=strlen(dados[cont].codigo2); x<=6; x++)
			dados[cont].codigo2[x] = ' ';
	}
	
	dados[cont].codigo2 [strlen(dados[cont].codigo2)] = '\0';
	
	dados[cont].editado = 1;
	
	strcpy (dados[cont].codigo, novocod);
	dados[cont].codigoint = atoi(novocod);
	
	strcpy (dados[cont].nome, novonome);
	
	dados[cont].dolar = novodolar;
	dados[cont].real  = novodolar*reais;
	
	
	cont++;
	
	salvaTabela(); //salva a tabela
	return 0;
}		

	
//===========================================================================================================
//== ALTERAR ITEM EXISTENTE =================================================================================
int alterarItem (){
	
	char  cod[200], novonome[200], tmp[200];
	int   opcao, i, retorno;
	float novodolar;
	
	do{ //repetir ate encontrar um codigo existente na tabela
		z = 1;
		caixa  ("ALTERAR   ");
		printf ("\n    (Coloque 0 no CODIGO para retornar ao menu C.R.U.D.)");
		printf ("\n    (1U$=R$%.2f)",reais);
		printf ("\n\n    CODIGO EXISTENTE NA TABELA: ");
		gets   (cod);
		
		retorno = strcmp(cod,"0");
		if (retorno == 0){
			return 0;
		}
		
		cod [strlen(cod)] = '\0';
		
		for (x=0; x<cont; x++){
			y = strcmp(cod, dados[x].codigo);
			if (y == 0){
				i = x; //recebe o indice do item achado
				z = 0;
			}
		}
		
		system ("cls");
	} while(z != 0);
	
	
	do{
		caixa  ("ALTERAR   ");
		printf ("\n    (Coloque 0 para retornar ao menu C.R.U.D.)");
		printf ("\n    (1U$=R$%.2f)", reais);
		printf ("\n\n    CODIGO: %s", dados[i].codigo);
		printf ("\n    NOME  : %s",   dados[i].nome);
		printf ("\n    PRECO : %.2f", dados[i].dolar);
		printf ("\n\n    1 - ALTERAR NOME DO PRODUTO");
		printf ("\n    2 - ALTERAR PRECO DO PRODUTO");
		printf ("\n\n    ESCOLHA OPCAO: ");
		scanf  ("%d",&opcao);
		fflush (stdin);
		system ("cls");
		if (opcao == 0){
			return 0;
		}
	}while (opcao!=1 && opcao!=2);
	
	
	if (opcao == 1){ //se deseja alterar o nome do produto:
		caixa  ("ALTERAR   ");
		printf ("\n\n    (1U$=R$%.2f)", reais);
		printf ("\n\n    CODIGO: %s",   dados[i].codigo);
		printf ("\n    NOME  : %s",     dados[i].nome);
		printf ("\n    PRECO : %.2f",   dados[i].dolar);
		printf ("\n\n    NOVO NOME: ");
		gets   (novonome);
		
		
		novonome[strlen(novonome)] = '\0';
		strcpy(dados[i].nome, novonome);
	}
	
	else{ //se deseja alterar o preço do produto:
		caixa  ("ALTERAR   ");
		printf ("\n\n    (1U$=R$%.2f)", reais);
		printf ("\n\n    CODIGO: %s",   dados[i].codigo);
		printf ("\n    NOME  : %s",     dados[i].nome);
		printf ("\n    PRECO : %.2f",   dados[i].dolar);
		printf ("\n\n    NOVO PRECO(somente numeros e ponto): ");
		scanf  ("%f", &novodolar);
		fflush (stdin);
		
		dados[i].dolar = novodolar;
		dados[i].real  = novodolar*reais;
	}
	
	dados[i].editado = 2;
	salvaTabela (); //salva a tabela
	return 0;
}


//===========================================================================================================
//== DELETAR ITEM EXISTENTE =================================================================================
int deletarItem (){
	
	char tmp[200], cod[200];
	int  i, opcao, retorno;
	
	do{ //repetir ate o codigo escrito estiver presente na tabela
		z = 1;
		caixa  ("DELETAR   ");
		printf ("\n    (Coloque 0 no CODIGO para retornar ao menu C.R.U.D.)");
		printf ("\n    (1U$=R$%.2f)", reais);
		printf ("\n\n    CODIGO EXISTENTE NA TABELA: ");
		gets   (cod);
		
		retorno = strcmp (cod, "0");
		if (retorno == 0)
			return 0;
		
		cod[strlen(cod)] = '\0';
		
		for (x=0; x<cont; x++){ //verifica se o codigo esta na tabela
			y = strcmp (cod, dados[x].codigo);
			if (y == 0){
				i = x; //se sim, recebe o indice de onde foi achado
				z = 0;
			}
		}
		system ("cls");
	} while(z!=0); 
	
	do{
		caixa  ("DELETAR   ");
		printf ("\n\n    (1U$=R$%.2f)", reais);
		printf ("\n\n    CODIGO: %s",   dados[i].codigo);
		printf ("\n    NOME  : %s",     dados[i].nome);
		printf ("\n    PRECO : %.2f",   dados[i].dolar);
		printf ("\n\n    DESEJA MESMO DELETAR? ");
		printf ("\n    1 - CONFIRMAR ");
		printf ("\n    2 - VOLTAR ");
		printf ("\n\n    OPCAO: ");
		scanf  ("%d", &opcao);
		fflush (stdin);
		system ("cls");
	}while (opcao!=1 && opcao!=2);
	
	if (opcao == 2)
		return 0;
	
	//numero de items diminui, e o indice recebe o ultimo item 
	//se desejar apagar o ultimo item, o vetor recebe ele mesmo, porem logo depois, por causa do cont diminuir, ele se apaga
	cont--;
	
	strcpy (codDel[del], dados[i].codigo2);
	
	strcpy (dados[i].codigo,  dados[cont].codigo);
	strcpy (dados[i].codigo2, dados[cont].codigo2);
	dados[i] . codigoint =   dados[cont].codigoint;
	
	strcpy (dados[i].nome, dados[cont].nome);
	
	dados[i].dolar = dados[cont].dolar;
	dados[i].real  = dados[cont].real;
	

	del++;
	salvaTabela (); //salva a tabela
	printf ("ITEM DELETADO, ");
	system ("pause");
	return 0;
}


//===========================================================================================================
//== SALVAR TABELA NO ARQUIVO ===============================================================================
void salvaTabela (){
	
	char tmp[200];
	int  contEdit=0;
	z = 0;
	classificacao (3);
	arq = fopen ("EDIT-Allan Ogawa.txt", "w"); //abre o arquivo de com o "w", que remove tudo que estava antes e coloca de novo
	
	if(del > 0){
		for(x=0; x<del; x++){
			fprintf (arq, " 3  %-7s\n", codDel[x]);
			contEdit++;
		}
	}
	
	for(x=0; x<cont; x++){
		if(dados[x].editado != 0){
			strcpy (tmp, dados[x].nome);
			
			for (z=strlen(tmp); z<=57; z++)
				tmp[z] = '.';
			tmp[57] = '\0';
			
			fprintf (arq, " %1d  %-7s  %-57s %8.2f\n", dados[x].editado, dados[x].codigo2, tmp, dados[x].dolar);
			contEdit++;
		}
	}
	
	fprintf (arq, "%d",contEdit);		
	fclose (arq); //fecha arquivo
}



//=====================================================================================================================
//==-----------------------------------------------------------------------------------------------------------------==
//== LEITURA DE ARQUIVO  ==============================================================================================
//==-----------------------------------------------------------------------------------------------------------------==
//=====================================================================================================================


//===========================================================================================================
//== LEITURA ================================================================================================
void leitura (){
	
	char precotmp[50],tmp[200];
	int  linha=0;
	
	arq = fopen("icompy.txt","r"); 
  	if (arq == NULL)
		entrada = false;
		
  	else{ 
  		entrada = true;
  		
		while ( !feof(arq) ){
	      	if (linha>=7){
	      		
	      		
	      		//-- LEITURA DO CODIGO ------------------------------------------------------------
	      		fseek (arq, 1, SEEK_CUR); //ele pula um espaço da linha
		    	fgets (dados[cont].codigo, 8, arq); //extrai o codigo da linha
	            dados[cont].codigo [strlen(dados[cont].codigo)]='\0';
	            
	            strcpy(dados[cont].codigo2, dados[cont].codigo); //vetor codigotmp é um vetor onde armazena o codigo com espaços para depois por de volta no arquivo
	            
				removeEspaco (dados[cont].codigo);
		    		
	            dados[cont].codigoint = atoi(dados[cont].codigo); //vetor de codigo em int para ser usada como comparação caso queira classificar por codigo
	            
	            
	            
	            //-- LEITURA DO NOME --------------------------------------------------------------
	            fseek (arq, 2, SEEK_CUR); //ele pula dois espaços da linha
		    	fgets (dados[cont].nome, 58, arq);//extrai o nome da linha
		    	
		    	while (dados[cont].nome[strlen(dados[cont].nome)-1] == '.' || dados[cont].nome[strlen(dados[cont].nome)-1] == ' ')//remove os espaços e pontos que estao no final da string
		    		dados[cont].nome[strlen(dados[cont].nome)-1] = '\0';
		
		
		
		    	//-- LEITURA DO PREÇO -------------------------------------------------------------
		    	fseek (arq, 1, SEEK_CUR); //ele pula um espaço da linha
		    	fgets (precotmp, 11, arq);//extrai o preço da linha
		    	precotmp[strlen(precotmp)]='\0';
		    	
				dados[cont].dolar = atof (precotmp); //vetor de dolar float recebe o vetor temporario do preço
				dados[cont].real  = dados[cont].dolar * reais; //vetor real recebe o dolar x cotação
				
				
				cont++;
				
				
				//-- MOSTRA NA TELA O CARREGAMENTO ------------------------------------------------
				if (cont == 1){ //se for a primeira vez q ocorre a leitura, ele informa ao usuario o carregamento da tabela
					printf ("    CARREGANDO TABELA ");
					_sleep (300); //delay
				}
				else if (cont%100 == 0) //a cada 100 linhas lidas, ele printa um "." 
					printf (".");
				
			}
			else{ //se a linha for menor que 7 (informações do cabeçalho), o vetor cabeçalho recebe essas linhas
				fgets (tmp, 200, arq);
				tmp[0] = '\0';
				linha++;
			}
	    }
	    system ("cls");
      	fclose (arq);
  	}
}


//===========================================================================================================
//== LEITURA DO ARQUIVO ADICIONAL ===========================================================================
void leituraedit (){
	char precotmp[10], codtmp[10], codtmp2[10], nomtmp[75], edittmp[5], qntedit[10];
	int  i, edit=0, contEdit=0, con=0;
	
	arq = fopen("EDIT-Allan Ogawa.txt","a+"); //caso nao tenha um arquivo, ele cria
	fclose(arq);
	
	
	arq = fopen("EDIT-Allan Ogawa.txt","r");
	fseek (arq, -1, SEEK_END);  //vai para o final do arquivo
	fgets (qntedit, 8, arq);    //pega o numero de ediçoes
	contEdit = atoi(qntedit);
	
	fseek (arq, 0, SEEK_SET);	//vai para o começo do arquivo
	
  	for(int add=1; add<=contEdit; add++){
  		
  		//-- TIPO DE EDIÇÃO --------------------------------------------------------------
  		fseek (arq, 1, SEEK_CUR); //ele pula um espaço da linha
		fgets (edittmp, 2, arq); //extrai o tipo da edição da linha
		edittmp[strlen(edittmp)]='\0';
		edit = atoi(edittmp);
		
		if(edit == 3){ //ITEM EXCLUIDO
			
			//-- CODIGO --------------------------------------------------------------
			fseek (arq, 2, SEEK_CUR); //ele pula um espaço da linha
			fgets (codtmp, 8, arq); //extrai o codigo da linha
			codtmp[strlen(codtmp)]='\0';
			removeEspaco (codtmp);
			
	  		for(x=0; x<cont; x++){ //pega o indice do item excluido
	  			y = strcmp(codtmp, dados[x].codigo);
	  			if (y==0){
	  				i=x;  
	  				break;
	  			}
			}
			
			//-- EXCLUI O ITEM -------------------------------------------------------
			cont--;
			strcpy (codDel[del],      dados[i].codigo2);
			strcpy (dados[i].codigo,  dados[cont].codigo);
			strcpy (dados[i].codigo2, dados[cont].codigo2);
			dados[i] . codigoint =   dados[cont].codigoint;
					
			strcpy (dados[i].nome, dados[cont].nome);
					
			dados[i].dolar = dados[cont].dolar;
			dados[i].real  = dados[cont].real;
			del++;
			fseek (arq, 2,SEEK_CUR);
		}
		
		else{
			
			//-- CODIGO --------------------------------------------------------------
			fseek (arq, 2, SEEK_CUR); //ele pula um espaço da linha
			fgets (codtmp, 8, arq); //extrai o codigo da linha
			codtmp[strlen(codtmp)]='\0';
			strcpy(codtmp2,codtmp);
			removeEspaco (codtmp);
			
			//-- NOME ----------------------------------------------------------------
			fseek (arq, 2, SEEK_CUR); //ele pula dois espaços da linha
			fgets (nomtmp, 58, arq);//extrai o nome da linha
			while (nomtmp[strlen(nomtmp)-1] == '.' || nomtmp[strlen(nomtmp)-1] == ' ')//remove os espaços e pontos que estao no final da string
			   	nomtmp[strlen(nomtmp)-1] = '\0';
			 
			//-- PREÇO ---------------------------------------------------------------	
			fseek (arq, 1, SEEK_CUR); //ele pula um espaço da linha
			fgets (precotmp, 100, arq);//extrai o preço da linha
			precotmp[strlen(precotmp)]='\0';
				
	  		
			if(edit == 2){ //ITEM EDITADO
			
				for(x=0; x<cont; x++){ //pega o indice do item
		  			y = strcmp(codtmp, dados[x].codigo);
		  			if (y==0){
		  				i=x;
		  				break;
		  			}
				}
			
	  			strcpy(dados[i].nome,nomtmp);
				dados[i].dolar = atof (precotmp); //vetor de dolar float recebe o vetor temporario do preço
				dados[i].real  = dados[i].dolar * reais; //vetor real recebe o dolar x cotação
				dados[i].editado = 2;
			}
			
			if(edit == 1){ //ITEM CRIADO
			
				strcpy(dados[cont].codigo,codtmp);
				strcpy(dados[cont].codigo2,codtmp2);
				dados[cont].codigoint = atoi(dados[cont].codigo);
				
				strcpy(dados[cont].nome,nomtmp);
				
				dados[cont].dolar = atof (precotmp); //vetor de dolar float recebe o vetor temporario do preço
				dados[cont].real  = dados[cont].dolar * reais; //vetor real recebe o dolar x cotação
				dados[cont].editado = 1;
				cont++;
			}
			
		}
	}
	
	fclose (arq);
	classificacao(3); //classifica por nome
}


//===========================================================================================================
//== REMOVE OS ESPAÇOS DA FRENTE E ATRAS DE UMA STRING ======================================================
void removeEspaco (char* string){
			
	while(string[0] == ' '){ //remove os espaços que estao no começo da string
		for(x=0; x<strlen(string); x++)
		    string[x] = string[x+1];
	}
		    
	while(string[strlen(string)-1] == ' ') //remove os espaços que estao no final da string
		string[strlen(string)-1] = '\0';
}



//=====================================================================================================================
//==-----------------------------------------------------------------------------------------------------------------==
//== PROCURA E MOSTRA DE TABELA  ======================================================================================
//==-----------------------------------------------------------------------------------------------------------------==
//=====================================================================================================================


//===========================================================================================================
//== PROCURA ================================================================================================
int procura (){
	
	int  retorno, tam, tmp, tmpup, tmplo, achado=0, s1=0, s2=0, a=0;
	bool achadobool=false;
	char stmp[200], digitadoup[200], digitadolo[200], digitado[200];
	
	caixa  ("PROCURA    ");
	printf ("\n    (Coloque 0 para retornar ao menu principal)");
	printf ("\n\n    Codigo ou Palavra-Chave desejado: ");
	gets   (digitado);
	
	retorno = strcmp (digitado, "0");
	
	if (retorno == 0)
		return 0;

	tam = strlen(digitado); //para evitar ficar fazendo strlen toda hora, variavel tam recebe o mesmo	    	
	system ("cls");
	
	//-- VERIFICA A PALAVRA-CHAVE NO VETOR DO CODIGO ----------------------------------------------
	if (tam>=4 && tam<=7){
	 	for (x=0; x<cont; x++){
	 		tmp = strcmp(digitado, dados[x].codigo); //comparação de string
	 		
			if (tmp == 0){//se achado:
				if (achado == 0){ //se for a primeira vez, ele printa:
					printf ("  CODIGO | PRECO DOLAR | PRECO REAL | NOME DO PRODUTO \n");
					printf ("         |             |            |\n");
				}
				
				achadobool = true;
				achado++; //um contador de itens achados
				printf (" %-7s |   %8.2f  |  %8.2f  | %s\n", dados[x].codigo,dados[x].dolar,dados[x].real,dados[x].nome);
			}	
		}
	}
	
	//-- VERIFICA A PALAVRA-CHAVE NO VETOR DO NOME ------------------------------------------------
	
	//o usuario pode digitar tanto maisuculo quanto minusculo
	for(x=0; x<tam; x++)
		digitadoup[x] = toupper(digitado[x]); //maiusculo
	
	for(x=0; x<tam; x++)
		digitadolo[x] = tolower(digitado[x]); //minusculo
		
	digitadoup[tam] = '\0';
	digitadolo[tam] = '\0';
	
	
	for(x=0; x<cont; x++){ //laço que passa pelo indice 
		for(y=0; y<strlen(dados[x].nome); y++){ //laço que passa pela string
			
			//uma string temporaria (stmp) vai receber uma parte da string do vetor do tamanho da palavra chave
			//e ela vai passando ate completar a string toda
			//ex-> palavra-chave: dell    string: computador dell
			//stmp=comp, depois, stmp=ompu, mput, puta, utad... ate chegar em dell 
			for(z=0; z<tam; z++) 
				stmp[z] = dados[x].nome[z+y];	
			stmp[tam]   = '\0';
			
			
			//comparação de strings
			tmp   = strcmp (digitado,   stmp);
			tmpup = strcmp (digitadoup, stmp);
			tmplo = strcmp (digitadolo, stmp);
			
			
			if ( (tmp==0 || tmpup==0 || tmplo==0) && (digitado[0]!='\0') ) { //se for achado tanto maiusculo quanto minusculo E se nao for ENTER
				//usando a tabela ASCII, se a palavra-chave tiver colada com uma letra de A-Z a-z, retorna 0
				s1 = stringColada(65,90,x,y,tam);
				s2 = stringColada(97,122,x,y,tam);
				
				if (s1==1 && s2==1){ //se a palavra-chave nao tiver colada com uma letra do alfabeto:
					
					if (achado == 0){ //se for a primeira vez, ele printa:
						printf ("  CODIGO | PRECO DOLAR | PRECO REAL | NOME DO PRODUTO \n");
						printf ("         |             |            |\n");
					}
					
					achadobool=true;
					achado++; //um contador de itens achados
					printf (" %-7s |   %8.2f  |  %8.2f  | %s\n",dados[x].codigo, dados[x].dolar, dados[x].real, dados[x].nome);
				
					
					if (achado%25 == 0){
						a++;
						printf ("         |             |            |\n");
						printf ("  CODIGO | PRECO DOLAR | PRECO REAL | NOME DO PRODUTO \n");
						printf ("%100c1U$=R$%.2f)\n",'(',reais); //mostra a cotação atual
						printf ("%100cPAGINA %d)\n",'(',a); //mostra	a pagina atual e total
						
						system ("pause");
						system ("cls");
						
						printf ("  CODIGO | PRECO DOLAR | PRECO REAL | NOME DO PRODUTO \n");
						printf ("         |             |            |\n");
					}	
					break; //break para, caso o nome tiver varias palavras-chaves na mesma string, impede de printar o mesmo nome varias vezes
				}
			}
		}
	}
	
	if (achadobool == false) //se ele nao for achado
		printf ("\n    NENHUM CODIGO OU NOME BATE COM O INFORMADO, ");
	
	else{	
		if (achado>=25){ //se tiver achado mais de 25 itens, ele printa isso no final dos itens para melhor visualizacao
			printf ("         |             |            |\n");
			printf ("  CODIGO | PRECO DOLAR | PRECO REAL | NOME DO PRODUTO \n");
		}
			
		printf ("%100c1U$=R$%.2f)\n",   '(' , reais); //mostra a cotação atual
		printf ("%100cPAGINA %d/%d)\n", '(' , a+1, (achado/25)+1);
	}
	
	system ("pause");
	return 0;
}


//===========================================================================================================
//== FUNÇAO QUE VERIFICA SE A PALAVRAS DE A-Z / a-z COLADA NA PALAVRA-CHAVE =================================
int stringColada (int n1, int n2, int x, int y, int tam){
	
	for (int a=n1; a<=n2; a++){ 
		//se a letra a frente da palavra-chave for letra de a-z e se a letra atras da palavra-chave for letra de a-z
		//retorna 0
		//OU se a letra atras da palavra-chave for letra de a-z
		if ( (dados[x].nome[y+tam]==a && dados[x].nome[y-1]==a) || dados[x].nome[y-1]==a)
			return 0;
	}
	return 1;//caso contrario, retorna 1
}
	
			
//===========================================================================================================
//== PROCEDIMENTO QUE MOSTRA A TABELA =======================================================================
int tabela (){
	
	int a=0;
	
	printf (" INDICE |  CODIGO | PRECO DOLAR | PRECO REAL | NOME DO PRODUTO \n");
	printf ("        |         |             |            |\n");
	
	for (x=0; x<cont; x++){
		printf ("  %-4d  | %-7s |   %8.2f  |  %8.2f  | %s\n",x,dados[x].codigo, dados[x].dolar, dados[x].real, dados[x].nome);
		
		if (x%100==0 && x>0){ //a cada 100 linhas, ele quebra a tabela
			a++;
			
			printf ("        |         |             |            |\n");
			printf( " INDICE |  CODIGO | PRECO DOLAR | PRECO REAL | NOME DO PRODUTO \n");
			
			printf ("%100c1U$=R$%.2f)\n",   '(', reais); //mostra a cotação atual
			printf ("%100cPAGINA %d/%d)\n", '(', a, (cont/100)+1); //mostra	a pagina atual e total	
			
			system ("pause");
			system ("cls");
			
			printf (" INDICE |  CODIGO | PRECO DOLAR | PRECO REAL | NOME DO PRODUTO \n"); 
			printf ("        |         |             |            |\n");
		}
	}
	
	printf ("        |         |             |            |\n");
	printf (" INDICE |  CODIGO | PRECO DOLAR | PRECO REAL | NOME DO PRODUTO \n");
	
	printf ("%100c1U$=R$%.2f)\n",   '(', reais); //mostra a cotação atual
	printf ("%100cPAGINA %d/%d)\n", '(', a+1, (cont/100)+1);//mostra a pagina atual e total	
	system ("pause");
	return 0;
}



//=====================================================================================================================
//==-----------------------------------------------------------------------------------------------------------------==
//== P R E Ç O  =======================================================================================================
//==-----------------------------------------------------------------------------------------------------------------==
//=====================================================================================================================


//===========================================================================================================
//== ALTERAÇAO DE PREÇO =====================================================================================
int alteracaoPreco (){ //ele nao altera o preço na tabela, apenas enquanto o programa estiver aberto
	
	float precotmp, tmp;
	int   opcao=0;
	
	do{
		caixa  ("PRECO     ");
		printf ("\n    (Coloque 0 para retornar ao menu principal)");
		printf ("\n    (1U$=R$%.2f)", reais);
		printf ("\n\n    Deseja aumentar ou diminuir preco? ");
		printf ("\n    1 - Aumentar ");
		printf ("\n    2 - Diminuir ");
		
		printf ("\n\n    Opcao: ");
		scanf  ("%i", &opcao);
		fflush (stdin);
		
		if (opcao == 0)
			return 0;
		
		system("cls");
	} while (opcao!=1 && opcao!=2);
	
	
	caixa  ("PRECO     ");
	printf ("\n    (Coloque 0 para retornar)");
	printf ("\n    (1U$=R$%.2f)", reais);
	printf ("\n\n    Porcentagem de valor a ser alterado (APENAS NUMERO E PONTO)? ");
	scanf  ("%f", &precotmp);
	fflush (stdin);
	
	if (precotmp == 0)
		return 0;
	
	precotmp = precotmp/100; //%
	
	if (opcao == 1){//se quer aumentar o preço:
		for (x=0; x<cont; x++) {
			tmp            = dados[x].dolar * precotmp;
			dados[x].dolar = dados[x].dolar + tmp;
			
			tmp            = dados[x].real * precotmp;
			dados[x].real  = dados[x].real + tmp;
			
		}
	}
	
	else //se quer diminuir o preço:
		for (x=0; x<cont; x++){
			tmp            = dados[x].dolar * precotmp;
			dados[x].dolar = dados[x].dolar - tmp;
			
			tmp            = dados[x].real * precotmp;
			dados[x].real  = dados[x].real - tmp;
			
		}
	
	printf ("\n    PRECO ALTERADO COM SUCESSO, ");
	system ("pause");	
	return 0;
}


//===========================================================================================================
//== PROCURA DE PREÇO =======================================================================================
int procuraPreco (){
	
	float min, max;
	int   a=0, achado=0;
	
	caixa  ("PROCURA EM DOLAR");
	printf ("\n\n    (1U$=R$%.2f)", reais);
	printf ("\n    DIGITAR APENAS NUMEROS E PONTO");
	printf ("\n\n    Preco Base   (minimo): ");
	scanf  ("%f", &min);
	fflush (stdin);
	
	do{ //laço de repetição para impedir que o numero de preço limite seja menor que o preço mase
		system ("cls");
		caixa  ("PROCURA EM DOLAR");
		printf ("\n    (Coloque 0 para retornar ao menu principal)");
		printf ("\n    (1U$=R$%.2f)", reais);
		printf ("\n    DIGITAR APENAS NUMEROS E PONTO");
		printf ("\n\n    Preco Base   (minimo): %.2f", min);
		printf ("\n    Preco Limite (maximo): ");
		scanf  ("%f", &max);
		fflush (stdin);
		
		if (max == 0)
			return 0;
		
	}
	while (max < min);
	
	system ("cls");
	printf ("  CODIGO | PRECO DOLAR | PRECO REAL | NOME DO PRODUTO \n");
	printf ("         |             |            |\n");
	
	
	for (x=0; x<cont; x++){
		if (dados[x].dolar >= min && dados[x].dolar <= max){
			printf (" %7s |  %8.2f   | %8.2f   | %s\n", dados[x].codigo, dados[x].dolar, dados[x].real, dados[x].nome);
			achado++;
			if (achado % 50 == 0){
				a++;
				printf ("         |             |            |\n");
				printf ("  CODIGO | PRECO DOLAR | PRECO REAL | NOME DO PRODUTO \n");
				printf ("%100c1U$=R$%.2f)\n", '(', reais); //mostra a cotação atual
				printf ("%100cPAGINA %d)\n",  '(', a); //mostra	a pagina atual
						
				system ("pause");
				system ("cls");
				
				printf ("  CODIGO | PRECO DOLAR | PRECO REAL | NOME DO PRODUTO \n");
				printf ("         |             |            |\n");
			}	
		}
	}
	
	if(achado>=50){ //se tiver achado mais de 25 itens, ele printa isso no final dos itens para melhor visualizacao
		printf ("         |             |            |\n");
		printf ("  CODIGO | PRECO DOLAR | PRECO REAL | NOME DO PRODUTO \n");
	}
			
	printf ("%100c1U$=R$%.2f)\n",   '(', reais); //mostra a cotação atual
	printf ("%100cPAGINA %d/%d)\n", '(', a+1, (achado/50)+1);//mostra a pagina atual
	system ("pause");
	return 0;
}

		
		
//=====================================================================================================================
//==-----------------------------------------------------------------------------------------------------------------==
//== CLASSIFICAÇÃO  ===================================================================================================
//==-----------------------------------------------------------------------------------------------------------------==
//=====================================================================================================================


//===========================================================================================================
//== PROCEDIMENTO DE CLASSIFICACAO ==========================================================================
void classificacao (int tipo){
	
	for(x=0; x<cont-1; x++)
		for(y=x+1; y<cont; y++){
			
			//-- tipo 1 = preço ---------------------------
			if (tipo == 1) {
				tipodeclass=1;
				if (dados[x].dolar > dados[y].dolar)
					troca(x, y);	
			}
					
			//-- tipo 2 = codigo --------------------------
			if (tipo == 2){
				tipodeclass=2;
				if (dados[x].codigoint > dados[y].codigoint)
					troca(x, y);
			}	
			
			//-- tipo 3 = nome ----------------------------	
			if (tipo == 3){ 
				tipodeclass=0;
				z = strcmp(dados[x].nome, dados[y].nome);
				if (z==1)
					troca(x, y); 
			}
			
		}
}


//===========================================================================================================
//== PROCEDIMENTO ONDE OCORRE A TROCA DOS VALORES DOS VETORES ===============================================
void troca (int a, int b){
	
	int   tmpi;
	float tmpf;
	char  tmpc[200];
	
	//-- NOME ---------------------------------------------
	strcpy (tmpc,          dados[a].nome);
	strcpy (dados[a].nome, dados[b].nome);
	strcpy (dados[b].nome, tmpc);
	
	
	//-- CODIGO -------------------------------------------
	strcpy (tmpc,            dados[a].codigo);
	strcpy (dados[a].codigo, dados[b].codigo);
	strcpy (dados[b].codigo, tmpc);
	
	strcpy (tmpc,             dados[a].codigo2);
	strcpy (dados[a].codigo2, dados[b].codigo2);
	strcpy (dados[b].codigo2, tmpc);
	
	//-- CODIGO INT ---------------------------------------
	tmpi               = dados[a].codigoint;
	dados[a].codigoint = dados[b].codigoint;
	dados[b].codigoint = tmpi;
	
	
	//-- EDITADO ---------------------------------------
	tmpi             = dados[a].editado;
	dados[a].editado = dados[b].editado;
	dados[b].editado = tmpi;
	
	
	//-- DOLAR --------------------------------------------
	tmpf           = dados[a].dolar;
	dados[a].dolar = dados[b].dolar;
	dados[b].dolar = tmpf;	
	
	
	//-- REAL ---------------------------------------------
	tmpf          = dados[a].real;
	dados[a].real = dados[b].real;
	dados[b].real = tmpf;	
}

