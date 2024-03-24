#include "window.h"

#include <QPainter>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>

#include <map>
#include <vector>

using namespace std;

Window::Window(QWidget *parent) : QWidget(parent)
{
    setFixedSize(GRID + 2*OFFSET, GRID + GRID/10.0);
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

    //connect buttons signals to slots
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


    //code to print the board (numbers)
    for(int row = 0; row<9; row++){
        for(int col =0; col<9; col++){
            if(sud.getCell(row, col) != '0'){
                QString buffer = QString(sud.getCell(row,col));
                painter.drawText((GRID / GRID_SIZE * col + GRID / ((GRID_SIZE * 2) + 2)) + OFFSET,
                                 (GRID / GRID_SIZE * row + GRID / ((GRID_SIZE * 2) - 5)) + OFFSET, buffer);
            }
        }
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
    //dialog to select file
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Puzzle"), "D:\\games", tr("Text Files (*.txt)"));
    //call the setBaord from file for the original sudoku which is declared as game
    sud.setBoardFromFile(fileName.toStdString());
    //must call update(), otherwise widget will not be updated
    update();

}
void Window::checkButtonClicked(){
    QString msg;
    qDebug() << "Check button clicked";
    if(sud.isBoardComplete() && sud.isBoardValid())
        msg = "YOU WON!!";
    else if(sud.isBoardValid())
        msg = "Board is not complete, no mistakes tho!";
    else if(sud.isBoardComplete())
        msg = "You have some mistakes although your baord is complete";
    else
        msg = "Board not complete and you have mistakes";

    QMessageBox::information(this, "Check board", msg);
}
void Window::clearButtonClicked(){
    qDebug() << "Clear button clicked";
    //clear the sudoku board
    sud.clearBoard();
    update();
}
