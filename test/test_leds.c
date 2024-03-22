/*
 * Nombre del archivo: mi_archivo.c
 * Descripción: Pruebas Unitarias mediante PPT
 * Autor: Luis Gómez P.
 * Derechos de Autor: (C) 2023 [Tu nombre o el de tu organización]
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
/*
//////////////////////////////////////////////
// *** lista de pruebas pendientes ***
07.- Prender leds que ya están prendidos antes.
08.- Apagar los leds que ya estén apagados.
09.- Comprobar valores prohibidos.
10.- Comprobar los valores de borde o límite.
///////////////////////////////////////////////
*/

/** @file
 ** @brief
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

/** @brief Estado inicial de un LED apagado.
 */
#define LED_OFF 0

/** @brief Estado inicial de un LED encendido.
 */
#define LED_ON 1

/* === Private data type declarations ========================================================== */

static uint16_t leds_virtuales;
static const int LED = 3;

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/**
 * @brief Convierte un número de LED en su respectiva máscara de bits.
 *
 * Calcula la máscara de bits correspondiente al LED especificado. Esto se logra
 * desplazando `BASE_VALUE` tantas posiciones a la izquierda como indique el número de LED,
 * ajustado por `BIT_POSITION`.
 *
 * @param led Número del LED a convertir en máscara de bits.
 * @return uint16_t Máscara de bits correspondiente al LED especificado.
 */
static uint16_t led_to_mask(int led) {
    return (BASE_VALUE << (led - BIT_POSITION));
}

/* === Public function implementation ========================================================== */
/*
LISTA DE PRUEBAS
 */

// función de configuración de inicio
void setUp(void) {
    // inicio con todos los leds apagados
    leds_init(&leds_virtuales);
}

// 1.0 Al iniciar el controlador los leds deben quedar todos los bits en 0
// sin importar el estado anterior.
void test_todos_los_leds_inician_apagados() {

    // partimos con esto para ver que todo funcione este test siempre
    // falla luego ejecutamos el comando ceedling
    // TEST_FAIL_MESSAGE("Arrancamos")

    uint16_t leds_virtuales = LEDS_ON;
    leds_init(&leds_virtuales);
    TEST_ASSERT_EQUAL_UINT16(LEDS_OFF, leds_virtuales);
}

// 2.- Con todos los leds apagados prender el led 3 y verificar que efectivamente
//     el bit 2 se pone en 1 y el resto de bit permanece en 0.
//     definimos un nuevo caso de prueba

void test_prender_un_led(void) {

    leds_turn_on(LED);
    // el bit 2 esta alto
    TEST_ASSERT_BIT_HIGH(LED - 1, leds_virtuales);
    // todos los otros  bits están en bajo
    TEST_ASSERT_BIT_LOW(~(1 << (LED - 1)), leds_virtuales);
}

// 3.- Apagar un led prendido y ver que efectivamente se apaga y que el resto no cambia.

void test_apagar_un_led(void) {

    leds_turn_on(LED);
    leds_turn_off(LED);
    // el bit 2 esta alto
    TEST_ASSERT_EQUAL_UINT16(LEDS_OFF, leds_virtuales);
}

// 4.- Prender y apagar varios leds y consultar que un led (led 5) esté encendido

void test_prender_y_pagar_varios_leds(void) {

    static int led_prueba = 7;
    leds_turn_on(5);
    leds_turn_on(led_prueba);
    leds_turn_on(5);
    leds_turn_off(5);
    leds_turn_off(9);

    // el bit 2 esta alto
    TEST_ASSERT_EQUAL_UINT16(led_to_mask(led_prueba), leds_virtuales);

    //  verificamos que el leds distintos al 7 estén apagados
    TEST_ASSERT_BIT_LOW(~led_to_mask(led_prueba), leds_virtuales);
}

// 05.- Con todos los leds apagados prender un led y verificar que al consultar
//      el estado del mismo me informa que esta prendido.

void test_apagar_todos_leds_prender_un_led(void) {

    // led 7 a prender
    static int led_prueba = 7;

    // nos aseguramos que todos los leds se inician pagados
    leds_init(&leds_virtuales);

    // prendemos el led 7
    leds_turn_on(led_prueba);

    //  verificamos que el led 7 se prenda
    TEST_ASSERT_EQUAL_UINT16(led_to_mask(led_prueba), leds_virtuales);

    //  verificamos que el leds distintos al 7 estén apagados
    TEST_ASSERT_BIT_LOW(~led_to_mask(led_prueba), leds_virtuales);
}

// 06.- Prender todos los leds que están apagados antes de la operación

void test_prender_todos_leds(void) {

    // prendemos todos los leds
    leds_turn_on_all();

    //  verificamos que todos los leds se enciendan
    TEST_ASSERT_EQUAL_UINT16(LEDS_ON, leds_virtuales);
}
// 07.- Apagar todos los leds que ya están prendidos.

void test_apagar_todos_leds(void) {

    // prendemos todos los leds
    leds_turn_on_all();

    // apagamos todos los leds
    leds_turn_off_all();

    //  verificamos que todos los leds se enciendan
    TEST_ASSERT_EQUAL_UINT16(LEDS_OFF, leds_virtuales);
}

//  **Consulta del Estado de un LED**: Permite consultar el estado actual
//                                    (encendido/apagado) de un LED específico.

void test_esta_leds_encendido(void) {

    // led 7 a prender
    static int led_prueba = 7;

    // apagamos todos los leds
    leds_turn_off_all();

    // prendemos el led 7
    leds_turn_on(led_prueba);

    //  verificamos que todos los leds se enciendan
    TEST_ASSERT_EQUAL_UINT16(LED_ON, leds_status(led_prueba));
}

void test_esta_leds_apagado(void) {

    // led 7 a prender
    static int led_prueba = 7;

    // apagamos todos los leds
    leds_turn_on_all();

    // prendemos el led 7
    leds_turn_off(led_prueba);

    //  verificamos que todos los leds se enciendan
    TEST_ASSERT_EQUAL_UINT16(LED_OFF, leds_status(led_prueba));
}

/* === End of documentation ==================================================================== */
