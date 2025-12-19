#include "ard.h"
#include <QSerialPortInfo>
#include <QElapsedTimer>
#include <QDebug>

static QElapsedTimer fireTimer;

Ard::Ard(QObject *parent)
    : QObject(parent)
{
    serial = new QSerialPort(this);
}

bool Ard::connectToArduino()
{
    qDebug() << "Searching for Arduino...";

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Found port:"
                 << info.portName()
                 << info.description()
                 << info.manufacturer();

        if (info.description().contains("Arduino", Qt::CaseInsensitive) ||
            info.manufacturer().contains("Arduino", Qt::CaseInsensitive)) {

            serial->setPort(info);
            break;
        }
    }

    if (serial->portName().isEmpty()) {
        qDebug() << "Arduino NOT found";
        return false;
    }

    serial->setBaudRate(QSerialPort::Baud9600);

    if (serial->open(QIODevice::ReadOnly)) {
        qDebug() << "Arduino connected on" << serial->portName();

        connect(serial, &QSerialPort::readyRead,
                this, &Ard::readData);

        emit arduinoConnected(serial->portName());
        return true;
    }

    qDebug() << "Failed to open serial port";
    return false;
}

void Ard::readData()
{
    static QByteArray buffer;
    static QElapsedTimer fireTimer;
    const int COOLDOWN_MS = 5000; // 5 seconds

    buffer += serial->readAll();

    if (buffer.contains("FIRE")) {

        // First time OR cooldown passed
        if (!fireTimer.isValid() || fireTimer.elapsed() > COOLDOWN_MS) {
            fireTimer.start();
            emit fireDetected();   // 🔥 FIRE EVENT
        }

        buffer.clear();
    }

    // Safety: prevent buffer overflow
    if (buffer.size() > 100)
        buffer.clear();
}


void Ard::disconnectArduino()
{
    if (serial->isOpen())
        serial->close();
}
