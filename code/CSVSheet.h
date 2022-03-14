#ifndef CSVSHEET_H
#define CSVSHEET_H

#include <QWidget>
#include <QTableView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QItemSelectionModel>

#include "ViewImplement.h"

namespace Ui {
class CSVSheet;
}

class CSVSheet : public ViewImplement
{
    Q_OBJECT
private:
    Ui::CSVSheet *ui;
    QItemSelectionModel* select;
    QStandardItemModel* dataModel;
public:
    void setFont();
    void setAlignment(Qt::AlignmentFlag);
    void ShowFile(const QString& filePath);
    bool SaveFile(const QString& filePath);
    explicit CSVSheet(QWidget *parent = nullptr);
    ~CSVSheet();
};

#endif // CSVSHEET_H
