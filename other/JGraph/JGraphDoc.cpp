// JGraphDoc.cpp : CJGraphDoc 类的实现
//

#include "stdafx.h"
#include "JGraph.h"

#include "JGraphDoc.h"
#include <cmath>
#include <algorithm>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using std::make_pair;

// CJGraphDoc

IMPLEMENT_DYNCREATE(CJGraphDoc, CDocument)

BEGIN_MESSAGE_MAP(CJGraphDoc, CDocument)
END_MESSAGE_MAP()


// CJGraphDoc 构造/析构

CJGraphDoc::CJGraphDoc()
    :m_nHistoryPos(-1)
{

}

CJGraphDoc::~CJGraphDoc()
{
}

BOOL CJGraphDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
    InitDocument();

	return TRUE;
}



void CJGraphDoc::InitDocument()
{

    // default document size is 800 x 800 screen pixels
    m_sizeDoc = CSize( 800, 800 );

    m_bitmap.resize( m_sizeDoc.cx );
    COLORREF color = RGB( 255, 255, 255 );
    for ( UINT i = 0; i < m_bitmap.size(); ++i )
        m_bitmap[i].insert( m_bitmap[i].begin(), m_sizeDoc.cy, color );
}




// CJGraphDoc 序列化

void CJGraphDoc::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{
        ar << m_sizeDoc.cx;
        ar << m_sizeDoc.cy;

        for ( int x = 0; x < m_sizeDoc.cx; ++x )
            for ( int y = 0; y < m_sizeDoc.cy; ++y )
                ar << m_bitmap[x][y];

	}
	else
	{
        ar >> m_sizeDoc.cx;
        ar >> m_sizeDoc.cy;

        m_bitmap.resize( m_sizeDoc.cx );
        for ( int x = 0; x < m_sizeDoc.cx; ++x )
        {
            m_bitmap[x].resize( m_sizeDoc.cy );
            for ( int y = 0; y < m_sizeDoc.cy; ++y )      
                ar >> m_bitmap[x][y];;
        }

	}
}


// CJGraphDoc 诊断

#ifdef _DEBUG
void CJGraphDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CJGraphDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CJGraphDoc 命令


COLORREF CJGraphDoc::GetPoint( int x, int y )
{
    //if ( x >=0 && x < m_sizeDoc.cx && y >= 0 && y < m_sizeDoc.cy )
        return m_bitmap[x][y];
}

vector<CColorPoint> CJGraphDoc::GetLatestChange()
{
    if ( m_vecHistory.size() == 0 )
    {
        vector<CColorPoint> tmp(0);
        return tmp;
    }
    return m_vecHistory.back();
}

vector<CColorPoint> CJGraphDoc::GetNextUndo()
{
    if ( m_nHistoryPos < 0 )
    {
       vector<CColorPoint> tmp(0);
        return tmp;
    }

    return m_vecHistory[ m_nHistoryPos ];
}

vector<CColorPoint> CJGraphDoc::GetNextRedo()
{
    if ( m_nHistoryPos == m_vecHistory.size() - 1 )
    {
        vector<CColorPoint> tmp(0);
        return tmp;
    }

    return m_vecHistory[ m_nHistoryPos + 1 ];
}

void CJGraphDoc::DrawLine( CPoint ptStart, CPoint ptEnd, COLORREF color )
{
    int xs = ptStart.x, xe = ptEnd.x;
    int ys = ptStart.y, ye = ptEnd.y; 

    int d2x = 2 * abs( xe - xs );
    int d2y = 2 * abs( ye - ys );

    int flg = 0;
    if( d2x < d2y )
    {
        flg = 1;
        std::swap( xs, ys );
        std::swap( xe, ye );
        std::swap( d2x, d2y );
    }

    vector<CColorPoint> ptsChange;

    int incx = xe - xs > 0 ? 1 : -1;
    int incy = ye - ys > 0 ? 1 : -1;
    int x = xs, y = ys, e = d2y - d2x / 2;
    while ( x != xe )
    {
        e = e + d2y;
        if ( e >= 0 )
        {
            y = y + incy;
            e = e - d2x;
        }

        if ( x < 0 || x >= m_sizeDoc.cx || y < 0 || y >= m_sizeDoc.cy )
            break;

        CPoint pt;
        if ( flg )  pt.SetPoint( y, x );
        else        pt.SetPoint( x, y );
        
        COLORREF origin; 
        if ( ( origin = GetPoint( pt.x, pt.y ) ) != color )
            ptsChange.push_back( CColorPoint( pt, color - origin ) );

        x = x + incx;
    }

    FinishDraw( ptsChange );
    return;
}



