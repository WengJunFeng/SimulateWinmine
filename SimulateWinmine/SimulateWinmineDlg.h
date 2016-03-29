
// SimulateWinmineDlg.h : ͷ�ļ�
//

#pragma once


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
	afx_msg void OnBnClickedButtonInit();

// �Զ���
private:
	//��Ϸ�Ĵ��ھ��
	HWND m_hGameHwnd;
	//��Ϸ�Ľ���ID
	DWORD m_hGamePID;
	//��Ϸ��ʵ�����
	HANDLE m_hGameHandle;

	int m_nAddCount;
	int m_nAddTime;
	int m_nAddWidth;
	int m_nAddHeight;
	int m_nAddData;
	int m_nCount;
	int m_nTime;
	int m_nWidth;
	int m_nHeight;

private:
	bool ShowHandle(void);
	bool ReadINI(void);
	bool Init(void);
	bool GetGameHwnd(void);
	bool GetGamePID(void);
	bool OpenGameProcess(void);
	int ReadMemoryByte(int nAddr);
	int ReadMemoryInt32(int nAddr);
	bool RunAction(void);
	bool ClickLeftButton(int nX, int nY);
	bool ClickRightButton(int nX, int nY);

};
