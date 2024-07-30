#include "personajeui.h"

PersonajeUI::PersonajeUI(QWidget *parent)
    : QWidget{parent}, //Inicializacion de los atributos de la clase.
    imagenPersonaje(new QLabel(this)),
    animacionPersonaje(new QPropertyAnimation(imagenPersonaje,"geometry")),
    lector(new LectorArchivos(":/archivos.txt/Recursos/Imagenes/imagenes-personajes.txt")),
    estadoAnimacion(false)
{

}

//######################## METODOS PARA CREAR LA PARTE VISUAL DEL PERSONAJE ###########################
//
//Este metodo inserta una imagen aleatoria, segun el tipo del personaje.
void PersonajeUI::setimagenPersonaje(QWidget *parent, QString tipoPj) // Requiere un padre QWidget para ajustarse y desplazarse solo en los limites del mismo.
{

    QString direccionImagen; //Este QString guardara la direccion de donde se encuentra la imagen.
                             //Luego segun el tipo con la funcion generarImagenPj se elige dicha imagen aleatoriamente
    if(tipoPj == "aldeano"){
        direccionImagen = generarImagenPj(":/archivos.txt/Recursos/Archivos/aldeano_aleatorio.txt");
    }
    else if(tipoPj == "revolucionario"){
        direccionImagen = generarImagenPj(":/archivos.txt/Recursos/Archivos/revolucionario_aleatorio.txt");
    }
    else if(tipoPj == "diplomatico"){
        direccionImagen = generarImagenPj(":/archivos.txt/Recursos/Archivos/diplomatico.txt");
    }
    else if(tipoPj == "refugiado"){
        direccionImagen = generarImagenPj(":/archivos.txt/Recursos/Archivos/refugiado.txt");
    }
    if (!direccionImagen.isEmpty()) {
        //De la linea 34 a 48 se eligen las propiedades de la imagen.

        imagenPersonaje->setScaledContents(true); //Se ajusta el contenido de la imagen segun el layout
        imagenPersonaje->setFixedSize(300, 300); //Se fija el tamaño de la imagen.
        setFixedSize(700, 700); //Se fija el tamaño de donde sera visible la imagen.
        imagenPersonaje->setStyleSheet("background-color: rgba(255, 255, 255, 0); border: none;"); //Se elige el estilo para que el fondo se vea transparente.

        QPixmap imagen(direccionImagen);
        if (imagen.isNull()) {
            qWarning("No se pudo cargar la imagen desde: %s", qPrintable(direccionImagen));
        } else {
            imagenPersonaje->setPixmap(imagen);
        }
        QRect centeredRect = centrarCoords(parent);
        imagenPersonaje->setGeometry(centeredRect);
    } else {
        qWarning("La dirección de la imagen está vacía.");
    }
}
//
//Controla el desplazamiento de la imagen eligiendo como parametros la direccion de movimiento segun el eje x y el padre de donde se desplazara.
void PersonajeUI::iniciarAnimation(int deltaX, QWidget *parent)
{
       //Condicional que compara si ya existe una animacion en proceso.
    if (!estadoAnimacion) {
        estadoAnimacion = true;
        animacionPersonaje->setDuration(2000); //Duracion de la animacion.
        QRect propsIniciales = imagenPersonaje->geometry(); //Propiedades iniciales
        QRect propsFinales = propsIniciales; //Propiedades finales
        propsFinales.translate(deltaX, 0);  //Se elige el desplazamiento
        animacionPersonaje->setStartValue(propsIniciales); //De donde empieza la animacion.
        animacionPersonaje->setEndValue(propsFinales); //Hasta donde termina.
        animacionPersonaje->start(); //Se ejecuta la animacion.
    }
}
//
//Este metodo se conectara con la señal personajeCambiado(QString tipoPersonaje) que mandara nivel1, para elegir la imagen que le corresponde al personaje.
void PersonajeUI::actualizarPersonaje(QString tipoPersonaje)
{
    estadoAnimacion = false; // La animación ha terminado
    imagenPersonaje->clear(); //Se borra la imagen del personaje anterior.
    qDebug() << "TIPO: " << tipoPersonaje;
    setimagenPersonaje(this, tipoPersonaje); //Se elige la imagen segun el tipo.
    imagenPersonaje->move(-200,imagenPersonaje->y()); //Se mueve la imagen hacia afuera del widget.
    iniciarAnimation(200, this); //Se ejecuta el metodo de animacion para simular la entrada del mismo.
}
//
//Metodo que elige en que parte del QWidget aparecera la imagen.
QRect PersonajeUI::centrarCoords(QWidget *parent)
{
    // Obtener el centro del rectángulo del widget padre
    QPoint center = parent->rect().center();

    // Calcular las coordenadas superiores izquierdas para centrar el QLabel
    int ancho = imagenPersonaje->width();
    int alto = imagenPersonaje->height();
    int coordsX = (center.x() - ancho) / 2;
    int coordsY = (center.y() - alto) * 1.5;

    // Crear un QRect con las coordenadas calculadas y el tamaño del QLabel
    return QRect(coordsX, coordsY, ancho, alto);
}
//
//Sobreescritura de la funcion resizeEvent para ajustar la imagen segun el tamaño de la pantalla.
void PersonajeUI::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    // Recalcular y ajustar la geometría del QLabel para centrarlo
    QRect centeredRect = centrarCoords(this); // Asumiendo que el padre es 'this'
    imagenPersonaje->setGeometry(centeredRect);
}
//
//Generador de imagenes aleatorios, retorna un QString con la direccion que encuentra en el documento txt.
QString PersonajeUI::generarImagenPj(QString direccionPj)
{
    LectorArchivos *lectorr = new LectorArchivos(direccionPj); //Variable que contiene los metodos para leer archivos.

    int tope = lectorr->getTopeArray(); //Variable que guarda el maximo de lineas que contiene el documento de texto.
    if (tope == 0) {
        qWarning("No hay imágenes disponibles en el archivo.");
        exit(0);
    }
    QRandomGenerator *numRandom = QRandomGenerator::global(); //Se crea una variable de tipo QRandomgenerator.

    int indice = numRandom->bounded(tope); //Indice guardara el numero elegido aleatoriamente con el metodo correspondiente a QRandomGenerator (tomara entre 0 y tope).
    QString direccionIma = lectorr->getArray()[indice]; //Elige del arreglo de lineas de texto con el numero indice, la direccion de la imagen.
    return direccionIma;
}
//
//#####################################################################################################
