#include <iostream>
#include <sstream>

#include <QtCore/QTimer>
#include <QtCore/QTextStream>
#include <QtGui/QKeyEvent>
#include <QtGui/QFontDatabase>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QMessageBox>

#include "OperandsController.h"
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
    restoreGeometry(settings.value("window").toByteArray());
    mainSplitter->restoreState(settings.value("mainSplitter").toByteArray());
    codeConsoleSplitter->restoreState(settings.value("codeConsoleSplitter").toByteArray());
    variablesSplitter->restoreState(settings.value("variablesSplitter").toByteArray());
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

    QFontMetrics fm(monospace);
    codeTextEdit->setTabStopWidth(fm.width("    "));

    programFileName = settings.value("program", "").toString();
    readFileToCodeTextEdit();

    _coutBuffer = new TextEditStreambuf(consoleTextEdit);
    _cerrBuffer = new TextEditStreambuf(consoleTextEdit);

    _coutOrig = cout.rdbuf();
    cout.rdbuf(_coutBuffer);

    _cerrOrig = cerr.rdbuf();
    cerr.rdbuf(_cerrBuffer);

    connect(visitorComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(visitorIndexChanged(int)));

    connect(newPushButton, SIGNAL(clicked()), this, SLOT(newProgram()));
    connect(openPushButton, SIGNAL(clicked()), this, SLOT(loadProgram()));
    connect(savePushButton, SIGNAL(clicked()), this, SLOT(saveProgram()));
    connect(runPushButton, SIGNAL(clicked()), this, SLOT(runProgram()));

//    _operandsController.reset(new OperandsController(operandsStackTableWidget));
}

MainWidget::~MainWidget() {
}

void MainWidget::keyPressEvent(QKeyEvent* e) {
    if (e->key() == Qt::Key_Escape)
        close();
}

void MainWidget::closeEvent(QCloseEvent*) {
    cout.rdbuf(_coutOrig);
    cout.rdbuf(_cerrOrig);
    delete _coutBuffer;
    delete _cerrBuffer;

    QSettings settings("Venus.Games", "Dancing-Comic");
    settings.setValue("window", saveGeometry());
    settings.setValue("mainSplitter", mainSplitter->saveState());
    settings.setValue("codeConsoleSplitter", codeConsoleSplitter->saveState());
    settings.setValue("variablesSplitter", variablesSplitter->saveState());
    settings.setValue("visitor", visitorComboBox->currentIndex());
    if (!programFileName.isEmpty())
        settings.setValue("program", programFileName);
}

void MainWidget::newProgram() {
//    codeTextEdit->clear();
    int ret = QMessageBox::warning(this, tr("My Application"),
            tr("The document has been modified.\n"
                "Do you want to save your changes?"),
                QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                QMessageBox::Save);
}

void MainWidget::loadProgram() {
    programFileName = QFileDialog::getOpenFileName(this, "Open Fun program", "/home", tr("Fun Program (*.fun)"));
    readFileToCodeTextEdit();
}

void MainWidget::saveProgram() {
}

void MainWidget::runProgram() {
    _coutBuffer->clear();
    _cerrBuffer->clear();
    consoleTextEdit->setText("");

    if (_th.isRunning())
        _th.join();

    _th.startFunc([=] {
        try {
            stringstream ss;

            ss << codeTextEdit->toPlainText().toStdString();

            Lexer lexer(programFileName.toStdString(), &ss);
            fun::Pot ast;
            fun::Parser parser(lexer, &ast);
            parser.set_debug_level(debugCheckBox->isChecked());
            parser.parse();
            ast.accept(_visitor);
        } catch (const exception &e) {
            cerr << e.what() << endl;
        }
    });
}

void MainWidget::visitorIndexChanged(int index){
    _visitor =
            visitorComboBox->currentIndex() == 0 ? _interpreter.get() :
            visitorComboBox->currentIndex() == 1 ? _compiler.get() :
            visitorComboBox->currentIndex() == 2 ? _printer.get() : _printer.get();
}

void MainWidget::readFileToCodeTextEdit() {
    QFile file(programFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    codeTextEdit->clear();
    QTextStream ts(&file);
    QString line = ts.readLine();
    while (!line.isNull()) {
        codeTextEdit->append(line);
        line = ts.readLine();
    }
}
