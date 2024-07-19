#include "pantallainicioui.h"
#include "PantallaInicioUI/ui_pantallainicioui.h"

PantallaInicioUI::PantallaInicioUI(QWidget *parent)
    : QWidget{parent},
      ui(new Ui::PantallaInicioUI)
{
    ui->setupUi(this);
    connect(ui->SalirJuegoBoton, &QPushButton::clicked, qApp, &QApplication::quit);
     connect(ui->iniciarJuegoBoton, &QPushButton::clicked, this, &PantallaInicioUI::iniciarJuegoClicked);
}

PantallaInicioUI::~PantallaInicioUI()
{
    delete ui;
}


