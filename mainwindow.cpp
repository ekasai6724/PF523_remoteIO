#include "mainwindow.h"
#include "ui_mainwindow.h"

/***************************************************************************
 *  コンストラクタ
 ***************************************************************************/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    bool port_ok = false;

    ui->setupUi(this);

    m_OutputBits = 0x00000000;
    m_CycleCount = 0;
    m_SendBuf.clear();

    // PF523のハードチェックプログラムモードを利用しているので
    // 起動直後はチェックモード専用のUSBポートとして認識される
    // 接続すると基板側で自動的に通常動作用のUSBポートが改めて開かれるので再接続する
    m_SerialPort = new QSerialPort(this);
    m_SerialPort->setPortName("NULL");
    SetupUSBport();
    if(m_SerialPort->open(QIODevice::ReadWrite))
    {
        m_SerialPort->close();
        QThread::msleep(1000);

        // 通常動作モードのUSBポートに再接続する
        SetupUSBport();
        if(m_SerialPort->open(QIODevice::ReadWrite))
        {
            connect(m_SerialPort, &QSerialPort::readyRead, this, &MainWindow::onSerialReceive);
            m_SendBuf = MakeDregWriteString();
            on_btnOnline_clicked(true);
            port_ok = true;
        }
    }

    if(port_ok == true)     qDebug().noquote() << "Serial port open.";
    else                    qDebug().noquote() << "Counldn't open the port.";
}

/*=========================================================================
 *  USBシリアルポート検索して接続準備
 *========================================================================*/
void MainWindow::SetupUSBport(void)
{
    foreach(const QSerialPortInfo info, QSerialPortInfo::availablePorts())
    {
        if(info.portName().left(6) == "ttyACM")
        {
            qDebug().noquote() << "Name        :" << info.portName();
            qDebug().noquote() << "Description :" << info.description();
            qDebug().noquote() << "Manufacturer:" << info.manufacturer() << "\n";

            m_SerialPort->setPortName(info.portName());
            m_SerialPort->setBaudRate(QSerialPort::Baud9600);
            m_SerialPort->setDataBits(QSerialPort::Data8);
            m_SerialPort->setParity(QSerialPort::EvenParity);
            m_SerialPort->setStopBits(QSerialPort::OneStop);
            break;
        }
    }
}

/***************************************************************************
 *  デストラクタ
 ***************************************************************************/
MainWindow::~MainWindow()
{
    // 受信中にポートをcloseするとアプリケーションが正常に終了しない
    // (ポートのハンドラが開放されない？)
    // のでオフライン状態にして少し待機してから終了する
    on_btnOnline_clicked(false);
    QThread::msleep(1000);

    if(m_SerialPort->isOpen())  m_SerialPort->close();
    delete m_SerialPort;

    delete ui;
}

/***************************************************************************
 *  オンライン/オフライン切替ボタンクリックSlot
 ***************************************************************************/
void MainWindow::on_btnOnline_clicked(bool checked)
{
    // ボタンクリックされてSLOTとしてここに来た場合はここでCheckedに触る必要はないが、
    // 実行中の制御でここに来る場合のために改めてCheckedを設定しておく
    ui->btnOnline->setChecked(checked);

    if(checked)
    {
        ui->btnOnline->setText("ONLINE");
        ui->btnOnline->setStyleSheet("background-color:lime");

        if(m_SendBuf != "")
        {
            SerialPortSend(m_SendBuf);
            m_SendBuf.clear();
        }
    }
    else
    {
        ui->btnOnline->setText("OFFLINE");
        ui->btnOnline->setStyleSheet("background-color:#efefef");
    }
}

/***************************************************************************
 *  リモートOutput個別ボタンクリックSlot
 ***************************************************************************/
