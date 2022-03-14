#ifndef VIEWIMPLEMENT_H
#define VIEWIMPLEMENT_H

#include <QFont>
#include <QWidget>
#include <QString>
#include <QFontDialog>

class ViewImplement:public QWidget
{
public:
    explicit  ViewImplement(QWidget *parent = nullptr):QWidget(parent){}

    virtual void setFont(){}
    virtual void ShowFile(const QString&){}
    virtual void setAlignment(Qt::AlignmentFlag){}
    virtual bool SaveFile(const QString&){return true;}
};

#endif // VIEWIMPLEMENT_H
