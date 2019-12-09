#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->initwidget); //setting a black initialization window

    /*initialing visualizing elements*/
    tinputreader = vtkSmartPointer<vtkDICOMImageReader>::New();
    tdicommapper = vtkSmartPointer<vtkImageMapper>::New();
    tdicomactor = vtkSmartPointer<vtkActor2D>::New();
    tdicomrenderer = vtkSmartPointer<vtkRenderer>::New();
    tdicomwindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked() //load and visualize images in a directory
{

    //dialog box for selecting input directory name.
    QString input = QFileDialog::getExistingDirectory(
                this,
                tr("Input Directory"),
                ".dcm files (*.dcm)"
                );
    QMessageBox::information(this, tr ("Folder name"), input);
    std::string inputdicom = input.toStdString(); //QString to std string conversion

    if(inputdicom != ""){ //checking whether a directory was choosen

        ui->stackedWidget->setCurrentWidget(ui->dicomview); //setting openglnativewidget as dicom viewer
        tinputreader->SetDirectoryName(inputdicom.c_str());
        tinputreader->Update(); //reading dicom images
        tdicommapper->SetInputConnection(tinputreader->GetOutputPort());
        tdicomactor->SetMapper(tdicommapper);
        tdicomrenderer->AddActor2D(tdicomactor);
        tdicomwindow->AddRenderer(tdicomrenderer);
        ui->dicomview->SetRenderWindow(tdicomwindow);
        tdicommapper->SetZSlice(0);
        tdicomrenderer->ResetCamera();
        tdicomwindow->Render();
        minSlice = tdicommapper->GetWholeZMin();
        maxSlice =tdicommapper->GetWholeZMax();
        cout << "min slice number is " << minSlice << "\n" << std::flush;
        cout << "max slice number is " << maxSlice << "\n" << std::flush;
        tdicomwindow->Render();
    }
}


void MainWindow::keyPressEvent(QKeyEvent *event){ // navigative through slides based on UP or DOWN key presses
    if(event->key() == Qt::Key_Up && (keyslicemove < maxSlice)){ //setting upperbound
        keyslicemove++;
        tdicommapper->SetZSlice(keyslicemove);
        cout << "current slice number is " << keyslicemove << "\n" << std::flush;
        tdicomwindow->Render();
    }
    if(event->key() == Qt::Key_Down && (keyslicemove > minSlice)){ //setting lower bound
        keyslicemove--;
        tdicommapper->SetZSlice(keyslicemove);
        cout << "current slice number is " << keyslicemove << "\n" << std::flush;
        tdicomwindow->Render();
    }
}
