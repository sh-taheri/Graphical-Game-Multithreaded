
// game_finalView.h : interface of the Cgame_finalView class
//

#pragma once
#include "CHook.h"
#include "CFish.h"
#include "CISBitmap.h"

class Cgame_finalView : public CView
{
protected: // create from serialization only
	Cgame_finalView();
	DECLARE_DYNCREATE(Cgame_finalView)

// Attributes
public:
	Cgame_finalDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~Cgame_finalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	///////////////////////////////////////////////////
	CDC* m_pdcDisplayMemory;
	CBitmap* m_pBitmap;
	CSize m_sizeSource, m_sizeDest;
	//////////////////////////////////////////////////
	bool status_SNG,status_Op,status_Q;
	int flag_bitmap;
	int LBDown_Flag_newgame;
	int LBDown_Flag_options;
	int LBDown_Flag_quit;
	int b;
	CString boat_location[4];
	int counter_oxygen;
	int flag_diver;
	int score;
	int oxygen;
protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	void build_fish(int ID, CBitmap bitmap);
//	void Build_Fish(int ID, CBitmap bitmap, CDC dcMemdis, CDC* pDC);
	//void Build_Fish(int ID, CBitmap bitmap, CDC dcMemdis, CDC* pDC, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in game_finalView.cpp
inline Cgame_finalDoc* Cgame_finalView::GetDocument() const
   { return reinterpret_cast<Cgame_finalDoc*>(m_pDocument); }
#endif

