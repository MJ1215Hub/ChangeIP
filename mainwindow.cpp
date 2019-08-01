#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMaximumSize(400,200);
    this->setMinimumSize(400,200);
    connect(ui->comboBox,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&MainWindow::comboboxIndexChangeSlot);
    connect(ui->lineEdit,&QLineEdit::textEdited,this,&MainWindow::LineEditEditedSlot);
    connect(ui->lineEdit_2,&QLineEdit::textEdited,this,&MainWindow::LineEditEditedSlot);

    //----------------扫描网卡--------------------//

    g_NetWorkInterfaces = myNetWorkInterface.allInterfaces();
    foreach (QNetworkInterface m_netinterface, g_NetWorkInterfaces) {
        QString name = m_netinterface.name();
        QString address = m_netinterface.hardwareAddress();
        ui->comboBox->addItem(m_netinterface.humanReadableName());
    }
    //------------------------------------------//
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::comboboxIndexChangeSlot(int m_dSelectNum)
{
    qDebug()<<"select changed";
    QNetworkInterface tem_NetInterface;
    QList<QNetworkInterface> tem_NetWorkInterfaces = tem_NetInterface.allInterfaces();
    QNetworkInterface tem_SelectNetWork = tem_NetWorkInterfaces[m_dSelectNum];
    QList<QNetworkAddressEntry> entrylist = tem_SelectNetWork.addressEntries();
    foreach (QNetworkAddressEntry entry, entrylist) {
        if(entry.prefixLength()<64){
            ui->lineEdit->setText(entry.ip().toString());
            ui->lineEdit_2->setText(entry.netmask().toString());
            qDebug()<<entry.netmask().toString();
        }else{
            ui->lineEdit->setText("");
            ui->lineEdit_2->setText("");
        }
        //qDebug()<<entry.prefixLength();
    }
}

void MainWindow::on_ChangePushButton_clicked()
{
    QString tem_strCommand;

    bool tem_bMatch = Match(ui->lineEdit->text());
    tem_bMatch = tem_bMatch && Match(ui->lineEdit_2->text());
    if(false == tem_bMatch){
        QMessageBox::information(this,"information","IP or net mask format error!");
        return;
    }

    QNetworkInterface tem_SelectNetWork =
            g_NetWorkInterfaces[ui->comboBox->currentIndex()];
#ifdef Q_OS_MAC//Mac系统下
    qDebug()<<"Mac";

#endif

#ifdef Q_OS_WIN32//Windows系统下
    qDebug()<<"Windows";
    tem_strCommand = "netsh interface ipv4 set address name = ";
    tem_strCommand += tem_SelectNetWork.humanReadableName();
    tem_strCommand += " source = static address = " + ui->lineEdit->text()+
            " mask = "+ui->lineEdit_2->text();

    qDebug()<<tem_strCommand;
#endif

#ifdef Q_OS_LINUX//Linux系统下
    qDebug()<<"Linux";
    tem_strCommand = "sudo ifconfig ";
    tem_strCommand += tem_SelectNetWork.humanReadableName();
    tem_strCommand += " " + ui->lineEdit->text()+
            " net mask "+ui->lineEdit_2->text();

    qDebug()<<tem_strCommand;

#endif

#ifdef __arm__//arm系统下
    qDebug()<<"ARM";


#endif
    process.start(tem_strCommand);
    process.waitForFinished();
    QMessageBox::information(this,QString("information"),QString("completed!"));

}
void MainWindow::LineEditEditedSlot(const QString &text)
{
    bool tem_bMatch = Match(text);
    QLineEdit *tem_Sender = static_cast<QLineEdit *>(sender());
    qDebug()<<tem_Sender->objectName();

    if(true == tem_bMatch){
        //match ip
        qDebug()<<"match";
        tem_Sender->setStyleSheet("background-color: white;");
    }else{
        //not match
        qDebug()<<"Not match";
        tem_Sender->setStyleSheet("background-color: red;");
    }
}
bool MainWindow::Match(QString text)
{
    QString Pattern = "\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.)"
                      "{3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b";
    QRegExp MyQRegExp(Pattern);
    return MyQRegExp.exactMatch(text);
}
