// CISBitmap.h: interface for the CCISBitmap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CISBITMAP_H__08BA6EB3_DB4C_11D1_8A89_0040052E2D91__INCLUDED_)
#define AFX_CISBITMAP_H__08BA6EB3_DB4C_11D1_8A89_0040052E2D91__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CCISBitmap : public CBitmap  
{
public:
	CCISBitmap();
	virtual ~CCISBitmap();

	// Functions
	// returns the height of the bitmap
	int Height();

	// returns the width of the bitmap
	int Width();	

	// reads the bitmap from the file
	bool LoadBMP(CString FN);

	// draws the bitmaps 
	// x0,y0: top and left point of the drawing rect
	// w,h  : width and height of the drawing rect
	// DrawBorder: if true, draws a border around the bmp
	virtual void DrawTransparent(CDC* pDC, int x0, int y0, int w, int h, COLORREF crColour,bool DrawBorder=false);	

	// returns where the bmp has been drawn the last time
	CRect GetDrawingPos();
private:
	COLORREF	m_crBlack;
	COLORREF	m_crWhite;
	HBITMAP hBmp;
	CRect DrawingPos;
};

#endif // !defined(AFX_CISBITMAP_H__08BA6EB3_DB4C_11D1_8A89_0040052E2D91__INCLUDED_)
