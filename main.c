#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <locale.h>
#include <conio.h>
/*
 * Missões:
 * Fazer erro léxico @, e preencher o tipoV do registro.
 */
/*
 * vetor de tokens
 * Variaveis
 */
char proxCaractere = '\0'; //guarda cada caractere
char lex_aux[] = "\0"; // os caracteres serão concatenados aqui.
int TamanhoL = 0; // quantidade dos leximas
int conter = 1; //contagem de pontos seguidos de numeros
const char *ptok[35]; // vetor que guarda todas as palavras reservdas
int contbe = 1; //contagem da gramatica beginend

typedef struct// registro da tabela lexema
{
    int declarado; // erro declaracao
    char lexema[30]; // todos os tokens que fazer parte ou não do lexema
    int tipoV; // se o identificador escolhido é : integer, real ou string. 1 2 3
    int linha; // posicao da linha onde está o token
    int coluna; // posicao da coluna onde esta o token
    int id; // id para saber se é um identificador ou palavra chave de 1 ate 36
    char bloco[300]; // auxilia na coleta de dados para a 2 parte: 3 enderecos. pega o lexema
    int blocoi, blocoli; // auxilia na coleta de dados para a 2 parte: 3 enderecos. pega o identificador (1-36), e pega a linha.
} tabela_lex;

tabela_lex tabelaLexica[10900]; //criação do vetor de Struc

//fim

// construtor

void construtor() {// nao precisa
    for (int i = 1; i <= 200; i++) {
        tabelaLexica[i].declarado = 0;
        tabelaLexica[i].tipoV = 0;
        tabelaLexica[i].linha = 0;
        tabelaLexica[i].coluna = 0;
        tabelaLexica[i].id = 0;
        tabelaLexica[i].blocoi = 0;
        strcpy(tabelaLexica[i].lexema, "\0");
        strcpy(tabelaLexica[i].bloco, "\0");
    }
}

//fim C

void preenchertokens() {// tabela preenchida com tokens
    ptok[1] = "begin"; // palavra reservada
    ptok[2] = "end";
    ptok[3] = "if";
    ptok[4] = "then";
    ptok[5] = "else";
    ptok[6] = "while";
    ptok[7] = "do";
    ptok[8] = "until";
    ptok[9] = "repeat";
    ptok[10] = "integer"; // tipoV = 1
    ptok[11] = "real"; // tipoV = 2
    ptok[12] = "all";
    ptok[13] = "and";
    ptok[14] = "or";
    ptok[15] = "string"; // tipoV = 3
    ptok[16] = "program"; // palavra reservada

    ptok[17] = "<";
    ptok[18] = ">";
    ptok[19] = "<=";
    ptok[20] = ">=";
    ptok[21] = "=";
    ptok[22] = "<>";

    ptok[23] = "+";
    ptok[24] = "-";
    ptok[25] = "*";
    ptok[26] = "/";

    ptok[27] = ".";
    ptok[28] = ",";
    ptok[29] = ";";
    ptok[30] = "(";
    ptok[31] = ")";
    ptok[32] = ":=";
    ptok[33] = ":";
    ptok[34] = "end.";
    ptok[35] = "var";
}

void GerarTabela(char token[10], int p) { // responsavel pela escrita da tabela 
    preenchertokens();

    //printf(" -%d \n", p);
    // printf("Lexema: %c com linha %d, e coluna: %d\n", token, linha, coluna);
    if (strcmp(token, ptok[1]) == 0) {
        // printf("Palavra reservada: %s com id: %i\n", token, 1);
        tabelaLexica[p].id = 1;
    } else if (strcmp(token, ptok[2]) == 0) {
        // printf("Palavra reservada: %s com id: %i\n", token, 2);
        tabelaLexica[p].id = 2;
    } else if (strcmp(token, ptok[3]) == 0) {
        // printf("Palavra reservada: %s com id:  %i\n", token, 3);
        tabelaLexica[p].id = 3;
    } else if (strcmp(token, ptok[4]) == 0) {
        // printf("Palavra reservada: %s com id:  %i\n", token, 4);
        tabelaLexica[p].id = 4;
    } else if (strcmp(token, ptok[5]) == 0) {
        //  printf("Palavra reservada: %s com id:  %i\n", token, 5);
        tabelaLexica[p].id = 5;
    } else if (strcmp(token, ptok[6]) == 0) {
        // printf("Palavra reservada: %s com id:  %i\n", token, 6);
        tabelaLexica[p].id = 6;
    } else if (strcmp(token, ptok[7]) == 0) {
        //    printf("Palavra reservada: %s com id:  %i\n", token, 7);
        tabelaLexica[p].id = 7;
    } else if (strcmp(token, ptok[8]) == 0) {
        //  printf("Palavra reservada: %s com id:  %i\n", token, 8);
        tabelaLexica[p].id = 8;
    } else if (strcmp(token, ptok[9]) == 0) {
        //  printf("Palavra reservada: %s  com id: %i\n", token, 9);
        tabelaLexica[p].id = 9;
    } else if (strcmp(token, ptok[10]) == 0) {
        // printf("Palavra reservada: %s  com id:\n", token);
        tabelaLexica[p].id = 10;
    } else if (strcmp(token, ptok[11]) == 0) {
        // printf("Palavra reservada: %s com id: \n", token);
        tabelaLexica[p].id = 11;
    } else if (strcmp(token, ptok[12]) == 0) {
        //  printf("Palavra reservada: %s  com id: %i\n", token, 12);
        tabelaLexica[p].id = 12;
    } else if (strcmp(token, ptok[13]) == 0) {
        //  printf("Palavra reservada e booleana: %s %i\n", token, 13);
        tabelaLexica[p].id = 13;
    } else if (strcmp(token, ptok[14]) == 0) {
        //  printf("Palavra reservada e booleana: %s %i\n", token, 14);
        tabelaLexica[p].id = 14;
    } else if (strcmp(token, ptok[15]) == 0) {
        // printf("Palavra reservada: %s com id:  \n", token);
        tabelaLexica[p].id = 15;
    } else if (strcmp(token, ptok[16]) == 0) {
        //    printf("Palavra reservada: %s com id:  %i\n", token, 16);
        tabelaLexica[p].id = 16;
    } else if (strcmp(token, ptok[17]) == 0) {
        //    printf("Operador Relacional: %s %i\n", token, 17);
        tabelaLexica[p].id = 17;
    } else if (strcmp(token, ptok[18]) == 0) {
        //  printf("Operador Relacional: %s %i\n", token, 18);
        tabelaLexica[p].id = 18;
    } else if (strcmp(token, ptok[19]) == 0) {
        //   printf("Operador Relacional: %s %i\n", token, 19);
        tabelaLexica[p].id = 19;
    } else if (strcmp(token, ptok[20]) == 0) {
        //   printf("Operador Relacional: %s %i\n", token, 20);
        tabelaLexica[p].id = 20;
    } else if (strcmp(token, ptok[21]) == 0) {
        //   printf("Operador Relacional: %s %i\n", token, 21);
        tabelaLexica[p].id = 21;
    } else if (strcmp(token, ptok[22]) == 0) {
        //   printf("Operador Relacional: %s %i\n", token, 22);
        tabelaLexica[p].id = 22;
    } else if (strcmp(token, ptok[23]) == 0) {
        //  printf("Operador Aritmedico: %s %i\n", token, 23);
        tabelaLexica[p].id = 23;
    } else if (strcmp(token, ptok[24]) == 0) {
        //  printf("Operador Aritmedico: %s %i\n", token, 24);
        tabelaLexica[p].id = 24;
    } else if (strcmp(token, ptok[25]) == 0) {
        //   printf("Operador Aritmedico: %s %i\n", token, 25);
        tabelaLexica[p].id = 25;
    } else if (strcmp(token, ptok[26]) == 0) {
        //  printf("Operador Aritmedico: %s %i\n", token, 26);
        tabelaLexica[p].id = 26;
    } else if (strcmp(token, ptok[27]) == 0) {
        //  printf("Operador Especiais: %s %i\n", token, 27);
        tabelaLexica[p].id = 27;
    } else if (strcmp(token, ptok[28]) == 0) {
        //  printf("Operador Especiais: %s %i\n", token, 28);
        tabelaLexica[p].id = 28;
    } else if (strcmp(token, ptok[29]) == 0) {
        //   printf("Operador Especiais: %s %i\n", token, 29);
        tabelaLexica[p].id = 29;
    } else if (strcmp(token, ptok[30]) == 0) {
        //  printf("Operador Especiais: %s %i\n", token, 30);
        tabelaLexica[p].id = 30;
    } else if (strcmp(token, ptok[31]) == 0) {
        // printf("Operador Especiais: %s %i\n", token, 31);
        tabelaLexica[p].id = 31;
    } else if (strcmp(token, ptok[32]) == 0) {
        //  printf("Operador Especiais: %s %i\n", token, 32);
        tabelaLexica[p].id = 32;
    } else if (strcmp(token, ptok[33]) == 0) {
        // printf("Operador Finalizador: %s %i\n", token, 33);
        tabelaLexica[p].id = 33;
    } else if (strcmp(token, ptok[34]) == 0) {
        // printf("Palavra reservada: %s %i\n", token, 34);
        tabelaLexica[p].id = 34;
    } else if (strcmp(token, ptok[35]) == 0) {
        // printf("Palavra reservada: %s %i\n", token, 35);
        tabelaLexica[p].id = 35;
    } else {
        //  printf("identificador: %s %i\n", token, 35);
        tabelaLexica[p].id = 36;
    }
}// fazer compraçoes 

int ExibirErro(char lexema[50], int linha, int coluna, int x) {// irá exibis os erros com as informações
    //Erro 01: Identificador ou símbolo inválido;

    switch (x) {
        case 1:
            printf("\n  ERRO 1: Identificador ou simbolo invalido - \n lexema: %s linha: %d e coluna: %d \n\n", lexema, linha, coluna);
            break;
        case 11:
            printf("\n  ERRO 1.1: não deve usar um numero antes de letra -\n lexema: %s linha: %d e coluna: %d \n\n", lexema, linha, coluna);
            break;
        case 12:
            printf("\n  ERRO 1.2: Uso do ponto ou virgula invalido (.)ou(,) ou(=) -\n lexema: %s linha: %d e coluna: %d \n\n", lexema, linha, coluna);
            printf("  Esperado a retirada");
            break;
        case 13:
            printf("\n  ERRO 1.3: Esperava um ;(ponto e virgula) ou , virgula. ou corrigir atribuiçoes anteriores dessa linha -\n lexema: %s linha: %d e coluna: %d \n\n", lexema, linha, coluna);
            break;
        case 14:
            printf("\n  ERRO 1.4: não esperava identificador junto com a quebra de linha -\n lexema: %s linha: %d e coluna: %d \n\n", lexema, linha, coluna);
            break;
        case 15:
            printf("\n  ERRO 1.5: declaracao de comentario invalido, tire um } ou verifique se está faltando um-\n lexema: %s linha: %d \n\n", ";", linha + 1);
            break;
        case 16:
            printf("\n  ERRO 1.6: declaracao errada, só é permitido o program -\n lexema: %s linha: %d e coluna: %d \n\n", lexema, linha, coluna);
            break;
        case 17:
            printf("\n  ERRO 1.7: declaracao errada, só é permitido identificador -\n lexema: %s linha: %d e coluna: %d \n\n", lexema, linha, coluna);
            break;
        case 18:
            printf("\n  ERRO 1.8: declaracão errada, só é permitido ; -\n linha: %d e coluna: %d \n\n", linha, coluna);
            break;
        case 19:
            printf("\n  ERRO 1.9: declaracao errada, só é permitido end. -\n lexema: %s linha: %d e coluna: %d \n\n ", lexema, linha, coluna);
            printf("\n ou { declarado errado, feche com } depois desse token: %s-\n de linha: %d e coluna: %d\n \n ", lexema, linha, coluna);
            break;
        case 20:
            printf("\n  ERRO 2.0: %s inesperado, apague o lexema da  entre a linha: %d e coluna: %d \n\n", lexema, linha, coluna);
            break;
        case 21:
            printf("\n  ERRO 2.1: %s sem ; (ponto e virgula)-  adicione ; no lexema da linha: %d e coluna: %d \n\n", lexema, linha, coluna);
            break;
        case 22:
            printf("\n  ERRO 2.2: Espera um %s para fechar o loop do programa. \n\n", lexema);
            break;
        case 23:
            printf("\n  ERRO 2.3: parenteses colocado de forma errada ou problema na condição, esperava um ;  ou recontagem de parenteses,- \n lexema: %s linha: %d e coluna: %d \n\n", lexema, linha, coluna);
            break;
        case 24:
            printf("\n  ERRO 2.3.1: inesperado na condição IF, esperando then ou operação relacional no lexema: %s, linha: %d  e coluna: %d\n\n", lexema, linha, coluna);
            break;
        case 25:
            printf("\n  ERRO 2.3.2: inesperado na condição while, esperando then ou operação relacional no lexema: %s, linha: %d  e coluna: %d\n\n", lexema, linha, coluna);
            break;
        case 26:
            printf("\n  ERRO 2.3.3: inesperado na condição repeat, esperando then ou operação relacional no lexema: %s, linha: %d  e coluna: %d\n\n", lexema, linha, coluna);
            break;
        case 27:
            printf("\n  ERRO 2.7: %s inesperado, esperado um if, while ou until ou procedimento linha: %d  e coluna: %d\n\n", lexema, linha, coluna);
            break;
        case 3:
            printf("\n  ERRO 03: Tipos incompatíveis - \n lexema: %s linha: %d e coluna: %d \n", lexema, linha, coluna);
            printf("\n  ERRO 03: Esperado valor ou identificador do seu tipo compativel dessa função ou condição. Caso seja all esperado seu tipo aceitar string ou começar com abre parenteses");
            break;
        case 4:
            printf("\n  ERRO 04: Identificador não declarado -\n lexema: %s linha: %d e coluna: %d \n\n", lexema, linha, coluna);
            break;
        case 6:
            printf("\n  ERRO 06: Variável declarada em duplicidade -\n lexema: %s linha: %d e coluna: %d \n\n", lexema, linha, coluna);
            break;
    }
    // printf("Erro 01: Identificador ou símbolo inválido - lexema: %s linha: %d e coluna: %d", lexema, linha, coluna);
    //// printf("Erro 02: não deve usar numero ou ponto antes das letras ou esperava numero depois do ponto no valor real - lexema: %s linha: %d e coluna: %d", lexema, linha, coluna);
    //ERRO 03: Tipos incompatíveis
    system("pause");
    exit(0);
}

void declararVariavel(int tamanho) {// passo pelas variaveis e as declaro
    //11 real ,=28
    //15 string    

    for (int i = 1; i <= tamanho; i++) {
        if (strcmp(tabelaLexica[i].lexema, "integer") == 0) {
            while (strcmp(tabelaLexica[i].lexema, ";") && strcmp(tabelaLexica[i].lexema, "real") && strcmp(tabelaLexica[i].lexema, "string")) {
                if (tabelaLexica[i].id > 35) {
                    tabelaLexica[i].tipoV = 1;
                    //  printf("oi - %s\n", tabelaLexica[i].lexema);
                    tabelaLexica[i].declarado = 1;

                }
                i++;
            }
        }
        if (strcmp(tabelaLexica[i].lexema, "real") == 0) {
            while (strcmp(tabelaLexica[i].lexema, ";") && strcmp(tabelaLexica[i].lexema, "integer") && strcmp(tabelaLexica[i].lexema, "string")) {
                if (tabelaLexica[i].id > 35) {
                    tabelaLexica[i].tipoV = 2;
                    // printf("oi1111 - %s\n", tabelaLexica[i].lexema);
                    tabelaLexica[i].declarado = 1;
                }
                i++;
            }
        }
        if (strcmp(tabelaLexica[i].lexema, "string") == 0) {
            while (strcmp(tabelaLexica[i].lexema, ";") && strcmp(tabelaLexica[i].lexema, "real") && strcmp(tabelaLexica[i].lexema, "integer")) {
                if (tabelaLexica[i].id > 35) {
                    tabelaLexica[i].tipoV = 3;
                    tabelaLexica[i].declarado = 1;
                }
                i++;
            }
        }
    }
}

