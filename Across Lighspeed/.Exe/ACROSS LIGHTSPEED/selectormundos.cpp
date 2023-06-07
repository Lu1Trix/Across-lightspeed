#include "selectormundos.h"
#include "ui_selectormundos.h"

selectormundos::selectormundos(int NaveUsada, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::selectormundos)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0,0,800,600);
    Nave = NaveUsada;
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(QPixmap(":/Selectores/Selector_Mundo.png").scaled(800,600));
    setFixedSize(825,625);
}

selectormundos::~selectormundos()
{
    delete ui;
    delete scene;
}

void selectormundos::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_1)
    {
        close();
        Mundo = 1;
        PantallaGame = new Game(Nave, Mundo);
        PantallaGame->show();
    }
    if(ev->key()==Qt::Key_2)
    {
        close();
        Mundo = 2;
        PantallaGame = new Game(Nave, Mundo);
        PantallaGame->show();
    }
    if(ev->key()==Qt::Key_3)
    {
        close();
        Mundo = 3;
        PantallaGame = new Game(Nave, Mundo);
        PantallaGame->show();
    }
    if(ev->key()==Qt::Key_4)
    {
        close();
        Mundo = 4;
        PantallaGame = new Game(Nave, Mundo);
        PantallaGame->show();
    }
    if(ev->key()==Qt::Key_5)
    {
        close();
        Mundo = 5;
        PantallaGame = new Game(Nave, Mundo);
        PantallaGame->show();
    }
}

