#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ui_mainwindow.h>
#include <QDebug>
#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnOnline_clicked(bool checked);
    void on_btnOUT00_clicked(bool checked);
    void on_btnOUT01_clicked(bool checked);
    void on_btnOUT02_clicked(bool checked);
    void on_btnOUT03_clicked(bool checked);
    void on_btnOUT04_clicked(bool checked);
    void on_btnOUT05_clicked(bool checked);
    void on_btnOUT06_clicked(bool checked);
    void on_btnOUT07_clicked(bool checked);
    void on_btnOUT08_clicked(bool checked);
    void on_btnOUT09_clicked(bool checked);
    void on_btnOUT10_clicked(bool checked);
    void on_btnOUT11_clicked(bool checked);
    void on_btnOUT12_clicked(bool checked);
    void on_btnOUT13_clicked(bool checked);
    void on_btnOUT14_clicked(bool checked);
    void on_btnOUT15_clicked(bool checked);
    void on_btnOUT16_clicked(bool checked);
    void on_btnOUT17_clicked(bool checked);
    void on_btnOUT18_clicked(bool checked);
    void on_btnOUT19_clicked(bool checked);
    void on_btnOUT20_clicked(bool checked);
    void on_btnOUT21_clicked(bool checked);
    void on_btnOUT22_clicked(bool checked);
    void on_btnOUT23_clicked(bool checked);
    void on_btnOUT24_clicked(bool checked);
    void on_btnOUT25_clicked(bool checked);
    void on_btnOUT26_clicked(bool checked);
    void on_btnOUT27_clicked(bool checked);
    void on_btnOUT28_clicked(bool checked);
    void on_btnOUT29_clicked(bool checked);
    void on_btnOUT30_clicked(bool checked);
    void on_btnOUT31_clicked(bool checked);

    void onSerialReceive();


private:
    Ui::MainWindow  *ui;
    QSerialPort     *m_SerialPort;
    QByteArray      m_SendBuf;
    QByteArray      m_RecvBuf;
    uint32_t        m_OutputBits;
    uint32_t        m_CycleCount;

    void            SetupUSBport();
    void            ToggleOutButton(QPushButton *button, bool checked);
    uint32_t        GetDregValue(QByteArray str);
    void            UpdateRemoteInput(uint32_t data);
    void            ToggleInputLabel(QLabel *label, bool fg);
    QByteArray      MakeDregWriteString();
    QByteArray      MakeDregReadString();
    QByteArray      MakeCheckSum(QByteArray str);
    void            SerialPortSend(QByteArray send);
};
#endif // MAINWINDOW_H
