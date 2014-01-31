// CenterCtlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CenterCtl.h"
#include "CenterCtlDlg.h"
#include "SlaveSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

CCenterCtlDlg::CSlaveState::CSlaveState()
    : id(0), crntTemp(0), trgtTemp(0), speed(0), mode(0), bTimmer(FALSE)
{

}


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


// CCenterCtlDlg 对话框


CCenterCtlDlg::CCenterCtlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCenterCtlDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CCenterCtlDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SLAVELIST, m_refSlaveList);
    DDX_Control(pDX, IDC_LOGLIST, m_refLogList);
}

BEGIN_MESSAGE_MAP(CCenterCtlDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_TIMER()
    ON_WM_CLOSE()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_POWER, &CCenterCtlDlg::ChangeWorkingState)
END_MESSAGE_MAP()


// CCenterCtlDlg 消息处理程序

BOOL CCenterCtlDlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码

    m_bWorking = FALSE;
	//add three columns
	m_refSlaveList.InsertColumn( 0, L"编号",     LVCFMT_LEFT, 100 );
    m_refSlaveList.InsertColumn( 1, L"连接时间", LVCFMT_LEFT, 100 );
    m_refSlaveList.InsertColumn( 2, L"风速",     LVCFMT_LEFT, 100 );
	m_refSlaveList.InsertColumn( 3, L"目标温度", LVCFMT_LEFT, 100 );
    m_refSlaveList.InsertColumn( 4, L"当前温度", LVCFMT_LEFT, 100 );


	m_refLogList.InsertColumn( 0, L"时间", LVCFMT_LEFT, 100 );
	m_refLogList.InsertColumn( 1, L"操作", LVCFMT_LEFT, 250 );

    this->GetDlgItem( IDC_INITTEMP )->SetWindowText( L"22" );

    ((CComboBox *)GetDlgItem( IDC_MODE ))->AddString( L"制冷" );
    ((CComboBox *)GetDlgItem( IDC_MODE ))->AddString( L"制热" );
    ((CComboBox *)GetDlgItem( IDC_MODE ))->SetCurSel( 0 );
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCenterCtlDlg::UpdateUI()
{
    m_refSlaveList.DeleteAllItems( );
    std::map<CSlaveSocket *, CSlaveState>::iterator i;
    for ( i = m_mapSlaves.begin(); i != m_mapSlaves.end(); ++i )
    {
        InsertRow( i->second );
    }
    
    this->UpdateWindow();
}

void CCenterCtlDlg::InsertRow( const CSlaveState & state )
{
    LVITEM row;
    ZeroMemory( &row, sizeof(LVITEM) );
    row.iItem = 0;
    row.mask = LVIF_TEXT | LVIF_PARAM;
    
    CString cell;
    cell.Format( L"%d", state.id );
    row.pszText = cell.GetBuffer();
    this->m_refSlaveList.InsertItem( &row );

    cell = state.enterTime.Format( "[%H:%M:%S]" );
    m_refSlaveList.SetItemText( row.iItem, 1, cell );

    static wchar_t speed[][2] = { L"低", L"中", L"高" };
    m_refSlaveList.SetItemText( row.iItem, 2, speed[state.speed] );  

    cell.Format( L"%d.%d", state.trgtTemp/10, state.trgtTemp%10 );
    m_refSlaveList.SetItemText( row.iItem, 3, cell );

    cell.Format( L"%d.%d", state.crntTemp/10, state.crntTemp%10 );
    m_refSlaveList.SetItemText( row.iItem, 4, cell );
}

void CCenterCtlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCenterCtlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
HCURSOR CCenterCtlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/* 处理新的从控机连接 */
void CCenterCtlDlg::OnSlaveConnect( CSlaveSocket * pSocket )
{  
    CSlaveState info;
    CTime clock;
    m_mapSlaves[pSocket] = info;
    m_mapSlaves[pSocket].enterTime = clock.GetCurrentTime();

    // 发送初温帧
    CCenterMessage msg;
    msg.type = CCenterMessage::FRAME_INIT;
    msg.info = m_iInitTemp;
    pSocket->Send( msg );

    // 定时发送温度信息请求
    this->SetTimer( (UINT)(pSocket), FREQ_INFO, NULL );
}

// 处理收到的消息
void CCenterCtlDlg::ProcessMessage( CSlaveMessage msg, CSlaveSocket * pSocket )
{
    if ( msg.type == CSlaveMessage::FRAME_REQUEST )
    {
        switch ( msg.mode )
        {
        case CSlaveMessage::MODE_HEAT:
        case CSlaveMessage::MODE_REFRIGE:
            this->m_mapSlaves[ pSocket ].id = msg.id;
            this->m_mapSlaves[ pSocket ].crntTemp = msg.crntTemp;

            if ( msg.mode != this->m_mode ) // 从控机请求与中央空调状态冲突
            {
                CCenterMessage reply;
                reply.mode = CCenterMessage::MODE_NACK;
                reply.type = CCenterMessage::FRAME_INFO;
                reply.info = this->m_mapSlaves[ pSocket ].trgtTemp;
                this->m_mapSlaves[ pSocket ].trgtTemp = msg.trgtTemp;
                reply.optional = 0;
                pSocket->Send( reply );
            }
            else
            {
                this->m_mapSlaves[ pSocket ].trgtTemp = msg.trgtTemp;
                this->m_mapSlaves[ pSocket ].speed = msg.speed;
                this->SetTimer( msg.id, FREQ_CTRL, NULL );
                this->m_mapSlaves[ pSocket ].bTimmer = TRUE;
            }
            break;

        case CSlaveMessage::MODE_INFO:
            this->m_mapSlaves[ pSocket ].id = msg.id;
            this->m_mapSlaves[ pSocket ].crntTemp = msg.crntTemp;
            break;

        default:
            break;
        }
    }
    else if ( msg.type == CSlaveMessage::FRAME_ACK )
    {
        if ( this->m_mapSlaves[ pSocket ].bTimmer = TRUE )
            this->KillTimer( msg.id );
    }
}


