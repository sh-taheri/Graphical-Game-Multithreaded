
// game_finalDoc.cpp : implementation of the Cgame_finalDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "game_final.h"
#endif
#include "CISBitmap.h"
#include "game_finalDoc.h"

#include <propkey.h>
#include "CHook.h"
#include "CFish.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cgame_finalDoc

IMPLEMENT_DYNCREATE(Cgame_finalDoc, CDocument)

BEGIN_MESSAGE_MAP(Cgame_finalDoc, CDocument)
END_MESSAGE_MAP()


// Cgame_finalDoc construction/destruction

Cgame_finalDoc::Cgame_finalDoc()
{    
	// TODO: add one-time construction code here
	

}

Cgame_finalDoc::~Cgame_finalDoc()
{
}

BOOL Cgame_finalDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;


	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	
	return TRUE;
}




// Cgame_finalDoc serialization

void Cgame_finalDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void Cgame_finalDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void Cgame_finalDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void Cgame_finalDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Cgame_finalDoc diagnostics

#ifdef _DEBUG
void Cgame_finalDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cgame_finalDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cgame_finalDoc commands


//void Cgame_finalDoc::Draw_Items(CDC* pDC, CString string)
//{
//}


//CSize Cgame_finalDoc::Draw_Items(CDC* pDC, CString string, int Item_Spacement)
//{
//}


//int Cgame_finalDoc::Draw_Items(BOOL Status, int Item_Spacement, CDC* pDC, CString string)
//{
//
//	return ;
//}


//CSize Cgame_finalDoc::Draw_Items(int Item_Spacement, BOOL Status, CDC* pDC, CString string)
//{
//
//}
