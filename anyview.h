#ifndef ANYVIEW_H
#define ANYVIEW_H

#include <QWidget>
#include "ViewImplement.h"

namespace Ui {
class AnyView;
}

class AnyView : public ViewImplement
{
    Q_OBJECT

public:
    explicit AnyView(QWidget *parent = nullptr);
    ~AnyView();

    bool SaveFile(const QString&);
    void ShowFile(const QString& FilePath);
private:
    Ui::AnyView *ui;
};

#endif // ANYVIEW_H
