
// ImageScanDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageScan.h"
#include "ImageScanDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CImageScanDlg �Ի���




CImageScanDlg::CImageScanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageScanDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nxDest = 0;
	m_nyDest = 0;
	m_nxOffset = 0;
	m_nyOffset = 0;
	m_nImgWidth = 0;
	m_nImgHeight = 0;
	m_dScale = 0.0;
	m_bLButtonDown = FALSE;
}

void CImageScanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CImageScanDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_OPENIMAGE, &CImageScanDlg::OnBnClickedButtonOpenimage)
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_CLOSEIMAGE, &CImageScanDlg::OnBnClickedButtonCloseimage)
END_MESSAGE_MAP()


// CImageScanDlg ��Ϣ�������

BOOL CImageScanDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CImageScanDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CImageScanDlg::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	
	/*if (IsIconic())
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
		CDialog::OnPaint();
	}*/

	if (!m_img.IsNull())
	{
		CRect rcClient;
		GetClientRect(&rcClient);
		
		CDC *pDC = GetDC();
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);

		int nxDest = m_nxDest + m_nxOffset;
		int nyDest = m_nyDest + m_nyOffset;
		COLORREF colorRef = GetBkColor(pDC->GetSafeHdc());

		// �����Ӱ
		CRect rcTop = CRect(rcClient.left, rcClient.top, rcClient.right, nyDest);
		CRect rcLeft = CRect(rcClient.left, nyDest, nxDest, m_rcImg.bottom);
		CRect rcRight = CRect(m_rcImg.right, nyDest, rcClient.right, m_rcImg.bottom);
		CRect rcBottom = CRect(rcClient.left, m_rcImg.bottom, rcClient.right, rcClient.bottom);
		pDC->FillSolidRect(rcTop, colorRef);
		pDC->FillSolidRect(rcLeft, colorRef);
		pDC->FillSolidRect(rcRight, colorRef);
		pDC->FillSolidRect(rcBottom, colorRef);

		TRACE("OnPaint@ ClientRect(%d, %d), (%d, %d), Width: %d, Height: %d\n", rcClient.left, rcClient.top, rcClient.right, rcClient.bottom, rcClient.Width(), rcClient.Height());
		TRACE("OnPaint@ m_rcImg: (%d, %d), (%d, %d), Width: %d, Height: %d\n", m_rcImg.left, m_rcImg.top, m_rcImg.right, m_rcImg.bottom, m_rcImg.Width(), m_rcImg.Height());
		TRACE("OnPaint@ topRect: (%d, %d), (%d, %d), Width: %d, Height: %d\n", rcTop.left, rcTop.top, rcTop.right, rcTop.bottom, rcTop.Width(), rcTop.Height());
		TRACE("OnPaint@ leftRect: (%d, %d), (%d, %d), Width: %d, Height: %d\n", rcLeft.left, rcLeft.top, rcLeft.right, rcLeft.bottom, rcLeft.Width(), rcLeft.Height());
		TRACE("OnPaint@ rightRect: (%d, %d), (%d, %d), Width: %d, Height: %d\n", rcRight.left, rcRight.top, rcRight.right, rcRight.bottom, rcRight.Width(), rcRight.Height());
		TRACE("OnPaint@ bottomRect: (%d, %d), (%d, %d), Width: %d, Height: %d\n", rcBottom.left, rcBottom.top, rcBottom.right, rcBottom.bottom, rcBottom.Width(), rcBottom.Height());
		TRACE("OnPaint@ ImageWidth: %d, ImageHeight: %d\n", m_nImgWidth, m_nImgHeight);
		TRACE("OnPaint@ WidthScale: %.4f, HeightScale: %.4f\n", (double)m_rcImg.Width() / m_nImgWidth, (double)m_rcImg.Height() / m_nImgHeight);
		ASSERT(((double)m_rcImg.Width() / m_nImgWidth - (double)m_rcImg.Height() / m_nImgHeight) < 0.01);

		// ��ͼ
		pDC->SetStretchBltMode(COLORONCOLOR);
		m_img.StretchBlt(pDC->GetSafeHdc(), nxDest, nyDest, m_rcImg.Width(), m_rcImg.Height(), 0, 0, m_img.GetWidth(), m_img.GetHeight(), SRCCOPY);
		TRACE("OnPaint@ nxDest: %d, nyDext: %d\n", nxDest, nyDest);
		TRACE("----------------------------------------------\n");

		m_rcImg = CRect(nxDest, nyDest, m_rcImg.Width() + nxDest, m_rcImg.Height() + nyDest);
	}
	else
	{
		CRect rcClient;
		GetClientRect(&rcClient);

		// �����Ӱ
		CDC *pDC = GetDC();
		pDC->FillSolidRect(CRect(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom), GetBkColor(pDC->GetSafeHdc()));

		GetDlgItem(IDC_BUTTON_OPENIMAGE)->Invalidate();
		GetDlgItem(IDC_BUTTON_CLOSEIMAGE)->Invalidate();
	}

	
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CImageScanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CImageScanDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CRect rcClient;
	GetClientRect(&rcClient);

	GetDlgItem(IDC_BUTTON_OPENIMAGE)->MoveWindow(CRect(rcClient.right - 180, rcClient.bottom - 20, rcClient.right - 100, rcClient.bottom));
	GetDlgItem(IDC_BUTTON_CLOSEIMAGE)->MoveWindow(CRect(rcClient.right - 95, rcClient.bottom - 20, rcClient.right - 15, rcClient.bottom));

	Invalidate();

}

