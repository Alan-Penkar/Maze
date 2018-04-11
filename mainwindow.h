#pragma once

#include <QMainWindow>
#include <QDebug>
#include <QApplication>
#include "scene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

Q_SIGNALS:
    void keyPressedEvent(QKeyEvent* event);
    void triggerSceneRestart(QEvent*);

private slots:
    void on_actionQuit_triggered();
    void on_MainWindow_iconSizeChanged(const QSize &iconSize);
    void on_actionRestart_triggered();

private:
    Ui::MainWindow *ui;
    MazeScene* scene;
public slots:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

};
