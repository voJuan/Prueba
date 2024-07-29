#ifndef NIVEL2_H
#define NIVEL2_H

#include <QWidget>
#include "nivel1.h"

namespace Ui {
class nivel2;
}

class nivel2 : public nivel1
{
    Q_OBJECT

public:
    explicit nivel2(QWidget *parent = nullptr);
    ~nivel2();

private:
    Ui::nivel2 *ui;
};

#endif // NIVEL2_H
