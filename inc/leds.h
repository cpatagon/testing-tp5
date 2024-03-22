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

#include <stdint.h>

#ifndef MAIN_H
#define MAIN_H

/** @file
 ** @brief
 **/

/* === Headers files inclusions ================================================================ */

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
 * @param puerto Puntero al registro de control de los LEDs.
 */
void leds_init(uint16_t * puerto);

/**
 * @brief Enciende un LED específico.
 * @param led Número del LED que se desea encender.
 */
void leds_turn_on(int led);

/**
 * @brief Apaga un LED específico.
 * @param led Número del LED que se desea apagar.
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
 * @brief consultar el estado de un LEDs.
 */
int leds_status(int led);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H */
