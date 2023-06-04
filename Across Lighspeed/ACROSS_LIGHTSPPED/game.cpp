#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing, false);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform, false);
    ui->graphicsView->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    escenario = new background(":/escenarios/F-ZeroMap06MuteCity2.jpg");

    Scene = new QGraphicsScene(0, 0, escenario->getScreen_size_x() - 2, escenario->getScreen_size_y() - 2);
    setFixedSize(escenario->getScreen_size_x() + 20, escenario->getScreen_size_y() + 20);
    ui->graphicsView->setScene(Scene);
    ui->graphicsView->setBackgroundBrush(escenario->actualizar());

    m_timer=new QTimer();
    connect(m_timer,SIGNAL(timeout()),this,SLOT(main_movement()));
    m_timer->start(3);

}

Game::~Game()
{
    delete ui;
    delete m_timer;
    delete Scene;
}

void Game::main_movement()
{
    if (movement_Up && movement_Right)
    {
        escenario->Fowards();
        escenario->turn_Right();
    }
    else if(movement_Up && movement_Left)
    {
        escenario->Fowards();
        escenario->turn_Left();
    }
    else if(movement_Left)
    {
        escenario->turn_Left();
        escenario->Fowards();
    }
    else if (movement_Right)
    {
        escenario->turn_Right();
        escenario->Fowards();
    }
    else if(movement_Up)
    {
        escenario->Fowards();
    }
    else if(movement_Down)
    {
        escenario->Backwards();
    }
    ui->graphicsView->setBackgroundBrush(escenario->actualizar());
}

void Game::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_A)
    {
        movement_Left=true;
    }
    else if(ev->key()==Qt::Key_D)
    {
        movement_Right=true;
    }
    else if(ev->key()==Qt::Key_W)
    {
        movement_Up=true;
    }
    else if(ev->key()==Qt::Key_S)
    {
        movement_Down=true;
    }
}

void Game::keyReleaseEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_A)
    {
        movement_Left=false;
    }
    else if(ev->key()==Qt::Key_D)
    {
        movement_Right=false;
    }
    else if(ev->key()==Qt::Key_W)
    {
        movement_Up=false;
    }
    else if(ev->key()==Qt::Key_S)
    {
        movement_Down=false;
    }
}

//float Game::Inercia(bool Momentun_status, float Speed)
//{
//    float NewSpeed;


//    if (Momentun_status)
//    {
//        NewSpeed = Speed + 0.3;
//    }
//    else
//    {
//        NewSpeed = Speed - 0.3;
//        if (NewSpeed < 0)
//        {
//            return 0;
//        }
//    }

//    if (Speed > 40)
//    {
//        return 40;
//    }

//    return NewSpeed;
//}






