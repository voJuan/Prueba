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
    void setimagenPersonaje(QWidget *parent);
    void iniciarAnimation(int deltaX, QWidget *parent);
    QRect centrarCoords(QWidget *parent);
protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    QLabel *imagenPersonaje;
    QPropertyAnimation *animacionPersonaje;
    LectorArchivos *lector;
    bool estadoAnimacion;
private slots:
    void gestionAnimacion();
signals:
};

#endif // PERSONAJEUI_H
