#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsView* w = ui->graphicsView;
    MazeScene* scene = new MazeScene(); // This is the model
    int height = scene->height();
    int width = scene->width();
    scene->setSceneRect(0, 0, width, height);
    w->setAlignment(Qt::AlignVCenter);
    w->setScene(scene);
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);
    connect(this, SIGNAL(keyPressedEvent(QKeyEvent*)), scene, SLOT(keyEvent(QKeyEvent*)));
    connect(this, SIGNAL(triggerSceneRestart(QEvent*)), scene, SLOT(restartEvent(QEvent*)));
}

MainWindow::~MainWindow()
{
    delete ui;
    //delete ui->graphicsView->scene();
}


void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}
const QSize baseSize(){
    return QSize(MAZE_SIZE*TILE_SIZE+200, MAZE_SIZE*TILE_SIZE+200);
}

void MainWindow::on_MainWindow_iconSizeChanged(const QSize &iconSize)
{

}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    emit(keyPressedEvent(event));
}

void MainWindow::keyReleaseEvent(QKeyEvent* event) {

}


void MainWindow::on_actionRestart_triggered()
{
    QEvent* e = new QEvent(QEvent::ApplicationStateChange);
    emit(triggerSceneRestart(e));
}
