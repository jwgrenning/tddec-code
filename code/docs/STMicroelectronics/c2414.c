/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
/***************** STFL-I Flash Memory Driver ***********************************

   Filename:    c2414.c
  Description: Library routines for the M28W160ECT/ECB
                16Mb (1Mb x 16,Boot Block) Flash Memory drivers
                in different configurations.

   Version:     $Id: c2414.c,v 1.0 2006/09/01
   Author:     Ze-Yu He, MSAC,STMicroelectronics, Shanghai (China)
               Wiley Xu, MSAC,STMicroelectronics, Shanghai (China)
               Echo Chen,MSAC,STMicroelectronics, Beijing  (China)
   Copyright (c) 2006 STMicroelectronics.

   THIS PROGRAM IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER
   EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTY
   OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE ENTIRE RISK
   AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU. SHOULD THE
   PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,
   REPAIR OR CORRECTION.
********************************************************************************

   Version History.

   Ver.   Date        Comments

   0.0    2006/08/25 Initial Release of the software (Alpha)
   1.0    2006/09/01 Qualified Release of the software 
*******************************************************************************

   This source file provides library C code for using the M28W160EC flash devices.
   The following devices are supported in the code:
      M28W160ECT/ECB

   The following functions are available in this library:

      Flash(BlockErase, ParameterType)            to erase one block
      Flash(BlockProtect, ParameterType)          to protect a block of the memory
      Flash(BlockUnprotect, ParameterType)        to unprotect a block of the memory
      Flash(CheckBlockProtection, ParameterType)  to check whether a given block is protected
      Flash(CheckCompatibility, ParameterType)    to check the compatibility of the flash 
      Flash(ChipErase, ParameterType)             to erase the whole chip
      Flash(ChipUnprotect, ParameterType)         to unprotect the whole chip
      Flash(Program, ParameterType)               to program an array of elements
      Flash(Read, ParameterType)                  to read from the flash device
      Flash(ReadCfi, ParameterType)               to read CFI information from the flash
      Flash(ReadDeviceId, ParameterType)          to get the Device ID from the device 
      Flash(ReadManufacturerCode, ParameterType)  to get the Manufacture Code from the device
      Flash(Reset, ParameterType)                 to reset the flash for normal memory access 
      Flash(Resume, ParameterType)                to resume a suspended erase
      Flash(SingleProgram, ParameterType)         to program a single element
      Flash(Suspend, ParameterType)               to suspend an erase
      Flash(Write, ParameterType)                 to write a value to the flash device

      FlashBlockLockDown()                        to lock-down a block
      FlashCheckBlockLockDownStatus()             to check a block-lock-down status
      FlashClearStatusRegister()                  to clear the Status Register manually
      FlashDoubleProgram()                        to program two elements
      FlashErrorStr()                             to return an error description (define VERBOSE)
      FlashProtectionRegisterProgram()            to program a protection register     
      FlashReadProtectionRegister()               to read a protection register location
      FlashReadStatusRegister()                   to read the Status Register
      FlashResponseIntegrityCheck()               to verify the response in multi-flash environments
      FlashTimeOut()                              to return after function timeouts 

   For further information consult the Data Sheet and the Application Note.
   The Application Note gives information about how to modify this code for
   a specific application.

   The hardware specific functions which may need to be modified by the user are:

      FlashWrite() for writing an element (uCPUBusType) to the flash
      FlashRead()  for reading an element (uCPUBusType) from the flash

   A list of the error conditions can be found at the end of the header file.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c2414.h"      /* Header file with global prototypes */
#include "c2414FlashReadAndWrite.h"

#ifdef TIME_H_EXISTS
   #include <time.h>
#endif

/******************************************************************************
    Global variables
*******************************************************************************/ 
ErrorInfoType eiErrorInfo;

/*******************************************************************************
Function:     ReturnType Flash( CommandType cmdCommand, ParameterType *fp )
Arguments:    cmdCommand is an enum which contains all the available function
   commands of the SW driver.
              fp is a (union) parameter struct for all flash command parameters
Return Values:The function returns the following conditions: 
   Flash_Success 
   Flash_AddressInvalid 
   Flash_BankEraseFailed
   Flash_BlockEraseFailed 
   Flash_BlockNrInvalid 
   Flash_BlockProtected 
   Flash_BlockProtectFailed 
   Flash_BlockProtectionUnclear 
   Flash_BlockUnprotected 
   Flash_BlockUnprotectFailed 
   Flash_CfiFailed 
   Flash_ChipEraseFailed 
   Flash_ChipUnprotectFailed 
   Flash_FunctionNotSupported
   Flash_GroupProtectFailed 
   Flash_NoInformationAvailable
   Flash_NoOperationToSuspend
   Flash_OperationOngoing 
   Flash_OperationTimeOut 
   Flash_ProgramFailed 
   Flash_ResponseUnclear 
   Flash_SpecificError
   Flash_VppInvalid 
   Flash_WrongType
Description:  This function is used to access all functions provided with the
   current flash chip.
Pseudo Code:
   Step 1: Select the right action using the cmdCommand parameter
   Step 2: Execute the Flash Function
   Step 3: Return the Error Code
*******************************************************************************/
ReturnType Flash( CommandType cmdCommand, ParameterType *fp ) { 
   ReturnType  rRetVal;

   switch (cmdCommand) {
       case BlockErase:
            rRetVal = FlashBlockErase( (*fp).BlockErase.ublBlockNr ); 
            break; 

       case BlockProtect:
            rRetVal = FlashBlockProtect( (*fp).BlockProtect.ublBlockNr ); 
            break; 

       case BlockUnprotect:
            rRetVal = FlashBlockUnprotect( (*fp).BlockUnprotect.ublBlockNr ); 
            break; 

       case CheckBlockProtection:
            rRetVal = FlashCheckBlockProtection( (*fp).CheckBlockProtection.ublBlockNr );  
            break; 

       case CheckCompatibility:
            rRetVal = FlashCheckCompatibility ();
            break; 

       case ChipErase:
            rRetVal = FlashChipErase( (*fp).ChipErase.rpResults );
            break;

       case ChipUnprotect:
            rRetVal = FlashChipUnprotect( (*fp).ChipUnprotect.rpResults );
            break;

       case Program:
            rRetVal = FlashProgram( (*fp).Program.udMode, 
                                    (*fp).Program.udAddrOff, 
                                    (*fp).Program.udNrOfElementsInArray, 
                                    (*fp).Program.pArray ); 
            break; 

       case Read:
            (*fp).Read.ucValue = FlashRead( (*fp).Read.udAddrOff ); 
            rRetVal = Flash_Success; 
            break; 

       case ReadCfi: 
            rRetVal = FlashReadCfi( (*fp).ReadCfi.uwCfiFunc, &((*fp).ReadCfi).ucCfiValue ); 
            break; 

       case ReadDeviceId:
            rRetVal = FlashReadDeviceId( &((*fp).ReadDeviceId.ucDeviceId) ); 
            break; 
      
       case ReadManufacturerCode:
            rRetVal = FlashReadManufacturerCode ( &((*fp).ReadManufacturerCode.ucManufacturerCode) ); 
            break; 
   
       case Reset:
            FlashReset(); 
            rRetVal = Flash_Success; 
            break; 
      
       case Resume:
            FlashResume();
            rRetVal = Flash_Success;
            break;
   
       case SingleProgram:
            rRetVal = FlashSingleProgram( (*fp).SingleProgram.udAddrOff, (*fp).SingleProgram.ucValue );
            break;
      
       case Suspend:
            FlashSuspend();
            rRetVal = Flash_Success;
            break;

       case Write: 
            FlashWrite( (*fp).Write.udAddrOff, (*fp).Write.ucValue );  
            rRetVal = Flash_Success; 
            break; 

       default:
            rRetVal = Flash_FunctionNotSupported; 
            break; 
   } /* EndSwitch */

   return rRetVal;
} /* EndFunction Flash */






