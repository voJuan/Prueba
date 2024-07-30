#ifndef PERSONAJEUI_H
#define PERSONAJEUI_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>
#include <QVBoxLayout>
#include <QVector>
#include <QRandomGenerator>
#include "../LectordeArchivos/lectorarchivos.h"
class PersonajeUI : public QWidget
{
    Q_OBJECT
public:
    explicit PersonajeUI(QWidget *parent = nullptr);
    void setimagenPersonaje(QWidget *parent, QString tipoPj);
    void iniciarAnimation(int deltaX, QWidget *parent);

    QRect centrarCoords(QWidget *parent);

public slots:
    void actualizarPersonaje(QString tipoPersonaje);
protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    QLabel *imagenPersonaje; //guardara la imagen del personaje.
    QPropertyAnimation *animacionPersonaje; //contiene los metodos para animar la imagen.
    LectorArchivos *lector; //Contiene los metodos para leer archivos.
    bool estadoAnimacion; //Bandera para saber cuando hay una animacion en ejecucion
    QString generarImagenPj(QString direccionPj);

private slots:


signals:
};

#endif // PERSONAJEUI_H
