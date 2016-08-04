#include <QtCore/QAbstractTableModel>
#include <QtWidgets/QTableWidget>

#include <fun.h>
#include "OperandsController.h"

class VariableTable: public QAbstractTableModel {
public:
    VariableTable() {
    }
    virtual ~VariableTable() {
    }

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const {
        return {};
    }
    virtual QModelIndex parent(const QModelIndex &child) const {
        return {};
    }
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const {
        return 2;
    }
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const {
        return 2;
    }
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const {
        return {};
    }
};

OperandsController::OperandsController(QTableWidget* table) :
        _tableWidget(table) {
    _tableModel = new VariableTable;
    _tableWidget->setModel(_tableModel);
}

OperandsController::~OperandsController() {
    delete _tableModel;
}

void OperandsController::setOperands(const std::vector<fun::Terminal*>&) {
}
