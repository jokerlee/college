// JGraphView.cpp : CJGraphView 类的实现
//

#include "stdafx.h"
#include "JGraph.h"

#include "JGraphDoc.h"
#include "JGraphView.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CJGraphView

IMPLEMENT_DYNCREATE(CJGraphView, CView)

BEGIN_MESSAGE_MAP(CJGraphView, CView)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_COMMAND(ID_EDIT_UNDO, &CJGraphView::OnEditUndo)
    ON_COMMAND(ID_EDIT_REDO, &CJGraphView::OnEditRedo)
    ON_COMMAND(ID_DRAW_DEFAULT, &CJGraphView::OnDrawDefault)
    ON_COMMAND(ID_DRAW_LINE, &CJGraphView::OnDrawLine)
    ON_COMMAND(ID_DRAW_CIRCLE, &CJGraphView::OnDrawCircle)
    ON_COMMAND(ID_DRAW_ECLIPSE, &CJGraphView::OnDrawEclipse)
    ON_COMMAND(ID_DRAW_FILL, &CJGraphView::OnDrawFill)
    ON_COMMAND(ID_SET_COLOR, &CJGraphView::OnSelectColor)
END_MESSAGE_MAP()

// CJGraphView 构造/析构

CJGraphView::CJGraphView()
    :m_nMode( MODE_NONE ), m_color( RGB(0,0,0) )
{
	// TODO: 在此处添加构造代码

}

CJGraphView::~CJGraphView()
{
}

BOOL CJGraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

  HBRUSH brush = CreateSolidBrush( RGB( 255, 255, 255 ) );//创建白色背景刷  
  LPCTSTR lpWhiteClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_OWNDC, 0, brush );
  cs.lpszClass = lpWhiteClass;
  return CView::PreCreateWindow(cs);
}

// CJGraphView 绘制

void CJGraphView::OnPrepareDC( CDC* pDC, CPrintInfo * pInfo = NULL )
{
    pDC->SetMapMode( MM_TEXT );
    pDC->SetWindowOrg( 0, 0 );
    CView::OnPrepareDC( pDC, pInfo );
}

void CJGraphView::OnInitialUpdate() 
{
    CJGraphDoc * pDoc = GetDocument();

    CView::OnInitialUpdate();
}

void CJGraphView::OnUpdate(CView* /* pSender */, LPARAM  lHint, 
                             CObject* pHint) 
{
    DrawLatestChange();
    return;
}



void CJGraphView::OnDraw( CDC * pDC )
{
	CJGraphDoc* pDoc = GetDocument();
	ASSERT_VALID( pDoc );
	if ( !pDoc )
		return;
    
    int nWidth  = pDoc->GetDocSize().cx;
    int nHeight = pDoc->GetDocSize().cy;
    
    CClientDC dc( this );
    OnPrepareDC( &dc );

    CPoint pt;
    COLORREF color;
    for ( int x = 0; x < nWidth; ++x )
    {
        for ( int y = 0; y < nHeight; ++y )
        {
            color = pDoc->GetPoint( x, y );
            if ( color != RGB( 255, 255, 255 ) )
                SetPixel( dc, x, y, color );
        }
    }
}


// CJGraphView 诊断

#ifdef _DEBUG
void CJGraphView::AssertValid() const
{
	CView::AssertValid();
}

void CJGraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CJGraphDoc * CJGraphView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJGraphDoc)));
	return (CJGraphDoc*)m_pDocument;
}
#endif //_DEBUG



// CJGraphView 消息处理程序

void CJGraphView::Draw( CPoint p1, CPoint p2 )
{
    CJGraphDoc * pDoc = GetDocument();

    switch ( m_nMode )
    {
    case MODE_LINE: 
        pDoc->DrawLine( p1, p2, m_color );
        break;
    case MODE_CIRCLE:
        pDoc->DrawCircle( p1, p2, m_color );
        break;
    case MODE_ECLIPSE:
        pDoc->DrawEclipse( p1, p2, m_color );
        break;
    default:
        break;
    }

}

