// JGraphView.h : CJGraphView 类的接口
//

#pragma once

using std::vector;

class CJGraphView : public CView
{
protected: // 仅从序列化创建
	CJGraphView();
	DECLARE_DYNCREATE(CJGraphView)

protected:
    CPoint m_ptStart;
    int m_nMode;
    COLORREF m_color;

// 属性
public:
	CJGraphDoc * GetDocument() const;

// 操作
public:
    void Draw( CPoint p1, CPoint p2 );
    void DrawLatestChange( );

// 重写
public:
	virtual void OnDraw( CDC * pDC );  // 重写以绘制该视图 
	virtual BOOL PreCreateWindow( CREATESTRUCT & cs );
    virtual void OnPrepareDC( CDC* pDC, CPrintInfo* pInfo );
    virtual void OnInitialUpdate();
    void OnUpdate( CView *, LPARAM , CObject * pHint );

protected:
    static enum mode_t { MODE_NONE, MODE_LINE, MODE_CIRCLE, MODE_ECLIPSE, MODE_FILL };
// 实现
public:
	virtual ~CJGraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext & dc) const;
#endif

protected:
    //{{AFX_MSG(CScribbleView)
    afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
    afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
    afx_msg void OnMouseMove( UINT nFlags, CPoint point );
    afx_msg void OnEditUndo();
    afx_msg void OnEditRedo();
    afx_msg void OnDrawLine();
    afx_msg void OnDrawDefault();
    afx_msg void OnDrawCircle();
    afx_msg void OnDrawEclipse();
    afx_msg void OnDrawFill();
    afx_msg void OnSelectColor();
    //}}AFX_MSG
// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:

};

#ifndef _DEBUG  // JGraphView.cpp 中的调试版本
inline CJGraphDoc* CJGraphView::GetDocument() const
   { return reinterpret_cast<CJGraphDoc*>(m_pDocument); }
#endif

