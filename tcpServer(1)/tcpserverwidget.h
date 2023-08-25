#ifndef TCPSERVERWIDGET_H
#define TCPSERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class tcpServerWidget; }
QT_END_NAMESPACE

class tcpServerWidget : public QWidget
{
    Q_OBJECT

public:
    tcpServerWidget(QWidget *parent = nullptr);
    ~tcpServerWidget();


private:
    Ui::tcpServerWidget *ui;
    QTcpServer *tcpServer; //监听套接字
    QTcpSocket *tcpSocket; //通讯套接字
private slots:
    void tcpServer_newConnection();
    void tcpSocket_readRead();
    void on_pushButtonSend_clicked();
    void on_pushButtonClose_clicked();
};
#endif // TCPSERVERWIDGET_H
