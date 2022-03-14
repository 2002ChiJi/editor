#include "CSVSheet.h"
#include "ui_CSVSheet.h"
#include <QFile>

void CSVSheet::setFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,this);
    if(ok)
    {
        int heigh=dataModel->rowCount(),
                width=dataModel->columnCount();

        for(int y=0;y<heigh;y++)
            for(int x=0;x<width;x++)
                dataModel->item(y,x)->setFont(font);
    }
    ui->view->resizeRowsToContents();
    ui->view->resizeColumnsToContents();
    ui->view->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->view->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
}

void CSVSheet::setAlignment(Qt::AlignmentFlag mode)
{
    QModelIndexList selected=select->selectedIndexes();
    for (QModelIndex index:selected)
        dataModel->itemFromIndex(index)->setTextAlignment(mode);
}

void CSVSheet::ShowFile(const QString &filePath)
{
    QFile file(filePath);
    file.open(QIODevice::ReadOnly);

    for(;!file.atEnd();)
    {
        QString line(file.readLine());
        QStringList buffer(line.split(','));
        QList<QStandardItem*> row;
        for(auto& x:buffer)
            row<<new QStandardItem(x);

        dataModel->appendRow(row);
    }

    ui->view->resizeColumnsToContents();
    ui-> view->resizeRowsToContents();
    file.close();
}

bool CSVSheet::SaveFile(const QString &filePath)
{    
    bool Success=false;
    QFile file(filePath);

    if(file.open(QIODevice::WriteOnly))
    {
        QString content;
        int heigh=dataModel->rowCount(),width=dataModel->columnCount();
        for(int y=0;y<heigh;y++)
        {
            for(int x=0;x<width;x++,content+=',')
            {
                QStandardItem* item=dataModel->item(y,x);
                if(item!=nullptr)
                    content+=dataModel->item(y,x)->text();
            }
            *(content.end()-1)='\0';
            file.write(content.toStdString().data());
            content.clear();
        }
        Success=true;
    }

    file.close();
    return Success;
}

CSVSheet::CSVSheet(QWidget *parent) :
    ViewImplement(parent),ui(new Ui::CSVSheet)

{
    ui->setupUi(this);

    dataModel=new QStandardItemModel(this);
    select=new QItemSelectionModel(dataModel,this);

    ui->view->setModel(dataModel);
    ui->view->setSelectionModel(select);
}

CSVSheet::~CSVSheet()
{
    delete ui;
}
