
// MFCApplication4Dlg.cpp: 구현 파일
//


#include "pch.h"
#include "framework.h"
#include "MFCApplication4.h"
#include "MFCApplication4Dlg.h"
#include "afxdialogex.h"
#include <math.h>
#pragma warning(disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
static DWORD dwID;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication4Dlg 대화 상자



CMFCApplication4Dlg::CMFCApplication4Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION4_DIALOG, pParent)
	, m_Timer(_T(""))
{
	m_Show = _T("");
	m_Showlist = _T("");
	m_Timer = _T("");
	m_Repeat = FALSE;
	m_Random = FALSE;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTON1, PlayButton);
	DDX_Control(pDX, IDC_SLIDER1, m_Slide);
	DDX_Control(pDX, IDC_LIST5, m_List);
	DDX_Control(pDX, IDC_LIST4, m_List2);
	DDX_Control(pDX, IDC_EDIT3, ShowTimer);
	DDX_Control(pDX, IDC_SLIDER2, m_Volume);
	DDX_Control(pDX, IDC_CHECK1, _Re);
	DDX_Control(pDX, IDC_CHECK2, _random);
	DDX_Control(pDX, IDC_BUTTON2, StopButton);
	DDX_Control(pDX, IDC_BUTTON7, PreButton);
	DDX_Control(pDX, IDC_BUTTON4, NextButton);
	DDX_Control(pDX, IDC_BUTTON6, ImsiButton);
}

BEGIN_MESSAGE_MAP(CMFCApplication4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication4Dlg::OnPlay)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication4Dlg::OnStop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication4Dlg::OnNext)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication4Dlg::OnPause)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCApplication4Dlg::OnPre)
	ON_EN_CHANGE(IDC_EDIT3, &CMFCApplication4Dlg::m_ShowTimer)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CMFCApplication4Dlg::OnVolumeSlider)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication4Dlg::OnAddList)
	ON_BN_CLICKED(IDC_BUTTON8, &CMFCApplication4Dlg::OnDeleteList)
	ON_BN_CLICKED(IDC_BUTTON9, &CMFCApplication4Dlg::OnAddFolder)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK1, &CMFCApplication4Dlg::OnIsRepeat)
	ON_BN_CLICKED(IDC_CHECK2, &CMFCApplication4Dlg::OnIsRandom)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, &CMFCApplication4Dlg::OnPlayerSlider)
	ON_LBN_DBLCLK(IDC_LIST5, &CMFCApplication4Dlg::OnMp3List)

END_MESSAGE_MAP()


// CMFCApplication4Dlg 메시지 처리기

BOOL CMFCApplication4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.



	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetWindowText("Kangnam MP3 Player");// 타이틀 생성

	//기본 값 초기화
	m_Volume.SetRange(0, 16); 
	m_Volume.SetPos(16);

	m_Timer = "0:0";
	SetDlgItemText(IDC_EDIT3, m_Timer);
	
	m_Repeat = false;
	m_Random = false;


	// 버튼 이미지 수정
	PlayButton.LoadBitmaps(IDB_PLAY, IDB_PLAYPUSH, NULL, NULL); // 첫 번째 인자에는 추가한 비트맵 ID명을 주면 된다.
	PlayButton.SizeToContent(); // 이건 이미지 크기에 버튼 크기를 맞춰주는 작업이다.
	StopButton.LoadBitmaps(IDB_STOP, IDB_STOPPUSH, NULL, NULL);
	StopButton.SizeToContent();
	PreButton.LoadBitmaps(IDB_BACK, IDB_BACKPUSH, NULL, NULL);
	PreButton.SizeToContent();
	NextButton.LoadBitmaps(IDB_PAST, IDB_PASTPUSH, NULL, NULL);
	NextButton.SizeToContent();
	ImsiButton.LoadBitmaps(IDB_IMSISTOP, IDB_IMSISTOPPUSH, NULL, NULL);
	ImsiButton.SizeToContent();

	//UI 둥글게
	CRect rect;
	CRgn rgn;
	GetClientRect(rect);
	rgn.CreateRoundRectRgn(rect.left + 8, rect.top + 8, rect.right+6 , rect.bottom + 30, 15, 15);
	::SetWindowRgn(this->m_hWnd, (HRGN)rgn, TRUE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication4Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
		
		
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;


		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트
		// 비트맵을 통해서 BackGround 그리기.
		CDC MemDC;
		CBitmap bmp;
		CRect rct;
		this->GetClientRect(&rct);

		MemDC.CreateCompatibleDC(&dc);
		bmp.LoadBitmap(IDB_BITMAP4);
		MemDC.SelectObject(&bmp);

		dc.BitBlt(0, 0, rct.Width(), rct.Height(), &MemDC, 0, 0, SRCCOPY);

		CDialogEx::OnPaint();
	}

}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication4Dlg::OnPlay()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	srand(time(NULL));
	MCIERROR mcierr; //장치가 제대로 열렸는지 확인하는 변수

	mcierr = mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)&mciPlay); 
	if (mcierr == 0)
	{
		SetTimer(1, 1000, NULL);
	}
}


