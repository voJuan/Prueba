#include "pantallainicioui.h"
#include "PantallaInicioUI/ui_pantallainicioui.h"

PantallaInicioUI::PantallaInicioUI(QWidget *parent)
    : QWidget{parent},
      ui(new Ui::PantallaInicioUI),
      sonidoFondo(new QSoundEffect(this))
{
    ui->setupUi(this);
    configurarSonidoFondo();
    sonidoFondo->play();
    //Linea 9: Conecta el boton SalirJuegoBoton con el slot de quit() para salir del programa.
    //Linea 10: conecta el boton IniciarJuegoBoton con el slot de iniciarJuegolicked() que cambiara a la pantalla donde se realizara el juego.
    connect(ui->SalirJuegoBoton, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(ui->iniciarJuegoBoton, &QPushButton::clicked, this, &PantallaInicioUI::iniciarJuegoClicked);
    connect(ui->cargar, &QPushButton::clicked, this, &PantallaInicioUI::cargarPartidaClicked);
}

PantallaInicioUI::~PantallaInicioUI()
{
    delete ui;
}

void PantallaInicioUI::configurarSonidoFondo()
{
    static QUrl url = QString("qrc:/sonidos/Recursos/Sonidos/backgroundInicioMusic.wav");
    sonidoFondo->setSource(url);
    sonidoFondo->setVolume(0.5);
    sonidoFondo->setLoopCount(QSoundEffect::Infinite);
}


