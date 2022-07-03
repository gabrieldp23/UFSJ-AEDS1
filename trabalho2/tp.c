#include <stdio.h> 
#include <string.h>
#include "tp.h"

#define CADASTRO_INCOMPLETO "ERRO - Cadastro Incompleto"

int onibusForamCadastrados (dados onibus[]);
int lugaresForamCadastrados (dados onibus[]);
void consertaString (char *nome);
char *obterNome ();


void cadastrarOnibus (dados onibus[]) {
    printMensagem("CADASTRAR VEICULOS");
    for (int i = 0; i < QUANTIDADE_ONIBUS; i++) {
        int numero, repetido;
        do {
            repetido = 0;
            printf("Numero do onibus %d: ", i+1);
            scanf("%d", &numero);
            for (int j = 0; j < QUANTIDADE_ONIBUS; j++) {
                if (onibus[j].id == numero) {
                    printMensagem("ERRO - Onibus ja cadastrado");
                    repetido = 1;
                }
            }
        } while (repetido == 1);
        onibus[i].id = numero;
    }
    printMensagem("VEICULOS CADASTRADOS COM SUCESSO");
}

void cadastrarLugares (dados onibus[]) {
    if (!onibusForamCadastrados(onibus)) {
        printMensagem(CADASTRO_INCOMPLETO);
        return;
    }

    printMensagem("CADASTRAR QUANTIDADE DE ASSENTOS");
    for (int i = 0; i < QUANTIDADE_ONIBUS; i++) {
        int lugares = 0;
        do {
            if (lugares != 0) {
                printMensagem("ERRO - Quantidade Invalida");
            }
            printf("Quantidade de lugares do onibus %d: ", onibus[i].id);
            scanf("%d", &lugares);
        } while (lugares < 0 || lugares > QUANTIDADE_LUGARES_MAX);
        onibus[i].quantidadeDisponivel = lugares;
        onibus[i].quantidadeReservas = 0;
    }
    printMensagem("ASSENTOS CADASTRADOS COM SUCESSO");
}

void reservarLugar (dados onibus[]) {
    if (!onibusForamCadastrados(onibus)|| !lugaresForamCadastrados(onibus)) {
        printMensagem(CADASTRO_INCOMPLETO);
        return;
    }

    printMensagem("RESERVAR PASSAGEM");

    int numero, erro = 1;
    printf("Numero do onibus: ");
    scanf("%d", &numero);
    for (int i = 0; i < QUANTIDADE_ONIBUS; i++) {
        if (onibus[i].id == numero) {
            erro = 2;
            if (onibus[i].quantidadeDisponivel > 0) {
                erro = 0;
                int indicePassageiro = onibus[i].quantidadeReservas;
                strncpy(onibus[i].passageiros[indicePassageiro], obterNome(), STRING_MAX);

                onibus[i].quantidadeDisponivel--;
                onibus[i].quantidadeReservas++;
            }
        }
    }

    switch (erro) {
        case 1:
            printMensagem("ERRO - Onibus nao encontrado");
            return;
        case 2:
            printMensagem("ERRO - Onibus lotado");
            return;
        default:
            printMensagem("RESERVA CONFIRMADA COM SUCESSO");
            break;
    }
}

void consultarOnibus (dados onibus[]) {
    if (!onibusForamCadastrados(onibus)|| !lugaresForamCadastrados(onibus)) {
        printMensagem(CADASTRO_INCOMPLETO);
        return;
    }

    printMensagem("CONSULTAR RESERVAS");

    int numero, encontrado = 0;
    printf("Numero do onibus: ");
    scanf("%d", &numero);
    for (int i = 0; i < QUANTIDADE_ONIBUS; i++) {
        if (onibus[i].id == numero) {
            encontrado = 1;

            //tabela de dados            
            for (int i = 0;  i < STRING_MAX+9;  i++, printf("%c", '_'));
            printf("\n| %s | %-*s |\n", "NR", STRING_MAX, "NOME");
            for (int reserva = 0; reserva < onibus[i].quantidadeReservas; reserva++) {
                printf("| %2d | %-*s |\n", reserva, STRING_MAX, onibus[i].passageiros[reserva]);
            }
            printf("|");
            for (int i = 0;  i < STRING_MAX+7;  i++, printf("%c", '_'));
            printf("|\n");
        }
    }

    if (!encontrado) {
        printMensagem("ERRO - Onibus nao encontrado");
        return;
    }
}

void consultarPassageiro (dados onibus[]) {
    if (!onibusForamCadastrados(onibus)|| !lugaresForamCadastrados(onibus)) {
        printMensagem(CADASTRO_INCOMPLETO);
        return;
    }

    printMensagem("CONSULTAR PASSAGEIRO");
    char *passageiro = obterNome();

    //tabela de dados
    for (int i = 0;  i < 23;  i++, printf("%c", '_'));
    printf("\n| %9s | %7s |\n", "ONIBUS", "RESERVA");
    for (int i = 0; i < QUANTIDADE_ONIBUS; i++) {
        for (int j = 0; j < onibus[i].quantidadeReservas; j++) {
            if (strcmp(onibus[i].passageiros[j], passageiro) == 0) {
                printf("| %9d | %7d |\n", onibus[i].id, j+1);
            }
        }
    }
    printf("|");
    for (int i = 0;  i < 21;  i++, printf("%c", '_'));
    printf("|\n");
}

void printMensagem (char *mensagem) {
    printf("<---- %s ---->\n", mensagem);
}

int onibusForamCadastrados (dados onibus[]) {
    return onibus[0].id != -1;
}

int lugaresForamCadastrados (dados onibus[]) {
    return onibus[0].quantidadeReservas != -1;
}

void consertaString (char *nome) {
    int tamanho = strlen(nome);
    if (nome[tamanho-1] == '\n') nome[tamanho-1] = '\0';
    nome[STRING_MAX] = '\0';
}

char *obterNome () {
    static char nome[STRING_MAX+1];
    printf("Nome do passageiro (max %d caracteres): ", STRING_MAX);
    fflush(stdin); setbuf(stdin, NULL);
    fgets(nome, STRING_MAX+2, stdin);
    consertaString(nome);
    return nome;
}