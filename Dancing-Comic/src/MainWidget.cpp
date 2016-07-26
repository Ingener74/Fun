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
            buffer(1 << 16), _te(te) {
        setp(buffer.data(), buffer.data() + buffer.size());
    }

    virtual ~TextEditStreambuf() {
    }

    int sync() override {
        _te->setPlainText(QString::fromStdString(string(buffer.data())));
        return 0;
    }

    void clear() {
        for (auto& i : buffer)
            i = 0;
        setp(buffer.data(), buffer.data() + buffer.size());
    }

    vector<char> buffer;

protected:
    QTextEdit* _te = nullptr;
};

MainWidget::MainWidget(QWidget* parent, Qt::WindowFlags f) :
        QWidget(parent, f) {
    setupUi(this);

    QSettings settings("Venus.Games", "Dancing-Comic");
    restoreGeometry(settings.value("geom").toByteArray());
    splitter->restoreState(settings.value("splitter").toByteArray());
    visitorComboBox->setCurrentIndex(settings.value("visitor").toInt());

    int id = QFontDatabase::addApplicationFont(":/fonts/DroidSansMono.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont monospace(family);

    _printer.reset(new fun::Printer);
    _interpreter.reset(new fun::Interpreter);
    _compiler.reset(new fun::Compiler);

    visitorIndexChanged(0);

    codeTextEdit->setFont(monospace);
    consoleTextEdit->setFont(monospace);

    _coutBuffer = new TextEditStreambuf(consoleTextEdit);
    _cerrBuffer = new TextEditStreambuf(consoleTextEdit);

    _coutOrig = cout.rdbuf();
    cout.rdbuf(_coutBuffer);

    _cerrOrig = cerr.rdbuf();
    cerr.rdbuf(_cerrBuffer);

    connect(visitorComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(visitorIndexChanged(int)));

    connect(runPushButton, SIGNAL(clicked()), this, SLOT(run()));
}

MainWidget::~MainWidget() {
    cout.rdbuf(_coutOrig);
    cout.rdbuf(_cerrOrig);
    delete _coutBuffer;
    delete _cerrBuffer;
}

void MainWidget::keyPressEvent(QKeyEvent* e) {
    if (e->key() == Qt::Key_Escape)
        close();
}

void MainWidget::closeEvent(QCloseEvent*) {
    QSettings settings("Venus.Games", "Dancing-Comic");
    settings.setValue("geom", saveGeometry());
    settings.setValue("splitter", splitter->saveState());
    settings.setValue("visitor", visitorComboBox->currentIndex());
}

void MainWidget::run() {
    try {
        _coutBuffer->clear();
        _cerrBuffer->clear();
        consoleTextEdit->setText("");

        stringstream ss;

        ss << codeTextEdit->toPlainText().toStdString();

        FunLexer lexer(&ss);
        fun::FunParser parser(lexer);
        parser.set_debug_level(debugCheckBox->isChecked());
        parser.parse();
        _visitor->iterateStatements(fun::Statement::entryPoint);
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

void MainWidget::visitorIndexChanged(int index){
    _visitor =
            visitorComboBox->currentIndex() == 0 ? _interpreter.get() :
            visitorComboBox->currentIndex() == 1 ? _compiler.get() :
            visitorComboBox->currentIndex() == 2 ? _printer.get() : _printer.get();
}
