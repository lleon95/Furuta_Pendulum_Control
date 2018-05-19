#include <project.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


/* Global constants */
 #define PWM_MAX         999   // PWM 100% (499) with Tpwm = 500us @ 1MHz (500 counts)
 #define V_MAX           12
 #define N_MAX           PWM_MAX+1
 #define PWM_FACTOR      N_MAX/V_MAX   // 100 counts/volt with Tpwm = 500us @ 1MHz
 #define MaxAnguloMotor  3.14
 #define MaxAnguloPendulo  1.5

 #define REFERENCE      0    // 
 #define MAXINTEGRAL    11  // Limits the integral part to 12V -> 11V
 #define TS_FACTOR      1    // 5ms counts for Ts = 5ms
 #define TS             0.005 // 1ms
 #define FS             1/TS  // TS = 1mss  

// Constantes de control
 #define KP 45
 #define KI 220
 #define KD 0.35
 #define N 10

// Constantes de control en discreto
 #define IT KI*TS
 #define DN KD*N
 #define DF KD*FS
 #define UNONTS 1+N*TS


// Inicio de control
int Inicio = 0;

// Encoder del pendulo
int cnt1 = 0;
float angulo1 = 0;

// ADC - deprecated
float adcMeas  = 0;
float Tension = 0;

// Variables PID
volatile float ikLast = 0; // Integral action and memory
volatile float dkLast = 0; // derivative action and memory
volatile float ekLast = 0; // last error
float mk = 0;   // total control action
int16 pwm = 0;

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
    if(Inicio)
        PWM_WriteCompare(pwm);
    else 
        {
        H_Dir1_Write(0);
        H_Dir2_Write(0);
        PWM_WriteCompare(0);
        }
}

CY_ISR_PROTO(isr_Timer_Handler);

// Global vars
float pk = 0;
float ik = 0;
float dk = 0;

CY_ISR(isr_Timer_Handler)
{
    // Calculo de angulo
    cnt1 = QuadDec_Sensor_GetCounter();
    angulo1 = 6.2832*(cnt1-4000)/(2*4000);
    
    // Acota el angulo maximo y apaga el motor
    if(Inicio == 1 && (fabs(angulo1) < MaxAnguloPendulo)){
    
        // Error
        float ek = REFERENCE - angulo1;   // speed error
        
        // Integral
        ik = ek*IT + ikLast;
        // Maximo valor integrativo
        if (ik > MAXINTEGRAL){
            ik = MAXINTEGRAL;
        }
        else if (ik < -MAXINTEGRAL){
            ik = -MAXINTEGRAL;
        }  
        
        // Derivador
        //dk = (DN*(ek - ekLast)+dkLast)/UNONTS;
        dk = DF*(ek - ekLast);
        
        //dk = 0;
        // Proporcional
        pk = KP*ek;
        // PID
        mk = pk + ik + dk;
       
        // Execute
        PWM_Controller();
        
        // Acc
        ikLast = ik;
        ekLast = ek;
        dkLast = dk;
    }
    else{
        Inicio = 0;
        mk = 0;
        PWM_Controller();
    }
}

uint c = 0;

int main(void)
{
  	/* Initialize*/
  	// Quadrature sensor
    QuadDec_Sensor_Start(); 
    QuadDec_Sensor_SetCounter(0);
    
    ADC_DelSig_1_Start();
    ADC_DelSig_1_StartConvert();
    ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_WAIT_FOR_RESULT);
    
    Timer_Start();
    PWM_Start();
    
  	// UART
  	UART_1_Start();  
  	// interrupts
    isr_Timer_StartEx(isr_Timer_Handler);
    
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
       
        c++;
        if(c <= 10){
            transmit(angulo1, 1); // Tab
            //transmit(mk, 0);
            transmit(mk, 1);
            transmit(pk, 1);
            transmit(ik, 1);
            transmit(dk, 1);
            transmit(pwm, 0);
        }
        else
        {
            c = 0;
        }
      	 
        // Boton de inicio  
        uint8 START_1 = START_BTN_Read();
        if (START_1 == 0){
            Inicio = 1;
        }
        
        // Indicador de inicio
        Pin_2_Write(Inicio);
    
      	CyDelay(5u);
    }
    
    
    
}


/*
    Convertir el float a string
    - bytes written =  sprintf(stringBuff, '%f', floatBuff);
    Imprimir un string
    - UART_1_PutString(stringBuff)
*/


/* [] END OF FILE */