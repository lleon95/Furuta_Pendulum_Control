#include <project.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


/* Global constants */
 #define PWM_MAX         499   // PWM 100% (499) with Tpwm = 500us @ 1MHz (500 counts)
 #define V_MAX           5
 #define N_MAX           PWM_MAX+1
 #define PWM_FACTOR      N_MAX/V_MAX   // 100 counts/volt with Tpwm = 500us @ 1MHz
 #define MaxAnguloMotor  1.5708 

 #define REFERENCE      0    // 
 #define MAXINTEGRAL    4.7  // Limits the integral part to 4.7V
 #define TS_FACTOR      1    // 5ms counts for Ts = 5ms
 #define TS             0.001 // 1ms
 #define FS             1000  // TS = 1mss  

int16 pwm = 0;
int cnt1 = 0;
float angulo1 = 0;

int cnt2 = 0;
float angulo2 = 0;

float adcMeas  = 0;
float Tension = 0;

/* PID algorithm global variables */
float KD = 17.459*FS;               // Derivative default constant
float KP = 845.94;       // Proportional default constant
float KI = 58552.5*TS;      // Integral default constant @ 5ms
volatile float ik = 0; // Integral action and memory
float dk = 0; // Integral action and memory
float mk = 0;   // total control action




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
    {
        sprintf(StringBuff, "%d\n", sender);
        
    }
    // Transmit string
        UART_1_PutString(StringBuff);
}

CY_ISR_PROTO(isr_Timer_Handler);

CY_ISR(isr_Timer_Handler)
{
float ek = 0;   // speed error
float ekLast = 0;   // last error
float pdK = 0;

    
    
    
    //Dato = ADC_DelSig_1_GetResult16();
    
    ek = REFERENCE - angulo1; // error
    
    ik += KI*ek; 
    
    
    if (ik > MAXINTEGRAL){
        ik = MAXINTEGRAL;
    }
    else if (ik < -MAXINTEGRAL){
        ik = -MAXINTEGRAL;
    }  
    
    dk = (ek-ekLast)/0.005; //5ms tiempo en el que se aplica el PID
    
    
    pdK = KP*angulo1 + dk*angulo1;
    
    mk = pdK + ik;
    
    
    ekLast = ek;
      
           

    
}

void PWM_Controller(){
    
    pwm = (int16) ((fabs(mk)/V_MAX)*N_MAX+0.5); // Use abs para enteros
    /* Satura el valor del PWM */
    if (pwm > PWM_MAX) {
        pwm = PWM_MAX;
    }
    /* Define la dirección del puente H */
    if (mk >= 0) {
        H_Dir1_Write(1);
        H_Dir2_Write(0);
        }
    else {
        H_Dir1_Write(0);
        H_Dir2_Write(1);
        }
    PWM_WriteCompare(pwm); // escribe al generador de PWM
}
int main(void)
{
  	/* Initialize*/
  	// Quadrature sensor
    QuadDec_Sensor_Start(); 
    QuadDec_Sensor_SetCounter(0);
    QuadDec_Motor_Start(); 
    QuadDec_Motor_SetCounter(0);
    
    ADC_DelSig_1_Start();
    ADC_DelSig_1_StartConvert();
    ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_WAIT_FOR_RESULT);
    
  	// UART
  	UART_1_Start();  
  	// interrupts
    isr_Timer_StartEx(isr_Timer_Handler);
    CyGlobalIntEnable; /* Enable global interrupts. */
    

    int c = 0;
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        /* Place your application code here. */
        //c = 0.1+c;
        //CyDelay(1000u);
        
        cnt1 = QuadDec_Sensor_GetCounter();
      	angulo1 = 6.2832*cnt1/(2*4000.036624);
        
        cnt2 = QuadDec_Motor_GetCounter();
      	angulo2 = 6.2832*cnt2/(2*4000.036624);
        
        
        adcMeas = ADC_DelSig_1_GetResult32();
        Tension = (adcMeas * 5) / 65536;
        
      	transmit(angulo1, 1); // Tab
        transmit(angulo2, 1); // Enter
        
              
        
        c++;
        if((c > 30 && c < 40) || (c > 1500 && c < 1510))
        {
            Pin_2_Write(1u);
            transmit(1,1);
        }
        else
        {
            Pin_2_Write(0u);
            transmit(0,1);
        }
            
            
        transmit(Tension, 0);
    
      	CyDelay(10u);
    }
    
    
    
}


/*
    Convertir el float a string
    - bytes written =  sprintf(stringBuff, '%f', floatBuff);
    Imprimir un string
    - UART_1_PutString(stringBuff)
*/


/* [] END OF FILE */