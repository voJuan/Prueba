#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "PantallaInicioUI/pantallainicioui.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      pantallas(new QStackedWidget(this))
{
    ui->setupUi(this);
    pantallaInicio = new PantallaInicioUI(this);
    AnadirPantallas();
    iraPantallaInicio();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AnadirPantallas()
{
    pantallas->addWidget(pantallaInicio);
    setCentralWidget(pantallas);
}

void MainWindow::iraPantallaInicio()
{
  pantallas->setCurrentWidget(pantallaInicio);
}
