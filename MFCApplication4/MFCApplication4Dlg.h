
// MFCApplication4Dlg.h: 헤더 파일
//

#if _MSC_VER > 1000
#pragma once
#endif 
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

// CMFCApplication4Dlg 대화 상자
class CMFCApplication4Dlg : public CDialogEx
{
// 생성입니다.
public:
	CBitmap  bt;
	void DirSearch(CString DirPath);
	long length;
	int maxIndex;
	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;
	int index;
	int End;

	CMFCApplication4Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION4_DIALOG };

	CString	m_Show;
	CString	m_Showlist;
	CString	m_Timer;
	BOOL	m_Repeat;
	BOOL	m_Random;
//#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	void OnRepeat();
	void OnRandom();
	void SliderMove();
// 구현입니다.
	CString path;
	CString name;
	int nCho, nBun;
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPlay();
	afx_msg void OnStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNext();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CBitmapButton PlayButton;
	CSliderCtrl m_Slide;
	afx_msg void OnPause();
	afx_msg void OnPre();
	CListBox m_List;
	CListBox m_List2;
	afx_msg void m_ShowTimer();
	CEdit ShowTimer;
	CSliderCtrl m_Volume;
	afx_msg void OnVolumeSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnAddList();
	afx_msg void OnDeleteList();
	afx_msg void OnAddFolder();
	afx_msg void OnClose();
	afx_msg void OnIsRepeat();
	afx_msg void OnIsRandom();
	CButton _Re;
	CButton _random;
	afx_msg void OnPlayerSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMp3List();
	CBitmapButton StopButton;
	CBitmapButton PreButton;
	CBitmapButton NextButton;
	CBitmapButton ImsiButton;

};
