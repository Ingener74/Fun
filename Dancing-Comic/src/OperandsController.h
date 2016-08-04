#pragma once

class QTableWidget;
namespace fun {
class Terminal;
}
class VariableTable;

class OperandsController {
public:
    OperandsController(QTableWidget*);
    virtual ~OperandsController();

    void setOperands(const std::vector<fun::Terminal*>&);

private:
    VariableTable* _tableModel = nullptr;
    QTableWidget* _tableWidget = nullptr;;
};
