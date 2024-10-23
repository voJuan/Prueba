#include "pantallajuego.h"
#include "ui_pantallajuego.h"


pantallajuego::pantallajuego(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pantallajuego),
    personaje(new PersonajeUI(this)),
     nivel(nullptr)


{

    ui->setupUi(this);
    agregarFuentes(":/archivos.txt/Recursos/Archivos/AtariSmall.ttf", ui->reglasTxt);
    ui->reglasTxt->hide();




    int numeroNivel=2;
    cambiarNivel(numeroNivel);


    this->puntaje=0;
    puntaje=this->puntaje;

    puntaje=0;
    ui->puntaje->setText(QString("0").arg(puntaje));
    connect(nivel, &nivel1::personajeCambiado, personaje, &PersonajeUI::actualizarPersonaje);
    anadirPersonaje(ui->fondopersona);
}

pantallajuego::~pantallajuego()
{
    delete personaje;
    delete ui;
}
void pantallajuego::cambiarNivel(int numeroNivel) {
    if (nivel != nullptr) { // Verificar si nivel ya fue inicializado
        ui->horizontalLayout->removeWidget(nivel); // Remover el nivel anterior del layout
        delete nivel; // Destruir el nivel actual
        nivel = nullptr; // Asegurarse de que quede en un estado seguro
    }

    switch (numeroNivel) {
    case 1:
        nivel = new nivel1(this);
        break;
    case 2:
        nivel = new nivel2(this);
        break;
        // Puedes agregar más niveles en el futuro
    }

    if (nivel) {
        // Asegura que el widget se expanda
        ui->horizontalLayout->addWidget(nivel);     // Agregar el nuevo nivel al layout
         this->mostrarReglas();
         // Asegurarse de que se ajuste el espacio

        // Conectar señales y slots nuevamente si es necesario

    }
}

//############### Mostrar personajes y textos en pantalla ############################
//Cambiar imagen segun su tipo
void pantallajuego::anadirPersonaje(QWidget *parent)
{
    if(personaje && nivel)
    {
        QString imagen = nivel->getTipoPersonaje();
        qDebug() << "tipo es:" << imagen;
        personaje->setParent(parent);
        personaje->setimagenPersonaje(parent,imagen);
        personaje->show();
    }
}
// mostrar texto
void pantallajuego::textoVisible(QLabel *texto)
{
    if(textovisible){
        texto->hide();
        textovisible = false;
    }else if (textovisible == false){
        texto->show();
        textovisible = true;
    }
}
// Agregar fuentes para el texto
void pantallajuego::agregarFuentes(QString direccionFuente, QLabel *Texto)
{
    int id = QFontDatabase::addApplicationFont(direccionFuente);
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont fuente(family);
    Texto->setFont(fuente);
}
// llamar a animacion del personaje
void pantallajuego::iniciarAnimacionPersonaje(int deltaX)
{
    if(personaje){
        personaje->iniciarAnimation(deltaX, ui->fondopersona);
    }
    else return;
}
//###############################################################################
//####### metodos botones #######################################################
// desabilitar botones
void pantallajuego::cooldownBotones()
{
    deshabilitarBoton=new QTimer(this);
    connect(deshabilitarBoton, &QTimer::timeout, this, &pantallajuego::activarBotones);
    deshabilitarBoton->start(2000);
    ui->aceptar->setEnabled(false);
    ui->rechazar->setEnabled(false);
}
// activar botones
void pantallajuego::activarBotones()
{
    ui->aceptar->setEnabled(true);
    ui->rechazar->setEnabled(true);
    deshabilitarBoton->stop();
    deshabilitarBoton->deleteLater();
}
//#### Llamar a funciones para actualizar puntaje y generar nuevos personajes ####
void pantallajuego::on_aceptar_clicked()
{
    cooldownBotones();
    iniciarAnimacionPersonaje(ui->fondopersona->width());
    int puntos=this->nivel->DejarPasarPuntos();//verificar si coincide la accion de dejar pasar con el bool de personaje(true)
    ActualizarPuntaje(puntos);


}

// Llamar a funciones para actualizar puntaje y generar nuevos personajes ###
void pantallajuego::on_rechazar_clicked()
{
    cooldownBotones();
    iniciarAnimacionPersonaje(-ui->fondopersona->width());
    int puntos=this->nivel->NoDejarPasarPuntos();//verificar si coincide la accion de dejar pasar con el bool de personaje(false)
    ActualizarPuntaje(puntos);

}
//################################################################################
//############### actualizar puntajes y multas ###################################
//actualizar puntaje en pantalla y llamar a funciones para mostrar multas y mostrar mensaje de juego terminado
void pantallajuego::ActualizarPuntaje(int puntos){
    puntaje=this->puntaje;
    puntaje+=puntos;
    int multas=this->nivel->GetMultas();
    if(multas>this->MaxMulta && multas<4){
    this->MaxMulta=multas;
     mostrarMensajeMulta();
    }
    if((puntaje<0) || (multas==4)) {
        puntaje=0;
        this->nivel->SetMulta();
        mostrarMensajePerdida();
    }
    this->puntaje=puntaje;
    QString numeroComoString = QString::number(puntaje);
    ui->puntaje->setText(numeroComoString);
}
// mostrar mensaje al perder
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
// Motrar mensaje al obtener una multa
void pantallajuego::mostrarMensajeMulta()
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("multa");
    msgBox.setText("sumaste una multa");
    msgBox.setInformativeText("recuerda que con 4 multas pierdes");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);

    // Mostrar el mensaje de advertencia
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Ok:

        break;
    default:
        break;
    }
}
//#############################################################################
//   Mostrar reglas
void pantallajuego::mostrarReglas() {
    if (nivel) {
        QString reglas = nivel->obtenerReglas(); // Obtener las reglas del nivel
        ui->reglasTxt->setText(reglas);          // Mostrar las reglas en el QLabel
        ui->reglasTxt->show();                   // Asegurarse de que el QLabel esté visible
    }
}


//
// Hacer visible texto de reglas
void pantallajuego::on_reglas_clicked()
{
    textoVisible(ui->reglasTxt);
    this->mostrarReglas();
    //QMessageBox::information(this, "REGLAS NIVEL 1:", "Nacionalidad permitida: argentino, brasilero y paraguayo\n Fecha de nacimiento: persona mayores de edad al 01/07/24\n Tipo de visita: trabajo\n Duración de la estancia: mas de 1 semana\n Estado civil: soltero.");
}

