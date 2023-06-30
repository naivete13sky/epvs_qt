#include "../../Include/g/g.h";

G::G(const QString& gatewayPath, const QString& gSetupType, const QString& GENESIS_DIR, const QString& gUserName)
    : gatewayPath(gatewayPath), gUserName(gUserName)
{
    QString command = QString("%1 %2").arg(gatewayPath, gUserName);
    if (gSetupType == "vmware")
    {
        QString command0 = "SET GENESIS_DIR=C:/Program Files/shareg";
        process = new QProcess();
        process->start(command0 + "&" + command);
    }
    else if (gSetupType == "local")
    {
        QString command0 = QString("SET GENESIS_DIR=%1").arg(GENESIS_DIR);
        process = new QProcess();
        process->start(command0 + "&" + command);
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
    QString line = process->readLine();
    int ret = line.trimmed().toInt();
    return ret;
}
