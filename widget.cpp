#include "widget.h"
#include "ui_widget.h"
#include "mymap.h"
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>


/**
 * 1.cxk本尊
 * 2.墙壁
 * 3.篮球
 * 4.篮筐（此时仍然可以推篮球）
 * 5.空地
 * 6.篮球篮筐共存态
 * 7.人，篮框共存态
 * 共六种基本地图状态
 * 可加道具：
 *      1.炸药，炸毁一处墙壁
 *      2.钩锁，将篮球向后拉，限制步数
 *      3.暴扣，摧毁一个已经入框的篮球
 */
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //加载地图资源
    cxk.load("../1.jpg");
    wall.load("../2.jpg");
    ball.load("../3.jpg");
    basket.load("../4.jpg");
    empty.load("../5.jpg");
    toge.load("../6.jpg");
    //初始化数据
    ui->stackedWidget->setCurrentWidget(ui->page_welcomr);
    update();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    if(game_page==1)
    {
        QPainter p;
        p.begin(this);
        p.drawPixmap(0,0,width(),height(),QPixmap("../start.jpg"));
        p.end();
    }
    if(game_page==2)
    {

        for(int i=0;i<600;++i)
        {
            for(int j=0;j<600;++j)
             {
                QPainter p;
                p.begin(this);
                switch (map[i][j])
                {
                case 1:
                case 7:
                    p.drawPixmap(i*60,j*60,60,60,cxk); break;
                case 2: p.drawPixmap(i*60,j*60,60,60,wall); break;
                case 3: p.drawPixmap(i*60,j*60,60,60,ball); break;
                case 4: p.drawPixmap(i*60,j*60,60,60,basket); break;
                case 5: p.drawPixmap(i*60,j*60,60,60,empty); break;
                case 6: p.drawPixmap(i*60,j*60,60,60,toge); break;
                }
                p.end();
            }
        }
    }
}

void Widget::timerEvent(QTimerEvent*ev)
{
    if(ev->timerId() == startid)
    {
        static int num_time = 0;
        ui->label_time->setText(QString("Time used:\n %1 s").arg(num_time));
        num_time++;
    }
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->key()!=Qt::Key_A&&event->key()!=Qt::Key_S&&event->key()!=Qt::Key_D&&event->key()!=Qt::Key_W)
        return;
    int mykey = event->key();
    ++step;
    KeyManipuation(mykey);
}

