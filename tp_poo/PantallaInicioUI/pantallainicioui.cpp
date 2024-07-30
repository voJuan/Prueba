#include "pantallainicioui.h"
#include "PantallaInicioUI/ui_pantallainicioui.h"

PantallaInicioUI::PantallaInicioUI(QWidget *parent)
    : QWidget{parent},
      ui(new Ui::PantallaInicioUI)
{
    ui->setupUi(this);
    //Linea 9: Conecta el boton SalirJuegoBoton con el slot de quit() para salir del programa.
    //Linea 10: conecta el boton IniciarJuegoBoton con el slot de iniciarJuegolicked() que cambiara a la pantalla donde se realizara el juego.
    connect(ui->SalirJuegoBoton, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(ui->iniciarJuegoBoton, &QPushButton::clicked, this, &PantallaInicioUI::iniciarJuegoClicked);
}

PantallaInicioUI::~PantallaInicioUI()
{
    delete ui;
}


