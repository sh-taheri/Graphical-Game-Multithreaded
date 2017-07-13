
// game_finalView.cpp : implementation of the Cgame_finalView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "game_final.h"
#endif
#include "CISBitmap.h"
#include "game_finalDoc.h"
#include "game_finalView.h"
#include "CFish.h"
#include "CHook.h"
#include <MMSystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define VK_LEFT 0x25
#define VK_UP 0x26
#define VK_RIGHT 0x27
#define VK_DOWN 0x28

////////////////////Global Variables///////////////////
 CSize size_text1,size_text2,size_text3;


// Cgame_finalView

IMPLEMENT_DYNCREATE(Cgame_finalView, CView)

BEGIN_MESSAGE_MAP(Cgame_finalView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cgame_finalView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// Cgame_finalView construction/destruction

Cgame_finalView::Cgame_finalView()
{
	// TODO: add construction code here
	m_pdcDisplayMemory=new CDC;
	m_pBitmap=new CBitmap;
	status_SNG=false;
	status_Op=false;
	status_Q=false;
	flag_bitmap=1;
    LBDown_Flag_newgame=0;
	LBDown_Flag_options=0;
	LBDown_Flag_quit=0;
	b=0;
	score=0;
	counter_oxygen=0;
	oxygen=6;
	
}

Cgame_finalView::~Cgame_finalView()
{
	delete m_pdcDisplayMemory; 
	delete m_pBitmap;
}

//void Cgame_finalView::Build_Fish(int ID, CBitmap bitmap, CDC dcMemdis, CDC* pDC, CPoint point)
//{
//	bitmap.LoadBitmap(ID);
//	dcMemdis.CreateCompatibleDC(pDC);
//	dcMemdis.SelectObject(&bitmap);
//	pDC->BitBlt(0,0,2000,2000,&dcMemdis,0,0,SRCCOPY);
//}

BOOL Cgame_finalView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Cgame_finalView drawing

void Cgame_finalView::OnDraw(CDC* pDC)
{
	Cgame_finalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int n=0;
	// TODO: add draw code for native data here
	if(LBDown_Flag_newgame==0){

	CBitmap bitmap;
	CDC dcDisplayMemory;
	CRect R1;
	GetClientRect(&R1);
	//pDC->StretchBlt(200,200,R1.Width(),R1.Height(),m_pdcDisplayMemory,0,0,R1.Width(),R1.Height(),SRCCOPY);
	bitmap.LoadBitmap(IDB_BITMAP22);
	dcDisplayMemory.CreateCompatibleDC(pDC);
	dcDisplayMemory.SelectObject(&bitmap);
	pDC->BitBlt(0,0,2000,2000,&dcDisplayMemory,0,0,SRCCOPY);
	//flag_bitmap=0;
	//pDC->StretchBlt(20,20,m_sizeDest.cx,m_sizeDest.cy,m_pdcDisplayMemory,0,0,m_sizeSource.cx,m_sizeSource.cy,SRCCOPY);
	/////////////////////////drawing options,new game and........////////////////////////////
 
 CFont F1,F2,*F0;
 F1.CreateFont(40,0,0,0,FW_HEAVY,false,false,false,ANSI_CHARSET,0,0,0,0,_T("Comic Sans MS"));
 F2.CreateFont(45,0,0,0,FW_HEAVY,false,false,false,ANSI_CHARSET,0,0,0,0,_T("Comic Sans MS"));
 pDC->SetBkMode(TRANSPARENT);
 //F0=pDC->SelectObject(&F1);

 //size_text1=pDC->GetTextExtent(_T("Start New Game"));
 //size_text2=pDC->GetTextExtent(_T("Options"));
 //size_text3=pDC->GetTextExtent(_T("Quit"));
 //////////////dar surate chap click nashodan rooye new game!!/////////////
 
 if(status_SNG){
	 F0=pDC->SelectObject(&F2);
	 size_text1=pDC->GetTextExtent(_T("Start New Game"));
     pDC->SetTextColor(0xe80000);}
 else{
	 F0=pDC->SelectObject(&F1);
	 size_text1=pDC->GetTextExtent(_T("Start New Game"));
	 pDC->SetTextColor(0x000000);
 }
 pDC->TextOut(R1.Width()/2-size_text1.cx/2,0.5*R1.Height(),_T("Start New Game"));
 //status_SNG=false;

  if(status_Op){
	  F0=pDC->SelectObject(&F2);
	  size_text2=pDC->GetTextExtent(_T("Options"));
      pDC->SetTextColor(0xe80000);
  }
  else{
	  F0=pDC->SelectObject(&F1);
	  size_text2=pDC->GetTextExtent(_T("Options"));
	  pDC->SetTextColor(0x000000);
  }
      pDC->TextOut(R1.Width()/2-size_text2.cx/2,0.5*R1.Height()+60,_T("Options"));
 //status_Op=false;

  if(status_Q){
	  F0=pDC->SelectObject(&F2);
	  size_text3=pDC->GetTextExtent(_T("Quit"));
      pDC->SetTextColor(0xe80000);
  }
 else{
	 F0=pDC->SelectObject(&F1);
	 size_text3=pDC->GetTextExtent(_T("Quit"));
	 pDC->SetTextColor(0x000000);
 }
 pDC->TextOut(R1.Width()/2-size_text3.cx/2,0.5*R1.Height()+120,_T("Quit"));
//status_Q=false;
 }
	
////////////////////////////////////starting game////////////////////////////////
 else{
	n++;
	CString score_string;
	CString s1;
	CFont F3;
	score_string.Format(_T("Score: %05d"),score);
	pDC->SetBkMode(TRANSPARENT);
	F3.CreateFont(30,0,0,0,FW_HEAVY,false,false,false,ANSI_CHARSET,0,0,0,0,_T("Comic Sans MS"));
	pDC->SelectObject(&F3);
	if (score<10)
	pDC->SetTextColor(RGB(255,0,0));
	else
	pDC->SetTextColor(RGB(4,111,227));
	pDC->TextOut(100,30,score_string);
	//CBitmap bitmap_fish[31];
	//CDC dcDisplayMemory_fish[31];


	//CBitmap bitmap_diver;
	//CDC dcDisplayMemory_diver;

	CCISBitmap bitmap_fish[31];
	CCISBitmap bitmap_diver;
	CCISBitmap bitmap_boat;
	CCISBitmap bitmap_score;

	CRect R1;
	GetClientRect(&R1);

	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC,R1.Width(),R1.Height());

		CBitmap* pOldBitmap = dcMemory.SelectObject(&bmp);

	//int bitmap_ID[30]={314,315,314,316,316,315, 314,316,315,315,316,315, 314,315,316,314,314,316,
	//	               315,316,316,314,316,316, 315,314,316,314,316,316};

	CString bitmap_name[30]={_T("type_1.bmp"),_T("type_2.bmp"),_T("type_1.bmp"),_T("type_3.bmp"),_T("type_3.bmp"),_T("type_2.bmp"),_T("type_1.bmp")
		,_T("type_3.bmp"),_T("type_2.bmp"),_T("type_2.bmp"),_T("type_3.bmp"),_T("type_2.bmp"),_T("type_1.bmp"),_T("type_2.bmp"),_T("type_3.bmp")
		,_T("type_1.bmp"),_T("type_1.bmp"),_T("type_3.bmp"),_T("type_2.bmp"),_T("type_3.bmp"),_T("type_3.bmp"),_T("type_1.bmp"),_T("type_3.bmp")
		,_T("type_3.bmp"),_T("type_2.bmp"),_T("type_1.bmp"),_T("type_3.bmp"),_T("type_1.bmp"),_T("type_3.bmp"),_T("type_3.bmp")};

	CString directory(_T("bitmaps\\"));

	//bitmap_fish[0].LoadBitmap(IDB_BITMAP4);
	//dcDisplayMemory_fish[0].CreateCompatibleDC(pDC);
	//dcDisplayMemory_fish[0].SelectObject(&bitmap_fish[0]);
	//pDC->BitBlt(0,100,2000,2000,&dcDisplayMemory_fish[0],0,0,SRCCOPY);
	
	bitmap_fish[0].LoadBMP(_T("bitmaps\\Sea.bmp"));
	bitmap_fish[0].DrawTransparent(&dcMemory,0,100,R1.Width(),R1.Height()-100,RGB(0,0,0),false);
	

	//RGB(0,154,252)

	if(n==1)
	SetTimer(1,0,NULL);
	//SetTimer(1,100,NULL);
	
	for(int i=0;i<30;i++){
		CString FullDirectory=directory + bitmap_name[i];
			bitmap_fish[i+1].LoadBMP(FullDirectory);
			if (pDoc->fish[i].type==1)
			bitmap_fish[i+1].DrawTransparent(&dcMemory,pDoc->fish[i].position.x,pDoc->fish[i].position.y,91,67,RGB(4,111,227),false);
			if (pDoc->fish[i].type==2)
			bitmap_fish[i+1].DrawTransparent(&dcMemory,pDoc->fish[i].position.x,pDoc->fish[i].position.y,74,67,RGB(4,111,227),false);
					if (pDoc->fish[i].type==3)
			bitmap_fish[i+1].DrawTransparent(&dcMemory,pDoc->fish[i].position.x,pDoc->fish[i].position.y,99,62,RGB(4,111,227),false);

	//bitmap_fish[i+1].LoadBitmap(bitmap_ID[i]);
	//dcDisplayMemory_fish[i+1].CreateCompatibleDC(pDC);
	//dcDisplayMemory_fish[i+1].SelectObject(&bitmap_fish[i+1]);
	//pDC->BitBlt(pDoc->fish[i].position.x,pDoc->fish[i].position.y,500,500,&dcDisplayMemory_fish[i+1],0,0,SRCCOPY);
	}

		//for(int i=0;i<30;i++)
  //  bitmap_fish[i].DeleteObject();



	//bitmap_diver.LoadBitmap(pDoc->diver_bitmap);
	//dcDisplayMemory_diver.CreateCompatibleDC(pDC);
	//dcDisplayMemory_diver.SelectObject(&bitmap_diver);
	//pDC->BitBlt(pDoc->diver.position.x,pDoc->diver.position.y,500,500,&dcDisplayMemory_diver,0,0,SRCCOPY);
	//bitmap_diver.DeleteObject();

	CString FullDirectory=directory + pDoc->diver_bitmap;
	bitmap_diver.LoadBMP(FullDirectory);
	bitmap_diver.DrawTransparent(&dcMemory,pDoc->diver.position.x,pDoc->diver.position.y,118,114,RGB(4,111,227),false);

	//////////////////////////////////////////boat //////////////////////////////////////////////////////////////
	CString FullDirectory1=directory + boat_location[b];
	bitmap_boat.LoadBMP(FullDirectory1);
	bitmap_boat.DrawTransparent(&dcMemory,0,0,R1.Width(),105,RGB(0,0,0),false);
	//bitmap_boat.LoadBitmap(boat_location[b]);
	//dcDisplayMemory_boat.CreateCompatibleDC(pDC);
	//dcDisplayMemory_boat.SelectObject(&bitmap_boat[b]);
	//pDC->BitBlt(2,2,4000,4000,&dcDisplayMemory_boat,0,0,SRCCOPY);
	b++;
	if(b==4)
		b=0;
	CString FullDirectory2=directory + pDoc->score_bitmap;
	bitmap_score.LoadBMP(FullDirectory2);
	bitmap_score.DrawTransparent(&dcMemory,2,2,80,70,RGB(255,255,255),false);

	
	pDC->BitBlt(0,0,R1.Width(),R1.Height(), &dcMemory, 0,0, SRCCOPY);


 /*   bitmap[1].DeleteObject();
	bitmap[2].DeleteObject();
	bitmap[3].DeleteObject();
	bitmap[4].DeleteObject();
	bitmap[5].DeleteObject();*/

	//dcDisplayMemory[0].DeleteTempMap();
	for (int i=0;i<31;i++)
	bitmap_fish[i].DeleteObject();
	bitmap_diver.DeleteObject();
    bitmap_boat.DeleteObject();
	bitmap_score.DeleteObject();
	bmp.DeleteObject();
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
    

}
///////////////thread for fish & diver movement simultaneously///////////////
#include <AFXMT.H>

CEvent EventStart;
CEvent EventStop;

UINT Thread1(LPVOID v)
{
	Cgame_finalView *view=(Cgame_finalView *)v;
	for(;;)
	{
		Sleep(100);	
		Cgame_finalDoc* pDoc =view->GetDocument();
	CClientDC dc(view);
	CRect R1;
	view->GetClientRect(&R1);
	for(int i=0;i<30;i++){
	pDoc->fish[i].Fish_Move();
	if(pDoc->fish[i].position.x>=R1.Width())
	   pDoc->fish[i].position.x=-100;
	}

	for (int i=0;i<30;i++){
		bool res=pDoc->fish[i].incident(CPoint(pDoc->diver.position.x,pDoc->diver.position.y+40),&dc); //40=diver.Height()*(1/3)
	if(res){

		if (pDoc->fish[i].type==1)
		{view->score+=5;pDoc->fish[i].position.x=-200;}
		if (pDoc->fish[i].type==2)
		{view->score+=10;pDoc->fish[i].position.x=-200;}
		if (pDoc->fish[i].type==3)
		{view->score-=4;}

	       }
	}
	view->counter_oxygen++;
	if(view->counter_oxygen==100)
		view->oxygen--;
	if(view->oxygen==0)
		view->MessageBox(_T("OopS!!! You're Dead !!"));
    
	}
}



// Cgame_finalView printing


void Cgame_finalView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cgame_finalView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Cgame_finalView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Cgame_finalView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void Cgame_finalView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cgame_finalView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cgame_finalView diagnostics

#ifdef _DEBUG
void Cgame_finalView::AssertValid() const
{
	CView::AssertValid();
}

void Cgame_finalView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cgame_finalDoc* Cgame_finalView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cgame_finalDoc)));
	return (Cgame_finalDoc*)m_pDocument;
}
#endif //_DEBUG


