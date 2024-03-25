/*
 * Nombre del archivo: leds.h
 * Descripción: Header para manejo de LEDs en microcontroladores STM32F429.
 *              Proporciona funciones para inicializar, encender, apagar, y verificar el estado de
 * los LEDs. Autor: Luis Gómez P. Derechos de Autor: (C) 2023 Luis Gómez Licencia: GNU General
 * Public License v3.0
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

/** @file  leds.h
 ** @brief header encargado de presentar funciones encargadas de manejar leds
 **/

#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>
#include <stdbool.h>

/* === Headers files inclusions ================================================================ */

#define LED_MAX_NUM 16 // Número máximo de LEDs soportados

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

/* === Public data type declarations =========================================================== */

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Inicializa el sistema de LEDs.
 * @param puerto Puntero al registro de control de los LEDs (16 bits).
 *
 */
void leds_init(uint16_t * puerto);

/**
 * @brief Enciende un LED específico.
 * @param led Índice del LED que se desea encender (0 a LED_MAX_NUM - 1).
 *
 */
void leds_turn_on(int led);

/**
 * @brief Apaga un LED específico.
 * @param led Índice del LED que se desea apagar (0 a LED_MAX_NUM - 1).
 *
 */
void leds_turn_off(int led);

/**
 * @brief Enciende todos los LEDs.
 */
void leds_turn_on_all(void);

/**
 * @brief Apaga todos los LEDs.
 */
void leds_turn_off_all(void);

/**
 * @brief Consulta el estado de un LED.
 * @param led Índice del LED a consultar.
 * @return true si el LED está encendido, false si está apagado o si el índice es inválido.
 */
bool leds_is_on(int led);

/**
 * @brief Consulta si un LED está apagado.
 * @param led Índice del LED a consultar.
 * @return true si el LED está apagado, false si está encendido o si el índice es inválido.
 */
bool leds_is_off(int led);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* LEDS_H */
