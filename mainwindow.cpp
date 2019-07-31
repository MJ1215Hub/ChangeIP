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

void MainWindow::on_ScanPushButton_clicked()
{
    int tem_dNetNum = 0;
    g_NetWorkInterfaces = myNetWorkInterface.allInterfaces();
    foreach (QNetworkInterface m_netinterface, g_NetWorkInterfaces) {
        QString name = m_netinterface.name();
        QString address = m_netinterface.hardwareAddress();
        qDebug()<<tem_dNetNum;
        //qDebug()<< name<<endl;
        qDebug()<<m_netinterface.humanReadableName()<<endl;
        ui->comboBox->addItem(m_netinterface.humanReadableName());


//        qDebug()<<address<<endl;

//        QList<QNetworkAddressEntry> entryList = m_netinterface.addressEntries();
//        foreach(QNetworkAddressEntry entry,entryList){
//            if(entry.prefixLength()<64 && entry.prefixLength() >0){
//                qDebug()<<"ip:"<<entry.ip().toString();
//                qDebug()<<"netmask:"<<entry.netmask().toString();
//                qDebug()<<"Broadcast:"<<entry.broadcast().toString();
//                qDebug()<<"PrefixLength:"<<entry.prefixLength();
//            }
//        }
        tem_dNetNum++;
    }
    tem_dNetNum = 0;
    foreach (QNetworkInterface m_netinterface, g_NetWorkInterfaces) {
        qDebug()<<tem_dNetNum;
        if(m_netinterface.isValid()){
            qDebug()<<m_netinterface.humanReadableName()<<"valid";
        }

        tem_dNetNum++;
    }




//   qDebug()<< myNetWorkInterface.hardwareAddress();

}
void MainWindow::comboboxIndexChangeSlot(int m_dSelectNum)
{
    qDebug()<<"select changed";
    QNetworkInterface tem_SelectNetWork = g_NetWorkInterfaces[m_dSelectNum];
    QList<QNetworkAddressEntry> entrylist = tem_SelectNetWork.addressEntries();
    foreach (QNetworkAddressEntry entry, entrylist) {
        if(entry.prefixLength()<64&& entry.prefixLength()>0){
            ui->lineEdit->setText(entry.ip().toString());
            ui->lineEdit_2->setText(entry.netmask().toString());
        }else if(entry.prefixLength()<0){
            ui->lineEdit->setText("");
            ui->lineEdit_2->setText("");
        }
    }
}

void MainWindow::on_ChangePushButton_clicked()
{
    QString tem_strCommand;
    QNetworkInterface tem_SelectNetWork = g_NetWorkInterfaces[ui->comboBox->currentIndex()];
//    QList<QNetworkAddressEntry> entrylist = tem_SelectNetWork.addressEntries();
//    foreach (QNetworkAddressEntry entry, entrylist) {
//        if(entry.prefixLength()<64){
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

#endif

#ifdef __arm__//arm系统下
    qDebug()<<"ARM";


#endif

//        }
//    }
//    process.start(tem_strCommand);
//    process.waitForFinished();

}
