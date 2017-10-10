// ReadobjView.h : interface of the CReadobjView class
//
/////////////////////////////////////////////////////////////////////////////
#include <gl/gl.h>
#include <gl/glu.h>
#include <glut.h>
#if !defined(AFX_READOBJVIEW_H__B152A7CE_39F1_4613_B4ED_45F0F88DE251__INCLUDED_)
#define AFX_READOBJVIEW_H__B152A7CE_39F1_4613_B4ED_45F0F88DE251__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CReadobjView : public CView
{
protected: // create from serialization only
	CReadobjView();
	DECLARE_DYNCREATE(CReadobjView)

// Attributes
public:
	CReadobjDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadobjView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL OnEraseBkgnd();
	void DrawScene(CReadobjDoc *pDoc);
	void Init();
	BOOL bSetupPixelFormat();
	CClientDC * m_pDC;
	virtual ~CReadobjView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CReadobjView)
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	CPoint Posl;//获得当前点
	float m_xRotation;//m_xRotation是视点绕x轴的角度
	float m_yRotation;//m_yRotation是视点绕y轴的角度
	//float m_zRotation;
	float m_xTranslation;
	float m_yTranslation;//m_yTranslation是视点绕y轴的角度,opengl里默认y轴是上方向
	float m_Scaling;//缩放
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ReadobjView.cpp
inline CReadobjDoc* CReadobjView::GetDocument()
   { return (CReadobjDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READOBJVIEW_H__B152A7CE_39F1_4613_B4ED_45F0F88DE251__INCLUDED_)
