// JGraphView.h : CJGraphView ��Ľӿ�
//

#pragma once

using std::vector;

class CJGraphView : public CView
{
protected: // �������л�����
	CJGraphView();
	DECLARE_DYNCREATE(CJGraphView)

protected:
    CPoint m_ptStart;
    int m_nMode;
    COLORREF m_color;

// ����
public:
	CJGraphDoc * GetDocument() const;

// ����
public:
    void Draw( CPoint p1, CPoint p2 );
    void DrawLatestChange( );

// ��д
public:
	virtual void OnDraw( CDC * pDC );  // ��д�Ի��Ƹ���ͼ 
	virtual BOOL PreCreateWindow( CREATESTRUCT & cs );
    virtual void OnPrepareDC( CDC* pDC, CPrintInfo* pInfo );
    virtual void OnInitialUpdate();
    void OnUpdate( CView *, LPARAM , CObject * pHint );

protected:
    static enum mode_t { MODE_NONE, MODE_LINE, MODE_CIRCLE, MODE_ECLIPSE, MODE_FILL };
// ʵ��
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
// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:

};

#ifndef _DEBUG  // JGraphView.cpp �еĵ��԰汾
inline CJGraphDoc* CJGraphView::GetDocument() const
   { return reinterpret_cast<CJGraphDoc*>(m_pDocument); }
#endif

