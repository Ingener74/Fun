#pragma once

#include <memory>

#include <QtCore/QSettings>
#include <QtWidgets/QWidget>

#include "ui_mainwidget.h"

class LifeWidget;

class MainWidget: public QWidget, public Ui_MainWidget {
    Q_OBJECT
public:
    MainWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~MainWidget();

    virtual void keyPressEvent(QKeyEvent *);
    virtual void closeEvent(QCloseEvent *);

    Q_SLOT void run();

private:
    std::streambuf* m_cout_buffer = nullptr, * m_cerr_buffer = nullptr, *m_cout_orig = nullptr, *m_cerr_orig = nullptr;
    QSettings m_settings;
};
