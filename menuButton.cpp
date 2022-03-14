#include "menuButton.h"
#include "ui_menuButton.h"

menuButton::menuButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menuButton)
{
    ui->setupUi(this);

    setMouseTracking(true);
    ui->solid->setAutoFillBackground(true);

    out.setTargetObject(ui->solid);
    out.setEasingCurve(QEasingCurve::OutQuint);
    out.setDuration(200),out.setPropertyName("geometry");

    intro.setTargetObject(ui->solid);
    intro.setEasingCurve(QEasingCurve::InCubic);
    intro.setDuration(200),intro.setPropertyName("geometry");
}

menuButton::~menuButton()
{
    delete ui;
}

void menuButton::showEvent(QShowEvent *event)
{
    intro.setStartValue(QRect(ui->text->x()+ui->text->size().width()/2,ui->solid->y(),0,ui->solid->size().height()));
    intro.setEndValue(QRect(ui->text->x(),ui->solid->y(),ui->text->size().width(),ui->solid->size().height()));

    out.setStartValue(QRect(ui->text->x(),ui->solid->y(),ui->text->size().width(),ui->solid->size().height()));
    out.setEndValue(QRect(ui->text->x()+ui->text->size().width()/2,ui->solid->y(),0,ui->solid->size().height()));

    out.start();
    ui->solid->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").
                             arg(solid.red()).arg(solid.green()).arg(solid.blue()));
    QWidget::showEvent(event);
}

void menuButton::resizeEvent(QResizeEvent *event)
{
    showEvent(nullptr);
    QWidget::resizeEvent(event);
}

void menuButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::MouseButton::LeftButton)
    {
        setText(ui->text->text(),sizePx*1.2);
        ui->text->setStyleSheet(QString("color: rgb(%1, %2, %3);").
                                arg(before.red()).arg(before.green()).arg(before.blue()));
        intro.start();
        emit clicked(this);
    }
}

void menuButton::UnActive()
{
    setText(ui->text->text(),sizePx);
    ui->text->setStyleSheet(QString("color: rgb(%1, %2, %3);").
                            arg(after.red()).arg(after.green()).arg(after.blue()));
    out.start();
}

void menuButton::setText(const QString &text,int sizePx)
{
    ui->text->setText(text);
    auto font=ui->text->font();
    font.setPixelSize(sizePx);
    ui->text->setFont(font);
}

void menuButton::setAll(quint32 solid,quint32 before,quint32 after, const QString &text, int sizePx_)
{
    sizePx=sizePx_;
    setColor(solid,before,after),setText(text,sizePx);
}

void menuButton::setColor(quint32 solid_,quint32 before_,quint32 after_)
{
    solid.setRgb(solid_),before.setRgb(before_),after.setRgb(after_);
    ui->text->setStyleSheet(QString("color: rgb(%1, %2, %3);").
                            arg(after.red()).arg(after.green()).arg(after.blue()));
    ui->solid->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").
                             arg(solid.red()).arg(solid.green()).arg(solid.blue()));
    out.start();
}
