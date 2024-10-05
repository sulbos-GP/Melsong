#include "stdAfx.h"
#include "pch.h"
#include "DrawDC.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


#define SAFE_DELETE_OBJECT(b)  		{ if ( b.GetSafeHandle() != NULL ) { b.DeleteObject(); } }

//CDrawDC�� �����ڴ� CBackDC Ŭ������ �������� ���ڿ� �����ϴ�
CDrawDC::CDrawDC(CDC &dc, CWnd *pWnd)
	: CBackDC(dc, pWnd)
{
}

//�Ҹ��ڴ� Ư���� ���� ����
CDrawDC::~CDrawDC(void)
{
}


void CDrawDC::DrawBitmap(int x, int y, CBitmap &bitmap)
{
	if (bitmap.GetSafeHandle() == NULL)
		return;

	BITMAP bm;
	bitmap.GetBitmap(&bm);

	CDC dcMem;
	dcMem.CreateCompatibleDC(this);
	CBitmap *pOldBitmap = (CBitmap *)dcMem.SelectObject(&bitmap);

	this->BitBlt(x, y, bm.bmWidth, bm.bmHeight, &dcMem, 0, 0, SRCCOPY);

	if (pOldBitmap != NULL)
		dcMem.SelectObject(pOldBitmap);
}

void CDrawDC::DrawStretchBitmap(int x, int y, int cx, int cy, CBitmap &bitmap)
{
	if (bitmap.GetSafeHandle() == NULL)
		return;

	BITMAP bm;
	bitmap.GetBitmap(&bm);

	CDC dcMem;
	dcMem.CreateCompatibleDC(this);
	CBitmap *pOldBitmap = (CBitmap *)dcMem.SelectObject(&bitmap);

	this->StretchBlt(x, y, cx, cy, &dcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

	if (pOldBitmap != NULL)
		dcMem.SelectObject(pOldBitmap);
}