// Cgame_finalView message handlers


void Cgame_finalView::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	CRect R1;
	GetClientRect(R1);

	 CFont F1,*F0;
     F1.CreateFont(40,0,0,0,FW_HEAVY,false,false,false,ANSI_CHARSET,0,0,0,0,_T("Times New Roman"));
     F0=dc.SelectObject(&F1);

	CSize size_text1,size_text2,size_text3; 
	size_text1=dc.GetTextExtent(_T("Start New Game"));
	CRect Text_startnewgame(R1.Width()/2-size_text1.cx/2, 0.5*R1.Height(), R1.Width()/2+size_text1.cx/2, 0.5*R1.Height()+size_text1.cy);
	bool old_status_SNG=status_SNG;
	bool old_status_Op=status_Op;
	bool old_status_Q=status_Q;
	/*dc.SetMapMode(MM_HIMETRIC);
	dc.LPtoDP(Text_startnewgame);*/
	if(Text_startnewgame.PtInRect(point)){
		status_SNG=true;
	}
	else
		status_SNG=false;

	size_text2=dc.GetTextExtent(_T("Options"));
	CRect Text_options(R1.Width()/2-size_text2.cx/2, 0.5*R1.Height()+60, R1.Width()/2+size_text2.cx/2, 0.5*R1.Height()+size_text2.cy+60);

	/*dc.SetMapMode(MM_HIMETRIC);
	dc.LPtoDP(Text_options);*/
	if(Text_options.PtInRect(point)){
		status_Op=true;
	}
	else
		status_Op=false;

	size_text3=dc.GetTextExtent(_T("Quit"));
	CRect Text_quit(R1.Width()/2-size_text3.cx/2, 0.5*R1.Height()+120, R1.Width()/2+size_text3.cx/2, 0.5*R1.Height()+size_text3.cy+120);
	
	/*dc.SetMapMode(MM_HIMETRIC);
	dc.LPtoDP(Text_quit);*/
	if(Text_quit.PtInRect(point)){
		status_Q=true;
	}
	else
		status_Q=false;

	if ( (old_status_SNG!=status_SNG) || (old_status_Op!=status_Op) || (old_status_Q!=status_Q))
	Invalidate(false);


    
	
	// TODO: Add your message handler code here and/or call default

	CView::OnMouseMove(nFlags, point);
}


