#ifndef TXTVIEW_H
#define TXTVIEW_H

#include <QWidget>
#include "ViewImplement.h"

namespace Ui {
class TXTView;
}

class TXTView : public ViewImplement
{
    Q_OBJECT

public:
    explicit TXTView(QWidget *parent = nullptr);
    ~TXTView();

    void setFont();
    bool SaveFile(const QString& FilePath);
    void ShowFile(const QString& FilePath);
    virtual void setAlignment(Qt::AlignmentFlag mode);
private:
    Ui::TXTView *ui;
};

#endif // TXTVIEW_H
