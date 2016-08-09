
// ImageScanDlg.h : ͷ�ļ�
//

#pragma once


// CImageScanDlg �Ի���
class CImageScanDlg : public CDialog
{
// ����
public:
	CImageScanDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IMAGESCAN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnBnClickedButtonOpenimage();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButtonCloseimage();

	void OpenImage(CString strPathName);

private:
	CString m_strPathName;		// ͼƬ·����
	CImage  m_img;				// 
	int		m_nImgWidth;		// ͼƬʵ�ʿ��
	int		m_nImgHeight;		// ͼƬʵ�ʸ߶�
	double  m_dScale;			// ���ű���
	int		m_nxDest;			// 
	int		m_nyDest;			//
	int		m_nxOffset;			// �ƶ�������ƫ��
	int		m_nyOffset;			// �ƶ�������ƫ��
	BOOL	m_bLButtonDown;		// �Ƿ��� 
	CPoint  m_ptLButtonDown;	//
	CRect	m_rcImg;			// ͼƬ��ʾ�ߴ�
	
};
