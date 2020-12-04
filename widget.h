#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mymap.h"

/**
 * 1.cxk本尊
 * 2.墙壁
 * 3.篮球
 * 4.篮筐（此时仍然可以推篮球）
 * 5.空地
 * 6.共存态
 * 共六种基本地图状态
 * 可加道具：
 *      1.炸药，炸毁一处墙壁
 *      2.钩锁，将篮球向后拉，限制步数
 *      3.暴扣，摧毁一个已经入框的篮球
 */

const int LINE = 10, ROLL = 10;
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    int map[LINE][ROLL]
    //1 cxk;2 wall;3 basketball;4 basket;5 empty;
    {
        {2,2,2,2,2,2,2,2,2,2},
        {2,1,5,5,5,5,5,5,5,2},
        {2,5,2,5,5,5,5,5,5,2},
        {2,5,2,4,2,5,5,5,5,2},
        {2,5,2,2,2,5,5,3,5,2},
        {2,5,5,5,5,5,5,5,5,2},
        {2,5,5,3,5,2,2,5,5,2},
        {2,5,5,5,5,2,4,5,5,2},
        {2,5,5,5,5,5,5,5,5,2},
        {2,2,2,2,2,2,2,2,2,2}
    };//load the map
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent*) override;
    void keyPressEvent(QKeyEvent *event) override;
    void KeyManipuation(int UserKey);
    void loadmap(int m);
    bool GameOver();
    void Winning();

private slots:
    void on_pdb_start_clicked();

    void on_pdb_exit_clicked();

private:
    Ui::Widget *ui;
    QPixmap cxk;
    QPixmap wall;
    QPixmap ball;
    QPixmap basket;
    QPixmap empty;
    QPixmap toge;
    int game_page = 1;
    int startid = 0;
    int step = 0;
};
#endif // WIDGET_H
