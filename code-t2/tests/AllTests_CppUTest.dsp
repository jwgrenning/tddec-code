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
# ADD CPP /nologo /MDd /W3 /GX /ZI /Od /I "..\mocks" /I "..\mocks\IO" /I "..\include\util" /I "..\include\devices" /I "..\include\IO" /I "..\include\MyOS" /I "..\include\zune" /I "..\include\LedDriver" /I "..\include\HomeAutomation" /I "..\include\dvr" /I "$(CPP_U_TEST)/include" /I "$(CPP_U_TEST)/include/Platforms/VisualCpp" /I "../include/HomeAutomation" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /FD /GZ /c
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
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AllTests.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Mocks"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\mocks\FakeRandomMinute.c
# End Source File
# Begin Source File

SOURCE=..\mocks\FakeRandomMinute.h
# End Source File
# Begin Source File

SOURCE=..\mocks\FakeTimeService.c
# End Source File
# Begin Source File

SOURCE=..\mocks\FakeTimeService.h
# End Source File
# Begin Source File

SOURCE=..\mocks\FakeTimeServiceTest.cpp
# End Source File
# Begin Source File

SOURCE=..\mocks\LightDriverSpy.c
# End Source File
# Begin Source File

SOURCE=..\mocks\LightDriverSpy.h
# End Source File
# Begin Source File

SOURCE=..\mocks\LightDriverSpyTest.cpp
# End Source File
# End Group
# Begin Group "HomeAutomation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\HomeAutomation\LightControllerTest.cpp
# End Source File
# Begin Source File

SOURCE=.\HomeAutomation\LightSchedulerRandomizeTest.cpp
# End Source File
# Begin Source File

SOURCE=.\HomeAutomation\LightSchedulerTest.cpp
# End Source File
# Begin Source File

SOURCE=.\HomeAutomation\RandomMinuteTest.cpp
# End Source File
# End Group
# Begin Group "Devices"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\devices\AcmeWirelessLightDriverTest.cpp
# End Source File
# Begin Source File

SOURCE=.\devices\LightDriverTest.cpp
# End Source File
# Begin Source File

SOURCE=.\devices\MemMappedLightDriverTest.cpp
# End Source File
# Begin Source File

SOURCE=.\devices\X10LightDriverTest.cpp
# End Source File
# End Group
# Begin Group "Util"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\util\TimeTest.cpp
# End Source File
# End Group
# End Target
# End Project