void gramaticaAtribuir(int tamanho) {///follow
    for (int i = 1; i <= tamanho; i++) {

        if (strcmp(tabelaLexica[i].lexema, "=") == 0) {// erro de atrbuição aq sem o :
            if (tabelaLexica[i + 2].id == 29 || (tabelaLexica[i + 2].id >= 23 && tabelaLexica[i + 2].id <= 26)) {
                ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 12);
            }
        }
        if (strcmp(tabelaLexica[i].lexema, ":=") == 0) {

            if (tabelaLexica[i - 1].id != 36) {

                ExibirErro(tabelaLexica[i - 1].lexema, tabelaLexica[i - 1].linha, tabelaLexica[i - 1].coluna, 17);
            }
            if (tabelaLexica[i - 1].tipoV == 3) {// atribuição tipo string para verificação
                //printf("lexema; %s\n", tabelaLexica[i].lexema);// chama erro   
                do {
                    i++;
                    if (tabelaLexica[i].id != 36) {

                        ExibirErro(tabelaLexica[i - 1].lexema, tabelaLexica[i - 1].linha, tabelaLexica[i - 1].coluna, 17);
                    }
                    //  printf("\noi111 - %s\n", tabelaLexica[i].lexema);
                    i++;
                    if (tabelaLexica[i].id != 29 && tabelaLexica[i].id != 28) {

                        ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 13);
                        //printf("\noi222 - %s\n", tabelaLexica[i].lexema);
                    }
                    //printf("\noi222 - %s\n", tabelaLexica[i].lexema);

                } while (strcmp(tabelaLexica[i].lexema, ";"));
            } else {
                do {
                    i++;
                    if (tabelaLexica[i].id != 36 && tabelaLexica[i].id != 30 && tabelaLexica[i].id != 31) {// verificado

                        //   ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 17);
                    }//verifica
                    // printf("\noi111 - %s\n", tabelaLexica[i].lexema);
                    i++;
                    if (tabelaLexica[i].id != 29 && tabelaLexica[i].id != 23 && tabelaLexica[i].id != 30 && tabelaLexica[i].id != 31 &&
                            tabelaLexica[i].id != 24 && tabelaLexica[i].id != 25 &&
                            tabelaLexica[i].id != 26 && tabelaLexica[i].id != 36) {//verifica
                        //printf("ERRROOOO\n\n"); // verifica
                        ExibirErro(tabelaLexica[i - 5].lexema, tabelaLexica[i - 5].linha, tabelaLexica[i - 5].coluna, 13);
                        //   printf("\noi222 - %s\n", tabelaLexica[i].lexema);
                    }
                    //printf("\noi222 - %s\n", tabelaLexica[i].lexema);
                    if ((tabelaLexica[i].id == 29 && tabelaLexica[i + 1].id > 35 && tabelaLexica[i + 2].id == 32) ||
                            (tabelaLexica[i].id == 29 && tabelaLexica[i + 1].id < 36)) {
                    } else {
                        // ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 17); 
                        // printf("oi");
                    }
                } while (strcmp(tabelaLexica[i].lexema, ";"));
                if (tabelaLexica[i + 1].id >= 23 && tabelaLexica[i + 1].id <= 26) {
                    ExibirErro(tabelaLexica[i + 1].lexema, tabelaLexica[i + 1].linha, tabelaLexica[i + 1].coluna, 13);
                }// if do erro de operador depois do ponto e virgula
            }
        }
    }//for
}

void gramaticaVariavel(int tamanho) {// follow da erro caso algum token invalido depois da declaração
    int cont = 0;
    for (int i = 1; i <= tamanho; i++) {
        if (strcmp(tabelaLexica[i].lexema, "integer") == 0) {
            do {
                if (strcmp(tabelaLexica[i].lexema, "\0") == 0) {// da erro se ele não encontra o ; até o final dos lexemas 
                    //  printf("ERROROROROORO"); 
                    ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 13);
                }

                i++;
                if (tabelaLexica[i].id > 35 && tabelaLexica[i + 1].id == 28 || tabelaLexica[i + 1].id == 29) {
                    //printf("OK1\n");
                } else {
                    //   printf("ERRROOOO")
                    ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 13);
                }
                i++;
                //printf("oi1111 - %s\n", tabelaLexica[i].lexema);  
                //   printf("valor de i: %d\n", i);
                //  if(tabelaLexica[i].id > 35){
                //   printf("oi1111 - %s\n", tabelaLexica[i].lexema);  
                //t    }

            } while (strcmp(tabelaLexica[i].lexema, ";"));
            if (cont > 1) {
                ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 13);

            }
        }//fim do integer

        if (strcmp(tabelaLexica[i].lexema, "real") == 0) {
            do {
                if (strcmp(tabelaLexica[i].lexema, "\0") == 0) {// da erro se ele não encontra o ; até o final dos lexemas 
                    ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 13);

                }

                i++;
                if (tabelaLexica[i].id > 35 && tabelaLexica[i + 1].id == 28 || tabelaLexica[i + 1].id == 29) {
                    //      printf("OK1\n");
                } else {

                    ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 13);

                }

                i++;
                //printf("oi1111 - %s\n", tabelaLexica[i].lexema);  
                //   printf("valor de i: %d\n", i);
                //  if(tabelaLexica[i].id > 35){
                //   printf("oi1111 - %s\n", tabelaLexica[i].lexema);  
                //t    }

            } while (strcmp(tabelaLexica[i].lexema, ";"));
            // erro do ; no final.
            if (cont > 1) {
                ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 13);
            }
        }//fim do real

        if (strcmp(tabelaLexica[i].lexema, "string") == 0) {
            do {
                if (strcmp(tabelaLexica[i].lexema, "\0") == 0) {// da erro se ele não encontra o ; até o final dos lexemas 
                    ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 13);

                }

                i++;
                if (tabelaLexica[i].id > 35 && tabelaLexica[i + 1].id == 28 || tabelaLexica[i + 1].id == 29) {
                    // printf("OK1\n");
                } else {
                    ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 13);
                }

                i++;
                //printf("oi1111 - %s\n", tabelaLexica[i].lexema);  
                //   printf("valor de i: %d\n", i);
                //  if(tabelaLexica[i].id > 35){
                //   printf("oi1111 - %s\n", tabelaLexica[i].lexema);  
                //t    }

            } while (strcmp(tabelaLexica[i].lexema, ";"));
            // erro do ; no final.
            if (cont > 1) {
                ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 13);
            }
        }//fim do string
        if (tabelaLexica[i].id == 36) {// verifica
            if ((tabelaLexica[i + 1].id > 0 && tabelaLexica[i + 1].id < 13) || (tabelaLexica[i + 1].id > 14 && tabelaLexica[i + 1].id < 17) ||
                    (tabelaLexica[i + 1].id > 26 && tabelaLexica[i + 1].id < 28) || (tabelaLexica[i + 1].id > 32 && tabelaLexica[i + 1].id <= 36)) {
                ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 13);
            }

        }
    }// fim do for

}

void pegarvalorNumerico(char lex[50], int indice, int id) {// irá pegar os lexemas que só possuem digitos e fazer o teste se são integer ou real
    if (id > 35 && isdigit(lex[0])) {
        int i = 1, cont = 0, cont1 = 0;
        //printf("lexemaaa: %s e identificador: %d\n", lex, id);
        while (lex[i] != '\0') {
            if (isdigit(lex[0])) {
                if (lex[i] == '.') {
                    cont++;
                }
                if (cont == 1 && isdigit(lex[i])) {
                    // printf("OKKKK.\n");
                    cont1++;
                }
            }
            i++;
        }
        if (cont == 1 && cont1 > 0) {
            //printf("Numero real.\n");
            tabelaLexica[indice].tipoV = 2;
            tabelaLexica[indice].declarado = 2;
        } else {
            //printf("Numero inteiro.\n");
            tabelaLexica[indice].tipoV = 1;
            tabelaLexica[indice].declarado = 2;
        }

    }
}

void naoDeclarado(char lexema[50], int tamanho, int indice) {// passa pelo vetor e conferi quais foram declarados, caso não ele da erro.
    // printf("\no lexem: %s \n",lexema);
    for (int i2 = 4; i2 <= tamanho; i2++) {// for para buscar varaveis declaradas
        do {
            //printf("\no lexem: %s \n", tabelaLexica[i2].lexema);  
            // printf("o lexema local: %s \n", lexema);  
            if (strcmp(tabelaLexica[i2].lexema, lexema) == 0 && tabelaLexica[i2].tipoV != 0) {
                //  printf("\no lexem: %s e tipoV %d\n", tabelaLexica[i2].lexema, tabelaLexica[i2].tipoV);  
                //  printf("OKKKKKK");
                //  printf("\no lexem local: %s e indice %d \n",lexema, indice);  
                tabelaLexica[indice].tipoV = tabelaLexica[i2].tipoV;
            }


            i2++;
        } while (tabelaLexica[i2].id != 34);

    }
}

void duplicidade(int tamanho) {// achar o erro 6 nos lexemas resgatados
    char dupli[60] = "\0";
    int cont = 0, col = 0, lin = 0;
    for (int i2 = 1; i2 <= tamanho; i2++) {// for para buscar varaveis declaradas

        if (tabelaLexica[i2].declarado == 1 && dupli != "\0") {
            //  printf("valor duplicado: %s e o lexem: %s \n",dupli, tabelaLexica[i2].lexema);
            for (int i2 = 1; i2 <= tamanho; i2++) {// varaveis declaradas que foram usadas 2 vezes

                if (tabelaLexica[i2].declarado == 1 && dupli != "\0") {
                    if (!strcmp(dupli, tabelaLexica[i2].lexema)) {
                        // printf("valor duplicado: %s e o lexem: %s \n",dupli, tabelaLexica[i2].lexema);   
                        cont++;
                    }
                }
            }// botar um while caso não forem do mesmo bloco
            if (cont > 1) {
                //   printf("valor duplicado: %s e o lexem: %d e %d\n", dupli, lin, col);
                ExibirErro(dupli, lin, col, 6);
            }
            cont = 0;
            //printf("valor do cont: %d", cont);
        }
        if (tabelaLexica[i2].declarado == 1) {
            //  printf("token: %s - declarados: %d\n",tabelaLexica[i2].lexema, tabelaLexica[i2].tipoV);
            strcpy(dupli, tabelaLexica[i2].lexema); ///Realiza a copia do conteúdo 
            col = tabelaLexica[i2].coluna;
            lin = tabelaLexica[i2].linha;
        }
    }
}

void gramaticaIF(int tamanho) {// checagem do que pode ser aceito pela condição if

    for (int i = 1; i <= tamanho; i++) {
        if (strcmp(tabelaLexica[i].lexema, "if") == 0) {
            if (tabelaLexica[i + 1].id != 30) {
                ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 24);
            }
            do {
                i++;
                if (strcmp(tabelaLexica[i].lexema, "\0") == 0) {// da erro se ele não encontra o ; até o final dos lexemas 
                    //  printf("ERROROROROORO"); 
                    ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 24);
                }
                if ((tabelaLexica[i].id == 1 && tabelaLexica[i].id == 2 && tabelaLexica[i].id == 3) ||
                        (tabelaLexica[i].id > 4 && tabelaLexica[i].id < 13) || (tabelaLexica[i].id > 14 && tabelaLexica[i].id < 17) ||
                        (tabelaLexica[i].id > 22 && tabelaLexica[i].id < 30) || (tabelaLexica[i].id > 32 && tabelaLexica[i].id < 36)) {
                    ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 24);
                }
                if (tabelaLexica[i].tipoV == 3) {
                    // printf("meu tipo - %d\n", tabelaLexica[i].tipoV);
                    ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 3);
                }
            } while (strcmp(tabelaLexica[i].lexema, "then"));
            if (tabelaLexica[i + 1].id == 5) {
                ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 24);
            }
        }//fim do if
    }
}

void gramaticawhile(int tamanho) {// checagem do que pode ser aceito pela condição while
    /*
        while(s1<>s1) do // falta erro
    begin
    end;
     */

    for (int i = 1; i <= tamanho; i++) {
        if (strcmp(tabelaLexica[i].lexema, "while") == 0) {
            if (tabelaLexica[i + 1].id != 30) {
                ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 25);

            }
            do {
                i++;
                if (strcmp(tabelaLexica[i].lexema, "\0") == 0) {// da erro se ele não encontra o ; até o final dos lexemas 
                    //  printf("ERROROROROORO"); 
                    ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 25);
                }
                if ((tabelaLexica[i].id >= 1 && tabelaLexica[i].id < 7) || (tabelaLexica[i].id > 7 && tabelaLexica[i].id < 13) ||
                        (tabelaLexica[i].id > 14 && tabelaLexica[i].id < 17) || (tabelaLexica[i].id > 22 && tabelaLexica[i].id < 30) ||
                        (tabelaLexica[i].id > 31 && tabelaLexica[i].id < 36)) {
                    ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 25);
                }
                if (tabelaLexica[i].tipoV == 3) {
                    ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 3);
                }
            } while (strcmp(tabelaLexica[i].lexema, "do"));

        }//fim do if
    }


}

void gramaticarepeat(int tamanho) {// checagem do que pode ser aceito pela condição repeat
    int contU = 0, contR = 0, contV = 0;
    /*
        repeat // falta erro


    until (s1<>s1)or (s2<>r4);
     */
    for (int i = 1; i <= tamanho; i++) {
        if (strcmp(tabelaLexica[i].lexema, "until") == 0) {
            if (tabelaLexica[i + 1].id != 30) {
                ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 26);
            }
            do {
                if (strcmp(tabelaLexica[i].lexema, "until") == 0) {
                    contU++;
                }
                i++;
                if (strcmp(tabelaLexica[i].lexema, "\0") == 0) {// da erro se ele não encontra o ; até o final dos lexemas 
                    //  printf("ERROROROROORO"); 
                    ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 26);
                }
                if ((tabelaLexica[i].id >= 1 && tabelaLexica[i].id < 13) || (tabelaLexica[i].id > 14 && tabelaLexica[i].id < 17) ||
                        (tabelaLexica[i].id > 22 && tabelaLexica[i].id < 29) || (tabelaLexica[i].id > 31 && tabelaLexica[i].id < 36)) {
                    ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 26);
                    // printf("valor: %s\n", tabelaLexica[i].lexema);
                }
                if (tabelaLexica[i].tipoV == 3) {
                    ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 3);
                }
            } while (strcmp(tabelaLexica[i].lexema, ";"));

        }//fim do if
    }
    for (int i = 1; i <= tamanho; i++) {
        if (strcmp(tabelaLexica[i].lexema, "repeat") == 0) {
            if (tabelaLexica[i + 1].id == 8 || tabelaLexica[i + 1].id == 9) {
                ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 26);
            }
            do {
                if (strcmp(tabelaLexica[i].lexema, "repeat") == 0) {
                    contR++;
                }
                i++;
            } while (strcmp(tabelaLexica[i].lexema, "("));
        }
    }
    contV = contR + contU;
    if (contV % 2 == 0) {
    } else {
        ExibirErro("until", 0, 0, 20);
    }
}

