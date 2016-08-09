
// ImageScanDlg.h : 头文件
//

#pragma once


// CImageScanDlg 对话框
class CImageScanDlg : public CDialog
{
// 构造
public:
	CImageScanDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_IMAGESCAN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	CString m_strPathName;		// 图片路径名
	CImage  m_img;				// 
	int		m_nImgWidth;		// 图片实际宽度
	int		m_nImgHeight;		// 图片实际高度
	double  m_dScale;			// 缩放比例
	int		m_nxDest;			// 
	int		m_nyDest;			//
	int		m_nxOffset;			// 移动横坐标偏移
	int		m_nyOffset;			// 移动纵坐标偏移
	BOOL	m_bLButtonDown;		// 是否点击 
	CPoint  m_ptLButtonDown;	//
	CRect	m_rcImg;			// 图片显示尺寸
	
};
