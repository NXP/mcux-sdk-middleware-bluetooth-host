/*! *********************************************************************************
* \addtogroup BLESecurityManager
* @{
********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2021 NXP
* All rights reserved.
*
* \file
*
* This is the header file which contains BLE Stack Security Manager parameters for the
* Security Manager commands and events.
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#ifndef SM_PARAMS_H
#define SM_PARAMS_H

/************************************************************************************
*************************************************************************************
* Include Files
*************************************************************************************
************************************************************************************/
#include "smp_types.h"
#include "ble_general.h"
#include "ble_constants.h"

/*! Authentication Request unpacked structure used for SM Pairing commands. */
typedef struct
{
    smpAuthReqBondingFlags_t    bondingFlags;
    smpAuthReqMitm_t            mitm;
#if (gBLE42_d == TRUE)
    smpAuthReqSc_t              sc;
    smpAuthReqKeypress_t        keypress;
#endif /* (gBLE42_d == TRUE) */
} smAuthReqParams_t;

/*! Key Distribution unpacked structure used for SM Pairing commands. */
typedef PACKED_UNION
{
    PACKED_STRUCT
    {
        uint8_t     enckey      :1; /*!< The LTK, EDIV and Rand are distributed. */
        uint8_t     idKey       :1; /*!< The IRK, BD_ADDR and address type are distributed. */
        uint8_t     sign        :1; /*!< The CSRK is distributed. */
#if (gBLE42_d == FALSE)
        uint8_t     reserved    :5;
#else  /* (gBLE42_d is FALSE) */
        uint8_t     LinkKey     :1; /*!< Device supports and requests to calculate the BR-EDR Link Key from the LTK. */
        uint8_t     reserved    :4;
#endif /* (gBLE42_d is FALSE) */

    } params;
    uint8_t     raw;
}
smKeyDistParams_t;

#define smKeyDistributionEncKey_c        0x01U   /*!< Bit for the raw field of a variable of \ref smKeyDistParams_t type. */
#define smKeyDistributionIdKey_c         0x02U   /*!< Bit for the raw field of a variable of \ref smKeyDistParams_t type. */
#define smKeyDistributionSignKey_c       0x04U   /*!< Bit for the raw field of a variable of \ref smKeyDistParams_t type. */
#if (gBLE42_d == TRUE)
#define smKeyDistributionLinkKey_c       0x08U   /*!< Bit for the raw field of a variable of \ref smKeyDistParams_t type. */
#endif /* (gBLE42_d == TRUE) */

#define smKeyDistDistributedKeysRawMask_c ((smKeyDistributionEncKey_c)  |   \
                                           (smKeyDistributionIdKey_c)   |   \
                                           (smKeyDistributionSignKey_c)) /*!< Mask for the raw field of a variable of \ref smKeyDistParams_t type.
                                                                          *   Distributed keys only */
#if (gBLE42_d == TRUE)
#define smKeyDistDistributedGeneratedKeysRawMask_c ((smKeyDistributionEncKey_c)  |  \
                                                    (smKeyDistributionIdKey_c)   |  \
                                                    (smKeyDistributionSignKey_c) |  \
                                                    (smKeyDistributionLinkKey_c)) /*!< Mask for the raw field of a variable of \ref smKeyDistParams_t type.
                                                                                   *   Distributed and generated keys */
#endif /* (gBLE42_d == TRUE) */

/*! Key type used for the pairing procedure. */
typedef enum
{
    smKeyTypePasskey_c      = 0x00, /*!< Denotes a Passkey: 0 to 999999 decimal. */
    smKeyTypeOob_c          = 0x01, /*!< Denotes an OOB obtained key: 16 bytes long. */
}smKeyType_t;

/*! Link encryption state at the end of a link encryption procedure. */
typedef enum
{
    smLinkEncryptionNoChange_c      = 0x00, /*!< No changes have been made to the link encryption either because it was not necessary or the encryption was not successful. */
    smLinkEncryptionNotEncrypted_c  = 0x01, /*!< The link was not encrypted. */
    smLinkEncryptionEncrypted_c     = 0x02, /*!< The link was encrypted. */
    smLinkEncryptionKeyChanged_c    = 0x03, /*!< The link was previously encrypted, but the key was changed. */
} smLlEncryptionState_t;

