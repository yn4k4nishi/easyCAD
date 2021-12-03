#include "gl_panel.hpp"

// some useful events to use
void GLPanel::mouseMoved(wxMouseEvent& event) {

    static int preX = event.GetX();
    static int preY = event.GetY();

    int deltaX = event.GetX() - preX;
    int deltaY = event.GetY() - preY;

    if(left_down && press_shift){
        // std::cout << deltaX << " " << deltaY << std::endl;
        glMatrixMode(GL_MODELVIEW);
        glTranslatef(deltaX/200.0f, deltaY/200.0f, 0);
        Refresh();
    }
    
    preX = event.GetX();
    preY = event.GetY();
}

void GLPanel::mouseDown(wxMouseEvent& event) {
    left_down = true;
}

void GLPanel::mouseReleased(wxMouseEvent& event) {
    left_down = false;
}

void GLPanel::mouseWheelMoved(wxMouseEvent& event) {

    glMatrixMode(GL_MODELVIEW);

    float mat[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, mat);

    /*
        0  4  8 12 
        1  5  9 13
        2  6 10 14
        3  7 11 15
     */
    
    float camera_x, camera_y, camera_z;
    camera_x = mat[0]*mat[12] + mat[1]*mat[13] + mat[ 2]*mat[14];
    camera_y = mat[4]*mat[12] + mat[5]*mat[13] + mat[ 6]*mat[14];
    camera_z = mat[8]*mat[12] + mat[9]*mat[13] + mat[10]*mat[14];

    float l = sqrt(camera_x*camera_x + camera_y*camera_y + camera_z*camera_z);

    if(event.GetWheelRotation() > 0){
        glTranslatef(
            event.GetWheelDelta()/200.0f * camera_x / l,
            event.GetWheelDelta()/200.0f * camera_y / l,
            event.GetWheelDelta()/200.0f * camera_z / l
        );
    } else {
        glTranslatef(
            - event.GetWheelDelta()/200.0f * camera_x / l,
            - event.GetWheelDelta()/200.0f * camera_y / l,
            - event.GetWheelDelta()/200.0f * camera_z / l
        );
    }

    Refresh();
}

void GLPanel::rightClick(wxMouseEvent& event) {
    glMatrixMode(GL_MODELVIEW);
    glRotatef(5.0f, 0.0f, 1.0f, 0.0f);

    Refresh();
}
void GLPanel::mouseLeftWindow(wxMouseEvent& event) {}
void GLPanel::keyPressed(wxKeyEvent& event) {
    switch (event.GetKeyCode()){
    case WXK_SHIFT:
        press_shift = true;
        break;
    }
}
void GLPanel::keyReleased(wxKeyEvent& event) {
    switch (event.GetKeyCode()){
    case WXK_SHIFT:
        press_shift = false;
        break;
    }
}

// Vertices and faces of a simple cube to demonstrate 3D render
// source: http://www.opengl.org/resources/code/samples/glut_examples/examples/cube.c
GLfloat v[8][3];
GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
    {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
    {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };


GLPanel::GLPanel(wxFrame* parent, int* args) :
    wxGLCanvas(parent, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE){
	m_context = new wxGLContext(this);
    // prepare a simple cube to demonstrate 3D render
    // source: http://www.opengl.org/resources/code/samples/glut_examples/examples/cube.c
    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;    

    // To avoid flashing on MSW
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}
 
GLPanel::~GLPanel(){
	delete m_context;
}

void GLPanel::resized(wxSizeEvent& evt){
    // wxGLCanvas::OnSize(evt);	
    Refresh();
}
 
/** Inits the OpenGL viewport for drawing in 3D. */
void GLPanel::init(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y){

    static bool has_init = false;

    if(has_init) return;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black Background
    glClearDepth(1.0f);	// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST); // Enables Depth Testing
    glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
    glEnable(GL_COLOR_MATERIAL);
	
    glViewport(topleft_x, topleft_y, bottomrigth_x-topleft_x, bottomrigth_y-topleft_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	
    float ratio_w_h = (float)(bottomrigth_x-topleft_x)/(float)(bottomrigth_y-topleft_y);
    gluPerspective(45 /*view angle*/, ratio_w_h, 0.1 /*clip close*/, 200 /*clip far*/);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor4f(0,0,1,1);
    glTranslatef(0,0,-5);
    glRotatef(50.0f, 0.0f, 1.0f, 0.0f);

    has_init = true;
}
 
int GLPanel::getWidth(){
    return GetSize().x;
}
 
int GLPanel::getHeight(){
    return GetSize().y;
}
 
 
void GLPanel::render( wxPaintEvent& evt ){
    if(!IsShown()) return;
    
    wxGLCanvas::SetCurrent(*m_context);
    wxPaintDC(this); // only to be used in paint events. use wxClientDC to paint outside the paint event
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    init(0,0,getWidth(), getHeight());
    
    glColor4f(1, 0, 0, 1);
    for (int i = 0; i < 6; i++){
        glBegin(GL_LINE_STRIP);
        glVertex3fv(&v[faces[i][0]][0]);
        glVertex3fv(&v[faces[i][1]][0]);
        glVertex3fv(&v[faces[i][2]][0]);
        glVertex3fv(&v[faces[i][3]][0]);
        glVertex3fv(&v[faces[i][0]][0]);
        glEnd();
    }
    
    glFlush();
    SwapBuffers();
}