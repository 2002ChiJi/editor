#include "menu.h"
#include "ui_menu.h"
#include <QStackedWidget>
#include <QComboBox>
#include <QToolTip>
#include "titlemenu.h"

menu::menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
    ui->font->setAll(0XEC7505,0xFFFFFF,"字体",15);
    ui->left->setAll(0XEC7505,0xFFFFFF,"左对齐",15);
    ui->middle->setAll(0XEC7505,0xFFFFFF,"居中",15);
    ui->right->setAll(0XEC7505,0xFFFFFF,"右对齐",15);
    ui->save->setAll(0XEC7505,0xFFFFFF,"立即保存",15);
    ui->openfile->setAll(0XEC7505,0xFFFFFF,"打开文件",15);
    ui->saveAnohter->setAll(0XEC7505,0xFFFFFF,"另存为",15);

    connect(ui->themeSelecter,&QComboBox::currentIndexChanged,this,&menu::setColor);
    connect(ui->topButton,&titleMenu::changed,ui->stackedWidget,&QStackedWidget::setCurrentIndex);
    ui->themeSelecter->setCurrentIndex(0);

    connect(ui->info, &QTableWidget::itemEntered, this, [&](QTableWidgetItem *item){
        if (item != nullptr)QToolTip::showText(QCursor::pos(), item->text());});
}

Mybutton *menu::getFont(){return ui->font;}
Mybutton *menu::getLeft(){return ui->left;}
Mybutton *menu::getMiddle(){return ui->middle;}
Mybutton *menu::getRight(){return ui->right;}
Mybutton *menu::getSave(){return ui->save;}
Mybutton *menu::getOpenfile(){return ui->openfile;}
Mybutton *menu::getSaveAnother(){return ui->saveAnohter;}

void menu::setFileInfo(QString &filePath)
{
    QFileInfo info(filePath);
    ui->info->item(0,1)->setText(QString::number(info.size()/1024.0)+"KB");
    ui->info->item(1,1)->setText(info.absolutePath());
    ui->info->item(2,1)->setText(info.birthTime().toString("yyyy/MM/dd hh:mm:ss"));
    ui->info->item(3,1)->setText(info.lastModified().toString("yyyy/MM/dd hh:mm:ss"));

    ui->info->resizeRowsToContents();
    ui->info->resizeColumnsToContents();
    ui->info->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->info->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
}

void menu::setColor(int colorIndex)
{
    ui->save->setColor(color[colorIndex][1],0xFFFFFF);
    ui->font->setColor(color[colorIndex][1],0xFFFFFF);
    ui->left->setColor(color[colorIndex][1],0xFFFFFF);
    ui->right->setColor(color[colorIndex][1],0xFFFFFF);
    ui->middle->setColor(color[colorIndex][1],0xFFFFFF);
    ui->openfile->setColor(color[colorIndex][1],0xFFFFFF);
    ui->saveAnohter->setColor(color[colorIndex][1],0xFFFFFF);
    ui->topButton->setColor(color[colorIndex][0],color[colorIndex][1],color[colorIndex][0]);
}

menu::~menu()
{
    delete ui;
}
