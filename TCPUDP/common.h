#ifndef COMMON_H
#define COMMON_H
#include <QDateTime>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QTextEdit>
static QStringList getIPAddresses() {
    QStringList addresses;
    for (const QHostAddress &address : QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol)
            addresses.append(address.toString());
    }
    return addresses;
}

static QString currentTimeStr() {
    return QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss.zzz");
}

static void appendLog(QTextEdit *logEdit, const QString &log) {
    logEdit->append(QString("%1:%2").arg(currentTimeStr()).arg(log));
}

#endif // COMMON_H
