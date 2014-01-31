// SoliDireCLI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SoliDireCLI.h"
#include "SoliDire.h"
#include <stdio.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;


void show_menu(int type = 0)
{
	cout << "Welcome to use SoliDire File Packer." << endl;
	cout << "CopyRight JackalDire 2009-2012." << endl;
	if (type == 0)
	{
		cout << "=================Main Menu====================" << endl;
		cout << "(1)New Pack Task" << endl;
		cout << "(2)Open an Exsited Packed File" << endl;
		cout << "(3)Compare Two Files" << endl;
		cout << "(4)Compare Two Folders" << endl;
		cout << "(0)Exit" << endl;
	}
	else if (type == 1)
	{
		cout << "================New Pack Task==================" << endl;
		cout << "(1)Add File" << endl;
		cout << "(2)Add Folder" << endl;
		cout << "(3)Pack all files" << endl;
		cout << "(4)List the files already added" << endl;
		cout << "(0)Back to Main Menu" << endl;
	}
	else if (type == 2)
	{
		cout << "=============Exsited Packed File===============" << endl;
		cout << "(1)Unpack All Files to..." << endl;
		cout << "(2)Add File(s)..." << endl;
		cout << "(3)Add Folder..." << endl;
		cout << "(4)Repack the Files" << endl;
		cout << "(5)List the contents in the file" << endl;
		cout << "(0)Back to Main Menu" << endl;
	}
}

void new_file()
{
	char cmd;
	CSoliDire newpack;
	system("CLS");
	show_menu(1);
	do
	{
		cout << "command:";
		cin >> cmd;
		switch (cmd)
		{
			case '1':
				newpack.add_file();	break;
			case '2':
				newpack.add_folder(); break;
			case '3':
				newpack.save_file(); break;
			case '4':
				newpack.list_files(); break;
			case '0':
				cout << "Return To Main Menu." << endl;
				break;
			default:
				cout << "Error Command." << endl;
				cin.clear();
				cin.sync();
				break;
		}
	}while (cmd != '0');
	system("CLS");
}

void open_file()
{
	CSoliDire prepack;
	system("CLS");
	if (prepack.open_file())
	{
		show_menu(2);
		char cmd;
		do
		{
			cout << "command:";
			cin >> cmd;
			switch (cmd)
			{
				case '1':
					prepack.extract_all_files();
					break;
				case '2':
					prepack.add_file(); break;
				case '3':
					prepack.add_folder(); break;
				case '4':
					prepack.save_file(); break;
				case '5':
					prepack.list_files(); break;
				case '0':
					cout << "Return To Main Menu." << endl;
					break;
				default:
					cout << "Error Command." << endl;
					cin.clear();
					cin.sync();
					break;
			}
		}
		while (cmd != '0');
	}
	system("CLS");
}
	
void file_cmp(CString path1, CString path2)
{
	path1 = "\"" + path1 + "\"";
	path2 = "\"" + path2 + "\"";
	CString tmp = "fc "+ path1 + " " + path2 + " /B";
	system(tmp.GetBuffer(0));
}

void file_cmp()
{
	CString path1;    
	CFileDialog dlg(TRUE, (LPCTSTR)"*.*|*.*||", NULL, OFN_OVERWRITEPROMPT, (LPCTSTR)"*.*|*.*||", NULL);   
	if(dlg.DoModal() == IDOK)   
	{   
		path1 = dlg.GetPathName();  
		CString path2;    
		CFileDialog dlg(TRUE, (LPCTSTR)"*.*|*.*||", NULL, OFN_OVERWRITEPROMPT, (LPCTSTR)"*.*|*.*||", NULL);   
		if(dlg.DoModal() == IDOK)   
		{   
			path2 = dlg.GetPathName();
			file_cmp(path1, path2);
		}   
	}else
		printf("Canceled.\n");

}

BOOL inode_cmp(CInode id1, CInode id2)
{
	printf("Comparing %s\n          %s\n", id1.lpszFileName, id2.lpszFileName);
	if (id1.lpszFileName.Right(id1.lpszFileName.GetLength()-id1.lpszFileName.ReverseFind('\\')-1) 
	 != id2.lpszFileName.Right(id2.lpszFileName.GetLength()-id2.lpszFileName.ReverseFind('\\')-1))
	{
		printf("filenames are different.\n");
		return FALSE;
	}
	else if (id1.nFileSize != id2.nFileSize)
	{
		printf("file sizes are different(%d %d).", id1.nFileSize, id2.nFileSize);
		return FALSE;
	}
	else
	{
		printf("The two files are the same.\n");
		return TRUE;
	}
}

void folder_cmp()
{
	CSoliDire f1;
	if (f1.add_folder())
	{
		CSoliDire f2;
		if (f2.add_folder())
		{
			f1.m_DirTree->serial(f1.m_files);
			f2.m_DirTree->serial(f2.m_files);
			printf("Comparing %s and %s", f1.m_DirTree->m_pRoot->get_inode().lpszFileName, 
										  f2.m_DirTree->m_pRoot->get_inode().lpszFileName);
			CInodeList::iterator i=f1.m_files.begin(), j=f2.m_files.begin();
			for ( ; i!=f1.m_files.end() | i!=f1.m_files.end(); i++, j++)
			{
				if (!inode_cmp(*i, *j))
				{
					printf("THE TWO FOLDERS ARE DIFFERENT.\n");
					return;
				}
			}
			printf("Totally %d files compared finished.\n", f1.m_DirTree->get_filenum());
			printf("THE TWO FOLDERS ARE THE SAME.\n");
		}
	}	
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		show_menu();
		char cmd;
		do
		{
			cout << "command:";
			cin >> cmd;
			switch (cmd)
			{
				case '1':
					new_file();
					show_menu();
					break;
				case '2':
					open_file(); 
					show_menu();
					break;
				case '3':
					file_cmp();
					break;
				case '4':
					folder_cmp();
					break;
				case '0':
					cout << "Exit Program." << endl;
					break;
				default:
					cout << "Error Command." << endl;
					cin.clear();
					cin.sync();
					break;
			}
		}while (cmd != '0');
	}

	return nRetCode;
}