void MainWindow::on_btnOUT00_clicked(bool checked){ ToggleOutButton(ui->btnOUT00, checked);}
void MainWindow::on_btnOUT01_clicked(bool checked){ ToggleOutButton(ui->btnOUT01, checked);}
void MainWindow::on_btnOUT02_clicked(bool checked){ ToggleOutButton(ui->btnOUT02, checked);}
void MainWindow::on_btnOUT03_clicked(bool checked){ ToggleOutButton(ui->btnOUT03, checked);}
void MainWindow::on_btnOUT04_clicked(bool checked){ ToggleOutButton(ui->btnOUT04, checked);}
void MainWindow::on_btnOUT05_clicked(bool checked){ ToggleOutButton(ui->btnOUT05, checked);}
void MainWindow::on_btnOUT06_clicked(bool checked){ ToggleOutButton(ui->btnOUT06, checked);}
void MainWindow::on_btnOUT07_clicked(bool checked){ ToggleOutButton(ui->btnOUT07, checked);}
void MainWindow::on_btnOUT08_clicked(bool checked){ ToggleOutButton(ui->btnOUT08, checked);}
void MainWindow::on_btnOUT09_clicked(bool checked){ ToggleOutButton(ui->btnOUT09, checked);}
void MainWindow::on_btnOUT10_clicked(bool checked){ ToggleOutButton(ui->btnOUT10, checked);}
void MainWindow::on_btnOUT11_clicked(bool checked){ ToggleOutButton(ui->btnOUT11, checked);}
void MainWindow::on_btnOUT12_clicked(bool checked){ ToggleOutButton(ui->btnOUT12, checked);}
void MainWindow::on_btnOUT13_clicked(bool checked){ ToggleOutButton(ui->btnOUT13, checked);}
void MainWindow::on_btnOUT14_clicked(bool checked){ ToggleOutButton(ui->btnOUT14, checked);}
void MainWindow::on_btnOUT15_clicked(bool checked){ ToggleOutButton(ui->btnOUT15, checked);}
void MainWindow::on_btnOUT16_clicked(bool checked){ ToggleOutButton(ui->btnOUT16, checked);}
void MainWindow::on_btnOUT17_clicked(bool checked){ ToggleOutButton(ui->btnOUT17, checked);}
void MainWindow::on_btnOUT18_clicked(bool checked){ ToggleOutButton(ui->btnOUT18, checked);}
void MainWindow::on_btnOUT19_clicked(bool checked){ ToggleOutButton(ui->btnOUT19, checked);}
void MainWindow::on_btnOUT20_clicked(bool checked){ ToggleOutButton(ui->btnOUT20, checked);}
void MainWindow::on_btnOUT21_clicked(bool checked){ ToggleOutButton(ui->btnOUT21, checked);}
void MainWindow::on_btnOUT22_clicked(bool checked){ ToggleOutButton(ui->btnOUT22, checked);}
void MainWindow::on_btnOUT23_clicked(bool checked){ ToggleOutButton(ui->btnOUT23, checked);}
void MainWindow::on_btnOUT24_clicked(bool checked){ ToggleOutButton(ui->btnOUT24, checked);}
void MainWindow::on_btnOUT25_clicked(bool checked){ ToggleOutButton(ui->btnOUT25, checked);}
void MainWindow::on_btnOUT26_clicked(bool checked){ ToggleOutButton(ui->btnOUT26, checked);}
void MainWindow::on_btnOUT27_clicked(bool checked){ ToggleOutButton(ui->btnOUT27, checked);}
void MainWindow::on_btnOUT28_clicked(bool checked){ ToggleOutButton(ui->btnOUT28, checked);}
void MainWindow::on_btnOUT29_clicked(bool checked){ ToggleOutButton(ui->btnOUT29, checked);}
void MainWindow::on_btnOUT30_clicked(bool checked){ ToggleOutButton(ui->btnOUT30, checked);}
void MainWindow::on_btnOUT31_clicked(bool checked){ ToggleOutButton(ui->btnOUT31, checked);}

/***************************************************************************
 *  USBシリアル受信Slot
 ***************************************************************************/
void MainWindow::onSerialReceive()
{
    QByteArray recv = m_SerialPort->readAll();
    //qDebug().noquote() << "Serial Receive:" << recv;

    if(!recv.isEmpty())
    {
        m_RecvBuf.append(recv);
        if((recv.indexOf(0x03) != -1) || (recv.indexOf(0x04) != -1))
        {
            m_CycleCount++;
            ui->lblCycleCount->setText(QString::number(m_CycleCount));

            // Dレジスタ読出コマンドの返信を受信
            if(m_RecvBuf.mid(1, 2) == "50")
            {
                uint32_t bf = GetDregValue(m_RecvBuf.mid(3, 8));
                                                        // リモートInput状態取得
                UpdateRemoteInput(bf);                  // リモートInput状態表示
                m_SendBuf = MakeDregWriteString();      // リモートOutput書込送信
                //qDebug().noquote() << "Remote Input:" << QString::number(bf, 16).rightJustified(8, '0');
            }
            // Dレジスタ書込コマンドの返信を受信
            else
            {
                m_SendBuf = MakeDregReadString();       // リモートInput状態読出送信
            }
            m_RecvBuf.clear();

            // オンライン状態であれば次のコマンド送信
            if(ui->btnOnline->isChecked())
            {
                SerialPortSend(m_SendBuf);
                m_SendBuf.clear();
            }
        }
    }
}

/*=========================================================================
 *  リモートOutputデータとボタン表示更新
 *========================================================================*/
void MainWindow::ToggleOutButton(QPushButton *button, bool checked)
{
    uint32_t    bit = 0x00000001 << button->objectName().right(2).toInt();

    if(checked)
    {
        m_OutputBits |= bit;
        button->setText("ON");
        button->setStyleSheet("background-color:lime");
    }
    else
    {
        m_OutputBits &= ~bit;
        button->setText("OFF");
        button->setStyleSheet("background-color:#efefef");
    }

    //qDebug().noquote() << "m_OutputBits:" << QString::number(m_OutputBits, 16).rightJustified(8, '0');
}

/*=========================================================================
 *  Dレジスタ読出コマンドで受信したデータ文字列を数値に変換
 *========================================================================*/
