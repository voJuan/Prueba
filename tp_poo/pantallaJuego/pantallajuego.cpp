#include "pantallajuego.h"
#include "ui_pantallajuego.h"

pantallajuego::pantallajuego(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pantallajuego)
{
    ui->setupUi(this);
}

pantallajuego::~pantallajuego()
{
    delete ui;
}
