#include "flamehistory.h"
#include "ui_flamehistory.h"   // lowercase file name
#include <QSqlTableModel>

FlameHistory::FlameHistory(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::flamehistory)   // 🔥 lowercase
{
    ui->setupUi(this);

    model = new QSqlTableModel(this);
    model->setTable("FLAME");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Date");
    model->setHeaderData(2, Qt::Horizontal, "Time");

    ui->tableViewFlame->setModel(model);
    ui->tableViewFlame->resizeColumnsToContents();
}

FlameHistory::~FlameHistory()
{
    delete ui;
}