void Cgame_finalView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
    PlaySoundW(_T("bitmaps\\Baby Vivaldi 3.wav"), 0, SND_FILENAME|SND_LOOP|SND_ASYNC);

	Cgame_finalDoc* pDoc = GetDocument();
	CRect R1;
	GetClientRect(&R1);
	int fish_height[6];
	for(int i=0;i<6;i++)
		fish_height[i]=100+((R1.Height()-100)/6)*i+5;
	pDoc->fish[0].position=CPoint(-1,fish_height[0]);pDoc->fish[0].type=1;  	pDoc->fish[15].position=CPoint(-842,fish_height[3]);pDoc->fish[15].type=1;
	pDoc->fish[1].position=CPoint(-1,fish_height[1]);pDoc->fish[1].type=2;	    pDoc->fish[16].position=CPoint(-830,fish_height[4]);pDoc->fish[16].type=1;
    pDoc->fish[2].position=CPoint(-1,fish_height[2]);pDoc->fish[2].type=1;	    pDoc->fish[17].position=CPoint(-841,fish_height[5]);pDoc->fish[17].type=3;
    pDoc->fish[3].position=CPoint(-10,fish_height[3]);pDoc->fish[3].type=3;	    pDoc->fish[18].position=CPoint(-1250,fish_height[0]);pDoc->fish[18].type=2;
    pDoc->fish[4].position=CPoint(-1,fish_height[4]);pDoc->fish[4].type=3;	    pDoc->fish[19].position=CPoint(-1280,fish_height[1]);pDoc->fish[19].type=3;
    pDoc->fish[5].position=CPoint(-5,fish_height[5]);pDoc->fish[5].type=2;      pDoc->fish[20].position=CPoint(-1230,fish_height[2]);pDoc->fish[20].type=3;
	pDoc->fish[6].position=CPoint(-400,fish_height[0]);pDoc->fish[6].type=1;	    pDoc->fish[21].position=CPoint(-1259,fish_height[3]);pDoc->fish[21].type=1;
	pDoc->fish[7].position=CPoint(-480,fish_height[1]);pDoc->fish[7].type=3;	    pDoc->fish[22].position=CPoint(-1230,fish_height[4]);pDoc->fish[22].type=3;
	pDoc->fish[8].position=CPoint(-420,fish_height[2]);pDoc->fish[8].type=2;     pDoc->fish[23].position=CPoint(-1244,fish_height[5]);pDoc->fish[23].type=3;
	pDoc->fish[9].position=CPoint(-430,fish_height[3]);pDoc->fish[9].type=2;     pDoc->fish[24].position=CPoint(-1670,fish_height[0]);pDoc->fish[24].type=2;
	pDoc->fish[10].position=CPoint(-435,fish_height[4]);pDoc->fish[10].type=3;	pDoc->fish[25].position=CPoint(-1667,fish_height[1]);pDoc->fish[25].type=1;
	pDoc->fish[11].position=CPoint(-437,fish_height[5]);pDoc->fish[11].type=2;	pDoc->fish[26].position=CPoint(-1674,fish_height[2]);pDoc->fish[26].type=3;
	pDoc->fish[12].position=CPoint(-840,fish_height[0]);pDoc->fish[12].type=1;	pDoc->fish[27].position=CPoint(-1678,fish_height[3]);pDoc->fish[27].type=1;
	pDoc->fish[13].position=CPoint(-847,fish_height[1]);pDoc->fish[13].type=2;	pDoc->fish[28].position=CPoint(-1680,fish_height[4]);pDoc->fish[28].type=3;
	pDoc->fish[14].position=CPoint(-850,fish_height[2]);pDoc->fish[14].type=3;	pDoc->fish[29].position=CPoint(-1690,fish_height[5]);pDoc->fish[29].type=3;

     boat_location[0]=_T("boatpos1.bmp");
	 boat_location[1]=_T("boatpos2.bmp");
	 boat_location[2]=_T("boatpos3.bmp");
	 boat_location[3]=_T("boatpos4.bmp");

	for (int i=0;i<30;i++)
	{
	   if(pDoc->fish[i].type==1)
	      pDoc->fish[i].fish_size=CSize(91,67);

	   if(pDoc->fish[i].type==2)
	     pDoc->fish[i].fish_size=CSize(74,67);

	   if(pDoc->fish[i].type==3)
	     pDoc->fish[i].fish_size=CSize(99,62);
	}

	pDoc->diver.position=CPoint(0.75*R1.Width(),0.5*R1.Height());
	//pDoc->diver_bitmap=IDB_BITMAP19;
	pDoc->diver_bitmap=_T("diver.bmp");
	flag_diver=0;
	pDoc->score_bitmap=_T("fishy1.bmp");



	

    
	/*CClientDC dc(this);
	dc.SetMapMode(MM_HIMETRIC);*/

}



