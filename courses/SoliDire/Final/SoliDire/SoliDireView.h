// SoliDireView.h : interface of the CSoliDireView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOLIDIREVIEW_H__B2F052D1_95A2_432F_BC3D_DA58978BCF79__INCLUDED_)
#define AFX_SOLIDIREVIEW_H__B2F052D1_95A2_432F_BC3D_DA58978BCF79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "folder_dialog.h"
#include "SystemIcon.h"



class CSoliDireView : public CListView
{
protected: // create from serialization only
	CSoliDireView();

	DECLARE_DYNCREATE(CSoliDireView)

private:
	CSystemImageList m_SysIcon;

// Attributes
public:
	CSoliDireDoc* GetDocument();
		

// Operations
public:
	void ShowFiles(CTreeNode * pRoot, UINT &, UINT, UINT);
	void CreateItem(const CInode &, LVITEM &, BOOL);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoliDireView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSoliDireView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSoliDireView)
	afx_msg void OnEditAdd();
	afx_msg void OnEditAddFolder();
	afx_msg void OnFileExtract();
	afx_msg void OnFileSave();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SoliDireView.cpp
inline CSoliDireDoc* CSoliDireView::GetDocument()
   { return (CSoliDireDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOLIDIREVIEW_H__B2F052D1_95A2_432F_BC3D_DA58978BCF79__INCLUDED_)
