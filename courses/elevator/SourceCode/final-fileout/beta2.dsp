# Microsoft Developer Studio Project File - Name="beta2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=beta2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "beta2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "beta2.mak" CFG="beta2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "beta2 - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "beta2 - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "beta2 - Win32 Release"

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
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "beta2 - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib egg.lib eggd.lib msimg32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "beta2 - Win32 Release"
# Name "beta2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\beta2.cpp
# End Source File
# Begin Source File

SOURCE=.\control.cpp
# End Source File
# Begin Source File

SOURCE=.\input.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\egg.h
# End Source File
# Begin Source File

SOURCE=.\elevator.h
# End Source File
# Begin Source File

SOURCE=.\externals.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\1.bmp
# End Source File
# Begin Source File

SOURCE=.\2.bmp
# End Source File
# Begin Source File

SOURCE=.\3.bmp
# End Source File
# Begin Source File

SOURCE=.\4.bmp
# End Source File
# Begin Source File

SOURCE=.\5.bmp
# End Source File
# Begin Source File

SOURCE=.\6.bmp
# End Source File
# Begin Source File

SOURCE=.\7.bmp
# End Source File
# Begin Source File

SOURCE=.\8.bmp
# End Source File
# Begin Source File

SOURCE=.\9.bmp
# End Source File
# Begin Source File

SOURCE=.\button1B.bmp
# End Source File
# Begin Source File

SOURCE=.\button2B.bmp
# End Source File
# Begin Source File

SOURCE=.\button3B.bmp
# End Source File
# Begin Source File

SOURCE=.\button4B.bmp
# End Source File
# Begin Source File

SOURCE=.\button5B.bmp
# End Source File
# Begin Source File

SOURCE=.\button6B.bmp
# End Source File
# Begin Source File

SOURCE=.\button7B.bmp
# End Source File
# Begin Source File

SOURCE=.\button8B.bmp
# End Source File
# Begin Source File

SOURCE=.\button9B.bmp
# End Source File
# Begin Source File

SOURCE=.\dnArrow.bmp
# End Source File
# Begin Source File

SOURCE=.\elevator1.bmp
# End Source File
# Begin Source File

SOURCE=.\sound\floor1.wav
# End Source File
# Begin Source File

SOURCE=.\sound\floor2.wav
# End Source File
# Begin Source File

SOURCE=.\sound\floor3.wav
# End Source File
# Begin Source File

SOURCE=.\sound\floor4.wav
# End Source File
# Begin Source File

SOURCE=.\sound\floor5.wav
# End Source File
# Begin Source File

SOURCE=.\sound\floor6.wav
# End Source File
# Begin Source File

SOURCE=.\sound\floor7.wav
# End Source File
# Begin Source File

SOURCE=.\sound\floor8.wav
# End Source File
# Begin Source File

SOURCE=.\sound\floor9.wav
# End Source File
# Begin Source File

SOURCE=.\sound\global.wav
# End Source File
# Begin Source File

SOURCE=.\smArrow2.bmp
# End Source File
# Begin Source File

SOURCE=.\stop.bmp
# End Source File
# Begin Source File

SOURCE=.\triangle1.bmp
# End Source File
# Begin Source File

SOURCE=.\triangle2.bmp
# End Source File
# Begin Source File

SOURCE=.\upArrow.bmp
# End Source File
# Begin Source File

SOURCE=.\whole.bmp
# End Source File
# End Group
# End Target
# End Project
