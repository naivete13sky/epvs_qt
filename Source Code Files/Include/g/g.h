#pragma once
#ifndef G_H
#define G_H

#include <QString>
#include <QProcess>

class G
{
public:
    G(const QString& gatewayPath, const QString& gSetupType = "vmware", const QString& GENESIS_DIR = "C:/genesis", const QString& gUserName = "1");
    ~G();

    int exec_cmd(const QString& cmd);

private:
    QString gatewayPath;
    QString gUserName;
    QProcess* process;
    QString command_output;
    
};

#endif // G_H
