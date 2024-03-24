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

#include <QPainter>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>

#include <QLineEdit>
#include <QIntValidator>

#include <QColor>

#include <vector>
#include <map>

#include "game.h"

#define GRID_SIZE 9.0
#define GRID 600.0
#define OFFSET 0
#define x_offset 0
#define y_offset 0


#define BOARDTEXTCOLOR "#184e77"
#define THICKLINESCOLOR "#184e77"
#define THINLINECOLOR "#184e77"
#define BUTTONTEXTCOLOR "#d9ed92"
#define BACKGROUNDCOLOR "#d9ed92"
#define BUTTONBACKGROUNDCOLOR "#184e77"
#define ERROR "#ff0000"

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
    void handleClickedCell(int row, int col);
    void handleReturnPressed(int row, int col);
private:
    game sud;
    int mistakes = 0;
    QLineEdit *userInput = nullptr;
    bool cellBeingEdited = false;
signals:
    void cellClicked(int row, int col);

};

#endif