void CImageScanDlg::OpenImage(CString strPathName)
{
	if (!m_img.IsNull())
	{
		m_img.Destroy();
	}

	m_img.Load(strPathName.GetBuffer());
	m_nImgWidth = m_img.GetWidth();
	m_nImgHeight = m_img.GetHeight();

	CRect rcClient;
	GetClientRect(&rcClient);

	/*TRACE("OpenImage@ ImageWidth %d, Imageheigh: %d\n", m_img.GetWidth(), m_img.GetHeight());
	HBITMAP hbitmap = m_img.Detach();
	CBitmap bitmap;
	bitmap.Attach(hbitmap);
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);
	TRACE("OpenImage@ bitmapWidth: %d, bitmapHeight: %d\n", bmp.bmWidth, bmp.bmHeight);
	bitmap.Detach();
	m_img.Attach(hbitmap);*/

	int nImgWidth = m_img.GetWidth();
	int nImgHeight = m_img.GetHeight();
	int nClientWidth = rcClient.Width();
	int nClientHeight = rcClient.Height();

	if (nImgWidth <= nClientWidth && nImgHeight <= nClientHeight)
	{
		// ͼƬ��߽�С�ڵ��ڿͻ���
		m_rcImg.left = (rcClient.Width() - nImgWidth) / 2;
		m_rcImg.top = (rcClient.Height() - nImgHeight) / 2;
		m_rcImg.right = m_rcImg.left + nImgWidth;
		m_rcImg.bottom = m_rcImg.top + nImgHeight;
	}
	else if (nImgWidth <= nClientWidth && nImgHeight > nClientHeight)
	{
		// ͼƬ��С�ڵ��ڿͻ������ߴ��ڿͻ���
		double dScale = (double)nImgHeight / nClientHeight;
		m_rcImg.left = (rcClient.Width() - nImgWidth / dScale) / 2;
		m_rcImg.top = (rcClient.Height() - nImgHeight / dScale) / 2;
		m_rcImg.right = m_rcImg.left + nImgWidth / dScale;
		m_rcImg.bottom = m_rcImg.top + nImgHeight / dScale;
	}
	else if (nImgWidth > nClientWidth && nImgHeight <= nClientHeight)
	{
		// ͼƬ����ڿͻ�������С�ڵ��ڿͻ���
		double dScale = (double)nImgWidth / nClientWidth;
		m_rcImg.left = (rcClient.Width() - nImgWidth / dScale) / 2;
		m_rcImg.top = (rcClient.Height() - nImgHeight / dScale) / 2;
		m_rcImg.right = m_rcImg.left + nImgWidth / dScale;
		m_rcImg.bottom = m_rcImg.top + nImgHeight / dScale;
	}
	else if (nImgWidth > nClientWidth && nImgHeight > nClientHeight)
	{
		// ͼƬ��߽Դ��ڿͻ���
		double dWidthScale = (double)nImgWidth / rcClient.Width();
		double dHeightScale = (double)nImgHeight / rcClient.Height();
		double dMaxScale = dWidthScale > dHeightScale ? dWidthScale : dHeightScale;
		dMaxScale = dMaxScale + 0.1;
		m_rcImg.left = (rcClient.Width() - nImgWidth / dMaxScale) / 2;
		m_rcImg.top = (rcClient.Height() - nImgHeight / dMaxScale) / 2;
		m_rcImg.right = m_rcImg.left + nImgWidth / dMaxScale;
		m_rcImg.bottom = m_rcImg.top + nImgHeight / dMaxScale;
	}

	m_dScale = (double)m_rcImg.Width() / m_nImgWidth;  // ���ű���
	TRACE("OpenImage@ rcImage: (%d, %d), (%d, %d), Width: %d, Height: %d; m_dSacle: %f\n", m_rcImg.left, m_rcImg.top, m_rcImg.right, m_rcImg.bottom, m_rcImg.Width(), m_rcImg.Height(), m_dScale);
	TRACE("-------------------------------\n");

	m_nxDest = m_rcImg.left;
	m_nyDest = m_rcImg.top;

	CDC *pDC = GetDC();
	pDC->SetStretchBltMode(COLORONCOLOR);

	m_img.StretchBlt(pDC->GetSafeHdc(), m_nxDest, m_nyDest, m_rcImg.Width(), m_rcImg.Height(), 0, 0, m_img.GetWidth(), m_img.GetHeight(), SRCCOPY);

	GetDlgItem(IDC_BUTTON_OPENIMAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_CLOSEIMAGE)->ShowWindow(SW_HIDE);
}

