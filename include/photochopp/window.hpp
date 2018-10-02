#pragma once

#include "photochopp/image.hpp"

#include <string>
#include <utility>

#include <GL/glut.h>
#include <stdlib.h>

class Window {
    std::pair<uint, uint> dimensions;
    std::string name;
    int id;

public:
    /**
     * Displays the image in the window.
     */
    void display();

    /**
     * 
     */
    void resize(std::pair<uint, uint> new_dimensions);

    /**
     * 
     */
    void reposition(std::pair<uint, uint> new_pos);

    Window(Image image, std::string window_name = "Untitled");

private:
    static bool glut_initialized;

    static void reshape(int width, int height);
};