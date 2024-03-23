#include "window.h"

#include <QPainter>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>

#include <map>
#include <vector>

#define GRID_SIZE 9
#define GRID 600
#define OFFSET 0

#define BOARDTEXTCOLOR "#184e77"
#define THICKLINESCOLOR "#184e77"
#define THINLINECOLOR "#184e77"
#define BUTTONTEXTCOLOR "#d9ed92"
#define BACKGROUNDCOLOR "#d9ed92"
#define BUTTONBACKGROUNDCOLOR "#184e77"
#define ERROR "#ff0000"

using namespace std;

Window::Window(QWidget *parent) : QWidget(parent)
{
    // set form size
    // setFixedSize(400,600);
    // setWindowTitle("Sudoku bla....");
    setMinimumSize(GRID, GRID);
    setWindowTitle("Sudoku");
}


void Window::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QPen pen;
    QFont font;
    font.setPixelSize(30);
    pen.setWidth(4);
    painter.setPen(pen);
    painter.setFont(font);
    // QPoint p1(10,20), p2(80,60);
    // painter.drawLine(p1, p2);
    // painter.drawText(120,200,tr("1"));

    for(int i= 0; i<GRID_SIZE+1; i++){
        painter.setPen(QPen(QColor(THINLINECOLOR) , 1));
        if (i % 3 == 0)
            painter.setPen(QPen(QColor(THICKLINESCOLOR),3));


        // Draw horizontal lines
        painter.drawLine(OFFSET, (i * (GRID / 9.0))+OFFSET, GRID+OFFSET,(i * (GRID / 9.0))+OFFSET);

        // Draw vertical lines
        painter.drawLine((i * (GRID / 9.0))+OFFSET, OFFSET,( i * (GRID / 9.0))+OFFSET, GRID +OFFSET);
    }


}

void Window::mouseReleaseEvent(QMouseEvent * event)
{
    // get click position
    qDebug() << "Mouse x " << event->x() << " Mouse y " << event->y();
}
