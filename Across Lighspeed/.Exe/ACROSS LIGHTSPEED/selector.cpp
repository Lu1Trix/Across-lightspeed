#include "selector.h"
#include "ui_selector.h"

Selector::Selector(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Selector)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0,0,800,600);
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(QPixmap(":/Selectores/Selector_Naves.png").scaled(800,600));
    setFixedSize(825,625);

}

Selector::~Selector()
{
    delete ui;
    delete scene;
}


void Selector::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_1)
    {
        close();
        NaveSeleccionada = 1;
        PantallaGame = new selectormundos(NaveSeleccionada);
        PantallaGame->show();
    }
    if(ev->key()==Qt::Key_2)
    {
        close();
        NaveSeleccionada = 2;
        PantallaGame = new selectormundos(NaveSeleccionada);
        PantallaGame->show();
    }
    if(ev->key()==Qt::Key_3)
    {
        close();
        NaveSeleccionada = 3;
        PantallaGame = new selectormundos(NaveSeleccionada);
        PantallaGame->show();
    }
    if(ev->key()==Qt::Key_4)
    {
        close();
        NaveSeleccionada = 4;
        PantallaGame = new selectormundos(NaveSeleccionada);
        PantallaGame->show();

    }

}