void Widget::KeyManipuation(int UserKey)
{
    if(game_page==1)
        return;
    int i=0,j=0;
    int currentnum = 1;
    for (i = 0; i < LINE; ++i)
    {
        for (j = 0; j < ROLL; ++j)
        {
            if (map[i][j] == 1 || map[i][j] == 7)
            {
                currentnum = map[i][j];
                break;
            }

        }
        if (map[i][j] == 1 || map[i][j] == 7)
            break;
    }
    //1 cxk;2 wall;3 basketball;4 basket;5 empty;6 toge;7 cxk+basket
    //up:72, down:80, right:75, left:77
    switch(UserKey)
    {
    case Qt::Key_W:
        if (map[i][j - 1] == 5)
        {
            map[i][j] = 5;
            map[i][j - 1] = 1;
            if (currentnum == 7)
                map[i][j] = 4;
        }//cxk towards empty space
        else if (map[i][j - 1] == 3 && map[i][j - 2] == 5)
        {
            map[i][j] = 5;
            map[i][j - 1] = 1;
            map[i][j - 2] = 3;
        }//push the basketball
        else if (map[i][j - 1] == 3 && map[i][j - 2] == 4)
        {
            map[i][j] = 5;
            map[i][j - 1] = 1;
            map[i][j - 2] = 6;
        }//enter the basket
        else if (map[i][j - 1] == 4)
        {
            map[i][j] = 5;
            map[i][j - 1] = 7;
        }
        break;
    case Qt::Key_S:
        if (map[i][j + 1] == 5)
        {
            map[i][j] = 5;
            map[i][j + 1] = 1;
            if (currentnum == 7)
                map[i][j] = 4;
        }//cxk towards empty space
        else if (map[i][j + 1] == 3 && map[i][j + 2] == 5)
        {
            map[i][j] = 5;
            map[i][j + 1] = 1;
            map[i][j + 2] = 3;
        }//push the basketball
        else if (map[i][j + 1] == 3 && map[i][j + 2] == 4)
        {
            map[i][j] = 5;
            map[i][j + 1] = 1;
            map[i][j + 2] = 6;
        }//enter the basket
        else if (map[i][j + 1] == 4)
        {
            map[i][j] = 5;
            map[i][j + 1] = 7;
        }
        break;
    case Qt::Key_D:
        if (map[i + 1][j] == 5)
        {
            map[i][j] = 5;
            map[i + 1][j] = 1;
            if (currentnum == 7)
                map[i][j] = 4;
        }//cxk towards empty space
        else if (map[i + 1][j] == 3 && map[i + 2][j] == 5)
        {
            map[i][j] = 5;
            map[i + 1][j] = 1;
            map[i + 2][j] = 3;
        }//push the basketball
        else if (map[i + 1][j] == 3 && map[i + 2][j] == 4)
        {
            map[i][j] = 5;
            map[i + 1][j] = 1;
            map[i + 2][j] = 6;
        }//enter the basket
        else if (map[i + 1][j] == 4)
        {
            map[i][j] = 5;
            map[i + 1][j] = 7;
        }
        break;
    case Qt::Key_A:
        if (map[i - 1][j] == 5)
        {
            map[i][j] = 5;
            map[i - 1][j] = 1;
            if (currentnum == 7)
                map[i][j] = 4;
        }//cxk towards empty space
        else if (map[i - 1][j] == 3 && map[i - 2][j] == 5)
        {
            map[i][j] = 5;
            map[i - 1][j] = 1;
            map[i - 2][j] = 3;
        }//push the basketball
        else if (map[i - 1][j] == 3 && map[i - 2][j] == 4)
        {
            map[i][j] = 5;
            map[i - 1][j] = 1;
            map[i - 2][j] = 6;
        }//enter the basket
        else if (map[i - 1][j] == 4)
        {
            map[i][j] = 5;
            map[i - 1][j] = 7;
        }
        break;
    default: --step;
    }
    ui->label_step->setText(QString("Steps:\n %1").arg(step));
    update();
    if(GameOver())
        Winning();
}

bool Widget::GameOver()
{
    //1 cxk;2 wall;3 basketball;4 basket;5 empty;6 toge;
    //up:72, down:80, right:75, left:77
    for(int i=0;i<LINE;++i)
        for(int j=0;j<ROLL;++j)
            if(map[i][j]==3)
                return false;
    killTimer(startid);
    return true;
}

void Widget::Winning()
{
    ui->stackedWidget->setCurrentWidget(ui->page_welcomr);
    game_page=1;
}
//start button
void Widget::on_pdb_start_clicked()
{
    //切界面
    ui->stackedWidget->setCurrentWidget(ui->page_game);
    game_page = 2;
    //初始化step
    step = 0;
    //初始化关卡名
    QString ma = ui->comboBox->currentText();
    ui->label_guanqia->setText(ma);
    //初始化地图
    QString str = ui->comboBox->currentText();
    QString dig ="";
    for(int i=str.size()-1;str[i].isDigit();--i)
        dig.append(str[i]);
    int m = dig.toInt();
    loadmap(m);
    //启动计时器
    startid = startTimer(1000);
}
//exit button
void Widget::on_pdb_exit_clicked()
{
    close();
}
//加载地图
void Widget::loadmap(int m)
{
    MyMap mp;
    if(m>11)
        return;
    for(int i=0;i<LINE;++i)
        for(int j=0;j<ROLL;++j)
            map[i][j] = mp.THEmap[m-1][i][j];
}
