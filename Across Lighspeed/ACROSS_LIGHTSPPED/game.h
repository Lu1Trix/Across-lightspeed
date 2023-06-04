#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>

#include <background.h>
#include <character.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Game; }
QT_END_NAMESPACE

class Game : public QMainWindow
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();

public slots:
    void main_movement();

private:
    Ui::Game *ui;
    QTimer* m_timer;
    background* escenario;

    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);

    bool movement_Up = false;
    bool movement_Down = false;
    bool movement_Left = false;
    bool movement_Right = false;
    bool increased_Spedd = false;

    QGraphicsScene *Scene;

//public:
//    float Inercia(bool Momentun_status, float Speed);

};

#endif // GAME_H
