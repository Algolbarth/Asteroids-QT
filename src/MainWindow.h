#ifndef CPP_QT_TPMINIPROJET_MAINWINDOW_H
#define CPP_QT_TPMINIPROJET_MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>

#include "MyScene.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
private :
    MyScene* mainScene;
    QGraphicsView* mainView;
    QMenu* helpMenu;
public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();
public slots:
    void slot_aboutMenu();
};

class vue : public QGraphicsView {
    protected:
        virtual void resizeEvent (QResizeEvent* event) {
            this->fitInView(sceneRect());
        }
};

#endif
