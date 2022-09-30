/*! *********************************************************************************
 * \defgroup FSCI_BLE
 * @{
 ********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* \file
*
* This is a header file for FSCI BLE management.
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#ifndef FSCI_BLE_L2CAP_TYPES_H
#define FSCI_BLE_L2CAP_TYPES_H

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/

#include "fsci_ble.h"
#include "l2ca_interface.h"

/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/

#define fsciBleL2capGetConfigStructBufferSize(pConfigStruct)    \
        (sizeof(uint32_t) + sizeof(uint32_t) + sizeof(uint16_t))

/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

void fsciBleL2capGetConfigStructFromBuffer
(
    l2caConfigStruct_t* pConfigStruct, 
    uint8_t**           ppBuffer
);

void fsciBleL2capGetBufferFromConfigStruct
(
    const l2caConfigStruct_t* pConfigStruct, 
    uint8_t**           ppBuffer
);

#ifdef __cplusplus
}
#endif 

#endif /* FSCI_BLE_L2CAP_TYPES_H */

/*! *********************************************************************************
* @}
********************************************************************************** */