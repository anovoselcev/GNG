#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
                                         ui(new Ui::MainWindow){
    ui->setupUi(this);
    mw = this;
}

MainWindow* MainWindow::GetInstance() noexcept{
    return mw;
}

MainWindow::~MainWindow()
{
    delete ui;
}

