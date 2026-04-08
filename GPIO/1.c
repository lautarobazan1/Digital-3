/*
 * Una famosa empresa de calzados a incorporado a sus zapatillas 10 luces leds
 * comandadas por un microcontrolador LPC1769 y ha pedido a su grupo de
 * ingenieros que diseñen 2 secuencias de luces que cada cierto tiempo se vayan
 * intercalando (secuencia A - secuencia B- secuencia A- ... ). Como todavía no se
 * ha definido la frecuencia a la cual va a funcionar el CPU del microcontrolador,
 * las funciones de retardos que se incorporen deben tener como parámetros de
 * entrada variables que permitan modificar el tiempo de retardo que se vaya a
 * utilizar finalmente. Se pide escribir el código que resuelva este pedido,
 * considerando que los leds se encuentran conectados en los puertos P0,0 al
 * P0.9.
 */

#include "LPC17xx.h"
#include <stdint.h>

#include <cr_section_macros.h>

#define DELAY 10000000  // Valor de retardo (depende de la frecuencia del CPU)

//Prototipos de funciones

void configPort();
void delay  (uint32_t delayTime);
void secuencia1();
void secuencia2();

int main(void){
    configPort();   //Llamo a la funcion que configura el puerto 0

    while(1)        //Bucle principal infinito, alterna entre las 2 secuencias
    {
    secuencia1();
    secuencia2();
    }
    return 0;

}

void configPort()   //Configura los bits del puerto 0 como GPIO/salida
{
    //P0.0 a P0.9 modo GPIO, debemos poner en 0 los primeros 18 bits de PINSEL0
    LPC_PINCON->PINSEL0 &= ~(0x3FFFF); //Pone en 0 los primeros 18 bits sin modificar los demas
    // 0000 0000 0000 0011 1111 1111 1111 1111 = 0x3FFFF

    LPC_GPIO0->FIODIR   |= (0x1FF); //Pone los pines del 0 al 9 del puerto 0 como salida
}

void secuencia1 ()
{
    LPC_GPIO0->FIOCLR = (0x3FF); //Apago los bits P0.0-P0.9
    for(int i = 0; i < 10; i++){
        LPC_GPIO0->FIOSET(1<<i);
        delay(DELAY);
        LPC_GPIO0->FIOCLR(1<<i);
    }
}

void secuencia2 ()
{
    LPC_GPIO0->FIOCLR = (0x3FF); //Apago los bits P0.0-P0.9
    for(int i = 9; i >= 0; i--){
        LPC_GPIO0->FIOSET(1<<i);
        delay(DELAY);
        LPC_GPIO0->FIOCLR(1<<i);
    }    
}

void delay (uint32_t delayTime){
    for(uint32_t i = 0; i < delayTime; i++);
}
