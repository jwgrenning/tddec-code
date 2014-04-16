/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
/***************** Header File for STFL-I Flash Memory Driver ******************

  Filename:    c2414.h
   Description: Header file for c2414.c
                Consult also the C file for more details.

   Version:     $Id: c2414.h,v 1.0 2006/09/01 
   Author:     Ze-Yu He, MSAC,STMicroelectronics, Shanghai (China)
               Wiley Xu, MSAC,STMicroelectronics, Shanghai (China)
               Echo Chen,MSAC,STMicroelectronics, Beijing  (China)
   Copyright (c) 2006 STMicroelectronics.

   THIS PROGRAM IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,EITHER
   EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTY
   OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE ENTIRE RISK
   AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU. SHOULD THE
   PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,
   REPAIR OR CORRECTION.
********************************************************************************

   Version History.

   Ver.   Date        Comments

   0.0    2006/08/25  Initial Release of the software (Alpha)   
   1.0    2006/09/01  Qualified Release of the software
  

*******************************************************************************/


/*************** User Change Area *******************************************

   This section is meant to give all the opportunities to customize the
   SW Drivers according to the requirements of hardware and flash configuration.
   It is possible to choose flash start address, CPU Bitdepth, number of flash
   chips, hardware configuration and performance data (TimeOut Info).

   The options are listed and explained below:

   ********* Data Types *********
   The source code defines hardware independent datatypes assuming the
   compiler implements the numerical types as

   unsigned char    8 bits (defined as ubyte)
   char             8 bits (defined as byte)  
   unsigned short  16 bits (defined as uword)
   short           16 bits (defined as word)
   unsigned int    32 bits (defined as udword)
   int             32 bits (defined as dword)
 
   In case the compiler does not support the currently used numerical types,
   they can be easily changed just once here in the user area of the headerfile.
   The data types are consequently referenced in the source code as (u)byte,
   (u)word and (u)dword. No other data types like 'CHAR','SHORT','INT','LONG'
   directly used in the code.


   ********* Flash Type *********
   This driver supports the following Flash Types

   M28W160ECT   16bit, 16Mbit Flash  #define USE_M28W160ECT
   M28W160ECB   16bit, 16Mbit Flash  #define USE_M28W160ECB  

   ********* Base Address *********
   The start address where the flash memory chips are "visible" within
   the memory of the CPU is called the BASE_ADDR. This address must be
   set according to the current system. This value is used by FlashRead()
   FlashWrite(). Some applications which require a more complicated
   FlashRead() or FlashWrite() may not use BASE_ADDR.


   ********* Flash and Board Configuration *********
   The driver supports also different configurations of the flash chips
   on the board. In each configuration a new data Type called
   'uCPUBusType' is defined to match the current CPU data bus width.
   This data type is then used for all accesses to the memory.

   The different options (defines) are explained below:
   
   - USE_16BIT_CPU_ACCESSING_1_16BIT_FLASH
   Using this define enables a configuration consisting of an environment
   containing a CPU with 16bit databus and 1 16bit flash chip connected
   to it. Standard Configuration

   - USE_32BIT_CPU_ACCESSING_2_16BIT_FLASH
   Using this define enables a configuration consisting of an environment
   containing a CPU with 32bit databus and 2 16bit flash chips connected
   to it.

   ********* TimeOut *********
   There are timeouts implemented in the loops of the code, in order
   to enable a timeout for operations that would otherwise never terminate.
   There are two possibilities:

   1) The ANSI Library functions declared in 'time.h' exist
  
      If the current compiler supports 'time.h' the define statement
      TIME_H_EXISTS should be activated. This makes sure that
      the performance of the current evaluation HW does not change
      the timeout settings. 

   2) or they are not available (COUNT_FOR_A_SECOND)

      If the current compiler does not support 'time.h', the define
      statement can not be used. To overcome this constraint the value
      COUNT_FOR_A_SECOND has to be defined in order to create a one
      second delay. For example, if 100000 repetitions of a loop are
      needed, to give a time delay of one second, then
      COUNT_FOR_A_SECOND should have the value 100000.

      Note: This delay is HW (Performance) dependent and needs,
      therefore, to be updated with every new HW.

      This driver has been tested with a certain configuration and other
      target platforms may have other performance data, therefore, the
      value may have to be changed.
      
      It is up to the user to implement this value to avoid the code
      timing out too early instead of completing correctly.


   ********* Additional Routines *********
   The drivers provides also a subroutine which displays the full
   error message instead of just an error number.

   The define statement VERBOSE activates additional Routines.
   Currently it activates the function FlashErrorStr()

   No further changes should be necessary. 

*****************************************************************************/