uint32_t MainWindow::GetDregValue(QByteArray str)
{
    if(str.length() < 2)    return 0;

    QByteArray sbf;
    while(str.length() >= 2)
    {
        sbf.append(str.mid(str.length()-2, 2));
        str.remove(str.length()-2, 2);
    }
    if(str.length() == 1)   sbf.append(str);

    sbf = sbf.rightJustified(8, '0', true);
    return sbf.toLong(nullptr, 16);
}

/*=========================================================================
 *  リモートInput表示更新
 *      引数はリモートInputのデータ(４バイト)
 *========================================================================*/
void MainWindow::UpdateRemoteInput(uint32_t data)
{
    for(int i = 0; i < 32; i++)
    {
        QLabel  *label;
        switch(i)
        {
            case  0: label = ui->lblIN00; break;
            case  1: label = ui->lblIN01; break;
            case  2: label = ui->lblIN02; break;
            case  3: label = ui->lblIN03; break;
            case  4: label = ui->lblIN04; break;
            case  5: label = ui->lblIN05; break;
            case  6: label = ui->lblIN06; break;
            case  7: label = ui->lblIN07; break;
            case  8: label = ui->lblIN08; break;
            case  9: label = ui->lblIN09; break;
            case 10: label = ui->lblIN10; break;
            case 11: label = ui->lblIN11; break;
            case 12: label = ui->lblIN12; break;
            case 13: label = ui->lblIN13; break;
            case 14: label = ui->lblIN14; break;
            case 15: label = ui->lblIN15; break;
            case 16: label = ui->lblIN16; break;
            case 17: label = ui->lblIN17; break;
            case 18: label = ui->lblIN18; break;
            case 19: label = ui->lblIN19; break;
            case 20: label = ui->lblIN20; break;
            case 21: label = ui->lblIN21; break;
            case 22: label = ui->lblIN22; break;
            case 23: label = ui->lblIN23; break;
            case 24: label = ui->lblIN24; break;
            case 25: label = ui->lblIN25; break;
            case 26: label = ui->lblIN26; break;
            case 27: label = ui->lblIN27; break;
            case 28: label = ui->lblIN28; break;
            case 29: label = ui->lblIN29; break;
            case 30: label = ui->lblIN30; break;
            case 31: label = ui->lblIN31; break;
        }
        bool    fg = data & (0x00000001 << i) ? true : false;
        ToggleInputLabel(label, fg);
    }
}

/*=========================================================================
 *  リモートInput状態表示ラベル更新
 *========================================================================*/
void MainWindow::ToggleInputLabel(QLabel *label, bool fg)
{
    if(fg)
    {
        label->setText("ON");
        label->setStyleSheet("background-color:lime");
    }
    else
    {
        label->setText("OFF");
        label->setStyleSheet("background-color:#efefef");
    }
}

/*=========================================================================
 *  リモートOutputデータ書込コマンド文字列作成
 *========================================================================*/
QByteArray MainWindow::MakeDregWriteString(void)
{
    // リモートOutputデータ(32bit=16進８桁)
    QString    data = QString::number(m_OutputBits, 16).rightJustified(8, '0');

    QByteArray ret = "51";      // データレジスタ書込コマンド
    ret.append("4E04");         // 開始アドレス(D1102:0x044E)
    ret.append("0200");         // 転送サイズ(2word:0x0002)

    ret.append(data.mid(6, 2).toLatin1());      // 出力データ(LL)
    ret.append(data.mid(4, 2).toLatin1());      // 出力データ(LH)
    ret.append(data.mid(2, 2).toLatin1());      // 出力データ(HL)
    ret.append(data.mid(0, 2).toLatin1());      // 出力データ(HH)

    ret.append(MakeCheckSum(ret));              // チェックサム

    return ret;
}

/*=========================================================================
 *  リモートInputデータ読出コマンド文字列作成
 *========================================================================*/
QByteArray MainWindow::MakeDregReadString(void)
{
    QByteArray ret = "50";      // データレジスタ読出コマンド
    ret.append("4C04");         // 開始アドレス(D1100:0x044C)
    ret.append("0200");         // 転送サイズ(2word:0x0002)

    ret.append(MakeCheckSum(ret));      // チェックサム

    return ret;
}

/*=========================================================================
 *  チェックサム文字列作成
 *========================================================================*/
QByteArray MainWindow::MakeCheckSum(QByteArray str)
{
    uint16_t   sum = 0;
    for(int i = 0; i < str.length(); i++)
    {
        sum += str[i];
    }
    QString sumstr = QString::number(sum, 16).rightJustified(4, '0');   // 16進４桁

    return sumstr.right(2).toLatin1();      // 下位２桁を返す
}

/*=========================================================================
 *  USBシリアルポート送信
 *========================================================================*/
void MainWindow::SerialPortSend(QByteArray send)
{
    QByteArray sbf;

    sbf.append(0x02);   // STX
    sbf.append(send);
    sbf.append(0x03);   // ETX

    m_SerialPort->write(sbf);
    //qDebug().noquote() << "Serial Send   :" << sbf;
}


