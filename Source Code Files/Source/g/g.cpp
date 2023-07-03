#pragma execution_character_set("utf-8")
#include "../../Include/g/g.h";
#include <qDebug>

G::G(const QString& gatewayPath, const QString& gSetupType, const QString& GENESIS_DIR, const QString& gUserName)
    : gatewayPath(gatewayPath), gUserName(gUserName)
{
    QString command = QString("%1 %2").arg(gatewayPath, gUserName);
    if (gSetupType == "vmware")
    {
        QString command0 = "SET GENESIS_DIR=C:/Program Files/shareg\n";
        process = new QProcess();
        //process->start(command0 + "&" + command);
        process->start("cmd");

        process->write("SET GENESIS_DIR=C:/Program Files/shareg\n");  // ·¢ËÍÃüÁî
        process->waitForBytesWritten();
        output = QString::fromLocal8Bit(process->readAll());
        qDebug().noquote() << output;

        QByteArray commandBytes = command.toLocal8Bit();  // Convert QString to QByteArray
        process->write(commandBytes + "\n");  // ·¢ËÍÃüÁî
        process->waitForBytesWritten();
        process->waitForReadyRead();
        output = QString::fromLocal8Bit(process->readAll());
        qDebug().noquote() << output;


    }
    else if (gSetupType == "local")
    {
        QString command0 = QString("SET GENESIS_DIR=%1").arg(GENESIS_DIR);
        process = new QProcess();
        //process->start(command0 + "&" + command);
        process->start("cmd");
    }
}

G::~G()
{
    QProcess::execute("taskkill /f /im gateway.exe");
}

int G::exec_cmd(const QString& cmd)
{
    process->write((cmd + "\n").toUtf8());
    process->waitForBytesWritten();
    process->waitForReadyRead();

    output = QString::fromLocal8Bit(process->readAll());
    qDebug() << "result:";
    qDebug().noquote() << output;
    //QString line = process->readLine();
    /*int ret = line.trimmed().toInt();
    return ret;*/
    return 0;
}
