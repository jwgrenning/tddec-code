/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
//- Copyright (c) 2010 James Grenning and Contributed to Unity Project
/* ==========================================
    Unity Project - A Test Framework for C
    Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
    [Released under MIT License. Please refer to license.txt for details]
========================================== */

#ifndef D_unity_output_Spy_H
#define D_unity_output_Spy_H

void UnityOutputCharSpy_Create(int s);
void UnityOutputCharSpy_Destroy();
int  UnityOutputCharSpy_OutputChar(int c);
const char * UnityOutputCharSpy_Get();
void UnityOutputCharSpy_Enable(int enable);

#endif
