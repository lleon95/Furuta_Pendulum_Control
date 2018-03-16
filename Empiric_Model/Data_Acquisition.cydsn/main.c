/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <string.h>
#include <stdio.h>

void transmit(float input, int tab)
{
    char StringBuff[10];
    // Verify if we have to put a tab or endl
    if(tab == 1)
        sprintf(StringBuff, "%f\t", input);
    // If it is a endl
    else
        sprintf(StringBuff, "%f\n", input);
    // Transmit string
    UART_1_PutString(StringBuff);
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_1_Start();     /* Enabling the UART */
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    float c = 0;
    for(;;)
    {
        /* Place your application code here. */
        c += 0.1;
        transmit(c,0);
        CyDelay(1000u);
    }
    
    
    
}



/*
    Convertir el float a string
    - bytes written =  sprintf(stringBuff, '%f', floatBuff);

    Imprimir un string
    - UART_1_PutString(stringBuff)
*/


/* [] END OF FILE */