void CCenterCtlDlg::OnSlaveDisconnect( CSlaveSocket * pSocket )
{
    this->KillTimer( (UINT)pSocket );
    if ( this->m_mapSlaves[pSocket].bTimmer == TRUE )
        this->KillTimer( this->m_mapSlaves[pSocket].id );
    this->m_mapSlaves.erase( pSocket );
    delete pSocket;
}


int CCenterCtlDlg::GetInitTemp( )
{
    CString strtemp;
    int iTemp;
    GetDlgItem( IDC_INITTEMP )->GetWindowText( strtemp );
    swscanf_s( strtemp, L"%d", &iTemp );
    if ( iTemp < 10 || iTemp > 30 )
    {
        CString csInfo;        
        csInfo.LoadString( IDS_ALERT_WRONG_INITTEMP );
        MessageBox( csInfo, L"错误", MB_OK | MB_ICONWARNING );
        return -1;
    }
    return iTemp;
}

UINT CCenterCtlDlg::GetPort( )
{
    UINT uPort;
    CString csPort;

    GetDlgItem( IDC_PORT )->GetWindowText( csPort );
    swscanf_s( csPort, L"%d", &uPort );
    if ( uPort > 99999 || uPort < 1024 )
    {
        CString csInfo;        
        csInfo.LoadString( IDS_ALERT_WRONG_PORT );
        MessageBox( csInfo, L"错误", MB_OK | MB_ICONWARNING );
        return 0;
    }
    return uPort;
}

void CCenterCtlDlg::ChangeWorkingState( )
{
    if ( m_bWorking == FALSE )
    {
        m_mode = CSlaveMessage::MODE_HEAT;
        if ( ((CComboBox *)GetDlgItem( IDC_MODE ))->GetCurSel() == 0 )
            m_mode = CSlaveMessage::MODE_REFRIGE;
        
        int iTemp;
        if ( ( iTemp = GetInitTemp() ) == -1 )
            return;
        m_iInitTemp = iTemp * 10;
        
        UINT uPort;
        if ( ( uPort = GetPort() ) == 0 )
            return;

        m_pSocket = new CServerSocket( this );
        m_pSocket->StartListen( uPort );

        this->SetTimer( 0xffffffff, FREQ_REFRESH, NULL );
        
        GetDlgItem( IDC_MODE )->EnableWindow( FALSE );
        GetDlgItem( IDC_PORT )->EnableWindow( FALSE );
        GetDlgItem( IDC_INITTEMP )->EnableWindow( FALSE );

        GetDlgItem( IDC_POWER )->SetWindowText( L"关机" );
        m_bWorking = TRUE;
    }
    else
    {
        if ( m_pSocket )
        {
            m_pSocket->Close();
            delete m_pSocket;
            m_pSocket = NULL;
        }
        
        std::map<CSlaveSocket *, CSlaveState>::iterator i;
        for ( i = m_mapSlaves.begin(); i != m_mapSlaves.end(); ++i )
        {
            i->first->Close();
            this->KillTimer( (UINT)i->first );
            if ( i->second.bTimmer == TRUE )
            this->KillTimer( i->second.id );
            delete i->first;
        }
        m_mapSlaves.clear();

        GetDlgItem( IDC_MODE )->EnableWindow( TRUE );
        GetDlgItem( IDC_PORT )->EnableWindow( TRUE );
        GetDlgItem( IDC_INITTEMP )->EnableWindow( TRUE );

        GetDlgItem( IDC_POWER )->SetWindowText( L"开机" );
        m_bWorking = FALSE;
    }
}


void CCenterCtlDlg::OnTimer( UINT nIDEvent )
{
    if ( nIDEvent == 0xffffffff )
    {
        UpdateUI( );
        return;
    }
    
    /* 定时发温控信息 */
    CCenterMessage msg;
    std::map<CSlaveSocket *, CSlaveState>::iterator i;
    for ( i = m_mapSlaves.begin(); i != m_mapSlaves.end(); ++i )
    {
        if ( nIDEvent == i->second.id )
        {
            msg.type = CCenterMessage::FRAME_INFO;
            msg.mode = this->m_mode;
            msg.info = GetTemperature( i->second );
            i->first->Send( msg );
            return;
        }
    }
   
    /* 定时发温度请求 */
    CSlaveSocket * pSocket = (CSlaveSocket *)nIDEvent;

    msg.type = CCenterMessage::FRAME_REQUEST;
    msg.mode = this->m_mode;

    pSocket->Send( msg );
}


int CCenterCtlDlg::GetTemperature( CSlaveState state )
{
    int dist = abs( state.crntTemp - state.trgtTemp );

    if ( state.speed == 0 )
        return 1;
    else if ( state.speed == 1 )
        return 2;
    else
        return 5;
}


void CCenterCtlDlg::AddLog( CString log )
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

void CCenterCtlDlg::OnClose()
{
    this->KillTimer( 0xffffffff );

    if ( m_mapSlaves.size() > 0 )
    {
        int iRet = MessageBox( L"有从控机连接到中央空调，确定要退出？", L"警告", 
            MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2 );
        
        if ( iRet == IDNO )
            return;
    }
    
    if ( m_bWorking == TRUE )
        ChangeWorkingState();

    CDialog::OnClose();
}