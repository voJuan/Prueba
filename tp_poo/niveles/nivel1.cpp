#include "nivel1.h"
#include "ui_nivel1.h"
#include <QDrag>
#include <QMimeData>
#include <QFile>
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
//lectorRegFake(new LectorArchivos(":/archivos.txt/Recursos/Archivos/reglas.txt")),
lectorNacFake(new LectorArchivos(":/archivos.txt/Recursos/Archivos/nacionalidad_fake.txt")),
lectorFechFake(new LectorArchivos(":/archivos.txt/Recursos/Archivos/fecha_nacimiento_fake.txt")),
lectorTipoFake(new LectorArchivos(":/archivos.txt/Recursos/Archivos/tipo_visita_fake.txt")),
lectorDurFake(new LectorArchivos(":/archivos.txt/Recursos/Archivos/duracion_fake.txt")),
lectorEstFake(new LectorArchivos(":/archivos.txt/Recursos/Archivos/estado_civil_fake.txt"))
//personaje(new personajeAbst())
{
   layout = new QVBoxLayout(this);
    personaje = nullptr;

    nacionalidades = lectorNac->getArray();
    topeNac = lectorNac->getTopeArray();

    LeerTxtNivel();
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
//       LEER TXT
void nivel1::LeerTxtNivel(){
    QFile archivo(":/archivos.txt/Recursos/Archivos/nivel1.txt");
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