void gramaticaPA(int tamanho) {// checagem do que pode ser aceito pelos parenteses
    int cont1 = 0, lin = 0, col = 0;
    char aux_le[10] = "\0";
    for (int i = 1; i <= tamanho; i++) {// primeiro for para contagem de parenteses
        if (tabelaLexica[i].id == 30 || tabelaLexica[i].id == 31) {//verifica

            if (tabelaLexica[i].id == 30) {
                cont1++;
                strcpy(aux_le, tabelaLexica[i].lexema); ///Realiza a copia do conteúdo 
                col = tabelaLexica[i].coluna;
                lin = tabelaLexica[i].linha;
            }
            if (tabelaLexica[i].id == 31) {
                cont1--;
            }

            i++;

            //contm = cont1 - cont2;   
            // printf("valor: %d\n", cont1);
        }
    }
    if (cont1 != 0) {

        ExibirErro(aux_le, lin, col, 23);
    }

    for (int i1 = 1; i1 <= tamanho; i1++) {// primeiro for para checagem de parenteses
        if (tabelaLexica[i1].id == 30) {//verifica
            do {
                if (tabelaLexica[i1 + 1].id == 31 || tabelaLexica[i1 + 1].id <= 29// follow do parenteses abre
                        || (tabelaLexica[i1 + 1].id > 32 && tabelaLexica[i1 + 1].id < 36)) {

                    ExibirErro(tabelaLexica[i1 + 1].lexema, tabelaLexica[i1 + 1].linha, tabelaLexica[i1 + 1].coluna, 23);
                }
                //  printf("valor: %s\n", tabelaLexica[i1].lexema);
                i1++;
            } while (strcmp(tabelaLexica[i1].lexema, ")") == 0);
        }
    }
    for (int i1 = 1; i1 <= tamanho; i1++) {// primeiro for para checagem de parenteses
        if (tabelaLexica[i1].id == 30) {
            do {
                if (tabelaLexica[i1 - 1].id == 1 || tabelaLexica[i1 - 1].id <= 2 || tabelaLexica[i1 - 1].id == 4
                        || tabelaLexica[i1 - 1].id == 5 || tabelaLexica[i1 - 1].id == 7 || tabelaLexica[i1 - 1].id == 36// follow do parenteses abre
                        || (tabelaLexica[i1 - 1].id > 8 && tabelaLexica[i1 - 1].id < 12) || (tabelaLexica[i1 - 1].id > 14 && tabelaLexica[i1 - 1].id < 23)
                        || (tabelaLexica[i1 - 1].id > 26 && tabelaLexica[i1 - 1].id < 32) || (tabelaLexica[i1 - 1].id > 32 && tabelaLexica[i1 - 1].id < 36)) {
                    printf("erro: %s\n", tabelaLexica[i1 - 1].lexema); // chamar erro

                    ExibirErro(tabelaLexica[i1 - 1].lexema, tabelaLexica[i1 - 1].linha, tabelaLexica[i1 - 1].coluna, 23);
                }
                // printf("valor: %s\n", tabelaLexica[i1].lexema);
                i1++;
            } while (strcmp(tabelaLexica[i1].lexema, ")") == 0);
        }

    }
    // segunda parte agora com o fecha
    for (int i1 = 1; i1 <= tamanho; i1++) {// segundo for para checagem de parenteses
        if (tabelaLexica[i1].id == 31) {// verifica
            do {
                if (tabelaLexica[i1 + 1].id == 1 || tabelaLexica[i1 + 1].id == 2 || tabelaLexica[i1 + 1].id == 3 || tabelaLexica[i1 + 1].id == 6 || tabelaLexica[i1 + 1].id == 5
                        || (tabelaLexica[i1 + 1].id > 7 && tabelaLexica[i1 + 1].id < 13) || (tabelaLexica[i1 + 1].id > 15 && tabelaLexica[i1 + 1].id < 23) ||
                        (tabelaLexica[i1 + 1].id > 26 && tabelaLexica[i1 + 1].id < 29) || tabelaLexica[i1 + 1].id == 30 || tabelaLexica[i1 + 1].id > 31) {
                    //    printf("erro 111111");
                    ExibirErro(tabelaLexica[i1].lexema, tabelaLexica[i1].linha, tabelaLexica[i1].coluna, 23); //verificar
                }

                // printf("valor: %s\n", tabelaLexica[i1].lexema);
                i1++;
            } while (strcmp(tabelaLexica[i1].lexema, ")") == 0);
        }
    }
    for (int i1 = 1; i1 <= tamanho; i1++) {// primeiro for para checagem de parenteses
        if (tabelaLexica[i1].id == 31) {
            do {
                if (tabelaLexica[i1 - 1].id < 31 || (tabelaLexica[i1 - 1].id > 31 && tabelaLexica[i1 - 1].id < 36)) {
                    ExibirErro(tabelaLexica[i1 - 1].lexema, tabelaLexica[i1 - 1].linha, tabelaLexica[i1 - 1].coluna, 23);
                }

                // printf("----valor: %s\n", tabelaLexica[i1].lexema);
                i1++;
            } while (strcmp(tabelaLexica[i1].lexema, ")") == 0);
        }

    }
}

void gramaticaALL(int tamanho) {// checagem do que pode ser aceito pelo procediemnto all

    // ptok[28] = ","; 29 ;
    for (int i = 1; i <= tamanho; i++) {
        if (strcmp(tabelaLexica[i].lexema, "all") == 0) {
            if (tabelaLexica[i + 1].id != 30) {
                ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 3);
            }
            do {

                i++; //ver depois
                if (tabelaLexica[i].id == 28 && tabelaLexica[i + 1].id == 28) {
                    ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 12);
                }
                if (tabelaLexica[i].id > 35) {
                    //  printf("valor: %s\n",tabelaLexica[i].lexema);
                    //   printf("valor2: %d\n",tabelaLexica[i].tipoV);
                    if (tabelaLexica[i].id == 36 && tabelaLexica[i + 1].id == 29 || tabelaLexica[i + 1].id == 28 || tabelaLexica[i + 1].id == 31) {
                    } else {

                        ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 13);
                    }
                    if (tabelaLexica[i].tipoV != 3) {
                        //        printf("OK %s: ",tabelaLexica[i].lexema);       
                        ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 3);
                    }

                }

            } while (strcmp(tabelaLexica[i].lexema, ";"));


            // } 

        }
    }
}

void ELexico(char caractere, int linha, int coluna) {// irá procurar caractere invalidos da gramatica
    char auxC[1]; // auxilia na copia do token de caracter para string
    auxC[0] = caractere;
    if (!isalnum(caractere) && caractere != ' ' && caractere != ';' && caractere != '.'
            && caractere != ':' && caractere != '=' && caractere != ',' && caractere != '\n'
            && caractere != '+' && caractere != '-' && caractere != '*' && caractere != '/'
            && caractere != '<' && caractere != '>' && caractere != '(' && caractere != ')'
            && caractere != '{' && caractere != '}' && caractere != '\t') {
        lex_aux[0] = '\0';
        ExibirErro(auxC, linha, coluna, 1); // ok. chama erro
    }

}

void ErroSintaticoI(char lex[50], int linha, int coluna, int iden) {// irá procurar ID ou lexemas invalidos que começam com numero. ex: 1n, 3m. 3program etc.  
    if (iden == 36) {
        int i = 1, cont = 0;
        //printf("\n id do lexema: %s e linha: %i\n", lex, linha);
        while (lex[i] != '\0') {
            if (isdigit(lex[0])) {// se tiver um digito com ponto e letra juntos. ex: 5m
                if (isalpha(lex[i])) {
                    //  printf("EROOOOO\n");
                    ExibirErro(lex, linha, coluna, 11); // ok
                }
                if (lex[i] == '.') {
                    cont++;
                }
            }
            if (lex[0] == '.') {
                if (isalnum(lex[i])) {// algum alfabeto com . na frente
                    //  printf("EROOOOO2222\n");
                    ExibirErro(lex, linha, coluna, 12);
                }
            }
            if (isalpha(lex[0])) {// erro de identificador com ponto na frente
                if (lex[i] == '.') {
                    // printf("EROOOOO3333\n");
                    ExibirErro(lex, linha, coluna, 12);
                }
            }
            if (isdigit(lex[0]) && lex[i] == '.') // erro nos casos = 3.|  3.n
                if (!isdigit(lex[i + 1])) {
                    //  printf("ERRRO 555 ...\n");
                    ExibirErro(lex, linha, coluna, 12);
                    conter = 0;
                }
            i++;
        }
        if (cont == 2) {// erro se tiver 2 pontos juntos do digito
            //  printf("EROOOOO4444 %d\n", cont);
            ExibirErro(lex, linha, coluna, 12);
        }

        lex = "\0";
    }
}

void gramaticaprogram(int tamanho) {//ira fazer toda a gramatica do program e apontar erro
    int contabegin = 0;
    //printf("Primeiro token: %d \n", tabelaLexica[1].id);
    if (tabelaLexica[1].id != 16) {
        // printf("\nerro111\n"); //falta erro
        ExibirErro(tabelaLexica[1].lexema, tabelaLexica[1].linha, tabelaLexica[1].coluna, 16);
    } else if (tabelaLexica[2].id < 35) {
        // printf("\nerro22\n"); //falta erro
        ExibirErro(tabelaLexica[2].lexema, tabelaLexica[2].linha, tabelaLexica[2].coluna, 17);
    } else if (tabelaLexica[3].id != 29) {
        // printf("\nerro333\n"); //falta erro
        ExibirErro(tabelaLexica[3].lexema, tabelaLexica[3].linha, tabelaLexica[3].coluna, 18);
    } else if (tabelaLexica[tamanho].id != 34) {
        //printf("\nerro333333\n"); //falta erro
        ExibirErro(tabelaLexica[tamanho].lexema, tabelaLexica[tamanho].linha, tabelaLexica[tamanho].coluna, 19);
    }
    tabelaLexica[2].tipoV = 4; //declarando o id test no vetor declarado para não usar ele.
    for (int i = 1; i <= tamanho; i++) {
        if (tabelaLexica[i].id == 2) {
            if (tabelaLexica[i].id == 2 && tabelaLexica[i + 1].id == 29) {
            } else {
                ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha,
                        tabelaLexica[i].coluna, 21);
            }
        }
    }
    for (int i = 1; i <= tamanho; i++) {
        if (tabelaLexica[i].id == 1) {
            contabegin++;
        }
    }
    if (contabegin < 1) {
        ExibirErro("begin", 1, 2, 22);
    }
}

void atribuirString(int tamanho) {// atribui para o tipo string, pelo fato de ser diferente do real e integer

    for (int i = 1; i <= tamanho; i++) {

        if (strcmp(tabelaLexica[i].lexema, ":=") == 0 && tabelaLexica[i - 1].tipoV == 3) {
            i++;
            do {
                if (tabelaLexica[i].id > 35) {
                    tabelaLexica[i].tipoV = 3;
                }
                //  printf("\noi111 - %s\n", tabelaLexica[i].lexema);
                i++;
            } while (strcmp(tabelaLexica[i].lexema, ";"));
        }
    }

}

void tipoincompativeis(int tamanho) {//checa os tipos das variaveis e token desorganizado

    for (int i = 1; i <= tamanho; i++) {// for para buscar varaveis declaradas
        char lex[60];
        int tipo = 0;
        if (strcmp(tabelaLexica[i].lexema, ":=") == 0) {
            // printf("valor identificado: %s e %d\n",tabelaLexica[i-1].lexema ,tabelaLexica[i-1].tipoV);
            strcpy(lex, tabelaLexica[i - 1].lexema);
            tipo = tabelaLexica[i - 1].tipoV; // neogioc esta aqui
            //printf("lex: %s - tipo: %d\n",lex,tipo);
            i++; // pra tirar o ponto e virgula
            while (strcmp(tabelaLexica[i].lexema, ";")) {
                //  printf("lex: %s - tipo: %d\n", lex, tipo);
                // printf("lexema central: %s - tipo: %d\n\n", tabelaLexica[i].lexema, tabelaLexica[i].tipoV);
                if (tipo == 1) {
                    if (tabelaLexica[i].tipoV != 1 && tabelaLexica[i].tipoV != 0) {// olhar aqui
                        // printf("MEUUU TIPOOOOOO %d \n\n\n", i );
                        //  printf("lexema %s \n\n\n", tabelaLexica[i].lexema );
                        // printf("tipo %d \n\n\n", tabelaLexica[i].tipoV );                                   
                        ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 3);
                        //           printf("erroooo no lexema: %s\n", tabelaLexica[i].lexema); //falta direcionar erro
                    }
                }
                if (tipo == 2) {
                    if (tabelaLexica[i].tipoV != 2 && tabelaLexica[i].tipoV != 1 && tabelaLexica[i].tipoV != 0) {

                        ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 3);
                        //           printf("erroooo no lexema: %s\n", tabelaLexica[i].lexema); //falta direcionar erro
                    }

                }
                if (tipo == 3) {
                    if (tabelaLexica[i].tipoV != 3 && tabelaLexica[i].tipoV != 0) {
                        ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 3);
                        // printf("erroooo no lexema: %s\n", tabelaLexica[i].lexema); //falta direcionar erro
                        //   printf("erroooo no lexema: %d\n", tabelaLexica[i].tipoV);
                    }

                }
                i++;
            }
        }
        if (tabelaLexica[i].tipoV != 0 && tabelaLexica[i].tipoV != 4) {// falta a gramatica de atribuiçaõ
            // printf("\nlexema: %s\n",tabelaLexica[i].lexema); //falta erro 
            //printf("\tipo V: %d\n",tabelaLexica[i].tipoV); //falta erro 
        }
    }

}

void beginEend(int tamanho) {

    int ind = 1, p = 5, c = 1;
    for (int i = 4; i <= tamanho; i++) {

        if (strcmp(tabelaLexica[i].lexema, "begin") == 0) {
            ind--;
            p = tabelaLexica[i].linha;
            c = tabelaLexica[i].coluna;
        }
        if (strcmp(tabelaLexica[i].lexema, "end") == 0) {
            ind++;
            p = tabelaLexica[i].linha;
            c = tabelaLexica[i].coluna;
        }

    }
    if (ind != 0) {
        ExibirErro("Begin ou end", p, c, 20);
    }
}

void condCod3End() {// nao foi usar

    int tamam;
    int i, lin;
    FILE *codInter_arq;
    codInter_arq = fopen("arquivo_3enderecos.txt", "r+");

    proxCaractere = fgetc(codInter_arq); // chamada de caracteres
    do {
        if (isalnum(proxCaractere)) {// caracteres com alfabeto
            strncat(lex_aux, &proxCaractere, 1); //Realiza a concatenação do conteúdo com controle de quantos caracteres                    

        }
        if (proxCaractere == ' ') {// caracteres especiais como espaço e quebra-linha         

            i++;
            strcpy(tabelaLexica[i].bloco, lex_aux); ///Realiza a copia do conteúdo 
            tabelaLexica[i].blocoi = lin; // atribuição da linha


            printf("-%s \n", lex_aux);
            //printf(" coluna: -%i e tam: %i\n", col, tamanho);
        }
        proxCaractere = fgetc(codInter_arq); // chamada de caracteres
    } while (proxCaractere != EOF);

    //fechando o arquivo
    fclose(codInter_arq);

}

