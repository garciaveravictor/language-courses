#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define SUMA 0
#define RESTA 1
#define MULTIPLICACION 2
#define DIVISION 3
#define NUMERO_JUGADAS 10

/*------------PROTOTIPOS--------------*/
/*  
        Funcion que crea numeros aleatorios
        Genera numeros entre 0 y 10     
    */
int numero_aleatorio();

/*  
        Funcion que crea numeros aleatorios para decidir los operadores
        Devuelve numeros entre 0 y 3
    */
int operador_aleatorio();
/*
        Funcion que se encarga de manejar el tiempo 
        */
void time_controller(char codigo_jugada);

/*-------------MAIN--------------------*/
pid_t pid;
int temporizador; /*      Variable global boolean     */

int main(int argc, char const *argv[])
{
    srand(time(NULL)); /*Cambia la semilla*/
    int jugadas, operando1, operando2, operador, resultado;
    int puntuacion_total = 0;
    int puntuacion_temporal = 10;

    printf("\tARIT GAME");

    /* Código perteneciente al proceso padre */
    for (jugadas = 0; jugadas < NUMERO_JUGADAS; jugadas++)
    {
        operando1 = numero_aleatorio();
        operando2 = numero_aleatorio();
        operador = operador_aleatorio();

        switch (operador)
        {
        case SUMA:
            temporizador = 0;
            time_controller("5");

            do
            {
                print("Jugada numero %d: ", jugadas + 1);
                print("%d + %d = ", operando1, operando2);
                scanf("%d", &resultado);

                if (resultado != operando1 + operando2)
                {
                    printf("Resultado incorrecto! Vuelva a intentarlo");
                    puntuacion_temporal--;
                }
            } while (resultado != operando1 + operando2 && temporizador == 0);

            if (temporizador == 0)
            {
                printf("Resultado correcto");
                puntuacion_total += puntuacion_temporal;
            }

            break;

        case RESTA:
            temporizador = 0;
            time_controller("6");

            do
            {
                print("Jugada numero %d: ", jugadas + 1);
                print("%d - %d = ", operando1, operando2);
                scanf("%d", &resultado);

                if (resultado != operando1 - operando2)
                {
                    printf("Resultado incorrecto! Vuelva a intentarlo");
                    puntuacion_temporal--;
                }
            } while (resultado != operando1 - operando2 && temporizador == 0);

            if (temporizador == 0)
            {
                printf("Resultado correcto");
                puntuacion_total += puntuacion_temporal;
            }
            break;

        case MULTIPLICACION:
            temporizador = 0;
            time_controller("7");

            do
            {
                print("Jugada numero %d: ", jugadas + 1);
                print("%d * %d = ", operando1, operando2);
                scanf("%d", &resultado);

                if (resultado != operando1 * operando2)
                {
                    printf("Resultado incorrecto! Vuelva a intentarlo");
                    puntuacion_temporal--;
                }
            } while (resultado != operando1 * operando2 && temporizador == 0);

            if (temporizador == 0)
            {
                printf("Resultado correcto");
                puntuacion_total += puntuacion_temporal;
            }
            break;

        case DIVISION:
            temporizador = 0;
            time_controller("8");

            do{    
                print("Jugada numero %d: ", jugadas + 1);
                print("%d : %d = ", operando1, operando2);
                scanf("%d", &resultado);
                
                if(resultado != operando1 / operando2){
                    printf("Resultado incorrecto! Vuelva a intentarlo");
                    puntuacion_temporal--;
                }
            }while(resultado != operando1 / operando2 && temporizador == 0);

            if(temporizador == 0){
                printf("Resultado correcto");
                puntuacion_total += puntuacion_temporal;
            }
            
            break;
        }
    }
}

/*-------DEFINICIONES DE FUNCIONES--------*/
int numero_aleatorio()
{
    return rand() % 11;
}
int operador_aleatorio()
{
    return rand() % 4;
}
void time_controller(char codigo_jugada)
{
    pid_t pid;

    /* Crea el proceso */
    pid = fork();

    /* Determina si ha dado error */
    if (pid == -1)
    {
        printf("Error al crear proceso \n");
        exit(0);
    }

    if (!pid)
        /* Código perteneciente al proceso hijo time controller*/
        execl("./timecontroller", "./timecontroller", pid, codigo_jugada, NULL);
}
void handler_sigusr1(int sig)
{
    temporizador = 1;
}
