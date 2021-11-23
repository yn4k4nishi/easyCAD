#include "app.hpp"
#include "frame.hpp"

bool MyApp::OnInit(){
    if ( !wxApp::OnInit() ) return false;

    MyFrame *frame = new MyFrame("easyCAD");
    frame->Show(true);

    return true;
}