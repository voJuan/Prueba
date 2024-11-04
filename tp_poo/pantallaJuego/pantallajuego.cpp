#include "pantallajuego.h"
#include "ui_pantallajuego.h"
#include "../partida.h"
#include <QFile>
#include <QDataStream>

pantallajuego::pantallajuego(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pantallajuego),
    personaje(new PersonajeUI(this)),
     nivel(nullptr),
    sonidoBoton(new QSoundEffect(this))



{
    nivel->borrarLogs();
    ui->setupUi(this);
    agregarFuentes(":/archivos.txt/Recursos/Archivos/AtariSmall.ttf", ui->reglasTxt);
    configurarSonidoBoton();
    ui->reglas->hide();
    ui->reglasTxt->hide();



    this->timerVisual = new QTimer(this);
    this->numeroNivel=1;
    cambiarNivel(numeroNivel);


    this->puntaje=0;

    puntaje=this->puntaje;
    puntaje=0;

    ui->puntaje->setText(QString("0").arg(puntaje));
    //connect(nivel, &nivel1::personajeCambiado, personaje, &PersonajeUI::actualizarPersonaje);
    anadirPersonaje(ui->fondopersona);

    // Inicializar el temporizador para actualizar el tiempo visual en pantalla


    this->tiempoRestante = nivel->getTiempo();
    timerVisual->start(1000);
    connect(ui->guardar, &QPushButton::clicked, this, &pantallajuego::guardarPartida);
    //connect(timerVisual, &QTimer::timeout, this, &pantallajuego::actualizarTiempoPantalla);

    // Obtén el tiempo del nivel y asignarlo a `tiempoRestante`


    // Comenzar a actualizar el tiempo visual en la pantalla cada segundo
     // Actualización cada segundo
}

pantallajuego::~pantallajuego()
{
    delete personaje;
    delete ui;
}

void pantallajuego::guardarPartida(){
    partida partidaGuardada;
    partidaGuardada.tiempo = this->tiempoRestante;
    partidaGuardada.puntos = this->puntaje;
    partidaGuardada.multas = this->nivel->GetMultas();
    partidaGuardada.nivel=this->numeroNivel;

    QFile archivo("partida_guardada.bin");
    if (archivo.open(QIODevice::WriteOnly)) {
        QDataStream out(&archivo);
        out << partidaGuardada.tiempo << partidaGuardada.puntos << partidaGuardada.multas<<partidaGuardada.nivel;
        archivo.close();
        QMessageBox::information(this, "Guardado", "Partida guardada exitosamente.");
    } else {
        QMessageBox::warning(this, "Error", "No se pudo guardar la partida.");
    }

}

void pantallajuego::cargarDatosPartida(const partida& par) {
    this->tiempoRestante = par.tiempo;
    this->puntaje = par.puntos;
    int multas=par.multas;
    this->nivel->SetMulta(multas);


    // Actualizar los elementos visuales
    ui->tiempoRestante->setText(QString::number(this->tiempoRestante));
    ui->puntaje->setText(QString::number(this->puntaje));

    this->numeroNivel=par.nivel;
    cambiarNivel(this->numeroNivel);
}



//###################### Actualizat tiempo pantalla ###########################
void pantallajuego::actualizarTiempoPantalla() {
    if (this->tiempoRestante > 0) {
        this->tiempoRestante--;  // Reducir solo el tiempo visual en la pantalla
        ui->tiempoRestante->setText( "          "+QString::number(this->tiempoRestante));  // Actualizar el QLabel en la UI
    }

    // Verificar si el tiempo ha llegado a cero
    if (this->tiempoRestante <= 0) {
        timerVisual->stop();  // Detener el temporizador visual
        verificarProgreso();  // Verificar si pasa al siguiente nivel o pierde
    }
}
void pantallajuego::verificarProgreso() {
    // Asegúrate de que el puntaje no sea negativo antes de la verificación
    if (this->puntaje < 0) {
        this->puntaje = 0; // Restablecer a cero si es negativo
    }

    if (this->puntaje >= nivel->getPuntaje()) {
        this->puntaje = 0; // Reiniciar puntaje al pasar de nivel
        this->numeroNivel = nivel->PasarNivel();
        cambiarNivel(this->numeroNivel);  // Pasar al siguiente nivel
    } else {
        mostrarMensajePerdida();
        this->puntaje = 0;        // Mostrar el mensaje de pérdida si no se alcanzó el puntaje
        ActualizarPuntaje(0);
        this->tiempoRestante = nivel->getTiempo();
        actualizarTiempoPantalla();
        timerVisual->start(1000);
        //connect(timerVisual, &QTimer::timeout, this, &pantallajuego::actualizarTiempoPantalla);
    }
}





