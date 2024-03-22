/*
 * Nombre del archivo: mi_archivo.c
 * Descripción: [Breve descripción del archivo]
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

/** @file
 ** @brief
 **/

/* === Headers files inclusions =============================================================== */

#include "leds.h"

/* === Macros definitions ====================================================================== */

/** @brief Valor representativo de un bit en alto.
 */
#define BIT_HIGH 1

/** @brief Estado inicial de un LED apagado.
 */
#define LED_OFF 0

/** @brief Estado inicial de un LED encendido.
 */
#define LED_ON 1

/** @brief Estado para encender todos los LEDs.
 */
#define LEDS_ON 0xFFFF

/** @brief Estado para apagar todos los LEDs.
 */
#define LEDS_OFF 0x0000

/** @brief Valor base usado en el cálculo de la máscara de un LED.
 */
#define BASE_VALUE 1

/** @brief Posición de bit de inicio para el cálculo de la máscara de un LED.
 */
#define BIT_POSITION 1

/* === Private data type declarations ========================================================== */

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

/** Puntero global para almacenar la dirección del puerto de los LEDs. */
static uint16_t * puntero;

/**
 * @brief Inicializa el sistema de LEDs.
 *
 * Configura el sistema de LEDs, asignando el puerto pasado como parámetro a un puntero
 * global y estableciendo todos los LEDs en el estado apagado (`LED_OFF`).
 *
 * @param puerto Puntero al puerto de los LEDs a controlar.
 */
void leds_init(uint16_t * puerto) {
    puntero = puerto;
    *puntero = LED_OFF;
};

/**
 * @brief Enciende un LED específico.
 *
 * Enciende el LED especificado al número pasado como parámetro, utilizando la función
 * `led_to_mask` para calcular la máscara de bits correspondiente y luego aplicándola
 * al puerto de los LEDs.
 *
 * @param led Número del LED a encender.
 */
void leds_turn_on(int led) {
    *puntero |= led_to_mask(led);
}

/**
 * @brief Apaga un LED específico.
 *
 * Apaga el LED especificado al número pasado como parámetro, utilizando la función
 * `led_to_mask` para calcular la máscara de bits correspondiente y luego aplicando
 * la negación de esta máscara al puerto de los LEDs.
 *
 * @param led Número del LED a apagar.
 */
void leds_turn_off(int led) {
    *puntero &= ~led_to_mask(led);
}

/**
 * @brief Enciende todos los LEDs.
 *
 * Establece todos los LEDs en el estado encendido (`LEDS_ON`) aplicando la máscara correspondiente
 * al puerto de los LEDs.
 */
void leds_turn_on_all(void) {
    *puntero = LEDS_ON;
}

/**
 * @brief Apaga todos los LEDs.
 *
 * Establece todos los LEDs en el estado apagado (`LEDS_OFF`) aplicando la máscara correspondiente
 * al puerto de los LEDs.
 */
void leds_turn_off_all(void) {
    *puntero = LEDS_OFF;
}

/**
 * @brief Consultar el estado de un LED.
 *
 * @param led Número del LED a consultar (1-n).
 * @return Estado del LED: 1 si está encendido, 0 si está apagado.
 */
int leds_status(int led) {
    uint16_t mask = led_to_mask(led); // Crea la máscara para el LED específico.
    return (*puntero & mask)
               ? LED_ON
               : LED_OFF; // Usa AND bit a bit para verificar si el LED está encendido.
}

/* === End of documentation ==================================================================== */
