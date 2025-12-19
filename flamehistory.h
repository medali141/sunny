#ifndef FLAMEHISTORY_H
#define FLAMEHISTORY_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class flamehistory;   // 🔥 MUST MATCH XML
}

class FlameHistory : public QWidget
{
    Q_OBJECT

public:
    explicit FlameHistory(QWidget *parent = nullptr);
    ~FlameHistory();

private:
    Ui::flamehistory *ui;   // 🔥 lowercase
    QSqlTableModel *model;
};

#endif // FLAMEHISTORY_H
