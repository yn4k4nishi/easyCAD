#pragma once

#include "wx/wxprec.h"
#include "wx/window.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

class MyApp : public wxApp {
public:
    virtual bool OnInit() wxOVERRIDE;
};