#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "PantallaInicioUI/pantallainicioui.h"
#include "pantallaJuego/pantallajuego.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      pantallas(new QStackedWidget(this))//stacked para manejar pantallas
{
    ui->setupUi(this);
    //Pantallas del juego
    pantallaInicio = new PantallaInicioUI(this);
    pantallaJugar = new pantallajuego(this);
    AnadirPantallas();
    iraPantallaInicio();
//..
//ir a pantalla de juego
connect(pantallaInicio, &PantallaInicioUI::iniciarJuegoClicked, this, &MainWindow::iraPantallaJuego);
}
//..
MainWindow::~MainWindow()
{
    delete ui;
}
//Añadir pantallas al stack de pantallas
void MainWindow::AnadirPantallas()
{
    pantallas->addWidget(pantallaInicio);
    pantallas->addWidget(pantallaJugar);
    setCentralWidget(pantallas);
}

//Mostrar pantalla de incio del juego
void MainWindow::iraPantallaInicio()
{
    pantallas->setCurrentWidget(pantallaInicio);

}
void MainWindow::iraPantallaJuego()
{
    pantallas->setCurrentWidget(pantallaJugar);
}
