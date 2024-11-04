#include "nivel1.h"
#include "ui_nivel1.h"
#include <QDrag>
#include <QMimeData>
#include <QFile>
#include <QDebug>
#include <QTextStream>
nivel1::nivel1(QWidget *parent)
    : QWidget(parent)

   ,

lectorReg(new LectorArchivos(":/archivos.txt/Recursos/Archivos/reglas.txt")),
lectorNac(new LectorArchivos(":/archivos.txt/Recursos/Archivos/nacionalidad.txt")),
lectorFech(new LectorArchivos(":/archivos.txt/Recursos/Archivos/fecha_nacimiento.txt")),
lectorTipo(new LectorArchivos(":/archivos.txt/Recursos/Archivos/tipo_visita.txt")),
lectorDur(new LectorArchivos(":/archivos.txt/Recursos/Archivos/duracion.txt")),
lectorEst(new LectorArchivos(":/archivos.txt/Recursos/Archivos/estado_civil.txt")),
lectorProp(new LectorArchivos(":/archivos.txt/Recursos/Archivos/proposito.txt")),
lectorInt(new LectorArchivos(":/archivos.txt/Recursos/Archivos/integrantes.txt")),
lectorOcup(new LectorArchivos(":/archivos.txt/Recursos/Archivos/ocupacion.txt")),
lectorVac(new LectorArchivos(":/archivos.txt/Recursos/Archivos/vacunacion.txt"))
//lectorRegFake(new LectorArchivos(":/archivos.txt/Recursos/Archivos/reglas.txt")),

//personaje(new personajeAbst())
{
   layout = new QVBoxLayout(this);
    personaje = nullptr;

    nacionalidades = lectorNac->getArray();
    topeNac = lectorNac->getTopeArray();
    SetNivel();
    SetDireccion();
    setupDocumentos();
    setupDragAndDrop();
    GenerarPersonajes();

}

nivel1::~nivel1()
{
  //  delete lectorReg;
    //delete lectorNac;
    //delete lectorFech;
   // delete lectorTipo;
    //delete lectorDur;
    //delete lectorEst;
    //delete ui;

}
//############ funciones para documentos ###############################
//       LEER TXT
void nivel1::SetDireccion(){
    if (this->nivel == 1) {
        this->direccion = ":/archivos.txt/Recursos/Archivos/nivel1.txt";
    }



    LeerTxtNivel(this->direccion);
}


void nivel1::LeerTxtNivel(QString direcc){
    QFile archivo(direcc);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("No se pudo abrir el archivo de reglas.");
        return;
    }

    QTextStream in(&archivo);
    while (!in.atEnd()) {
        QString linea = in.readLine();

        // Parsear la línea: por ejemplo "nacionalidad: 1, 2, 5"
        QStringList partes = linea.split(":");
        if (partes.size() < 2) continue;  // Si no hay suficientes partes, continuar

        QString campo = partes[0].trimmed();
        QStringList numeros = partes[1].split(",");

        // Convertir cada número en un entero y agregarlo al vector correspondiente
        vector<int> lineas;
        for (const QString &num : numeros) {
            lineas.push_back(num.trimmed().toInt());
        }

        // Guardar el vector de líneas válidas en el mapa
        this->lineasValidas[campo] = lineas;
    }

    archivo.close();
}


QString nivel1::obtenerReglas(){
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

    return reglasTexto;
}








