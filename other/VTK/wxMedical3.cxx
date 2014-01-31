// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWindows headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include "wxVTKRenderWindowInteractor.h"

#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkVolume.h"
#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkGlyph3D.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkGaussianCubeReader.h"
#include "vtkImageShiftScale.h"
#include "vtkOutlineFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkPiecewiseFunction.h"
#include "vtkColorTransferFunction.h"
#include "vtkVolumeRayCastCompositeFunction.h"
#include "vtkVolumeProperty.h"
#include "vtkVolumeRayCastMapper.h"
#include "vtkImageData.h"
#include "vtkPointData.h"



// the application icon
#ifndef __WXMSW__
    #include "mondrian.xpm"
#endif

class MyApp;
class MyFrame;

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();
};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    ~MyFrame();

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

protected:
    void ConstructVTK();
    void ConfigureVTK();
    void DestroyVTK();

private:
  wxVTKRenderWindowInteractor *m_pVTKWindow;

  // vtk classes
  vtkRenderer       *aRenderer;

private:
    // any class wishing to process wxWindows events must use this macro
    DECLARE_EVENT_TABLE()
};

// IDs for the controls and the menu commands
enum
{
    // menu items
    Minimal_Quit = 1,
    Minimal_About
};

#define MY_FRAME      101
#define MY_VTK_WINDOW 102

// the event tables connect the wxWindows events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
END_EVENT_TABLE()

// Create a new application object: this macro will allow wxWindows to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also declares the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
IMPLEMENT_APP(MyApp)

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // create the main application window
    MyFrame *frame = new MyFrame(_T("wxWindows-VTK App"),
                                 wxPoint(50, 50), wxSize(450, 340));

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(TRUE);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned FALSE here, the
    // application would exit immediately.
    return TRUE;
}

// frame constructor
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
#ifdef __WXMAC__
    // we need this in order to allow the about menu relocation, since ABOUT is
    // not the default id of the about menu
    wxApp::s_macAboutMenuItemId = Minimal_About;
#endif

    // set the frame icon
    SetIcon(wxICON(mondrian));

    // create a menu bar
    wxMenu *menuFile = new wxMenu(_T(""), wxMENU_TEAROFF);

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, _T("&About...\tCtrl-A"), _T("Show about dialog"));

    menuFile->Append(Minimal_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, _T("&File"));
    menuBar->Append(helpMenu, _T("&Help"));

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText(_T("Drag the mouse here! (wxWindows 2.4.0)"));
#endif // wxUSE_STATUSBAR

    m_pVTKWindow = new wxVTKRenderWindowInteractor(this, MY_VTK_WINDOW);
    //turn on mouse grabbing if possible
    m_pVTKWindow->UseCaptureMouseOn();
    ConstructVTK();
    ConfigureVTK();
}

MyFrame::~MyFrame()
{
  if(m_pVTKWindow) m_pVTKWindow->Delete();
  DestroyVTK();
}

void MyFrame::ConstructVTK()
{
  
}

