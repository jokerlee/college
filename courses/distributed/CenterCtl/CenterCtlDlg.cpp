// CenterCtlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CenterCtl.h"
#include "CenterCtlDlg.h"
#include "SlaveSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

CCenterCtlDlg::CSlaveState::CSlaveState()
    : id(0), crntTemp(0), trgtTemp(0), speed(0), mode(0), bTimmer(FALSE)
{

}


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


// CCenterCtlDlg �Ի���


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


// CCenterCtlDlg ��Ϣ�������

BOOL CCenterCtlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

    m_bWorking = FALSE;
	//add three columns
	m_refSlaveList.InsertColumn( 0, L"���",     LVCFMT_LEFT, 100 );
    m_refSlaveList.InsertColumn( 1, L"����ʱ��", LVCFMT_LEFT, 100 );
    m_refSlaveList.InsertColumn( 2, L"����",     LVCFMT_LEFT, 100 );
	m_refSlaveList.InsertColumn( 3, L"Ŀ���¶�", LVCFMT_LEFT, 100 );
    m_refSlaveList.InsertColumn( 4, L"��ǰ�¶�", LVCFMT_LEFT, 100 );


	m_refLogList.InsertColumn( 0, L"ʱ��", LVCFMT_LEFT, 100 );
	m_refLogList.InsertColumn( 1, L"����", LVCFMT_LEFT, 250 );

    this->GetDlgItem( IDC_INITTEMP )->SetWindowText( L"22" );

    ((CComboBox *)GetDlgItem( IDC_MODE ))->AddString( L"����" );
    ((CComboBox *)GetDlgItem( IDC_MODE ))->AddString( L"����" );
    ((CComboBox *)GetDlgItem( IDC_MODE ))->SetCurSel( 0 );
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

    static wchar_t speed[][2] = { L"��", L"��", L"��" };
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCenterCtlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
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
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CCenterCtlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/* �����µĴӿػ����� */
void CCenterCtlDlg::OnSlaveConnect( CSlaveSocket * pSocket )
{  
    CSlaveState info;
    CTime clock;
    m_mapSlaves[pSocket] = info;
    m_mapSlaves[pSocket].enterTime = clock.GetCurrentTime();

    // ���ͳ���֡
    CCenterMessage msg;
    msg.type = CCenterMessage::FRAME_INIT;
    msg.info = m_iInitTemp;
    pSocket->Send( msg );

    // ��ʱ�����¶���Ϣ����
    this->SetTimer( (UINT)(pSocket), FREQ_INFO, NULL );
}

// �����յ�����Ϣ
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

            if ( msg.mode != this->m_mode ) // �ӿػ�����������յ�״̬��ͻ
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
        MessageBox( csInfo, L"����", MB_OK | MB_ICONWARNING );
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
        MessageBox( csInfo, L"����", MB_OK | MB_ICONWARNING );
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

        GetDlgItem( IDC_POWER )->SetWindowText( L"�ػ�" );
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

        GetDlgItem( IDC_POWER )->SetWindowText( L"����" );
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
    
    /* ��ʱ���¿���Ϣ */
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
   
    /* ��ʱ���¶����� */
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
        int iRet = MessageBox( L"�дӿػ����ӵ�����յ���ȷ��Ҫ�˳���", L"����", 
            MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2 );
        
        if ( iRet == IDNO )
            return;
    }
    
    if ( m_bWorking == TRUE )
        ChangeWorkingState();

    CDialog::OnClose();
}