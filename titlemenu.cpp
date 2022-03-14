#include "titlemenu.h"
#include "ui_titlemenu.h"

titleMenu::titleMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::titleMenu)
{
    ui->setupUi(this);
    ui->ButtonFile->setAll(0XEC7505,0XD84A05,0XEC7505,"文件",20);
    ui->ButtonWord->setAll(0XEC7505,0XD84A05,0XEC7505,"格式",20);
    ui->ButtonInfo->setAll(0XEC7505,0XD84A05,0XEC7505,"信息",20);

    connect(ui->ButtonFile,&menuButton::clicked,this,&titleMenu::Switch);
    connect(ui->ButtonWord,&menuButton::clicked,this,&titleMenu::Switch);
    connect(ui->ButtonInfo,&menuButton::clicked,this,&titleMenu::Switch);

    widgets[0]=ui->ButtonFile,widgets[1]=ui->ButtonWord,widgets[2]=ui->ButtonInfo;
}

void titleMenu::setColor(quint32 light, quint32 dark, quint32 solid)
{
    ui->ButtonFile->setColor(solid,dark,light);
    ui->ButtonWord->setColor(solid,dark,light);
    ui->ButtonInfo->setColor(solid,dark,light);
}

titleMenu::~titleMenu()
{
    delete ui;
}

void titleMenu::Switch(menuButton* sender)
{
    if(now!=nullptr&&now!=sender)
        now->UnActive();
    now=sender;

    for(auto iter=std::begin(widgets);iter<std::end(widgets);iter++)
        if(sender==*iter)emit changed(iter-std::begin(widgets));
}
