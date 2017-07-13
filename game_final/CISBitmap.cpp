// CISBitmap.cpp: implementation of the CCISBitmap class.
// Author:	Paul Reynolds 
// Date:	24/04/1998
// Version:	1.0
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CISBitmap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCISBitmap::CCISBitmap()
{
	m_crBlack = 0;
	m_crWhite = RGB(255,255,255);
	hBmp=0;
}

CCISBitmap::~CCISBitmap()
{

}

bool CCISBitmap::LoadBMP(CString FN)
{
	if(hBmp)
		Detach();
	hBmp = (HBITMAP)::LoadImage(NULL,FN,
		IMAGE_BITMAP,0,0,
		LR_LOADFROMFILE|LR_CREATEDIBSECTION);	
	if(hBmp)
	{
		Attach(hBmp);	
		return true;
	}
	else{
		AfxMessageBox(_T("Could not open ")+FN);
		return false;
	}
}

int CCISBitmap::Width()
{
	BITMAP bm;
	GetBitmap(&bm);
	return bm.bmWidth;
}

int CCISBitmap::Height()
{
	BITMAP bm;
	GetBitmap(&bm);
	return bm.bmHeight;
}

void CCISBitmap::DrawTransparent(CDC * pDC, int x0, int y0, int w, int h,COLORREF crColour,bool DrawBorder)
{
	COLORREF crOldBack = pDC->SetBkColor(m_crWhite);
	COLORREF crOldText = pDC->SetTextColor(m_crBlack);
	CDC dcImage, dcTrans;

	// Create two memory dcs for the image and the mask
	dcImage.CreateCompatibleDC(pDC);
	dcTrans.CreateCompatibleDC(pDC);

	// Select the image into the appropriate dc
	CBitmap* pOldBitmapImage = dcImage.SelectObject(this);

	// Create the mask bitmap
	CBitmap bitmapTrans;
	int nWidth = Width();
	int nHeight = Height();
	bitmapTrans.CreateBitmap(nWidth, nHeight, 1, 1, NULL);

	// Select the mask bitmap into the appropriate dc
	CBitmap* pOldBitmapTrans = dcTrans.SelectObject(&bitmapTrans);

	// Build mask based on transparent colour
	dcImage.SetBkColor(crColour);
	dcTrans.BitBlt(0, 0, nWidth, nHeight, &dcImage, 0, 0, SRCCOPY);

	// Do the work - True Mask method - cool if not actual display
//	pDC->BitBlt(x, y, nWidth, nHeight, &dcImage, 0, 0, SRCINVERT);
//	pDC->BitBlt(x, y, nWidth, nHeight, &dcTrans, 0, 0, SRCAND);
//	pDC->BitBlt(x, y, nWidth, nHeight, &dcImage, 0, 0, SRCINVERT);

	pDC->StretchBlt(x0, y0, w, h, &dcImage, 0, 0,nWidth,nHeight, SRCINVERT);
	pDC->StretchBlt(x0, y0, w, h, &dcTrans, 0, 0,nWidth,nHeight, SRCAND);
	pDC->StretchBlt(x0, y0, w, h, &dcImage, 0, 0,nWidth,nHeight, SRCINVERT);

	DrawingPos=CRect(x0,y0,x0+w,y0+h);

	// Restore settings
	dcImage.SelectObject(pOldBitmapImage);
	dcTrans.SelectObject(pOldBitmapTrans);
	pDC->SetBkColor(crOldBack);
	pDC->SetTextColor(crOldText);

	if(DrawBorder)
	{
		CPen Pen1,*Pen0;
		Pen1.CreatePen(PS_SOLID,4,0x0ff);
		Pen0=pDC->SelectObject(&Pen1);
		pDC->MoveTo(x0,y0);
		pDC->LineTo(x0+w,y0);
		pDC->LineTo(x0+w,y0+h);
		pDC->LineTo(x0,y0+h);
		pDC->LineTo(x0,y0);
		pDC->SelectObject(Pen0);
		Pen1.DeleteObject();
	}
}

CRect CCISBitmap::GetDrawingPos()
{
	return DrawingPos;
}