#ifndef NIVEL1_H
#define NIVEL1_H
#include <QQueue>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>
#include <QVBoxLayout>
#include <QVector>
#include <QRandomGenerator>
#include "../LectordeArchivos/lectorarchivos.h"
#include "../PersonajeUI/personajeui.h"
#include <QWidget>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QDragEnterEvent>
#include <QDropEvent>
#include "../personajes/personajeabst.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class nivel1;
}
QT_END_NAMESPACE

class nivel1 : public QWidget
{
    Q_OBJECT

public:
    explicit nivel1(QWidget *parent = nullptr);
    ~nivel1();
    int DejarPasar();
    int NoDejarPasar();
   // virtual void mostrar_documentos();
    virtual void setupDocumentos();
    virtual void setupDragAndDrop();
    QString obtenerLineaAleatoria(LectorArchivos *lector);
    virtual bool eventFilter(QObject *obj, QEvent *event);
    QString getTipoPersonaje();
    int DejarPasarPuntos();
    int NoDejarPasarPuntos();
    virtual void GenerarPersonajes();
    virtual void SetDoc();


    // *personajeAbst crearPersonajeAleatorio();
   // void dragEnterEvent(QDragEnterEvent *event);
   // void dropEvent(QDropEvent *event);

signals:
    void personajeCambiado(QString tipoPersonaje);
private:
    Ui::nivel1 *ui;

protected:
    personajeAbst *personaje;

    // QQueue<std::unique_ptr<Personaje>> personajes;
    QLabel* reglas;
    QLabel*nacionalidad;
    QLabel* fecha_de_nacimiento;
    QLabel* tipo_visita;
    QLabel* duracion;
    QLabel* estado_civil;
    QLabel *proposito;
    QLabel *residencia;
    QMouseEvent* mouseEvent;
    QMouseEvent* event;
    QVBoxLayout *layout;
    LectorArchivos *lectorReg;
    LectorArchivos *lectorNac;
    LectorArchivos *lectorFech;
    LectorArchivos *lectorTipo;
    LectorArchivos *lectorDur;
    LectorArchivos *lectorEst;
    LectorArchivos *lectorRegFake;
    LectorArchivos *lectorNacFake;
    LectorArchivos *lectorFechFake;
    LectorArchivos *lectorTipoFake;
    LectorArchivos *lectorDurFake;
    LectorArchivos *lectorEstFake;
    LectorArchivos *lectorProp;
    LectorArchivos *lectorRes;
    LectorArchivos *lectorPropFake;
    LectorArchivos *lectorResFake;
public slots:

private slots:


};

#endif // NIVEL1_H

