#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "PantallaInicioUI/pantallainicioui.h"
#include "pantallaJuego/pantallajuego.h"
#include "partida.h"
#include <QFile>
#include <QDataStream>
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
connect(pantallaInicio, &PantallaInicioUI::cargarPartidaClicked, this, &MainWindow::cargarPartida);
connect(pantallaInicio, &PantallaInicioUI::iniciarJuegoClicked, this, &MainWindow::stopMusica);

}
//..
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cargarPartida() {
    QFile archivo("partida_guardada.bin");
    if (archivo.open(QIODevice::ReadOnly)) {
        QDataStream in(&archivo);

        partida partidaCargada;
        in >> partidaCargada.tiempo >> partidaCargada.puntos >> partidaCargada.multas >> partidaCargada.nivel;
        archivo.close();

        // Inicializar `pantallajuego` con los datos de la partida cargada
        pantallaJugar->cargarDatosPartida(partidaCargada);

        // Cambiar a la pantalla del juego
        iraPantallaJuego();
        QMessageBox::information(this, "Cargar Partida", "Partida cargada exitosamente.");
    } else {
        QMessageBox::warning(this, "Error", "No se encontró una partida guardada.");
    }
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

void MainWindow::stopMusica()
{
    static QSoundEffect *musica = pantallaInicio->getMusicaFondo();
    musica->stop();
}
