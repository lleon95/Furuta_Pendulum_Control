#include <project.h>
#include <string.h>
#include <stdio.h>


int cnt1 = 0;
float angulo1 = 0;

int cnt2 = 0;
float angulo2 = 0;

float adcMeas  = 0;
float Tension = 0;


void transmit(float input, int tab)
{
    char StringBuff[50];
    input = input*1000;
    int sender = input;
    // Verify if we have to put a tab or endl
    if(tab == 1)
        sprintf(StringBuff, "%d\t", sender);
    // If it is a endl
    else
        sprintf(StringBuff, "%d\n", sender);
    // Transmit string
    UART_1_PutString(StringBuff);
}

int main(void)
{
  	/* Initialize*/
  	// Quadrature sensors
    QuadDec_Sensor_Start(); 
    QuadDec_Sensor_SetCounter(0);
    QuadDec_Motor_Start(); 
    QuadDec_Motor_SetCounter(0);
    // ADC for measuring motor voltage
    ADC_DelSig_1_Start();
    ADC_DelSig_1_StartConvert();
    ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_WAIT_FOR_RESULT);
  	// UART
  	UART_1_Start();  
  	// interrupts
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    
    // Cyclic routine
    for(;;)
    {
        /* Place your application code here. */
        // Get the pendulum angle
        cnt1 = QuadDec_Sensor_GetCounter();
      	angulo1 = 6.2832*cnt1/(2*4000.036624);
        // Get the motor angle
        cnt2 = QuadDec_Motor_GetCounter();
      	angulo2 = 6.2832*cnt2/(2*4000.036624);
        // Get motor voltage
        adcMeas = ADC_DelSig_1_GetResult32();
        Tension = (adcMeas * 5) / 65536;
        
        // Transmit by UART
      	transmit(angulo1, 1); // Tab
        transmit(angulo2, 1); // Enter
        transmit(Tension, 0);
        
        // Transmit 50Hz sampling
      	CyDelay(20u); 
    }
    
    
    
}


/*
    Convertir el float a string
    - bytes written =  sprintf(stringBuff, '%f', floatBuff);
    Imprimir un string
    - UART_1_PutString(stringBuff)

    Connections:
    # Pendulum encoder:
        A: P1[6]
        B: P1[7]
    # Motor encoder:
        A: P2[1]
        B: P2[0]
    # ADC Motor Input:
        In: P2[2]

*/


/* [] END OF FILE */