void CMFCApplication4Dlg::OnStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&mciPlay);
	m_Slide.SetPos(0);
	End = 0;
	nCho = 1, nBun = 0;   //값들 초기화
	m_Timer = "0:0";
	SetDlgItemText(IDC_EDIT3, m_Timer);
	UpdateData(false);
	KillTimer(1);
}


void CMFCApplication4Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	char szText[100];

	sprintf(szText, "%d:%d", nBun, nCho);
	m_Timer = szText;   //시간 텍스트 창에다 출력
	//UpdateData(false);

	nCho = nCho + 1;
	if (nCho == 60)
	{
		nCho = 0;                  //시간계산
		nBun = nBun + 1;
	}
	m_Slide.SetPos(++End);     //슬라이드 move
	//UpdateData(false);

	if (End >= length)
	{
		if (m_Repeat == 1)
		{
			OnStop();
			OnPlay();
		}
		else
		{
			if (maxIndex == 1)
				OnStop();
			else
				OnNext();
		}
	}
	SetDlgItemText(IDC_EDIT3, m_Timer);
	CDialogEx::OnTimer(nIDEvent);
}


void CMFCApplication4Dlg::OnNext()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_Repeat == false)
	{
		if (maxIndex != 0)
		{
			mciSendCommand(dwID, MCI_CLOSE, 0, NULL);
			m_Slide.SetPos(0);
			End = 0;
			nCho = 1, nBun = 0;   //값들 초기화
			m_Timer = "0:0";
			UpdateData(false);
			index++;
			if (m_Random == 1)
				index = rand() % maxIndex;


			if (index == maxIndex) //인덱스가 끝까지 갔을때 처음으로 돌림
			{
				index = 0;
			}

			CString strFileName;
			CString strFilePath;
			m_List.GetText(index, strFileName);
			m_List2.GetText(index, strFilePath);	 //다음 노래 받아와서


			mciOpen.lpstrElementName = strFilePath;

			m_Show = strFileName;

			mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)&mciOpen); //노래열고
			dwID = mciOpen.wDeviceID;
			SetDlgItemText(IDC_EDIT3, m_Timer);
			m_List.SetCurSel(index); //현재 선택한 리스트박스에 있는 노래 표시 


			OnPlay(); //재생
		}
	}
	else
	{
		OnStop();
		OnPlay();
	}
}


int CMFCApplication4Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	nCho = 1, nBun = 0;
	index = 0;
	maxIndex = 0;
	End = 0;
	mciOpen.lpstrDeviceType = "mpegvideo";
	mciOpen.lpstrElementName = path;

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)&mciOpen);
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}





void CMFCApplication4Dlg::OnRepeat()
{
	if (m_Random == 1)
		m_Random = false;

	// TODO: Add your control notification handler code here
	if (m_Repeat == false)
		m_Repeat = true;
	else
		m_Repeat = false;
	UpdateData(false);

}


void CMFCApplication4Dlg::OnPause()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		//노래 일시정지
	MCI_GENERIC_PARMS mciGeneric;
	mciSendCommand(dwID, MCI_PAUSE, MCI_WAIT, (DWORD)&mciGeneric);

	KillTimer(1); //kill timer
}


