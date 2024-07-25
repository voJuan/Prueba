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
lectorEst(new LectorArchivos(":/archivos.txt/Recursos/Archivos/estado_civil.txt")),
 personaje(new personajeAbst())
{
    ui->setupUi(this);
    // lector(new LectorArchivos(":/archivos.txt/Recursos/Imagenes/imagenes-personajes.txt"))

    setupDocumentos();
    setupDragAndDrop();
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
    reglas->setText("Texto de prueba");
    nacionalidad->setText(obtenerLineaAleatoria(lectorNac));
    fecha_de_nacimiento->setText(obtenerLineaAleatoria(lectorFech));
    tipo_visita->setText(obtenerLineaAleatoria(lectorTipo));
    duracion->setText(obtenerLineaAleatoria(lectorDur));
    estado_civil->setText(obtenerLineaAleatoria(lectorEst));
   // mostrar_documentos();
   // setupDragAndDrop();
}


QString nivel1::obtenerLineaAleatoria(LectorArchivos *lector)
{
    int tope = lector->getTopeArray();
    QRandomGenerator *numRandom = QRandomGenerator::global();
    // Genera un índice aleatorio entre 0 y tope - 1
    int index = numRandom->bounded(tope);
    QString text = lector->getArray()[index];
    return text;

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
