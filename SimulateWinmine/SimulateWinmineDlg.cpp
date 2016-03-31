
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
	DDX_Control(pDX, IDC_COMBO_LEVEL, m_comboLevel);
	DDX_Control(pDX, IDC_COMBO_VERSION, m_comboVersion);
}

BEGIN_MESSAGE_MAP(CSimulateWinmineDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INIT, &CSimulateWinmineDlg::OnBnClickedButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_START, &CSimulateWinmineDlg::OnBnClickedButtonStart)
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
	if (GetGameHwnd())
	{
		// ��ȡ����ID
		GetGamePID();
		// ע����Ϸ����
		if (OpenGameProcess())
		{
			// �ȴ���ʼ
			ShowStatus(2);
			// ���½���
			SetWindowEnable(1);
		}
		else
		{
			// ��ʾȨ�޲���
			ShowStatus(5);
		}
		
	}
	else
	{
		// δ�ҵ�ɨ��
		ShowStatus(1);
		// ���½���
		SetWindowEnable(0);
	}

}

void CSimulateWinmineDlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (GetGameHwnd())
	{
		// ��ȡ
		m_WinmineVersion = m_comboVersion.GetCurSel();
		// ��ȡ��Ϸ����
		m_nCount = ReadMemoryInt32(m_nAddCount[m_WinmineVersion]);
		m_nTime = ReadMemoryInt32(m_nAddTime[m_WinmineVersion]);
		m_nWidth = ReadMemoryInt32(m_nAddWidth[m_WinmineVersion]);
		m_nHeight = ReadMemoryInt32(m_nAddHeight[m_WinmineVersion]);
		// ɨ���С���
		ShowStatus(3);
		if (RunAction())
		{
			// ɨ�׳ɹ�
			ShowStatus(4);
		}
		else
		{
			// ɨ��ʧ��
			ShowStatus(5);
			// ���½���
			SetWindowEnable(0);
		}
	}
	else
	{
		// δ�ҵ�ɨ��
		ShowStatus(1);
		// ���½���
		SetWindowEnable(0);
	}

}

bool CSimulateWinmineDlg::SetWindowEnable(int nEnable)
{
	if (1 == nEnable)
	{
		// �ɿ�ʼɨ��
		GetDlgItem(IDC_BUTTON_INIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_LEVEL)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);

	}
	else if (0 == nEnable)
	{
		// ���ɿ�ʼɨ��
		GetDlgItem(IDC_BUTTON_INIT)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_LEVEL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	}
	else
	{
		;
	}
	return true;
}

bool CSimulateWinmineDlg::ShowStatus(int nStatus)
{
	CString strWnd;

	GetDlgItem(IDC_STATUS)->SetWindowTextW(m_strStatus[nStatus]);
// 	if (3 == nStatus)
// 	{
// 		strWnd.Format(_T("Hwnd:\t%d\nPID:\t%d\nhand:\t%d\nCount:\t%d\nTime:\t%d\nWidth:\t%d\nHeight:\t%d\n"), 
// 			m_hGameHwnd, m_hGamePID, m_hGameHandle, 
// 			m_nCount, m_nTime, m_nWidth, m_nHeight);
// 		AfxMessageBox(strWnd);
// 	}
	return true;
}

bool CSimulateWinmineDlg::ReadINI(void)
{

	return true;
}

bool CSimulateWinmineDlg::Init(void)
{
	// ��ʼ����ʾ��Ϣ
	m_strStatus[0] = "����ǰ״̬���ȴ���ʼ��";
	m_strStatus[1] = "����ǰ״̬��δ�ҵ�ɨ��";
	m_strStatus[2] = "����ǰ״̬���ȴ���ʼ";
	m_strStatus[3] = "����ǰ״̬��ɨ���С���";
	m_strStatus[4] = "����ǰ״̬��ɨ�����";
	m_strStatus[5] = "������Ȩ�޲��㣬��Ǹ";
	m_strStatus[6] = "����ǰ״̬������";
	m_strStatus[7] = "����ǰ״̬������";
	m_strStatus[8] = "����ǰ״̬������";
	m_strStatus[9] = "����ǰ״̬������";
	// ��ʼ����Ա����
	m_hGameHwnd = 0x00;
	m_hGamePID = 0x00;
	m_hGameHandle = 0x00;
	// Ver4.1
	m_nAddCount[0] = 0x01005330;
	m_nAddTime[0] = 0x0100579C;
	m_nAddWidth[0] = 0x01005334;
	m_nAddHeight[0] = 0x01005338;
	m_nAddData[0] = 0x01005360;
	// Ver5.1
	m_nAddCount[1] = 0x01005330;
	m_nAddTime[1] = 0x0100579C;
	m_nAddWidth[1] = 0x01005334;
	m_nAddHeight[1] = 0x01005338;
	m_nAddData[1] = 0x01005360;
	// Ver6.1
	m_nAddCount[2] = 0x01005330;
	m_nAddTime[2] = 0x0100579C;
	m_nAddWidth[2] = 0x01005334;
	m_nAddHeight[2] = 0x01005338;
	m_nAddData[2] = 0x01005360;
	m_nCount = 0x00;
	m_nTime = 0x00;
	m_nWidth = 0x00;
	m_nHeight = 0x00;
	m_WinmineVersion = 1;
	// ��ʼ���ؼ�
	SetWindowEnable(0);
	m_comboVersion.SetCurSel(1);
	m_comboLevel.SetCurSel(2);

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
		return false;
	}
	else
	{
		return true;
	}

}

bool CSimulateWinmineDlg::GetGamePID(void)
{
	//���ݴ��ھ����ȡ������ID
	::GetWindowThreadProcessId(m_hGameHwnd, &m_hGamePID);

	return true;
}

bool CSimulateWinmineDlg::EnableDebugPrivilege(void)
{
	HANDLE hToken;
	bool fOk = false;
	if(OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
	{
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1;
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

		AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);

		fOk = (GetLastError() == ERROR_SUCCESS);
		CloseHandle(hToken);
	}
	return fOk;
}
bool CSimulateWinmineDlg::OpenGameProcess(void)
{
	// ����DebugȨ��
	EnableDebugPrivilege();
	//���ݽ���ID�򿪽���
	m_hGameHandle = ::OpenProcess(PROCESS_ALL_ACCESS, false, m_hGamePID);
	if (0x00 == m_hGameHandle)
	{
		return false;
	}
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
	int nDelay = (3 - m_comboLevel.GetCurSel()) * 6;

	for (int i = 0; i < m_nHeight; i++)
	{
		for (int j = 1; j <= m_nWidth; j++)
		{
			nSign = ReadMemoryByte(m_nAddData[m_WinmineVersion] + i * 32 + j);
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
				//return false;
				
			}
			Sleep(nDelay);
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



