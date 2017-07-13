#include "stdafx.h"
#include "game_final.h"
#include "CFish.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CFish :: Fish_Move(){
	position.x+=2+type;
}
BOOL CFish :: incident(CPoint point,CDC* pDC){
      CRect r1(position,fish_size);
	  r1.DeflateRect(10,10,10,10);
	  if (r1.PtInRect(point))
		return true;
	else
		return false;

}