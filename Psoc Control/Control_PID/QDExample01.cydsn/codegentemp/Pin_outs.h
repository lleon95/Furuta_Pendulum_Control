/*******************************************************************************
* File Name: Pin_outs.h  
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

#if !defined(CY_PINS_Pin_outs_H) /* Pins Pin_outs_H */
#define CY_PINS_Pin_outs_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin_outs_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin_outs__PORT == 15 && ((Pin_outs__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Pin_outs_Write(uint8 value);
void    Pin_outs_SetDriveMode(uint8 mode);
uint8   Pin_outs_ReadDataReg(void);
uint8   Pin_outs_Read(void);
void    Pin_outs_SetInterruptMode(uint16 position, uint16 mode);
uint8   Pin_outs_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Pin_outs_SetDriveMode() function.
     *  @{
     */
        #define Pin_outs_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Pin_outs_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Pin_outs_DM_RES_UP          PIN_DM_RES_UP
        #define Pin_outs_DM_RES_DWN         PIN_DM_RES_DWN
        #define Pin_outs_DM_OD_LO           PIN_DM_OD_LO
        #define Pin_outs_DM_OD_HI           PIN_DM_OD_HI
        #define Pin_outs_DM_STRONG          PIN_DM_STRONG
        #define Pin_outs_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Pin_outs_MASK               Pin_outs__MASK
#define Pin_outs_SHIFT              Pin_outs__SHIFT
#define Pin_outs_WIDTH              4u

/* Interrupt constants */
#if defined(Pin_outs__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Pin_outs_SetInterruptMode() function.
     *  @{
     */
        #define Pin_outs_INTR_NONE      (uint16)(0x0000u)
        #define Pin_outs_INTR_RISING    (uint16)(0x0001u)
        #define Pin_outs_INTR_FALLING   (uint16)(0x0002u)
        #define Pin_outs_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Pin_outs_INTR_MASK      (0x01u) 
#endif /* (Pin_outs__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_outs_PS                     (* (reg8 *) Pin_outs__PS)
/* Data Register */
#define Pin_outs_DR                     (* (reg8 *) Pin_outs__DR)
/* Port Number */
#define Pin_outs_PRT_NUM                (* (reg8 *) Pin_outs__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin_outs_AG                     (* (reg8 *) Pin_outs__AG)                       
/* Analog MUX bux enable */
#define Pin_outs_AMUX                   (* (reg8 *) Pin_outs__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin_outs_BIE                    (* (reg8 *) Pin_outs__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin_outs_BIT_MASK               (* (reg8 *) Pin_outs__BIT_MASK)
/* Bypass Enable */
#define Pin_outs_BYP                    (* (reg8 *) Pin_outs__BYP)
/* Port wide control signals */                                                   
#define Pin_outs_CTL                    (* (reg8 *) Pin_outs__CTL)
/* Drive Modes */
#define Pin_outs_DM0                    (* (reg8 *) Pin_outs__DM0) 
#define Pin_outs_DM1                    (* (reg8 *) Pin_outs__DM1)
#define Pin_outs_DM2                    (* (reg8 *) Pin_outs__DM2) 
/* Input Buffer Disable Override */
#define Pin_outs_INP_DIS                (* (reg8 *) Pin_outs__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin_outs_LCD_COM_SEG            (* (reg8 *) Pin_outs__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin_outs_LCD_EN                 (* (reg8 *) Pin_outs__LCD_EN)
/* Slew Rate Control */
#define Pin_outs_SLW                    (* (reg8 *) Pin_outs__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin_outs_PRTDSI__CAPS_SEL       (* (reg8 *) Pin_outs__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin_outs_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin_outs__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin_outs_PRTDSI__OE_SEL0        (* (reg8 *) Pin_outs__PRTDSI__OE_SEL0) 
#define Pin_outs_PRTDSI__OE_SEL1        (* (reg8 *) Pin_outs__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin_outs_PRTDSI__OUT_SEL0       (* (reg8 *) Pin_outs__PRTDSI__OUT_SEL0) 
#define Pin_outs_PRTDSI__OUT_SEL1       (* (reg8 *) Pin_outs__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin_outs_PRTDSI__SYNC_OUT       (* (reg8 *) Pin_outs__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Pin_outs__SIO_CFG)
    #define Pin_outs_SIO_HYST_EN        (* (reg8 *) Pin_outs__SIO_HYST_EN)
    #define Pin_outs_SIO_REG_HIFREQ     (* (reg8 *) Pin_outs__SIO_REG_HIFREQ)
    #define Pin_outs_SIO_CFG            (* (reg8 *) Pin_outs__SIO_CFG)
    #define Pin_outs_SIO_DIFF           (* (reg8 *) Pin_outs__SIO_DIFF)
#endif /* (Pin_outs__SIO_CFG) */

/* Interrupt Registers */
#if defined(Pin_outs__INTSTAT)
    #define Pin_outs_INTSTAT            (* (reg8 *) Pin_outs__INTSTAT)
    #define Pin_outs_SNAP               (* (reg8 *) Pin_outs__SNAP)
    
	#define Pin_outs_0_INTTYPE_REG 		(* (reg8 *) Pin_outs__0__INTTYPE)
	#define Pin_outs_1_INTTYPE_REG 		(* (reg8 *) Pin_outs__1__INTTYPE)
	#define Pin_outs_2_INTTYPE_REG 		(* (reg8 *) Pin_outs__2__INTTYPE)
	#define Pin_outs_3_INTTYPE_REG 		(* (reg8 *) Pin_outs__3__INTTYPE)
#endif /* (Pin_outs__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin_outs_H */


/* [] END OF FILE */