/******************************************************************************* 
Function:     ReturnType FlashBlockErase( uBlockType ublBlockNr ) 
Arguments:    ublBlockNr is the number of the Block to be erased. 
Return Values:The function returns the following conditions: 
   Flash_Success              
   Flash_OperationTimeOut
   Flash_BlockEraseFailed  
   Flash_BlockNrInvalid 
   Flash_BlockProtected  
   Flash_VppInvalid  
Description:  This function can be used to erase the Block specified in ublBlockNr. 
   The function checks that the block nr is within the valid range before issuing 
   the erase command. Once the erase has completed the function checks the Status 
   Register for errors. Any errors are returned, otherwise Flash_Success 
   is returned. 
Pseudo Code:
   Step 1:  Check that the block number exists
   Step 2:  Clear Status Register 
   Step 3:  Issue Erase Command
   Step 4:  Wait until Program/Erase Controller is ready
   Step 5:  Check for any errors and if there is an error clear Status Register
   Step 6:  Return to Read Array mode
   Step 7:  Return error condition
*******************************************************************************/
ReturnType FlashBlockErase( uBlockType ublBlockNr) {
   ReturnType rRetVal;     /* Holds return value */ 
   uCPUBusType ucStatus;   /* Holds the Status Register reads */ 
   
   /* Step 1: Check that the block number exists */
   if ( ublBlockNr >= NUM_BLOCKS )
      return Flash_BlockNrInvalid;
      
   /* Step 2: Clear Status Register */
   FlashWrite( ANY_ADDR, 0x0050 ); /* Clear Status Register */
   /* NOTE ! CSR also clears bit 1 BPS as well as bits 3, 4 and 5 */

   /* Step 3: Issue Erase Command */
   FlashWrite( ANY_ADDR, CMD(0x0020) );
   FlashWrite( BlockOffset[ublBlockNr], CMD(0x00D0) );
   
   /* Step 4: Wait until Program/Erase Controller is ready */
   FlashTimeOut(0); /* Initialize TimeOut Counter */
   do {
      ucStatus = FlashRead( ANY_ADDR );
      if (FlashTimeOut(5) == Flash_OperationTimeOut) {
         FlashReset();
         return Flash_OperationTimeOut; 
      } /* EndIf */
   } while( (ucStatus & CMD(0x0080)) != CMD(0x0080) ); /* Wait until every Action is finished (StatusRegister Bit7 = 1) */ 
   
   /* Step 5: Check for any errors and if there is an error clear Status Register 
      (command sequence error is not possible) */
   if( ucStatus & CMD(0x002A) ) {
      if ( ucStatus & CMD(0x0008) )
         rRetVal = Flash_VppInvalid;
      else if ( ucStatus & CMD(0x0002) )
         rRetVal = Flash_BlockProtected;
      else
         rRetVal = Flash_BlockEraseFailed;
      FlashWrite( ANY_ADDR , CMD(0x0050) );  /* clear Status Register */
   } /* EndIf ucStatus */
   else
      rRetVal = Flash_Success;   

   /* Step 6: Return to Read Array mode */
   FlashReset(); /* Read Array Command */
   
   /* Step 7: Return error condition */
   return rRetVal; 
} /* EndFunction FlashBlockErase */





/*******************************************************************************
Function:     ReturnType FlashBlockLockDown(uBlockType ublBlockNr)
Arguments:    ublBlockNr holds the block number to lock-down
Return Values:The function returns the following conditions:
   Flash_Success
   Flash_BlockNrInvalid
   Flash_SpecificError. In this case:
      eiErrorInfo.sprRetVal = FlashSpec_BlockLockDownFailed
Description:  This function locks-down a block selected by ublBlockNr but 
   only if that particular block is valid. It then tests to see if the lock-down
	command was successful.   
Pseudo Code:
   Step 1:  Check to see if the block number exists
   Step 2:  Lock-down the block
   Step 3:  Read the block ublBlockNr to check lock-down status and return the
            device to Read Array mode
*******************************************************************************/
ReturnType FlashBlockLockDown(uBlockType ublBlockNr) {
   ReturnType rRetVal;  /* holds the block lock-down status */
   
   /* Step 1: Check to see if the block number exists */
   if ( ublBlockNr >= NUM_BLOCKS )
      return Flash_BlockNrInvalid;
   
   /* Step 2: Lock-down the block */
   FlashWrite(ANY_ADDR, CMD(0x0060));
   FlashWrite(BlockOffset[ublBlockNr], CMD(0x002F));
   
   /* Step 3:Read the block ublBlockNr to check lock-down status (also return the device to Read Array mode) */
   rRetVal = FlashCheckBlockLockDownStatus( ublBlockNr );
   if ( (rRetVal != Flash_BlockProtectionUnclear) && (eiErrorInfo.sprRetVal == FlashSpec_BlockLockedDown) )
      return Flash_Success;
   else {
      eiErrorInfo.sprRetVal = FlashSpec_BlockLockDownFailed;
      return Flash_SpecificError;
   } /* EndIf */   
} /* EndFunction FlashBlockLockDown */





/*******************************************************************************
Function:     ReturnType FlashBlockProtect( uBlockType ublBlockNr )
Arguments:    ublBlockNr holds the block number to protect (i.e. "lock"
   in the data sheet).
Return Values:The function returns the following conditions:  
   Flash_Success       
   Flash_BlockNrInvalid
   Flash_BlockProtectFailed
Description:  This function protects a block selected by ublBlockNr, but
   only if that particular block is unprotected and valid. The block 
   protect command is then written and then checked to ensure that 
   it was successful.   
Pseudo Code:
   Step 1:  Check to see if the block number exists
   Step 2:  Protect the block
   Step 3:  Read the block ublBlockNr to check protect status and return the 
            device to Read Array mode
*******************************************************************************/
ReturnType FlashBlockProtect( uBlockType ublBlockNr ) {
   /* Step 1: Check to see if the block number exists */
   if ( ublBlockNr >= NUM_BLOCKS )
      return Flash_BlockNrInvalid;

   /* Step 2: Protect the block */
   FlashWrite( ANY_ADDR , CMD(0x0060) );
   FlashWrite( BlockOffset[ublBlockNr], CMD(0x0001) );

   /* Step 3: Read the block ublBlockNr to check protect status (also return the 
              addressed bank to Read Array mode) */
   if ( FlashCheckBlockProtection(ublBlockNr) != Flash_BlockProtected )
      return Flash_BlockProtectFailed;
   else
      return Flash_Success;
} /* EndFunction FlashBlockProtect */





/*******************************************************************************
Function:     ReturnType FlashBlockUnprotect( uBlockType ublBlockNr )
Arguments:    ublBlockNr holds the block number to unprotect (i.e. "unlock"
   in the data sheet).
Return Values:The function returns the following conditions:  
   Flash_Success       
   Flash_BlockNrInvalid
   Flash_BlockUnprotectFailed
Description:  This function protects a block selected by ublBlockNr, but
   only if that particular block is unprotected and valid. The block 
   unprotect command is then written and then checked to ensure that 
   it was successful.   
Pseudo Code:
   Step 1:  Check to see if the block number exists
   Step 2:  Unprotect the block
   Step 3:  Read the block ublBlockNr to check protect status and return the 
            device to Read Array mode
*******************************************************************************/
ReturnType FlashBlockUnprotect( uBlockType ublBlockNr ) {
   /* Step 1: Check to see if the block number exists */
   if ( ublBlockNr >= NUM_BLOCKS )
      return Flash_BlockNrInvalid;

   /* Step 2: Protect the block */
   FlashWrite( ANY_ADDR, CMD(0x0060) );
   FlashWrite( BlockOffset[ublBlockNr], CMD(0x00D0) );

   /* Step 3: Read the block ublBlockNr to check protect status (also return the 
              addressed bank to Read Array mode) */
   if ( FlashCheckBlockProtection(ublBlockNr) != Flash_BlockUnprotected )
      return Flash_BlockUnprotectFailed;
   else
      return Flash_Success;
} /* EndFunction FlashBlockUnprotect */





