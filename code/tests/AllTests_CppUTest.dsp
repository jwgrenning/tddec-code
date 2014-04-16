# Microsoft Developer Studio Project File - Name="AllTests_CppUTest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=AllTests_CppUTest - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AllTests_CppUTest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AllTests_CppUTest.mak" CFG="AllTests_CppUTest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AllTests_CppUTest - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "AllTests_CppUTest - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AllTests_CppUTest - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "AllTests_CppUTest - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /GX /ZI /Od /I "..\mocks" /I "..\include\util" /I "..\include\IO" /I "..\include\MyOS" /I "..\include\zune" /I "..\include\LedDriver" /I "..\include\HomeAutomation" /I "..\include\dvr" /I "$(CPP_U_TEST)/include" /I "$(CPP_U_TEST)/include/Platforms/VisualCpp" /I "../include/HomeAutomation" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 $(CPP_U_TEST)\lib\cpputest.lib ..\lib\ProductionCodeLib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /incremental:no

!ENDIF 

# Begin Target

# Name "AllTests_CppUTest - Win32 Release"
# Name "AllTests_CppUTest - Win32 Debug"
# Begin Group "Mocks"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\mocks\FakeMicroTime.c
# End Source File
# Begin Source File

SOURCE=..\mocks\FakeMicroTime.h
# End Source File
# Begin Source File

SOURCE=..\mocks\FakeMicroTimeTest.cpp
# End Source File
# Begin Source File

SOURCE=..\mocks\FormatOutputSpy.c
# End Source File
# Begin Source File

SOURCE=..\mocks\FormatOutputSpy.h
# End Source File
# Begin Source File

SOURCE=..\mocks\FormatOutputSpyTest.cpp
# End Source File
# Begin Source File

SOURCE=..\mocks\MockIO.c
# End Source File
# Begin Source File

SOURCE=..\mocks\MockIO.h
# End Source File
# Begin Source File

SOURCE=..\mocks\MockIOTest.cpp
# End Source File
# Begin Source File

SOURCE=..\mocks\RuntimeErrorStub.c
# End Source File
# Begin Source File

SOURCE=..\mocks\RuntimeErrorStub.h
# End Source File
# End Group
# Begin Group "dvr"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\dvr\DvRecorderTest.cpp
# End Source File
# End Group
# Begin Group "HomeAutomation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\HomeAutomation\FakeTimeService.c
# End Source File
# Begin Source File

SOURCE=.\HomeAutomation\FakeTimeService.h
# End Source File
# Begin Source File

SOURCE=.\HomeAutomation\FakeTimeServiceTest.cpp
# End Source File
# Begin Source File

SOURCE=.\HomeAutomation\LightControllerSpy.c
# End Source File
# Begin Source File

SOURCE=.\HomeAutomation\LightControllerSpy.h
# End Source File
# Begin Source File

SOURCE=.\HomeAutomation\LightControllerSpyTest.cpp
# End Source File
# Begin Source File

SOURCE=.\HomeAutomation\LightSchedulerTest.cpp
# End Source File
# End Group
# Begin Group "IO"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\IO\FlashTest.cpp
# End Source File
# Begin Source File

SOURCE=.\IO\LegacyFlashTest.cpp
# End Source File
# End Group
# Begin Group "LedDriver"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LedDriver\LedDriverTest.cpp
# End Source File
# End Group
# Begin Group "MyOS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MyOS\ThreadTest.cpp
# End Source File
# End Group
# Begin Group "studio"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\stdio\SprintfTest.cpp
# End Source File
# End Group
# Begin Group "util"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\util\CircularBufferPrintTest.cpp
# End Source File
# Begin Source File

SOURCE=.\util\CircularBufferTest.cpp
# End Source File
# End Group
# Begin Group "zune"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\zune\RtcTimeTest.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\AllTests.cpp
# End Source File
# End Target
# End Project
