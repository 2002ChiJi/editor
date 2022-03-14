#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QWidget>
#include <QLabel>
#include <QEvent>
#include <QObject>
#include <QEnterEvent>
#include <QPropertyAnimation>

namespace Ui {
class menuButton;
}

class menuButton : public QWidget
{
    Q_OBJECT
    int sizePx=-1;
    Ui::menuButton *ui;
    QColor before,solid,after;
    QPropertyAnimation intro,out;
public:
    void UnActive();

    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);

    void setText(const QString& text,int sizePx);
    void setColor(quint32 solid_,quint32 before_,quint32 after_);
    void setAll(quint32 solid,quint32 before,quint32 after,const QString& text,int sizePx_);

    explicit menuButton(QWidget *parent = nullptr);
    ~menuButton();

signals:
    void clicked(menuButton*);
};

#endif // MENUBUTTON_H
