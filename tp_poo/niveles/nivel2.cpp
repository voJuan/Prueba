#include "nivel2.h"
#include "ui_nivel2.h"

nivel2::nivel2(QWidget *parent)
    : nivel1(parent)

{
   // personaje = nullptr;

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
    this->reglas->setText("DOCUMENTOS:");

    // Si el personaje puede pasar, todos los documentos son verdaderos
    if (this->personaje->getDejarPasar()) {
        this->nacionalidad->setText(obtenerLinea_Archivo(lectorNac, lineasValidas["nacionalidad"], false));
        this->fecha_de_nacimiento->setText(obtenerLinea_Archivo(lectorFech, lineasValidas["fecha_de_nacimiento"], false));
        this->tipo_visita->setText(obtenerLinea_Archivo(lectorTipo, lineasValidas["tipo_visita"], false));
        this->duracion->setText(obtenerLinea_Archivo(lectorDur, lineasValidas["duracion"], false));
        this->estado_civil->setText(obtenerLinea_Archivo(lectorEst, lineasValidas["estado_civil"], false));
        return;
    }

    // Si no puede pasar, asignamos documentos falsos de manera aleatoria
    int numDocumentos = 5;
    std::vector<int> documentosFalsos;
    int cantidadFalsos = QRandomGenerator::global()->bounded(1, numDocumentos+1);
    qDebug() << "Cantidad de documentos falsos seleccionados: " << cantidadFalsos;
    // Seleccionar índices de documentos falsos
    for (int i = 0; i < cantidadFalsos; ++i) {
        int indiceFalso;
        do {
            indiceFalso = QRandomGenerator::global()->bounded(0, numDocumentos);
        } while (std::find(documentosFalsos.begin(), documentosFalsos.end(), indiceFalso) != documentosFalsos.end());
        documentosFalsos.push_back(indiceFalso);
    }

    // Asignación de documentos (falsos o verdaderos según el índice)
    for (int i = 0; i < numDocumentos; ++i) {
        if (std::find(documentosFalsos.begin(), documentosFalsos.end(), i) != documentosFalsos.end()) {
            // Documento falso
            switch (i) {
            case 0:
                this->nacionalidad->setText(obtenerLinea_Archivo(lectorNac, lineasValidas["nacionalidad"], true));
                break;
            case 1:
                this->fecha_de_nacimiento->setText(obtenerLinea_Archivo(lectorFech, lineasValidas["fecha_de_nacimiento"], true));
                break;
            case 2:
                this->tipo_visita->setText(obtenerLinea_Archivo(lectorTipo, lineasValidas["tipo_visita"], true));
                break;
            case 3:
                this->duracion->setText(obtenerLinea_Archivo(lectorDur, lineasValidas["duracion"], true));
                break;
            case 4:
                this->estado_civil->setText(obtenerLinea_Archivo(lectorEst, lineasValidas["estado_civil"], true));
                break;
            }
        } else {
            // Documento verdadero
            switch (i) {
            case 0:
                this->nacionalidad->setText(obtenerLinea_Archivo(lectorNac, lineasValidas["nacionalidad"], false));
                break;
            case 1:
                this->fecha_de_nacimiento->setText(obtenerLinea_Archivo(lectorFech, lineasValidas["fecha_de_nacimiento"], false));
                break;
            case 2:
                this->tipo_visita->setText(obtenerLinea_Archivo(lectorTipo, lineasValidas["tipo_visita"], false));
                break;
            case 3:
                this->duracion->setText(obtenerLinea_Archivo(lectorDur, lineasValidas["duracion"], false));
                break;
            case 4:
                this->estado_civil->setText(obtenerLinea_Archivo(lectorEst, lineasValidas["estado_civil"], false));
                break;
            }
        }
    }


}
nivel2::~nivel2()
{
    delete ui;
}
