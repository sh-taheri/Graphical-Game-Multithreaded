
// game_finalDoc.h : interface of the Cgame_finalDoc class
//


#pragma once
#include "CFish.h"
#include "CHook.h"
#include "CISBitmap.h"


class Cgame_finalDoc : public CDocument
{
protected: // create from serialization only
	Cgame_finalDoc();
	DECLARE_DYNCREATE(Cgame_finalDoc)

// Attributes
public:
	CFish fish[30]; 
	CFish diver;
	//int diver_bitmap;
	CString diver_bitmap;
	CString score_bitmap;


// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~Cgame_finalDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
//	void Draw_Items(CDC* pDC, CString string);
//	CSize Draw_Items(CDC* pDC, CString string, int Item_Spacement);
//	int Draw_Items(BOOL Status, int Item_Spacement, CDC* pDC, CString string);
//	CSize Draw_Items(int Item_Spacement, BOOL Status, CDC* pDC, CString string);
};