char *aux_all(int N) {// funcao que retorna um valor de inteiro para string de quantos param ele retornou.
    switch (N) {
        case 1:
            return "1";
            break;
        case 2:
            return "2";
            break;
        case 3:
            return "3";
            break;
        case 4:
            return "4";
            break;
        case 5:
            return "5";
            break;
        case 6:
            return "6";
            break;
        case 7:
            return "7";
            break;
        case 8:
            return "8";
            break;
        case 9:
            return "9";
            break;
        case 10:
            return "10";
            break;
        case 11:
            return "11";
            break;
        case 12:
            return "12";
            break;
        case 13:
            return "13";
            break;
        case 14:
            return "14";
            break;
        case 15:
            return "15";
            break;
        case 16:
            return "16";
            break;
        case 17:
            return "17";
            break;
        case 18:
            return "18";
            break;
        case 19:
            return "19";
            break;
        case 20:
            return "20";
            break;
            //
        case 21:
            return "1";
            break;
        case 22:
            return "22";
            break;
        case 23:
            return "23";
            break;
        case 24:
            return "24";
            break;
        case 25:
            return "25";
            break;
        case 26:
            return "26";
            break;
        case 27:
            return "27";
            break;
        case 28:
            return "28";
            break;
        case 29:
            return "29";
            break;
        case 30:
            return "30";
            break;
        case 31:
            return "31";
            break;
        case 32:
            return "32";
            break;
        case 33:
            return "33";
            break;
        case 34:
            return "34";
            break;
        case 35:
            return "35";
            break;
        case 36:
            return "36";
            break;
        case 37:
            return "37";
            break;
        case 38:
            return "38";
            break;
        case 39:
            return "39";
            break;
        case 40:
            return "40";
            break;
            //
        case 41:
            return "41";
            break;
        case 42:
            return "42";
            break;
        case 43:
            return "43";
            break;
        case 44:
            return "44";
            break;
        case 45:
            return "45";
            break;
        case 46:
            return "46";
            break;
        case 47:
            return "47";
            break;
        case 48:
            return "48";
            break;
        case 49:
            return "49";
            break;
    }
}

int Iterator(char nome_t[40]) {// manipulação dos caracteres
    FILE* arCodigo; // nome do arquivo
    char aux_caractere = '\0', lex_aux2[] = "\0"; // vetor de caracteres para auxiliar na copia e concatenação
    int tamanho; // me retorna o tamanho dos vetores de caracteres
    arCodigo = fopen(nome_t, "r"); // chamando para leitura o arquivo
    int i = 0; // contagem de quantos lexemas foram registrados
    int lin = 1, col = 1; // contagens de linhas e colunas

    proxCaractere = fgetc(arCodigo); // chamada de caracteres

    do {
        ELexico(proxCaractere, lin, col);
        proxCaractere = tolower(proxCaractere); // toupper transforma em minuscula 
        //strncat(lex_aux, &proxCaractere, 1); //Realiza a concatenação do conteúdo com controle de quantos caracteres 

        if (isdigit(proxCaractere) || proxCaractere == '.') {// caracteres numericos e pontos.
            strncat(lex_aux, &proxCaractere, 1); //Realiza a concatenação do conteúdo com controle de quantos caracteres                    
            col++;
        }

        if (isalpha(proxCaractere)) {// caracteres com alfabeto
            strncat(lex_aux, &proxCaractere, 1); //Realiza a concatenação do conteúdo com controle de quantos caracteres                    
            col++;
        }

        if (aux_caractere == ' ' || proxCaractere == EOF || proxCaractere == '\t') {// caracteres especiais como espaço e quebra-linha
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna 

                //printf("-%s \n", lex_aux);
                //printf(" coluna: -%i e tam: %i\n", col, tamanho);
            }
            col++;
            lex_aux[0] = '\0';

        }
        if (aux_caractere == '\n' || proxCaractere == EOF) {// caracteres especiais como espaço e quebra-linha
            if (lex_aux[0] != '\0') { // caso o valor que está no lexico concatenado for nulo, não passa nesse if.   
                tamanho = strlen(lex_aux);
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo   
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna

                // atribuição da coluna
                // printf("Aqui chegou1 %d -",tamanho);
                //printf("2- %s e tamanho %d \n", lex_aux, tamanho);
                if (tamanho > 1 && lex_aux[0] == ';') {// checagem se tem caractere junto do ponto e virgula
                    ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 14);
                }
            }
            lin++;
            col = 1;
            lex_aux[0] = '\0';
        }

        if (proxCaractere == ';') {// copia o que foi concatenado              
            if (lex_aux[0] != '\0') { // caso o valor que está no lexico concatenado for nulo, não passa nesse if.      
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo   
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna
                // printf("3-%s \n", lex_aux);

            }
            lex_aux[0] = '\0';

        }
        if (aux_caractere == ';') {//concatenação do ;
            strncat(lex_aux, &proxCaractere, 1); //Realiza a concatenação do conteúdo com controle de quantos caracteres   
            lex_aux[0] = ';';
            col++;
        }

        if (proxCaractere == ':') {// copia o que foi concatenado quando está junto a outro caractere.
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna
                //printf("-%s \n", lex_aux);
            }
            lex_aux[0] = '\0';
        }
        if (aux_caractere == ':') {//concatenação do ;
            strncat(lex_aux, &proxCaractere, 1); //Realiza a concatenação do conteúdo com controle de quantos caracteres   
            col++;
        }
        if (proxCaractere == ':') {// copia o que foi concatenado
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna
                // printf("-%s \n", lex_aux);
            }
            lex_aux[0] = '\0';
        }
        if (proxCaractere == '=') {// copia o que foi concatenado
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna
                // printf("-%s \n", lex_aux);
            }
            lex_aux[0] = '\0';
        }
        if (aux_caractere == '=') {//concatenação do ;
            strncat(lex_aux, &proxCaractere, 1); //Realiza a concatenação do conteúdo com controle de quantos caracteres   
            col++;
        }
        if (proxCaractere == '=') {// copia o que foi concatenado
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna
                //printf("-%s \n", lex_aux);
            }
            lex_aux[0] = '\0';
        }
        if (proxCaractere == '(') {// copia o que foi concatenado
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna
                // printf("-%s \n", lex_aux);
            }
            lex_aux[0] = '\0';
        }
        if (aux_caractere == '(') {//concatenação do ;
            strncat(lex_aux, &proxCaractere, 1); //Realiza a concatenação do conteúdo com controle de quantos caracteres   
            col++;
        }
        if (proxCaractere == '(') {// copia o que foi concatenado
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna
                //printf("-%s \n", lex_aux);
            }
            lex_aux[0] = '\0';
        }
        if (proxCaractere == ')') {// copia o que foi concatenado
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna
                //  printf("-%s \n", lex_aux);
            }
            lex_aux[0] = '\0';
        }
        if (aux_caractere == ')') {//concatenação do ;
            strncat(lex_aux, &proxCaractere, 1); //Realiza a concatenação do conteúdo com controle de quantos caracteres   
            col++;
        }
        if (proxCaractere == ')') {// copia o que foi concatenado
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna
                // printf("-%s \n", lex_aux);
            }
            lex_aux[0] = '\0';
        }
        if (proxCaractere == '>') {// copia o que foi concatenado
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna
                // printf("-%s \n", lex_aux);
            }
            lex_aux[0] = '\0';
        }
        if (aux_caractere == '>') {//concatenação do ;
            strncat(lex_aux, &proxCaractere, 1); //Realiza a concatenação do conteúdo com controle de quantos caracteres   
            col++;
        }
        if (proxCaractere == '>') {// copia o que foi concatenado
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna
                //printf("-%s \n", lex_aux);
            }
            lex_aux[0] = '\0';
        }
        if (proxCaractere == '<') {// copia o que foi concatenado
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna
                //  printf("-%s \n", lex_aux);
            }
            lex_aux[0] = '\0';
        }
        if (aux_caractere == '<') {//concatenação do ;
            strncat(lex_aux, &proxCaractere, 1); //Realiza a concatenação do conteúdo com controle de quantos caracteres   
            col++;
        }
        if (proxCaractere == '<') {// copia o que foi concatenado
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna
                //  printf("-%s \n", lex_aux);
            }
            lex_aux[0] = '\0';
        }
        if (proxCaractere == ',') {// copia o que foi concatenado
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna  
                // printf("-%s \n", lex_aux);
            }
            lex_aux[0] = '\0';
        }
        if (aux_caractere == ',') {//concatenação do ;
            strncat(lex_aux, &proxCaractere, 1); //Realiza a concatenação do conteúdo com controle de quantos caracteres   
            col++;
        }
        if (proxCaractere == ',') {// copia o que foi concatenado
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna
                // printf("-%s \n", lex_aux);
            }
            lex_aux[0] = '\0';
        }
        if (proxCaractere == '/') {// copia o que foi concatenado
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna
                tabelaLexica[i].tipoV = 1; // atribuição do tipo
                //printf("-%s \n", lex_aux);
            }
            lex_aux[0] = '\0';
        }
        if (aux_caractere == '/') {//concatenação do ;
            strncat(lex_aux, &proxCaractere, 1); //Realiza a concatenação do conteúdo com controle de quantos caracteres   
            col++;
        }
        if (proxCaractere == '/') {// copia o que foi concatenado
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna
                tabelaLexica[i].tipoV = 2; // atribuição do tipo
                // printf("-%s \n", lex_aux);
            }
            lex_aux[0] = '\0';
        }
        if (proxCaractere == '+') {// copia o que foi concatenado
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna 
                tabelaLexica[i].tipoV = 2; // atribuição do tipo
                //printf("-%s \n", lex_aux);

            }
            lex_aux[0] = '\0';
        }
        if (aux_caractere == '+') {//concatenação do ;
            strncat(lex_aux, &proxCaractere, 1); //Realiza a concatenação do conteúdo com controle de quantos caracteres   
            col++;
        }
        if (proxCaractere == '+') {// copia o que foi concatenado
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna
                tabelaLexica[i].tipoV = 1; // atribuição do tipo
                //printf("-%s \n", lex_aux);
            }
            lex_aux[0] = '\0';
        }
        if (proxCaractere == '-') {// copia o que foi concatenado
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna
                tabelaLexica[i].tipoV = 2; // atribuição do tipo
                // printf("-%s \n", lex_aux);
            }
            lex_aux[0] = '\0';
        }
        if (aux_caractere == '-') {//concatenação do ;
            strncat(lex_aux, &proxCaractere, 1); //Realiza a concatenação do conteúdo com controle de quantos caracteres   
            col++;
        }
        if (proxCaractere == '-') {// copia o que foi concatenado
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna
                tabelaLexica[i].tipoV = 1; // atribuição do tipo
                //printf("-%s \n", lex_aux);
            }
            lex_aux[0] = '\0';
        }
        if (proxCaractere == '*') {// copia o que foi concatenado
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna
                tabelaLexica[i].tipoV = 2; // atribuição do tipo
                //printf("-%s \n", lex_aux);
            }
            lex_aux[0] = '\0';
        }
        if (aux_caractere == '*') {//concatenação do ;
            strncat(lex_aux, &proxCaractere, 1); //Realiza a concatenação do conteúdo com controle de quantos caracteres   
            col++;
        }
        if (proxCaractere == '*') {// copia o que foi concatenado
            if (lex_aux[0] != '\0') {
                tamanho = strlen(lex_aux); //retorno o valor da string, quantas letras ela possui.
                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo 
                tabelaLexica[i].linha = lin; // atribuição da linha
                tabelaLexica[i].coluna = col - tamanho; // atribuição da coluna
                tabelaLexica[i].tipoV = 1; // atribuição do tipo
                //  printf("-%s \n", lex_aux);
            }
            lex_aux[0] = '\0';
        }
        if (proxCaractere == '}') {
            char aux_coment[1] = "}";
            ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 15);

        }
        if (proxCaractere == '{') {
            char coment[1] = "}";
            //  printf("comentario-%s \n", coment);
            while (proxCaractere != '}') {
                if (proxCaractere == '\n') {
                    lin++; // contagem de linhas quando o loop estiver dentro do coment.
                }
                proxCaractere = fgetc(arCodigo);

                if (proxCaractere == EOF) {

                    ExibirErro(tabelaLexica[i].lexema, tabelaLexica[i].linha, tabelaLexica[i].coluna, 15);

                    break;
                }
            }
        }
        // printf("%c \n", proxCaractere);  //printf("%c\n", proxCaractere);

        // juntar 2 caracteres especiais
        if (proxCaractere == '=' || proxCaractere == '>') {
            strncpy(lex_aux2, tabelaLexica[i - 1].lexema, 1); ///Realiza a copia do conteúdo  

            if (lex_aux2[0] == ':' && proxCaractere == '=') {
                --i;
                strcpy(tabelaLexica[i].lexema, ":="); ///Realiza a copia do conteúdo  
            }
            if (lex_aux2[0] == '>' && proxCaractere == '=') {
                --i;
                strcpy(tabelaLexica[i].lexema, ">="); ///Realiza a copia do conteúdo  
            }
            if (lex_aux2[0] == '<' && proxCaractere == '=') {
                --i;
                strcpy(tabelaLexica[i].lexema, "<="); ///Realiza a copia do conteúdo  
            }
            if (lex_aux2[0] == '<' && proxCaractere == '>') {
                --i;
                strcpy(tabelaLexica[i].lexema, "<>"); ///Realiza a copia do conteúdo  
            }
            lex_aux2[0] == '\0';
        } // juntar 2 caracteres especiais   

        proxCaractere = fgetc(arCodigo);

        aux_caractere = proxCaractere; // outra char para melhor auxiliar nos caracteres    
        if (proxCaractere == EOF) {
            if (lex_aux[0] != '\0') {

                i++;
                strcpy(tabelaLexica[i].lexema, lex_aux); ///Realiza a copia do conteúdo   
                //printf("-%s \n", lex_aux);
                //lin++;
            }

            lex_aux[0] = '\0';
        }


    } while (proxCaractere != EOF);


    // printf("numero de lexemas %d, numero de linhas: %d\n", i, lin);
    //printf("\nPrimeiro token: %s e proximo: %d\n", tabelaLexica[45].lexema, tabelaLexica[45].tipoV);
    //printf("Primeiro com linha: %d e proximo: %d\n", tabelaLexica[1].linha, tabelaLexica[2].linha);
    //printf("Primeiro com coluna: %d e proximo: %d\n", tabelaLexica[2].coluna, tabelaLexica[2].coluna);
    //tamanho = strlen(tabelaLexica[42].lexema);

    if (tamanho != 0) {
        //     printf("Tamanho - %d\n\n\n\n", tamanho);
    }
    //chamadas
    TamanhoL = i; // resgato o tamanho total dos lexemas
    for (int i1 = 1; i1 <= i; i1++) {
        GerarTabela(tabelaLexica[i1].lexema, i1); // geração da tabela lexica     
        ErroSintaticoI(tabelaLexica[i1].lexema, tabelaLexica[i1].linha, tabelaLexica[i1].coluna, tabelaLexica[i1].id);
        pegarvalorNumerico(tabelaLexica[i1].lexema, i1, tabelaLexica[i1].id);
    }
    gramaticaVariavel(i);
    declararVariavel(i);
    duplicidade(i);
    gramaticaprogram(i);
    for (int i1 = 1; i1 <= i; i1++) {//varaiveis não declaradas
        if (tabelaLexica[i1].declarado == 0 && tabelaLexica[i1].id > 35) {
            naoDeclarado(tabelaLexica[i1].lexema, i, i1);
        }

    }
    atribuirString(i);
    for (int i4 = 3; i4 <= i; i4++) {// chama o erro de não atribuiçao
        if (tabelaLexica[i4].tipoV == 0 && tabelaLexica[i4].id > 35) {
            //  printf("numero do tipo: %s \n", tabelaLexica[i4].lexema);
            ExibirErro(tabelaLexica[i4].lexema, tabelaLexica[i4].linha, tabelaLexica[i4].coluna, 4);
        }

    }// fim erro de atribuição 04    
    // tipoincompativeis(i); // exibir erro.
    gramaticaAtribuir(i);
    beginEend(i);
    gramaticaPA(i);
    gramaticaALL(i);
    gramaticaIF(i);
    gramaticawhile(i);
    gramaticarepeat(i);
    tipoincompativeis(i); // exibir erro.

    printf("\n\n");
    printf("\n::: Compilado com sucesso :::\n\n");

    // printf("Primeiro token: %d e proximo: %d\n", tabelaLexica[51].bloco, tabelaLexica[52].bloco);

    //FIm das chamadas

    //printf("\n\nnumero do tipo V %d \n", tabelaLexica[19].tipoV);

    //for (int i1 = 1; i1 <= i; i1++) {
    //      if (tabelaLexica[i1].declarado == 1){
    //        printf("declarados: %s\n",tabelaLexica[i1].lexema);  }
    //     }
    // printf("\n valor do id do lexema: %d", tabelaLexica[2].tipoV);//mostra o valor de V no indice indicado
    fclose(arCodigo);
    // exit(0);
}