/*! The key type used by the SM in the link encryption procedure. */
typedef enum
{
    smLinkEncKeyTypeNone_c  = 0x00, /*!< Not applicable or unknown key type. */
    smLinkEncKeyTypeStk_c   = 0x01, /*!< Short Term Key set up by the SM during the pairing procedure. */
    smLinkEncKeyTypeLtk_c   = 0x02, /*!< Long Term Key provided by the upper layer or determined through a LE SC procedure. */
} smLlEncKeyType_t;

/*! The type of the random BLE device address to be generated by the SM. */
typedef enum
{
    smBleRandAddrTypeNone_c         = 0x00,
    smBleStaticAddr_c               = 0x01,
    smBleNonResolvablePrivateAddr_c = 0x02,
    smBleResolvablePrivate_Addr_c   = 0x03,
} smBleRandomDevAddType_t;

/*! Keys and additional data exchanged by peers during the Key Distribution phase of the SMP Pairing Procedure. */
typedef struct
{
    uint8_t             ltk[gSmpLtkSize_c];                 /*!< Long Term Key */
    uint8_t             irk[gSmpIrkSize_c];                 /*!< Identity Resolving Key */
    uint8_t             csrk[gSmpCsrkSize_c];               /*!< Connection Signature Resolving Key */
    uint16_t            ediv;                               /*!< Encrypted Diversifier
                                                             *      + Valid only if the LTK is present */
    uint8_t             rand[gSmpLlEncryptionRandSize_c];   /*!< Random Number (for the LL Connection Encryption)
                                                             *      + Valid only if the LTK is present */
    uint8_t             bdAddr[gcBleDeviceAddressSize_c];   /*!< BLE Address.
                                                             *      + Valid only if the IRK is present
                                                             *      + Will contain a Public Device Address or a Static Device Address based on the address type field
                                                             *      + Will be all zeroes if the device has a Resolvable Private Address or a Non-resolvable Private Address. */
    bleAddressType_t    bdAddrType;                         /*!< BLE Address Type - Random or Public (Only A Random Static Address is actually sent.)
                                                             *      + Valid only if the IRK is present */
} smKeyDistPayload_t;

#if (gBLE42_d == TRUE)
/*! Enumerated type to specifiy if the OOB pairing method has MITM protection. */
typedef enum
{
    smOobMitmProtectionOff_c    = 0x00,
    smOobMitmProtectionOn_c     = 0x01,
} smOobMitmProtection_t;
#endif /* (gBLE42_d == TRUE) */

/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/

/***************************************************************
** Parameters of the SM commands and events
***************************************************************/

/*! Parameters of the SM Status event.
 * Used for:
 *      + \ref gBleSmEventStatus_c event. See \ref bleSmEvent_t */
 typedef struct
 {
     bleResult_t    status; /*!< A status returned by the SM regarding it's functionality.
                             *   This event is usually triggered by the activity of the lower layers of the SM. */
 } smStatusParams_t;

/*! Parameters of the SM Pairing Request command and event, SM Pairing Response event and for the Pairing Request Reply command.
 * Used for:
 *      + \ref gBleSmCmdInitiatorStartPairing_c command. See \ref bleSmCommand_t
 *      + \ref gBleSmEventRemotePairingRequest_c event. See \ref bleSmEvent_t
 *      + \ref gBleSmCmdPairingRequestReply_c command. See \ref bleSmCommand_t
 *      + \ref gBleSmEventRemotePairingResponse_c event. See \ref bleSmCommand_t */
typedef struct
{
    smpPairingIoCapability_t        ioCap;
    smpPairingOobDataFlag_t         oobDataFlag;
    smAuthReqParams_t               authReq;
    uint8_t                         maxEncKeySize;
    smKeyDistParams_t               initiatorKeyDist;
    smKeyDistParams_t               responderKeyDist;
} smPairingParams_t;

/*! Parameters of the SM Security Request command and event.
 * Used for:
 *      + \ref gBleSmCmdSendSecurityRequest_c command. See \ref bleSmCommand_t
 *      + \ref gBleSmEventRemoteSecurityRequest_c event. See \ref bleSmEvent_t */
typedef struct
{
    smAuthReqParams_t           authReq;
} smSecurityReqParams_t;

/*! Parameters of the SM Terminate Pairing command.
 * Used for:
 *      + \ref gBleSmCmdTerminatePairing_c command. See \ref bleSmCommand_t */
