#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkInterface>
#include <QNetworkAddressEntry>
#include <QDebug>
#include <QComboBox>
#include <QtGlobal>
#include <QProcess>
#include <QMessageBox>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ScanPushButton_clicked();

    void on_ChangePushButton_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkInterface myNetWorkInterface;
    QList<QNetworkInterface> g_NetWorkInterfaces;
    void comboboxIndexChangeSlot(int m_dSelectNum);
    QProcess process;
};

#endif // MAINWINDOW_H
