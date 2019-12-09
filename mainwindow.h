#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkDICOMImageReader.h>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkActor2D.h>
#include <vtkImageMapper.h>
#include <vtkImageViewer2.h>
#include <vtkImageActor.h>
#include <vtkSmartPointer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <QKeyEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>
#include <QDebug>
#include <QWheelEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pushButton_clicked(); //button to load a dicom series in a directory

    void keyPressEvent(QKeyEvent *e); //function to monitor key press events

    void wheelEvent(QWheelEvent *event);

private:
    Ui::MainWindow *ui;

    /*declaring elements for visualizing*/
    vtkSmartPointer<vtkDICOMImageReader> tinputreader;
    vtkSmartPointer<vtkImageMapper> tdicommapper;
    vtkSmartPointer<vtkActor2D> tdicomactor;
    vtkSmartPointer<vtkRenderer> tdicomrenderer;
    vtkSmartPointer<vtkRenderer> backgroundrenderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> tdicomwindow;

    /*variables to store max and min slice numbers*/
    int minSlice;
    int maxSlice;

    int keyslicemove = 0; //variable to hold slice numbers while navigating

    QPoint numDegrees; //variable to hold the angle of wheel rotation
    QPoint numSteps; //variable to hold the steps

};
#endif // MAINWINDOW_H
