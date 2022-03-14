#include "anyview.h"
#include "ui_anyview.h"

#include <QFile>
#include <QMessageBox>

AnyView::AnyView(QWidget *parent) :
    ViewImplement(parent),ui(new Ui::AnyView)
{
    ui->setupUi(this);
    ui->text->setReadOnly(true);
}

AnyView::~AnyView()
{
    delete ui;
}

void AnyView::ShowFile(const QString &FilePath)
{
    QFile file(FilePath);
    file.open(QIODevice::ReadOnly);
    ui->text->setPlainText(file.readAll());
    file.close();
}

bool AnyView::SaveFile(const QString &)
{
    QMessageBox::warning(this,"","只读模式，不可保存       ",QMessageBox::Ok);
    return false;
}