typedef struct
{
    smpPairingFailedReason_t    reason;
} smTerminatePairingParams_t;


/*! Parameters of the SM Passkey Request Reply command.
 * Used for:
 *      + \ref gBleSmCmdPasskeyRequestReply_c command. See \ref bleSmCommand_t */
typedef struct
{
    smKeyType_t     passKeyType; /*!< Decimal passkey from 0 to 999999 or 16 byte OOB. */
    uint8_t         key[gSmpMaxKeySize_c]; /*!< The key as specified by the key type. */
} smPasskeyReqReplyParams_t;

/*! Parameters of the SM Pairing Keyset Request Reply command.
 * Used for:
 *      + \ref gBleSmCmdPairingKeysetRequestReply_c command. See \ref bleSmCommand_t */
typedef struct
{
    smKeyDistPayload_t  keyDistPayload;     /*!< Keys and additional data to be exchanged during the SMP Pairing key distribution phase. */
    smKeyDistParams_t   sentKeys;           /*!< Keys to be sent to the peer device during the SMP Pairing key distribution phase. */
} smPairingKeysetRequestReplyParams_t;

/*! Parameters of the SM Passkey Display Request event.
 * Used for:
 *      + \ref gBleSmEventPasskeyDisplayRequest_c event. See \ref bleSmEvent_t */
typedef struct
{
    uint32_t    passKey; /*!< A number between 0 and 999999 decimal. */
} smPasskeyDisplayReqParams_t;

/*! Parameters of the SM Passkey Request event.
 * Used for:
 *      + \ref gBleSmEventPasskeyRequest_c event. See \ref bleSmEvent_t */
typedef struct
{
    smKeyType_t    passKeyType; /*!< Decimal passkey from 0 to 999999 or 16 byte OOB. */
} smPasskeyReqParams_t;

/*! Parameters of the SM Pairing Keyset Request event.
 * Used for:
 *      + \ref gBleSmEventPairingKeysetRequest_c event. See \ref bleSmEvent_t */
typedef struct
{
    smKeyDistParams_t   requestedKeys;      /*!< Keys requested by the peer device to be exchanged during the SMP Pairing key distribution phase. */
    uint8_t             encKeySize;         /*!< Encryption key size negotiated by the SMP. */
} smPairingKeysetReqParams_t;

/*! Parameters of the SM Pairing Keyset Received event.
 * Used for:
 *      + \ref gBleSmEventPairingKeysetReceived_c event. See \ref bleSmEvent_t */
typedef struct
{
    smKeyDistPayload_t  keyDistPayload;     /*!< Keys and additional data exchanged during the SMP Pairing key distribution phase. */
    smKeyDistParams_t   receivedKeys;       /*!< Keys received from the peer device during the SMP Pairing key distribution phase. */
    uint8_t             encKeySize;         /*!< Encryption key size negotiated by the SMP. */
} smPairingKeysetReceivedParams_t;

/*! Parameters of the SM Pairing Complete event.
 * Used for:
 *      + \ref gBleSmEventPairingComplete_c event. See \ref bleSmEvent_t */
typedef struct
{
    uint8_t             encKeySize;             /*!< Encryption key size negotiated by the SMP. */
    bool_t              mitmProtection;         /*!< The pairing procedure was completed with MITM protection enabled. */
    bool_t              bonding;                /*!< Both devices involved in the pairing procedure support bonding. */
#if (gBLE42_d == TRUE)
    bool_t              leSc;                   /*!< The pairing procedure was performed using a LE Secure Connections pairing method. */
    uint8_t             leScLtk[gSmpLtkSize_c]; /*!< This is the LTK generated during a LE Secure Connections pairing procedure.
                                                 *   EDIV and RAND for thsi LTK are both 0.
                                                 *   This parameter must be ignored if the boolean indicating LE SC is set to FALSE. */
#endif /* (gBLE42_d == TRUE) */
} smPairingCompleteParams_t;

/*! Parameters of the SM Pairing Failed (local or remote) event.
 * Used for:
 *      + \ref gBleSmEventPairingFailed_c event. See \ref bleSmEvent_t
 *      + \ref gBleSmEventRemotePairingFailed_c event. See \ref bleSmEvent_t */
typedef struct
{
    smpPairingFailedReason_t    reason;
} smPairingFailedParams_t;

