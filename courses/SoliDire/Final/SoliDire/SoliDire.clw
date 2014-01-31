; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=ProgressDialog
LastTemplate=CFormView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SoliDire.h"
LastPage=0

ClassCount=9
Class1=CSoliDireApp
Class2=CSoliDireDoc
Class3=CSoliDireView
Class4=CMainFrame

ResourceCount=5
Resource1=IDR_SDTYPE
Resource2=IDR_MAINFRAME
Class5=CChildFrame
Class6=CAboutDlg
Resource3=IDD_DIALOG1
Class7=CProgressDialog
Resource4=IDD_ABOUTBOX
Class8=ProgressDialog
Class9=sasas
Resource5=IDD_STATUSDIALOG

[CLS:CSoliDireApp]
Type=0
HeaderFile=SoliDire.h
ImplementationFile=SoliDire.cpp
Filter=N
LastObject=CSoliDireApp

[CLS:CSoliDireDoc]
Type=0
HeaderFile=SoliDireDoc.h
ImplementationFile=SoliDireDoc.cpp
Filter=N
LastObject=CSoliDireDoc
BaseClass=CDocument
VirtualFilter=DC

[CLS:CSoliDireView]
Type=0
HeaderFile=SoliDireView.h
ImplementationFile=SoliDireView.cpp
Filter=C
LastObject=CSoliDireView
BaseClass=CListView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_BUTTON32773


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=SoliDire.cpp
ImplementationFile=SoliDire.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342177287

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_EDIT_ADD_FILE
Command4=ID_EDIT_ADD_FOLDER
Command5=ID_FILE_SAVE
Command6=ID_FILE_EXTRACT
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_SDTYPE]
Type=1
Class=CSoliDireView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_EXTRACT
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_ADD
Command9=ID_EDIT_ADD_FOLDER
Command10=ID_EDIT_DEL
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_WINDOW_NEW
Command14=ID_WINDOW_CASCADE
Command15=ID_WINDOW_TILE_HORZ
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_FILE_EXTRACT
Command3=ID_FILE_NEW
Command4=ID_FILE_OPEN
Command5=ID_FILE_PRINT
Command6=ID_FILE_SAVE
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
CommandCount=11

[CLS:CProgressDialog]
Type=0
HeaderFile=ProgressDialog.h
ImplementationFile=ProgressDialog.cpp
BaseClass=CDialog
Filter=D

[DLG:IDD_DIALOG1]
Type=1
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[DLG:IDD_STATUSDIALOG]
Type=1
Class=ProgressDialog
ControlCount=3
Control1=IDCANCEL,button,1342242816
Control2=IDC_PROGRESS,msctls_progress32,1350565888
Control3=IDC_TEXT,static,1342308352

[CLS:sasas]
Type=0
HeaderFile=sasas.h
ImplementationFile=sasas.cpp
BaseClass=CFormView
Filter=D
LastObject=ID_APP_ABOUT

[CLS:ProgressDialog]
Type=0
HeaderFile=progressdialog.h
ImplementationFile=progressdialog.cpp
BaseClass=CDialog
LastObject=ID_APP_ABOUT
Filter=D
VirtualFilter=dWC

