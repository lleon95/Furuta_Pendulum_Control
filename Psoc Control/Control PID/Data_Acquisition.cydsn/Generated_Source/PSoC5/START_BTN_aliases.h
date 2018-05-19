/*******************************************************************************
* File Name: START_BTN.h  
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

#if !defined(CY_PINS_START_BTN_ALIASES_H) /* Pins START_BTN_ALIASES_H */
#define CY_PINS_START_BTN_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define START_BTN_0			(START_BTN__0__PC)
#define START_BTN_0_INTR	((uint16)((uint16)0x0001u << START_BTN__0__SHIFT))

#define START_BTN_INTR_ALL	 ((uint16)(START_BTN_0_INTR))

#endif /* End Pins START_BTN_ALIASES_H */


/* [] END OF FILE */
