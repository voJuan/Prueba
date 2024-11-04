#include "nivel2.h"
#include "ui_nivel2.h"

nivel2::nivel2(QWidget *parent)
    : nivel1(parent)

{
   // personaje = nullptr;

    nacionalidades = lectorNac->getArray();
    topeNac = lectorNac->getTopeArray();
    SetNivel();
    SetDireccion();
    setupDocumentos();
    setupDragAndDrop();
    GenerarPersonajes();

}



void nivel2::SetNivel(){
    this->nivel=2;
}

void nivel2::SetDireccion(){
    if (this->nivel == 2) {
        this->direccion = ":/archivos.txt/Recursos/Archivos/nivel2.txt";
    }

    LeerTxtNivel(this->direccion);
}

void nivel2::escribirLogs()
{
    QFile archivo("registro_de_logs.txt");
    archivo.open(QIODevice::Append | QIODevice::Text);
    QTextStream salida(&archivo);
    for(const auto& mensaje : this->fallos_nivel2){
        salida << mensaje << Qt::endl;
    }
    archivo.close();
    this->fallos_nivel2.clear();
}

QString nivel2::obtenerReglas(){
    QString reglasTexto = "";

    // Nacionalidad permitida
    reglasTexto += "Nacionalidad permitida:\n";
    if (lineasValidas.find("nacionalidad") != lineasValidas.end()) {
        for (int indice : lineasValidas["nacionalidad"]) {
            reglasTexto += "- " + lectorNac->getArray()[indice] + "\n"; // Usamos el índice para obtener la línea
        }
    }

    // Fecha de nacimiento permitida
    reglasTexto += "Fecha de nacimiento permitida:\n";
    if (lineasValidas.find("fecha_de_nacimiento") != lineasValidas.end()) {
        for (int indice : lineasValidas["fecha_de_nacimiento"]) {
            reglasTexto += "- " + lectorFech->getArray()[indice] + "\n";
        }
    }

    // Tipo de visita permitido
    reglasTexto += "Tipo de visita permitido:\n";
    if (lineasValidas.find("tipo_visita") != lineasValidas.end()) {
        for (int indice : lineasValidas["tipo_visita"]) {
            reglasTexto += "- " + lectorTipo->getArray()[indice] + "\n";
        }
    }

    // Duración de estancia permitida
    reglasTexto += "Duración de la estancia permitida:\n";
    if (lineasValidas.find("duracion") != lineasValidas.end()) {
        for (int indice : lineasValidas["duracion"]) {
            reglasTexto += "- " + lectorDur->getArray()[indice] + "\n";
        }
    }

    // Estado civil permitido
    reglasTexto += "Estado civil permitido:\n";
    if (lineasValidas.find("estado_civil") != lineasValidas.end()) {
        for (int indice : lineasValidas["estado_civil"]) {
            reglasTexto += "- " + lectorEst->getArray()[indice] + "\n";
        }
    }

    reglasTexto += "proposito permitido:\n";
    if (lineasValidas.find("proposito") != lineasValidas.end()) {
        for (int indice : lineasValidas["proposito"]) {
            reglasTexto += "- " + lectorProp->getArray()[indice] + "\n";
        }
    }



    return reglasTexto;
}



void nivel2::setupDocumentos(){
     // Llama al método base para configurar etiquetas

    proposito = new QLabel("Cargando...", this);
    proposito->setStyleSheet("background-color: lightgray; color: black;");

    // Obtener el layout actual y añadir el nuevo widget
    QLayout *currentLayout = this->layout; // Obtén el puntero a layout
    if (currentLayout) {
        QVBoxLayout *vboxLayout = qobject_cast<QVBoxLayout *>(currentLayout);
        if (vboxLayout) {
            vboxLayout->addWidget(proposito); // Añadir la nueva etiqueta al layout existente
            vboxLayout->addStretch(); // Opcional: añadir espacio extra después de agregar nuevo widget
        } else {
            qWarning() << "El layout no es un QVBoxLayout.";
        }
    } else {
        qWarning() << "No se pudo obtener el layout de nivel2.";
    }
}

