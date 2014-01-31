// SlaveCtlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SlaveCtl.h"
#include "SlaveCtlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CSlaveCtlDlg 对话框

CSlaveCtlDlg::CSlaveState::CSlaveState()
    : id(0), mode(0), speed(0), crntTemp(0), trgtTemp(0), bTimmer(FALSE)
{

}



CSlaveCtlDlg::CSlaveCtlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSlaveCtlDlg::IDD, pParent), m_pSocket( NULL )
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSlaveCtlDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LOGLIST, m_refLogList);
}

BEGIN_MESSAGE_MAP(CSlaveCtlDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_TIMER()
	//}}AFX_MSG_MAP
    ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_POWER, &CSlaveCtlDlg::ChangeWorkingState)
	ON_BN_CLICKED(IDC_RISE, &CSlaveCtlDlg::OnBnClickedUp)
	ON_BN_CLICKED(IDC_FALL, &CSlaveCtlDlg::OnBnClickedDown)
    ON_BN_CLICKED(IDC_SPEED_ONE, &CSlaveCtlDlg::OnBnClickedSpeedOne)
    ON_BN_CLICKED(IDC_SPEED_TWO, &CSlaveCtlDlg::OnBnClickedSpeedTwo)
    ON_BN_CLICKED(IDC_SPEED_THREE, &CSlaveCtlDlg::OnBnClickedSpeedThree)
END_MESSAGE_MAP()


// CSlaveCtlDlg 消息处理程序

BOOL CSlaveCtlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
    
    // 设置字体
    m_fontBig.CreatePointFont( 160, L"宋体", NULL );
    GetDlgItem( IDC_MODE )->SetFont( &m_fontBig );
    GetDlgItem( IDC_MODE_LBL )->SetFont( &m_fontBig );

    m_refLogList.InsertColumn( 0, L"时间", LVCFMT_LEFT, 100 );
    m_refLogList.InsertColumn( 1, L"操作", LVCFMT_LEFT, 250 );

    DWORD dwIP = ntohl( inet_addr( "127.0.0.1" ) );
    ((CIPAddressCtrl *)GetDlgItem(IDC_IP))->SetAddress(dwIP);
    ((CButton *)GetDlgItem( IDC_SPEED_THREE ))->SetCheck( TRUE );

    m_bWorking = FALSE;
    this->m_state.id = 2;
    m_iInitTemp = 200;
    this->m_state.crntTemp = m_iInitTemp;
    this->m_state.trgtTemp = 200;
    this->m_state.speed = 2;
    this->m_laststate = this->m_state;
    SetTimer( 0xffffffff, FREQ_CHANGE, NULL );

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSlaveCtlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSlaveCtlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

        SendMessage( WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0 );

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CSlaveCtlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSlaveCtlDlg::OnUserRequest( int temp, int speed )
{
    this->m_laststate = this->m_state;

    this->m_state.trgtTemp += temp;
    this->m_state.speed = speed;

    if ( this->m_state.mode == CSlaveMessage::MODE_HEAT && this->m_iInitTemp > this->m_state.trgtTemp
        || this->m_state.mode == CSlaveMessage::MODE_REFRIGE && this->m_iInitTemp < this->m_state.trgtTemp )
    {
        /* 请求与状态矛盾 */
        this->m_state = this->m_laststate;
    }
    else
    {
        CheckState( MODE_FIRST );
    }
    
    UpdateUI( );
}

void CSlaveCtlDlg::CheckState( mode_t mode )
{
    CSlaveMessage msg;

    msg.id = this->m_state.id;
    msg.speed = this->m_state.speed;
    msg.crntTemp = (int)this->m_state.crntTemp;
    msg.trgtTemp = this->m_state.trgtTemp;
    
    int sign = this->m_state.mode == CCenterMessage::MODE_HEAT ? 1 : -1;

    if ( abs( (int)this->m_state.crntTemp - this->m_state.trgtTemp ) >= 1 * 10 )
    {
        if ( mode == MODE_WORKING )
            return;
        
        if ( mode == MODE_STABLE && this->m_state.bTimmer == TRUE )
            this->KillTimer( this->m_state.id );
        
        m_laststate = m_state;
        msg.type = CSlaveMessage::FRAME_REQUEST; 
        msg.mode = ( this->m_state.crntTemp > this->m_state.trgtTemp )
                        ? ( CCenterMessage::MODE_REFRIGE ) : ( CCenterMessage::MODE_HEAT );
    }
    else if ( sign == 1 && this->m_state.crntTemp >= this->m_state.trgtTemp
                || sign == -1 && this->m_state.crntTemp <= this->m_state.trgtTemp )
    {
        if ( mode == MODE_STABLE )
            return;
        
        msg.type = CSlaveMessage::FRAME_ACK;
        this->SetTimer( this->m_state.id, FREQ_CHANGE, NULL );
        this->m_state.bTimmer = TRUE;
        this->GetDlgItem( IDC_MODE )->SetWindowText( L"待机中" );
    }
    else
        return;

    if ( m_pSocket != NULL )
        this->m_pSocket->Send( msg );
}

