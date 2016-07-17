#pragma once

#include <memory>

#include <QtCore/QSettings>
#include <QtWidgets/QWidget>

#include "ui_mainwidget.h"

class LifeWidget;
class TextEditStreambuf;

class MainWidget: public QWidget, public Ui_MainWidget {
Q_OBJECT
public:
    MainWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~MainWidget();

    void keyPressEvent(QKeyEvent *) override;
    void closeEvent(QCloseEvent *) override;

    Q_SLOT
    void run();

private:
    TextEditStreambuf* m_cout_buffer = nullptr, *m_cerr_buffer = nullptr;
    std::streambuf *m_cout_orig = nullptr, *m_cerr_orig = nullptr;
    QSettings m_settings;
};
