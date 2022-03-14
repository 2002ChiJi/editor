#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mybutton.h"

void MainWindow::AddTab(const QString& filePath,ViewImplement* widget)
{
    QTabWidget* tabs=ui->tabs;
    widget->ShowFile(filePath);

    tabs->insertTab(tabs->currentIndex(),widget,(filePath.split('/').last()));
    tabs->setCurrentIndex(tabs->currentIndex()-1);

    if(tabs->count()>1)
        tabWidgets.insert(tabs->currentIndex(),QSharedPointer<ViewImplement>(widget));
    else
        tabWidgets.append(QSharedPointer<ViewImplement>(widget));
}


bool MainWindow::IsOpenBefore(const QString &filePath)
{
    int index=OpenedFiles.indexOf(filePath);

    if(index!=-1)
        ui->tabs->setCurrentIndex(index);
    else
    {
        if(ui->tabs->count()>0)
            OpenedFiles.insert(ui->tabs->currentIndex(),filePath);
        else
            OpenedFiles.append(filePath);
    }
    return index==-1;
}

QString MainWindow::selectFile()
{
    QFile file;
    QString filePath;
    for(;;)
    {
        filePath=QFileDialog::getOpenFileName(this,"选择一个文件","","所有文件(*.*)");
        file.setFileName(filePath);
        if(file.open(QIODevice::ReadWrite)||filePath.isEmpty())
        {
            file.close();
            return filePath;
        }
        if(QMessageBox::warning(this,"文件选择失败","请重试，或选择其它文件       ",QMessageBox::Ok|QMessageBox::No,QMessageBox::No) ==QMessageBox::No)
            return QString();
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->panel->getSave(),&Mybutton::clicked,this,[&](){on_fileSave_clicked();ui->panel->getSave()->reset();});
    connect(ui->panel->getOpenfile(),&Mybutton::clicked,this,[&](){on_fileOpen_clicked();ui->panel->getOpenfile()->reset();});
    connect(ui->panel->getSaveAnother(),&Mybutton::clicked,this,[&](){on_fileSaveAnother_clicked();ui->panel->getSaveAnother()->reset();});

    connect(ui->panel->getLeft(),&Mybutton::clicked,this,[&](){tabWidgets[ui->tabs->currentIndex()]->setAlignment(Qt::AlignLeft);});
    connect(ui->panel->getRight(),&Mybutton::clicked,this,[&](){tabWidgets[ui->tabs->currentIndex()]->setAlignment(Qt::AlignRight);});
    connect(ui->panel->getMiddle(),&Mybutton::clicked,this,[&](){tabWidgets[ui->tabs->currentIndex()]->setAlignment(Qt::AlignHCenter);});
    connect(ui->panel->getFont(),&Mybutton::clicked,this,[&](){tabWidgets[ui->tabs->currentIndex()]->setFont();ui->panel->getFont()->reset();});
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_fileOpen_clicked()
{
    QString filePath=selectFile();
    if(!filePath.isEmpty())
    {
        if(IsOpenBefore(filePath))
        {
            if(filePath.endsWith(".csv",Qt::CaseInsensitive))
                AddTab(filePath,new CSVSheet);
            else if(filePath.endsWith(".txt",Qt::CaseInsensitive))
                AddTab(filePath,new TXTView);
            else
                AddTab(filePath,new AnyView);
        }
    }
}

void MainWindow::on_tabs_tabCloseRequested(int index)
{
    bool falg=true;
    auto choose=QMessageBox::warning(this,"提示","尚未保存，是否需要保存？       ",QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,QMessageBox::Cancel);

    if(choose==QMessageBox::Yes)
    {
        if(QMessageBox::warning(this,"提示","直接保存吗？不是的话我就另存为了       ",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes)==QMessageBox::Yes)
            falg=on_fileSave_clicked();
        else
            falg=on_fileSaveAnother_clicked();
    }

    if(falg&&choose!=QMessageBox::Cancel)
    {
        ui->tabs->removeTab(index);
        OpenedFiles.removeAt(index);
        tabWidgets.remove(index);
    }

}

bool MainWindow::on_fileSave_clicked(QString filePath)
{
    if(ui->tabs->count()==0)return false;

    QSharedPointer<ViewImplement> widget=tabWidgets[ui->tabs->currentIndex()];

    bool Success;
    if(!filePath.isEmpty())
        Success=widget->SaveFile(filePath);
    else
        Success=widget->SaveFile(OpenedFiles[ui->tabs->currentIndex()]);

    if(Success)
        QMessageBox::information(this,"提示","文件成功保存       ",QMessageBox::Ok);
    else
        QMessageBox::warning(this,"提示","文件保存失败，请重试，或选择另存为",QMessageBox::Ok);
    return Success;
}


bool MainWindow::on_fileSaveAnother_clicked()
{
    if(ui->tabs->count()==0)
        return false;

    QString filePath=selectFile();
    return on_fileSave_clicked(filePath);
}

void MainWindow::on_tabs_currentChanged(int index)
{
    ui->panel->setFileInfo(OpenedFiles[index]);
}

