#include "photochopp/window.hpp"

bool Window::glut_initialized = false;

/* Window::Window(
    int argc,
    char** argv,
    std::pair<uint, uint> window_position,
    std::pair<uint, uint> window_dimensions,
    std::string window_name)
    : name{ window_name }
    , dimensions{ window_dimensions }
{
    if (!glut_initialized) {
        glutInit(&argc, argv);
        glut_initialized = true;
        glutReshapeFunc(Window::reshape);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glClearColor(0, 0, 0, 0);
    }

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(window_position.first, window_position.second);
    glutInitWindowSize(this->dimensions.first, this->dimensions.second);
    this->id = glutCreateWindow(this->name.c_str());
    glutDisplayFunc(this->display);
} */

Window::Window(Image image, std::string window_name)
    : name{ window_name }
{
}