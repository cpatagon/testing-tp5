/*
 * Nombre del archivo: test_leds.c
 * Descripción: TP4 Pruebas Unitarias mediante PPT de la librería leds para el curso
 * de Testing en Sistemas Embebidos
 * Autor: Luis Gómez P.
 * Derechos de Autor: (C) 2023 Curso de Testing para sistemas embebidos
 * Licencia: GNU General Public License v3.0
 *
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo
 * bajo los términos de la Licencia Pública General GNU publicada por
 * la Free Software Foundation, ya sea la versión 3 de la Licencia, o
 * (a tu elección) cualquier versión posterior.
 *
 * Este programa se distribuye con la esperanza de que sea útil,
 * pero SIN NINGUNA GARANTÍA; sin siquiera la garantía implícita
 * de COMERCIABILIDAD o APTITUD PARA UN PROPÓSITO PARTICULAR. Ver la
 * Licencia Pública General GNU para más detalles.
 *
 * Deberías haber recibido una copia de la Licencia Pública General GNU
 * junto con este programa. Si no es así, visita <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-only
 *
 */

/** @file leds.c
 ** @brief archivo que contiene las funciones para manejar 16 bits de leds
 **/

/**
 * @brief **lista de pruebas pendientes ***
 * @todo 07.- Prender leds que ya están prendidos antes.
 * @todo 08.- Apagar los leds que ya estén apagados.
 * @todo 09.- Comprobar valores prohibidos.
 * @todo 10.- Comprobar los valores de borde o límite.
 **/

/* === Headers files inclusions =============================================================== */

#include "unity.h"
#include "leds.h"

/* === Macros definitions ====================================================================== */
// #define LED_ENCEDIDO_BIT 1
// #define AJUSTE_INDICE_LED 1

/** @brief Valor base usado en el cálculo de la máscara de un LED.
 */
#define BASE_VALUE 1

/** @brief Posición de bit de inicio para el cálculo de la máscara de un LED.
 */
#define BIT_POSITION 1

/**@brief Macro que define el estado de todos los LEDs apagados.
 */
#define LEDS_OFF 0x0000

/**@brief Macro que define el estado de todos los LEDs encendidos.
 */
#define LEDS_ON 0xFFFF

/* === Private data type declarations ========================================================== */

/** @brief leds de prueba
 **/

static uint16_t leds_virtuales;
static const int LED3 = 3;
static const int LED5 = 5;
static const int LED7 = 7;
static const int LED9 = 9;

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/**
 * @brief función interna que Convierte un número de LED en su respectiva máscara de bits.
 *
 * Calcula la máscara de bits correspondiente al LED especificado. Esto se logra
 * desplazando `BASE_VALUE` tantas posiciones a la izquierda como indique el número de LED,
 * ajustado por `BIT_POSITION`.
 *
 * @param led Número del LED a convertir en máscara de bits.
 * @return uint16_t Máscara de bits correspondiente al LED especificado.
 */
static uint16_t led_to_mask(int led) {
    // Desplazar BASE_VALUE a la izquierda (led - BIT_POSITION) posiciones
    // para obtener la máscara de bits para el LED especificado.
    return (BASE_VALUE << (led - BIT_POSITION));
}

/* === Public function implementation ========================================================== */
/*
LISTA DE PRUEBAS
 */

/**
 *  @brief setUp función de configuración de inicio para ceedling
 *
 **/
void setUp(void) {

    // inicio con todos los leds apagados
    leds_init(&leds_virtuales);
}
/**
 *  @test  Al iniciar el controlador los leds deben quedar todos los bits en 0
 *  sin importar el estado anterior.
 */

void test_todos_los_leds_inician_apagados() {

    // **Preparación:**
    // Se inicializa el estado de los LEDs virtuales.
    leds_init(&leds_virtuales);

    // **Prueba:**
    // Se verifica que el estado de todos los LEDs sea "apagado" (LEDS_OFF).
    TEST_ASSERT_EQUAL_UINT16(LEDS_OFF, leds_virtuales);
}

/**
 *  @test con todos los leds apagados prender el led 3 y verificar que efectivamente
 *     el bit 2 se pone en 1 y el resto de bit permanece en 0.
 *     definimos un nuevo caso de prueba
 **/

void test_prender_un_led(void) {

    // **Preparación:**
    // - Enciende el LED 3.
    leds_turn_on(LED3);

    // **Pruebas:**
    // 1. Verifica que el bit correspondiente al LED 3 esté en alto:
    TEST_ASSERT_BIT_HIGH(LED3 - BIT_POSITION, leds_virtuales);

    // 2. Verifica que la máscara de bits del LED 3 coincida con el estado actual de los LEDs:
    TEST_ASSERT_EQUAL_UINT16(led_to_mask(LED3), leds_virtuales);
}