#ifndef __c2414__H__
#define __c2414__H__

typedef unsigned char  ubyte; /* All HW dependent Basic Data Types */      
typedef          char   byte;  
typedef unsigned short uword;      
typedef          short  word;      
typedef unsigned int  udword;      
typedef          int   dword;      


#define USE_M28W160ECT
/* Possible Values: USE_M28W160ECT
                    USE_M28W160ECB */

#define BASE_ADDR ((volatile uCPUBusType*)0x00000000)
/* BASE_ADDR is the base or start address of the flash, see the functions
   FlashRead and FlashWrite(). Some applications which require a more
   complicated FlashRead() or FlashWrite() may not use BASE_ADDR */

#define USE_16BIT_CPU_ACCESSING_1_16BIT_FLASH /* Current PCB Info */
/* Possible Values: USE_16BIT_CPU_ACCESSING_1_16BIT_FLASH
                    USE_32BIT_CPU_ACCESSING_2_16BIT_FLASH */

/*#define TIME_H_EXISTS*/  /* set this macro if C-library "time.h" is supported */
/* Possible Values: TIME_H_EXISTS 
                    - no define - TIME_H_EXISTS */
 
#ifndef TIME_H_EXISTS
  #define COUNT_FOR_A_SECOND 432666    /* Timer Usage */
#endif

#define VERBOSE /* Activates additional Routines */
/* Currently the Error String Definition */

/********************** End of User Change Area *****************************/

/*****************************************************************************
HW Structure Info, Usage of the Flash Memory (Circuitry)
*****************************************************************************/

#ifdef USE_16BIT_CPU_ACCESSING_1_16BIT_FLASH
   typedef uword uCPUBusType;
   typedef  word  CPUBusType;
   #define FLASH_BIT_DEPTH 16
   #define HEX "04Xh"
   #define CMD(A) (A)
   #define CONFIGURATION_DEFINED
#endif                                       

#ifdef USE_32BIT_CPU_ACCESSING_2_16BIT_FLASH
   typedef udword uCPUBusType;
   typedef  dword  CPUBusType;
   #define FLASH_BIT_DEPTH 16
   #define HEX "08Xh"
   #define CMD(A) (A+(A<<16))
   #define CONFIGURATION_DEFINED
#endif

/******************************************************************************* 
     Specific Return Codes 
*******************************************************************************/ 
typedef enum {
   FlashSpec_BlockLockDownFailed,
   FlashSpec_BlockLockedDown,
   FlashSpec_BlockUnlockedDown,
   FlashSpec_ProtectionRegisterLocked
 } SpecificReturnType;

/******************************************************************************* 
     CONFIGURATION CHECK
*******************************************************************************/ 
 
#ifndef CONFIGURATION_DEFINED 
#error  User Change Area Error: PCB Info uncorrect Check the USE_xxBIT_CPU_ACCESSING_n_yyBIT_FLASH Value
#endif
 
/******************************************************************************* 
     DERIVED DATATYPES
*******************************************************************************/ 

/******** CommandsType ********/ 

typedef enum { 
   BankErase,
   BankReset,
   BankResume,
   BankSuspend,
   BlockErase,
   BlockProtect, 
   BlockUnprotect, 
   CheckBlockProtection, 
   CheckCompatibility, 
   ChipErase, 
   ChipUnprotect, 
   GroupProtect,
   Program, 
   Read, 
   ReadCfi, 
   ReadDeviceId, 
   ReadManufacturerCode, 
   Reset, 
   Resume, 
   SingleProgram, 
   Suspend, 
   Write  
} CommandType; 


/******** ReturnType ********/ 