void Cgame_finalView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect R1;
	GetClientRect(&R1);

	CRect R_FirstItem (R1.Width()/2-size_text1.cx/2, 0.5*R1.Height(), R1.Width()/2+size_text1.cx/2, 0.5*R1.Height()+size_text1.cy);
	if(R_FirstItem.PtInRect(point)&&LBDown_Flag_newgame==0)
	{LBDown_Flag_newgame=1;AfxBeginThread(Thread1,this,THREAD_PRIORITY_NORMAL);Invalidate(false);
	PlaySoundW(0,0,0);
	PlaySoundW(_T("bitmaps\\Baby Vivaldi 1.wav"), 0, SND_FILENAME|SND_LOOP|SND_ASYNC);}
	

	CRect R_SecondItem (R1.Width()/2-size_text2.cx/2, 0.5*R1.Height()+60, R1.Width()/2+size_text2.cx/2, 0.5*R1.Height()+size_text2.cy+60);
	if(R_SecondItem.PtInRect(point)&&LBDown_Flag_options==0)
	{LBDown_Flag_options=1;Invalidate(false);}

	CRect R_ThirdItem (R1.Width()/2-size_text3.cx/2, 0.5*R1.Height()+120, R1.Width()/2+size_text3.cx/2, 0.5*R1.Height()+size_text3.cy+120);
	if(R_ThirdItem.PtInRect(point)&&LBDown_Flag_quit==0)
    {LBDown_Flag_quit=1;Invalidate(false);}
	


	//size_text1=pDC->GetTextExtent(_T("Start New Game"));
	//pDC->TextOut(R1.Width()/2-size_text1.cx/2,0.5*R1.Height(),_T("Start New Game"));


	CView::OnLButtonDown(nFlags, point);
}


