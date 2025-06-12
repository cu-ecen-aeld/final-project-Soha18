#include "mainwindow.h"
#include <QApplication>
#include <csignal>

void handleSigInt(int)
{
    qApp->quit();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    signal(SIGINT, handleSigInt);
        // Set global font size for small display
    
    MainWindow w;
    w.show();
    return a.exec();
}

