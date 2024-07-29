#include "nivel2.h"
#include "ui_nivel2.h"
#include <QDrag>
#include <QMimeData>
nivel2::nivel2(QWidget *parent)
    : nivel1(parent)
    , ui(new Ui::nivel2),
     layout2(new QVBoxLayout(this))




{
    ui->setupUi(this);
    setupDocumentos();
    setupDragAndDrop();
    GenerarPersonajes();
}

nivel2::~nivel2()
{
    delete ui;
}

void nivel2::setupDocumentos()
{


    nacionalidad = new QLabel("Cargando...", this);
    fecha_de_nacimiento = new QLabel("Cargando...", this);
    tipo_visita = new QLabel("Cargando...", this);
    proposito = new QLabel("Cargando...", this);
    duracion = new QLabel("Cargando...", this);
    estado_civil = new QLabel("Cargando...", this);

    residencia = new QLabel("Cargando...", this);
    reglas->setStyleSheet("background-color: lightgray; color: black;");
    nacionalidad->setStyleSheet("background-color: lightgray; color: black;");
    fecha_de_nacimiento->setStyleSheet("background-color: lightgray; color: black;");
    tipo_visita->setStyleSheet("background-color: lightgray; color: black;");
    duracion->setStyleSheet("background-color: lightgray; color: black;");
    estado_civil->setStyleSheet("background-color: lightgray; color: black;");
    proposito->setStyleSheet("background-color: lightgray; color: black;");
    residencia->setStyleSheet("background-color: lightgray; color: black;");


    layout2->addWidget(nacionalidad);
    layout2->addWidget(proposito);
    layout2->addWidget(fecha_de_nacimiento);
    layout2->addWidget(tipo_visita);
    layout2->addWidget(duracion);
    layout2->addWidget(estado_civil);

    layout2->addWidget(residencia);

    //setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //setMinimumSize(200, 200);  // Tamaño mínimo
    //setMaximumSize(200, 200);

    setLayout(layout2);

}
void nivel2::SetDoc()  {
    if(this->personaje->getDejarPasar()==true){

        this->nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
        this->fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));

        this->tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
        this->duracion->setText(obtenerLineaAleatoria(lectorDur));
        this->estado_civil->setText(obtenerLineaAleatoria(lectorEst));
        this->proposito->setText(obtenerLineaAleatoria(lectorProp));
        this->residencia->setText(obtenerLineaAleatoria(lectorRes));
        return;
    }
    else {

        QRandomGenerator *numRandom = QRandomGenerator::global();
        int num = numRandom->bounded(7) + 1;
        switch (num) {
        case 1:
            this->nacionalidad->setText(obtenerLineaAleatoria(lectorNacFake));
            this->fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));
            this->tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
            this->duracion->setText(obtenerLineaAleatoria(lectorDur));
            this->estado_civil->setText(obtenerLineaAleatoria(lectorEst));
            this->proposito->setText(obtenerLineaAleatoria(lectorProp));
            this->residencia->setText(obtenerLineaAleatoria(lectorRes));
            break;
        case 2:
            this->nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
            this->fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFechFake));
            this->tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
            this->duracion->setText(obtenerLineaAleatoria(lectorDur));
            this->estado_civil->setText(obtenerLineaAleatoria(lectorEst));
            this->proposito->setText(obtenerLineaAleatoria(lectorProp));
            this->residencia->setText(obtenerLineaAleatoria(lectorRes));
            break;
        case 3:
            this->nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
            this->fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));
            this->tipo_visita->setText(obtenerLineaAleatoria(lectorTipoFake));
            this->duracion->setText(obtenerLineaAleatoria(lectorDur));
            this->estado_civil->setText(obtenerLineaAleatoria(lectorEst));
            this->proposito->setText(obtenerLineaAleatoria(lectorProp));
            this->residencia->setText(obtenerLineaAleatoria(lectorRes));
            break;
        case 4:
            this->nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
            this->fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));
            this->tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
            this->duracion->setText(obtenerLineaAleatoria(lectorDurFake));
            this->estado_civil->setText(obtenerLineaAleatoria(lectorEst));
            this->proposito->setText(obtenerLineaAleatoria(lectorProp));
            this->residencia->setText(obtenerLineaAleatoria(lectorRes));
            break;
        case 5:
            this->nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
            this->fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));
            this->tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
            this->duracion->setText(obtenerLineaAleatoria(lectorDur));
            this->estado_civil->setText(obtenerLineaAleatoria(lectorEstFake));
            this->proposito->setText(obtenerLineaAleatoria(lectorProp));
            this->residencia->setText(obtenerLineaAleatoria(lectorRes));
            break;
        case 6:
            this->nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
            this->fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));
            this->tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
            this->duracion->setText(obtenerLineaAleatoria(lectorDur));
            this->estado_civil->setText(obtenerLineaAleatoria(lectorEst));
            this->proposito->setText(obtenerLineaAleatoria(lectorPropFake));
            this->residencia->setText(obtenerLineaAleatoria(lectorResFake));
            break;
        case 7:
            this->nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
            this->fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));
            this->tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
            this->duracion->setText(obtenerLineaAleatoria(lectorDur));
            this->estado_civil->setText(obtenerLineaAleatoria(lectorEstFake));
            this->proposito->setText(obtenerLineaAleatoria(lectorProp));
            this->residencia->setText(obtenerLineaAleatoria(lectorRes));
            break;

        default:
            break;
        }
        return;
    }


}
void nivel2::setupDragAndDrop()
{
    for (QLabel* label : { nacionalidad,proposito, fecha_de_nacimiento, tipo_visita, duracion, estado_civil, residencia}) {
        label->setAcceptDrops(true);
        label->installEventFilter(this);
    }
}
bool nivel2::eventFilter(QObject *obj, QEvent *event)
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
void nivel2::GenerarPersonajes(){
    personajeAbst *personaje = personajeAbst::crearPersonajeAleatorio();
    this->personaje = personaje;
    emit personajeCambiado(personaje->getTipo());
    SetDoc();
}