//###########################################################################
//################### cambiar nivel ##########################################
void pantallajuego::cambiarNivel(int numeroNivel) {
    if (nivel != nullptr) { // Verificar si nivel ya fue inicializado
        timerVisual->stop();
        disconnect(timerVisual, &QTimer::timeout, this, &pantallajuego::actualizarTiempoPantalla);
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
    case 3:
        nivel = new nivel3(this);
        break;
    case 4:
        nivel = new nivel4(this);
        break;
    case 5:
        nivel = new nivel5(this);
        break;
    default:
        qWarning() << "Nivel no válido!";
        return;
        // Puedes agregar más niveles en el futuro
    }

    if (nivel) {
        // Asegura que el widget se expanda
        ui->horizontalLayout->addWidget(nivel);     // Agregar el nuevo nivel al layout
        this->mostrarReglas();
         // Asegurarse de que se ajuste el espacio

        ActualizarPuntaje(0);
        // Conectar señales y slots nuevamente si es necesario
         // Obtener el nuevo tiempo para el nuevo nivel
        this->tiempoRestante = nivel->getTiempo();
        actualizarTiempoPantalla();
         // Reiniciar el temporizador para mostrar el tiempo visual del nuevo nivel
        timerVisual->start(1000);
        connect(nivel, &nivel1::personajeCambiado, personaje, &PersonajeUI::actualizarPersonaje);
        connect(timerVisual, &QTimer::timeout, this, &pantallajuego::actualizarTiempoPantalla);
    }
}
//####################################################################################
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
    nivel->escribirLog("Registro de evento: Pulso Aceptar");
    cooldownBotones();
    qDebug() << "Reproduciendo sonido...";
    sonidoBoton->play();
    if(!sonidoBoton->isPlaying()){
        qDebug() << "NO SE ESTA REPRODUCIENDO";
    }
    iniciarAnimacionPersonaje(ui->fondopersona->width());
    int puntos=this->nivel->DejarPasarPuntos();//verificar si coincide la accion de dejar pasar con el bool de personaje(true)
    if(puntos > 0){
        nivel->escribirLog("Registro Evento: Acertaste");
    }else{
        nivel->escribirLog("Registro Evento: Pifiaste");
        nivel->escribirLog("Errores: ");
        nivel->escribirLogs();
    }
    ActualizarPuntaje(puntos);



}

// Llamar a funciones para actualizar puntaje y generar nuevos personajes ###
void pantallajuego::on_rechazar_clicked()
{
    nivel->escribirLog("Registro de evento: Pulso Rechazar");

    cooldownBotones();
    sonidoBoton->play();
    iniciarAnimacionPersonaje(-ui->fondopersona->width());
    int puntos=this->nivel->NoDejarPasarPuntos();//verificar si coincide la accion de dejar pasar con el bool de personaje(false)
    if(puntos > 0){
        nivel->escribirLog("Registro Evento: Acertaste");
    }else{
        nivel->escribirLog("Registro Evento: Pifiaste");
        nivel->escribirLog("Error: Personaje con documentos autenticos");
    }
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
        this->nivel->SetMulta(0);
        mostrarMensajePerdida();
    }
    /*if(puntaje >=200 && this->numeroNivel==1){
        this->numeroNivel=2;
        cambiarNivel(2);
    }*/

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

void pantallajuego::configurarSonidoBoton(){
    static QUrl url = QString("qrc:/sonidos/Recursos/Sonidos/stamp.wav");
    sonidoBoton->setSource(url);
    sonidoBoton->setVolume(0.5);
}
