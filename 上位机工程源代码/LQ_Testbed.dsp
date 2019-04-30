# Microsoft Developer Studio Project File - Name="LQ_Testbed" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=LQ_Testbed - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LQ_Testbed.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LQ_Testbed.mak" CFG="LQ_Testbed - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LQ_Testbed - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "LQ_Testbed - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LQ_Testbed - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "LQ_Testbed - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "LQ_Testbed - Win32 Release"
# Name "LQ_Testbed - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ADOConn.cpp
# End Source File
# Begin Source File

SOURCE=.\Comm.cpp
# End Source File
# Begin Source File

SOURCE=.\Common.cpp
# End Source File
# Begin Source File

SOURCE=.\DataManageDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EvaluatorAnalysisDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EvluatorManageDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\excel.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\iplotannotationx.cpp
# End Source File
# Begin Source File

SOURCE=.\iplotaxisx.cpp
# End Source File
# Begin Source File

SOURCE=.\iplotchannelx.cpp
# End Source File
# Begin Source File

SOURCE=.\iplotdatacursorx.cpp
# End Source File
# Begin Source File

SOURCE=.\iplotdataviewx.cpp
# End Source File
# Begin Source File

SOURCE=.\iplotlabelx.cpp
# End Source File
# Begin Source File

SOURCE=.\iplotlegendx.cpp
# End Source File
# Begin Source File

SOURCE=.\iplotlimitx.cpp
# End Source File
# Begin Source File

SOURCE=.\iplottablecolumnx.cpp
# End Source File
# Begin Source File

SOURCE=.\iplottablex.cpp
# End Source File
# Begin Source File

SOURCE=.\iplottoolbarx.cpp
# End Source File
# Begin Source File

SOURCE=.\iplotx.cpp
# End Source File
# Begin Source File

SOURCE=.\LinkEstimateDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LQ_Testbed.cpp
# End Source File
# Begin Source File

SOURCE=.\LQ_Testbed.rc
# End Source File
# Begin Source File

SOURCE=.\LQ_TestbedDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\SceneConfigDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerComm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TestCustomDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TestResultDisplayDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ADOConn.h
# End Source File
# Begin Source File

SOURCE=.\Comm.h
# End Source File
# Begin Source File

SOURCE=.\Common.h
# End Source File
# Begin Source File

SOURCE=.\DataManageDlg.h
# End Source File
# Begin Source File

SOURCE=.\EvaluatorAnalysisDlg.h
# End Source File
# Begin Source File

SOURCE=.\EvluatorManageDlg.h
# End Source File
# Begin Source File

SOURCE=.\excel.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\Global.h
# End Source File
# Begin Source File

SOURCE=.\HighResolutionTimer.h
# End Source File
# Begin Source File

SOURCE=.\iplotannotationx.h
# End Source File
# Begin Source File

SOURCE=.\iplotaxisx.h
# End Source File
# Begin Source File

SOURCE=.\iplotchannelx.h
# End Source File
# Begin Source File

SOURCE=.\iplotdatacursorx.h
# End Source File
# Begin Source File

SOURCE=.\iplotdataviewx.h
# End Source File
# Begin Source File

SOURCE=.\iplotlabelx.h
# End Source File
# Begin Source File

SOURCE=.\iplotlegendx.h
# End Source File
# Begin Source File

SOURCE=.\iplotlimitx.h
# End Source File
# Begin Source File

SOURCE=.\iplottablecolumnx.h
# End Source File
# Begin Source File

SOURCE=.\iplottablex.h
# End Source File
# Begin Source File

SOURCE=.\iplottoolbarx.h
# End Source File
# Begin Source File

SOURCE=.\iplotx.h
# End Source File
# Begin Source File

SOURCE=.\LinkEstimateDlg.h
# End Source File
# Begin Source File

SOURCE=.\LQ_Testbed.h
# End Source File
# Begin Source File

SOURCE=.\LQ_TestbedDlg.h
# End Source File
# Begin Source File

SOURCE=.\OptionDlg.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\Protocol.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SceneConfigDlg.h
# End Source File
# Begin Source File

SOURCE=.\ServerComm.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TestCustomDlg.h
# End Source File
# Begin Source File

SOURCE=.\TestResultDisplayDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\res\1定制方案.ico"
# End Source File
# Begin Source File

SOURCE=".\res\1节点管理.ico"
# End Source File
# Begin Source File

SOURCE=".\res\2定制方案.ico"
# End Source File
# Begin Source File

SOURCE=".\res\2结果显示.ico"
# End Source File
# Begin Source File

SOURCE=".\res\3结果显示.ico"
# End Source File
# Begin Source File

SOURCE=".\res\3开始测试.ico"
# End Source File
# Begin Source File

SOURCE=".\res\3链路评估.ico"
# End Source File
# Begin Source File

SOURCE=".\res\4结果显示.ico"
# End Source File
# Begin Source File

SOURCE=".\res\4开始测试.ico"
# End Source File
# Begin Source File

SOURCE=".\res\4链路评估.ico"
# End Source File
# Begin Source File

SOURCE=".\res\4链路预测.ico"
# End Source File
# Begin Source File

SOURCE=".\res\5查询结果.ico"
# End Source File
# Begin Source File

SOURCE=".\res\5链路评估.ico"
# End Source File
# Begin Source File

