/*
 * Considerando pulsadores normalmente abiertos conectados en un extremo a
 * masa y en el otro directamente a las entradas P0.0 y p0.1. Realizar un
 * programa que identifique en una variable cual o cuales pulsadores han sido
 * presionados. Las identificaciones posibles a implementar en esta variable van a
 * ser "ninguno", "pulsador 1", "pulsador 2", "pulsador 1 y 2".
 */

// ninguno -> P0.2 encendido
// pulsador 1 -> P0.3 encendido
// pulsador 2 -> P0.4 encendido
// pulsador 1 y 2 -> P0.5 encendido

#include "LPC17xx.h"
#include <stdint.h>

void cfgPort(void);

int main(void){
    cfgPort();
    while(1){
    uint32_t p1 = (LPC_GPIO0->FIOPIN >> 0) & 1; // si el boton esta presionado p1 = 0, sino lo esta p1 = 1
    uint32_t p2 = (LPC_GPIO0->FIOPIN >> 1) & 1; // si el boton esta presionado p2 = 0, sino lo esta p2 = 1

    LPC_GPIO0->FIOCLR = (15<<2); // 0011 1100, apago los leds

    if(p1 && p2) LPC_GPIO0->FIOSET = (1<<2);        //ambos presionados
    else if (!p1 && p2) LPC_GPIO0->FIOSET = (1<<3); //p1 presionado
    else if (!p2 && p1) LPC_GPIO0->FIOSET = (1<<4); //p2 presionado
    else LPC_GPIO0->FIOSET =(1<<5);                 //ambos presionados
    }
    return 0;
}

void cfgPort(void){
    LPC_PINCON->PINSEL &= ~(0xFFF); // 1111 1111 1111 = OxFFF

    // Pull-up en P0.0 y P0.1
    LPC_PINCON->PINMODE0 &= ~(0x0F);

    // P0.0 y P0.1 → entrada
    LPC_GPIO0->FIODIR &= ~((1<<0) | (1<<1));

    // P0.2 a P0.5 → salida
    LPC_GPIO0->FIODIR |= (0x0F << 2);
}
