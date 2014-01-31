// JGraphDoc.h : CJGraphDoc ��Ľӿ�
//


#pragma once

using std::vector;
using std::pair;
typedef pair<CPoint,int> CColorPoint;

class CJGraphDoc : public CDocument
{
protected: // �������л�����
	CJGraphDoc();
	DECLARE_DYNCREATE(CJGraphDoc)

// ����
protected:
    CSize   m_sizeDoc;
    CRect   m_rectUpdate;
    vector< vector<COLORREF> >    m_bitmap;
    vector< vector<CColorPoint> >   m_vecHistory;
    int     m_nHistoryPos;
    
// ����
public:
    CSize   GetDocSize() { return m_sizeDoc; }
    CRect   GetUpdateRect() { return m_rectUpdate; }

    vector<CColorPoint> GetLatestChange();
    vector<CColorPoint> GetNextUndo();
    vector<CColorPoint> GetNextRedo();

    COLORREF    GetPoint( int x, int y );

    void    Undo( );
    void    Redo( );
    void    DrawLine( CPoint ptStart, CPoint ptEnd, COLORREF color );
    void    DrawCircle( CPoint ptStart, CPoint ptEnd, COLORREF color );
    void    DrawCircularArc( CPoint ptCenter, double r, double t1, double t2, COLORREF color );
    void    DrawEclipse( CPoint ptStart, CPoint ptEnd, COLORREF color );
    void    DrawEclipseArc( CPoint ptCenter, int a, int b, double t1, double t2, COLORREF color );
    void    FillArea( CPoint ptStart, COLORREF color );
    void    FillArea( CColorPoint pt, COLORREF target, vector<vector<BOOL>> & bAdded, vector<CColorPoint> & pts );
    void    ScanFill( vector<CEdge> edges, vector<CEdge> & fills );
    void    FinishDraw( const vector<CColorPoint> & pts );


// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CJGraphDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    void InitDocument();

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