/*******************************************************************************
Function:     ReturnType FlashCheckBlockLockDownStatus( uBlockType ublBlockNr )
Arguments:    ublBlockNr = block number to be checked
   Note: the first block is Block 0
Return Values:The function returns the following conditions:  
   Flash_BlockNrInvalid
   Flash_BlockProtectionUnclear
   Flash_SpecificError. In this case:
      eiErrorInfo.sprRetVal = FlashSpec_BlockLockedDown
      eiErrorInfo.sprRetVal = FlashSpec_BlockUnlockedDown
Description:  This function checks the lock-down status of block selected 
   by ublBlockNr, but only if that particular block is valid.
Pseudo Code:
   Step 1:  Check Range of Block Number Parameter
   Step 2:  Send the Read Electronic Signature command
   Step 3:  Read lock-down status
   Step 4:  Return the device to Read Array mode
   Step 5:  Return the correct value and fill sprRetVal field of eiErrorInfo
            structure if necessary
*******************************************************************************/
ReturnType FlashCheckBlockLockDownStatus( uBlockType ublBlockNr ) {
   uCPUBusType ucProtStatus; /* Holds the lock-down status */
   
   /* Step 1: Check that the block number exists */
   if ( ublBlockNr >= NUM_BLOCKS )
      return Flash_BlockNrInvalid;
      
   /* Step 2: Send the Read Electronic Signature command */
   FlashWrite( ANY_ADDR, CMD(0x0090) );
   
   /* Step 3: Read lock-down Status */
   ucProtStatus = FlashRead( BlockOffset[ublBlockNr] + 0x00000002 ); 

   /* Step 4: Return to read array mode */
   FlashReset();  
      
   /* Step 5: Return the correct value and fill sprRetVal field of eiErrorInfo structure if necessary */
   if ( (ucProtStatus == CMD(2)) || (ucProtStatus == CMD(3)) ) {
      eiErrorInfo.sprRetVal = FlashSpec_BlockLockedDown;
      return Flash_SpecificError;
   } else if  ( (ucProtStatus == CMD(0)) || (ucProtStatus == CMD(1)) ) {
      eiErrorInfo.sprRetVal = FlashSpec_BlockUnlockedDown;
      return Flash_SpecificError;
   } else
      return Flash_BlockProtectionUnclear;
} /* EndFunction FlashCheckBlockLockDownStatus */






/*******************************************************************************
Function:     ReturnType FlashCheckBlockProtection( uBlockType ublBlockNr )
Arguments:    ublBlockNr holds block number to be checked
   Note: the first block is Block 0
Return Values:The function returns the following conditions:  
   Flash_BlockNrInvalid
   Flash_BlockProtected
   Flash_BlockProtectionUnclear
   Flash_BlockUnprotected
Description:  This function checks the protection status of block selected 
   by ublBlockNr, but only if that particular block is valid.
Pseudo Code:
   Step 1:  Check Range of Block Number Parameter
   Step 2:  Send the Read Electronic Signature command
   Step 3:  Read protection Status
   Step 4:  Return the device to Read Array mode
*******************************************************************************/
ReturnType FlashCheckBlockProtection( uBlockType ublBlockNr ) {
   ReturnType  rRetVal; /* Holds the return value */
   uCPUBusType ucProtStatus; /* Holds the protection status */ 

   /* Step 1: Check that the block number exists */
   if ( ublBlockNr >= NUM_BLOCKS )
      return Flash_BlockNrInvalid;
   
   /* Step 2: Send the Read Electronic Signature command */
   FlashWrite( ANY_ADDR , CMD(0x0090) );
   
   /* Step 3: Read protectionStatus */
   ucProtStatus = FlashRead( BlockOffset[ublBlockNr] + 0x00000002 ); 
   
   if ( (ucProtStatus == 0) || (ucProtStatus == CMD(2)) )
      rRetVal = Flash_BlockUnprotected;
   else if ( (ucProtStatus == CMD(1)) || (ucProtStatus == CMD(3)) )
      rRetVal = Flash_BlockProtected;
   else
      rRetVal = Flash_BlockProtectionUnclear;
   
   /* Step 4: Return the device to Read Array mode */
   FlashReset();  
   
   return rRetVal;
} /* EndFunction FlashCheckBlockProtection */





/******************************************************************************* 
Function:     ReturnType FlashCheckCompatibility( void ) 
Arguments:    None
Return Values:The function returns the following conditions:  
   Flash_Success
   Flash_WrongType
Description:  This function checks the compatibility of the device with
   the SW driver.
Pseudo Code: 
   Step 1:  Read the Device Id 
   Step 2:  Read the Manufacturer Code
   Step 3:  Check the results
*******************************************************************************/ 
ReturnType FlashCheckCompatibility( void ) { 
   ReturnType  rRetVal, rCheck1, rCheck2;       /* Holds the result of the Read ops  */ 
   uCPUBusType ucDeviceId, ucManufacturerCode;  /* Holds the values read */ 
   
   rRetVal = Flash_WrongType;
   
   /* Step 1:  Read the Device Id */
   rCheck1 = FlashReadDeviceId( &ucDeviceId ); 
   
   /* Step 2:  Read the Manufacturer Code */
   rCheck2 = FlashReadManufacturerCode( &ucManufacturerCode ); 
   
   /* Step 3:  Check the correctness of the result */
   if ( (rCheck1 == Flash_Success)  && (rCheck2 == Flash_Success) && 
       (ucDeviceId == EXPECTED_DEVICE)  && (ucManufacturerCode == MANUFACTURER_ST) )  
      rRetVal = Flash_Success; 
   return rRetVal; 
} /* EndFunction FlashCheckCompatibility */ 






/*******************************************************************************
Function:     ReturnType FlashChipErase( ReturnType *rpResults )
Arguments:    rpResults is a pointer to an array where the results will be 
   stored for each block. If rpResults == NULL then no results have been stored.
Return Values:The function returns the following conditions:
      Flash_Success              
      Flash_ChipEraseFailed
Description: The function can be used to erase the whole flash chip. Each Block
   is erased in turn. The function only returns when all of the Blocks have
   been erased or have generated an error, except if the Flash_VppInvalid is
   encountered, in which case the function aborts and reports all remaining
   blocks as having Flash_VppInvalid. If Vpp is invalid for one block then it
   follows that it will be invalid for subsequent blocks as well (battery failure?).
Pseudo Code:
   Step 1: Send Block Erase Command for each block
   Step 2: Register the errors or success in the array
   Step 3: If Flash_VppInvalid returned fill rest of results array & abort
   Step 4: Return error condition
*******************************************************************************/
ReturnType FlashChipErase( ReturnType *rpResults ) {
   ReturnType rRetVal = Flash_Success; /* Return value: Initially optimistic */
   ReturnType rError;       /* Holds the latest error */
   uBlockType ublCurBlock;  /* Used to track the current block in a range */
   
   for( ublCurBlock = 0; ublCurBlock < NUM_BLOCKS; ublCurBlock++ ) {
      /* Step 1: Send Block Erase Command for each block */
      rError = FlashBlockErase( ublCurBlock );
      
      if ( rError != Flash_Success )
         rRetVal = Flash_ChipEraseFailed;
      
      /* Step 2: Register the errors in the array */
      if( rpResults != NULL )
         rpResults[ublCurBlock] = rError;
      
      /* Step 3: If Flash_VppInvalid returned fill rest of results array and abort */
      if( rError == Flash_VppInvalid ) {
         if( rpResults != NULL )
            while( ++ublCurBlock < NUM_BLOCKS )  /* on remaining blocks */
               rpResults[ublCurBlock] = rError;  /* fill in Vpp error */
         break;  /* Exit from Next */
      } /* EndIf Flash_VppInvalid */
   } /* Next ublCurBlock */
   
   /* Step 4: Return error condition */
   return rRetVal;
} /* EndFunction FlashChipErase */





