/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
#ifndef D_c2414FlashReadAndWrite_H
#define D_c2414FlashReadAndWrite_H

#include "c2414.h"

uCPUBusType  FlashRead( udword udAddrOff );
void  FlashWrite( udword udAddrOff, uCPUBusType ucVal );

#endif

//Original code thanks to STMicroelectronics.

