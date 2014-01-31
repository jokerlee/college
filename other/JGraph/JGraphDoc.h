// JGraphDoc.h : CJGraphDoc 类的接口
//


#pragma once

using std::vector;
using std::pair;
typedef pair<CPoint,int> CColorPoint;

class CJGraphDoc : public CDocument
{
protected: // 仅从序列化创建
	CJGraphDoc();
	DECLARE_DYNCREATE(CJGraphDoc)

// 属性
protected:
    CSize   m_sizeDoc;
    CRect   m_rectUpdate;
    vector< vector<COLORREF> >    m_bitmap;
    vector< vector<CColorPoint> >   m_vecHistory;
    int     m_nHistoryPos;
    
// 操作
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


// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CJGraphDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    void InitDocument();

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};


