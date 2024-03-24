#ifndef WINDOW_H
#define WINDOW_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QFileDialog>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QLabel>
#include <QFrame>

#include <vector>
#include <map>

using namespace std;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);

public slots:
    // event handlers (in Qt "slots")
    // ...
    void openButtonClicked();
    void checkButtonClicked();
    void clearButtonClicked();
private:

signals:

};

#endif
