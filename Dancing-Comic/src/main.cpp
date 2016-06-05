#include <QtWidgets/QMessageBox>

#include "MainWidget.h"

using namespace std;

int main(int argc, char* argv[]) {
    QApplication app { argc, argv };
    try {
        MainWidget mw;
        mw.show();
        return app.exec();
    } catch (const exception& e) {
        QMessageBox::critical(nullptr, "Error", e.what());
    }
}

