#include "mybutton.h"
#include "ui_mybutton.h"

Mybutton::Mybutton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mybutton)
{
    ui->setupUi(this);

    setMouseTracking(true);
    ui->solid->setAutoFillBackground(true);

    out.setTargetObject(ui->solid);
    out.setEasingCurve(QEasingCurve::OutQuint);
    out.setDuration(200),out.setPropertyName("geometry");

    intro.setTargetObject(ui->solid);
    intro.setEasingCurve(QEasingCurve::OutQuint);
    intro.setDuration(200),intro.setPropertyName("geometry");

    fade.setTargetObject(ui->solid);
    fade.setDuration(200),fade.setPropertyName("color");

    QGridLayout *g_Layout = new QGridLayout(this);
    g_Layout->addWidget(ui->bg,0,0);
    g_Layout->addWidget(ui->solid,0,0);
    g_Layout->addWidget(ui->text,0,0);
    g_Layout->setContentsMargins(5,0,5,0);
    ui->solid->lower(),ui->bg->lower();
}

Mybutton::~Mybutton()
{
    delete ui;
}

void Mybutton::showEvent(QShowEvent *event)
{
    fade.setStartValue(text);
    fade.setEndValue(QColor(text.red()*0.9,text.green()*0.9,text.blue()*0.9));

    intro.setStartValue(QRect(ui->text->x(),ui->text->y(),0,ui->text->size().height()));
    intro.setEndValue(QRect(ui->text->x(),ui->text->y(),ui->text->size().width(),ui->text->size().height()));

    out.setStartValue(QRect(ui->text->x(),ui->text->y(),ui->text->size().width(),ui->text->size().height()));
    out.setEndValue(QRect(ui->text->x()+ui->text->size().width(),ui->text->y(),0,ui->text->size().height()));

    out.start();
    ui->solid->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").
                             arg(text.red()).arg(text.green()).arg(text.blue()));
    ui->bg->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").
                          arg(bg.red()).arg(bg.green()).arg(bg.blue()));

    QWidget::showEvent(event);
}

void Mybutton::resizeEvent(QResizeEvent *event)
{
    showEvent(nullptr);
    QWidget::resizeEvent(event);
}

void Mybutton::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::MouseButton::LeftButton)
    {
        fade.setDirection(QPropertyAnimation::Forward);
        fade.start();

        emit clicked();
    }
}

void Mybutton::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::MouseButton::LeftButton)
    {
        fade.setDirection(QPropertyAnimation::Backward);
        fade.start();
    }
}

void Mybutton::mySetText(const QString &text,int sizePx)
{
    ui->text->setText(text);
    auto font=ui->text->font();
    font.setPixelSize(sizePx);
    ui->text->setFont(font);
}

void Mybutton::setAll(quint32 bg_, quint32 text_, const QString &text, int sizePx)
{
    setColor(bg_,text_),mySetText(text,sizePx);
}

void Mybutton::reset()
{
    ui->solid->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").
                             arg(text.red()).arg(text.green()).arg(text.blue()));
    out.start();
}

void Mybutton::setColor(quint32 bg_,  quint32 text_)
{
    text.setRgb(text_),bg.setRgb(bg_);
    ui->text->setStyleSheet(QString("color:rgb(%1, %2, %3);"
                                    "border:0px solid;"
                                    "border-bottom :1px solid rgb(%1, %2, %3);").
                            arg(text.red()).arg(text.green()).arg(text.blue()));

}

void Mybutton::enterEvent(QEnterEvent *)
{
    ui->text->setStyleSheet(QString("color:rgb(%1, %2, %3);"
                                    "border:0px solid;"
                                    "border-bottom :1px solid rgb(%1, %2, %3);").
                            arg(bg.red()).arg(bg.green()).arg(bg.blue()));
    intro.start();
}


void Mybutton::leaveEvent(QEvent *)
{
    ui->text->setStyleSheet(QString("color:rgb(%1, %2, %3);"
                                    "border:0px solid;"
                                    "border-bottom :1px solid rgb(%1, %2, %3);").
                            arg(text.red()).arg(text.green()).arg(text.blue()));
    out.start();
}

Solid::Solid(QWidget *parent) :QLabel(parent){}

Solid::~Solid(){}
