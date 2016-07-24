#include <iostream>
#include <sstream>

#include <QtCore/QTimer>
#include <QtGui/QKeyEvent>
#include <QtGui/QFontDatabase>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QMessageBox>

#include "MainWidget.h"

#include <fun.h>

using namespace std;

class TextEditStreambuf: public streambuf {
public:
    TextEditStreambuf(QTextEdit* te) :
            m_buffer(1 << 16), m_te(te) {
        setp(m_buffer.data(), m_buffer.data() + m_buffer.size());
    }

    virtual ~TextEditStreambuf() {
    }

    int sync() override
    {
        m_te->setPlainText(QString::fromStdString(string(m_buffer.data())));
        return 0;
    }

    void clear() {
        for (auto& i : m_buffer)
            i = 0;
        setp(m_buffer.data(), m_buffer.data() + m_buffer.size());
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

    m_printer.reset(new fun::Printer);
    m_interpreter.reset(new fun::Interpreter);
    m_compiler.reset(new fun::Compiler);

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
    try {
        m_cout_buffer->clear();
        m_cerr_buffer->clear();
        consoleTextEdit->setText("");

        stringstream ss;

        ss << codeTextEdit->toPlainText().toStdString();

        FunLexer lexer(&ss);
        fun::FunParser parser(lexer);
        parser.set_debug_level(debugCheckBox->isChecked());
        parser.parse();
        m_interpreter->iterateStatements(fun::Statement::entryPoint);
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
}
