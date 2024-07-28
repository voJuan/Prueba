#include "pantallajuego.h"
#include "ui_pantallajuego.h"

pantallajuego::pantallajuego(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pantallajuego),
    personaje(new PersonajeUI(this)),

    nivel(new nivel1(this))
{
    ui->setupUi(this);
    ui->reglasTxt->hide();
    anadirPersonaje(ui->fondopersona);
    //QVBoxLayout *layout = new QVBoxLayout(this);

    nivel1 *nivel = new nivel1(this);
    this->nivel=nivel;
    this->puntaje=0;
    puntaje=this->puntaje;
    ui->horizontalLayout->addWidget(nivel);
    puntaje=0;
    ui->puntaje->setText(QString("1%").arg(puntaje));
    connect(nivel, &nivel1::personajeCambiado, personaje, &PersonajeUI::actualizarPersonaje);
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
        QString imagen = nivel->getTipoPersonaje();
        qDebug() << "tipo es:" << imagen;
        personaje->setParent(parent);
        personaje->setimagenPersonaje(parent,imagen);
        personaje->show();
    }
}

void pantallajuego::textoVisible(QLabel *texto)
{

    if(textovisible){
        texto->hide();
        textovisible = false;
    }else{
        texto->show();
        textovisible = true;
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
    puntaje=this->puntaje;
    int puntos=this->nivel->DejarPasarPuntos();
    qDebug() << "PUNTAJE BOTON ACEPTAR: " << puntos;
    puntaje+=puntos;
    this->puntaje=puntaje;
    QString numeroComoString = QString::number(puntaje);
    ui->puntaje->setText(numeroComoString);

}


void pantallajuego::on_rechazar_clicked()
{
    cooldownBotones();
    iniciarAnimacionPersonaje(-ui->fondopersona->width());
    puntaje=this->puntaje;
    int puntos=this->nivel->NoDejarPasarPuntos();
    qDebug() << "PUNTAJE BOTON RECHAZAR: " << puntos;
    puntaje+=puntos;
    this->puntaje=puntaje;
    QString numeroComoString = QString::number(puntaje);
    ui->puntaje->setText(numeroComoString);

}


void pantallajuego::on_reglas_clicked()
{
    textoVisible(ui->reglasTxt);
    //QMessageBox::information(this, "REGLAS NIVEL 1:", "Nacionalidad permitida: argentino, brasilero y paraguayo\n Fecha de nacimiento: persona mayores de edad al 01/07/24\n Tipo de visita: trabajo\n Duración de la estancia: mas de 1 semana\n Estado civil: soltero.");
}

