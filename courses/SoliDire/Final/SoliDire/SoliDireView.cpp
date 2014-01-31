// SoliDireView.cpp : implementation of the CSoliDireView class
//

#include "stdafx.h"
#include "SoliDire.h"

#include "SoliDireDoc.h"
#include "SoliDireView.h"
#include "ProgressDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSoliDireView

IMPLEMENT_DYNCREATE(CSoliDireView, CListView)

BEGIN_MESSAGE_MAP(CSoliDireView, CListView)
	//{{AFX_MSG_MAP(CSoliDireView)
	ON_COMMAND(ID_EDIT_ADD, OnEditAdd)
	ON_COMMAND(ID_EDIT_ADD_FOLDER, OnEditAddFolder)
	ON_COMMAND(ID_FILE_EXTRACT, OnFileExtract)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoliDireView construction/destruction

CSoliDireView::CSoliDireView()
{
	// TODO: add construction code here

}

CSoliDireView::~CSoliDireView()
{
	
}

BOOL CSoliDireView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |=	LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL;
	return CListView::PreCreateWindow(cs);
}


void CSoliDireView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CSoliDireView printing

BOOL CSoliDireView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSoliDireView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSoliDireView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSoliDireView diagnostics

#ifdef _DEBUG
void CSoliDireView::AssertValid() const
{
	CListView::AssertValid();
}

void CSoliDireView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CSoliDireDoc* CSoliDireView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSoliDireDoc)));
	return (CSoliDireDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSoliDireView message handlers

void CSoliDireView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CSoliDireDoc* pDoc = GetDocument();
	CFileTree * tree = pDoc->get_dir_tree();
	CTreeNode * root = tree->m_pRoot;

	ASSERT_VALID(pDoc);

	CWaitCursor wait;
	CListCtrl	&refCtrl = GetListCtrl();

	SetRedraw(FALSE);
	refCtrl.DeleteAllItems();
	UINT i=0;
	ShowFiles(pDoc->m_DirTree->m_pRoot, i, -1, 0);

	DWORD dwStyle = refCtrl.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
	dwStyle |= LVS_EX_HEADERDRAGDROP| LVS_EX_GRIDLINES;
	dwStyle |= LVS_EX_FULLROWSELECT;

	refCtrl.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)dwStyle);

	SetRedraw(TRUE);

}

void CSoliDireView::OnEditAdd() 
{
	CSoliDireDoc * pDoc = GetDocument();

	CFileDialog dlgAdd(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, NULL, NULL);
	DWORD MAXFILE = 4000;
	
	char * buffer = new char[MAXFILE];
	dlgAdd.m_ofn.nMaxFile = MAXFILE;
	dlgAdd.m_ofn.lpstrFile = buffer;
	dlgAdd.m_ofn.lpstrFile[0] = 0;
	dlgAdd.m_ofn.lpstrTitle = "选择文件";
	dlgAdd.m_ofn.lpstrFilter = "所有文件 (*.*)";

	UINT iRet = dlgAdd.DoModal(),
		 nCount = 0;

	if (iRet == IDOK)
	{
		POSITION pos = dlgAdd.GetStartPosition();
		while (pos)
		{
			pDoc->insert_file(dlgAdd.GetNextPathName(pos));
			nCount++;
		}
		CString msg;
		msg.Format("%d file(s) sucessfully added.\n", nCount);
		AfxMessageBox(msg);
	}

	pDoc->UpdateAllViews(0,0,0);
	delete []buffer;
}

void CSoliDireView::OnEditAddFolder() 
{

	CSoliDireDoc * pDoc = GetDocument();
	
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
		pDoc->build_dir_tree(path);
		pDoc->UpdateAllViews(0,0,0);
    }
}

void CSoliDireView::OnFileExtract() 
{
	CSoliDireDoc * pDoc = GetDocument();
	if (pDoc->is_packed())
	{
		pDoc->extract_all_files();
	}
	else
		AfxMessageBox("文件尚未被压缩。");
}

