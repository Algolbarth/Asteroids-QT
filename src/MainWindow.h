#ifndef CPP_QT_TPMINIPROJET_MAINWINDOW_H
#define CPP_QT_TPMINIPROJET_MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>

#include "MyScene.h"

class MainWindow : public QMainWindow
{
Q_OBJECT
private :
	MyScene *mainScene;
	QGraphicsView *mainView;
	QMenu *helpMenu;
public:
	explicit MainWindow(QWidget *parent = nullptr);

	~MainWindow() override = default;

public slots:

	void slot_aboutMenu();
};

class vue : public QGraphicsView
{
protected:
	void resizeEvent(QResizeEvent *event) override
	{
		this->fitInView(sceneRect());
	}
};

#endif