void Cgame_finalView::OnTimer(UINT_PTR nIDEvent)
{
//	// TODO: Add your message handler code here and/or call default
	//Cgame_finalDoc* pDoc = GetDocument();
	//CClientDC dc(this);
	//CRect R1;
	//GetClientRect(&R1);
	//for(int i=0;i<30;i++){
	//pDoc->fish[i].Fish_Move();
	//if(pDoc->fish[i].position.x>=R1.Width())
	//   pDoc->fish[i].position.x=-100;
	//}

	//for (int i=0;i<30;i++){
	//	bool res=pDoc->fish[i].incident(CPoint(pDoc->diver.position.x,pDoc->diver.position.y+40),&dc); //40=diver.Height()*(1/3)
	//if(res){
	//	pDoc->fish[i].position.x=-200;
	//	if (pDoc->fish[i].type==1)
	//		score+=5;
	//	if (pDoc->fish[i].type==2)
	//		score+=10;
	//	if (pDoc->fish[i].type==3)
	//		score-=4;
	//       }
	//}
	//counter_oxygen++;
	//if(counter_oxygen==100)
	//	oxygen--;
	//if(oxygen==0)
	//	MessageBox(_T("OopS!!! You're Dead !!"));
 //   

	Invalidate(false);
//
	CView::OnTimer(nIDEvent);
}


