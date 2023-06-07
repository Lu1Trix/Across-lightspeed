#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include <background.h>
#include <windows.h>
#include <sprites.h>
#include <QProgressBar>
#include <QGraphicsProxyWidget>
#include <gameover.h>
#include <vector>


struct Checkpoint {
    int x;
    int y;
    int width;
    int height;
    int id;
};

QT_BEGIN_NAMESPACE
namespace Ui {class Game;}
QT_END_NAMESPACE

class Game : public QMainWindow
{
    Q_OBJECT

public:
    Game(int Nave, int Mundo, QWidget *parent = nullptr);
    ~Game();
    void GenerarCheckpoints();

public slots:
    void main_movement();
    void RecibirElementos();
    void AgregarNave(int Nave);
    void AgregarTimer();
    void ActualizarTemporizador();
    void AgregarVida();
    void VerificarCheckpoints();

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

    int MundoSeleccionado;
    int checkpointsCompletados;

    int TiempoRestante = 50;
    float Speed;

    QGraphicsScene *Scene;

    Sprites *character;

    GameOver *final;

    std::vector<Checkpoint> checkpoints;

    QProgressBar* BarraDeVida; QGraphicsProxyWidget* ProxyBarraDeVida;






};


#endif // GAME_H
