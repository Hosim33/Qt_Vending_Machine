#include "widget.h"
#include "ui_widget.h"
#include "QMessageBox"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    button_state();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::button_state()
{
    ui->pbCoffee->setEnabled(money >= 100);
    ui->pbTea->setEnabled(money >= 150);
    ui->pbMilk->setEnabled(money >= 200);
}

void Widget::changeMoney(int diff)
{
    money += diff;
    ui->lcdNumber->display(money);
    button_state();
}

void Widget::on_pb10_clicked()
{
    changeMoney(10);
}

void Widget::on_pb50_clicked()
{
    changeMoney(50);
}

void Widget::on_pb100_clicked()
{
    changeMoney(100);
}

void Widget::on_pb500_clicked()
{
    changeMoney(500);
}

void Widget::on_pbCoffee_clicked()
{
    if (money >= 100) {
        changeMoney(-100);
    }
}

void Widget::on_pbTea_clicked()
{
    if (money >= 150) {
        changeMoney(-150);
    }
}

void Widget::on_pbMilk_clicked()
{
    if (money >= 200) {
        changeMoney(-200);
    }
}

bool Widget::give_coin()
{
    int tmp = money;

    int coin500 = money / 500;
    money %= 500;

    int coin100 = money / 100;
    money %= 100;

    int coin50 = money / 50;
    money %= 50;

    int coin10 = money / 10;

    QMessageBox mb;
    mb.setWindowTitle("거스름돈");
    mb.setInformativeText(QString("500원: %1개\n100원: %2개\n50원: %3개\n10원: %4개")
                                         .arg(coin500).arg(coin100).arg(coin50).arg(coin10));
    mb.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    mb.setIcon(QMessageBox::Icon::Warning);
    mb.setStyleSheet("background-color: #FEF9EF; color: #FF865E;");
    int ret = mb.exec();
    if (ret == QMessageBox::Ok) {
        return true;
    } else if (ret == QMessageBox::Cancel) {
        money = tmp;
        return false;
    }

}

void Widget::on_pbReset_clicked()
{
    int check = give_coin();
    if(check == true) {
        money = 0;
        ui->lcdNumber->display(money);
        button_state();
    }
}
