#include "pantallajuego.h"
#include "ui_pantallajuego.h"


pantallajuego::pantallajuego(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pantallajuego),
    personaje(new PersonajeUI(this)),

    nivel(new nivel1(this))
{
    ui->setupUi(this);
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
    int puntos=this->nivel->DejarPasarPuntos();
    ActualizarPuntaje(puntos);


}


void pantallajuego::on_rechazar_clicked()
{
    cooldownBotones();
    iniciarAnimacionPersonaje(-ui->fondopersona->width());
    int puntos=this->nivel->NoDejarPasarPuntos();
    ActualizarPuntaje(puntos);

}
void pantallajuego::ActualizarPuntaje(int puntos){
    puntaje=this->puntaje;
    puntaje+=puntos;
    if(puntaje<0){
        puntaje=0;
        mostrarMensajePerdida();
    }
    this->puntaje=puntaje;
    QString numeroComoString = QString::number(puntaje);
    ui->puntaje->setText(numeroComoString);
}
void pantallajuego::mostrarMensajePerdida()
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Juego Terminado");
    msgBox.setText("¡Has perdido!");
    msgBox.setInformativeText("Lo siento, pero has perdido el juego.");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);

    // Mostrar el mensaje de advertencia
    int ret = msgBox.exec();

    // Puedes manejar la respuesta del usuario si es necesario
    switch (ret) {
    case QMessageBox::Ok:
        // Aquí puedes hacer algo si el usuario presiona OK
        break;
    default:
        // Por defecto, no se hace nada
        break;
    }
}

