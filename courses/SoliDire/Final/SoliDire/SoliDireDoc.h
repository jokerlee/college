// SoliDireDoc.h : interface of the CSoliDireDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOLIDIREDOC_H__0DA80AED_6393_4237_AF30_36D74B38F8EB__INCLUDED_)
#define AFX_SOLIDIREDOC_H__0DA80AED_6393_4237_AF30_36D74B38F8EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ProgressDialog.h"
#include "CFileTree.h"

using namespace std;

UINT ExtractThread(LPVOID param);
UINT PackingThread(LPVOID param);



class CSoliDireDoc : public CDocument
{
protected: // create from serialization only
	CSoliDireDoc();
	DECLARE_DYNCREATE(CSoliDireDoc)

// Attributes
private:
	BOOL m_bIsPacked;
public:
	ProgressDialog m_dlgProgress;
	CInodeList m_files;
	CFileHead m_CSDHead;
	CFileTree * m_DirTree;
	void InitDocument();
	void pack_file(CFile *, CInodeList::iterator);

public:
	BOOL is_packed() { return m_bIsPacked; }
	void set_packed(BOOL isPacked) { m_bIsPacked = isPacked; }
	void read_file(CFile *);
	void pack_all_file(CFile *);
	void pack_added_file(CFile *);
	void extract_file(CInode, CFile *, CString);
	void extract_all_files();
	void extract_all_files(CTreeNode *, CFile *, CString);
	void insert_file(CString);
	void build_dir_tree(CString);
	BOOL Stop;
	BOOL IsStop(){ return Stop; }

private:
	void build_dir_tree(CTreeNode * &, CString);

// Operations
public:
	CFileTree * get_dir_tree(){ return m_DirTree; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoliDireDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSoliDireDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSoliDireDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOLIDIREDOC_H__0DA80AED_6393_4237_AF30_36D74B38F8EB__INCLUDED_)