#if (gBLE42_d == TRUE)
/*! Parameters of the SM Keypress Notification command and event.
 * Used for:
 *      + \ref gBleSmCmdSendKeypressNotification_c command. See \ref bleSmCommand_t
 *      + \ref gBleSmEventRemoteKeypressNotification_c event. See \ref bleSmEvent_t */
typedef struct
{
    smpKeypressNotificationType_t    keypressNotifType;  /*!< Keypress notification type which denotes a passkey entry keypress action. */
} smKeypressNotificationParams_t;

/*! Parameters of the SM Numeric Comparison Display Request event.
 * Used for:
 *      + \ref gBleSmEventNcDisplayRequest_c event. See \ref bleSmEvent_t */
typedef struct
{
    uint32_t    ncValue; /*!< A number between 0 and 999999 decimal which must be confirmed by the user on both paiairng devices. */
} smNcDisplayReqParams_t;

/*! Parameters of the SM Numeric Comparison Display Confirm command.
 * Used for:
 *      + \ref gBleSmCmdNcDisplayConfirm_c command. See \ref bleSmCommand_t */
typedef struct
{
    bool_t      ncValueConfirm; /*!< True if the value is confirmed by the user (YES) and false otherwise (NO) */
} smNcDisplayConfirmParams_t;

/*! Parameters of the LE SC OOB Data Response command and the Local LE SC OOB Data Response event.
 * Used for:
 *      + \ref gBleSmCmdLeScOobDataRequestReply_c command. See \ref bleSmCommand_t
 *      + \ref gBleSmEventLocalLeScOobData_c event. See \ref bleSmEvent_t */
typedef struct
{
    uint8_t     rValue[gSmpLeScRandomValueSize_c];          /*!< LE SC OOB r (Random value) */
    uint8_t     crValue[gSmpLeScRandomConfirmValueSize_c];  /*!< LE SC OOB Cr (Random Confirm value) */
    uint8_t     addr[gcBleDeviceAddressSize_c];             /*!< BLE Address of the peer used during the pairing procedure */
} smLeScOobDataParams_t;
#endif /* (gBLE42_d == TRUE) */

/***************************************************************
** Parameters of the SM Link Layer related commands and events
***************************************************************/

/*! Parameters of the SM Link Layer Start Encryption command.
 * Used for:
 *      + \ref gBleSmCmdLlStartEncryption_c command. See \ref bleSmCommand_t */
typedef struct
{
    uint8_t     randomNumber[gSmpLlEncryptionRandSize_c];
    uint16_t    encryptedDiversifier;
    uint8_t     longTermKey[gSmpLtkSize_c];
} smLlStartEncryptionParams_t;

/*! Parameters of the SM Link Layer LTK Request Reply command.
 * Used for:
 *      + \ref gBleSmCmdLlLtkRequestReply_c command. See \ref bleSmCommand_t */
typedef struct
{
    uint8_t     longTermKey[gSmpLtkSize_c];
} smLlLtkRequestReplyParams_t;

#if defined(gHciLeEncryptSupport_d) && (gHciLeEncryptSupport_d == TRUE)
/*! Parameters of the SM Link Layer Encrypt Request command.
 * Used for:
 *      + \ref gBleSmCmdLlEncryptReq_c command. See \ref bleSmCommand_t */
typedef struct
{
    uint8_t     key[gSmpLlEncryptBlockSize_c];
    uint8_t     plaintextData[gSmpLlEncryptBlockSize_c];
} smLlEncryptReqParams_t;
#endif

/*! Parameters of the SM Link Layer LTK Request event.
 * Used for:
 *      + \ref gBleSmEventLlLtkRequest_c event. See \ref bleSmEvent_t */
typedef struct
{
    uint8_t     randomNumber[gSmpLlEncryptionRandSize_c];
    uint16_t    encryptedDiversifier;
} smLlLtkRequestParams_t;

/*! Parameters of the SM Link Layer Encryption Status event.
 * Used for:
 *      + \ref gBleSmEventLlEncryptionStatus_c event. See \ref bleSmEvent_t */
typedef struct
{
    bleResult_t                 llStatus;           /*!< Status returned by the Link Layer during the link encryption procedure. */
    smLlEncryptionState_t       encryptionState;    /*!< State of the encryption of the link. */
    smLlEncKeyType_t            encKeyType;         /*!< Type of key used to encrypt the link. */
} smLlEncryptionStatusParams_t;

