#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_TOKENS 200

typedef struct
{
    char tipo[20];  // Tipo do token (PAL_RES, SMB_SEM, etc.)
    char valor[50]; // Valor do token
    int linha;      // Linha do token
    int coluna;     // Coluna do token
} Token;

Token tokens[MAX_TOKENS]; // Array de tokens
int token_count = 0;
int token_atual = 0;

// programa e bloco
void programa(); // Gustavo
void bloco(); // Gustavo

// declarações
void parteDeDeclaracoesDeVariaveis(); // Gustavo
void declaracaoDeVariaveis(); // Gustavo
void listaDeIdentificadores(); // a fazer
void tipo(); // Pedro

// comandos
void comandoComposto(); // nunes
void comando(); // nunes
void atribuicao(); // nunes
void comando_condicional(); // nunes
void comando_repetitivo(); // a fazer

// expressões
void expressao(); // Pedro
void relacao(); // Guilherme
void expressao_simples(); // Pedro
void termo(); // Guilherme
void fator(); // Guilherme
void variavel(); // Guilherme


// funções auxiliares
void ler_tokens(const char *nome_arquivo);
void proximo_token();

void proximo_token() {
    if (token_count > token_atual) {
        token_count++;
    }
}

void comandoComposto() {
      if (token_count > token_atual && !strcmp(tokens[token_atual].valor, "begin")) {
        proximo_token();
        comando();

        while (token_count > token_atual && !strcmp(tokens[token_atual].tipo, "SMB_SEM")) {
            proximo_token();
            comando();
        }

        if (token_count > token_atual && !strcmp(tokens[token_atual].valor, "end")) {
            proximo_token();
        } else {
            printf("Erro: esperado 'end'\n");
        }
    } else {
        printf("Erro: esperado 'begin'\n");
    }
}
}

void comando() {
    if (!strcmp(tokens[token_atual].tipo, "ID")) {
        atribuicao();
    } else if (!strcmp(tokens[token_atual].valor, "begin")) {
        comandoComposto();
    } else if (!strcmp(tokens[token_atual].valor, "if")) {
        comando_condicional();
    } else if (!strcmp(tokens[token_atual].valor, "while")) {
        comando_repetitivo();
    } else {
        printf("Erro: comando inválido\n");
    }
}

void atribuicao(){
	variavel();
    if (token_count > token_atual && !strcmp(tokens[token_atual].tipo, "OP_ASS")) {
        proximo_token();
        expressao();
    } else {
        printf("Erro: operador ':=' esperado\n");
    }
}
}

void comando_condicional() {
    // a fazer
}

void comando_repetitivo() {
    // a fazer
}

void expressao() {
    expressao_simples();

    if (token_count > token_atual && (!strcmp(tokens[token_atual].tipo, "OP_GE") || !strcmp(tokens[token_atual].tipo, "OP_NE") || !strcmp(tokens[token_atual].tipo, "OP_LE") || !strcmp(tokens[token_atual].tipo, "OP_GT") || !strcmp(tokens[token_atual].tipo, "OP_ASS") || !strcmp(tokens[token_atual].tipo, "OP_LT"))) {
        relacao();
        expressao_simples();
    } 
    else if (token_count > token_atual && strcmp(tokens[token_atual].tipo, "SMB_SEM") != 0) {
        printf("Erro: operador relacional ou fim de expressão esperado\n");
    }
}

void expressao_simples() {
    if (token_count > token_atual && (!strcmp(tokens[token_atual].tipo, "OP_AD") || !strcmp(tokens[token_atual].tipo, "OP_MIN"))) {
        proximo_token();
    }
    termo();

    while (token_count > token_atual && (!strcmp(tokens[token_atual].tipo, "OP_AD") || !strcmp(tokens[token_atual].tipo, "OP_MIN"))) {
        proximo_token();
        termo();
    }

    if (token_count > token_atual && strcmp(tokens[token_atual].tipo, "SMB_SEM") != 0) {
        printf("Erro: operador '+' ou '-' esperado \n");
    }
} 


void tipo()
{
    if (token_count > token_atual && 
        (!strcmp(tokens[token_atual].valor, "integer") || !strcmp(tokens[token_atual].valor, "real") || !strcmp(tokens[token_atual].valor, "boolean"))) {
        proximo_token();
    } 
    else {
        printf("Erro: tipo esperado (integer, real ou boolean)\n");
    }

}

void listaDeIdentificadores()
{
    // a fazer
}

void declaracaoDeVariaveis()
{
    listaDeIdentificadores();
    if (token_count > token_atual && !strcmp(tokens[token_atual].tipo, "OP_DP,"))
    {
        token_atual++;
        tipo();
    }
    else
    {
        printf("erro-3-1\n");
    }
}

int variaveis = 0;

void parteDeDeclaracoesDeVariaveis()
{
    if (token_count > token_atual && !strcmp(tokens[token_atual].tipo, "PAL_RES,") && !strcmp(tokens[token_atual].valor, "\"var\","))
    {
        token_atual++;
        declaracaoDeVariaveis();
        if (token_count > token_atual && !strcmp(tokens[token_atual].tipo, "SMB_SEM,"))
        {
            token_atual++;
        }
        else
        {
            printf("erro-2-1\n");
        }
        while (!strcmp(tokens[token_atual].tipo, "ID"))
        {
            declaracaoDeVariaveis();
            if (token_count > token_atual && !strcmp(tokens[token_atual].tipo, "SMB_SEM"))
            {
                token_atual++;
            }
            else
            {
                printf("erro-2-1\n");
            }
        }

        variaveis = 1;
        parteDeDeclaracoesDeVariaveis();
    }
    else if (!variaveis)
    {
        printf("erro-2-2\n");
    }
}

