#ifndef PANTALLAINICIOUI_H
#define PANTALLAINICIOUI_H

#include <QWidget>
QT_BEGIN_NAMESPACE
namespace Ui {
class PantallaInicioUI;
}
QT_END_NAMESPACE

class PantallaInicioUI : public QWidget
{
    Q_OBJECT
public:
    explicit PantallaInicioUI(QWidget *parent = nullptr);
    ~PantallaInicioUI();
signals:

private:
    Ui::PantallaInicioUI *ui;
protected:
private slots:

};

#endif // PANTALLAINICIOUI_H