#if defined(gHciLeEncryptSupport_d) && (gHciLeEncryptSupport_d == TRUE)
/*! Parameters of the SM Link Layer Encrypt Response event.
 * Used for:
 *      + \ref gBleSmEventLlEncryptRes_c event. See \ref bleSmEvent_t */
typedef struct
{
    bleResult_t status;
    uint8_t     encryptedData[gSmpLlEncryptBlockSize_c];
} smLlEncryptResParams_t;
#endif

#if defined(gHciLeRandomSupport_d) && (gHciLeRandomSupport_d == TRUE)
/*! Parameters of the SM Link Layer Rand Response event.
 * Used for:
 *      + \ref gBleSmEventLlRandRes_c event. See \ref bleSmEvent_t */
typedef struct
{
    bleResult_t status;
    uint8_t     randomNumber[gSmpLlRandSize_c];
} smLlRandResParams_t;
#endif

/***************************************************************
** Parameters of the SM Tool Box commands and events
***************************************************************/

/*! Parameters of the SM Tool Box Create Random Device Address Request command.
 * Used for:
 *      + \ref gBleSmCmdTbCreateRandomDeviceAddrReq_c command. See \ref bleSmCommand_t */
typedef struct
{
    smBleRandomDevAddType_t     addrType;   /*!< Type of BLE Random Address to be created. */
    uint8_t*                    pIrk;       /*!< IRK to be used only if a Resolvable Private Address needs to be created.
                                             *   Ignored for other types of addresses. (Can be NULL). */
    uint8_t*                    pRand;      /*!< Random part of a Resolvable Private Address (3 bytes).
                                             *   Last 2 bits must be 0b01 if it is provided by the upper layer.
                                             *   If it is NULL it will be generated internally.
                                             *   Ignored for other types of addresses. */
} smTbCreateRandomDeviceAddrReqParams_t;

/*! Parameters of the SM Tool Box Create Random Device Address Response event.
 * Used for:
 *      + \ref gBleSmEventTbCreateRandomDeviceAddrRes_c event. See \ref bleSmEvent_t */
typedef struct
{
    bleResult_t                 status;                         /*!< Status of the operation. */
    smBleRandomDevAddType_t     addrType;                       /*!< Type of BLE Random Address returned. */
    uint8_t                     addr[gcBleDeviceAddressSize_c]; /*!< Returned random address. */
} smTbCreateRandomDeviceAddrResParams_t;

/*! Parameters of the SM Tool Box Check Resolvable Private Address Request command.
 * Used for:
 *      + \ref gBleSmCmdTbCheckResolvablePrivateAddrReq_c command. See \ref bleSmCommand_t */
typedef struct
{
    uint8_t                     irk[gSmpIrkSize_c];             /*!< IRK used to check the Resolvable Private Address */
    uint8_t                     addr[gcBleDeviceAddressSize_c]; /*!< Address to be checked. */
} smTbCheckResolvablePrivateAddrReqParams_t;

/*! Parameters of the SM Tool Box Create Random Device Address Response event.
 * Used for:
 *      + \ref gBleSmEventTbCheckResolvalePrivateAddrRes_c event. See \ref bleSmEvent_t */
typedef struct
{
    bleResult_t                 status;     /*!< Status of the verification. */
} smTbCheckResolvablePrivateAddrResParams_t;

/*! Parameters of the SM Tool Box Sign Data Request command.
 * Used for:
 *      + \ref gBleSmCmdTbSignDataReq_c command. See \ref bleSmCommand_t */
typedef struct
{
    uint8_t                     csrk[gSmpCsrkSize_c];   /*!< CSRK used to sign the data block. */
    uint16_t                    dataLength;             /*!< Length of the data to be signed. Actual data + 4 byte sign counter.
                                                         *   The maximum accepted length is MAX_ATT_MTU - 8. */
    uint8_t*                    pData;                  /*!< Data to be checked. */
} smTbSignDataReqParams_t;

/*! Parameters of the SM Tool Box Sign Data Response event.
 * Used for:
 *      + \ref gBleSmEventTbSignDataRes_c event. See \ref bleSmEvent_t */
typedef struct
{
    bleResult_t                 status;                                 /*!< Status of the signing operation. */
    uint8_t                     signature[gSmpAuthSignatureLength_c];   /*!< Signature for the provided data (64 bit CMAC). */
} smTbSignDataResParams_t;

