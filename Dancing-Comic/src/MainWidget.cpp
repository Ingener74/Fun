#include <iostream>

#include <QtGui/QKeyEvent>
#include <QtGui/QFontDatabase>
#include <QtCore/QTimer>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

#include "MainWidget.h"

using namespace std;

MainWidget::MainWidget(QWidget* parent, Qt::WindowFlags f) :
    QWidget(parent, f) {
    setupUi(this);
	
	int id = QFontDatabase::addApplicationFont(":/fonts/DroidSansMono.ttf");
	QString family = QFontDatabase::applicationFontFamilies(id).at(0);
	QFont monospace(family);

	codeTextEdit->setFont(monospace);
	consoleTextEdit->setFont(monospace);
}

MainWidget::~MainWidget() {
}

void MainWidget::keyPressEvent(QKeyEvent* e) {
    if (e->key() == Qt::Key_Escape) {
        close();
    }
}

