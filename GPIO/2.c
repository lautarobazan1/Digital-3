/*
 * En los pines P2.0 a P2.7 se encuentra conectado un display de 7 segmentos.
 * Utilizando la variable numDisplay [10] ={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D,
 * 0x7D, 0x07, 0x7F, 0x67} que codifica los números del 0 a 9 para ser mostrados
 * en el display, realizar un programa que muestre indefinidamente la cuenta de 0
 * a 9 en dicho display.
 */

#include "LPC17xx.h"
#include <stdint.h>

#define DELAY 10000000

//Defino prototipos de funciones

void mostrarNum(void);
void cfgPort(void);
void delay(void);

int main(void){
    cfgPort();

    while(1){
        mostrarNum();
    }
}

void cfgPort(void){
    //Configuro los pines 0 a 7 de el puerto 2 como GPIO/salida
    //Recordar que para poner un bit del puerto en GPIO u otra funcion se debe usar 2 bits del registro PINSELx q le corresponda
    LPC_PINCON->PINSEL4 &= ~(0xFFFF); //con la and negada nos aseguramos de modificar solo los primeros 16 bits (8 bits del puerto) y los otros los dejamos como estan
    // 0000 0000 0000 0000 1111 1111 1111 1111 = 0xFFFF
    LPC_GPIO2->FIODIR |= (OxFF); //0xFF = 1111 1111
    LPC_GPIO2->FIOMASK &= ~(OxFF);
}

void mostrarNum (void){
    uint8_t numDisplay [10] ={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};
    for (int i=0; i<10; i++){
    LPC_GPIO2->FIOPIN = numDisplay[i];
    delay(DELAY);
    }
}

void delay(uint32_t delayTime){
    for(uint32_t i = 0; i < delayTime; i++)
}
