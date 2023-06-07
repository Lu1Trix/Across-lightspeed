
#include "inicio.h"
#include "ui_inicio.h"
#include "windows.h"
#include "QMainWindow"


inicio::inicio(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    const char* ImInicio = ":/naves/ImInicio.jpeg";
    Inicio = new Sprites(ImInicio, 560, 416);

    scene = new QGraphicsScene();

    scene->addItem(Inicio);
    Inicio->setPos(0,0);
    Inicio->changecurrentpixmap(0,0);
    Inicio->set_ampliar(2);

    ui->graphicsView->setScene(scene);

}

inicio::~inicio()
{
    delete ui;

}

void inicio::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_Return)
    {
        close();
        PantallaSelector = new Selector;
        PantallaSelector->show();
    }
    if(ev->key()==Qt::Key_T)
    {
        close();
        PantallaGame = new Game(1, 1);
        PantallaGame->show();
    }

}


