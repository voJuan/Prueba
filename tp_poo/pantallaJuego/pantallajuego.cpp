#include "pantallajuego.h"
#include "ui_pantallajuego.h"

pantallajuego::pantallajuego(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pantallajuego),
    personaje(new PersonajeUI(this))
{
    ui->setupUi(this);
    anadirPersonaje(ui->fondopersona);
}

pantallajuego::~pantallajuego()
{
    delete personaje;
    delete ui;
}

void pantallajuego::anadirPersonaje(QWidget *parent)
{
    if(personaje)
    {
        personaje->setParent(parent);
        personaje->setimagenPersonaje(parent);
        personaje->show();
    }
}
void pantallajuego::iniciarAnimacionPersonaje(int deltaX)
{
    if(personaje){
        personaje->iniciarAnimation(deltaX, ui->fondopersona);
    }
    else return;
}

void pantallajuego::cooldownBotones()
{
    deshabilitarBoton=new QTimer(this);
    connect(deshabilitarBoton, &QTimer::timeout, this, &pantallajuego::activarBotones);
    deshabilitarBoton->start(2000); // 2000 ms = 2 segundos
    ui->aceptar->setEnabled(false);
    ui->rechazar->setEnabled(false);
}

void pantallajuego::activarBotones()
{
    ui->aceptar->setEnabled(true);
    ui->rechazar->setEnabled(true);
    deshabilitarBoton->stop();
    deshabilitarBoton->deleteLater(); // Limpiar el timer después de su uso
}

void pantallajuego::on_aceptar_clicked()
{
    cooldownBotones();
    iniciarAnimacionPersonaje(ui->fondopersona->width());
}


void pantallajuego::on_rechazar_clicked()
{
    cooldownBotones();
    iniciarAnimacionPersonaje(-ui->fondopersona->width());
}

