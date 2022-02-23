#include "gui/mainwindow.h"

#include <QApplication>
#include <QQuickWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("Tomas Bata University in Zlin");
    QCoreApplication::setOrganizationDomain("utb.cz");
    QCoreApplication::setApplicationName("ArkArena");

    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);
    MainWindow w;
    w.show();
    return a.exec();
}
