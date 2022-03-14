#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <QLabel>
#include <QEvent>
#include <QObject>
#include <QPalette>
#include <QEnterEvent>
#include <QGridLayout>
#include <QPropertyAnimation>

namespace Ui {
class Mybutton;
}

class Solid: public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
public:
    QColor color()
    {
        return Qt::black;
    }
    void setColor (QColor color)
    {
        setStyleSheet(QString("background-color: rgb(%1, %2, %3);").
                      arg(color.red()).arg(color.green()).arg(color.blue()));
    }
    explicit Solid(QWidget *parent = nullptr);
    ~Solid();
};

class Mybutton : public QWidget
{
    Q_OBJECT
    QString style;
    QColor text,bg;
    Ui::Mybutton *ui;
    QPropertyAnimation intro,out,fade;
public:
    void leaveEvent(QEvent *);
    void enterEvent(QEnterEvent *);
    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void setColor(quint32 bg_,quint32 text_);
    void mySetText(const QString& text,int sizePx);
    void setAll(quint32 bg_,quint32 text_,const QString& text,int sizePx);
    void reset();

    explicit Mybutton(QWidget *parent = nullptr);
    ~Mybutton();

signals:
    void clicked();
};

#endif // MYBUTTON_H