/*******************************************************************************
Function:     ReturnType FlashChipUnprotect( ReturnType *rpResults )
Arguments:    rpResults is a pointer to an array where the results will be 
   stored for each block. If rpResults == NULL then no results have been stored.
Return Values:The function returns the following conditions:  
   Flash_Success     
   Flash_ChipUnprotectFailed
Description: The function can be used to unprotect the whole flash chip. Each
   block is erased in turn.
Pseudo Code:
   Step 1: Send unprotect command for each block 
   Step 2: Register the errors or success in the array
   Step 3: Return error condition
*******************************************************************************/
ReturnType FlashChipUnprotect(ReturnType *rpResults) {
   ReturnType rRetVal = Flash_Success; /* Return value: Initially optimistic */     
   ReturnType rError;      /* holds latest error value */ 
   uBlockType ublCurBlock; /* Used to track the current block in a range */          
   
   for (ublCurBlock=0;ublCurBlock < NUM_BLOCKS;ublCurBlock++) {
      /* Step 1: Send unprotect command for each block */
      rError = FlashBlockUnprotect(ublCurBlock); 
      
      if ( rError != Flash_Success )
         rRetVal = Flash_ChipUnprotectFailed;
      
      /* Step 2: Register the errors in the array */
      if (rpResults != NULL)
         rpResults[ublCurBlock] = rError;
   } /* Next ublCurBlock */
   
   /* Step 3: Return error condition */
   return rRetVal;  
} /* EndFunction FlashChipUnprotect */





/*******************************************************************************
Function:     void FlashClearStatusRegister( void )
Arguments:    none
Return Values:none
Description:  This function clear the status register
Pseudo Code:
   Step 1: Send the Clear Status Register command
*******************************************************************************/
void FlashClearStatusRegister( void ) {
   /* Step 1: Send the Clear Status Register command */
   FlashWrite( ANY_ADDR, CMD(0x0050) );
} /* EndFunction FlashReadDeviceId */






/******************************************************************************* 
Function: ReturnType FlashDoubleProgram( udword udAddrOff, uCPUBusType ucVal1,
                   uCPUBusType ucVal2 )
Arguments:
   udAddrOff is an address offset into pair to be programmed 
   ucValue1 is the value to be programmed at the first address offset of pair
   ucValue2 is the value to be programmed the second address offset of pair
Return Values:The function returns the following conditions:
   Flash_Success
   Flash_AddressInvalid
   Flash_BlockProtected
   Flash_OperationTimeOut
   Flash_ProgramFailed
   Flash_VppInvalid
Description: 
   This function is used to program two uCPUBusType value into two addresses
   which differ only for the bit A0 (LSB). It uses double-word program command.
   It does not erase the flash first and no error is returned in case of
   double programming. Once the program command has completed the function 
   checks the Status Register for errors. The function returns Flash_Success
   if the addresses have successfully been programmed.
   
	Note: VPP must be set to VPPH. (Other limitations are indicated in the data sheet).
                                   
Pseudo Code: 
   Step 1:  Check whether the data to be programmed are 
            within the Flash memory space 
   Step 2:  Program the data
   Step 3:  Wait until the Program/Erase Controller is ready 
   Step 4:  Check for any errors 
   Step 5:  Return to Read Array mode 
   Step 6:  Return the error condition 
*******************************************************************************/ 
ReturnType FlashDoubleProgram( udword udAddrOff, uCPUBusType ucVal1, uCPUBusType ucVal2 ) { 
   ReturnType rRetVal; /* Return Value: Initially optimistic */ 
   uCPUBusType ucStatus;      /* Holds the Status Register reads */ 
   udword udFirstAddrOff;   /* first address offset */
   
   /* Step 1: Check whether the data to be programmed are are within the Flash memory space */ 
   if( udAddrOff >= FLASH_SIZE )
      return Flash_AddressInvalid;
   
   udFirstAddrOff = udAddrOff & (~0x1); /* calculate first address offset*/
   
   FlashWrite( ANY_ADDR, CMD(0x0050) );  /* clear status register */
   /* NOTE ! CSR also clears bit 1 BPS as well as bits 3, 4 and 5 */ 
   
   /* Step 2: Program the data */ 
   FlashWrite( ANY_ADDR, CMD(0x0030) );
   FlashWrite( udFirstAddrOff, ucVal1 );
   FlashWrite( udFirstAddrOff + 1, ucVal2 );
   
   /* Step 3: Wait until Program/Erase Controller is ready */ 
   FlashTimeOut(0); /* Initialize TimeOut Counter */ 
   do {
      ucStatus = FlashRead(udFirstAddrOff);
      if (FlashTimeOut(5) == Flash_OperationTimeOut) {
         FlashReset();
         return Flash_OperationTimeOut; 
      } /* EndIf */
   } while( (ucStatus & CMD(0x0080)) != CMD(0x0080) );
    /* Wait until every Action is finished (StatusRegister Bit7 = 1) */ 
   
   /* Step 4: Check for any errors */ 
   if( ucStatus & (0x001A) ) {
      if ( ucStatus & CMD(0x0008) )
         rRetVal = Flash_VppInvalid;
      else if ( ucStatus & CMD(0x0002) )
         rRetVal = Flash_BlockProtected;
      else
         rRetVal = Flash_ProgramFailed;
      FlashWrite( ANY_ADDR, CMD(0x0050) );   /* clear Status Register */
   } /* EndIf ucStatus */
   else
      rRetVal = Flash_Success;   
   
   /* Step 5:  Return to Read Array mode */
   FlashReset();
   
   /* Step 6: Return the error condition */ 
   return rRetVal; 
} /* EndFunction FlashDoubleProgram */





#ifdef VERBOSE
/******************************************************************************* 
Function:     byte *FlashErrorStr( ReturnType rErrNum ); 
Arguments:    rErrNum is the error number returned from other Flash Routines 
Return Value: A pointer to a string with the error message 
Description:  This function is used to generate a text string describing the 
   error from the flash. Call with the return value from other flash routines. 
Pseudo Code: 
   Step 1: Return the correct string. 
*******************************************************************************/ 
byte *FlashErrorStr( ReturnType rErrNum ) {   
    switch(rErrNum) {
       case Flash_AddressInvalid: 
            return "Flash - Address is out of Range"; 
       case Flash_BlockEraseFailed: 
            return "Flash - Block Erase failed"; 
       case Flash_BlockNrInvalid: 
            return "Flash - Block Number is out of Range"; 
       case Flash_BlockProtected: 
            return "Flash - Block is protected"; 
       case Flash_BlockProtectFailed: 
            return "Flash - Block Protection failed"; 
       case Flash_BlockProtectionUnclear: 
            return "Flash - Block Protection Status is unclear"; 
       case Flash_BlockUnprotected: 
            return "Flash - Block is unprotected"; 
       case Flash_BlockUnprotectFailed:
            return "Flash - Block Unprotection failed"; 
       case Flash_CfiFailed: 
            return "Flash - CFI Interface failed"; 
       case Flash_ChipEraseFailed: 
            return "Flash - Chip Erase failed"; 
       case Flash_ChipUnprotectFailed: 
            return "Flash - Chip Unprotect failed"; 
       case Flash_FunctionNotSupported: 
            return "Flash - Function not supported"; 
       case Flash_NoInformationAvailable: 
            return "Flash - No Additional Information Available"; 
       case Flash_OperationOngoing: 
            return "Flash - Operation ongoing"; 
       case Flash_OperationTimeOut: 
            return "Flash - Operation TimeOut"; 
       case Flash_ProgramFailed: 
            return "Flash - Program failed";
       case Flash_ResponseUnclear:
            return "Flash - Response unclear"; 
       case Flash_SpecificError: 

            switch (eiErrorInfo.sprRetVal) {
               case FlashSpec_BlockLockDownFailed:
                    return "Flash - Block Lock Down Failed";
               case FlashSpec_BlockLockedDown:
                    return "Flash - Block is locked down";
               case FlashSpec_BlockUnlockedDown:
                    return "Flash - Block is unlocked down";
               case FlashSpec_ProtectionRegisterLocked:
                    return "Flash - Protection Register Locked";
               default: 
                    return "Flash - Undefined Specific Error";
            } /* EndSwitch */

       case Flash_Success: 
            return "Flash - Success"; 
       case Flash_VppInvalid: 
            return "Flash - Program/Erase Voltage (VPP) unsufficient"; 
       case Flash_WrongType: 
            return "Flash - Wrong Type"; 
       default: 
            return "Flash - Undefined Error Value"; 
    } /* EndSwitch */ 

} /* EndFunction FlashErrorString */
#endif /* VERBOSE Definition */ 
 




