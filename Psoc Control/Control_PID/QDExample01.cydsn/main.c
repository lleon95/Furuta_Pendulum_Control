/*******************************************************************************
* File Name: main.c
*
* Version: 2.10
*
* Description:
*  This is source code for the datasheet example of the Quadrature Decoder 
*  Component.
*
*  Quadrature Decoder Component is driven by two PWM's. Each 500 counts which 
*  are totaled by the Quadrature Decoder Component on Character LCD add one 
*  line of the Vertical Bargraph. When 4000 counts are counted - the Control 
*  Register generates the index signal and Quadrature Decoder is Reset. Number
*  of counts resets to zero, and the procedure cyclically repeats.
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <project.h>

extern uint8 const CYCODE LCD_customFonts[];


/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  main function performs following functions:
*   1. Enables global interrupts.
*   2. Start LCD component.
*   3. Start PWM components.
*   4. Start QD component.
*   5. Display on LCD lines of the Vertical Bargraph every 500 counts of QD 
*      component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
int main()
{
    uint16 qdCount = 0u;
    uint8 i = 1u;
    uint8 j = 0u;
    uint8 k;
    char8 number[5u] = {0x30u, 0x30u, 0x30u, 0x30u, '\0'};

    CyGlobalIntEnable;  /* enable global interrupts. */
    
    Control_Reg_Index_Write(1u);
    
    LCD_Start();    
    LCD_LoadCustomFonts(LCD_customFonts);              
    
    LCD_Position(0u, 0u);
    LCD_PrintString("CountNumber");
    
    PWM_1_Start();
    PWM_2_Start(); 
    QD_SetCounter(5u);
    QD_Start();
    
    LCD_Position(0u, 12u);
    LCD_PrintString(number);
    
    for(;;)
    {
        qdCount = QD_GetCounter();  /* Get value of counts */
        
        /* Check when number of counts multiple of 500 */
        if( ((qdCount % 500u) == 0u) && (qdCount > 0u) )
        {
            /* Procedure of number conversion to decimal system */
            k = 3u;
            number[0u] = '0';
            while (qdCount >= 10u)
            {
                number[k--] = (qdCount % 10u) + 0x30u;
                qdCount /= 10u;
            }
            
            number[k] = (qdCount % 10u) + 0x30u;

            /* Display on LCD number of counts */
            LCD_Position(0u, 12u);
            LCD_PrintString(number);
            
            /* Display on LCD next Vertical Bargraph line */
            LCD_DrawVerticalBG(1u, j++, 1u, i++);
            CyDelay(50u);
        }

        if(j > 7u)
        {
            CyDelay(150u);
            j = 0u;
            i = 1u;
            
            /* Set index input for QD reset generation */
            Control_Reg_Index_Write(0u);
            CyDelay(5u);
            Control_Reg_Index_Write(1u);
            
            /* Clear LCD */
            LCD_Position(1u, 0u);
            LCD_PrintString("                ");            
        }                
    }
}


/* [] END OF FILE */
