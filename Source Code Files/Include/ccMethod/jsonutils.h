#ifndef JSONUTILS_H
#define JSONUTILS_H

#include <QJsonObject>
#include <QVariant>

void modifyJsonValue(QJsonObject& jsonObject, const QString& keyPath, const QVariant& newValue);

#endif // JSONUTILS_H

