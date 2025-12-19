#ifndef ARD_H
#define ARD_H

#include <QObject>
#include <QSerialPort>

class Ard : public QObject
{
    Q_OBJECT

public:
    explicit Ard(QObject *parent = nullptr);
    bool connectToArduino();
    void disconnectArduino();

signals:
    void fireDetected();
    void arduinoConnected(QString port);

private slots:
    void readData();

private:
    QSerialPort *serial;
};

#endif // ARD_H