typedef enum { 
   Flash_AddressInvalid, 
   Flash_BankEraseFailed,
   Flash_BlockEraseFailed, 
   Flash_BlockNrInvalid, 
   Flash_BlockProtected, 
   Flash_BlockProtectFailed, 
   Flash_BlockProtectionUnclear, 
   Flash_BlockUnprotected, 
   Flash_BlockUnprotectFailed, 
   Flash_CfiFailed, 
   Flash_ChipEraseFailed, 
   Flash_ChipUnprotectFailed, 
   Flash_FunctionNotSupported,
   Flash_GroupProtectFailed, 
   Flash_NoInformationAvailable,
   Flash_NoOperationToSuspend,
   Flash_OperationOngoing, 
   Flash_OperationTimeOut, 
   Flash_ProgramFailed, 
   Flash_ResponseUnclear, 
   Flash_SpecificError,
   Flash_Success, 
   Flash_VppInvalid, 
   Flash_WrongType,  
 } ReturnType;  
 
/******** BlockType ********/ 

typedef uword      uBlockType; 
 
/******** ParameterType ********/ 
 
typedef union { 
    /**** BankErase Parameters ****/ 
    struct { 
      uBlockType ublBlockNr;
      ReturnType *rpResults; 
    } BankErase; 
     
    /**** BankReset Parameters ****/ 
    struct { 
      udword udBankAddrOff; 
    } BankReset;

    /**** BankResume Parameters ****/ 
    struct { 
      udword udAddrOff; 
    } BankResume;
     
    /**** BankSuspend Parameters ****/ 
    struct { 
      udword udAddrOff; 
    } BankSuspend;

    /**** BlockErase Parameters ****/ 
    struct { 
      uBlockType ublBlockNr; 
    } BlockErase; 

    /**** BlockProtect Parameters ****/ 
    struct { 
      uBlockType ublBlockNr; 
    } BlockProtect; 
 
    /**** BlockUnprotect Parameters ****/ 
    struct { 
      uBlockType ublBlockNr; 
    } BlockUnprotect; 
 
    /**** CheckBlockProtection Parameters ****/ 
    struct { 
      uBlockType ublBlockNr; 
    } CheckBlockProtection; 
 
    /**** CheckCompatibility has no parameters ****/ 
 
    /**** ChipErase Parameters ****/ 
    struct { 
      ReturnType *rpResults; 
    } ChipErase;  
     
    /**** ChipUnprotect Parameters ****/ 
    struct { 
      ReturnType *rpResults; 
    } ChipUnprotect;  

    /**** GroupProtect Parameters ****/ 
    struct { 
      uBlockType ublBlockNr; 
    } GroupProtect;  

    /**** Program Parameters ****/ 
    struct { 
      udword udAddrOff; 
      udword udNrOfElementsInArray;         
        void *pArray; 
      udword udMode;        
    } Program; 

    /**** Read Parameters ****/ 
    struct { 
      udword  udAddrOff; 
      uCPUBusType ucValue;  
    } Read; 
 
    /**** ReadCfi Parameters ****/ 
    struct { 
      uword  uwCfiFunc; 
      uCPUBusType ucCfiValue;        
    } ReadCfi; 

    /**** ReadDeviceId Parameters ****/ 
    struct { 
      uCPUBusType ucDeviceId; 
    } ReadDeviceId; 
 
    /**** ReadManufacturerCode Parameters ****/ 
    struct { 
      uCPUBusType ucManufacturerCode; 
    } ReadManufacturerCode; 

    /**** Reset has no parameters ****/ 

    /**** Resume has no parameters ****/ 
    
    /**** SingleProgram Parameters ****/ 
    struct { 
      udword udAddrOff; 
      uCPUBusType ucValue; 
   } SingleProgram;     
    
    /**** Suspend has no parameters ****/ 
     
    /**** Write Parameters ****/ 
    struct { 
      udword udAddrOff; 
      uCPUBusType ucValue; 
   } Write;     
 
} ParameterType; 
 
/******** ErrorInfoType ********/ 

typedef struct {
 SpecificReturnType sprRetVal;
 udword             udGeneralInfo[4];
} ErrorInfoType;

/******************************************************************************
    Global variables
*******************************************************************************/ 
extern ErrorInfoType eiErrorInfo;