void CMFCApplication4Dlg::OnPre()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (maxIndex != 0)
	{

		if (nCho > 3) //3초이상이면 노래 다시재생
		{
			OnStop();
			OnPlay();
		}

		else		//아니면 이전곡으로
		{
			mciSendCommand(dwID, MCI_CLOSE, 0, NULL);
			m_Slide.SetPos(0);
			End = 0;
			nCho = 1, nBun = 0;   //값들 초기화
			m_Timer = "0:0";
			UpdateData(false);


			index--;

			if (m_Random == 1)
				index = rand() % maxIndex;
			if (index < 0)
			{
				index = maxIndex - 1;
			}

			CString strFileName;
			CString strFilePath;
			m_List.GetText(index, strFileName);
			m_List2.GetText(index, strFilePath);

			mciOpen.lpstrElementName = strFilePath;

			m_Show = strFileName;

			mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)&mciOpen);
			dwID = mciOpen.wDeviceID;

			m_List.SetCurSel(index); //현재 선택한 리스트박스에 있는 노래 표시 


			OnPlay();
		}
	}

}






void CMFCApplication4Dlg::m_ShowTimer()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRect rc;
	CWnd* pWnd = GetDlgItem(IDC_EDIT3);
	pWnd->GetWindowRect(rc);
	ScreenToClient(rc);
	InvalidateRect(rc);

}


void CMFCApplication4Dlg::OnVolumeSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int pos;



	pos = m_Volume.GetPos();

	m_Volume.SetPos(pos);


	DWORD m_nVolume;
	m_nVolume = 0xfff * pos;
	m_nVolume = m_nVolume << 16;
	m_nVolume = m_nVolume + 0xfff * pos;

	waveOutSetVolume(NULL, m_nVolume);



	*pResult = 0;
}







void CMFCApplication4Dlg::OnAddList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog fDlg(TRUE, "MP3", "*.MP3",
		OFN_HIDEREADONLY,
		"MP3 파일 (*.MP3)"); // 1: 열기 2: 기본 확장자 3:파일명 4: 읽기전용 파일 출력안함,존재하는 파일을 입력하면 덮어 씌울지 출력,
	//파일을 한번에 여러개 선택 가능 5: 확장자에 의해서 걸러지도록 하기위한 필터.


	fDlg.DoModal();  //다이얼로그 닫음



	path = fDlg.GetPathName(); //경로명 받기
	name = fDlg.GetFileName(); //파일이름 받기*
	if (name != "") //취소했을때 노래 넣지마요
	{
		maxIndex++;
		m_List.AddString(name);
		m_List2.AddString(path);
	}

}


void CMFCApplication4Dlg::OnDeleteList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int CrtIndex = m_List.GetCurSel();	//리스트 박스에서 현재 선택되어있는 리스트 내용을 가져옴
	m_List.DeleteString(CrtIndex); // 이름 지움
	m_List2.DeleteString(CrtIndex); // 경로 지움
	if (maxIndex > 0)
		maxIndex--;// 노래 카운트 -1
	OnStop();// 노래 정지

}


void CMFCApplication4Dlg::OnAddFolder()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ITEMIDLIST *pidlBrowse;

	char pszPathname[1000];





	BROWSEINFO BrInfo;



	BrInfo.hwndOwner = GetSafeHwnd(); // 자신의 핸들을 가져옴

	BrInfo.pidlRoot = NULL; // 여기에 지정되는 폴더가 최상위 폴더로 지정됨

	memset(&BrInfo, 0, sizeof(BrInfo)); //BrInfo 변수 의 내용을 0으로 초기화

	BrInfo.pszDisplayName = pszPathname;

	BrInfo.lpszTitle = "디렉토리를 선택하세요"; // 폴더 선택 창 문구

	BrInfo.ulFlags = BIF_RETURNONLYFSDIRS; // 파일시스템 디렉토리만 선택이 가능하며 아닌경우 ok버튼이 비활성화 됨

	pidlBrowse = ::SHBrowseForFolder(&BrInfo); // 폴더 선택 dialogbox를 보여줌



	if (pidlBrowse != NULL)
	{
		SHGetPathFromIDList(pidlBrowse, pszPathname); // 사용자가 선택한 폴더를 저장함


		DirSearch(pszPathname);
		// pszPathname에 선택한 폴더가 들어있음.

	}


}
void CMFCApplication4Dlg::DirSearch(CString DirPath) {
	CFileFind finder;


	// build a string with wildcards

	CString strWildcard(DirPath); //경로를 가져옴

	strWildcard += _T("\\*.mp3"); // 확장자 추가

	// start working for files

	BOOL bWorking = finder.FindFile(strWildcard); // 주어진 경로의 파일을 찾음. 존재하지 않으면  0리턴 



	while (bWorking) // 파일이 있는 경우

	{
		bWorking = finder.FindNextFile(); // 다음 파일을 찾음
		// skip . and .. files; otherwise, we'd

		// recur infinitely!

		if (finder.IsDots()) // 파일이 . 또는 .. 이면 0이 아닌 수 리턴 (현재 디렉토리,상위 디렉토리)
		{
			continue;
		}
		else                                //파일이라면...

		{
			name = finder.GetFileName(); // 파일의 이름 리턴
			path = finder.GetFilePath(); // 파일의 경로 리턴
			if (name != "") //취소했을때 노래 넣지마요
			{
				maxIndex++; //파일의 개수 추가
				m_List.AddString(name); //리스트1에 이름 추가
				m_List2.AddString(path); //리스트2에 경로 추가


			}


		}
	}

	finder.Close();//파일 찾기 마침.
}
void CMFCApplication4Dlg::OnRandom() {
	if (m_Repeat == 1)
		m_Repeat = false;
	if (m_Random == 0)
		m_Random = true;
	else
		m_Random = false;
	UpdateData(false);
}