int main(int argc, char** argv) {
    int li = 1, posi, linhaB = 0, aux_op = 1, linhaCOD = 0; // variaveis auxiliares, para 2 parte. pega posicao para o codigo 3 enderecos, posi: do tmp para alternar, linhab auzlia nas linhas do vetor bloco, aux_op auxilia nos operadores. linha COD auxilia na exclusao de linhas
    char Vinicio[20], op[4]; // vicnicio pega o id antes do :=, op: pega os operadores quando existirem 2
    construtor();
    FILE *arqNome;
    char nome[40], nomext[] = ".txt", *aux_tmp = "\0"; // string auxiliares : aux_tmp para axuliar no #tmp
    int contAll = 0; // conta quantos param tem no all
    printf("\n\n");
    printf("|===============================================|\n"); //Inicio da tela.
    printf("|== Digite o nome do arquivo a ser compilado: ==|\n");
    printf("|== Caso deseja sair, digite 0: ==|\n\n");
    printf("|==Tem certeza? ==|\n\n");
    printf("|===============================================|\n"); //Inicio da tela.
    scanf("%s", nome);

    strcat(nome, nomext); //concateno com o nome da extensão
    //strcpy();//copiando "variavel fora do typedef" para "variavel dentro type"
    arqNome = fopen(nome, "r");
    if (nome == 0) {
        return (EXIT_SUCCESS);
    }
    if (nome == NULL) { //testando se arquivo existe.
        printf("\n\n==== Arquivo inexistente ou Saida =====");
        fclose(arqNome);
        exit(0); // termina o programa
    } else {
        fclose(arqNome);
        Iterator(nome);

        // começo da 2 parte do trabalho

        // Gerador de Codigo Intermediario


        //Gravando lexemas no arquivo, recria a cada execucao.
        for (int i1 = 1; i1 <= TamanhoL; i1++) {
            /*
            começo da parte 2 do trabalho            
             */
            if (tabelaLexica[i1].id != 29 && tabelaLexica[i1].id != 2 && tabelaLexica[i1].id != 1) {// começo da atribuiçao para o novo vetor sem ; begin end
                if (tabelaLexica[i1].id == 36 && tabelaLexica[i1 + 1].id == 32) {// caso esteja 1 id e na proxima um := entrar para fazer o codigo 3 endereços
                    if (tabelaLexica[i1 + 2].id == 30 || (tabelaLexica[i1 + 5].id == 23 ||
                            tabelaLexica[i1 + 5].id == 24 || tabelaLexica[i1 + 5].id == 25 || tabelaLexica[i1 + 5].id == 26)) {// pego os numero entre parenteses e se tem operador
                        //printf("ARARAQUARA: %s\n", tabelaLexica[i1-2].lexema);    
                        //tabela3end(tabelaLexica[i2].bloco, tabelaLexica[i2+1].bloco)      
                        strcpy(Vinicio, tabelaLexica[i1].lexema); //alimentando valor de inicio

                        while (tabelaLexica[i1].id != 29) {// rodando ate achar ; ate terminar a customizacao
                            i1++;
                            // começo da separaçao entre parenteses ()
                            if (tabelaLexica[i1].id != 30 && tabelaLexica[i1].id != 31) {// retiro os parenteses
                                if (tabelaLexica[i1].id == 36 && (tabelaLexica[i1 + 1].id >= 23 && tabelaLexica[i1 + 1].id <= 26) && tabelaLexica[i1 + 2].id == 36 &&
                                        tabelaLexica[i1 + 3].id == 31) {// a cada trecho ( ) pego os lexemas
                                    if (tabelaLexica[i1 - 2].id == 32) {// utilizaçao de onde podera se encaixar o tmp1 e tmp2
                                        aux_tmp = "#tmp1";
                                        posi = 1;
                                        // printf("\nAQUIIIIII %s\n", tabelaLexica[i1-2].lexema); // copia
                                    } else {
                                        aux_tmp = "#tmp2";
                                        posi = 2;
                                    }
                                    // printf(" entrou com lexema: %s", tabelaLexica[i1].lexema);
                                    // printf(" %s", tabelaLexica[i1 + 1].lexema); // copia
                                    // printf(" %s\n", tabelaLexica[i1 + 2].lexema); //copia
                                    // printf(" linha: %d\n", tabelaLexica[i1].linha); //copia
                                    //printf(" posi: %s\n", aux_tmp);

                                    if (tabelaLexica[i1 + 4].id >= 23 && tabelaLexica[i1 + 4].id <= 26) {// pego o operador do meio e faço a arvore sintatica
                                        strcpy(op, tabelaLexica[i1 + 4].lexema); //alimentando o lexema

                                    }

                                    strcpy(tabelaLexica[li].bloco, aux_tmp); //alimentando o lexema   
                                    tabelaLexica[li].blocoi = 36; // alimentando o id do token
                                    tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                    //
                                    strcpy(tabelaLexica[li + 1].bloco, ":="); //alimentando o lexema
                                    tabelaLexica[li + 1].blocoi = 32; // alimentando o id do token
                                    tabelaLexica[li + 1].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                    //
                                    strcpy(tabelaLexica[li + 2].bloco, tabelaLexica[i1].lexema); //alimentando o lexema
                                    tabelaLexica[li + 2].blocoi = 36; // alimentando o id do token
                                    tabelaLexica[li + 2].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                    //
                                    strcpy(tabelaLexica[li + 3].bloco, tabelaLexica[i1 + 1].lexema); //alimentando operador
                                    tabelaLexica[li + 3].blocoi = tabelaLexica[i1 + 1].id; // alimentando o id do token
                                    tabelaLexica[li + 3].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                    //
                                    strcpy(tabelaLexica[li + 4].bloco, tabelaLexica[i1 + 2].lexema); //alimentando o lexema
                                    tabelaLexica[li + 4].blocoi = 36; // alimentando o id do token
                                    tabelaLexica[li + 4].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                    //acrescimo de linha
                                    li = li + 5;
                                    i1 = i1 + 2;
                                    linhaB++;
                                    if (tabelaLexica[i1 - 5].id >= 23 && tabelaLexica[i1 - 5].id <= 26) {//pego o operador que esta
                                        strcpy(tabelaLexica[li].bloco, aux_tmp); //alimentando o lexema
                                        tabelaLexica[li].blocoi = 36; // alimentando o id do token
                                        tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                        //
                                        strcpy(tabelaLexica[li + 1].bloco, ":="); //alimentando o lexema
                                        tabelaLexica[li + 1].blocoi = 32; // alimentando o id do token
                                        tabelaLexica[li + 1].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                        //
                                        strcpy(tabelaLexica[li + 2].bloco, tabelaLexica[i1].lexema); //alimentando o lexema
                                        tabelaLexica[li + 2].blocoi = 36; // alimentando o id do token
                                        tabelaLexica[li + 2].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                        //
                                        strcpy(tabelaLexica[li + 3].bloco, tabelaLexica[i1 + 1].lexema); //alimentando o lexema
                                        tabelaLexica[li + 3].blocoi = tabelaLexica[i1 + 1].id; // alimentando o id do token
                                        tabelaLexica[li + 3].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex                                     
                                        //
                                        strcpy(tabelaLexica[li + 4].bloco, tabelaLexica[i1 + 2].lexema); //alimentando o lexema
                                        tabelaLexica[li + 4].blocoi = 36; // alimentando o id do token
                                        tabelaLexica[li + 4].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                        //acrescimo de linha
                                        li = li + 5;
                                        i1 = i1 + 2;
                                        linhaB++;

                                    }
                                    // printf("\n primeiro: %s\n\n", tabelaLexica[i1+2].lexema);
                                    if (tabelaLexica[i1 + 2].id == 29) {// caso no final do trecho um ; paro de rodar esse trecho
                                        // printf("\n primeiro: %s\n\n", tabelaLexica[i1-4].lexema);
                                        //printf("\n %s := tmp1 %s tmp2 \n\n",Vinicio, op); 

                                        strcpy(tabelaLexica[li].bloco, tabelaLexica[i1 - 11].lexema); //alimentando o lexema
                                        tabelaLexica[li].blocoi = 36; // alimentando o id do token
                                        tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                        //
                                        strcpy(tabelaLexica[li + 1].bloco, ":="); //alimentando o lexema
                                        tabelaLexica[li + 1].blocoi = 32; // alimentando o id do token
                                        tabelaLexica[li + 1].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                        //
                                        strcpy(tabelaLexica[li + 2].bloco, "#tmp1"); //alimentando o lexema
                                        tabelaLexica[li + 2].blocoi = 36; // alimentando o id do token
                                        tabelaLexica[li + 2].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                        //
                                        strcpy(tabelaLexica[li + 3].bloco, op); //alimentando o lexema
                                        tabelaLexica[li + 3].blocoi = tabelaLexica[i1 - 4].id; // alimentando o id do token
                                        tabelaLexica[li + 3].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                        //tprintf("Lexema: %s e id: %d\n",tabelaLexica[i1-4].lexema, tabelaLexica[i1 -4].id);
                                        //
                                        strcpy(tabelaLexica[li + 4].bloco, "#tmp2"); //alimentando o lexema
                                        tabelaLexica[li + 4].blocoi = 36; // alimentando o id do token
                                        tabelaLexica[li + 4].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                        //acrescimo de linha
                                        li = li + 5;
                                        i1 = i1 + 2;
                                        linhaB++;
                                        // strcpy(tabelaLexica[li].bloco, tabelaLexica[i1 + 2].lexema); //alimentando o lexema
                                        //    tabelaLexica[li].blocoi = tabelaLexica[i1 + 2].id; // alimentando o id do token
                                        //   tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                    }
                                }
                            } // FIM da separaçao entre parenteses ()
                            // começo da separaçao sem parenteses
                            if (tabelaLexica[i1].id != 30 && tabelaLexica[i1].id != 31) {// retiro os ()
                                if (tabelaLexica[i1].id == 36 && (tabelaLexica[i1 + 1].id >= 23 && tabelaLexica[i1 + 1].id <= 26) && tabelaLexica[i1 + 2].id == 36 &&
                                        (tabelaLexica[i1 + 3].id >= 23 && tabelaLexica[i1 + 3].id <= 26)) {// procuro se na posicao existe loop em par, ex: 1+2+3
                                    while (tabelaLexica[i1].id != 29) { // retiro os ;                                  
                                        // printf("\n entrou outro: %s", tabelaLexica[i1].lexema);                                       
                                        //printf("Proximo: %s",tabelaLexica[i1+1].lexema);
                                        if (tabelaLexica[i1].id == 36 && tabelaLexica[i1 - 1].id == 32) { // codicao para alocar o primeiro numero
                                            // printf("\n%s := %s ",Vinicio,tabelaLexica[i1].lexema);   
                                            //inicio da coleta
                                            strcpy(tabelaLexica[li].bloco, Vinicio); //alimentando o lexema
                                            tabelaLexica[li].blocoi = 36; // alimentando o id do token
                                            tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                            //
                                            strcpy(tabelaLexica[li + 1].bloco, ":="); //alimentando o lexema
                                            tabelaLexica[li + 1].blocoi = 32; // alimentando o id do token
                                            tabelaLexica[li + 1].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                            //
                                            strcpy(tabelaLexica[li + 2].bloco, tabelaLexica[i1].lexema); //alimentando o lexema
                                            tabelaLexica[li + 2].blocoi = 36; // alimentando o id do token
                                            tabelaLexica[li + 2].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do le
                                            //acrescimo de linha
                                            li = li + 3;
                                            //  i1 = i1 + 2;
                                            linhaB++;
                                            //fim da coleta
                                        } else {// aloco os 2 loop de operaçoes, tipo arvore sintatica
                                            if (tabelaLexica[i1 + 1].id == 36) { // alocaçao do primeiro loop
                                                // printf("\n%s := %s %s %s ",Vinicio,Vinicio,tabelaLexica[i1].lexema, tabelaLexica[i1+1].lexema);                                 
                                                //inicio da coleta
                                                strcpy(tabelaLexica[li].bloco, Vinicio); //alimentando o lexema
                                                tabelaLexica[li].blocoi = 36; // alimentando o id do token
                                                tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                                //
                                                strcpy(tabelaLexica[li + 1].bloco, ":="); //alimentando o lexema
                                                tabelaLexica[li + 1].blocoi = 32; // alimentando o id do token
                                                tabelaLexica[li + 1].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                                //
                                                strcpy(tabelaLexica[li + 2].bloco, Vinicio); //alimentando o lexema
                                                tabelaLexica[li + 2].blocoi = 36; // alimentando o id do token
                                                tabelaLexica[li + 2].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                                //
                                                strcpy(tabelaLexica[li + 3].bloco, tabelaLexica[i1].lexema); //alimentando o lexema
                                                tabelaLexica[li + 3].blocoi = tabelaLexica[i1].id; // alimentando o id do token
                                                tabelaLexica[li + 3].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                                //tprintf("Lexema: %s e id: %d\n",tabelaLexica[i1-4].lexema, tabelaLexica[i1 -4].id);
                                                //
                                                strcpy(tabelaLexica[li + 4].bloco, tabelaLexica[i1 + 1].lexema); //alimentando o lexema
                                                tabelaLexica[li + 4].blocoi = 36; // alimentando o id do token
                                                tabelaLexica[li + 4].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                                //acrescimo de linha
                                                li = li + 5;
                                                i1 = i1 + 1;
                                                linhaB++;
                                                //fim da coleta
                                            }
                                        }
                                        i1++;
                                    }
                                }
                            } // FIM da separaçao sem parenteses        
                        }//fim do while                 
                    }
                    aux_tmp = "\0";
                }
                // 3 enderecos do 1-all, 2-while, 3-if, 4-repeat,
                if (tabelaLexica[i1].id == 12) {// procuro o 1-all
                    i1++; // acrescento para pular o lexema all
                    while (tabelaLexica[i1].id != 29) {// vou ate o ;
                        if (tabelaLexica[i1].id == 36) {// pego os identificadores
                            //  printf("param %s\n", tabelaLexica[i1].lexema);
                            //inicio da transferencia
                            strcpy(tabelaLexica[li].bloco, "param"); //alimentando o lexema
                            tabelaLexica[li].blocoi = 55; // alimentando o id do token
                            tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //tprintf("Lexema: %s e id: %d\n",tabelaLexica[i1-4].lexema, tabelaLexica[i1 -4].id);
                            //
                            strcpy(tabelaLexica[li + 1].bloco, tabelaLexica[i1].lexema); //alimentando o lexema
                            tabelaLexica[li + 1].blocoi = 36; // alimentando o id do token
                            tabelaLexica[li + 1].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //acrescimo de linha
                            li = li + 2;
                            // i1 = i1 + 1;
                            linhaB++;
                            //fim
                            contAll++;
                        }//fim if
                        i1++; // contagem dentro do while                       
                    }// fim do while
                    // printf("\ncall all,%d\n\n", contAll);
                    //começo
                    strcpy(tabelaLexica[li].bloco, "call all, "); //alimentando o lexema
                    tabelaLexica[li].blocoi = 55; // alimentando o id do token
                    tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                    //                    
                    strcpy(tabelaLexica[li + 1].bloco, aux_all(contAll)); //chamando aux_aul para transofmar o numero inteiro em char
                    tabelaLexica[li + 1].blocoi = 36; // alimentando o id do token
                    tabelaLexica[li + 1].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                    //acrescimo de linha
                    li = li + 2;
                    //i1 = i1 + 1;
                    linhaB++;
                    //fim
                    contAll = 0; // contagem de quantos id tem no all

                }//fim do 1-all

                //começo 4-repeat de 3 enderecos
                if (tabelaLexica[i1].id == 8) {// procuro o until
                    aux_op = 1;
                    i1++; // acrescento para pular o lexema until
                    aux_tmp = "#tmp2";
                    while (tabelaLexica[i1].id != 29) {// vou ate o ;

                        if (tabelaLexica[i1].id == 36 || (tabelaLexica[i1].id >= 17 &&
                                tabelaLexica[i1].id <= 22)) {// algort do tmp
                            if (aux_tmp == "#tmp2") {
                                aux_tmp = "#tmp1";
                            } else {
                                aux_tmp = "#tmp2";
                            }
                            //printf("- %s - e li:%d\n", tabelaLexica[i1].lexema,li);                       
                            if (tabelaLexica[i1].id == 36 && tabelaLexica[i1 + 1].id == 31) {// atribuiçao dos valores
                                //  printf("\n--- %s := ", aux_tmp);
                                ///     printf(" %s", tabelaLexica[i1 - 2].lexema);
                                ///     printf(" %s", tabelaLexica[i1 - 1].lexema);
                                //     printf(" %s\n", tabelaLexica[i1].lexema);
                                //inicio
                                //verifica o (())
                                //começo
                                if (aux_op > 4) {
                                    strcpy(tabelaLexica[li].bloco, "#tmp3"); //alimentando o lexema
                                    tabelaLexica[li].blocoi = 36; // alimentando o id do token
                                    tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                } else {
                                    strcpy(tabelaLexica[li].bloco, aux_tmp); //alimentando o lexema
                                    tabelaLexica[li].blocoi = 36; // alimentando o id do token
                                    tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB;
                                }//alimentando a linha do lex
                                //                    
                                strcpy(tabelaLexica[li + 1].bloco, ":="); //chamando aux_aul para transofmar o numero inteiro em char
                                tabelaLexica[li + 1].blocoi = 32; // alimentando o id do token
                                tabelaLexica[li + 1].blocoli = tabelaLexica[i1].linha + linhaB;
                                //
                                strcpy(tabelaLexica[li + 2].bloco, tabelaLexica[i1 - 2].lexema); //alimentando o lexema
                                tabelaLexica[li + 2].blocoi = tabelaLexica[i1 - 2].id; // alimentando o id do token
                                tabelaLexica[li + 2].blocoli = tabelaLexica[i1 - 2].linha + linhaB; //alimentando a linha do lex
                                //
                                strcpy(tabelaLexica[li + 3].bloco, tabelaLexica[i1 - 1].lexema); //alimentando o lexema
                                tabelaLexica[li + 3].blocoi = tabelaLexica[i1 - 1].id; // alimentando o id do token
                                tabelaLexica[li + 3].blocoli = tabelaLexica[i1 - 1].linha + linhaB; //alimentando a linha do lex
                                //
                                strcpy(tabelaLexica[li + 4].bloco, tabelaLexica[i1].lexema); //alimentando o lexema
                                tabelaLexica[li + 4].blocoi = tabelaLexica[i1].id; // alimentando o id do token
                                tabelaLexica[li + 4].blocoli = tabelaLexica[i1].linha + linhaB;
                                //fim
                                //printf("OIII: %d e id: %d\n", aux_op, tabelaLexica[i1 - 11].id); // se achar until nao tem mais q 2 operandos//verifica apos acerto do ()
                                li = li + 5;
                                //i1 = i1 + 1;
                                linhaB++;
                            }

                            if (tabelaLexica[i1 + 2].id == 13 || tabelaLexica[i1 + 2].id == 14) {// resgata o operador
                                //printf("\nseparaçao OPPPP %s \n\n", tabelaLexica[i1 + 2].lexema);
                                strcpy(op, tabelaLexica[i1 + 2].lexema);
                                aux_op++;
                            }
                        }
                        i1++;
                        if (tabelaLexica[i1 + 1].id == 29 && aux_op > 1) {
                            //  printf("\n #tmp1 := #tmp1 %s #tmp2\n", op);
                            // printf("\n OKKKKK %d\n", aux_op);
                            //começo
                            strcpy(tabelaLexica[li].bloco, "#tmp1"); //alimentando o lexema
                            tabelaLexica[li].blocoi = 36; // alimentando o id do token
                            tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //                    
                            strcpy(tabelaLexica[li + 1].bloco, ":="); //chamando aux_aul para transofmar o numero inteiro em char
                            tabelaLexica[li + 1].blocoi = 32; // alimentando o id do token
                            tabelaLexica[li + 1].blocoli = tabelaLexica[i1].linha + linhaB;
                            //
                            strcpy(tabelaLexica[li + 2].bloco, "#tmp1"); //alimentando o lexema
                            tabelaLexica[li + 2].blocoi = tabelaLexica[i1].id; // alimentando o id do token
                            tabelaLexica[li + 2].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //
                            strcpy(tabelaLexica[li + 3].bloco, op); //alimentando o lexema
                            tabelaLexica[li + 3].blocoi = 13; // alimentando o id do token
                            tabelaLexica[li + 3].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //
                            if (aux_op > 4) {
                                strcpy(tabelaLexica[li + 4].bloco, "#tmp3"); //alimentando o lexema
                                tabelaLexica[li + 4].blocoi = 36; // alimentando o id do token
                                tabelaLexica[li + 4].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            } else {
                                strcpy(tabelaLexica[li + 4].bloco, "#tmp2"); //alimentando o lexema
                                tabelaLexica[li + 4].blocoi = 36; // alimentando o id do token
                                tabelaLexica[li + 4].blocoli = tabelaLexica[i1].linha + linhaB;
                            }
                            //fim
                            li = li + 5;
                            //i1 = i1 + 1;
                            linhaB++;
                            aux_op++;
                        }
                        //printf("oi: %d\n\n",aux_op);
                        if (aux_op == 3 && (tabelaLexica[i1 - 5].id == 13 || tabelaLexica[i1 - 5].id == 14)) {//caso ache mais que 2 operadores
                            //  printf("\n #tmp2 := #tmp1 %s #tmp2\n", tabelaLexica[i1 - 5].lexema); //verifica o (())
                            //printf("oi: %d\n\n",aux_op);
                            //começo
                            strcpy(tabelaLexica[li].bloco, "#tmp2"); //alimentando o lexema
                            tabelaLexica[li].blocoi = 36; // alimentando o id do token
                            tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //                    
                            strcpy(tabelaLexica[li + 1].bloco, ":="); //chamando aux_aul para transofmar o numero inteiro em char
                            tabelaLexica[li + 1].blocoi = 32; // alimentando o id do token
                            tabelaLexica[li + 1].blocoli = tabelaLexica[i1].linha + linhaB;
                            //
                            strcpy(tabelaLexica[li + 2].bloco, "#tmp2"); //alimentando o lexema
                            tabelaLexica[li + 2].blocoi = tabelaLexica[i1].id; // alimentando o id do token
                            tabelaLexica[li + 2].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //
                            strcpy(tabelaLexica[li + 3].bloco, tabelaLexica[i1 - 5].lexema); //alimentando o lexema
                            tabelaLexica[li + 3].blocoi = tabelaLexica[i1 - 5].id; // alimentando o id do token
                            tabelaLexica[li + 3].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //
                            strcpy(tabelaLexica[li + 4].bloco, "#tmp1"); //alimentando o lexema
                            tabelaLexica[li + 4].blocoi = tabelaLexica[i1].id; // alimentando o id do token
                            tabelaLexica[li + 4].blocoli = tabelaLexica[i1].linha + linhaB;
                            //fim
                            li = li + 5;
                            //i1 = i1 + 1;
                            linhaB++;
                            aux_op++;
                        }
                        if (aux_op == 6 && (tabelaLexica[i1 - 12].id == 13 || tabelaLexica[i1 - 12].id == 14)) {//caso ache mais que 2 operadores
                            // printf("#tmp1 := #tmp1 %s #tmp2\n", tabelaLexica[i1 - 12].lexema);
                            //começo
                            strcpy(tabelaLexica[li].bloco, "#tmp1"); //alimentando o lexema
                            tabelaLexica[li].blocoi = 36; // alimentando o id do token
                            tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //                    
                            strcpy(tabelaLexica[li + 1].bloco, ":="); //chamando aux_aul para transofmar o numero inteiro em char
                            tabelaLexica[li + 1].blocoi = 32; // alimentando o id do token
                            tabelaLexica[li + 1].blocoli = tabelaLexica[i1].linha + linhaB;
                            //
                            strcpy(tabelaLexica[li + 2].bloco, "#tmp1"); //alimentando o lexema
                            tabelaLexica[li + 2].blocoi = tabelaLexica[i1].id; // alimentando o id do token
                            tabelaLexica[li + 2].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //
                            strcpy(tabelaLexica[li + 3].bloco, tabelaLexica[i1 - 12].lexema); //alimentando o lexema
                            tabelaLexica[li + 3].blocoi = tabelaLexica[i1 - 5].id; // alimentando o id do token
                            tabelaLexica[li + 3].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //
                            strcpy(tabelaLexica[li + 4].bloco, "#tmp2"); //alimentando o lexema
                            tabelaLexica[li + 4].blocoi = tabelaLexica[i1].id; // alimentando o id do token
                            tabelaLexica[li + 4].blocoli = tabelaLexica[i1].linha + linhaB;
                            //fim
                            li = li + 5;
                            //i1 = i1 + 1;
                            linhaB++;
                            aux_op++;
                        }
                    }// fim do while
                    // printf("\nif not #tmp1 goto Linha \n");
                    strcpy(tabelaLexica[li].bloco, "if not #tmp1 goto"); //if not
                    tabelaLexica[li].blocoi = 50; // alimentando o id do token
                    tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                    //         
                    int irepeat = i1;
                    while (tabelaLexica[irepeat].blocoi != 9) {
                        irepeat--;
                    }
                    //printf("linha:%d \n", tabelaLexica[irepeat].linha);
                    strcpy(tabelaLexica[li + 1].bloco, aux_all(tabelaLexica[irepeat].linha)); //chamando aux_aul para transofmar o numero inteiro em char
                    tabelaLexica[li + 1].blocoi = 36; // alimentando o id do token
                    tabelaLexica[li + 1].blocoli = tabelaLexica[i1].linha + linhaB;
                    //
                    li = li + 2;
                    linhaB++;

                }

                // fim repeat 3 enderecos
                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                //começo 2-while 3 enderecos
                if (tabelaLexica[i1].id == 6) {// procuro o while
                    aux_op = 1;
                    i1++; // acrescento para pular o lexema until
                    aux_tmp = "#tmp2";
                    while (tabelaLexica[i1].id != 7) {// vou ate o do//verificar

                        if (tabelaLexica[i1].id == 36 || (tabelaLexica[i1].id >= 17 &&
                                tabelaLexica[i1].id <= 22)) {// algort do tmp
                            if (aux_tmp == "#tmp2") {
                                aux_tmp = "#tmp1";
                            } else {
                                aux_tmp = "#tmp2";
                            }
                            //printf("- %s - e li:%d\n", tabelaLexica[i1].lexema,li);                       
                            if (tabelaLexica[i1].id == 36 && tabelaLexica[i1 + 1].id == 31) {// atribuiçao dos valores
                                // printf("\n %s := ", aux_tmp);
                                //printf(" %s", tabelaLexica[i1 - 2].lexema);
                                //printf(" %s", tabelaLexica[i1 - 1].lexema);
                                //printf(" %s\n", tabelaLexica[i1].lexema);
                                //inicio
                                //verifica o (())
                                //começo
                                if (aux_op > 4) {
                                    strcpy(tabelaLexica[li].bloco, "#tmp3"); //alimentando o lexema
                                    tabelaLexica[li].blocoi = 36; // alimentando o id do token
                                    tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                } else {
                                    strcpy(tabelaLexica[li].bloco, aux_tmp); //alimentando o lexema
                                    tabelaLexica[li].blocoi = 36; // alimentando o id do token
                                    tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB;
                                }//alimentando a linha do lex
                                //                    
                                strcpy(tabelaLexica[li + 1].bloco, ":="); //chamando aux_aul para transofmar o numero inteiro em char
                                tabelaLexica[li + 1].blocoi = 32; // alimentando o id do token
                                tabelaLexica[li + 1].blocoli = tabelaLexica[i1].linha + linhaB;
                                //
                                strcpy(tabelaLexica[li + 2].bloco, tabelaLexica[i1 - 2].lexema); //alimentando o lexema
                                tabelaLexica[li + 2].blocoi = tabelaLexica[i1 - 2].id; // alimentando o id do token
                                tabelaLexica[li + 2].blocoli = tabelaLexica[i1 - 2].linha + linhaB; //alimentando a linha do lex
                                //
                                strcpy(tabelaLexica[li + 3].bloco, tabelaLexica[i1 - 1].lexema); //alimentando o lexema
                                tabelaLexica[li + 3].blocoi = tabelaLexica[i1 - 1].id; // alimentando o id do token
                                tabelaLexica[li + 3].blocoli = tabelaLexica[i1 - 1].linha + linhaB; //alimentando a linha do lex
                                //
                                strcpy(tabelaLexica[li + 4].bloco, tabelaLexica[i1].lexema); //alimentando o lexema
                                tabelaLexica[li + 4].blocoi = tabelaLexica[i1].id; // alimentando o id do token
                                tabelaLexica[li + 4].blocoli = tabelaLexica[i1].linha + linhaB;
                                //fim
                                //printf("OIII: %d e id: %d\n", aux_op, tabelaLexica[i1 - 11].id); // se achar until nao tem mais q 2 operandos//verifica apos acerto do ()
                                li = li + 5;
                                //i1 = i1 + 1;
                                linhaB++;
                            }

                            if (tabelaLexica[i1 + 2].id == 13 || tabelaLexica[i1 + 2].id == 14) {// resgata o operador
                                //printf("\nseparaçao OPPPP %s \n\n", tabelaLexica[i1 + 2].lexema);
                                strcpy(op, tabelaLexica[i1 + 2].lexema);
                                aux_op++;
                            }
                        }
                        i1++;

                        if (tabelaLexica[i1 + 1].id == 7 && aux_op > 1) {
                            // printf("\n #tmp1 := #tmp1 %s #tmp2\n", op);
                            //  printf("\n OKKKKK %d\n", aux_op);
                            //começo
                            strcpy(tabelaLexica[li].bloco, "#tmp1"); //alimentando o lexema
                            tabelaLexica[li].blocoi = 36; // alimentando o id do token
                            tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //                    
                            strcpy(tabelaLexica[li + 1].bloco, ":="); //chamando aux_aul para transofmar o numero inteiro em char
                            tabelaLexica[li + 1].blocoi = 32; // alimentando o id do token
                            tabelaLexica[li + 1].blocoli = tabelaLexica[i1].linha + linhaB;
                            //
                            strcpy(tabelaLexica[li + 2].bloco, "#tmp1"); //alimentando o lexema
                            tabelaLexica[li + 2].blocoi = tabelaLexica[i1].id; // alimentando o id do token
                            tabelaLexica[li + 2].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //
                            strcpy(tabelaLexica[li + 3].bloco, op); //alimentando o lexema
                            tabelaLexica[li + 3].blocoi = 13; // alimentando o id do token
                            tabelaLexica[li + 3].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //
                            if (aux_op > 5) {
                                strcpy(tabelaLexica[li + 4].bloco, "#tmp3"); //alimentando o lexema
                                tabelaLexica[li + 4].blocoi = 36; // alimentando o id do token
                                tabelaLexica[li + 4].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            } else {
                                strcpy(tabelaLexica[li + 4].bloco, "#tmp2"); //alimentando o lexema
                                tabelaLexica[li + 4].blocoi = 36; // alimentando o id do token
                                tabelaLexica[li + 4].blocoli = tabelaLexica[i1].linha + linhaB;
                            }
                            //fim
                            li = li + 5;
                            //i1 = i1 + 1;
                            linhaB++;
                            aux_op++;
                        }
                        //printf("oi: %d\n\n",aux_op);
                        if (aux_op == 3 && (tabelaLexica[i1 - 5].id == 13 || tabelaLexica[i1 - 5].id == 14)) {//caso ache mais que 2 operadores
                            //  printf("\n #tmp2 := #tmp1 %s #tmp2\n", tabelaLexica[i1 - 5].lexema); //verifica o (())
                            //   printf("oi: %d\n\n",aux_op);
                            //começo
                            strcpy(tabelaLexica[li].bloco, "#tmp2"); //alimentando o lexema
                            tabelaLexica[li].blocoi = 36; // alimentando o id do token
                            tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //                    
                            strcpy(tabelaLexica[li + 1].bloco, ":="); //chamando aux_aul para transofmar o numero inteiro em char
                            tabelaLexica[li + 1].blocoi = 32; // alimentando o id do token
                            tabelaLexica[li + 1].blocoli = tabelaLexica[i1].linha + linhaB;
                            //
                            strcpy(tabelaLexica[li + 2].bloco, "#tmp2"); //alimentando o lexema
                            tabelaLexica[li + 2].blocoi = tabelaLexica[i1].id; // alimentando o id do token
                            tabelaLexica[li + 2].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //
                            strcpy(tabelaLexica[li + 3].bloco, tabelaLexica[i1 - 5].lexema); //alimentando o lexema
                            tabelaLexica[li + 3].blocoi = tabelaLexica[i1 - 5].id; // alimentando o id do token
                            tabelaLexica[li + 3].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //
                            strcpy(tabelaLexica[li + 4].bloco, "#tmp1"); //alimentando o lexema
                            tabelaLexica[li + 4].blocoi = tabelaLexica[i1].id; // alimentando o id do token
                            tabelaLexica[li + 4].blocoli = tabelaLexica[i1].linha + linhaB;
                            //fim
                            li = li + 5;
                            //i1 = i1 + 1;
                            linhaB++;
                            aux_op++;
                        }
                        if (aux_op == 5 && (tabelaLexica[i1 - 12].id == 13 || tabelaLexica[i1 - 12].id == 14)) {//caso ache mais que 2 operadores
                            //  printf("#tmp1 := #tmp1 %s #tmp2\n", tabelaLexica[i1 - 12].lexema);
                            //começo
                            strcpy(tabelaLexica[li].bloco, "#tmp1"); //alimentando o lexema
                            tabelaLexica[li].blocoi = 36; // alimentando o id do token
                            tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //                    
                            strcpy(tabelaLexica[li + 1].bloco, ":="); //chamando aux_aul para transofmar o numero inteiro em char
                            tabelaLexica[li + 1].blocoi = 32; // alimentando o id do token
                            tabelaLexica[li + 1].blocoli = tabelaLexica[i1].linha + linhaB;
                            //
                            strcpy(tabelaLexica[li + 2].bloco, "#tmp1"); //alimentando o lexema
                            tabelaLexica[li + 2].blocoi = tabelaLexica[i1].id; // alimentando o id do token
                            tabelaLexica[li + 2].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //
                            strcpy(tabelaLexica[li + 3].bloco, tabelaLexica[i1 - 12].lexema); //alimentando o lexema
                            tabelaLexica[li + 3].blocoi = tabelaLexica[i1 - 5].id; // alimentando o id do token
                            tabelaLexica[li + 3].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //
                            strcpy(tabelaLexica[li + 4].bloco, "#tmp2"); //alimentando o lexema
                            tabelaLexica[li + 4].blocoi = tabelaLexica[i1].id; // alimentando o id do token
                            tabelaLexica[li + 4].blocoli = tabelaLexica[i1].linha + linhaB;
                            //fim
                            li = li + 5;
                            //i1 = i1 + 1;
                            linhaB++;
                            aux_op++;
                        }
                    }// fim do while
                    //  printf("\nif not #tmp1 goto Linha \n");

                    strcpy(tabelaLexica[li].bloco, "if not #tmp1 goto"); //if not
                    tabelaLexica[li].blocoi = 51; // alimentando o id do token
                    tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                    //                    
                    strcpy(tabelaLexica[li + 1].bloco, "00"); //chamando aux_aul para transofmar o numero inteiro em char
                    tabelaLexica[li + 1].blocoi = 36; // alimentando o id do token
                    tabelaLexica[li + 1].blocoli = tabelaLexica[i1].linha + linhaB;
                    //
                    li = li + 3;
                    //i1++;
                    linhaB++;
                }

                // fim 2-while 3 enderecos
                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

                //começo 3-if do 3enderecos
                if (tabelaLexica[i1].id == 3) {// procuro o if
                    aux_op = 1; // auxilia na quantidade de operadores para fazer o algoritmo de 3 enderecos
                    i1++; // acrescento para pular o lexema if
                    aux_tmp = "#tmp2";
                    while (tabelaLexica[i1].id != 4) {// vou ate o then//verificar

                        if (tabelaLexica[i1].id == 36 || (tabelaLexica[i1].id >= 17 &&
                                tabelaLexica[i1].id <= 22)) {// algort do tmp
                            if (aux_tmp == "#tmp2") {
                                aux_tmp = "#tmp1";
                            } else {
                                aux_tmp = "#tmp2";
                            }
                            //printf("- %s - e li:%d\n", tabelaLexica[i1].lexema,li);                       
                            if (tabelaLexica[i1].id == 36 && tabelaLexica[i1 + 1].id == 31) {// atribuiçao dos valores
                                // printf("\n %s := ", aux_tmp);
                                //   printf(" %s", tabelaLexica[i1 - 2].lexema);
                                //   printf(" %s", tabelaLexica[i1 - 1].lexema);
                                //   printf(" %s\n", tabelaLexica[i1].lexema);
                                //inicio
                                //verifica o (())
                                //começo
                                if (aux_op > 4) {
                                    strcpy(tabelaLexica[li].bloco, "#tmp3"); //alimentando o lexema
                                    tabelaLexica[li].blocoi = 36; // alimentando o id do token
                                    tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                                } else {
                                    strcpy(tabelaLexica[li].bloco, aux_tmp); //alimentando o lexema
                                    tabelaLexica[li].blocoi = 36; // alimentando o id do token
                                    tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB;
                                }//alimentando a linha do lex
                                //                    
                                strcpy(tabelaLexica[li + 1].bloco, ":="); //chamando aux_aul para transofmar o numero inteiro em char
                                tabelaLexica[li + 1].blocoi = 32; // alimentando o id do token
                                tabelaLexica[li + 1].blocoli = tabelaLexica[i1].linha + linhaB;
                                //
                                strcpy(tabelaLexica[li + 2].bloco, tabelaLexica[i1 - 2].lexema); //alimentando o lexema
                                tabelaLexica[li + 2].blocoi = tabelaLexica[i1 - 2].id; // alimentando o id do token
                                tabelaLexica[li + 2].blocoli = tabelaLexica[i1 - 2].linha + linhaB; //alimentando a linha do lex
                                //
                                strcpy(tabelaLexica[li + 3].bloco, tabelaLexica[i1 - 1].lexema); //alimentando o lexema
                                tabelaLexica[li + 3].blocoi = tabelaLexica[i1 - 1].id; // alimentando o id do token
                                tabelaLexica[li + 3].blocoli = tabelaLexica[i1 - 1].linha + linhaB; //alimentando a linha do lex
                                //
                                strcpy(tabelaLexica[li + 4].bloco, tabelaLexica[i1].lexema); //alimentando o lexema
                                tabelaLexica[li + 4].blocoi = tabelaLexica[i1].id; // alimentando o id do token
                                tabelaLexica[li + 4].blocoli = tabelaLexica[i1].linha + linhaB;
                                //fim
                                //printf("OIII: %d e id: %d\n", aux_op, tabelaLexica[i1 - 11].id); // se achar until nao tem mais q 2 operandos//verifica apos acerto do ()
                                li = li + 5;
                                //i1 = i1 + 1;
                                linhaB++;
                            }

                            if (tabelaLexica[i1 + 2].id == 13 || tabelaLexica[i1 + 2].id == 14) {// resgata o operador
                                //printf("\nseparaçao OPPPP %s \n\n", tabelaLexica[i1 + 2].lexema);
                                strcpy(op, tabelaLexica[i1 + 2].lexema);
                                aux_op++;
                            }
                        }
                        i1++;

                        if (tabelaLexica[i1 + 1].id == 4 && aux_op > 3) {// verifica
                            // printf("\n #tmp1 := #tmp1 %s #tmp2\n", op);
                            //   printf("\n OKKKKK %d\n", aux_op);
                            //começo
                            strcpy(tabelaLexica[li].bloco, "#tmp1"); //alimentando o lexema
                            tabelaLexica[li].blocoi = 36; // alimentando o id do token
                            tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //                    
                            strcpy(tabelaLexica[li + 1].bloco, ":="); //chamando aux_aul para transofmar o numero inteiro em char
                            tabelaLexica[li + 1].blocoi = 32; // alimentando o id do token
                            tabelaLexica[li + 1].blocoli = tabelaLexica[i1].linha + linhaB;
                            //
                            strcpy(tabelaLexica[li + 2].bloco, "#tmp1"); //alimentando o lexema
                            tabelaLexica[li + 2].blocoi = tabelaLexica[i1].id; // alimentando o id do token
                            tabelaLexica[li + 2].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //
                            strcpy(tabelaLexica[li + 3].bloco, op); //alimentando o lexema
                            tabelaLexica[li + 3].blocoi = 14; // alimentando o id do token
                            tabelaLexica[li + 3].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //
                            if (aux_op > 3) {
                                strcpy(tabelaLexica[li + 4].bloco, "#tmp3"); //alimentando o lexema
                                tabelaLexica[li + 4].blocoi = 36; // alimentando o id do token
                                tabelaLexica[li + 4].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            } else {
                                strcpy(tabelaLexica[li + 4].bloco, "#tmp2"); //alimentando o lexema
                                tabelaLexica[li + 4].blocoi = 36; // alimentando o id do token
                                tabelaLexica[li + 4].blocoli = tabelaLexica[i1].linha + linhaB;
                            }
                            //fim
                            li = li + 5;
                            //i1 = i1 + 1;
                            linhaB++;
                            aux_op++;
                        }
                        //printf("oi: %d\n\n",aux_op);
                        if (aux_op == 3 && (tabelaLexica[i1 - 5].id == 13 || tabelaLexica[i1 - 5].id == 14)) {//caso ache mais que 2 operadores
                            //  printf("\n #tmp2 := #tmp1 %s #tmp2\n", tabelaLexica[i1 - 5].lexema); //verifica o (())
                            //   printf("oi: %d\n\n",aux_op);
                            //começo
                            strcpy(tabelaLexica[li].bloco, "#tmp2"); //alimentando o lexema
                            tabelaLexica[li].blocoi = 36; // alimentando o id do token
                            tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //                    
                            strcpy(tabelaLexica[li + 1].bloco, ":="); //chamando aux_aul para transofmar o numero inteiro em char
                            tabelaLexica[li + 1].blocoi = 32; // alimentando o id do token
                            tabelaLexica[li + 1].blocoli = tabelaLexica[i1].linha + linhaB;
                            //
                            strcpy(tabelaLexica[li + 2].bloco, "#tmp2"); //alimentando o lexema
                            tabelaLexica[li + 2].blocoi = tabelaLexica[i1].id; // alimentando o id do token
                            tabelaLexica[li + 2].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //
                            strcpy(tabelaLexica[li + 3].bloco, tabelaLexica[i1 - 5].lexema); //alimentando o lexema
                            tabelaLexica[li + 3].blocoi = tabelaLexica[i1 - 5].id; // alimentando o id do token
                            tabelaLexica[li + 3].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //
                            strcpy(tabelaLexica[li + 4].bloco, "#tmp1"); //alimentando o lexema
                            tabelaLexica[li + 4].blocoi = tabelaLexica[i1].id; // alimentando o id do token
                            tabelaLexica[li + 4].blocoli = tabelaLexica[i1].linha + linhaB;
                            //fim
                            li = li + 5;
                            //i1 = i1 + 1;
                            linhaB++;
                            aux_op++;
                        }
                        if (aux_op > 5 && (tabelaLexica[i1 - 12].id == 13 || tabelaLexica[i1 - 12].id == 14)) {//caso ache mais que 2 operadores
                            //printf("=====#tmp1 := #tmp1 %s #tmp2\n", tabelaLexica[i1 - 12].lexema);
                            //começo
                            strcpy(tabelaLexica[li].bloco, "#tmp1"); //alimentando o lexema
                            tabelaLexica[li].blocoi = 36; // alimentando o id do token
                            tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //                    
                            strcpy(tabelaLexica[li + 1].bloco, ":="); //chamando aux_aul para transofmar o numero inteiro em char
                            tabelaLexica[li + 1].blocoi = 32; // alimentando o id do token
                            tabelaLexica[li + 1].blocoli = tabelaLexica[i1].linha + linhaB;
                            //
                            strcpy(tabelaLexica[li + 2].bloco, "#tmp1"); //alimentando o lexema
                            tabelaLexica[li + 2].blocoi = tabelaLexica[i1].id; // alimentando o id do token
                            tabelaLexica[li + 2].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //
                            strcpy(tabelaLexica[li + 3].bloco, tabelaLexica[i1 - 12].lexema); //alimentando o lexema
                            tabelaLexica[li + 3].blocoi = tabelaLexica[i1 - 12].id; // alimentando o id do token
                            tabelaLexica[li + 3].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                            //
                            strcpy(tabelaLexica[li + 4].bloco, "#tmp2"); //alimentando o lexema
                            tabelaLexica[li + 4].blocoi = tabelaLexica[i1].id; // alimentando o id do token
                            tabelaLexica[li + 4].blocoli = tabelaLexica[i1].linha + linhaB;
                            //fim
                            li = li + 5;
                            //i1 = i1 + 1;
                            linhaB++;
                            aux_op++;
                        }
                    }// fim do while
                    //  printf("\nif not #tmp1 goto Linha \n");

                    strcpy(tabelaLexica[li].bloco, "if not #tmp1 goto"); //if not
                    tabelaLexica[li].blocoi = 50; // alimentando o id do token
                    tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                    //                       
                    strcpy(tabelaLexica[li + 1].bloco, "00"); //chamando aux_aul para transofmar o numero inteiro em char
                    tabelaLexica[li + 1].blocoi = 36; // alimentando o id do token
                    tabelaLexica[li + 1].blocoli = tabelaLexica[i1].linha + linhaB;
                    //
                    li = li + 3;
                    //i1++;
                    linhaB++;
                    aux_tmp = "\0";
                }


                // fim 3-if do 3 enedrecos  
                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


                //processo de transferencia para o arquivo, parte 5
                if (tabelaLexica[i1].id != 29 && tabelaLexica[i1].id != 4 && tabelaLexica[i1].id != 7) {// transferencia dos lexemas e id . bem como seu identificador e linha para ir para 6 parte           
                    if (tabelaLexica[i1].id == 34) {// caso chegue no final do programa, atualiza copm o FIM
                        strcpy(tabelaLexica[li].bloco, "FIM."); //alimentando o lexema
                        tabelaLexica[li].blocoi = tabelaLexica[i1].id; // alimentando o id do token
                        tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                        li++;
                    } else {
                        strcpy(tabelaLexica[li].bloco, tabelaLexica[i1].lexema); //alimentando o lexema
                        tabelaLexica[li].blocoi = tabelaLexica[i1].id; // alimentando o id do token
                        tabelaLexica[li].blocoli = tabelaLexica[i1].linha + linhaB; //alimentando a linha do lex
                        li++;
                    }
                }
            }
        }
        /*
         etapa onde sera escrito a parte 2 no arquivo_3endderecos.txt () no txt. 
         */
        FILE *codInter_arq;
        int r;
        codInter_arq = fopen("arquivo_3enderecos.txt", "w+");
        linhaB = 0;
        //Testando a abertura do arquivo
        if (codInter_arq == NULL) {
            printf("Erro ao tentar abrir o arquivo!");
            exit(1);
        }
        //r = fputs("FIM", codInter_arq); // FIm quando estiver no end.
        for (int i2 = 1; i2 < 1100; i2++) {// transferencia da 4 e 5 parte do trabalho para o arquivo

            r = fputs(tabelaLexica[i2].bloco, codInter_arq);
            r = fputs(" ", codInter_arq);
            if (tabelaLexica[i2].blocoli != tabelaLexica[i2 + 1].blocoli) {
                r = fputs("\n", codInter_arq);
            }
            // printf("BLOCOS: %s lin: %d \n",tabelaLexica[i2].bloco,tabelaLexica[i2].blocoli);
        }//fim do for
        /*
                                         ultima parte sendo inserida no .txt
         */
        r = fputs("\n", codInter_arq);
        r = fputs("============= Gerador de Codigo Final ==============", codInter_arq);
        fputs("\n\n", codInter_arq);
        //--------------------começo do for
        for (int i3 = 1; i3 < 990; i3++) {// transferencia da 4 e 5 parte do trabalho para o arquivo
            if (tabelaLexica[i3].blocoi == 55) {
                //printf(" %s ", tabelaLexica[i3].bloco);
                //printf(" %s \n", tabelaLexica[i3 + 1].bloco);
                fputs(tabelaLexica[i3].bloco, codInter_arq);
                fputs(" ", codInter_arq);
                fputs(tabelaLexica[i3 + 1].bloco, codInter_arq);
                fputs("\n", codInter_arq);
                // printf(" %s ", tabelaLexica[i3 + 2].bloco);
                //  printf(" %s ", tabelaLexica[i3 + 3].bloco);
                //  printf(" %s\n", tabelaLexica[i3 + 4].bloco);                       
            }
            if (tabelaLexica[i3].blocoi == 16 || tabelaLexica[i3].blocoi == 10 || tabelaLexica[i3].blocoi == 11 ||
                    tabelaLexica[i3].blocoi == 15 /*||  tabelaLexica[i3].blocoi == 9 ||  tabelaLexica[i3].blocoi == 5*/) {
                // printf("Linha : %d bloco: %s\n", tabelaLexica[i3].blocoli, tabelaLexica[i3].bloco); 
                linhaCOD = tabelaLexica[i3].blocoli; // elmiino a linha onde tem as declaraçoes 
            }
            if (tabelaLexica[i3].blocoli != linhaCOD) {
                if (tabelaLexica[i3].blocoi == 36 && tabelaLexica[i3 + 1].blocoi == 32 &&
                        (tabelaLexica[i3 + 3].blocoi >= 13 && tabelaLexica[i3 + 3].blocoi <= 14) ||
                        (tabelaLexica[i3 + 3].blocoi >= 23 && tabelaLexica[i3 + 3].blocoi <= 26)) {
                    if (strcmp(tabelaLexica[i3].bloco, tabelaLexica[i3 + 2].bloco) == 0) {// varaiveis que so acrescetam. ex: x := x+1
                        //printf(" =%s ", tabelaLexica[i3].bloco);
                        //  printf(" %s ", tabelaLexica[i3 + 1].bloco);
                        // printf(" %s ", tabelaLexica[i3 + 2].bloco);
                        //  printf(" %s ", tabelaLexica[i3 + 3].bloco);
                        //  printf(" %s\n", tabelaLexica[i3 + 4].bloco);                       
                        //começo
                        if (tabelaLexica[i3 + 3].blocoi == 23) {
                            fputs("ADD", codInter_arq);
                        } else if (tabelaLexica[i3 + 3].blocoi == 24) {
                            fputs("SUB", codInter_arq);
                        } else if (tabelaLexica[i3 + 3].blocoi == 25) {
                            fputs("MUL", codInter_arq);
                        } else if (tabelaLexica[i3 + 3].blocoi == 26) {
                            fputs("DIV", codInter_arq);
                            //printf("aqui DIV\n");
                        } else if (strcmp(tabelaLexica[i3 + 3].bloco, "and") == 0) {
                            fputs("AND", codInter_arq);
                            //  printf("aqui\n");
                        } else if (strcmp(tabelaLexica[i3 + 3].bloco, "or") == 0) {
                            fputs("OR", codInter_arq);
                        }
                        //fputs("ADD", codInter_arq);
                        fputs(" ", codInter_arq);
                        fputs(tabelaLexica[i3 + 4].bloco, codInter_arq);
                        fputs(", ", codInter_arq);
                        fputs(tabelaLexica[i3].bloco, codInter_arq);
                        fputs("\n", codInter_arq);
                        //fim
                    }
                }

                // começo transformar codigo 3 endereços em final
                if (tabelaLexica[i3].blocoi == 32 || (tabelaLexica[i3].blocoi >= 17 &&
                        tabelaLexica[i3].blocoi <= 26) || tabelaLexica[i3].blocoi > 35) {// pego todos os operandos
                    //printf("ID : %d bloco: %s\n", tabelaLexica[i3].blocoi, tabelaLexica[i3].bloco);
                    //printf("Linha : %d\n", tabelaLexica[i3].blocoli); 
                    //printf("%s ", tabelaLexica[i3].bloco);
                    if (tabelaLexica[i3].blocoi == 36 && tabelaLexica[i3 + 1].blocoi == 32 &&
                            tabelaLexica[i3].blocoi == 36 && (tabelaLexica[i3 + 2].blocoli != tabelaLexica[i3 + 3].blocoli)) {// depois do primeiro id nao tiver nada alem do ; ex: x := 10
                        //  printf(" %s ", tabelaLexica[i3].bloco);
                        //  printf(" %s ", tabelaLexica[i3 + 1].bloco);
                        // printf(" %s \n", tabelaLexica[i3 + 2].bloco);
                        //printf("linha 1: %d e linha 2: %d\n",tabelaLexica[i3 + 2].blocoli, tabelaLexica[i3 + 3].blocoli);
                        fputs("COPY", codInter_arq);
                        fputs(" ", codInter_arq);
                        fputs(tabelaLexica[i3 + 2].bloco, codInter_arq);
                        fputs(", ", codInter_arq);
                        fputs(tabelaLexica[i3].bloco, codInter_arq);
                        fputs("\n", codInter_arq);
                    }
                    if (tabelaLexica[i3].blocoi == 36 && tabelaLexica[i3 + 1].blocoi == 32 &&
                            (tabelaLexica[i3 + 3].blocoi >= 23 && tabelaLexica[i3 + 3].blocoi <= 26) &&
                            !(strcmp(tabelaLexica[i3].bloco, tabelaLexica[i3 + 2].bloco) == 0)) {//pego alguns operando, tipo: i1 := 2+3, = +, -, * , /
                        //printf("%s ", tabelaLexica[i3].bloco);
                        // printf(" %s ", tabelaLexica[i3 + 1].bloco);
                        //printf(" %s ", tabelaLexica[i3 + 2].bloco);
                        //printf(" %s ", tabelaLexica[i3 + 3].bloco);
                        //printf(" %s\n", tabelaLexica[i3 + 4].bloco);
                        fputs("COPY", codInter_arq);
                        fputs(" ", codInter_arq);
                        fputs(tabelaLexica[i3 + 4].bloco, codInter_arq);
                        fputs(", ", codInter_arq);
                        fputs(tabelaLexica[i3].bloco, codInter_arq);
                        fputs("\n", codInter_arq);
                        // espaço
                        if (tabelaLexica[i3 + 3].blocoi == 23) {
                            fputs("ADD", codInter_arq);
                        } else if (tabelaLexica[i3 + 3].blocoi == 24) {
                            fputs("SUB", codInter_arq);
                        } else if (tabelaLexica[i3 + 3].blocoi == 25) {
                            fputs("MUL", codInter_arq);
                        } else if (tabelaLexica[i3 + 3].blocoi == 26) {
                            fputs("DIV", codInter_arq);
                        }
                        //fputs("ADD", codInter_arq);
                        fputs(" ", codInter_arq);
                        fputs(tabelaLexica[i3 + 2].bloco, codInter_arq);
                        fputs(", ", codInter_arq);
                        fputs(tabelaLexica[i3].bloco, codInter_arq);
                        fputs("\n", codInter_arq);
                    }
                    if (tabelaLexica[i3].blocoi == 36 && tabelaLexica[i3 + 1].blocoi == 32 &&
                            (tabelaLexica[i3 + 3].blocoi >= 17 && tabelaLexica[i3 + 3].blocoi <= 22)) {// pego os calculos que se relacionam com o <, > , <> etc. ex: t1 := 5>3
                        //printf(" %s ", tabelaLexica[i3].bloco);
                        //printf(" %s ", tabelaLexica[i3+1].bloco);
                        //printf(" %s ", tabelaLexica[i3+2].bloco);
                        //printf(" %s ", tabelaLexica[i3+3].bloco);
                        //printf(" %s \n", tabelaLexica[i3+4].bloco);
                        //printf("linha 1: %d e linha 2: %d\n",tabelaLexica[i3 + 2].blocoli, tabelaLexica[i3 + 3].blocoli);
                        fputs("COPY", codInter_arq);
                        fputs(" ", codInter_arq);
                        fputs(tabelaLexica[i3 + 4].bloco, codInter_arq);
                        fputs(", ", codInter_arq);
                        fputs(tabelaLexica[i3].bloco, codInter_arq);
                        fputs("\n", codInter_arq);
                        // espaço
                        if (strcmp(tabelaLexica[i3 + 3].bloco, ">") == 0) {
                            fputs(">", codInter_arq);
                        }
                        if (strcmp(tabelaLexica[i3 + 3].bloco, "<") == 0) {
                            fputs("<", codInter_arq);
                        }
                        if (strcmp(tabelaLexica[i3 + 3].bloco, ">=") == 0) {
                            fputs(">=", codInter_arq);
                        }
                        if (strcmp(tabelaLexica[i3 + 3].bloco, "=<") == 0) {
                            fputs("<=", codInter_arq);
                        }
                        if (strcmp(tabelaLexica[i3 + 3].bloco, "<>") == 0) {
                            fputs("<>", codInter_arq);
                        }
                        if (strcmp(tabelaLexica[i3 + 3].bloco, "=") == 0) {
                            fputs("=", codInter_arq);
                        }
                        fputs(" ", codInter_arq);
                        fputs(tabelaLexica[i3 + 2].bloco, codInter_arq);
                        fputs(", ", codInter_arq);
                        fputs(tabelaLexica[i3].bloco, codInter_arq);
                        fputs("\n", codInter_arq);
                    }
                    if (tabelaLexica[i3].blocoi == 50 || tabelaLexica[i3].blocoi == 51) {// adiciono o if not goto
                        //printf(" %s %s \n", tabelaLexica[i3].bloco, tabelaLexica[i3 + 1].bloco);
                        fputs("COPY not tmp1", codInter_arq);
                        fputs("\n", codInter_arq);
                        fputs("CMP tmp1", codInter_arq);
                        fputs("\n", codInter_arq);
                        fputs("JNZ ", codInter_arq);
                        fputs(tabelaLexica[i3 + 1].bloco, codInter_arq);
                        fputs("\n", codInter_arq);
                    }

                }
                //  r = fputs(tabelaLexica[i3].bloco, codInter_arq);
                // r = fputs(" ", codInter_arq);
                // FIM transformar codigo 3 endereços em final
                //printf("ID : %d bloco: %s\n", tabelaLexica[i3].blocoi, tabelaLexica[i3].bloco); 
                if (tabelaLexica[i3].blocoli != tabelaLexica[i3 + 1].blocoli) {
                    // r = fputs("\n", codInter_arq);
                }
                // printf("BLOCOS: %s lin: %d \n",tabelaLexica[i2].bloco,tabelaLexica[i2].blocoli);
            }//fim do for
            //printf("b: %s\n",tabelaLexica[i3].bloco);
        }
        //Verificando se os dados foram gravados com sucesso
        if (r == EOF) {
            printf("Erro ao tentar gravar os dados! \n");
        }

        //fechando o arquivo
        fclose(codInter_arq);
        // fim da segunda perta do trabalho
        
    }
    int num;
    // scanf(" Aperte 0 : %d", num);
    system("pause");
    return (EXIT_SUCCESS);
  
}

