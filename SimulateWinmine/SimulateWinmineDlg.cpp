
// SimulateWinmineDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SimulateWinmine.h"
#include "SimulateWinmineDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSimulateWinmineDlg �Ի���




CSimulateWinmineDlg::CSimulateWinmineDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSimulateWinmineDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSimulateWinmineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSimulateWinmineDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INIT, &CSimulateWinmineDlg::OnBnClickedButtonInit)
END_MESSAGE_MAP()


// CSimulateWinmineDlg ��Ϣ�������

BOOL CSimulateWinmineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	Init();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSimulateWinmineDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSimulateWinmineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSimulateWinmineDlg::OnBnClickedButtonInit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ͨ������������������ȡ��Ϸ�Ĵ��ھ��
	GetGameHwnd();
	// ��ȡ����ID
	GetGamePID();
	// ע����Ϸ����
	OpenGameProcess();
	// ��ȡ��Ϸ����
	m_nCount = ReadMemoryInt32(m_nAddCount);
	m_nTime = ReadMemoryInt32(m_nAddTime);
	m_nWidth = ReadMemoryInt32(m_nAddWidth);
	m_nHeight = ReadMemoryInt32(m_nAddHeight);

	// ��ʾ��ǰ״̬
	ShowHandle();

	RunAction();
}

bool CSimulateWinmineDlg::ShowHandle(void)
{
	CString strWnd;

	strWnd.Format(_T("Hwnd:\t%d\nPID:\t%d\nhand:\t%d\nCount:\t%d\nTime:\t%d\nWidth:\t%d\nHeight:\t%d\n"), 
		m_hGameHwnd, m_hGamePID, m_hGameHandle, 
		m_nCount, m_nTime, m_nWidth, m_nHeight);
	GetDlgItem(IDC_STATUS)->SetWindowTextW(strWnd);
	return true;
}

bool CSimulateWinmineDlg::ReadINI(void)
{

	return true;
}

bool CSimulateWinmineDlg::Init(void)
{
	// ��ʼ����Ա����
	m_hGameHwnd = 0x00;
	m_hGamePID = 0x00;
	m_hGameHandle = 0x00;

	m_nAddCount = 0x01005330;
	m_nAddTime = 0x0100579C;
	m_nAddWidth = 0x01005334;
	m_nAddHeight = 0x01005338;
	m_nAddData = 0x01005360;

	m_nCount = 0x00;
	m_nTime = 0x00;
	m_nWidth = 0x00;
	m_nHeight = 0x00;
	// ��ȡ�����ļ�
	ReadINI();
	
	return true;
}

bool CSimulateWinmineDlg::GetGameHwnd(void)
{
	// ����ָ�������ľ��
	m_hGameHwnd = ::FindWindowW(_T("ɨ��"), _T("ɨ��"));
	if (0x00 == m_hGameHwnd)
	{
		AfxMessageBox(_T("���ɨ��Ӧ�ó���"));
	}

	return true;
}

bool CSimulateWinmineDlg::GetGamePID(void)
{
	//���ݴ��ھ����ȡ������ID
	::GetWindowThreadProcessId(m_hGameHwnd, &m_hGamePID);

	return true;
}

bool CSimulateWinmineDlg::OpenGameProcess(void)
{
	//���ݽ���ID�򿪽���
	m_hGameHandle = ::OpenProcess(PROCESS_ALL_ACCESS, false, m_hGamePID);

	return true;
}

int CSimulateWinmineDlg::ReadMemoryByte(int nAddr)
{
	DWORD bytes = 0x00;
	int nBuffer = 0x00;
	//���ݷ��صľ����ȡ�ڴ�ָ���ڴ��ַ������
	::ReadProcessMemory(m_hGameHandle, (LPCVOID)nAddr, &nBuffer, 1, &bytes);
	return nBuffer;
}

int CSimulateWinmineDlg::ReadMemoryInt32(int nAddr)
{
	DWORD bytes = 0x00;
	int nBuffer = 0x00;
	//���ݷ��صľ����ȡ�ڴ�ָ���ڴ��ַ������
	::ReadProcessMemory(m_hGameHandle, (LPCVOID)nAddr, &nBuffer, sizeof(int), &bytes);
	return nBuffer;
}

bool CSimulateWinmineDlg::RunAction(void)
{
	CString strSign;
	int nSign;

	for (int i = 0; i < m_nHeight; i++)
	{
		for (int j = 1; j <= m_nWidth; j++)
		{
			nSign = ReadMemoryByte(m_nAddData + i * 32 + j);
			// 143Ϊ�ף�15Ϊ����
			if (15 == nSign)
			{
				ClickLeftButton(j, i);
			}
			else if(143 == nSign)
			{
				ClickRightButton(j, i);
			} 
			else
			{
				;
			}
			//Sleep(10);
		}
	}

	return true;
}

bool CSimulateWinmineDlg::ClickLeftButton(int nX, int nY)
{
	::PostMessageW(m_hGameHwnd, WM_LBUTTONDOWN, 0, (4 + 16 * nX) + ((64 + 16 * nY) << 16));
	//Sleep(1);
	::PostMessageW(m_hGameHwnd, WM_LBUTTONUP, 0, (4 + 16 * nX) + ((64 + 16 * nY) << 16));

	return true;
}

bool CSimulateWinmineDlg::ClickRightButton(int nX, int nY)
{
	::PostMessageW(m_hGameHwnd, WM_RBUTTONDOWN, 0, (4 + 16 * nX) + ((64 + 16 * nY) << 16));
	//Sleep(1);
	::PostMessageW(m_hGameHwnd, WM_RBUTTONUP, 0, (4 + 16 * nX) + ((64 + 16 * nY) << 16));

	return true;
}

