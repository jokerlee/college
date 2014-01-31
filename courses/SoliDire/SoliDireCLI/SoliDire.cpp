#ifndef _SOLIDIRE_H_
#define _SOLIDIRE_H_

#include "stdafx.h"
#include "CFileTree.h"
#include "SoliDire.h"
#include "windows.h"

UINT n;

CSoliDire::CSoliDire()
{
	m_DirTree = new CFileTree;
	m_bIsPacked = FALSE;
}

CSoliDire::~CSoliDire()
{
	delete m_DirTree;
}

void CSoliDire::list_files()
{
	if (m_DirTree->m_pRoot)
		list_files(m_DirTree->m_pRoot, 0);
	else
		printf("empty\n");
}
void CSoliDire::list_files(CTreeNode * root, UINT level)
{
	for (int i=0; i<level; i++)
		printf("│    ");
	CString name = root->get_inode().lpszFileName;
	name = name.Right(name.GetLength()-name.ReverseFind('\\')-1);
	printf ("├──%s\n", name.GetBuffer(0));
	if (root->has_lchild())
		list_files(root->get_lchild(), level+1);
	if (root->has_rchild())
		list_files(root->get_rchild(), level);
}

void CSoliDire::read_file(CFile * ifp)
{
	ifp->Seek(0, CFile::begin);
	ifp->Read((char*)&m_CSDHead, sizeof(CFileHead));
	ifp->Seek(m_CSDHead.nTreeStart, CFile::begin);
	
	CInode tmp;
	UINT nCount;

	ifp->Read((char*)&nCount, sizeof(UINT));
	m_DirTree->set_filenum(nCount);
	while (nCount--)
	{
		tmp.Read(ifp);
		m_files.push_back(tmp);
	}
	m_bIsPacked = TRUE;
	m_DirTree->build_tree(m_files);
}		

void CSoliDire::pack_added_file(CFile * ofp)
{
	CInodeList::iterator i;
	m_files.clear();
	m_DirTree->serial(m_files);
	
	ofp->Seek(m_CSDHead.nTreeStart, CFile::begin);

	for (i=m_files.begin(); i->lpszFileName.Find(':')==-1; ++i);

	pack_file(ofp, i);
	SetModifiedFlag(FALSE);
}

void CSoliDire::pack_all_file(CFile * ofp)
{
	m_files.clear();
	m_DirTree->serial(m_files);

	CInode tmp;
	CInodeList::iterator i;

	CFile ifile;

	ofp->Seek(sizeof(CFileHead), CFile::begin);
	m_CSDHead.nDataStart = ofp->GetPosition();

	i = m_files.begin();
	pack_file(ofp, i);
	SetModifiedFlag(FALSE);
}


void CSoliDire::pack_file(CFile * ofp, CInodeList::iterator i)
{

	char buffer[512];
	UINT nLen;
	CFile ifile;
	UINT nCount = m_files.size();

	for (; i!=m_files.end(); ++i)
		if (!i->bIsDir)
			if (ifile.Open(i->lpszFileName, CFile::modeRead | CFile::shareDenyWrite, NULL))
			{
				i->nBegin = ofp->GetPosition();
				CString name = i->lpszFileName;
				name = name.Right(name.GetLength()-name.ReverseFind('\\')-1);
				printf ("(%d/%d) Packing %s...\n", ++n, m_DirTree->get_filenum(), name.GetBuffer(0));
				for (UINT j=0; nLen = ifile.Read(buffer, 512); ++j)
					ofp->Write(buffer, nLen);

				ifile.Close();
			}
	
	m_CSDHead.nTreeStart = ofp->GetPosition();
	CString name;
	ofp->Write((char*)&nCount, sizeof(UINT));
	for (i=m_files.begin(); i!=m_files.end(); ++i)
	{
		name = i->lpszFileName;
		name = name.Right(name.GetLength()-name.ReverseFind('\\')-1);
		i->lpszFileName = name;
		i->Write(ofp);
	}

	ofp->SeekToBegin(); 
	ofp->Write((char*)&m_CSDHead, sizeof(CFileHead));
		
	// Rebuild the file tree
	m_DirTree->clear();
	read_file(ofp);
}

