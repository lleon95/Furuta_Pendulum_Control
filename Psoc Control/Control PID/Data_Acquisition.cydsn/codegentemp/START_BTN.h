/*******************************************************************************
* File Name: START_BTN.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_START_BTN_H) /* Pins START_BTN_H */
#define CY_PINS_START_BTN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "START_BTN_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 START_BTN__PORT == 15 && ((START_BTN__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    START_BTN_Write(uint8 value);
void    START_BTN_SetDriveMode(uint8 mode);
uint8   START_BTN_ReadDataReg(void);
uint8   START_BTN_Read(void);
void    START_BTN_SetInterruptMode(uint16 position, uint16 mode);
uint8   START_BTN_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the START_BTN_SetDriveMode() function.
     *  @{
     */
        #define START_BTN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define START_BTN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define START_BTN_DM_RES_UP          PIN_DM_RES_UP
        #define START_BTN_DM_RES_DWN         PIN_DM_RES_DWN
        #define START_BTN_DM_OD_LO           PIN_DM_OD_LO
        #define START_BTN_DM_OD_HI           PIN_DM_OD_HI
        #define START_BTN_DM_STRONG          PIN_DM_STRONG
        #define START_BTN_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define START_BTN_MASK               START_BTN__MASK
#define START_BTN_SHIFT              START_BTN__SHIFT
#define START_BTN_WIDTH              1u

/* Interrupt constants */
#if defined(START_BTN__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in START_BTN_SetInterruptMode() function.
     *  @{
     */
        #define START_BTN_INTR_NONE      (uint16)(0x0000u)
        #define START_BTN_INTR_RISING    (uint16)(0x0001u)
        #define START_BTN_INTR_FALLING   (uint16)(0x0002u)
        #define START_BTN_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define START_BTN_INTR_MASK      (0x01u) 
#endif /* (START_BTN__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define START_BTN_PS                     (* (reg8 *) START_BTN__PS)
/* Data Register */
#define START_BTN_DR                     (* (reg8 *) START_BTN__DR)
/* Port Number */
#define START_BTN_PRT_NUM                (* (reg8 *) START_BTN__PRT) 
/* Connect to Analog Globals */                                                  
#define START_BTN_AG                     (* (reg8 *) START_BTN__AG)                       
/* Analog MUX bux enable */
#define START_BTN_AMUX                   (* (reg8 *) START_BTN__AMUX) 
/* Bidirectional Enable */                                                        
#define START_BTN_BIE                    (* (reg8 *) START_BTN__BIE)
/* Bit-mask for Aliased Register Access */
#define START_BTN_BIT_MASK               (* (reg8 *) START_BTN__BIT_MASK)
/* Bypass Enable */
#define START_BTN_BYP                    (* (reg8 *) START_BTN__BYP)
/* Port wide control signals */                                                   
#define START_BTN_CTL                    (* (reg8 *) START_BTN__CTL)
/* Drive Modes */
#define START_BTN_DM0                    (* (reg8 *) START_BTN__DM0) 
#define START_BTN_DM1                    (* (reg8 *) START_BTN__DM1)
#define START_BTN_DM2                    (* (reg8 *) START_BTN__DM2) 
/* Input Buffer Disable Override */
#define START_BTN_INP_DIS                (* (reg8 *) START_BTN__INP_DIS)
/* LCD Common or Segment Drive */
#define START_BTN_LCD_COM_SEG            (* (reg8 *) START_BTN__LCD_COM_SEG)
/* Enable Segment LCD */
#define START_BTN_LCD_EN                 (* (reg8 *) START_BTN__LCD_EN)
/* Slew Rate Control */
#define START_BTN_SLW                    (* (reg8 *) START_BTN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define START_BTN_PRTDSI__CAPS_SEL       (* (reg8 *) START_BTN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define START_BTN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) START_BTN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define START_BTN_PRTDSI__OE_SEL0        (* (reg8 *) START_BTN__PRTDSI__OE_SEL0) 
#define START_BTN_PRTDSI__OE_SEL1        (* (reg8 *) START_BTN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define START_BTN_PRTDSI__OUT_SEL0       (* (reg8 *) START_BTN__PRTDSI__OUT_SEL0) 
#define START_BTN_PRTDSI__OUT_SEL1       (* (reg8 *) START_BTN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define START_BTN_PRTDSI__SYNC_OUT       (* (reg8 *) START_BTN__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(START_BTN__SIO_CFG)
    #define START_BTN_SIO_HYST_EN        (* (reg8 *) START_BTN__SIO_HYST_EN)
    #define START_BTN_SIO_REG_HIFREQ     (* (reg8 *) START_BTN__SIO_REG_HIFREQ)
    #define START_BTN_SIO_CFG            (* (reg8 *) START_BTN__SIO_CFG)
    #define START_BTN_SIO_DIFF           (* (reg8 *) START_BTN__SIO_DIFF)
#endif /* (START_BTN__SIO_CFG) */

/* Interrupt Registers */
#if defined(START_BTN__INTSTAT)
    #define START_BTN_INTSTAT            (* (reg8 *) START_BTN__INTSTAT)
    #define START_BTN_SNAP               (* (reg8 *) START_BTN__SNAP)
    
	#define START_BTN_0_INTTYPE_REG 		(* (reg8 *) START_BTN__0__INTTYPE)
#endif /* (START_BTN__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_START_BTN_H */


/* [] END OF FILE */