void CSlaveCtlDlg::ProcessMessage( const CCenterMessage & msg )
{
    CSlaveMessage reply;
    reply.id = this->m_state.id;
    
    switch ( msg.type )
    {
    case CCenterMessage::FRAME_INIT:
        m_state.trgtTemp = msg.info;
        CheckState( MODE_FIRST );
        break;

    case CCenterMessage::FRAME_INFO:
        if ( msg.mode == CCenterMessage::MODE_HEAT || msg.mode == CCenterMessage::MODE_REFRIGE )
        {
            this->m_laststate = this->m_state;
            this->m_state.mode = msg.mode;
            int sign = msg.mode == CCenterMessage::MODE_HEAT ? 1 : -1;
            this->m_state.crntTemp += sign * msg.info;
            GetDlgItem( IDC_MODE )->SetWindowText( 
                msg.mode == CCenterMessage::MODE_HEAT ? L"制热中" : L"制冷中" );
            CheckState( MODE_WORKING );
        }
        else if ( msg.mode == CCenterMessage::MODE_NACK )
        {
            this->m_state = this->m_laststate;
            this->m_state.trgtTemp = (int)this->m_state.crntTemp;
            CheckState( MODE_WORKING );
        }
        break;

    case CCenterMessage::FRAME_REQUEST:
        reply.type = CSlaveMessage::FRAME_REQUEST;
        reply.mode = CSlaveMessage::MODE_INFO;
        reply.speed = this->m_state.speed;
        reply.trgtTemp = this->m_state.trgtTemp;
        reply.crntTemp = (int)this->m_state.crntTemp;
        reply.optional = 0;

        m_pSocket->Send( reply );
        
        break;

    default:
        break;
    }
    
    UpdateUI( );
}



void CSlaveCtlDlg::OnDestroy( )
{
    if ( m_pSocket != NULL )
        m_pSocket->Destroy( );

    CDialog::OnDestroy( );
}

void CSlaveCtlDlg::AddLog( CString log )
{
    LVITEM lvitem;

    ZeroMemory( &lvitem, sizeof(LVITEM) );  
    lvitem.iItem = 0;
    lvitem.mask = LVIF_TEXT | LVIF_PARAM;

    CTime clock = CTime::GetCurrentTime();
    CString str = clock.Format( "[%H:%M:%S]" );

    lvitem.pszText = str.GetBuffer();
    this->m_refLogList.InsertItem( &lvitem );
    m_refLogList.SetItemText( lvitem.iItem, 1, log );

}

void CSlaveCtlDlg::OnTimer( UINT nIDEvent )
{
    /* 平稳后定时改变温度 */
    int change;
    if ( this->m_state.mode == 0 )
        change = rand()%3 - 1;
    else
    {
        change = this->m_state.mode == CSlaveMessage::MODE_HEAT ? -1 : 1;
        if ( change == -1 && m_state.crntTemp <= m_iInitTemp
            || change == 1 && m_state.crntTemp >= m_iInitTemp )
        {
            this->m_state.mode = 0;
        }
    }
    
    this->m_state.crntTemp += change;
    CheckState( MODE_STABLE );
    UpdateUI( );
}

void CSlaveCtlDlg::OnDisconnected( CSlaveSocket * pSocket )
{
    ChangeWorkingState();
    AfxMessageBox( L"服务器关闭连接" );
}

void CSlaveCtlDlg::OnBnClickedUp()
{
	this->OnUserRequest( 10 ,this->m_state.speed );
}

void CSlaveCtlDlg::OnBnClickedDown()
{
	this->OnUserRequest( -10 ,this->m_state.speed );
}


void CSlaveCtlDlg::OnBnClickedSpeedOne()
{
	this->OnUserRequest( 0, 0 );
}


