#include "game.h"
#include "ui_game.h"
#include "random"

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

    escenario = new background(":/escenarios/BigBlueNoBackG.png");
    escenario->setCamera_x_pos(2411);
    escenario->setCamera_z_pos(3253);

    estrella.setPicture(QPixmap(":/sprites/Estrella.png"));


    Scene = new QGraphicsScene(0, 0, escenario->getScreen_size_x() - 2, escenario->getScreen_size_y() - 2);
    setFixedSize(escenario->getScreen_size_x() + 20, escenario->getScreen_size_y() + 20);
    ui->graphicsView->setScene(Scene);
    ui->graphicsView->setBackgroundBrush(escenario->actualizar());

    Scene->addItem(&estrella);
    estrella.show();

    m_timer=new QTimer();
    connect(m_timer,SIGNAL(timeout()),this,SLOT(main_movement()));
    m_timer->start(10);

    Speed = 0;

}

Game::~Game()
{
    delete ui;
    delete m_timer;
    delete Scene;
}

void Game::main_movement()
{

    if(movement_Left)
    {
        escenario->turn_Left();
    }
    if (movement_Right)
    {
        escenario->turn_Right();
    }
    if(movement_Up && Speed < 20)
    {
        Speed += 0.2;
    }
    else if(movement_Down && Speed > -10)
    {
        Speed -= 0.2;
    }
    else if (Speed != 0)
    {
        if (Speed > 0)
        {
             Speed -= 0.1;
        }
        else
        {
             Speed += 0.1;
        }
    }
    escenario->setCamera_movement_speed(Speed);
    escenario->Fowards();
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