/******************************************************************************
    Standard functions
*******************************************************************************/ 
  ReturnType  Flash( CommandType cmdCommand, ParameterType *fp );
  ReturnType  FlashBankErase( uBlockType ublBlockNr, ReturnType  *rpResults );
        void  FlashBankReset( udword udBankAddrOff );
  ReturnType  FlashBankResume( udword udBankAddrOff );
  ReturnType  FlashBankSuspend( udword udBankAddrOff ); 
  ReturnType  FlashBlockErase( uBlockType ublBlockNr );
  ReturnType  MyFlashBlockErase( uBlockType ublBlockNr );
  ReturnType  FlashBlockProtect( uBlockType ublBlockNr );
  ReturnType  FlashBlockUnprotect( uBlockType ublBlockNr );
  ReturnType  FlashCheckBlockProtection( uBlockType ublBlockNr );
  ReturnType  FlashCheckCompatibility( void );
  ReturnType  FlashChipErase( ReturnType  *rpResults );
  ReturnType  FlashChipUnprotect( ReturnType  *rpResults );
  ReturnType  FlashGroupProtect( uBlockType ublBlockNr );
  ReturnType  FlashProgram( udword udMode, udword udAddrOff, udword udNrOfElementsInArray, void *pArray );
  ReturnType  FlashReadCfi( uword uwCFIFunc, uCPUBusType *ucpCFIValue );
  ReturnType  FlashReadDeviceId( uCPUBusType *ucpDeviceID);
  ReturnType  FlashReadManufacturerCode( uCPUBusType *ucpManufacturerCode);
  ReturnType  FlashReset( void );
  ReturnType  FlashResume( void );
  ReturnType  FlashSingleProgram( udword udAddrOff, uCPUBusType ucVal );
  ReturnType  FlashSuspend( void );


/******************************************************************************
    Utility functions
*******************************************************************************/ 
#ifdef VERBOSE
        byte *FlashErrorStr( ReturnType rErrNum );
#endif
  ReturnType  FlashResponseIntegrityCheck( uCPUBusType *ucpFlashResponse );
  ReturnType  FlashTimeOut( udword udSeconds );


/*******************************************************************************
Device Constants
*******************************************************************************/

#define MANUFACTURER_ST (0x0020)   /* ST Manufacturer Code is 0x20 */
#define ANY_ADDR (0x0)             /* Any address offset within the Flash Memory will do */

#ifdef USE_M28W160ECT                  /* The M28W60ECT device */
   #define EXPECTED_DEVICE (0x88CE)    /* Device code for the M28W160ECT */
   #define FLASH_SIZE (0x00100000)     /* maximum number of addresses */
   #define FLASH_WRITE_BUFFER_SIZE 1   /* Write Buffer in Words */  
   #define FLASH_MWA 1                 /* Minimum Write Access  */

   static const udword BlockOffset[] = {
      0x0FF000,  /* Start offset of block 0     */
      0x0FE000,  /* Start offset of block 1     */
      0x0FD000,  /* Start offset of block 2     */
      0x0FC000,  /* Start offset of block 3     */
      0x0FB000,  /* Start offset of block 4     */
      0x0FA000,  /* Start offset of block 5     */
      0x0F9000,  /* Start offset of block 6     */
      0x0F8000,  /* Start offset of block 7     */
      0x0F0000,  /* Start offset of block 8     */
      0x0E8000,  /* Start offset of block 9     */
      0x0E0000,  /* Start offset of block 10    */
      0x0D8000,  /* Start offset of block 11    */
      0x0D0000,  /* Start offset of block 12    */
      0x0C8000,  /* Start offset of block 13    */
      0x0C0000,  /* Start offset of block 14    */
      0x0B8000,  /* Start offset of block 15    */
      0x0B0000,  /* Start offset of block 16    */
      0x0A8000,  /* Start offset of block 17    */
      0x0A0000,  /* Start offset of block 18    */
      0x098000,  /* Start offset of block 19    */
      0x090000,  /* Start offset of block 20    */
      0x088000,  /* Start offset of block 21    */
      0x080000,  /* Start offset of block 22    */
      0x078000,  /* Start offset of block 23    */
      0x070000,  /* Start offset of block 24    */
      0x068000,  /* Start offset of block 25    */
      0x060000,  /* Start offset of block 26    */
      0x058000,  /* Start offset of block 27    */
      0x050000,  /* Start offset of block 28    */
      0x048000,  /* Start offset of block 29    */
      0x040000,  /* Start offset of block 30    */
      0x038000,  /* Start offset of block 31    */
      0x030000,  /* Start offset of block 32    */
      0x028000,  /* Start offset of block 33    */
      0x020000,  /* Start offset of block 34    */
      0x018000,  /* Start offset of block 35    */
      0x010000,  /* Start offset of block 36    */
      0x008000,  /* Start offset of block 37    */
      0x000000,  /* Start offset of block 38    */      
   }; /* EndArray BlockOffset[] */