void CJGraphDoc::DrawCircle( CPoint ptStart, CPoint ptEnd, COLORREF color )
{
    CPoint ptCenter;
    ptCenter.SetPoint( ( ptStart.x + ptEnd.x ) / 2, ( ptStart.y + ptEnd.y ) / 2 );

    double dx = ptStart.x - ptEnd.x;
    double dy = ptStart.y - ptEnd.y;
    double r = sqrt( dx * dx + dy * dy ) / 2;
    DrawCircularArc( ptCenter, r, 0, 2 * 3.1416, color );
}

void CJGraphDoc::DrawCircularArc( CPoint ptCenter, double r, double t1, double t2, COLORREF color )
{
    double x, y, dt;
    x = r * cos(t1) + ptCenter.x;
    y = r * sin(t1) + ptCenter.y;
    int xx = int(x) + 1, yy;

    dt = 1/double(2*r);
    vector<CColorPoint> cpts;

    while ( t1 < t2 )
    {
        COLORREF origin; 
        if ( int(x) != xx || int(y) != yy )
            if ( int(x) >= 0 && int(x) < m_sizeDoc.cx && int(y) >= 0 && int(y) < m_sizeDoc.cy ) 
                if ( ( origin = GetPoint( int(x), int(y) ) ) != color )
                    cpts.push_back( CColorPoint( CPoint( int(x), int(y) ), color - origin ) );
        
        xx = int(x); yy = int(y);
        
        t1 += dt;
        x = r * cos(t1) + ptCenter.x;
        y = r * sin(t1) + ptCenter.y;
    }

    FinishDraw( cpts );
    return;
}

void CJGraphDoc::DrawEclipse( CPoint ptStart, CPoint ptEnd, COLORREF color )
{
    CPoint ptCenter;
    ptCenter.SetPoint( ( ptStart.x + ptEnd.x ) / 2, ( ptStart.y + ptEnd.y ) / 2 );
    DrawEclipseArc( ptCenter, abs(ptStart.x - ptEnd.x)/2, abs(ptStart.y - ptEnd.y)/2, 0, 2*3.1416, color );
}


void CJGraphDoc::DrawEclipseArc( CPoint ptCenter, int a, int b, double t1, double t2, COLORREF color )
{
    double x, y, dt;
    x = a * cos(t1) + ptCenter.x;
    y = b * sin(t1) + ptCenter.y;
    int xx = int(x) + 1, yy;   

    dt = 1/double(a+b);
    vector<CColorPoint> cpts;
    while ( t1 < t2 )
    {
        COLORREF origin; 
        if ( int(x) != xx || int(y) != yy )
            if ( int(x) >= 0 && int(x) < m_sizeDoc.cx && int(y) >= 0 && int(y) < m_sizeDoc.cy ) 
                if ( ( origin = GetPoint( int(x), int(y) ) ) != color )
                    cpts.push_back( CColorPoint( CPoint( int(x), int(y) ), color - origin ) );
        
        xx = int(x); yy = int(y);

        t1 += dt;
        x = a * cos(t1) + ptCenter.x;
        y = b * sin(t1) + ptCenter.y;
    }
    FinishDraw( cpts );
    return;
}


void CJGraphDoc::FillArea( CPoint ptStart, COLORREF color )
{
    COLORREF target;
    if ( ( target = GetPoint( ptStart.x, ptStart.y ) ) == color )
        return;

    vector<vector<BOOL>> bAdded;
    bAdded.resize( m_sizeDoc.cx );
    for ( UINT i = 0; i < bAdded.size(); ++i )
        bAdded[i].resize( m_sizeDoc.cy );    
    
    vector<CColorPoint> ptsChange;
    
    ptsChange.push_back( CColorPoint( ptStart, color - target ) );
    bAdded[ ptStart.x ][ ptStart.y ] = TRUE;
    for ( UINT i = 0; i < ptsChange.size(); ++i )
    {
        FillArea( ptsChange[i], target, bAdded, ptsChange );       
    }
    FinishDraw( ptsChange );
    
}

