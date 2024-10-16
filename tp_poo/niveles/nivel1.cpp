#include "nivel1.h" //hola
#include "ui_nivel1.h"
#include <QDrag>
#include <QMimeData>

nivel1::nivel1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::nivel1)
   ,

lectorReg(new LectorArchivos(":/archivos.txt/Recursos/Archivos/reglas.txt")),
lectorNac(new LectorArchivos(":/archivos.txt/Recursos/Archivos/nacionalidad.txt")),
lectorFech(new LectorArchivos(":/archivos.txt/Recursos/Archivos/fecha_nacimiento.txt")),
lectorTipo(new LectorArchivos(":/archivos.txt/Recursos/Archivos/tipo_visita.txt")),
lectorDur(new LectorArchivos(":/archivos.txt/Recursos/Archivos/duracion.txt")),
lectorEst(new LectorArchivos(":/archivos.txt/Recursos/Archivos/estado_civil.txt")),
//lectorRegFake(new LectorArchivos(":/archivos.txt/Recursos/Archivos/reglas.txt")),
lectorNacFake(new LectorArchivos(":/archivos.txt/Recursos/Archivos/nacionalidad_fake.txt")),
lectorFechFake(new LectorArchivos(":/archivos.txt/Recursos/Archivos/fecha_nacimiento_fake.txt")),
lectorTipoFake(new LectorArchivos(":/archivos.txt/Recursos/Archivos/tipo_visita_fake.txt")),
lectorDurFake(new LectorArchivos(":/archivos.txt/Recursos/Archivos/duracion_fake.txt")),
lectorEstFake(new LectorArchivos(":/archivos.txt/Recursos/Archivos/estado_civil_fake.txt"))
//personaje(new personajeAbst())
{
    ui->setupUi(this);
    personaje = nullptr;

    nacionalidades = lectorNac->getArray();
    topeNac = lectorNac->getTopeArray();


    setupDocumentos();
    setupDragAndDrop();
    GenerarPersonajes();

}

nivel1::~nivel1()
{
    delete lectorReg;
    delete lectorNac;
    delete lectorFech;
    delete lectorTipo;
    delete lectorDur;
    delete lectorEst;
    delete ui;

}
//############ funciones para documentos ###############################

// Crear la etiquetas para documentos
void nivel1::setupDocumentos()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    reglas = new QLabel("Cargando...", this);
    nacionalidad = new QLabel("Cargando...", this);
    fecha_de_nacimiento = new QLabel("Cargando...", this);
    tipo_visita = new QLabel("Cargando...", this);
    duracion = new QLabel("Cargando...", this);
    estado_civil = new QLabel("Cargando...", this);
    reglas->setStyleSheet("background-color: lightgray; color: black;");
    nacionalidad->setStyleSheet("background-color: lightgray; color: black;");
    fecha_de_nacimiento->setStyleSheet("background-color: lightgray; color: black;");
    tipo_visita->setStyleSheet("background-color: lightgray; color: black;");
    duracion->setStyleSheet("background-color: lightgray; color: black;");
    estado_civil->setStyleSheet("background-color: lightgray; color: black;");

    layout->addWidget(reglas);
    layout->addWidget(nacionalidad);
    layout->addWidget(fecha_de_nacimiento);
    layout->addWidget(tipo_visita);
    layout->addWidget(duracion);
    layout->addWidget(estado_civil);

    setLayout(layout);

}
// setear texto dependiendo el bool de dejarPasar llamando la funcion obtenerLineaAleatoria(),
//en el caso que sea falso pasarle un puntero a Lector de Archivo que contenga datos incorrectos,
// elegir aleatoriamente que dato va a estar incorrecto
void nivel1::SetDoc(){
    if(this->personaje->getDejarPasar()==true){
        this->reglas->setText("DOCUMENTOS:");
        this->nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
        this->fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));
        this->tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
        this->duracion->setText(obtenerLineaAleatoria(lectorDur));
        this->estado_civil->setText(obtenerLineaAleatoria(lectorEst));
        return;
    }
    else {
        this->reglas->setText("DOCUMENTOS:");
        QRandomGenerator *numRandom = QRandomGenerator::global();
        int num = numRandom->bounded(5) + 1;
        switch (num) {
        case 1:
            this->nacionalidad->setText(obtenerLineaAleatoria(lectorNacFake));
            this->fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));
            this->tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
            this->duracion->setText(obtenerLineaAleatoria(lectorDur));
            this->estado_civil->setText(obtenerLineaAleatoria(lectorEst));
            break;
        case 2:
            this->nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
            this->fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFechFake));
            this->tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
            this->duracion->setText(obtenerLineaAleatoria(lectorDur));
            this->estado_civil->setText(obtenerLineaAleatoria(lectorEst));
            break;
        case 3:
            this->nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
            this->fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));
            this->tipo_visita->setText(obtenerLineaAleatoria(lectorTipoFake));
            this->duracion->setText(obtenerLineaAleatoria(lectorDur));
            this->estado_civil->setText(obtenerLineaAleatoria(lectorEst));
            break;
        case 4:
            this->nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
            this->fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));
            this->tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
            this->duracion->setText(obtenerLineaAleatoria(lectorDurFake));
            this->estado_civil->setText(obtenerLineaAleatoria(lectorEst));
            break;
        case 5:
            this->nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
             this->fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));
             this->tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
             this->duracion->setText(obtenerLineaAleatoria(lectorDur));
             this->estado_civil->setText(obtenerLineaAleatoria(lectorEstFake));
            break;

        default:
            break;
        }
        return;
    }


}