/*! Parameters of the SM Tool Box Verify Data Signature Request command.
 * Used for:
 *      + \ref gBleSmCmdTbVerifyDataSignatureReq_c command. See \ref bleSmCommand_t */
typedef struct
{
    uint8_t                     csrk[gSmpCsrkSize_c];                   /*!< CSRK used to verify the signature of the data block. */
    uint16_t                    dataLength;                             /*!< Length of the data to be verified. Actual data + 4 byte sign counter.
                                                                         *   The maximum accepted length is MAX_ATT_MTU - 8. */
    uint8_t*                    pData;                                  /*!< Data to be verified. */
    uint8_t                     signature[gSmpAuthSignatureLength_c];   /*!< Signature to be verified. */
} smTbVerifyDataSignatureReqParams_t;

/*! Parameters of the SM Tool Box Verify Data Signature Response event.
 * Used for:
 *      + \ref gBleSmEventTbVerifyDataSignatureRes_c event. See \ref bleSmEvent_t */
typedef struct
{
    bleResult_t                 status;     /*!< Status of the signature verification operation. */
} smTbVerifyDataSignatureResParams_t;

/***************************************************************
** Parameters for other SM commands and events
***************************************************************/

/*! Parameters of the SM Set Default Passkey command.
 * Used for:
 *      + \ref gBleSmCmdSetDefaultPasskey_c command. See \ref bleSmCommand_t */
typedef struct
{
    uint32_t                    defaultPasskey; /*!< The SM default passkey. Used when the SM must request the display of a passkey.
                                                 *   Set this parameter to:
                                                 *      + decimal 0 to 999.999 - the SM will use this and request this value to be displayed instead of generating a random passkey.
                                                 *      + greater than 999.999 - the SM will ignore the value and generate a random passkey. */
} smSetDefaultPasskeyParams_t;

#if (gBLE42_d == TRUE)
/*! Parameters of the SM Set OOB MITM Protection command.
 * Used for:
 *      + \ref gBleSmCmdSetOobMitmProtection_c command. See \ref bleSmCommand_t */
typedef struct
{
    smOobMitmProtection_t       oobMitmProt;    /*!< Sets the OOB pairing method MITM protection to ON or OFF. Default is OFF. */
} smSetOobMitmProtectionParams_t;

/*! Public Key Generation Type parameter of the SM Generate New ECDH Public Key - Secret Key Pair command.
 * Used for:
 *      + \ref gBleSmCmdGenerateNewEcdhPkSkPairReq_c command. See \ref bleSmCommand_t */
typedef enum smGenerateNewEcdhPkSkPairReqType_tag
{
    smPublicKeyDefault_c        = 0x00, /*!< Unaltered Public Key */
    smPublicKeyZeroed_c         = 0x01, /*!< Public Key coordinates (0, 0) */
    smPublicKeyZeroedY_c        = 0x02, /*!< Generate valid public key and set y-coordinate = 0 */
    smPublicKeyBitFlippedY_c    = 0x03  /*!< Generate valid public key and flip a bit in y-coordinate */
} smGenerateNewEcdhPkSkPairReqType_t;

/*! Parameters of the SM Generate New ECDH Public Key - Secret Key Pair Response event.
 * Used for:
 *      + \ref gBleSmEventGenerateNewEcdhPkSkPairRes_c event. See \ref bleSmEvent_t */
typedef struct
{
    bleResult_t                 status;     /*!< Status of the ECDH key pair generation operation. */
} smGenerateNewEcdhPkSkPairResParams_t;
#endif /* (gBLE42_d == TRUE) */

/*! Parameters of the SM Set Minimum Pairing Security Properties command.
 * Used for:
 *      + \ref gBleSmCmdSetMinPairingSecurityProperties_c command. See \ref bleSmCommand_t */
typedef struct
{
    bool_t              mitmProtection;         /*!< MITM protection accepted by the local device. */
#if (gBLE42_d == TRUE)
    bool_t              leSc;                   /*!< SC requirement for the local device.  */
#endif /* (gBLE42_d == TRUE) */
    uint8_t             minEncKeySize;          /*!< Minimum encryption key size accepted by the local device. */
} smSetMinPairingSecurityPropertiesParams_t;


#endif /* SM_PARAMS_H */


/*! *********************************************************************************
* @}
********************************************************************************** */
