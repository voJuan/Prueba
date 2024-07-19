#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "PantallaInicioUI/pantallainicioui.h"
#include "pantallaJuego/pantallajuego.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      pantallas(new QStackedWidget(this))
{
    ui->setupUi(this);
    pantallaInicio = new PantallaInicioUI(this);
    pantallaJugar = new pantallajuego(this);
    AnadirPantallas();
    iraPantallaInicio();

//ir a pantalla de juego
connect(pantallaInicio, &PantallaInicioUI::iniciarJuegoClicked, this, &MainWindow::iraPantallaJuego);
}
//..
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AnadirPantallas()
{
    pantallas->addWidget(pantallaInicio);
    pantallas->addWidget(pantallaJugar);
    setCentralWidget(pantallas);
}


void MainWindow::iraPantallaInicio()
{
    pantallas->setCurrentWidget(pantallaInicio);

}
void MainWindow::iraPantallaJuego()
{
    pantallas->setCurrentWidget(pantallaJugar);
}
