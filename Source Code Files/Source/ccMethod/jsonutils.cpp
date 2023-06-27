#include "../../Include/ccMethod/jsonutils.h"
#include <QStringList>
#include <QJsonValue>

void modifyJsonValue(QJsonObject& jsonObject, const QString& keyPath, const QVariant& newValue)
{
    QStringList keys = keyPath.split('/');
    QString topLevelKey = keys.takeFirst();

    if (jsonObject.contains(topLevelKey)) {
        if (keys.isEmpty()) {
            jsonObject.insert(topLevelKey, QJsonValue::fromVariant(newValue));
        }
        else {
            QJsonValue topLevelValue = jsonObject.value(topLevelKey);
            if (topLevelValue.isObject()) {
                QJsonObject subObject = topLevelValue.toObject();
                modifyJsonValue(subObject, keys.join('/'), newValue);
                jsonObject.insert(topLevelKey, subObject);
            }
        }
    }
}