//..
// Crear la etiquetas para documentos
void nivel1::setupDocumentos()
{
    // Asumiendo que reglas es un puntero a QLabel
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
    this->reglas->setText("DOCUMENTOS:");
    this->nacionalidad->clear();
    this->fecha_de_nacimiento->clear();
    this->tipo_visita->clear();
    this->duracion->clear();
    this->estado_civil->clear();

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
    QString parametroFalso;
    // Asignación de documentos (falsos o verdaderos según el índice)
    for (int i = 0; i < numDocumentos; ++i) {
        if (std::find(documentosFalsos.begin(), documentosFalsos.end(), i) != documentosFalsos.end()) {
            // Documento falso
            switch (i) {
            case 0:
                parametroFalso = obtenerLinea_Archivo(lectorNac, lineasValidas["nacionalidad"], true);
                this->nacionalidad->setText(parametroFalso);
                fallos_nivel1.insert(parametroFalso);
                break;
            case 1:
                parametroFalso = obtenerLinea_Archivo(lectorFech, lineasValidas["fecha_de_nacimiento"], true);
                this->fecha_de_nacimiento->setText(parametroFalso);
                fallos_nivel1.insert(parametroFalso);
                break;
            case 2:
                parametroFalso = obtenerLinea_Archivo(lectorTipo, lineasValidas["tipo_visita"], true);
                this->tipo_visita->setText(parametroFalso);
                fallos_nivel1.insert(parametroFalso);
                break;
            case 3:
                parametroFalso = obtenerLinea_Archivo(lectorDur, lineasValidas["duracion"], true);
                this->duracion->setText(parametroFalso);
                fallos_nivel1.insert(parametroFalso);
                break;
            case 4:
                parametroFalso = obtenerLinea_Archivo(lectorEst, lineasValidas["estado_civil"], true);
                this->estado_civil->setText(parametroFalso);
                fallos_nivel1.insert(parametroFalso);
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
// dado un puntero a LectorArchivos elegir una linea aleatoriamente
QString nivel1::obtenerLinea_Archivo(LectorArchivos *lector, const vector<int>& permitidas, bool generarFalso) {
    int tope = lector->getTopeArray();
    QRandomGenerator *numRandom = QRandomGenerator::global();
    int intentos = 0;

    if (generarFalso) {
        // Generar una línea que NO esté en el vector de permitidas
        int indexFalso;
        do {
            indexFalso = numRandom->bounded(tope);  // Generar índice aleatorio
            qDebug() << "Intento #" << intentos << " con indexFalso: " << indexFalso;
            intentos++;
            indexFalso++;
            // Verificar si `indexFalso + 1` supera el tope y ajustarlo si es necesario
            if (indexFalso >= tope) {
                indexFalso = 0;  // Ajustar a un índice válido
            }

        } while (std::find(permitidas.begin(), permitidas.end(), indexFalso ) != permitidas.end());  // Repetir si está permitido

        return lector->getArray()[indexFalso];
    } else {
        // Elegir una línea dentro de las permitidas
        int indexPermitido = permitidas[numRandom->bounded(permitidas.size())] ;
        return lector->getArray()[indexPermitido];
    }
}



//



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
    personajeAbst *personaje = personajeAbst::crearPersonajeAleatorio();
    this->personaje = personaje;

    if (personaje != nullptr) {
        emit personajeCambiado(personaje->getTipo());
        SetDoc();
    } else {
        // Manejo del caso donde personaje es nullptr
        //std::cerr << "Error: El personaje es un puntero nulo." << std::endl;
        // Puedes añadir lógica adicional aquí si es necesario
    }
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

void nivel1::escribirLogs()
{
    QFile archivo("registro_de_logs.txt");
    archivo.open(QIODevice::Append | QIODevice::Text);
    QTextStream salida(&archivo);
    for(const auto& mensaje : this->fallos_nivel1){
        salida << mensaje << Qt::endl;
    }
    archivo.close();
    this->fallos_nivel1.clear();
}

void nivel1::escribirLog(const QString& mensaje)
{
    QFile archivo("registro_de_logs.txt");
    archivo.open(QIODevice::Append | QIODevice::Text);
    QTextStream salida(&archivo);
    salida << mensaje << Qt::endl;
    archivo.close();
}

void nivel1::borrarLogs()
{
    QFile archivo("registro_de_logs.txt");
    archivo.open(QIODevice::WriteOnly | QIODevice::Text);
    archivo.close();
}
// Get para saber cuantas multas hay acumuladas
int nivel1::GetMultas(){
    return this->multa;
}
//#######################################################################################
//########################## get de tiempo nivel ########################################
int nivel1::getTiempo(){


    this->tiempo=this->lineasValidas["tiempo"][0];
    return this->tiempo;
}

//#######################################################################################
//#########################  get de puntaje #############################################
int nivel1::getPuntaje(){
    this->puntaje=this->lineasValidas["puntos"][0];
    return this->puntaje;
}
//#######################################################################################
void nivel1::SetNivel(){

    this->nivel=1;
}

int nivel1::PasarNivel(){
    this->fallos_nivel1.clear();
    return 2;
}
