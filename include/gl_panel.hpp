#pragma once

#include "wx/wx.h"
#include "wx/glcanvas.h"

#include <GL/glu.h>
#include <GL/gl.h>

class GLPanel : public wxGLCanvas {
    wxGLContext* m_context;
public:
	GLPanel(wxFrame* parent, int* args);
	virtual ~GLPanel();
    
	void resized(wxSizeEvent& evt);
    
	int getWidth();
	int getHeight();
    
	void render(wxPaintEvent& evt);
	void init(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);
    
	// events
	void mouseMoved(wxMouseEvent& event);
	void mouseDown(wxMouseEvent& event);
	void mouseWheelMoved(wxMouseEvent& event);
	void mouseReleased(wxMouseEvent& event);
	void rightClick(wxMouseEvent& event);
	void mouseLeftWindow(wxMouseEvent& event);
	void keyPressed(wxKeyEvent& event);
	void keyReleased(wxKeyEvent& event);
    
	DECLARE_EVENT_TABLE()
};
