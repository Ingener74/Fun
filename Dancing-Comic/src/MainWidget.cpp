#include <iostream>
#include <sstream>

#include <QtCore/QTimer>
#include <QtGui/QKeyEvent>
#include <QtGui/QFontDatabase>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QMessageBox>

#include "MainWidget.h"

#include <FunAst.h>
#include <AstVisitors/PrintVisitor.h>
#include <AstNodes/Scope.h>

using namespace std;
using namespace fun;

class TextEditStreambuf: public streambuf {
public:
    TextEditStreambuf(QTextEdit* te) :
        m_buffer(1 << 16), m_te(te) {
        setp(m_buffer.data(), m_buffer.data() + m_buffer.size());
    }

    virtual ~TextEditStreambuf() {
    }

    virtual int sync() {
        m_te->setPlainText(QString::fromStdString(string(m_buffer.data())));
        return 0;
    }

    vector<char> m_buffer;

protected:
    QTextEdit* m_te = nullptr;
};

MainWidget::MainWidget(QWidget* parent, Qt::WindowFlags f) :
    QWidget(parent, f) {
    setupUi(this);

    QSettings settings("Venus.Games", "Dancing-Comic");
    restoreGeometry(settings.value("geom").toByteArray());
    splitter->restoreState(settings.value("splitter").toByteArray());

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

void MainWidget::closeEvent(QCloseEvent*) {
    QSettings settings("Venus.Games", "Dancing-Comic");
    settings.setValue("geom", saveGeometry());
    settings.setValue("splitter", splitter->saveState());
}

void MainWidget::run() {
    stringstream ss;

    ss << codeTextEdit->toPlainText().toStdString();

    FunAst ast;
    PrintVisitor pv;
    ast.setResultVisitor(&pv);
    ast.parse(ss, debugCheckBox->isChecked());
}
