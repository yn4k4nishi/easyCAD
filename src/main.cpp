#include <iostream>

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "app.hpp"
#include "frame.hpp"
#include "gl_panel.hpp"

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(GLPanel, wxGLCanvas)
    EVT_MOTION(GLPanel::mouseMoved)
    EVT_LEFT_DOWN(GLPanel::mouseDown)
    EVT_LEFT_UP(GLPanel::mouseReleased)
    EVT_RIGHT_DOWN(GLPanel::rightClick)
    EVT_LEAVE_WINDOW(GLPanel::mouseLeftWindow)
    EVT_SIZE(GLPanel::resized)
    EVT_KEY_DOWN(GLPanel::keyPressed)
    EVT_KEY_UP(GLPanel::keyReleased)
    EVT_MOUSEWHEEL(GLPanel::mouseWheelMoved)
    EVT_PAINT(GLPanel::render)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);