void nivel2::SetDoc(){
    //this->proposito->setText("nivel2");
    this->reglas->setText("DOCUMENTOS:");

    this->nacionalidad->clear();
    this->fecha_de_nacimiento->clear();
    this->tipo_visita->clear();
    this->duracion->clear();
    this->estado_civil->clear();
    this->proposito->clear();

    // Si el personaje puede pasar, todos los documentos son verdaderos
    if (this->personaje->getDejarPasar()) {
        this->proposito->setText(obtenerLinea_Archivo(lectorProp, lineasValidas["proposito"], false));
        this->nacionalidad->setText(obtenerLinea_Archivo(lectorNac, lineasValidas["nacionalidad"], false));
        this->fecha_de_nacimiento->setText(obtenerLinea_Archivo(lectorFech, lineasValidas["fecha_de_nacimiento"], false));
        this->tipo_visita->setText(obtenerLinea_Archivo(lectorTipo, lineasValidas["tipo_visita"], false));
        this->duracion->setText(obtenerLinea_Archivo(lectorDur, lineasValidas["duracion"], false));
        this->estado_civil->setText(obtenerLinea_Archivo(lectorEst, lineasValidas["estado_civil"], false));
        return;
    }

    // Si no puede pasar, asignamos documentos falsos de manera aleatoria
    int numDocumentos = 6;
    std::vector<int> documentosFalsos;
    int cantidadFalsos = QRandomGenerator::global()->bounded(1, numDocumentos-1);
    qDebug() << "Cantidad de documentos falsos seleccionados: " << cantidadFalsos;
    // Seleccionar índices de documentos falsos
    for (int i = 0; i < cantidadFalsos; ++i) {
        int indiceFalso;
        do {
            indiceFalso = QRandomGenerator::global()->bounded(0, numDocumentos);
        } while (std::find(documentosFalsos.begin(), documentosFalsos.end(), indiceFalso) != documentosFalsos.end());
        documentosFalsos.push_back(indiceFalso);
    }
    QString parametroFalso;
    // Asignación de documentos (falsos o verdaderos según el índice)
    for (int i = 0; i < numDocumentos; ++i) {
        if (std::find(documentosFalsos.begin(), documentosFalsos.end(), i) != documentosFalsos.end()) {
            // Documento falso
            switch (i) {
            case 0:
                parametroFalso = obtenerLinea_Archivo(lectorNac, lineasValidas["nacionalidad"], true);
                this->nacionalidad->setText(parametroFalso);
                fallos_nivel2.insert(parametroFalso);
                break;
            case 1:
                parametroFalso = obtenerLinea_Archivo(lectorFech, lineasValidas["fecha_de_nacimiento"], true);
                this->fecha_de_nacimiento->setText(parametroFalso);
                fallos_nivel2.insert(parametroFalso);
                break;
            case 2:
                parametroFalso = obtenerLinea_Archivo(lectorTipo, lineasValidas["tipo_visita"], true);
                this->tipo_visita->setText(parametroFalso);
                fallos_nivel2.insert(parametroFalso);
                break;
            case 3:
                parametroFalso = obtenerLinea_Archivo(lectorDur, lineasValidas["duracion"], true);
                this->duracion->setText(parametroFalso);
                fallos_nivel2.insert(parametroFalso);
                break;
            case 4:
                parametroFalso = obtenerLinea_Archivo(lectorEst, lineasValidas["estado_civil"], true);
                this->estado_civil->setText(parametroFalso);
                fallos_nivel2.insert(parametroFalso);
                break;
            case 5:
                parametroFalso = obtenerLinea_Archivo(lectorProp, lineasValidas["proposito"], true);
                this->proposito->setText(parametroFalso);
                fallos_nivel2.insert(parametroFalso);
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
            case 5:
                this->proposito->setText(obtenerLinea_Archivo(lectorProp, lineasValidas["proposito"], false));
                break;
            }
        }
    }


}
int nivel2::PasarNivel(){
    this->fallos_nivel2.clear();
    return 3;
}

nivel2::~nivel2()
{
   // delete ui;
}
