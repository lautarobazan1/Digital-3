/*
 * Configurar el pin P0.4 como entrada digital con resistencia de pull down y
 * utilizarlo para decidir si el valor representado por los pines P0.0 al P0.3 van a
 * ser sumados o restados al valor guardado en la variable "acumulador".
 * El valor inicial de "acumulador" es 0.
 */

#include "LPC17xx.h"
#include <stdint.h>

void cfgPort(void);
uint32_t getNum(void);

int main(void){
    cfgPort();
    uint32_t acumulador = 0;

    while(1){
        uint32_t num = getNum();
        if(LPC_GPIO0->FIOPIN & (1<<4)){
            acumulador += num;
        }
        else {
            acumulador -= num;
        }
    }
    return 0;

}

void cfgPort(){
    //configurar p0.0=p0.4 como GPIO
    LPC_PINCON->PINSEL0 &= ~(0x2FF);
    //LPC_PINCON->PINSEL0 &= ~( (3<<0) | (3<<2) | (3<<4) | (3<<6) | (3<<8) ); otra forma de configurar GPIO

    LPC_PINCON->PINMODE &= ~(3<<8); //Me aseguro que los bits 8 y 9 (P0.4) esten en 0
    LPC_PINCON->PINMODE |= (3<<8);  //Ahora si pongo en 1 los bits 8 y 9 (P0.4 pull-down)
    LPC_GPIO0->FIODIR &= ~(1<<4);   //~(1<<4) = 1110 1111 con esto pongo el bit 4 de FIODIR en 0 (P0.4 -> entrada)
}

uint32_t getNum(){
    return (LPC_GPIO0->FIOPIN & Ox0F) //Lee los primeros 4 bits de FIOPIN
}
