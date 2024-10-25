#include "nivel2.h"
#include "ui_nivel2.h"

nivel2::nivel2(QWidget *parent)
    : nivel1(parent)

{
    personaje = nullptr;

    nacionalidades = lectorNac->getArray();
    topeNac = lectorNac->getTopeArray();


    setupDocumentos();
    setupDragAndDrop();
    GenerarPersonajes();

}

void nivel2::setupDocumentos(){
     // Llama al método base para configurar etiquetas

    equipo = new QLabel("Cargando...", this);
    equipo->setStyleSheet("background-color: lightgray; color: black;");

    // Obtener el layout actual y añadir el nuevo widget
    QLayout *currentLayout = this->layout; // Obtén el puntero a layout
    if (currentLayout) {
        QVBoxLayout *vboxLayout = qobject_cast<QVBoxLayout *>(currentLayout);
        if (vboxLayout) {
            vboxLayout->addWidget(equipo); // Añadir la nueva etiqueta al layout existente
            vboxLayout->addStretch(); // Opcional: añadir espacio extra después de agregar nuevo widget
        } else {
            qWarning() << "El layout no es un QVBoxLayout.";
        }
    } else {
        qWarning() << "No se pudo obtener el layout de nivel2.";
    }
}

void nivel2::SetDoc(){
    this->equipo->setText("nivel2");
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
nivel2::~nivel2()
{
    delete ui;
}