void bloco()
{
    parteDeDeclaracoesDeVariaveis();
    comandoComposto();
}

void programa()
{
    if (token_count > token_atual && !strcmp(tokens[token_atual].tipo, "PAL_RES,") && !strcmp(tokens[token_atual].valor, "\"program\","))
    {
        token_atual++;
        if (token_count > token_atual && !strcmp(tokens[token_atual].tipo, "ID,"))
        {
            token_atual++;
            if (token_count > token_atual && !strcmp(tokens[token_atual].tipo, "SMB_SEM,"))
            {
                token_atual++;
                bloco();
                if (token_count > token_atual && !strcmp(tokens[token_atual].tipo, "SMB_END,"))
                {
                    token_atual++;
                    printf("sucesso!!!!!!!!!!");
                }
                else
                {
                    printf("erro-1-1\n");
                }
            }
            else
            {
                printf("erro-1-2\n");
            }
        }
        else
        {
            printf("erro-1-3\n");
        }
    }
    else
    {
        printf("erro-1-4\n");
    }
}

void relacao() {
    // verifica se o token é um dos aceitos
    if (!strcmp(tokens[token_atual].tipo, "OP_GE,") || !strcmp(tokens[token_atual].tipo, "OP_NE,") || !strcmp(tokens[token_atual].tipo, "OP_LE,") || !strcmp(tokens[token_atual].tipo, "OP_GT,") || !strcmp(tokens[token_atual].tipo, "OP_ASS,") || !strcmp(tokens[token_atual].tipo, "OP_LT,")) {
        // o token é lido
        proximo_token();
    }
    else {
        // mensagem de erro caso o token não seja um dos aceitos
        printf("Erro: relacao esperada");
    }
}

void termo() {
    fator();
    // verifica se o token é um dos aceitos
    if (!strcmp(tokens[token_atual].tipo, "OP_MUL,") || !strcmp(tokens[token_atual].tipo, "OP_DIV,")) {
        // o token é lido
        proximo_token();
        fator();
    }
    else {
        // mensagem de erro caso o token não seja um dos aceitos
        printf("Erro: operador (*|/) esperado!"); 
    }
}

void fator() {
    // verifica se o token é um ID
    if (!strcmp(tokens[token_atual].tipo, "ID,")) {
        // o ID é lido
        variavel();
    }
    // verifica se o token é um numero
    else if (!strcmp(tokens[token_atual].tipo, "NUM_INT,") || !strcmp(tokens[token_atual].tipo, "NUM_FLT,")) {
        proximo_token();
    } // a fazer expressao()
    else {
        printf("Erro: Fator esperado!");
    }
}

void variavel() {
     // verifica se o token é um ID
    if (!strcmp(tokens[token_atual].tipo, "ID,")) {
         // o token é lido
        proximo_token();
    }
    else {
         // erro caso o token não seja um ID
        printf("Erro: ID esperado");
    }
}


// Funcao para ler tokens de um arquivo
void ler_tokens(const char *nome_arquivo)
{
    FILE *file = fopen(nome_arquivo, "r");
    if (!file)
    {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "<%[^ ] %[^ ] %d, %d>%*c",
                  tokens[token_count].tipo,
                  tokens[token_count].valor,
                  &tokens[token_count].linha,
                  &tokens[token_count].coluna) != EOF)
    {
        token_count++;
        // printf("%d ", token_count);
        if (token_count >= MAX_TOKENS)
        {
            printf("Limite de tokens atingido.\n");
            break;
        }
    }
    fclose(file);
}

// Funcao de analise sintatica
// void analise_sintatica()
// {
//     if (token_count > 0 && strcmp(tokens[0].tipo, "PAL_RES") == 0 && strcmp(tokens[0].valor, "program") == 0)
//     {
//         printf("Inicio do programa detectado.\n");

//         // Verifique o proximo token
//         if (token_count > 1 && strcmp(tokens[1].tipo, "SMB_SEM") == 0)
//         {
//             printf("Ponto e virgula apos 'program' encontrado.\n");

//             // Continue com mais verificacoes...
//             if (token_count > 2 && strcmp(tokens[2].tipo, "PAL_RES") == 0 && strcmp(tokens[2].valor, "var") == 0)
//             {
//                 printf("Declaracao de variaveis encontrada.\n");

//                 // Verifique o proximo token, e assim por diante...
//                 // Continue expandindo essa logica conforme sua gramatica.
//             }
//             else
//             {
//                 printf("Erro: Esperado 'var' apos ';'.\n");
//             }
//         }
//         else
//         {
//             printf("Erro: Esperado ';' apos 'program'.\n");
//         }
//     }
//     else
//     {
//         printf("Erro: Esperado 'program' no inicio.\n");
//     }
// }

// Funcao principal
int main()
{
    setlocale(LC_ALL, "Portuguese");
    // ler_tokens("meudeus.txt"); // Nome do arquivo com os tokens
    ler_tokens("saida.lex"); // Nome do arquivo com os tokens
    // analise_sintatica();
    programa();

    // Exibir os tokens lidos para verificar
    // int i;
    // for (i = 0; i < token_count; i++)
    // {
    //     printf("Token: Tipo=%s, Valor=%s, Linha=%d, Coluna=%d\n",
    //            tokens[i].tipo, tokens[i].valor, tokens[i].linha, tokens[i].coluna);
    // }

    return 0;
}
