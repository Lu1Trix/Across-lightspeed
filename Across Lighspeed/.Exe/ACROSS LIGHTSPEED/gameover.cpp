#include "gameover.h"
#include "ui_gameover.h"

GameOver::GameOver(int X, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameOver)
{
    ui->setupUi(this);

    Scene = new QGraphicsScene(0,0,800,600);
    ui->graphicsView->setScene(Scene);
    setFixedSize(825,625);

    if(X == 0)
    {
        Scene->setBackgroundBrush(QPixmap(":/Selectores/Game_Over_con_fondo.png").scaled(800,600));
    }
    else if(X == 1)
    {
        Scene->setBackgroundBrush(QPixmap(":/Selectores/Time_over_con_estrellas.png").scaled(800,600));
    }
    else
    {
        Scene->setBackgroundBrush(QPixmap(":/Selectores/Trophy.jpg").scaled(800, 600));
    }

}

GameOver::~GameOver()
{
    delete ui;
}
