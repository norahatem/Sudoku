#include "window.h"

#include <QPainter>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>

#include <map>
#include <vector>

#define GRID_SIZE 9
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

Window::Window(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(GRID + 2*OFFSET, GRID + GRID/10.0);
    setWindowTitle("Sudoku");
    //layouts
    auto *mainLayout = new QVBoxLayout(this);
    auto *buttonLayout = new QHBoxLayout();


    //buttons
    //open button to allow the user to open a board
    QPushButton *openButton = new QPushButton("Open", this);
    QPushButton *checkButton = new QPushButton("Check", this);
    QPushButton *clearButton = new QPushButton("Clear", this);
    // QPushButton *solveButton = new QPushButton("Solve", this);
    //QPushButton *randomButton = new QPushButton("Generate Random", this);

    buttonLayout->addWidget(openButton, 1, Qt::AlignRight);
    buttonLayout->addWidget(checkButton, 0);
    buttonLayout->addWidget(clearButton, 0);
    // hbox->addWidget(solveButton, 0);
    // hbox->addWidget(randomButton, 0);


    mainLayout->addStretch(1);
    mainLayout->addLayout(buttonLayout);
    //move buttons to be below the board
    //openButton->move(GRID/6.0, GRID + GRID/40.0);

    //connect buttons signals to slots
    //connect the open button to the slot open button clicked
    connect(openButton, &QPushButton::clicked, this, &Window::openButtonClicked);
    connect(checkButton, &QPushButton::clicked, this, &Window::checkButtonClicked);
    connect(clearButton, &QPushButton::clicked, this, &Window::clearButtonClicked);
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
    // painter.drawText(120,200,tr("1"));


    //draw the grid of the sudoku
    for(int i= 0; i<GRID_SIZE+1; i++){
        //set default line width to 1
        painter.setPen(QPen(QColor(THINLINECOLOR) , 1));
        //if it is the one of the 9 boxes outlines, set it to 3 instead
        if (i % 3 == 0)
            painter.setPen(QPen(QColor(THICKLINESCOLOR),3));


        // Draw horizontal lines
        painter.drawLine(x_offset, (i * (GRID / 9.0)) + x_offset, GRID+x_offset,(i * (GRID / 9.0))+x_offset);

        // Draw vertical lines
        painter.drawLine((i * (GRID / 9.0))+y_offset, y_offset,( i * (GRID / 9.0))+y_offset, GRID +y_offset);
    }
}

void Window::mouseReleaseEvent(QMouseEvent * event)
{
    // get click position
    qDebug() << "Mouse x " << event->x() << " Mouse y " << event->y();
}

//slots to handle buttons
void Window::openButtonClicked(){
    qDebug() << "Open button clicked";
}
void Window::checkButtonClicked(){
    qDebug() << "Check button clicked";
}
void Window::clearButtonClicked(){
    qDebug() << "Clear button clicked";
}