void MyFrame::ConfigureVTK()
{
  // connect the render window and wxVTK window
    vtkRenderWindow *renWin = m_pVTKWindow->GetRenderWindow();

    aRenderer = vtkRenderer::New();
    renWin->AddRenderer(aRenderer);

    //vtkRenderer * ren1 = vtkRenderer::New();

   // vtkRenderWindow * renWin = vtkRenderWindow::New();
        renWin->SetMultiSamples( 0 );
        renWin->AddRenderer( aRenderer );
        renWin->SetSize( 300, 300 );

    //vtkRenderWindowInteractor * iren = vtkRenderWindowInteractor::New();
        //iren->SetRenderWindow( renWin );

    vtkCamera * camera = vtkCamera::New();
      camera->ParallelProjectionOn();
      camera->SetViewUp( 0, 1, 0 );
      camera->SetFocalPoint( 12, 10.5, 15 );
      camera->SetPosition( -70, 15, 34 );
      camera->ComputeViewPlaneNormal();
      aRenderer->SetActiveCamera( camera );
      
    //Create the reader for the data
    //vtkStructuredPointsReader * reader = vtkStructuredPointsReader::New();
    vtkGaussianCubeReader * reader = vtkGaussianCubeReader::New();
        reader->SetFileName( "c:\\m4_TotalDensity.cube" );
        reader->SetHBScale( 1.1 );
        reader->SetBScale( 10 );
        reader->Update();

    double * range = reader->GetGridOutput()->GetPointData()->GetScalars()->GetRange();
    double min = range[0];
    double max = range[1];

    vtkImageShiftScale * readerSS = vtkImageShiftScale::New();
        readerSS->SetInput( reader->GetGridOutput() );
        readerSS->SetShift( -min );
        readerSS->SetScale( 255 / (max - min) );
        readerSS->SetOutputScalarTypeToUnsignedChar();

    vtkOutlineFilter * bounds = vtkOutlineFilter::New();
        bounds->SetInput( reader->GetGridOutput() );

    vtkPolyDataMapper * boundsMapper = vtkPolyDataMapper::New();
        boundsMapper->SetInputConnection( bounds->GetOutputPort() );

    vtkActor * boundsActor = vtkActor::New();
        boundsActor->SetMapper( boundsMapper );
        boundsActor->GetProperty()->SetColor( 0, 0, 0 );
        //boundsActor->GetProperty()->SetOpacity( 0.9 );

    // Create transfer mapping scalar value to opacity
    vtkPiecewiseFunction * opacityTransferFunction = vtkPiecewiseFunction::New();
        opacityTransferFunction->AddPoint(   0, 0.01 );
        opacityTransferFunction->AddPoint( 255, 0.35 );
        opacityTransferFunction->ClampingOn();

    // Create transfer mapping scalar value to color
    vtkColorTransferFunction * colorTransferFunction = vtkColorTransferFunction::New();
        colorTransferFunction->AddHSVPoint(   0.0, 0.66, 1.0, 1.0 );
        colorTransferFunction->AddHSVPoint(  50.0, 0.20, 1.0, 1.0 );
        colorTransferFunction->AddHSVPoint( 100.0, 0.00, 1.0, 1.0 );

    // The property describes how the data will look
    vtkVolumeProperty * volumeProperty = vtkVolumeProperty::New();
        volumeProperty->SetColor( colorTransferFunction );
        volumeProperty->SetScalarOpacity( opacityTransferFunction );
        volumeProperty->SetInterpolationTypeToLinear();

    // The mapper / ray cast function know how to render the data
    vtkVolumeRayCastCompositeFunction * compositeFunction = vtkVolumeRayCastCompositeFunction::New();

    vtkVolumeRayCastMapper * volumeMapper = vtkVolumeRayCastMapper::New();
        volumeMapper->SetVolumeRayCastFunction( compositeFunction );
        volumeMapper->SetInputConnection( readerSS->GetOutputPort() );

    // The volume holds the mapper and the property and
    // can be used to position/orient the volume

    vtkVolume * volume = vtkVolume::New();
        volume->SetMapper( volumeMapper );
        volume->SetProperty( volumeProperty );

    aRenderer->AddVolume( volume );
    aRenderer->AddActor( boundsActor );

    vtkInteractorStyleTrackballCamera *style = 
        vtkInteractorStyleTrackballCamera::New();
    //iren->SetInteractorStyle(style);
    m_pVTKWindow->SetInteractorStyle(style);

    aRenderer->SetBackground( 1, 1, 1 );
    aRenderer->ResetCamera();
    //renWin->Render();


    //iren->Initialize();
    //iren->Start();

    volume->Delete();
    volumeMapper->Delete();
    volumeProperty->Delete();
    colorTransferFunction->Delete();
    opacityTransferFunction->Delete();
    boundsActor->Delete();
    boundsMapper->Delete();
    bounds->Delete();
    readerSS->Delete();
    reader->Delete();
    camera->Delete();
    //iren->Delete();
    //renWin->Delete();
    style->Delete();
    //aRenderer->Delete();
}

void MyFrame::DestroyVTK()
{
  aRenderer->Delete();
}

// event handlers

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // TRUE is to force the frame to close
    Close(TRUE);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxString msg;
    msg.Printf( _T("This is the about dialog of wx-vtk sample.\n"));

    wxMessageBox(msg, _T("About wx-vtk"), wxOK | wxICON_INFORMATION, this);
}
