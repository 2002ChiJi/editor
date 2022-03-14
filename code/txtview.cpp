#include "txtview.h"
#include "ui_txtview.h"
#include <QFile>

TXTView::TXTView(QWidget *parent) :
    ViewImplement(parent),ui(new Ui::TXTView)
{
    ui->setupUi(this);
}

TXTView::~TXTView()
{
    delete ui;
}

void TXTView::setFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,this);
    if(ok)ui->text->setFont(font);
}

void TXTView::ShowFile(const QString &FilePath)
{
    QFile file(FilePath);
    file.open(QIODevice::ReadOnly);
    ui->text->setPlainText(file.readAll());
    file.close();
}

void TXTView::setAlignment(Qt::AlignmentFlag mode)
{
    ui->text->setAlignment(mode);
}

bool TXTView::SaveFile(const QString &FilePath)
{
    bool Success=false;
    QFile file(FilePath);

    if(file.open(QIODevice::WriteOnly))
    {
        file.write(ui->text->toPlainText().toStdString().data());
        Success=true;
    }

    file.close();
    return Success;
}
