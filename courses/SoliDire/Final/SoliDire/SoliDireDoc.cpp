// SoliDireDoc.cpp : implementation of the CSoliDireDoc class
//
#ifdef AFX_CORE2_SEG
#pragma code_seg(AFX_CORE2_SEG)
#endif

#include "stdafx.h"
#include "SoliDire.h"
#include "CFileTree.h"
#include "SoliDireDoc.h"
#include "folder_dialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSoliDireDoc

IMPLEMENT_DYNCREATE(CSoliDireDoc, CDocument)

BEGIN_MESSAGE_MAP(CSoliDireDoc, CDocument)
	//{{AFX_MSG_MAP(CSoliDireDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoliDireDoc construction/destruction


CSoliDireDoc::CSoliDireDoc()
{
	m_DirTree = new CFileTree;
}

CSoliDireDoc::~CSoliDireDoc()
{
	delete m_DirTree;
}

void CSoliDireDoc::read_file(CFile * ifp)
{
	ifp->Seek(0, CFile::begin);
	ifp->Read((char*)&m_CSDHead, sizeof(CFileHead));
	ifp->Seek(m_CSDHead.nTreeStart, CFile::begin);
	
	CInode tmp;
	UINT nCount;

	ifp->Read((char*)&nCount, sizeof(UINT));
	while (nCount--)
	{
		tmp.Read(ifp);
		m_files.push_back(tmp);
	}

	m_DirTree->build_tree(m_files);
}

void CSoliDireDoc::pack_added_file(CFile * ofp)
{
	CInodeList::iterator i;
	m_files.clear();
	m_DirTree->serial(m_files);
	
	ofp->Seek(m_CSDHead.nTreeStart, CFile::begin);

	for (i=m_files.begin(); i->lpszFileName.Find(':')==-1; ++i);

	pack_file(ofp, i);

}

void CSoliDireDoc::pack_all_file(CFile * ofp)
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

}


void CSoliDireDoc::pack_file(CFile * ofp, CInodeList::iterator i)
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

				for (UINT j=0; nLen = ifile.Read(buffer, 512); ++j)
					ofp->Write(buffer, nLen);

				i->nEnd = ofp->GetPosition();
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

void CSoliDireDoc::insert_file(CString filename)
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

void CSoliDireDoc::extract_all_files()
{
	if (!is_packed() || !m_DirTree->m_pRoot)
		return;
	
	CFile ifile;

	if (ifile.Open(GetPathName(), CFile::modeRead | CFile::shareDenyWrite))
	{
		CString path;
		CFolderDialog dlg(&path);

		if (dlg.DoModal() == IDOK)
		{
			if (path.Right(1) != "\\")
				path += "\\";
			
			extract_all_files(m_DirTree->m_pRoot, &ifile, path);
		}
	}
}

void CSoliDireDoc::extract_all_files(CTreeNode * p, CFile * ifp, CString path)
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


void CSoliDireDoc::extract_file(CInode info, CFile * ifp, CString path)
{
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

void CSoliDireDoc::build_dir_tree(CString basedir)
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

void CSoliDireDoc::build_dir_tree(CTreeNode * & m_pRoot, CString basedir)
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


/////////////////////////////////////////////////////////////////////////////
// CSoliDireDoc serialization

void CSoliDireDoc::Serialize(CArchive& ar)
{
	ar.Flush();
	CFile* fp = ar.GetFile( );
	if (ar.IsStoring())
	{
		if (is_packed() && IsModified())
			pack_added_file(fp);
		else	
			pack_all_file(fp);// pack the file
	}
	else
	{
		read_file(fp);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSoliDireDoc diagnostics

#ifdef _DEBUG
void CSoliDireDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSoliDireDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSoliDireDoc commands

void CSoliDireDoc::InitDocument()
{
	
}

BOOL CSoliDireDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	
	set_packed(FALSE); //Set Unsaved Flag

	InitDocument();
	return TRUE;
}

BOOL CSoliDireDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	set_packed(TRUE);

	InitDocument();
	return TRUE;
}


void CSoliDireDoc::DeleteContents() 
{

}

BOOL CSoliDireDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	CFileException fe;
	CFile* pFile = NULL;
	
	DWORD nFlags = CFile::modeReadWrite | CFile::shareExclusive;
	if (!is_packed())
		nFlags |= CFile::modeCreate;

	pFile = GetFile(lpszPathName, nFlags, &fe);

	if (pFile == NULL)
	{
		ReportSaveLoadException(lpszPathName, &fe,
			TRUE, AFX_IDP_INVALID_FILENAME);
		return FALSE;
	}

	CArchive saveArchive(pFile, CArchive::store | CArchive::bNoFlushOnDelete);
	saveArchive.m_pDocument = this;
	saveArchive.m_bForceFlat = FALSE;

	CWaitCursor wait;
	Serialize(saveArchive);     // save me
	saveArchive.Close();
	ReleaseFile(pFile, FALSE);

	SetModifiedFlag(FALSE);     // back to unmodified

	return TRUE;        // success
}