void CMFCApplication4Dlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	mciSendCommand(dwID, MCI_CLOSE, 0, NULL);
	DestroyWindow();
	CDialogEx::OnClose();
}


void CMFCApplication4Dlg::OnIsRepeat()
{
	m_Repeat = _Re.GetCheck();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_Random == 1)
		m_Random = false;

	// TODO: Add your control notification handler code here
	if (m_Repeat == 1)
		m_Repeat = true;
	else
		m_Repeat = false;
	UpdateData(false);
}


void CMFCApplication4Dlg::OnIsRandom()
{
	m_Random = _random.GetCheck();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_Repeat == 1)
		m_Repeat = false;
	if (m_Random == 1)
		m_Random = true;
	else
		m_Random = false;
	UpdateData(false);
}


void CMFCApplication4Dlg::OnPlayerSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		int pos;
	MCI_PLAY_PARMS mciPlay;


	pos = m_Slide.GetPos();

	m_Slide.SetPos(pos);
	nBun = pos / 60;
	nCho = pos % 60;

	End = pos;

	mciPlay.dwFrom = pos * 1000;

	mciSendCommand(dwID, MCI_PLAY, MCI_FROM, (DWORD)(LPVOID)&mciPlay);
	SliderMove();
	UpdateData(false);

	*pResult = 0;
}
void CMFCApplication4Dlg::SliderMove() {
	char szText[100];

	sprintf(szText, "%d:%d", nBun, nCho);
	m_Timer = szText;   //시간 텍스트 창에다 출력
	//UpdateData(false);

	nCho = nCho + 1;
	if (nCho == 60)
	{
		nCho = 1;                  //시간계산
		nBun = nBun + 1;
	}
/*	m_Slide.SetPos(++End); */    //슬라이드 move
	//UpdateData(false);

	if (End >= length)
	{
		if (m_Repeat == 1)
		{
			OnStop();
			OnPlay();
		}
		else
		{
			if (maxIndex == 1)
				OnStop();
			else
				OnNext();
		}
	}
	SetDlgItemText(IDC_EDIT3, m_Timer);
}



void CMFCApplication4Dlg::OnMp3List()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnStop();
	mciSendCommand(dwID, MCI_CLOSE, 0, NULL);
	m_Slide.SetPos(0);
	End = 0;
	nCho = 1, nBun = 0;   //값들 초기화
	m_Timer = "0:0";
	UpdateData(false);

	index = m_List.GetCurSel();	/*GetCurSel()은 list box의 기본 함수로 현재 선택된 아이템의
	인덱스를 가져오는 함수*/
	CString strFilePath;
	CString strFileName;



	m_List.GetText(index, strFileName);
	m_List2.GetText(index, strFilePath);

	mciOpen.lpstrElementName = strFilePath;
	m_Show = strFileName;
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)&mciOpen);

	dwID = mciOpen.wDeviceID;
	MCI_STATUS_PARMS mciStatusParms;
	mciStatusParms.dwItem = MCI_FORMAT_HMS;
	//MCI_STATUS_ITEM를 사용하여 총시간정보 출력
	mciSendCommand(dwID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms);
	length = mciStatusParms.dwReturn;//총시간 저장(단위:밀리세컨)

	length /= 1000;


	m_Slide.SetRange(1, length);   //노래 길이를 슬라이더 길이에 삽입
	OnPlay();
}




