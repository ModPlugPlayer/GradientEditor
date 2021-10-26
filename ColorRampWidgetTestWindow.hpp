#pragma once

#include <QMainWindow>

namespace Ui {
class ColorRampWidgetTestWindow;
}

class ColorRampWidgetTestWindow : public QMainWindow
{
    Q_OBJECT

        public:
                 explicit ColorRampWidgetTestWindow(QWidget *parent = nullptr);
    ~ColorRampWidgetTestWindow();
             public slots:
    void onColorClicked(double value, QColor color);


protected:
    Ui::ColorRampWidgetTestWindow *ui;
    void closeEvent(QCloseEvent *event);
};