/*******************************************************************************
Function:     ReturnType FlashProgram( udword udMode, udword udAddrOff,
   udword udNrOfElementsInArray, void *pArray )
Arguments:    udMode changes between programming modes
   udAddrOff is the address offset into the flash to be programmed
   udNrOfElementsInArray holds the number of elements (uCPUBusType) in the array.
   pArray is a void pointer to the array with the contents to be programmed.
Return Values:The function returns the following conditions:
   Flash_Success                
   Flash_AddressInvalid
	Flash_OperationTimeOut
	Flash_BlockProtected
	Flash_ProgramFailed
   Flash_VppInvalid
	Moreover, if the value returned isn't Flash_Success, the function
	fills the element 0 of udGeneralInfo field of eiErrorInfo structure with
	the first address where program failed.
Description: This function is used to program an array into the flash. It does
   not erase the flash first and will not produce proper results, if the block(s)
   are not erased first.
   Any errors are returned without any further attempts to program other addresses
   of the device. The function returns Flash_Success when all addresses have
   successfully been programmed.

   Note: Two program modes are available:
   - udMode = 0, Normal Program Mode
   The number of elements (udNumberOfElementsInArray) contained in pArray
   are programmed directly to the flash starting with udAddrOff.    
   - udMode = 1, Single Value Program Mode
   Only the first value of the pArray will be programmed to the flash
   starting from udAddrOff.
Pseudo Code:
   Step 1:  Check whether the data to be programmed are within the Flash memory 
   Step 2:  While there is more to be programmed and current program result is success...
   Step 3:  ...program next word...
   Step 4:  ...wait until the Program/Erase Controller is ready...
   Step 5:  ...check for any errors and if there is an error fill element 0 of 
            udGeneralInfo field of eiErrorInfo structure and clear Status Register.
   Step 6:  Return to read array mode the device
   Step 7:  Return the error condition
*******************************************************************************/
ReturnType FlashProgram(udword udMode, udword udAddrOff, udword udNrOfElementsInArray, void *pArray ) {
   ReturnType rRetVal = Flash_Success; /* Return Value: Initially optimistic */ 
   uCPUBusType *ucpArrayPointer;  /* Use an uCPUBusType to access the array */ 
   udword udLastAddrOff;  /* Holds the last offset to be programmed */ 
   udword udOffset;   /* Generic address offset */
   uCPUBusType ucStatus;  /* Holds the Status Register reads */ 
   
   if (udMode > 1)
		 return Flash_FunctionNotSupported;

   /* Step 1: Check whether the data to be programmed are within the Flash memory */
   if  ( (udAddrOff >= FLASH_SIZE) || (udNrOfElementsInArray > (FLASH_SIZE - udAddrOff)) ) {
      eiErrorInfo.udGeneralInfo[0] = udAddrOff;
      return Flash_AddressInvalid;
   } /* EndIf */

   udOffset = udAddrOff;
   udLastAddrOff = udAddrOff + udNrOfElementsInArray - 1;

   ucpArrayPointer = (uCPUBusType *) pArray;
   
   /* Step 2: While there is more to be programmed and current program result is success... */
   while ( (udOffset <= udLastAddrOff) && (rRetVal == Flash_Success) ) {
      FlashWrite( ANY_ADDR, CMD(0x0050) );  /* clear status register */
      
      /* Step 3: ...program next word... */
      FlashWrite( ANY_ADDR, CMD(0x0040) );
      FlashWrite( udOffset, *ucpArrayPointer );
      
      /* Step 4: ...wait until the Program/Erase Controller is ready... */
      FlashTimeOut(0);
      do {
         ucStatus = FlashRead(udOffset);
         if (FlashTimeOut(5) == Flash_OperationTimeOut) {
            FlashReset();
            return Flash_OperationTimeOut; 
         } /* EndIf */
      } while( (ucStatus & CMD(0x0080)) != CMD(0x0080) ); /* Wait until every Action is finished (StatusRegister Bit7 = 1) */ 


      /* Step 5:  ...check for any errors and if there is an error fill element 0 of 
           udGeneralInfo field of eiErrorInfo structure and clear Status Register...*/
      if( ucStatus & (0x001A) ) {
         if ( ucStatus & CMD(0x0008) )
            rRetVal = Flash_VppInvalid;
         else if ( ucStatus & CMD(0x0002) )
            rRetVal = Flash_BlockProtected;
         else
            rRetVal = Flash_ProgramFailed;
         FlashWrite( ANY_ADDR, CMD(0x0050) );   /* clear Status Register */

         eiErrorInfo.udGeneralInfo[0] = udOffset;  /* give error general info */
      } else
         rRetVal = Flash_Success;   

      if (udMode == 0) /* Decision between direct and modulo programming */
         ucpArrayPointer++;  
      udOffset++;  /* increment current program address */
   } /* EndWhile  Main Program Loop */
   
   /* Step 6:  Return to Read Array mode */
   FlashReset(); /* Read Array Command */

   /* Step 7: Return the error condition */
   return rRetVal;
} /* EndFunction FlashProgram */





/*******************************************************************************
Function:     void FlashProtectionRegisterProgram( udword 
              udProtectionRegisterAddrOff, uCPUBusType ucProtectionRegisterVal )
Arguments:
   udProtectionRegisterAddrOff is the Protection Register offset in the flash 
      where the Protection Register Program command can be issued.
   ucProtectionRegisterVal is the value to be programmed
Return Values:The function returns the following conditions:
   Flash_Success
   Flash_AddressInvalid
   Flash_OperationTimeOut
   Flash_ProgramFailed
   Flash_VppInvalid
   Flash_SpecificError. In this case:
      eiErrorInfo.sprRetVal = FlashSpec_ProtectionRegisterLocked
Description: This function is used to program a uCPUBusType to the appropriate 
   address offset of the Protection Register.
Pseudo Code:
   Step 1: Check whether the address offset to be read are within the Protection Register Memory Map
   Step 2: Protection Register Program setup 
   Step 3: Write the Protection register data in the Protection register address
   Step 4: Wait until the Program/Erase Controller is ready
   Step 5: Check for any errors
   Step 7: Return the error condition             
*******************************************************************************/
ReturnType FlashProtectionRegisterProgram( udword udProtectionRegisterAddrOff, 
                                 uCPUBusType ucProtectionRegisterVal ) {

   ReturnType rRetVal;         /* Return Value */   
   uCPUBusType ucStatus;       /* Holds the Status Register reads */
   
   /* Step 1: Check whether the address offset to be read are within the Protection Register Memory Map */
   if ( (udProtectionRegisterAddrOff < 0x80) || (udProtectionRegisterAddrOff > 0x8C) )
      return Flash_AddressInvalid;
   
   /* Step 2: Protection Register Program setup */
   FlashWrite( ANY_ADDR, CMD(0x00C0) );
   
   /* Step 3: Write the Protection register data in the Protection register address */
   FlashWrite( udProtectionRegisterAddrOff, ucProtectionRegisterVal );
   
   /* Step 4: Wait until the Program/Erase Controller is ready */
   FlashTimeOut(0);       /* Initialize TimeOut Counter */
   do {
      ucStatus = FlashRead( ANY_ADDR );
      if (FlashTimeOut(5) == Flash_OperationTimeOut) { 
         FlashReset( );
         return Flash_OperationTimeOut; 
      } /* EndIf */
   } while( (ucStatus & CMD(0x0080)) != CMD(0x0080) );
   /* Wait until every Action is finished (StatusRegister Bit7 = 1) */
   
   /* Step 5: Check for any errors */
   if( ucStatus & (0x001A) ) {
      if ( ucStatus & CMD(0x0008) )
         rRetVal = Flash_VppInvalid;
      else if ( ucStatus & CMD(0x0002) ) {
         rRetVal = Flash_SpecificError;
         eiErrorInfo.sprRetVal = FlashSpec_ProtectionRegisterLocked;
      } else
         rRetVal = Flash_ProgramFailed;
      FlashWrite( ANY_ADDR, CMD(0x0050) );   /* clear Status Register */
   } else
      rRetVal = Flash_Success;   
   
   /* Step 6: Return to Read Array mode */
   FlashReset( );
   
   /* Step 7: Return the error condition */ 
   return rRetVal; 
} /* EndFunction FlashProtectionRegisterProgram */



