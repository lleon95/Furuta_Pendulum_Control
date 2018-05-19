/*******************************************************************************
* File Name: Pin_outs.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Pin_outs_ALIASES_H) /* Pins Pin_outs_ALIASES_H */
#define CY_PINS_Pin_outs_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Pin_outs_0			(Pin_outs__0__PC)
#define Pin_outs_0_INTR	((uint16)((uint16)0x0001u << Pin_outs__0__SHIFT))

#define Pin_outs_1			(Pin_outs__1__PC)
#define Pin_outs_1_INTR	((uint16)((uint16)0x0001u << Pin_outs__1__SHIFT))

#define Pin_outs_2			(Pin_outs__2__PC)
#define Pin_outs_2_INTR	((uint16)((uint16)0x0001u << Pin_outs__2__SHIFT))

#define Pin_outs_3			(Pin_outs__3__PC)
#define Pin_outs_3_INTR	((uint16)((uint16)0x0001u << Pin_outs__3__SHIFT))

#define Pin_outs_INTR_ALL	 ((uint16)(Pin_outs_0_INTR| Pin_outs_1_INTR| Pin_outs_2_INTR| Pin_outs_3_INTR))

#endif /* End Pins Pin_outs_ALIASES_H */


/* [] END OF FILE */
