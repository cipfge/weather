#include "main_window.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Weather");
    app.setApplicationVersion("1.0.0");

    MainWindow main_window;
    main_window.show();

    return app.exec();
}
