# Microsoft Developer Studio Project File - Name="ProductionCodeLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ProductionCodeLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ProductionCodeLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ProductionCodeLib.mak" CFG="ProductionCodeLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ProductionCodeLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ProductionCodeLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ProductionCodeLib - Win32 Release"

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

!ELSEIF  "$(CFG)" == "ProductionCodeLib - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /GX /ZI /Od /I "..\include\util" /I "..\include\IO" /I "..\include\MyOS" /I "..\include\zune" /I "..\include\LedDriver" /I "..\include\HomeAutomation" /I "..\include\dvr" /I "$(CPP_U_TEST)/include" /I "$(CPP_U_TEST)/include/Platforms/VisualCpp" /I "../include/HomeAutomation" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Debug\ProductionCodeLib.lib ..\lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "ProductionCodeLib - Win32 Release"
# Name "ProductionCodeLib - Win32 Debug"
# Begin Group "dvr"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\dvr\DvRecorder.c
# End Source File
# End Group
# Begin Group "HomeAutomation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\HomeAutomation\LightScheduler.c
# End Source File
# End Group
# Begin Group "IO"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\IO\Flash.c
# End Source File
# Begin Source File

SOURCE=.\IO\IO.c
# End Source File
# End Group
# Begin Group "LedDriver"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LedDriver\LedDriver.c
# End Source File
# End Group
# Begin Group "MyOS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MyOS\Win32\Thread.c
# End Source File
# End Group
# Begin Group "util"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\util\CircularBuffer.c
# End Source File
# Begin Source File

SOURCE=.\util\Utils.c
# End Source File
# End Group
# Begin Group "zune"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\zune\RtcTime.c
# End Source File
# End Group
# End Target
# End Project
