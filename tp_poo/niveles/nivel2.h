#ifndef NIVEL2_H
#define NIVEL2_H
#include "nivel1.h"
#include <QWidget>
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
QT_BEGIN_NAMESPACE
namespace Ui {
class nivel2;
}
QT_END_NAMESPACE
class nivel2 : public nivel1
{
    Q_OBJECT

public:
    explicit nivel2(QWidget *parent = nullptr);
    ~nivel2();
    void setupDocumentos() ;
    void SetDoc ()  ;
   void setupDragAndDrop()  ;
    void GenerarPersonajes();
   bool eventFilter(QObject *obj, QEvent *event);
signals:

private:
    Ui::nivel2 *ui;
    QVBoxLayout *layout2;

protected:
public slots:

private slots:

};

#endif // NIVEL2_H