void CSoliDireView::OnFileSave() 
{
	CSoliDireDoc * pDoc = GetDocument();
	if (pDoc->IsModified())
	{
		pDoc->DoFileSave();
		pDoc->set_packed(TRUE);
	}
}

int CSoliDireView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CListCtrl& listctrl = GetListCtrl();
	
	listctrl.SetExtendedStyle(listctrl.GetExtendedStyle() | LVS_EX_SUBITEMIMAGES);
	
	CImageList * imageList = m_SysIcon.GetImageList( TRUE );
	listctrl.SetImageList(imageList, LVSIL_SMALL);

	//add three columns
	listctrl.InsertColumn(0, "文件名", LVCFMT_LEFT, 300);
	listctrl.InsertColumn(1, "类型", LVCFMT_LEFT, 150);
	listctrl.InsertColumn(2, "大小", LVCFMT_RIGHT, 100);

	return 0;
}

void CSoliDireView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CListCtrl& listctrl = GetListCtrl();
	CSoliDireDoc * pDoc = GetDocument();
	
	UINT index, hit;
	index = listctrl.HitTest(point, &hit);
	
	if ( (hit & LVHT_ONITEMICON) || (hit & LVHT_ONITEMLABEL))
	{
		SetRedraw(FALSE);
		UINT i=0;
		listctrl.DeleteAllItems();
		ShowFiles(pDoc->m_DirTree->m_pRoot, i, index, 0);

		DWORD dwStyle = listctrl.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
		dwStyle |= LVS_EX_HEADERDRAGDROP| LVS_EX_GRIDLINES;
		dwStyle |= LVS_EX_FULLROWSELECT;
		listctrl.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)dwStyle);

		SetRedraw(TRUE);
	}

	
	CListView::OnLButtonDblClk(nFlags, point);
}

void CSoliDireView::ShowFiles(CTreeNode * pRoot, UINT & num, UINT index, UINT level)
{
	LVITEM lvitem;
	ZeroMemory(&lvitem, sizeof(LVITEM));  
	lvitem.mask |= LVIF_INDENT;
	lvitem.iIndent = level;

	for (UINT i=0; pRoot; i++)
	{		
		if (num == index)
			pRoot->is_opened = !pRoot->is_opened;	

		lvitem.iItem = num++;

		CreateItem(pRoot->get_inode(), lvitem, pRoot->is_opened);
		
		if (pRoot->is_opened)
			ShowFiles(pRoot->get_lchild(), num, index, level+1);
		
		pRoot = pRoot->get_rchild();	
	}
}


void CSoliDireView::CreateItem(const CInode & info, LVITEM & lvitem, BOOL isOpen)
{
	CListCtrl	&refCtrl = GetListCtrl();

	SHFILEINFO sfi;

	CString size;
	m_SysIcon.GetIcon(sfi, info, isOpen);
	
	if (!info.bIsDir)
		size.Format("%d KB", info.nFileSize/1024);
	
	lvitem.mask |= LVIF_IMAGE | LVIF_TEXT |LVIF_PARAM;   
	lvitem.iImage = sfi.iIcon;
	lvitem.iSubItem = 0;   
	lvitem.lParam = 0; 
	lvitem.pszText = sfi.szDisplayName;

	refCtrl.InsertItem(&lvitem);
	refCtrl.SetItemText(lvitem.iItem, 1, sfi.szTypeName);	
	refCtrl.SetItemText(lvitem.iItem, 2, size);
}

void CSoliDireView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CPoint pos;
	GetCursorPos(&pos);

	CMenu menu;   
	VERIFY(menu.LoadMenu (IDR_SDTYPE));   
	CMenu * pPopup = menu.GetSubMenu(1);   
	ASSERT(pPopup != NULL);   
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, pos.x, pos.y, this);   

	*pResult = 0;
}
