#include "nivel1.h"
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
lectorEst(new LectorArchivos(":/archivos.txt/Recursos/Archivos/estado_civil.txt"))
//personaje(new personajeAbst())
{
    ui->setupUi(this);
    // lector(new LectorArchivos(":/archivos.txt/Recursos/Imagenes/imagenes-personajes.txt"))

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


void nivel1::setupDocumentos()
{
    if (reglas) {
        if(this->personaje->getDejarPasar()==true){
            reglas->setText("dejar pasar");
            nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
            fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));
            tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
            duracion->setText(obtenerLineaAleatoria(lectorDur));
            estado_civil->setText(obtenerLineaAleatoria(lectorEst));
            // mostrar_documentos();
            // setupDragAndDrop();
            return;
        }
        else {
            reglas->setText("no dejar pasar");
            QRandomGenerator *numRandom = QRandomGenerator::global();
            // Genera un índice aleatorio entre 0 y tope - 1
            int num = numRandom->bounded(6);
            switch (num) {
            case 1:
                nacionalidad->setText(obtenerLineaAleatoriaFake(lectorNac));
                fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));
                tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
                duracion->setText(obtenerLineaAleatoria(lectorDur));
                estado_civil->setText(obtenerLineaAleatoria(lectorEst));
                break;
            case 2:
                nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
                fecha_de_nacimiento->setText(obtenerLineaAleatoriaFake(lectorFech));
                tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
                duracion->setText(obtenerLineaAleatoria(lectorDur));
                estado_civil->setText(obtenerLineaAleatoria(lectorEst));
                break;
            case 3:
                nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
                fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));
                tipo_visita->setText(obtenerLineaAleatoriaFake(lectorTipo));
                duracion->setText(obtenerLineaAleatoria(lectorDur));
                estado_civil->setText(obtenerLineaAleatoria(lectorEst));
                break;
            case 4:
                nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
                fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));
                tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
                duracion->setText(obtenerLineaAleatoriaFake(lectorDur));
                estado_civil->setText(obtenerLineaAleatoria(lectorEst));
                break;
            case 5:
                nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
                fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));
                tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
                duracion->setText(obtenerLineaAleatoria(lectorDur));
                estado_civil->setText(obtenerLineaAleatoriaFake(lectorEst));
                break;

            default:
                break;
            }

            return;

    }

    }

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

   // personajeAbst *personaje;
    //personaje =  personajeAbst::crearPersonajeAleatorio();
    //QString tipo=personaje->getTipo();
   // reglas->setText(this->personaje->getTipo());
    if(this->personaje->getDejarPasar()==true){
     reglas->setText("dejar pasar");
    nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
    fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));
    tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
    duracion->setText(obtenerLineaAleatoria(lectorDur));
    estado_civil->setText(obtenerLineaAleatoria(lectorEst));
   // mostrar_documentos();
   // setupDragAndDrop();
   }
    else {
         reglas->setText("no dejar pasar");
        QRandomGenerator *numRandom = QRandomGenerator::global();
        // Genera un índice aleatorio entre 0 y tope - 1
        int num = numRandom->bounded(6);
        switch (num) {
        case 1:
            nacionalidad->setText(obtenerLineaAleatoriaFake(lectorNac));
            fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));
            tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
            duracion->setText(obtenerLineaAleatoria(lectorDur));
            estado_civil->setText(obtenerLineaAleatoria(lectorEst));
            break;
        case 2:
            nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
            fecha_de_nacimiento->setText(obtenerLineaAleatoriaFake(lectorFech));
            tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
            duracion->setText(obtenerLineaAleatoria(lectorDur));
            estado_civil->setText(obtenerLineaAleatoria(lectorEst));
            break;
        case 3:
            nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
            fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));
            tipo_visita->setText(obtenerLineaAleatoriaFake(lectorTipo));
            duracion->setText(obtenerLineaAleatoria(lectorDur));
            estado_civil->setText(obtenerLineaAleatoria(lectorEst));
            break;
        case 4:
            nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
            fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));
            tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
            duracion->setText(obtenerLineaAleatoriaFake(lectorDur));
            estado_civil->setText(obtenerLineaAleatoria(lectorEst));
            break;
        case 5:
            nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
            fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));
            tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
            duracion->setText(obtenerLineaAleatoria(lectorDur));
            estado_civil->setText(obtenerLineaAleatoriaFake(lectorEst));
            break;

        default:
            break;
        }

    }

}


QString nivel1::obtenerLineaAleatoria(LectorArchivos *lector)
{

  //  int tope = lector->getTopeArray();
    QRandomGenerator *numRandom = QRandomGenerator::global();
    // Genera un índice aleatorio entre 0 y tope - 1
    int index = numRandom->bounded(10);
    QString text = lector->getArray()[index];
    return text;

}
QString nivel1::obtenerLineaAleatoriaFake(LectorArchivos *lector)
{

   int tope = lector->getTopeArray();
   QRandomGenerator *numRandomFake = QRandomGenerator::global();
   int min = 11;

   int index = numRandomFake->bounded(min, tope);
   lector->getArray()[index];
    return lector->getArray()[index];

}

void nivel1::setupDragAndDrop()
{
    for (QLabel* label : {reglas, nacionalidad, fecha_de_nacimiento, tipo_visita, duracion, estado_civil}) {
        label->setAcceptDrops(true);
        label->installEventFilter(this);
    }
}

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

QString nivel1::getTipoPersonaje()
{
    QString tipo = personaje->getTipo();
    return tipo;
}

int nivel1::DejarPasarPuntos(){
     if (this->personaje->getDejarPasar()==true){
        GenerarPersonajes();

        return personaje->getPuntos();
    }
    else {

         GenerarPersonajes();

        return this->personaje->getSacarPunto()*-1;

    }
}

int nivel1::NoDejarPasarPuntos(){
    if (this->personaje->getDejarPasar()==false){
         GenerarPersonajes();
        return personaje->getPuntos();
    }
    else {
        GenerarPersonajes();
        return this->personaje->getSacarPunto()*-1;
    }


}
void nivel1::GenerarPersonajes(){
    personajeAbst *personaje;
    personaje =  personajeAbst::crearPersonajeAleatorio();
    this->personaje=personaje;
    emit personajeCambiado(personaje->getTipo());
    setupDocumentos();
    setupDragAndDrop();


}