void CJGraphDoc::FillArea( CColorPoint cpt, COLORREF target, vector<vector<BOOL>> & bAdded, vector<CColorPoint> & pts )
{
    static int dir[8] = { 0, -1, 1, 0, 0, 1, -1, 0 };
    
    int x, y;
    for ( int i = 0; i < 4; ++i )
    {
        x = cpt.first.x + dir[ 2*i ];
        y = cpt.first.y + dir[ 2*i + 1 ];

        if ( x < 0 || x >= (int)bAdded.size() || y < 0 || y >= (int)bAdded.size() )
            continue;

        if ( bAdded[ x ][ y ] == FALSE && GetPoint( x, y ) == target )
        {
            pts.push_back( CColorPoint( CPoint( x, y ), cpt.second ) );
            bAdded[ x ][ y ] = TRUE;
        }
    }
    return;
}

void CJGraphDoc::FinishDraw( const vector<CColorPoint> & cpts )
{
    UINT i;
    for ( i = 0; i < cpts.size(); ++i )
    {
        m_bitmap[ cpts[i].first.x ][ cpts[i].first.y ] += cpts[i].second;
        
        CPoint pt =  cpts[i].first;
        m_rectUpdate.left     = min( m_rectUpdate.left,    pt.x );
        m_rectUpdate.right    = max( m_rectUpdate.right,   pt.x );
        m_rectUpdate.top      = max( m_rectUpdate.top,     pt.y );
        m_rectUpdate.bottom   = min( m_rectUpdate.bottom,  pt.y );
    }

    while ( (int)m_vecHistory.size() - 1 > m_nHistoryPos )
        m_vecHistory.pop_back();

    m_vecHistory.push_back( cpts );
    m_nHistoryPos = (int)m_vecHistory.size() - 1;

    SetModifiedFlag( TRUE );
    UpdateAllViews( NULL );
}


void CJGraphDoc::Undo( )
{
    if ( m_nHistoryPos < 0 )
        return;
    
    vector<CColorPoint> & cpts = m_vecHistory[ m_nHistoryPos ];

    for ( UINT i = 0; i < cpts.size(); ++i )
        m_bitmap[ cpts[i].first.x ][ cpts[i].first.y ] -= cpts[i].second;

    m_nHistoryPos --;
    
    if ( m_nHistoryPos == -1 )
        SetModifiedFlag( FALSE );

    UpdateAllViews( NULL );
}

void CJGraphDoc::Redo( )
{
    if ( m_nHistoryPos == m_vecHistory.size() - 1 )
        return;

    vector<CColorPoint> & cpts = m_vecHistory[ m_nHistoryPos + 1 ];

    for ( UINT i = 0; i < cpts.size(); ++i )
        m_bitmap[ cpts[i].first.x ][ cpts[i].first.y ] += cpts[i].second;

    m_nHistoryPos ++;

    if ( m_nHistoryPos == -1 )
        SetModifiedFlag( FALSE );

    UpdateAllViews( NULL );
}

void CJGraphDoc::ScanFill( vector<CEdge> edges, vector<CEdge> & fills )
{
    using namespace std;
    map< int,vector<int> > interPoints;
    
    for ( UINT i = 0; i < edges.size(); ++i )
    {
        if ( edges[i].p1.y == edges[i].p2.y )
            continue;

        double dx = ( (double)edges[i].p1.x - edges[i].p2.x ) / ( (double)edges[i].p1.y - edges[i].p2.y );
        int maxy = ( edges[i].p1.y > edges[i].p2.y ) ? edges[i].p1.y : edges[i].p2.y;
        int miny = ( edges[i].p1.y < edges[i].p2.y ) ? edges[i].p1.y : edges[i].p2.y;
        double x = ( edges[i].p1.y < edges[i].p2.y ) ? edges[i].p1.x : edges[i].p2.x;
        for ( int y = miny; y <= maxy; ++y )
        {
            interPoints[y].push_back( (int)x );
            x += dx;
        }
    }
    

    map< int,vector<int> >::iterator it = interPoints.begin();
    for ( ; it != interPoints.end(); ++it )
    {
        sort( it->second.begin(), it->second.end() );
        //unique( i->second.begin(), i->second.end() );

        if ( it->second.size() < 2 )
            continue;
        
        CEdge e;
        for ( UINT j = 0; j < it->second.size(); j+=2 )
        {
            e.p1 = CPoint( it->second[j], it->first );
            e.p2 = CPoint( it->second[j+1], it->first );
            fills.push_back(e);
        }
    }
}