void CSoliDire::insert_file(CString filename)
{
	CFile f(filename, CFile::modeRead);

	if (f)
	{
		CInode tmp(f.GetFilePath(), 0, f.GetLength());

		if (!m_DirTree->m_pRoot)
		{
			m_DirTree->m_pRoot = new CTreeNode;
			m_DirTree->m_pRoot->set_inode(tmp);
		}
		else
		{
			CTreeNode * p = m_DirTree->m_pRoot;
			while (p->has_rchild())
				p = p->get_rchild();
			p->new_rchild(tmp);
		}
	
		SetModifiedFlag(TRUE);
		f.Close();
	}
}

void CSoliDire::extract_all_files()
{
	if (!is_packed() || !m_DirTree->m_pRoot)
		return;


	CFile ifile;

	if (ifile.Open(GetPathName(), CFile::modeRead | CFile::shareDenyWrite))
	{
		BROWSEINFO bi;
		ZeroMemory(&bi,sizeof(BROWSEINFO));
		LPMALLOC pMalloc;
		LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
		TCHAR * pth = new TCHAR[MAX_PATH];
		ZeroMemory(pth, MAX_PATH);
		if(pidl != NULL)
		{
			SHGetPathFromIDList(pidl,pth);
			if(SUCCEEDED(SHGetMalloc(&pMalloc)))//pidl指向的对象用完应该释放，之前忽略了
			{
				pMalloc->Free(pidl);
				pMalloc->Release();
			}
			CString path(pth);
			if (path != "")
			{
				n = 0;
				if (path.Right(1) != "\\")
					path += "\\";
				extract_all_files(m_DirTree->m_pRoot, &ifile, path);
				printf ("All(%d) files extracted successfuly.\n", m_DirTree->get_filenum());
			}
			else
				printf("Canceled.\n");
		}


	
	}
}

void CSoliDire::extract_all_files(CTreeNode * p, CFile * ifp, CString path)
{
	extract_file(p->get_inode(), ifp, path);

	CString tmp = path;
	if (tmp.Right(1) != "\\")
		tmp += "\\";
	if (p->get_inode().bIsDir)
		tmp = tmp + p->get_inode().lpszFileName + "\\";

	if (p->has_lchild())
		extract_all_files(p->get_lchild(), ifp, tmp);

	if (p->has_rchild())
	{
		p = p->get_rchild();
		extract_all_files(p, ifp, path);
	}
}


void CSoliDire::extract_file(CInode info, CFile * ifp, CString path)
{	
	printf ("(%d/%d) Extracting %s...\n", ++n, m_DirTree->get_filenum(), info.lpszFileName.GetBuffer(0));

	if (info.bIsDir)
	{
		CreateDirectory(path.GetBuffer(0)+info.lpszFileName, NULL);
	}
	else
	{
		char * buffer[512];
		UINT nLen,
			 nRemain = info.nFileSize;

		ifp->Seek(info.nBegin, CFile::begin);
		CFile ofp;
		ofp.Open(path+info.lpszFileName, 
			CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);

		for (UINT i=0; nRemain; ++i)
		{
			nLen = ifp->Read(buffer, (nRemain>=512)?(512):(nRemain));
			ofp.Write(buffer, nLen);
			nRemain -= nLen;
		}
		ofp.Close();
	}
}

void CSoliDire::build_dir_tree(CString basedir)
{
	CTreeNode * p = NULL;
	if (!m_DirTree->m_pRoot)
	{
		m_DirTree->m_pRoot = new CTreeNode;
		p = m_DirTree->m_pRoot;
	}
	else
	{
		p = m_DirTree->m_pRoot;
		while (p->has_rchild())
			p = p->get_rchild();
		p->new_rchild(); 
		p = p->get_rchild();
	}
	
	build_dir_tree(p, basedir);
	SetModifiedFlag(TRUE);
}

