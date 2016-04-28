#include <iostream>

#include <QtGui/QKeyEvent>
#include <QtCore/QTimer>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

#include "MainWidget.h"

using namespace std;

MainWidget::MainWidget(QWidget* parent, Qt::WindowFlags f) :
    QWidget(parent, f) {
    setupUi(this);

}

MainWidget::~MainWidget() {
}

void MainWidget::keyPressEvent(QKeyEvent* e) {
    if (e->key() == Qt::Key_Escape) {
        close();
    }
}

