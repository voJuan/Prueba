#ifndef NIVEL1_H
#define NIVEL1_H
#include <QQueue>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QFile>
#include <QPropertyAnimation>
#include <QVBoxLayout>
#include <QVector>
#include <QSet>
#include <QRandomGenerator>
#include "../LectordeArchivos/lectorarchivos.h"
#include "../PersonajeUI/personajeui.h"
#include <QWidget>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QLabel>
#include "../personajes/personajeabst.h"
#include <map>
#include <vector>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QIODevice>
#include <QDebug>
#include <algorithm>
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
    void setupDragAndDrop();
    void LeerTxtNivel(QString direcc);
    virtual void SetDireccion();
    QString obtenerLineaAleatoria(LectorArchivos *lector);
    QString obtenerLinea_Archivo(LectorArchivos *lector, const vector<int>& permitidas, bool generarFalso);
    bool eventFilter(QObject *obj, QEvent *event);
    QString getTipoPersonaje();
    int getTiempo();
    int getPuntaje();
    virtual QString obtenerReglas();
    int DejarPasarPuntos();
    int NoDejarPasarPuntos();
    void GenerarPersonajes();
    virtual void SetDoc();
    virtual int PasarNivel();
    int GetMultas();
    void SetMulta();
    void escribirLog(const QString& mensaje);
    virtual void escribirLogs();
    void borrarLogs();
    virtual void SetNivel();
    // *personajeAbst crearPersonajeAleatorio();
   // void dragEnterEvent(QDragEnterEvent *event);
   // void dropEvent(QDropEvent *event);

signals:
    void personajeCambiado(QString tipoPersonaje);
protected:
    Ui::nivel1 *ui;
    int multa = 0;
    int tiempo;
    int puntaje;
    int nivel;
    QString direccion;
    map<QString,vector<int>> lineasValidas;
    personajeAbst *personaje;
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
    LectorArchivos *lectorInt;
    LectorArchivos *lectorOcup;
    LectorArchivos *lectorVac;
    QString * nacionalidades;
    int topeNac;

   // QQueue<std::unique_ptr<Personaje>> personajes;
    QLabel* reglas;
    QLabel*nacionalidad;
    QLabel* fecha_de_nacimiento;
    QLabel* tipo_visita;
    QLabel* duracion;
    QLabel* estado_civil;
    QMouseEvent* mouseEvent;
    QMouseEvent* event;
    QVBoxLayout *layout;
private:
    QSet<QString> fallos_nivel1;
};

#endif // NIVEL1_H