/*******************************************************************************
Function:      ReturnType FlashReadCfi( uword uwCfiFunc, uCPUBusType *ucpCfiValue )
Arguments:     uwCfiFunc is set to the offset of the CFI parameter to be read.
   The CFI value read from offset uwCfiFunc is passed back to the calling 
   function by *ucpCfiValue.
Return Values: 
   Flash_Success
   Flash_CfiFailed  
Description: This function checks whether the flash CFI is present and operable, 
   then reads the CFI value at the specified offset. The CFI value requested is
   then passed back to the calling function.   
Pseudo Code:
   Step 1: Send the Read CFI Instruction  
   Step 2: Check that the CFI interface is operable     
   Step 3: If CFI is operable read the required CFI value
   Step 4: Return the flash to Read Array mode 
*******************************************************************************/
ReturnType FlashReadCfi( uword uwCfiFunc, uCPUBusType *ucpCfiValue ) {
   ReturnType rRetVal = Flash_Success; /* Holds the return value */
   udword udCfiAddr;  /* Holds CFI address */
   
   /* Step 1: Send the Read CFI Instruction */
   FlashWrite( ANY_ADDR, CMD(0x0098) ); 
   
   /* Step 2: Check that the CFI interface is operable */
   if (  (FlashRead( 0x00000010 )  != CMD(0x0051) ) ||
         (FlashRead( 0x00000011 )  != CMD(0x0052) ) ||
         (FlashRead( 0x00000012 )  != CMD(0x0059) ) ) 
      rRetVal = Flash_CfiFailed;
   else {
      /* Step 3: Read the required CFI Info */
      udCfiAddr = (udword)uwCfiFunc;
      *ucpCfiValue = FlashRead( udCfiAddr & 0x000000FF );  
   } /* Endif */
   
   /* Step 4: Return to Read Array mode */
   FlashReset();
   
   return rRetVal;
} /* EndFunction FlashReadCfi */





/*******************************************************************************
Function:      ReturnType FlashReadDeviceId( uCPUBusType *ucpDeviceId )
Arguments:
   *ucpDeviceId: after the execution the variable contains: 
   -> The device ID of a single device if all flash chips give
      an identical result 
   -> The complete response of all devices in any other situation. 
   The device code for the part is:
      M28W160ECT: 88CEh
      M28W160ECB: 88CFh      
Return Values:
	Flash_Success         , if the Device ID(s) are equal or there is a single
                           flash chip
   Flash_CfiFailed       , if the CFI is not operable
	Flash_WrongType       , if the device command set code is not recognizable
Description: This function can be used to read the device code of the flash.
Pseudo Code:
   Step 1: Send the Read CFI Instruction
   Step 2: Check that the CFI interface is operable
   Step 3: Read Primary Algorithm Command Set Id
   Step 4: Read array command
   Step 5: Send the Read Electronic Signature instruction
   Step 6: Read the DeviceId
   Step 7: Return to read array mode
   Step 8: Check flash response (more flashes could give different results)
*******************************************************************************/
ReturnType FlashReadDeviceId(uCPUBusType *ucpDeviceId) {
   uCPUBusType ucAlgId;

   /* Step 1: Send the Read CFI Instruction */
   FlashWrite( 0x0055, CMD(0x0098) ); 

   /* Step 2: Check that the CFI interface is operable */
   if( ((FlashRead( 0x0010 ) & CMD(0x00FF)) != CMD(0x0051)) ||
       ((FlashRead( 0x0011 ) & CMD(0x00FF)) != CMD(0x0052)) ||
       ((FlashRead( 0x0012 ) & CMD(0x00FF)) != CMD(0x0059)) ) 
      return Flash_CfiFailed;

   /* Step 3: Read Primary Algorithm Command Set Id */
   ucAlgId = FlashRead( 0x0013 );

   if ( ucAlgId == CMD(0x0003) ) {
      /* Step 4a: Read array command (INTEL like) */
      FlashWrite( BlockOffset[0], CMD(0x00FF) );

      /* Step 5a: Send the Read Electronic Signature instruction */
      FlashWrite( BlockOffset[0], CMD(0x0090) );

      /* Step 6a: Read the DeviceId */
      *ucpDeviceId = FlashRead( BlockOffset[0] + 0x0001 ); /* A0 = 1, A1 = 0 */

      /* Step 7a: Read array command (INTEL like) */
      FlashWrite( BlockOffset[0], CMD(0x00FF) );
   } else if ( ucAlgId == CMD(0x0002) ) {
      /* Step 4b: Read array command (AMD like) */
      FlashWrite( BlockOffset[0], CMD(0x00F0) );
      
      /* Step 5b: Send the Auto Select instruction */ 
      FlashWrite( 0x0555, CMD(0x00AA) );	      /* 1st Cycle   */
      FlashWrite( 0x02AA, CMD(0x0055) );	      /* 2nd Cycle  */
      FlashWrite( 0x0555, CMD(0x0090) );	      /* 3rd Cycle  */
      
      /* Step 6b: Read the DeviceId  */ 
      *ucpDeviceId = FlashRead ( 0x0001 ); /* A1 =1, A2 =0 */    
      
      /* Step 7b: Read array command (AMD like) */
      FlashWrite( BlockOffset[0], CMD(0x00F0) );
   } else {
      return Flash_WrongType;
   } /* EndIf ucAlgId */

   /* Step 8: Check flash response (more flashes could give different results) */
   return FlashResponseIntegrityCheck(ucpDeviceId);
} /* EndFunction FlashReadDeviceId */




/*******************************************************************************
Function:      ReturnType FlashReadManufacturerCode( uCPUBusType *ucpManufacturerCode )
Arguments:
   *ucpManufacturerCode: after the execution the variable contains: 
   -> The Manufacturer Code of a single device if all flash chips give
      an identical result 
   -> The complete response of all devices in any other situation. 
Return Values:
	Flash_Success         , if the manufacturer code(s) are equal or there is a single
                           flash chip
   Flash_CfiFailed       , if the CFI is not operable
	Flash_WrongType       , if the device command set code is not recognizable
Description: This function can be used to read manufacturer code of the flash.
Pseudo Code:
   Step 1: Send the Read CFI Instruction
   Step 2: Check that the CFI interface is operable
   Step 3: Read Primary Algorithm Command Set Id
   Step 4: Read array command
   Step 5: Send the Read Electronic Signature instruction
   Step 6: Read the manufacturer code
   Step 7: Return to read array mode
   Step 8: Check flash response (more flashes could give different results)
*******************************************************************************/
ReturnType FlashReadManufacturerCode(uCPUBusType *ucpManufacturerCode) {
   uCPUBusType ucAlgId;

   /* Step 1: Send the Read CFI Instruction */
   FlashWrite( 0x0055, CMD(0x0098) ); 

   /* Step 2: Check that the CFI interface is operable */
   if( ((FlashRead( 0x0010 ) & CMD(0x00FF)) != CMD(0x0051)) ||
       ((FlashRead( 0x0011 ) & CMD(0x00FF)) != CMD(0x0052)) ||
       ((FlashRead( 0x0012 ) & CMD(0x00FF)) != CMD(0x0059)) ) 
      return Flash_CfiFailed;

   /* Step 3: Read Primary Algorithm Command Set Id */
   ucAlgId = FlashRead( 0x0013 );

   if ( ucAlgId == CMD(0x0003) ) {
      /* Step 4a: Read array command (INTEL like) */
      FlashWrite( BlockOffset[0], CMD(0x00FF) );

      /* Step 5a: Send the Read Electronic Signature instruction */
      FlashWrite( BlockOffset[0], CMD(0x0090) );

      /* Step 6a: Read the ManufacturerCode */
      *ucpManufacturerCode = FlashRead( BlockOffset[0] + 0x00 ); /* A0 = 0, A1 = 0 */

      /* Step 7a: Read array command (INTEL like) */
      FlashWrite( BlockOffset[0], CMD(0x00FF) );
   } else if ( ucAlgId == CMD(0x0002) ) {
      /* Step 4b: Read array command (AMD like) */
      FlashWrite( BlockOffset[0], CMD(0x00F0) );

      /* Step 5b: Send the Auto Select instruction */ 
      FlashWrite( 0x0555, CMD(0x00AA) );	      /* 1st Cycle   */
      FlashWrite( 0x02AA, CMD(0x0055) );	      /* 2nd Cycle  */
      FlashWrite( 0x0555, CMD(0x0090) );	      /* 3rd Cycle  */

      /* Step 6b: Read the ManufacturerCode  */ 
      *ucpManufacturerCode = FlashRead ( 0x0000 ); /* A1 =0, A2 =0 */

      /* Step 7b: Read array command (AMD like) */
      FlashWrite( BlockOffset[0], CMD(0x00F0) );
   } else {
      return Flash_WrongType;
   } /* EndIf ucAlgId */

   /* Step 8: Check flash response (more flashes could give different results) */
   return FlashResponseIntegrityCheck(ucpManufacturerCode);
} /* EndFunction FlashReadManufacturerCode */





