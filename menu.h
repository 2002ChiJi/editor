#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QFileInfo>
#include "mybutton.h"
namespace Ui {
class menu;
}

class menu : public QWidget
{
    Q_OBJECT
    quint32 color[7][2]/*橙，红，绿，紫，黄，蓝，灰蓝*/ /*dark,light*/{
        {0XD84A05,0XEF233C},{0XC3423F,0XFF686B},{0X354F52,0X1A936F},
        {0X69306D,0X7B1E7A},{0XE09F3E,0XECA400},{0X004E89,0X0582CA},
        {0X5670D7,0X73BEDE}};

public:
    explicit menu(QWidget *parent = nullptr);
    Mybutton* getOpenfile();
    ~menu();

    Mybutton *getSave();
    Mybutton *getFont();
    Mybutton *getLeft();
    Mybutton *getRight();
    Mybutton *getMiddle();
    Mybutton *getSaveAnother();

    void setFileInfo(QString& filePath);
private:
    Ui::menu *ui;
public slots:
    void setColor(int colorIndex);
};

#endif // MENU_H
