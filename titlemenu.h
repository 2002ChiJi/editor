#ifndef TITLEMENU_H
#define TITLEMENU_H

#include <QWidget>
#include "menuButton.h"

namespace Ui {
class titleMenu;
}

class titleMenu : public QWidget
{
    Q_OBJECT
    menuButton* widgets[3];
    menuButton* now=nullptr;
public:
    explicit titleMenu(QWidget *parent = nullptr);
    void setColor(quint32 light,quint32 dark,quint32 solid);
    ~titleMenu();

private:
    Ui::titleMenu *ui;

private slots:
    void Switch(menuButton* sender);
signals:
    void changed(int index);
};

#endif // TITLEMENU_H