SOURCE=".\res\5链路预测.ico"
# End Source File
# Begin Source File

SOURCE=".\res\6查询结果1.ico"
# End Source File
# Begin Source File

SOURCE=".\res\6导出数据.ico"
# End Source File
# Begin Source File

SOURCE=".\res\6链路预测.ico"
# End Source File
# Begin Source File

SOURCE=".\res\7查询结果.ico"
# End Source File
# Begin Source File

SOURCE=".\res\7导出数据.ico"
# End Source File
# Begin Source File

SOURCE=".\res\8导出数据.ico"
# End Source File
# Begin Source File

SOURCE=".\res\9退出系统.ico"
# End Source File
# Begin Source File

SOURCE=.\res\bottom.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LQ_Testbed.ico
# End Source File
# Begin Source File

SOURCE=.\res\LQ_Testbed.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ooopic_1452188916.bmp
# End Source File
# Begin Source File

SOURCE=.\res\serial.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section LQ_Testbed : {24DA2975-3806-46E5-BA56-DAC1F3C234DE}
# 	2:5:Class:CiPlotDataViewX
# 	2:10:HeaderFile:iplotdataviewx.h
# 	2:8:ImplFile:iplotdataviewx.cpp
# End Section
# Section LQ_Testbed : {D017E3C4-9CA0-4D94-9AA9-CF421E1AF6DD}
# 	2:5:Class:CiPlotX
# 	2:10:HeaderFile:iplotx.h
# 	2:8:ImplFile:iplotx.cpp
# End Section
# Section LQ_Testbed : {C0FC6A66-D740-4962-97D5-E0ADD4658924}
# 	2:5:Class:CiPlotAxisX
# 	2:10:HeaderFile:iplotaxisx.h
# 	2:8:ImplFile:iplotaxisx.cpp
# End Section
# Section LQ_Testbed : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section LQ_Testbed : {27FDC973-2ED3-4769-9ED7-01D81C45A32E}
# 	2:5:Class:CiPlotLimitX
# 	2:10:HeaderFile:iplotlimitx.h
# 	2:8:ImplFile:iplotlimitx.cpp
# End Section
# Section LQ_Testbed : {0BFA465F-B214-41F6-B5D6-986D4991F257}
# 	2:5:Class:CiPlotToolBarX
# 	2:10:HeaderFile:iplottoolbarx.h
# 	2:8:ImplFile:iplottoolbarx.cpp
# End Section
# Section LQ_Testbed : {854A06F7-C75E-4A42-B757-B4C352FC8488}
# 	2:5:Class:CiPlotLegendX
# 	2:10:HeaderFile:iplotlegendx.h
# 	2:8:ImplFile:iplotlegendx.cpp
# End Section
# Section LQ_Testbed : {02537798-A7C9-42D3-A8EE-70088290EAA4}
# 	2:5:Class:CiPlotChannelX
# 	2:10:HeaderFile:iplotchannelx.h
# 	2:8:ImplFile:iplotchannelx.cpp
# End Section
# Section LQ_Testbed : {E3F19885-4F77-438B-96FC-B3D16F3CC31F}
# 	2:5:Class:CiPlotTableColumnX
# 	2:10:HeaderFile:iplottablecolumnx.h
# 	2:8:ImplFile:iplottablecolumnx.cpp
# End Section
# Section LQ_Testbed : {57EE716C-BC86-4DFC-8548-5FD12F6D855F}
# 	2:5:Class:CiPlotDataCursorX
# 	2:10:HeaderFile:iplotdatacursorx.h
# 	2:8:ImplFile:iplotdatacursorx.cpp
# End Section
# Section LQ_Testbed : {48ED4A15-F4EE-410F-B52E-AC3875D1608E}
# 	2:5:Class:CiPlotTableX
# 	2:10:HeaderFile:iplottablex.h
# 	2:8:ImplFile:iplottablex.cpp
# End Section
# Section LQ_Testbed : {249CF20E-8331-4C41-8C13-7C8D2A72FADA}
# 	2:5:Class:CiPlotLabelX
# 	2:10:HeaderFile:iplotlabelx.h
# 	2:8:ImplFile:iplotlabelx.cpp
# End Section
# Section LQ_Testbed : {1791C036-8981-492A-BD28-F2331BC9B7C7}
# 	2:21:DefaultSinkHeaderFile:iplotx.h
# 	2:16:DefaultSinkClass:CiPlotX
# End Section
# Section LQ_Testbed : {4E4EFA15-4C5F-4C22-8CD7-B869EFDB97B8}
# 	1:14:IDD_OPTION_DLG:108
# 	2:16:Resource Include:resource.h
# 	2:17:CLASS: COptionDlg:COptionDlg
# 	2:11:OptionDlg.h:OptionDlg.h
# 	2:14:IDD_OPTION_DLG:IDD_OPTION_DLG
# 	2:10:ENUM: enum:enum
# 	2:13:OptionDlg.cpp:OptionDlg.cpp
# 	2:19:Application Include:LQ_Testbed.h
# End Section
# Section LQ_Testbed : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section LQ_Testbed : {217995A5-7C8E-4307-8750-34F4BEC14BB5}
# 	2:5:Class:CiPlotAnnotationX
# 	2:10:HeaderFile:iplotannotationx.h
# 	2:8:ImplFile:iplotannotationx.cpp
# End Section
