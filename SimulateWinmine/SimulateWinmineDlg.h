
// SimulateWinmineDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CSimulateWinmineDlg �Ի���
class CSimulateWinmineDlg : public CDialogEx
{
// ����
public:
	CSimulateWinmineDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SIMULATEWINMINE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CComboBox m_comboLevel;
	CComboBox m_comboVersion;

public:
	afx_msg void OnBnClickedButtonInit();
	afx_msg void OnBnClickedButtonStart();

// �Զ���
private:
	CString m_strStatus[10];
	//��Ϸ�Ĵ��ھ��
	HWND m_hGameHwnd;
	//��Ϸ�Ľ���ID
	DWORD m_hGamePID;
	//��Ϸ��ʵ�����
	HANDLE m_hGameHandle;

	int m_nAddCount[3];
	int m_nAddTime[3];
	int m_nAddWidth[3];
	int m_nAddHeight[3];
	int m_nAddData[3];
	int m_nCount;
	int m_nTime;
	int m_nWidth;
	int m_nHeight;

	int m_WinmineVersion;

private:
	bool SetWindowEnable(int nEnable);
	bool ShowStatus(int nStatus);
	bool ReadINI(void);
	bool Init(void);
	bool GetGameHwnd(void);
	bool GetGamePID(void);
	bool EnableDebugPrivilege(void);
	bool OpenGameProcess(void);
	int ReadMemoryByte(int nAddr);
	int ReadMemoryInt32(int nAddr);
	bool RunAction(void);
	bool ClickLeftButton(int nX, int nY);
	bool ClickRightButton(int nX, int nY);

public:

};