void CSlaveCtlDlg::OnBnClickedSpeedTwo()
{
	this->OnUserRequest( 0, 1 );
}

void CSlaveCtlDlg::OnBnClickedSpeedThree()
{
	this->OnUserRequest( 0, 2 );
}

void CSlaveCtlDlg::UpdateUI()
{
    CString csStr;
    csStr.Format( L"%d.%d", (int)m_state.crntTemp/10, (int)m_state.crntTemp%10 );
    SetDlgItemText( IDC_CUR_TEMP, csStr );

    csStr.Format( L"%d.%d", m_state.trgtTemp/10,  m_state.trgtTemp%10 );
    SetDlgItemText( IDC_DIR_TEMP, csStr );
    UpdateWindow();
}

CString CSlaveCtlDlg::GetIP( )
{
    CString csIP;
    BYTE b[4];

    ((CIPAddressCtrl*)GetDlgItem(IDC_IP))->GetAddress( b[0], b[1], b[2], b[3] );
    csIP.Format( L"%d.%d.%d.%d", b[0], b[1], b[2], b[3] );

    /*if ( ulAddr == INADDR_NONE || ulAddr == INADDR_ANY )
    {  
        CString csInfo;        
        csInfo.LoadString( IDS_ALERT_WRONG_IP );
        MessageBox( csInfo, L"错误", MB_OK | MB_ICONWARNING );
        csIP = L"";
    }*/
    
    return csIP;
}

UINT CSlaveCtlDlg::GetPort( )
{
    UINT uPort;
    CString csStr;

    GetDlgItem( IDC_PORT )->GetWindowText( csStr );
    swscanf_s( csStr, L"%d", &uPort );
    if ( uPort > 99999 || uPort < 1024 )
    {
        CString csInfo;        
        csInfo.LoadString( IDS_ALERT_WRONG_PORT );
        MessageBox( csInfo, L"错误", MB_OK | MB_ICONWARNING );
        uPort = 0;
    }
    
    return uPort;
}

void CSlaveCtlDlg::ChangeWorkingState( )
{
    if ( m_bWorking == FALSE )
    {
        CString csIP;
        UINT uPort;
        if ( ( csIP = GetIP() ) == L"" )
            return;

        if ( ( uPort = GetPort() ) == 0 )
            return;

        this->m_pSocket = new CSlaveSocket( this );
        if ( this->m_pSocket->ConnectServer( csIP, uPort ) == FALSE )
            return;
        
        KillTimer( 0xffffffff );

        GetDlgItem( IDC_DIR_TEMP )->EnableWindow( TRUE );
        GetDlgItem( IDC_RISE )->EnableWindow( TRUE );
        GetDlgItem( IDC_FALL )->EnableWindow( TRUE );
        GetDlgItem( IDC_SPEED_ONE )->EnableWindow( TRUE );
        GetDlgItem( IDC_SPEED_TWO )->EnableWindow( TRUE );
        GetDlgItem( IDC_SPEED_THREE )->EnableWindow( TRUE );

        GetDlgItem( IDC_POWER )->SetWindowText( L"关机" );
        GetDlgItem( IDC_MODE )->SetWindowText( 
            m_state.mode == CCenterMessage::MODE_HEAT ? L"制热中" : L"制冷中" );
        if ( m_state.mode == 0 ) 
            GetDlgItem( IDC_MODE )->SetWindowText( L"待机中" );

        m_bWorking = TRUE;
    }
    else
    {
        SetTimer( 0xffffffff, FREQ_CHANGE, NULL );

        GetDlgItem( IDC_DIR_TEMP )->EnableWindow( FALSE );        
        GetDlgItem( IDC_RISE )->EnableWindow( FALSE );
        GetDlgItem( IDC_FALL )->EnableWindow( FALSE );
        GetDlgItem( IDC_SPEED_ONE )->EnableWindow( FALSE );
        GetDlgItem( IDC_SPEED_TWO )->EnableWindow( FALSE );
        GetDlgItem( IDC_SPEED_THREE )->EnableWindow( FALSE );

        GetDlgItem( IDC_POWER )->SetWindowText( L"开机" );
        GetDlgItem( IDC_MODE )->SetWindowText( L"未开机" );

        m_pSocket->Close();
        delete m_pSocket;
        m_pSocket = NULL;
        m_bWorking = FALSE;
    }
}

