#include <iostream>
#include <sstream>

#include <QtGui/QKeyEvent>
#include <QtGui/QFontDatabase>
#include <QtCore/QTimer>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QMessageBox>

#include <MyAst.h>

#include "MainWidget.h"

using namespace std;

class TextEditStreambuf: public streambuf {
public:
    TextEditStreambuf(QTextEdit* te) :
        m_buffer(1 << 12), m_te(te) {
        setp(m_buffer.data(), m_buffer.data() + m_buffer.size());
    }

    virtual ~TextEditStreambuf() {
    }

    virtual int sync() {
        for (auto& i : m_buffer) {
            if (i == '\n')
                i = ' ';
        }
        if (m_buffer.data()[0] == 0)
            return 0;
        m_te->append(QString::fromStdString(string(m_buffer.data())));
        for (auto& i : m_buffer)
            i = 0;
        setp(m_buffer.data(), m_buffer.data() + m_buffer.size());
        return 0;
    }

protected:
    vector<char> m_buffer;
    QTextEdit* m_te = nullptr;
};

MainWidget::MainWidget(QWidget* parent, Qt::WindowFlags f) :
    QWidget(parent, f) {
    setupUi(this);

    int id = QFontDatabase::addApplicationFont(":/fonts/DroidSansMono.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont monospace(family);

    codeTextEdit->setFont(monospace);
    consoleTextEdit->setFont(monospace);

    m_cout_buffer = new TextEditStreambuf(consoleTextEdit);
    m_cerr_buffer = new TextEditStreambuf(consoleTextEdit);

    m_cout_orig = cout.rdbuf();
    cout.rdbuf(m_cout_buffer);

    m_cerr_orig = cerr.rdbuf();
    cerr.rdbuf(m_cerr_buffer);

    connect(runPushButton, SIGNAL(clicked()), this, SLOT(run()));
}

MainWidget::~MainWidget() {
    cout.rdbuf(m_cout_orig);
    cout.rdbuf(m_cerr_orig);
    delete m_cout_buffer;
    delete m_cerr_buffer;
}

void MainWidget::keyPressEvent(QKeyEvent* e) {
    if (e->key() == Qt::Key_Escape) {
        close();
    }
}

void MainWidget::run() {
    stringstream ss;

    ss << codeTextEdit->toPlainText().toStdString();

    MyAst ast;
    ast.parse(ss, debugCheckBox->isChecked());
}
