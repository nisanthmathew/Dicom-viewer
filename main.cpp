#include <list>
#include <fstream>
#include "mainwindow.h"
#include <QApplication>
#include <QVTKOpenGLNativeWidget.h>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    /*using compatibilit mode mode to prevent an issue. See this link for more details.
     https://discourse.vtk.org/t/problem-in-vtk-8-2-with-defaultformat-and-qvtkopenglwidget-on-windows-10-intel/998/26*/
    //QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
    auto format = QVTKOpenGLNativeWidget::defaultFormat();
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    QSurfaceFormat::setDefaultFormat(format);
    MainWindow w; //initiating dicom viewer window
    w.show();
    return a.exec();
}
