#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->mainScene = new MyScene;
    this->mainView = new vue;
    this->mainView->setScene(mainScene);
    this->setCentralWidget(mainView);
    this->setWindowTitle("Space War");
    this->resize(1200, 700);
    helpMenu = menuBar()->addMenu(tr("&Aide"));
    QAction* actionHelp = new QAction(tr("&Touches"), this);
    connect(actionHelp, SIGNAL(triggered()), this, SLOT(slot_aboutMenu()));
    helpMenu->addAction(actionHelp);
}

MainWindow::~MainWindow () {

}

void MainWindow::slot_aboutMenu () {
    QMessageBox msgBox;
    msgBox.setText("Bouger le vaisseau -> ZQSD \n Recommencer une partie -> R");
    msgBox.setModal(true);
    msgBox.exec();
}


