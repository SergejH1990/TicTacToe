#include "tttgame.h"
#include "./ui_tttgame.h"

TTTGame::TTTGame(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TTTGame)
{
    ui->setupUi(this);

     connect(ui->pushButton_1,SIGNAL(released()),this,SLOT(paintField()));
     connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(paintField()));
     connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(paintField()));
     connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(paintField()));
     connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(paintField()));
     connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(paintField()));
     connect(ui->pushButton_7,SIGNAL(released()),this,SLOT(paintField()));
     connect(ui->pushButton_8,SIGNAL(released()),this,SLOT(paintField()));
     connect(ui->pushButton_9,SIGNAL(released()),this,SLOT(paintField()));

     connect(ui->buttonReset,SIGNAL(released()),this,SLOT(resetFields()));
}


void TTTGame::paintField(){
    QPushButton *button=(QPushButton*)sender();

    button->setText("X");


}

void TTTGame::resetFields(){

    for(int i=1;i<=9;i++){
       ui->pushButton_1->setText(QString::number(i,'g',0));
    }

}


void TTTGame::paintField(){
    QPushButton *button=(QPushButton*)sender();

    button->setText("X");


}

TTTGame::~TTTGame()
{
    delete ui;
}

