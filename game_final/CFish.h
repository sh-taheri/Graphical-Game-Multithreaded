
#if !defined(AFX_NOTESVIEW_H__155489BF_0B24_4D59_B185_74715A0762F7__INCLUDED_)
#define AFX_NOTESVIEW_H__155489BF_0B24_4D59_B185_74715A0762F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFish {
public:
	CFish(){};
	~CFish() {};
	void Fish_Move();
	BOOL incident(CPoint point,CDC* pDC);
	double type;
	CPoint position;
	CSize fish_size;
};
#endif // !defined(AFX_NOTESVIEW_H__155489BF_0B24_4D59_B185_74715A0762F7__INCLUDED_)