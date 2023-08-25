#include "tcpserverwidget.h"
#include "ui_tcpserverwidget.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>

tcpServerWidget::tcpServerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::tcpServerWidget)
{
    ui->setupUi(this);

    //1  创建一个监听套接字   QTcpServer
    tcpServer = NULL;
    tcpSocket = NULL;

    tcpServer = new QTcpServer(this);//指定父对象，用于析构时自动回收空间
    //2 绑定IP PORT 设置为监听 Qt 中，省掉了绑定IP这一步
    tcpServer->listen(QHostAddress::Any,8888);
    this->setWindowTitle("服务器端口号:8888");
    //3 如果收到有用户连接的信号  newconnection
    connect(tcpServer,&QTcpServer::newConnection,this,&tcpServerWidget::tcpServer_newConnection);
    //就使用监听套接字建立一个通讯套接字  QTcpSocket

    //4 开始收发  当收到readRead信号，就读取套接字的接收区
    //           当发送按钮按下向套接字的发送区写界面上的文字
    // 5 关闭   当close按钮被点击，关闭连接


}

tcpServerWidget::~tcpServerWidget()
{
    delete ui;
}

void tcpServerWidget::tcpServer_newConnection()
{
    //就使用监听套接字建立一个通讯套接字  QTcpSocket
    tcpSocket = tcpServer->nextPendingConnection();

    //开始收发过程
    // 获取对方的IP和PORT 查通讯套接字的数据手册
    QString ip = tcpSocket->peerAddress().toString();
    qint16 port = tcpSocket->peerPort();
    //组一个字符串，将对方的IP和端口号打印在界面的输出区
    QString temp = QString("[%1:%2]连接成功").arg(ip).arg(port);
    ui->textEditRead->setText(temp);
    //如果发送按钮被点击，就将界面的文本写入套接字的发送域
    //如果收到一个readRead信号，就读取套接字的接收域
    connect(tcpSocket,&QTcpSocket::readyRead,this,&tcpServerWidget::tcpSocket_readRead);
}

void tcpServerWidget::tcpSocket_readRead()
{
    //如果收到一个readRead信号，就读取套接字的接收域
    QByteArray array = tcpSocket->readAll();
    //输出到界面的接收区
    ui->textEditRead->append(array);
}

void tcpServerWidget::on_pushButtonSend_clicked()
{
    //读取界面发送区文字，发送到套接字的发送域
    if(NULL == tcpSocket)
    {
        return;
    }
    QString str = ui->textEditWrite->toPlainText();
    tcpSocket->write(str.toUtf8().data());
    //清空发送区
    ui->textEditWrite->clear();
}

void tcpServerWidget::on_pushButtonClose_clicked()
{
    if(NULL == tcpSocket)
    {
        return;
    }
    //断开连接指针指向空
    tcpSocket->disconnect();
    tcpSocket->close();
    tcpSocket = NULL;
}