/******************************************************************************* 
Function:
   ReturnType FlashReadProtectionRegister( udword udProtectionRegisterAddrOff, uCPUBusType *ucpValue )
Arguments:    
   udProtectionRegisterAddrOff is the offset where to read the Protection Register
   ucpValue: after execution, if success, *ucpValue contains the value read
Return Values:The function returns the following conditions: 
   Flash_Success
   Flash_AddressInvalid
Description:  This function can be used to read a location from the Protection 
   Register of the flash. 
Pseudo Code: 
   Step 1:  Check whether the address offset is within the Protection Register Memory Map
   Step 2:  Send the Read Electronic Signature instruction
   Step 3:  Read the required location from the Protection Register
   Step 4:  Return the bottom bank to Read Array mode 
*******************************************************************************/ 
ReturnType FlashReadProtectionRegister( udword udProtectionRegisterAddrOff, uCPUBusType *ucpValue ) { 
   
   /* Step 1: Check whether the address offset to be read are within the Protection Register Memory Map */
   if ( (udProtectionRegisterAddrOff < 0x80) || (udProtectionRegisterAddrOff > 0x8C) )
      return Flash_AddressInvalid;
   
   /* Step 2: Send the Read Electronic Signature instruction */
   FlashWrite( ANY_ADDR, CMD(0x0090) );
   
   /* Step 3: Read the required location from the Protection Register */ 
   *ucpValue = FlashRead( udProtectionRegisterAddrOff ); 
   
   /* Step 4: Return to Read Array mode */
   FlashReset();
   
   return Flash_Success; 
} /* EndFunction FlashReadProtectionRegister */ 





/*******************************************************************************
Function:     uCPUBusType FlashReadStatusRegister(void)
Arguments:    none 
Return Values:The status register value
Description:  This function can be used to read the status register in a bank.
Pseudo Code:
   Step 1:  Send the Read Status Register command
   Step 2:  Read the Status Register
   Step 3:  Return to Read Array mode
   Step 4:  Return status register value 
*******************************************************************************/
uCPUBusType FlashReadStatusRegister(void) {
   uCPUBusType ucStatus;
   
   /* Step 1: Send the Read Status Register command */
   FlashWrite( ANY_ADDR, CMD(0x0070) );
   
   /* Step 2: Read the Status Register */
   ucStatus = FlashRead( ANY_ADDR );
   
   /* Step 3: Return to Read Array mode */
   FlashReset( );
   
   /* Step 4: Return status register value */ 
   return ucStatus; 
} /* EndFunction FlashReadStatusRegister */






/*******************************************************************************
Function:        ReturnType FlashReset( void )
Arguments:       none
Return Values:
   Flash_Success
Description:     This function places the flash (all the banks) in the Read Array mode 
   described in the Data Sheet. In this mode the flash can be read   as normal
   memory.
Pseudo Code:
   Step 1: Write the read memory array command
   Step 2: Return Flash_Success
*******************************************************************************/
ReturnType FlashReset( void ) {
   /* Step 1: Write the read memory array command */ 
   FlashWrite( ANY_ADDR, CMD(0x00FF) );
   
   /* Step 2: Return Flash_Success */
   return Flash_Success; 
} /* EndFunction FlashReset */






/*******************************************************************************
Function:      ReturnType FlashResponseIntegrityCheck(uCPUBusType *ucpFlashResponse)
Arguments:     - ucpFlashResponse <parameter> + <return value> 
   The function returns a unique value in case one flash or an
   array of flashes return all the same value (Consistent Response = Flash_Success).
   In case an array of flashes returns different values the function returns the
   received response without any changes (Inconsistent Response = Flash_ResponseUnclear).

Return Value:  The function returns the following conditions:
   Flash_Success
   Flash_ResponseUnclear
               
Description:   This function is used to create one response in multi flash
   environments, instead of giving multiple answers of the single flash
   devices. 

   For example: Using a 32bit CPU and two 16bit Flash devices, the device Id
   would be directly read: 00170017h, because each device gives an answer
   within the range of the databus. In order to give a simple response
   like 00000017h in all possible configurations, this subroutine is used. 

   In case the two devices give different results for the device Id, the
   answer would then be: 00150017h. This allows debugging and helps to
   discover multiple flash configuration problems.
       
Pseudo Code: 
   Step 1:  Extract the first single flash response 
   Step 2:  Compare all next possible flash responses with the first one
   Step 3a: Return all flash responses in case of different values
   Step 3b: Return only the first single flash response in case of matching values 
*******************************************************************************/
 ReturnType FlashResponseIntegrityCheck(uCPUBusType *ucpFlashResponse) { 
   ubyte a; 
   union { 
      uCPUBusType ucFlashResponse; 
      ubyte       ubBytes[sizeof(uCPUBusType)]; 
   } FullResponse; 
   
   union { 
      uCPUBusType ucSingleResponse; 
      ubyte       ubBytes[FLASH_BIT_DEPTH/8]; 
   } SingleResponse; 
   
   SingleResponse.ucSingleResponse = 0; 
   FullResponse.ucFlashResponse = *ucpFlashResponse; 
   
   /* Step 1: Extract the first single flash response */ 
   memcpy(SingleResponse.ubBytes, FullResponse.ubBytes, FLASH_BIT_DEPTH/8); 
   
   /* Step 2: Compare all next possible flash responses with the first one */ 
   for (a = 0; a < sizeof(uCPUBusType); a += FLASH_BIT_DEPTH/8) { 
      if (memcmp (&FullResponse.ubBytes[a], SingleResponse.ubBytes, FLASH_BIT_DEPTH/8) != 0)   
      /* Step 3a: Return all flash responses in case of different values */ 
      return Flash_ResponseUnclear; 
   } /* Next a */                                                                  
   
   /* Step 3b: Return only the first single flash response in case of matching values */ 
   *ucpFlashResponse = SingleResponse.ucSingleResponse; 

   return Flash_Success; 
} /* EndFunction FlashResponseIntegrityCheck */ 



 


/******************************************************************************* 
Function:     ReturnType FlashResume( void ) 
Arguments:    none 
Description:  This function resume a suspended operation if needed.
Return Value: 
   Flash_Success
Pseudo Code: 
   Step 1: Check Status Register  
   Step 2: Resume operation, if needed 
*******************************************************************************/ 
ReturnType FlashResume( void ) { 
   uCPUBusType ucStatus; /* Status Register */
   
   /* Step 1: Check Status Register */ 
   FlashWrite( ANY_ADDR, CMD(0x0070) ); /* Read Status Register */
   ucStatus = FlashRead( ANY_ADDR );
   
   /* Step 2: Resume Erase, if needed */ 
   if ((ucStatus & CMD(0x0044)) != 0)
      FlashWrite( ANY_ADDR, CMD(0x00D0) );  /* Resume Command */
   return Flash_Success; 
} /* EndFunction FlashEraseResume */ 
 