//void Cgame_finalView::build_fish(int ID, CBitmap bitmap)
//{
//	bitmap.LoadBitmap(IDB_BITMAP1);
//	dcDisplayMemory.CreateCompatibleDC(pDC);
//	dcDisplayMemory.SelectObject(&bitmap);
//	pDC->BitBlt(0,0,2000,2000,&dcDisplayMemory,0,0,SRCCOPY);
//}


//void Cgame_finalView::Build_Fish(int ID, CBitmap bitmap, CDC dcMemdis, CDC* pDC)
//{
//
//	bitmap.LoadBitmap(ID);
//	dcMemdis.CreateCompatibleDC(pDC);
//	dcMemdis.SelectObject(&bitmap);
//	pDC->BitBlt(0,0,2000,2000,&dcMemdis,0,0,SRCCOPY);
//}





void Cgame_finalView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{    
	// TODO: Add your message handler code here and/or call default
	Cgame_finalDoc* pDoc = GetDocument();
	CRect R1;
	GetClientRect(&R1);
	if (nChar==VK_UP)
	   {
		   if(pDoc->diver.position.y<110)
	       pDoc->diver.position.y=100;
	   else 
	      pDoc->diver.position.y-=10;
	} 
	if (nChar==VK_DOWN)
	   {if(pDoc->diver.position.y+118> R1.Height())
	       pDoc->diver.position.y=R1.Height()-118;
	   else 
	      pDoc->diver.position.y+=10;
	}  
	if (nChar==VK_LEFT)
	     {if(pDoc->diver.position.x<0)
	       pDoc->diver.position.x=0;
	   else 
	      pDoc->diver.position.x-=10;
	      /*pDoc->diver_bitmap=IDB_BITMAP19;*/ pDoc->diver_bitmap=_T("diver.bmp"); }
	if (nChar==VK_RIGHT)
	        {if(pDoc->diver.position.x+114>R1.Width())
	       pDoc->diver.position.x=R1.Width()-114;
	   else 
	      pDoc->diver.position.x+=10;
	     /* pDoc->diver_bitmap=IDB_BITMAP20;*/pDoc->diver_bitmap=_T("diver_reverse.bmp");}

	flag_diver=1;
	Invalidate(false);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
