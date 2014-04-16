# Microsoft Developer Studio Project File - Name="ApplicationLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ApplicationLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ApplicationLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ApplicationLib.mak" CFG="ApplicationLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ApplicationLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ApplicationLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ApplicationLib - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "ApplicationLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /GX /ZI /Od /I "../mocks" /I "../include/util" /I "../include/devices" /I "../include/HomeAutomation" /I "../platform/VisualStudio" /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D malloc=cpputest_malloc /D free=cpputest_free /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "ApplicationLib - Win32 Release"
# Name "ApplicationLib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\devices\AcmeWirelessLightDriver.c
# End Source File
# Begin Source File

SOURCE=.\util\common.c
# End Source File
# Begin Source File

SOURCE=.\HomeAutomation\LightController.c
# End Source File
# Begin Source File

SOURCE=.\devices\LightDriver.c
# End Source File
# Begin Source File

SOURCE=.\HomeAutomation\LightScheduler.c
# End Source File
# Begin Source File

SOURCE=.\devices\MemMappedLightDriver.c
# End Source File
# Begin Source File

SOURCE=.\HomeAutomation\RandomMinuteGenerator.c
# End Source File
# Begin Source File

SOURCE=.\util\TimeService.c
# End Source File
# Begin Source File

SOURCE=.\util\TimeService_Helpers.c
# End Source File
# Begin Source File

SOURCE=.\devices\X10LightDriver.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\devices\AcmeWirelessLightDriver.h
# End Source File
# Begin Source File

SOURCE=..\include\util\common.h
# End Source File
# Begin Source File

SOURCE=..\include\HomeAutomation\LightController.h
# End Source File
# Begin Source File

SOURCE=..\include\devices\LightDriver.h
# End Source File
# Begin Source File

SOURCE=..\include\HomeAutomation\LightScheduler.h
# End Source File
# Begin Source File

SOURCE=..\include\devices\MemMappedLightDriver.h
# End Source File
# Begin Source File

SOURCE=..\include\HomeAutomation\RandomMinuteGenerator.h
# End Source File
# Begin Source File

SOURCE=..\platform\VisualStudio\stdint.h
# End Source File
# Begin Source File

SOURCE=..\include\util\TimeService.h
# End Source File
# Begin Source File

SOURCE=..\include\devices\X10LightDriver.h
# End Source File
# End Group
# End Target
# End Project
