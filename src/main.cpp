//
// Created by Marwin Nowak on 18.11.23.
//

#include <QApplication>
#include "../include/mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