// dado un puntero a LectorArchivos elegir una linea aleatoriamente
QString nivel1::obtenerLineaAleatoria(LectorArchivos *lector) //QString * lista, int TopeLista,
{
    /*
    QRandomGenerator numRandom;
    int indice = numRandom.bounded(TopeLista);
    return lista[indice];
    */
    // ############ EJEMPLO ####################
    int tope = lector->getTopeArray();
    QRandomGenerator *numRandom = QRandomGenerator::global();
    int index = numRandom->bounded(tope);
    QString text = lector->getArray()[index];
    return text;

}
//############ configuracion de las etiquetas #######################
// función que configura la funcionalidad de arrastrar y
//soltar (drag and drop) para las etiquetas de cada documento
void nivel1::setupDragAndDrop()
{
    for (QLabel* label : {reglas, nacionalidad, fecha_de_nacimiento, tipo_visita, duracion, estado_civil}) {
        label->setAcceptDrops(true);
        label->installEventFilter(this);
    }
}
// interceptar eventos del Mouse en las etiquetas de la clase
bool nivel1::eventFilter(QObject *obj, QEvent *event)
{
    QLabel *label = qobject_cast<QLabel *>(obj);
    if (label && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            qDebug() << "MouseButtonPress detected on label:" << label->text();
            QDrag *drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData;
            mimeData->setText(label->text());
            drag->setMimeData(mimeData);
            QPixmap pixmap(label->size());
            label->render(&pixmap);
            drag->setPixmap(pixmap);
            drag->exec();
            return true;
        }
    }

    return QWidget::eventFilter(obj, event);
}
//################################################################
//######################################################################################

//########################## funciones para personajes #################################
// Get para saber el tipo del personaje creado
QString nivel1::getTipoPersonaje()
{
    QString tipo = personaje->getTipo();
    return tipo;
}
// generar personaje de forma aleatoria y llamar a la funcio para setear documentos
void nivel1::GenerarPersonajes(){
    personajeAbst *personaje;
    personaje =  personajeAbst::crearPersonajeAleatorio();
    this->personaje=personaje;
    emit personajeCambiado(personaje->getTipo());
    SetDoc();

}
//#####################################################################################
//###################### logica para sumar puntos #####################################

//Verifica que el bool de dejarPasar sea true para sumar puntos y en el caso que no restar puntos
int nivel1::DejarPasarPuntos(){
     if (this->personaje->getDejarPasar()==true){
        GenerarPersonajes();
        return personaje->getPuntos();
    }
     else {
          GenerarPersonajes();
        int multas=this->multa;
        qDebug() << "cant mult" << multas;
        this->multa=multas +1;
         return this->personaje->getSacarPunto()*-1;

    }
}
//Verifica que el bool de NoDejarPasar sea false para sumar puntos y en el caso que no restar puntos
int nivel1::NoDejarPasarPuntos(){
    if (this->personaje->getDejarPasar()==false){
         GenerarPersonajes();
        return personaje->getPuntos();
    }
    else {
        GenerarPersonajes();
        int multas=this->multa;
        qDebug() << "cant mult" << multas;
        this->multa=multas +1;
        return this->personaje->getSacarPunto()*-1;

    }


}
//#######################################################################################
// ########################### manejo de multas #########################################
// Setear multa en 0
void nivel1::SetMulta(){
    this->multa=0;
}
// Get para saber cuantas multas hay acumuladas
int nivel1::GetMultas(){
    return this->multa;
}
//#######################################################################################





