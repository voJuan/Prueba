#ifndef PANTALLAJUEGO_H
#define PANTALLAJUEGO_H

#include <QWidget>
QT_BEGIN_NAMESPACE
namespace Ui {
class pantallajuego;
}
QT_END_NAMESPACE

class pantallajuego : public QWidget
{
    Q_OBJECT

public:
    explicit pantallajuego(QWidget *parent = nullptr);
    ~pantallajuego();
signals:

private:
    Ui::pantallajuego *ui;
protected:
private slots:


};

#endif // PANTALLAJUEGO_H
