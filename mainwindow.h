#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

    QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_matrielButton_clicked();
    void on_sponsorButton_clicked();
    void on_eventButton_clicked();
    void on_employeButton_clicked();
    void on_participantButton_clicked();
    void on_logoutButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