/**
 * @test Apagar un LED prendido y verificar que se apaga correctamente.
 */
void test_apagar_un_led(void) {

    // Precondición: el LED está encendido.
    leds_turn_on(LED3);

    // Apaga el LED que se había encendido previamente.
    leds_turn_off(LED3);

    // Verifica que el estado actual de los LEDs sea "apagado" (LEDS_OFF).
    TEST_ASSERT_EQUAL_UINT16(LEDS_OFF, leds_virtuales);
}

/**
 * @test Prender y apagar varios LEDs, verificando que el LED 7 y otros led se enciende y apaga
 * correctamente.
 */
void test_prender_y_pagar_varios_leds(void) {

    // Se utiliza una variable estática para almacenar el número de otro LED a probar.

    // Prende el LED 5 y LED7 usando la variable estática.
    leds_turn_on(LED5);
    leds_turn_on(LED7);

    // Enciende el LED 5 por segunda vez para verificar que no cambia su estado.
    leds_turn_on(LED5);

    // Apaga el LED 5 y  LED 9.
    leds_turn_off(LED5);
    leds_turn_off(LED9);

    // Verifica que el LED 7 esté encendido.
    TEST_ASSERT_EQUAL_UINT16(led_to_mask(LED7), leds_virtuales);

    // Verifica que los LEDs distintos al 5 estén apagados.
    TEST_ASSERT_BIT_LOW(~led_to_mask(LED7), leds_virtuales);
}

/**
 *  @test 05.- Con todos los leds apagados prender un led y verificar que al consultar
 *       el estado del mismo me informa que esta prendido.
 **/

void test_apagar_todos_leds_prender_un_led(void) {

    // led 7 a prender

    // prendemos el led 7
    leds_turn_on(LED7);

    //  verificamos que el led 7 se prenda
    TEST_ASSERT_EQUAL_UINT16(led_to_mask(LED7), leds_virtuales);

    //  verificamos que el leds distintos al 7 estén apagados
    TEST_ASSERT_BIT_LOW(~led_to_mask(LED7), leds_virtuales);
}

/**
 * @test Prender todos los LEDs y verificar que se encienden correctamente.
 */
void test_prender_todos_leds(void) {

    // Prende todos los LEDs.
    leds_turn_on_all();

    // Verifica que el estado actual de los LEDs sea "todos encendidos" (LEDS_ON).
    TEST_ASSERT_EQUAL_UINT16(LEDS_ON, leds_virtuales);
}

/**
 * @test Apagar todos los LEDs y verificar que se apagan correctamente.
 */
void test_apagar_todos_leds(void) {

    // Prende todos los LEDs.
    leds_turn_on_all();

    // Apaga todos los LEDs.
    leds_turn_off_all();

    // Verifica que el estado actual de los LEDs sea "todos apagados" (LEDS_OFF).
    TEST_ASSERT_EQUAL_UINT16(LEDS_OFF, leds_virtuales);
}

/**
 * @test Test para verificar que el LED 7 se enciende correctamente.
 *
 * Este test realiza las siguientes acciones:
 * 1. Apaga todos los LEDs.
 * 2. Prende el LED 7.
 * 3. Verifica que el LED 7 esté efectivamente encendido.
 */

void test_esta_leds_encendido(void) {

    // led 7 a prender
    // apagamos todos los leds
    leds_turn_off_all();

    // prendemos el led 7
    leds_turn_on(LED7);

    //  verificamos que todos los leds se enciendan
    TEST_ASSERT_EQUAL_UINT16(true, leds_is_on(LED7));
}

/**
 * @test Test para verificar que el LED 7 se apaga correctamente.
 *
 * Este test realiza las siguientes acciones:
 * 1. Prende todos los LEDs.
 * 2. Apaga el LED 7.
 * 3. Verifica que el LED 7 esté efectivamente apagado.
 */

void test_esta_leds_apagado(void) {

    // LED 7 a probar.
    // Prendemos todos los LEDs.
    leds_turn_on_all();

    // Apagamos el LED 7.
    leds_turn_off(LED7);

    // Verifica que el LED 7 esté apagado.
    TEST_ASSERT_EQUAL_UINT16(true, leds_is_off(LED7));
}

/* === End of documentation ==================================================================== */
