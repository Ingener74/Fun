#pragma once

#include <memory>

#include <QtCore/QSettings>
#include <QtWidgets/QWidget>

#include "ui_mainwidget.h"

class LifeWidget;
class TextEditStreambuf;
class OperandsController;

namespace fun{
class Visitor;
}

class MainWidget: public QWidget, public Ui_MainWidget {
Q_OBJECT
public:
    MainWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~MainWidget();

    void keyPressEvent(QKeyEvent *) override;
    void closeEvent(QCloseEvent *) override;

public slots:
    void newProgram();
    void loadProgram();
    void saveProgram();
    void runProgram();
    void visitorIndexChanged(int index);

    void readFileToCodeTextEdit();

private:
    TextEditStreambuf* _coutBuffer = nullptr, *_cerrBuffer = nullptr;
    std::streambuf *_coutOrig = nullptr, *_cerrOrig = nullptr;
    QSettings _settings;

    QString programFileName;

    std::unique_ptr<OperandsController> _operandsController;

    std::unique_ptr<fun::Visitor> _printer, _interpreter, _compiler;
    fun::Visitor* _visitor = nullptr;
};
