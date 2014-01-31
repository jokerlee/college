// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SoliDire.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const UINT kImageWidth (50);
static const UINT kImageHeight (70);
static const UINT kNumImages (9);
static const UINT kToolBarBitDepth (ILC_COLOR24);


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	//ID_INDICATOR_CAPS,
	//ID_INDICATOR_NUM,
	//ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	AttachToolbarImages(IDB_TOOLBAR_IMAGE, NULL, NULL);


	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

static void	MakeToolbarImageList (UINT inBitmapID, CImageList& outImageList)
{
	CBitmap bm;

	// if we use CBitmap::LoadBitmap() to load the bitmap, the colors
	// will be reduced to the bit depth of the main screen and we won't
	// be able to access the pixels directly. To avoid those problems,
	// we'll load the bitmap as a DIBSection instead and attach the
	// DIBSection to the CBitmap.
	VERIFY (bm.Attach (::LoadImage (::AfxFindResourceHandle(
	MAKEINTRESOURCE (inBitmapID), RT_BITMAP),
	MAKEINTRESOURCE (inBitmapID), IMAGE_BITMAP, 0, 0,
	(LR_DEFAULTSIZE | LR_CREATEDIBSECTION))));

	// create a 24 bit image list with the same dimensions and number
	// of buttons as the toolbar
	VERIFY (outImageList.Create (
		kImageWidth, kImageHeight, kToolBarBitDepth, kNumImages, 0));

	// attach the bitmap to the image list
	VERIFY (outImageList.Add (&bm, RGB (0, 0, 0)) != -1);
}


void CMainFrame::AttachToolbarImages (UINT inNormalImageID,
                                      UINT inDisabledImageID,
                                      UINT inHotImageID)
{
	// make high-color image lists for each of the bitmaps
	::MakeToolbarImageList (inNormalImageID, m_ToolbarImages);
	//::MakeToolbarImageList (inDisabledImageID, m_ToolbarImages);
	//::MakeToolbarImageList (inHotImageID, m_ToolbarImages);

	// get the toolbar control associated with the CToolbar object
	CToolBarCtrl& barCtrl = m_wndToolBar.GetToolBarCtrl();

	// attach the image lists to the toolbar control
	barCtrl.SetImageList(&m_ToolbarImages);
	barCtrl.SetDisabledImageList(&m_ToolbarImages);
	barCtrl.SetHotImageList(&m_ToolbarImages);
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

