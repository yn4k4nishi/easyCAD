#include "app.hpp"
#include "frame.hpp"
#include "wx/sizer.h"

bool MyApp::OnInit(){
    if ( !wxApp::OnInit() ) return false;

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    MyFrame *frame = new MyFrame("easyCAD");

    int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};

    GLPlane *glPlane = new GLPlane((wxFrame*)frame, args);
    sizer->Add(glPlane, 1, wxEXPAND);

    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);

    frame->Show(true);
    return true;
}