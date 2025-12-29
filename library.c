#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ==========================================
// PROYECTO: JUEGO DE DADOS (C + PYTHON)
// ==========================================

// Función auxiliar para generar un número aleatorio entre 1 y 6
int tirar_dado() {
    return rand() % 6 + 1;
}

// Función que gestiona el evento especial cuando sale un 6
int evento_especial_seis(int acumulado_actual) {
    printf("\n--- ¡EVENTO ESPECIAL POR SACAR UN 6! ---\n");

    int es_multiplicador = rand() % 2;
    int valor = (rand() % 2) + 2;

    if (es_multiplicador) {
        acumulado_actual *= valor;
        printf(">>> ¡Suerte! Tus puntos se MULTIPLICAN por %d. Nuevo acumulado: %d\n", valor, acumulado_actual);
    } else {
        acumulado_actual /= valor;
        printf(">>> Lástima. Tus puntos se DIVIDEN entre %d. Nuevo acumulado: %d\n", valor, acumulado_actual);
    }
    return acumulado_actual;
}

// Función que gestiona todo el turno del jugador humano
int turno_jugador() {
    int acumulado = 0;
    int dado;
    char seguir;
    int fin_turno = 0;

    printf("\n>>> TU TURNO <<<\n");

    while (!fin_turno) {
        dado = tirar_dado();
        printf("Has sacado un: [%d]\n", dado);

        if (dado == 1) {
            printf("¡Oh no! Sacaste un 1. Pierdes el turno y los puntos acumulados.\n");
            acumulado = 0;
            fin_turno = 1;
        }
        else if (dado >= 2 && dado <= 5) {
            acumulado += dado;
            printf("Puntos acumulados en este turno: %d\n", acumulado);

            printf("¿Quieres tirar otra vez? (s/n): ");
            scanf(" %c", &seguir);

            if (seguir == 'n' || seguir == 'N') {
                fin_turno = 1;
            }
        }
        else { // Ha salido un 6
            acumulado = evento_especial_seis(acumulado);

            printf("Puntos acumulados tras el evento: %d\n", acumulado);
            printf("¿Quieres tirar otra vez? (s/n): ");
            scanf(" %c", &seguir);

            if (seguir == 'n' || seguir == 'N') {
                fin_turno = 1;
            }
        }
    }
    return acumulado;
}

// Función que gestiona el turno de la máquina
int turno_maquina() {
    int acumulado = 0;
    int dado;
    int fin_turno = 0;

    printf("\n>>> TURNO DE LA MÁQUINA <<<\n");

    while (!fin_turno) {
        dado = tirar_dado();
        printf("La máquina ha sacado un: [%d]\n", dado);

        if (dado == 1) {
            printf("La máquina saca un 1 y pierde todo.\n");
            acumulado = 0;
            fin_turno = 1;
        }
        else if (dado >= 2 && dado <= 5) {
            acumulado += dado;
        }
        else {
            acumulado = evento_especial_seis(acumulado);
        }

        if (!fin_turno && acumulado >= 12) {
            printf("La máquina decide plantarse con %d puntos.\n", acumulado);
            fin_turno = 1;
        }
    }
    return acumulado;
}

// Función Principal del Juego
int jugar_partida() {
    // ESTA LÍNEA ES LA IMPORTANTE PARA QUE NO SE CUELGUE EN PYTHON:
    setbuf(stdout, NULL);
    srand(time(NULL));

    int vida_jugador = 100;
    int vida_maquina = 100;
    int puntos_turno;

    printf("\n========================================\n");
    printf("   🎲 INICIO DEL JUEGO DE DADOS 🎲\n");
    printf("   Objetivo: Reducir la vida del rival a 0\n");
    printf("========================================\n");

    while (vida_jugador > 0 && vida_maquina > 0) {

        // --- Turno Jugador ---
        puntos_turno = turno_jugador();
        vida_maquina -= puntos_turno;
        if (vida_maquina < 0) vida_maquina = 0;

        printf("\nRESULTADO: Le has quitado %d puntos a la máquina.\n", puntos_turno);
        printf("Vida restante Máquina: %d | Tu vida: %d\n", vida_maquina, vida_jugador);

        if (vida_maquina == 0) break;

        // --- Turno Máquina ---
        puntos_turno = turno_maquina();
        vida_jugador -= puntos_turno;
        if (vida_jugador < 0) vida_jugador = 0;

        printf("\nRESULTADO: La máquina te ha quitado %d puntos.\n", puntos_turno);
        printf("Vida restante Máquina: %d | Tu vida: %d\n", vida_maquina, vida_jugador);
        printf("----------------------------------------\n");
    }

    // Declarar ganador
    printf("\n\n****************************************\n");
    if (vida_maquina == 0) {
        printf("🏆 ¡ENHORABUENA! HAS GANADO LA PARTIDA 🏆\n");
    } else {
        printf("🤖 LA MÁQUINA GANA. ¡MEJOR SUERTE LA PRÓXIMA! 🤖\n");
    }
    printf("****************************************\n");

    return 0;
}