/*******************************************************************************
Function:     ReturnType FlashSingleProgram( udword udAddrOff, uCPUBusType ucVal )
Arguments:    udAddrOff is the offset in the flash to write to.
              ucVal is the value to be written
Description: This function is used to write a single element to the flash.
Return Values:
   Flash_Success
   Flash_AddressInvalid
   Flash_BlockProtected  
   Flash_OperationTimeOut
   Flash_ProgramFailed
   Flash_VppInvalid
Pseudo Code: 
   Step 1:  Check whether the data to be programmed are 
            within the Flash memory space 
   Step 2:  Program the data
   Step 3:  Wait until the Program/Erase Controller is ready 
   Step 4:  Check for any errors 
   Step 5:  Return to Read Array mode 
   Step 6:  Return the error condition 
*******************************************************************************/ 
ReturnType FlashSingleProgram( udword udAddrOff, uCPUBusType ucVal ) { 
   ReturnType rRetVal; /* Return Value: Initially optimistic */ 
   uCPUBusType ucStatus;      /* Holds the Status Register reads */ 
   
   /* Step 1: Check whether the data to be programmed are are within the Flash memory space */ 
   if( udAddrOff >= FLASH_SIZE ) 
      return Flash_AddressInvalid; 
   
   FlashWrite( ANY_ADDR, CMD(0x0050) );  /* clear status register */
   /* NOTE ! CSR also clears bit 1 BPS as well as bits 3, 4 and 5 */ 
   
   /* Step 2: Program the data */ 
   FlashWrite( ANY_ADDR, CMD(0x0040) );
   FlashWrite( udAddrOff, ucVal );
   
   /* Step 3: Wait until Program/Erase Controller is ready */ 
   FlashTimeOut(0); /* Initialize TimeOut Counter */ 
   do {
      ucStatus = FlashRead(udAddrOff);
      if (FlashTimeOut(5) == Flash_OperationTimeOut) {
         FlashReset();
         return Flash_OperationTimeOut; 
      } /* EndIf */
   } while( (ucStatus & CMD(0x0080)) != CMD(0x0080) ); /* Wait until every Action is finished (StatusRegister Bit7 = 1) */ 
   
   /* Step 4: Check for any errors */ 
   if( ucStatus & (0x001A) ) {
      if ( ucStatus & CMD(0x0008) )
         rRetVal = Flash_VppInvalid;
      else if ( ucStatus & CMD(0x0002) )
         rRetVal = Flash_BlockProtected;
      else
         rRetVal = Flash_ProgramFailed;
      FlashWrite( ANY_ADDR, CMD(0x0050) );   /* clear Status Register */
   } else
      rRetVal = Flash_Success;   
   
   /* Step 5:  Return to Read Array mode */
   FlashReset();
   
   /* Step 6: Return the error condition */ 
   return rRetVal; 
} /* EndFunction FlashSingleProgram */  
 




/******************************************************************************* 
Function:     ReturnType FlashSuspend( void ) 
Arguments:    none 
Description:  This function suspend an erase or program operation. 
Return Values:
   Flash_Success
   Flash_NoOperationToSuspend
Pseudo Code: 
   Step 1: Clear Status Register 
   Step 2: Issue Suspend Command
   Step 3: Wait until the controller is ready
   Step 4: Check if the operation was effectively suspended
   Step 5: Return the device to read array mode
*******************************************************************************/ 
ReturnType FlashSuspend( void ) { 
   uCPUBusType  ucStatus; /* Status Register */
   
   /* Step 1: Clear Status Register */
   FlashWrite( ANY_ADDR, CMD(0x0050) );
   /* NOTE ! CSR also clears bit 1 BPS as well as bits 3, 4 and 5 */

    /* Step 2: Issue Suspend Command */
   FlashWrite( ANY_ADDR, CMD(0x00B0) );

   FlashWrite(ANY_ADDR, CMD(0x0070)); /* issue read status register command */
   
   /* Step 3: Wait until the controller is ready */ 
   FlashTimeOut(0); /* Initialize TimeOut Counter */ 
   do { 
      ucStatus = FlashRead(ANY_ADDR);
      if (FlashTimeOut(5) == Flash_OperationTimeOut) { 
         FlashReset();
         return Flash_OperationTimeOut;  
      } /* EndIf */ 
   } while( (ucStatus & CMD(0x0080)) != CMD(0x0080) ); /* Wait until the controller is free */ 
   
   /* Step 4: Check if the operation was effectively suspended */
   if ( (ucStatus & CMD(0x0044)) != 0 )
      return Flash_Success;
   else
      return Flash_NoOperationToSuspend;

   /* Step 5: Return the device to read array mode */
   FlashReset();
} /* EndFunction FlashSuspend */ 

               



/*******************************************************************************
Function:     ReturnType FlashTimeOut(udword udSeconds)

Arguments:    fSeconds holds the number of seconds before giving a TimeOut 
Return Value: The function returns the following conditions:  
   Flash_OperationTimeOut   
   Flash_OperationOngoing 

Example:   FlashTimeOut(0)  // Initializes the Timer

           While(1) {
              ...
              If (FlashTimeOut(5) == Flash_OperationTimeOut) break;
              // The loop is executed for 5 Seconds before leaving it
           } EndWhile

*******************************************************************************/
#ifdef TIME_H_EXISTS
/*-----------------------------------------------------------------------------
Description:   This function realizes a timeout for flash polling actions or
   other operations which would otherwise never return.
   The Routine uses the function clock() inside ANSI C library "time.h". 
-----------------------------------------------------------------------------*/
ReturnType FlashTimeOut(udword udSeconds){
   static clock_t clkReset,clkCount;
     
   if (udSeconds == 0) { /* Set Timeout to 0 */
      clkReset=clock();
   } /* EndIf */

   clkCount = clock() - clkReset;

   if (clkCount<(CLOCKS_PER_SEC*(clock_t)udSeconds))
      return Flash_OperationOngoing;
   else
	  return Flash_OperationTimeOut;
}/* EndFunction FlashTimeOut */

#else 
/*-----------------------------------------------------------------------------
Description:   This function realizes a timeout for flash polling actions or
   other operations which would otherwise never return.
   The Routine uses COUNT_FOR_A_SECOND which describes the performance of 
   the current Hardware. If I count in a loop to COUNT_FOR_A_SECOND
   I would reach 1 Second. Needs to be adopted to the current Hardware. 
-----------------------------------------------------------------------------*/
ReturnType FlashTimeOut(udword udSeconds) {

   static udword udCounter;

   if (udSeconds == 0) { /* Set Timeout to 0 */
      udCounter = 0;
   } /* EndIf */

   if (udCounter == (udSeconds * COUNT_FOR_A_SECOND)) {
      return Flash_OperationTimeOut;
   } else {
      udCounter++;
      return Flash_OperationOngoing;
   } /* Endif */

} /* EndFunction FlashTimeOut */
#endif /* TIME_H_EXISTS */

/******************************************************************************* 
 End of c2414.c
*******************************************************************************/ 


ReturnType MyFlashBlockErase(uBlockType blockNumber)
{
    FlashWrite(ANY_ADDR, 0x20);
    FlashWrite(BlockOffset[blockNumber], 0xD0); 
    
    uCPUBusType status;
    do {
        status = FlashRead(ANY_ADDR);
    } while ((status & 0x80) != 0x80);
    
    FlashWrite(ANY_ADDR, 0x50);
    
    status &= ~0x80;
    if ((status & 0x08) != 0)
        return Flash_VppInvalid;
    else if ((status & 0x30) != 0)
        return Flash_BlockEraseFailed;
    else if ((status & 1) != 0)
        return Flash_BlockProtected;
    return Flash_Success;
}
