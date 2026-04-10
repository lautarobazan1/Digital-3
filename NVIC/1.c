
/*Toggling de un LED con Interrupción
 *Escriba un programa muy sencillo que utilice un pin del Puerto 2 como interrupción externa (EINT0). 
 *Cada vez que se active la interrupción (por flanco de bajada), un LED conectado a otro pin debe 
 *cambiar de estado (encenderse si estaba apagado, y apagarse si estaba encendido).
 *Pines: Utiliza P2.10 para el botón (EINT0) y P0.22 para el LED
 */


// Resumen:
// Led -> P0.22 -> GPIO salida
// EINT0 -> P2.10 Funcion EINT0 (PINSEL : 01) -> EXTMODE (FLANCO) EXTPOLAR (BAJADA)


// |= → setear bits sin afectar los demás
// &= ~ → limpiar bits
// ^= → toggle bits


#include "LPC17xx.h"
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

void cfgGPIO(void);
void cfgEINT0(void);

int main(void){
    cfgGPIO();
    cfgEINT0();

    while (1))
    {
    
    }
    
}

//Ahora implemento las funciones

void cfgGPIO(void){
    LPC_PINCON->PINSEL1 &= ~(3 << 12); //P0.22 como GPIO, bits 12 y 13 de PINSEL1 en 0
    LPC_GPIO0->FIODIR |= (1 << 22); //P0.22 como salida

    LPC_GPIO0->FIOSET = (1 << 22);  //Apagar LED, es activo por bajo, pongo un 1
}

void cfgEINT0(void){
    LPC_PINCON->PINSEL4 &= ~(3 << 20);  //P2.10; limpio bits 20 y 21
    LPC_PINCON->PINSEL4 |= (1 << 20);   // pongo un 1 en la posicion 20 -> (21 20 -> 0 1) -> P2.10 funcion 01 = EINT0

    LPC_SC->EXTMODE |= (1 << 0);   //EINT0 activo por flanco
    LPC_SC->EXTPOLAR &= ~(1 << 0); //flanco de bajada

    LPC_SC->EXTINT |= (1 << 0);    //Limpio bandera por las dudas

    //Habilitar en NVIC
    NVIC_EnableIRQ(EINT0_IRQn);
}

//Handler

void EINT0_IRQHandler(void){
    //Toggle led
    LPC_GPIO->FIOPIN ^= (1<<22); //Lee el registro FIOPIN y hace una xor con 0000 0000 0010 0000 0000 0000 0000 0000
                                 // si esta en 0 el bit 22 lo pone un 1 y se esta en 1 lo pone en 0

    LPC_EXTINT |= (1 << 0) //Limpio el flag de interrupcion
}