void CJGraphView::OnLButtonDown( UINT, CPoint point ) 
{
    CClientDC dc( this );
    OnPrepareDC( &dc );
    dc.DPtoLP( &point );

    /*
    vector<CEdge> edges, fills;
    CEdge e;
    
    e.p1 = CPoint( 100, 100 );
    e.p2 = CPoint( 200, 100 );
    edges.push_back(e);
    
    e.p1 = CPoint( 100, 100 );
    e.p2 = CPoint( 100, 200 );
    edges.push_back(e);
    
    e.p1 = CPoint( 100, 200 );
    e.p2 = CPoint( 200, 100 );
    edges.push_back(e);

    e.p1 = CPoint( 110, 110 );
    e.p2 = CPoint( 180, 110 );
    edges.push_back(e);
    
    e.p1 = CPoint( 110, 110 );
    e.p2 = CPoint( 110, 180 );
    edges.push_back(e);
    
    e.p1 = CPoint( 110, 180 );
    e.p2 = CPoint( 180, 110 );
    edges.push_back(e);

    GetDocument()->ScanFill( edges, fills );
    

    for ( UINT i = 0; i < fills.size(); ++i )
    {
        dc.MoveTo( fills[i].p1 );
        dc.LineTo( fills[i].p2 );
    }
*/
    if ( m_nMode == MODE_NONE )
        return;

    if ( m_nMode == MODE_FILL )
    {
        GetDocument()->FillArea( point, m_color );
        return;
    }

    m_ptStart = point;
    Draw( point, point );

    SetCapture();
    
}

void CJGraphView::OnMouseMove( UINT, CPoint point ) 
{ 
    /* Show current mouse position on statusbar */
    CClientDC dc( this );
    OnPrepareDC( &dc );
    dc.DPtoLP( &point );

    CStatusBar * pStatusBar = (CStatusBar *)AfxGetMainWnd()
            ->GetDescendantWindow(AFX_IDW_STATUS_BAR);
   
    CString csStatus; 
    csStatus.Format( L"[%d,%d]", point.x, point.y );  
    pStatusBar->SetPaneText( 0, csStatus );
    

    if ( GetCapture() != this )
        return;

    CJGraphDoc * pDoc = GetDocument();
    OnEditUndo();
    Draw( m_ptStart, point );
}


void CJGraphView::OnLButtonUp( UINT, CPoint point ) 
{
    if ( GetCapture() != this )
        return; 

    ReleaseCapture();
    return;
}



void CJGraphView::DrawLatestChange( ) 
{
    CJGraphDoc * pDoc = GetDocument();
    vector<CColorPoint> cpts = pDoc->GetLatestChange();

    CClientDC dc( this );
    OnPrepareDC( &dc );

    for ( UINT i = 0; i < cpts.size(); ++i )
    {
        dc.LPtoDP( &cpts[i].first );
        COLORREF curcolor = pDoc->GetPoint( cpts[i].first.x, cpts[i].first.y );
        SetPixel( dc, cpts[i].first.x, cpts[i].first.y, curcolor );
    }
}

void CJGraphView::OnEditUndo()
{
    CJGraphDoc * pDoc = GetDocument();
    vector<CColorPoint> cpts = pDoc->GetNextUndo();

    CClientDC dc( this );
    OnPrepareDC( &dc );

    for ( UINT i = 0; i < cpts.size(); ++i )
    {
        dc.LPtoDP( &cpts[i].first );
        COLORREF curcolor = pDoc->GetPoint( cpts[i].first.x, cpts[i].first.y );
        SetPixel( dc, cpts[i].first.x, cpts[i].first.y, curcolor - cpts[i].second );
    }

    pDoc->Undo();
}

void CJGraphView::OnEditRedo()
{
    CJGraphDoc * pDoc = GetDocument();
    vector<CColorPoint> cpts = pDoc->GetNextRedo();

    CClientDC dc( this );
    OnPrepareDC( &dc );

    for ( UINT i = 0; i < cpts.size(); ++i )
    {
        dc.LPtoDP( &cpts[i].first );
        COLORREF curcolor = pDoc->GetPoint( cpts[i].first.x, cpts[i].first.y );
        SetPixel( dc, cpts[i].first.x, cpts[i].first.y, curcolor + cpts[i].second );
    }

    pDoc->Redo();
}

void CJGraphView::OnDrawDefault()
{
    m_nMode = MODE_NONE;
}

void CJGraphView::OnDrawLine()
{
    m_nMode = MODE_LINE;
}

void CJGraphView::OnDrawCircle()
{
    m_nMode = MODE_CIRCLE;
}

void CJGraphView::OnDrawEclipse()
{
    m_nMode = MODE_ECLIPSE;
}

void CJGraphView::OnDrawFill()
{
    m_nMode = MODE_FILL;
}

void CJGraphView::OnSelectColor()
{
    CColorDialog   dlg;  
    dlg.DoModal();  
    m_color = dlg.GetColor();
}