#endif /* USE_M28W160ECT */

#ifdef USE_M28W160ECB
   #define EXPECTED_DEVICE (0x88CF)    /* Device code for the M28W160ECB */
   #define FLASH_SIZE (0x00100000)     /* Total device size in Words */
   #define FLASH_WRITE_BUFFER_SIZE 1   /* Write Buffer in Words */  
   #define FLASH_MWA 1                 /* Minimum Write Access  */

   static const udword BlockOffset[] = {
      0x000000,  /* Start offset of block 0  */
      0x001000,  /* Start offset of block 1  */
      0x002000,  /* Start offset of block 2  */
      0x003000,  /* Start offset of block 3  */
      0x004000,  /* Start offset of block 4  */
      0x005000,  /* Start offset of block 5  */
      0x006000,  /* Start offset of block 6  */
      0x007000,  /* Start offset of block 7  */
      0x008000,  /* Start offset of block 8  */
      0x010000,  /* Start offset of block 9  */
      0x018000,  /* Start offset of block 10 */
      0x020000,  /* Start offset of block 11 */
      0x028000,  /* Start offset of block 12 */
      0x030000,  /* Start offset of block 13 */
      0x038000,  /* Start offset of block 14 */
      0x040000,  /* Start offset of block 15 */
      0x048000,  /* Start offset of block 16 */
      0x050000,  /* Start offset of block 17 */
      0x058000,  /* Start offset of block 18 */
      0x060000,  /* Start offset of block 19 */
      0x068000,  /* Start offset of block 20 */
      0x070000,  /* Start offset of block 21 */
      0x078000,  /* Start offset of block 22 */
      0x080000,  /* Start offset of block 23 */
      0x088000,  /* Start offset of block 24 */
      0x090000,  /* Start offset of block 25 */
      0x098000,  /* Start offset of block 26 */
      0x0A0000,  /* Start offset of block 27 */
      0x0A8000,  /* Start offset of block 28 */
      0x0B0000,  /* Start offset of block 29 */
      0x0B8000,  /* Start offset of block 30 */
      0x0C0000,  /* Start offset of block 31 */
      0x0C8000,  /* Start offset of block 32 */
      0x0D0000,  /* Start offset of block 33 */
      0x0D8000,  /* Start offset of block 34 */
      0x0E0000,  /* Start offset of block 35 */
      0x0E8000,  /* Start offset of block 36 */
      0x0F0000,  /* Start offset of block 37 */
      0x0F8000,  /* Start offset of block 38 */      
   }; /* EndArray BlockOffset[] */   
#endif /* USE_M28W160ECB */



#define NUM_BLOCKS (sizeof(BlockOffset)/sizeof(BlockOffset[0]))

/*******************************************************************************
Specific Function Prototypes
*******************************************************************************/
 ReturnType FlashBlockLockDown(uBlockType ublBlockNr);
 ReturnType FlashCheckBlockLockDownStatus( uBlockType ublBlockNr );
       void FlashClearStatusRegister( void );
 ReturnType FlashDoubleProgram( udword udAddrOff, uCPUBusType ucVal1, uCPUBusType ucVal2 );
 ReturnType FlashProtectionRegisterProgram( udword udProtectionRegisterAddrOff, 
                  uCPUBusType ucProtectionRegisterVal );
ReturnType FlashReadProtectionRegister( udword udProtectionRegisterAddrOff,
                           uCPUBusType *ucpValue );
uCPUBusType FlashReadStatusRegister(void);

