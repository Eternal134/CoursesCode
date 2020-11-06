#include <QPushButton>

void setButtonStyleSheet(QPushButton *btn) {
    btn->setStyleSheet(
                       "QPushButton:hover{"
                       "background-color:rgba(100,255,100,100);"
                       "border-color:rgba(243,135,175,200);"
                       "color:rgba(0,0,0,200);"
                       "}"

                       "QPushButton{"
                       "background-color:qlineargradient(spread:pad, "
                            "x1:0, y1:0, x2:1, y2:1, stop:0 rgba(194, 255, 216, 255), "
                            "stop:1 rgba(70, 94, 251, 255));"
                       "border-radius:5px;"
                       "}"

                       "QPushButton:pressed{"
                       "background-color:rgba(100,255,100,200);"
                       "border-color:rgba(255,255,255,30);"
                       "border-style:inset;"
                       "color:rgba(0,0,0,100);"
                       "}"
                       );
}
