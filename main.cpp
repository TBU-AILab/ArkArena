#include "gui/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("Tomas Bata University in Zlin");
    QCoreApplication::setOrganizationDomain("utb.cz");
    QCoreApplication::setApplicationName("ArkArena");
    MainWindow w;
    w.show();
    return a.exec();
}
