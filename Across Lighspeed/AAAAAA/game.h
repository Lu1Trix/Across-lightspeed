#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include <background.h>
#include <QSound>
#include <windows.h>
#include <sprites.h>
#include <QProgressBar>
#include <QGraphicsProxyWidget>


QT_BEGIN_NAMESPACE
namespace Ui {class Game;}
QT_END_NAMESPACE

class Game : public QMainWindow
{
    Q_OBJECT

public:
    Game(int Nave, int Mundo, QWidget *parent = nullptr);
    ~Game();

public slots:
    void main_movement();
    void RecibirElementos();
    void AgregarNave(int Nave);
    void AgregarTimer();
    void ActualizarTemporizador();
    void AgregarVida();
private:
    Ui::Game *ui;
    QTimer* m_timer; QTimer* temporizador;
    background* escenario;

    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);

    bool movement_Up = false;
    bool movement_Down = false;
    bool movement_Left = false;
    bool movement_Right = false;
    bool increased_Spedd = false;

    int TiempoRestante = 180;
    float Speed;

    QSound* Musica;

    QGraphicsScene *Scene;

    Sprites *character;

    QProgressBar* BarraDeVida; QGraphicsProxyWidget* ProxyBarraDeVida;


};

#endif // GAME_H
