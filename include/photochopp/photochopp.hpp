#pragma once

#include <memory>

#include <gtk/gtk.h>

class Photochopp {
    std::unique_ptr<GtkBuilder> builder;
    std::unique_ptr<GtkWindow> window;

public:

    Photochopp(int& argc, char* argv[]);

private:

    static bool gtk_initialized;
};