void CSoliDire::build_dir_tree(CTreeNode * & m_pRoot, CString basedir)
{
	CTreeNode * root = m_pRoot;
	CFileFind fnd;
	CInode tmp(basedir, 1, 0);
	root->set_inode(tmp);

	if (basedir.Right(1) != "\\")
		basedir += "\\";

	BOOL bWorking = fnd.FindFile(basedir+"*.*");

	for (int i=0; bWorking; i++)
	{
		bWorking = fnd.FindNextFile( );
		
		if (fnd.IsDots())
		{
			i--;
			continue;
		}
		
		m_DirTree->inc_filenum();

		tmp = CInode(fnd.GetFilePath(), 0, fnd.GetLength());
		if (i==0)
		{
			root->new_lchild();
			root = root->get_lchild();
			if (fnd.IsDirectory())
				build_dir_tree(root, basedir+fnd.GetFileName());
			else
				root->set_inode(tmp);
		}
		else
		{
			root->new_rchild(tmp);
			root = root->get_rchild();
			if (fnd.IsDirectory())
				build_dir_tree(root, basedir+fnd.GetFileName());
			else
				root->set_inode(tmp);
		}
	}
}


BOOL CSoliDire::save_file()
{

	DWORD nFlags = CFile::modeReadWrite | CFile::shareExclusive;
	if (is_packed() && IsModified())
	{
		CFile ofile(path.GetBuffer(0), nFlags);
		pack_added_file(&ofile);
		printf("New-added files successfuly packed.\n");
		return TRUE;
	}
	else
	{

		CFileDialog dlg(FALSE, (LPCTSTR)"*.sdr|*.sdr||", NULL, OFN_OVERWRITEPROMPT, (LPCTSTR)"*.sdr|*.sdr||", NULL);   
		printf("Choose the location of the packed file\n");
		if(dlg.DoModal() == IDOK)   
		{   
			path = dlg.GetPathName();   
			nFlags |= CFile::modeCreate;
			CFile ofile(path.GetBuffer(0), nFlags);
			n = 0;

			pack_all_file(&ofile);// pack the file
			printf("All(%d) files successfuly packed.\n", m_DirTree->get_filenum());
			
			SetModifiedFlag(FALSE);     // back to unmodified
			return TRUE;
		}
		else
		{
			printf("Canceled.\n");
			return FALSE;
		}
	}
}

BOOL CSoliDire::open_file()
{
	CFileDialog dlgAdd(TRUE, (LPCTSTR)"*.sdr|*.sdr||", NULL, OFN_OVERWRITEPROMPT, (LPCTSTR)"*.sdr|*.sdr||", NULL);   
	UINT iRet = dlgAdd.DoModal();

	printf("Choose the packed file to open.\n");
	if (iRet == IDOK)
	{
		path = dlgAdd.GetPathName();
		CFile ifile(path, CFile::modeRead | CFile::shareDenyWrite);
		read_file(&ifile);
		ifile.Close();
		printf ("%s successfully opened.\n", dlgAdd.GetFileName());
		return TRUE;
	}
	else
	{
		printf("Canceled.\n");
		return FALSE;
	}
}

BOOL CSoliDire::add_file()
{
	CFileDialog dlgAdd(TRUE, (LPCTSTR)"*.*|*.*||", NULL, OFN_OVERWRITEPROMPT, (LPCTSTR)"*.*|*.*||", NULL);   

	UINT iRet = dlgAdd.DoModal(),
		 nCount = 0;

	if (iRet == IDOK)
	{
		POSITION pos = dlgAdd.GetStartPosition();
		while (pos)
		{
			insert_file(dlgAdd.GetNextPathName(pos));
			nCount++;
		}
		CString msg;
		printf("%d file(s) sucessfully added.\n", nCount);
		return TRUE;
	}
	return FALSE;

}

BOOL CSoliDire::add_folder()
{	
	BROWSEINFO bi;
    ZeroMemory(&bi,sizeof(BROWSEINFO));
    LPMALLOC pMalloc;
    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
    TCHAR * pth = new TCHAR[MAX_PATH];
    if(pidl != NULL)
    {
        SHGetPathFromIDList(pidl,pth);
        if(SUCCEEDED(SHGetMalloc(&pMalloc)))//pidl指向的对象用完应该释放，之前忽略了
        {
            pMalloc->Free(pidl);
            pMalloc->Release();
        }
		CString path(pth);
		if (path != "")
		{
			build_dir_tree(path);
			SetModifiedFlag(TRUE);
			printf("Folder %s successfully added.\n", path);
			return TRUE;
		}
    }
	return FALSE;
}