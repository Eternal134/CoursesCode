#ifndef BTN_APPLY_H
#define BTN_APPLY_H

#include <QObject>
#include <QPushButton>

class btn_apply : public QPushButton
{
    Q_OBJECT
public:
    explicit btn_apply(QWidget *parent = nullptr);
    // 设置鼠标点击事件
    void mousePressEvent(QMouseEvent *mouseEvent);

signals:

    // 点击了该控件，准备选择算法
    void toChoose();
    // 选择了首次适应算法
    void choseFirstFit();
    // 选择了循环适应算法
    void choseNextFit();
    // 选择了最佳适应算法
    void choseBestFit();
    // 选择完后
    void chosen();

};

#endif // BTN_APPLY_H
