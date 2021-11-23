#include <iostream>

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "app.hpp"
#include "frame.hpp"
#include "gl_plane.hpp"

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(GLPlane, wxGLCanvas)
    EVT_MOTION(GLPlane::mouseMoved)
    EVT_LEFT_DOWN(GLPlane::mouseDown)
    EVT_LEFT_UP(GLPlane::mouseReleased)
    EVT_RIGHT_DOWN(GLPlane::rightClick)
    EVT_LEAVE_WINDOW(GLPlane::mouseLeftWindow)
    EVT_SIZE(GLPlane::resized)
    EVT_KEY_DOWN(GLPlane::keyPressed)
    EVT_KEY_UP(GLPlane::keyReleased)
    EVT_MOUSEWHEEL(GLPlane::mouseWheelMoved)
    EVT_PAINT(GLPlane::render)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);
