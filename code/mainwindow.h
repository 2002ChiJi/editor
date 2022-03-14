#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVector>
#include <QTabWidget>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QSharedPointer>
#include <QPlainTextEdit>

#include "CSVSheet.h"
#include "txtview.h"
#include "anyview.h"
#include "ViewImplement.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Ui::MainWindow *ui;
    QVector<QString> OpenedFiles;
    QVector<QSharedPointer<ViewImplement>> tabWidgets;

    QString selectFile();
    bool IsOpenBefore(const QString& filePath);
    void AddTab(const QString& filePath,ViewImplement* widget);

    void on_fileOpen_clicked();
    bool on_fileSaveAnother_clicked();
    bool on_fileSave_clicked(QString filePath=QString());

private slots:
    void on_tabs_tabCloseRequested(int index);
    void on_tabs_currentChanged(int index);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
