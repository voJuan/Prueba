#include "personajeui.h"

PersonajeUI::PersonajeUI(QWidget *parent)
    : QWidget{parent},
    imagenPersonaje(new QLabel(this)),
    animacionPersonaje(new QPropertyAnimation(imagenPersonaje,"geometry")),
    lector(new LectorArchivos(":/recursos/imagenes/Recursos/Imagenes/imagenes-personajes.txt"))
{
}

void PersonajeUI::setimagenPersonaje(QWidget *parent)
{
    int tope = lector->getTopeArray();
    if (tope == 0) {
        qWarning("No hay imágenes disponibles en el archivo.");
        return;
    }
    QRandomGenerator *numRandom = QRandomGenerator::global();
    // Genera un índice aleatorio entre 0 y tope - 1
    int index = numRandom->bounded(tope);
    QString direccionImagen = lector->getArray()[index];

    if (!direccionImagen.isEmpty()) {
        imagenPersonaje->setScaledContents(true);
        imagenPersonaje->setFixedSize(300, 300); // Asegúrate de que el QLabel tenga un tamaño fijo
        setFixedSize(700, 700);

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

void PersonajeUI::iniciarAnimation(int deltaX, QWidget *parent)
{
    animacionPersonaje->setDuration(2000);
    QRect propsIniciales = imagenPersonaje->geometry();
    QRect propsFinales = propsIniciales;
    propsFinales.translate(deltaX, 0); //translate añade int en la prop x e y
    animacionPersonaje->setStartValue(propsIniciales);
    animacionPersonaje->setEndValue(propsFinales);
    animacionPersonaje->start();
}

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

void PersonajeUI::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    // Recalcular y ajustar la geometría del QLabel para centrarlo
    QRect centeredRect = centrarCoords(this); // Asumiendo que el padre es 'this'
    imagenPersonaje->setGeometry(centeredRect);
}