/******************************************************************************* 
List of Errors and Return values, Explanations and Help. 
******************************************************************************** 

Error Name:   Flash_AddressInvalid 
Description:  The address offset given is out of the range of the flash device. 
Solution:     Check the address offset whether it is in the valid range of the 
              flash device. 
******************************************************************************** 
 
Error Name:   Flash_BankEraseFailed 
Description:  The bank erase command did not finish successfully. 
Solution:     Check that Vpp is not floating. Try erasing the block again. If 
              this fails once more, the device may be faulty and needs to be replaced. 
******************************************************************************** 
 
Error Name:   Flash_BlockEraseFailed 
Description:  The block erase command did not finish successfully. 
Solution:     Check that Vpp is not floating. Try erasing the block again. If 
              this fails once more, the device may be faulty and needs to be replaced. 
******************************************************************************** 
 
Error Name:   Flash_BlockNrInvalid 
Note:         This is not a flash problem. 
Description:  A selection for a block has been made (Parameter), which is not 
              within the valid range. Valid block numbers are from 0 to NUM_BLOCKS-1. 
Solution:     Check that the block number given is in the valid range. 
******************************************************************************** 
 
Error Name:   Flash_BlockProtected               
Description:  The user has attempted to erase, program or protect a block of  
              the flash that is protected. The operation failed because the block in  
              question is protected. This message appears also after checking the pro- 
              protection status of a block.  
Solutions:    Choose another (unprotected) block for erasing or programming. 
              Alternatively change the block protection status of the current block. 
              (see Datasheet for more details). In the case of the user protecting a block 
              that is already protected, this warning notifies the user that the command 
              had no effect.  
******************************************************************************** 

Error Name:   Flash_BlockProtectFailed 
Description:  This error return value indicates that a block protect command did 
              not finish successfully. 
Solution:     Check that Vpp is not floating but is tied to a valid voltage. Try 
              the command again. If it fails a second time then the block cannot be  
              protected and it may be necessary to replace the device. 
******************************************************************************** 
 
Error Name:   Flash_BlockProtectionUnclear 
Description:  The user has attempted to erase, program or protect a block of  
              the flash which did not return a proper protection status. The operation 
              has been cancelled. 
Solutions:    This should only happen in configurations with more than one 
              flash device. If the response of each device does not match, this return code 
              is given. Mostly that means the usage of not properly initialized flash 
              parts.   
******************************************************************************** 
 
Error Name:   Flash_BlockUnprotected 
Description:  This message appears after checking the block protection status.  
              This block is ready to get erased, programmed or protected.  
******************************************************************************** 

Error Name:   Flash_BlockUnprotectFailed 
Description:  This error return value indicates that a block unprotect command did 
              not finish successfully. 
Solution:     Check that Vpp is not floating but is tied to a valid voltage. Try 
              the command again. If it fails a second time then the block cannot be  
              unprotected and it may be necessary to replace the device. 
******************************************************************************** 
    
Error Name:   Flash_CfiFailed 
Description:  This return value indicates that a Common Flash Interface (CFI) 
              read access was unsuccessful. 
Solution:     Try to read the Identifier Codes (Manufacture ID, Device ID) 
              if these commands fail as well it is likely that the device is faulty or 
              the interface to the flash is not correct. 
********************************************************************************    
 
Error Name:   Flash_ChipEraseFailed 
Description:  This message indicates that the erasure of the whole device has  
              failed. 
Solution:     Investigate this failure further by checking the results 
              array (parameter), where all blocks and their erasure results are listed. What 
              is more, try to erase each block individually. If erasing a single block still 
              causes failure, then the Flash needs to be replaced. 
******************************************************************************** 
 
Error Name:   Flash_ChipUnprotectFailed 
Description:  This return value indicates that the chip unprotect command  
              was unsuccessful. 
Solution:     Check that Vpp is not floating but is tied to a valid voltage. Try 
              the command again. If it fails a second time then it is likely that the  
              device cannot be unprotected and will need to be replaced. 
******************************************************************************** 
 
Return Name:  Flash_FunctionNotSupported 
Description:  The user has attempted to make use of functionality not 
              available on this flash device (and thus not provided by the software 
              drivers).   
Solution:     This can happen after changing Flash SW Drivers in existing 
              environments. For example an application tries to use 
              functionality which is then no longer provided with a new device. 
******************************************************************************** 

Error Name:   Flash_GroupProtectFailed 
Description:  This error return value indicates that a group protect command did 
              not finish successfully. 
Solution:     Check that Vpp is not floating but is tied to a valid voltage. Try 
              the command again. If it fails a second time then the group cannot be  
              protected and it may be necessary to replace the device.
******************************************************************************** 
 
Return Name:  Flash_NoInformationAvailable
Description:  The system can't give any additional information about the error.
Solution:     None
******************************************************************************** 
 
Error Name:   Flash_NoOperationToSuspend
Description:  This message is returned by a suspend operation if there isn't 
              operation to suspend (i.e. the program/erase controller is inactive).
******************************************************************************** 
 
Error Name:   Flash_OperationOngoing 
Description:  This message is one of two messages which are given by the TimeOut 
              subroutine. That means the flash operation still operates within the defined 
              time frame.  
******************************************************************************** 
 
Error Name:   Flash_OperationTimeOut 
Description:  The Program/Erase Controller algorithm could not finish an 
              operation successfully. It should have set bit 7 of the status register from 
              0 to 1, but that did not happen within a predefined time. The program execution 
              has been, therefore, cancelled by a timeout. This may be because the device 
              is damaged.  
Solution:     Try the previous command again. If it fails a second time then it is 
              likely that the device will need to be replaced. 
******************************************************************************** 
 
Error Name:   Flash_ProgramFailed 
Description:  The value that should be programmed has not been written correctly 
              to the flash. 
Solutions:    Make sure that the block which is supposed to receive the value 
              was erased successuly before programming. Try erasing the block and programming 
              the value again. If it fails again then the device may be faulty. 
******************************************************************************** 
 
Error Name:   Flash_ResponseUnclear 
Description:  This message appears in multiple flash configurations, if  the single  
              flash responses are different and, therefore, a sensible reaction of the SW  
              driver is not possible. 
Solutions:    Check all the devices currently used and make sure they are all  
              working properly. Use only equal devices in multiple configurations. If it 
              fails again then the devices may be faulty and need to be replaced. 
******************************************************************************** 

Error Name:   Flash_SpecificError
Description:  The function makes an error depending on the device.
              More information about the error are available into the ErrorInfo variable.
Solutions:    See SpecificReturnType remarks
******************************************************************************** 

Return Name:  Flash_Success 
Description:  This value indicates that the flash command has executed 
              correctly. 
******************************************************************************** 

Error Name:   Flash_VppInvalid  
Description:  A Program or a Block Erase has been attempted with the Vpp supply 
              voltage outside the allowed ranges. This command had no effect since an  
              invalid Vpp has the effect of protecting the whole of the flash device. 
Solution:     The (hardware) configuration of Vpp will need to be modified to  
              make programming or erasing the device possible.  
*******************************************************************************

Error Name:   Flash_WrongType 
Description:  This message appears if the Manufacture and Device ID read from 
              the current flash device do not match with the expected identifier codes. 
              That means the source code is not explicitely written for the currently 
              used flash chip. It may work, but it cannot be guaranteed. 
Solutions:    Use a different flash chip with the target hardware or contact 
              STMicroelectronics for a different source code library. 
********************************************************************************/

/*******************************************************************************
List of Specific Errors and Return values, Explanations and Help.
*******************************************************************************

Error Name:   FlashSpec_BlockLockDownFailed 
Description:  This error return value indicates that a block lock-down command did 
              not finish successfully. 
Solution:     Try the command again. If it fails a second time then the block cannot be  
              locked-down and it may be necessary to replace the device. 
********************************************************************************

Error Name:   FlashSpec_BlockLockedDown 
Description:  This message appears also after checking the lock-down status of a block.  
Solutions:    none.  
********************************************************************************

Error Name:   FlashSpec_BlockUnlockedDown 
Description:  This message appears also after checking the lock-down status of a block.  
Solutions:    none.  
********************************************************************************

Error Name:   FlashSpec_ProtectionRegisterLocked 
Description:  The user has attempted to write to a locked segment into  Protection Register.
Solutions:    Choose another (unlocked) segment for programming.
********************************************************************************/

/* In order to avoid a repeated usage of the header file */
#endif  /* __c2414__H__ */

/*******************************************************************************  
     End of c2414.h
********************************************************************************/