void CImageScanDlg::OnBnClickedButtonOpenimage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, "jpg", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "JPEG�ļ�(*.jpg)|*jpg|PNG�ļ�(*.png)|*.png||");
	if (dlg.DoModal() == IDOK)
	{
		m_strPathName = dlg.GetPathName();
		OpenImage(m_strPathName);
	}
}

BOOL CImageScanDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (!m_img.IsNull())
	{
		double dScale = ((double)zDelta / 120) / 100;
		m_dScale += dScale;
		m_rcImg.right = m_rcImg.left + m_nImgWidth * m_dScale;
		m_rcImg.bottom = m_rcImg.top + m_nImgHeight * m_dScale;

		TRACE("OnMouseWheel@ m_rcImage: (%d, %d), (%d, %d); m_dScale: %f, dScale: %f\n", m_rcImg.left, m_rcImg.top, m_rcImg.right, m_rcImg.bottom, m_dScale, dScale);
		TRACE("-----------------------------\n");

		Invalidate();
	}

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void CImageScanDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_bLButtonDown)
	{
		if (!m_img.IsNull())
		{
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));

			m_nxOffset = point.x - m_ptLButtonDown.x;
			m_nyOffset = point.y - m_ptLButtonDown.y;

			//TRACE("OnMouseMove@ m_nxOffset: %d, m_nyOffset: %d\n", m_nxOffset, m_nyOffset);
			Invalidate();
		}
	}
	else
	{
		if (!m_img.IsNull())
		{
			CRect rcClient;
			GetClientRect(&rcClient);

			CRect rcButtonShow;
			rcButtonShow = rcClient;
			rcButtonShow.top = rcButtonShow.bottom - 30;
			if (rcButtonShow.PtInRect(point))
			{
				GetDlgItem(IDC_BUTTON_OPENIMAGE)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON_CLOSEIMAGE)->ShowWindow(SW_SHOW);
			}
			else
			{
				GetDlgItem(IDC_BUTTON_OPENIMAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON_CLOSEIMAGE)->ShowWindow(SW_HIDE);
			}
		}	
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CImageScanDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bLButtonDown = TRUE;
	m_ptLButtonDown = point;
	SetCapture();
	//TRACE("OnLButtonDown@ \n");

	if (!m_img.IsNull())
	{
		GetDlgItem(IDC_BUTTON_OPENIMAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_CLOSEIMAGE)->ShowWindow(SW_HIDE);
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CImageScanDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bLButtonDown = FALSE;
	m_nxDest = m_nxDest + m_nxOffset;
	m_nyDest = m_nyDest + m_nyOffset;
	m_nxOffset = 0;
	m_nyOffset = 0;

	ReleaseCapture();
	//TRACE("OnLButtonUp@ m_nxDest: %d, m_nyDest: %d\n", m_nxDest, m_nyDest);

	CDialog::OnLButtonUp(nFlags, point);
}

BOOL CImageScanDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return TRUE;
	//return CDialog::OnEraseBkgnd(pDC);
}

void CImageScanDlg::OnBnClickedButtonCloseimage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!m_img.IsNull())
	{
		m_img.Destroy();
		m_nxDest = 0;
		m_nyDest = 0;
		m_nxOffset = 0;
		m_nyOffset = 0;
		m_bLButtonDown = FALSE;

		Invalidate();
	}
}
