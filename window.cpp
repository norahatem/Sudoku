#include "window.h"

using namespace std;

Window::Window(QWidget *parent) : QWidget(parent)
{
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColor(BACKGROUNDCOLOR));
    setPalette(pal);
    setFixedSize(GRID + 2*OFFSET, GRID + GRID/12.5);
    setWindowTitle("Anwar Sudoku");
    //layouts
    auto *mainLayout = new QVBoxLayout(this);
    auto *buttonLayout = new QHBoxLayout();


    //buttons
    //open button to allow the user to open a board
    QPushButton *openButton = new QPushButton("Open", this);
    QPushButton *checkButton = new QPushButton("Check", this);
    QPushButton *clearButton = new QPushButton("Clear", this);
    QPushButton *solveButton = new QPushButton("Solve", this);
    QPushButton *randomButton = new QPushButton("Random Board", this);

    //edit stylesheet of buttons
    QString style = "background-color: " BUTTONBACKGROUNDCOLOR "; color: " BUTTONTEXTCOLOR ";";
    openButton->setStyleSheet(style);
    checkButton->setStyleSheet(style);
    clearButton->setStyleSheet(style);
    randomButton->setStyleSheet(style);
    solveButton->setStyleSheet(style);

    buttonLayout->addWidget(openButton, 1, Qt::AlignRight);
    buttonLayout->addWidget(checkButton, 0);
    buttonLayout->addWidget(clearButton, 0);
    buttonLayout->addWidget(randomButton, 0);
    buttonLayout->addWidget(solveButton, 0);


    mainLayout->addStretch(1);
    mainLayout->addLayout(buttonLayout);

    //connect buttons signals to slots
    connect(openButton, &QPushButton::clicked, this, &Window::openButtonClicked);
    connect(checkButton, &QPushButton::clicked, this, &Window::checkButtonClicked);
    connect(clearButton, &QPushButton::clicked, this, &Window::clearButtonClicked);
    connect(randomButton, &QPushButton::clicked, this, &Window::randomButtonClicked);
    connect(solveButton, &QPushButton::clicked, this, &Window::solveButtonClicked);


    //connect signal (cellClicked) to the slot handle clicked cell
    connect(this, &Window::cellClicked, this, &Window::handleClickedCell);

}

void Window::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QPen pen;
    QFont font;
    font.setPixelSize(30);
    //pen.setWidth(4);
    painter.setPen(pen);
    painter.setFont(font);

    //code to print the board (numbers)
    for(int row = 0; row<9; row++){
        for(int col =0; col<9; col++){
            if(sud.getCell(row, col) != '0'){

                // Determine if the cell is predefined
                bool isPredefined = noEdit[row][col];

                if(!isPredefined && !sud.isValidCell(row, col))
                    painter.setPen(QColor(ERROR));
                else
                    painter.setPen(QColor(BOARDTEXTCOLOR));


                // Define background color based on whether the cell is predefined or not
                QColor backgroundColor = isPredefined ? QColor(PREDEFINEDCELLCOLOR) : QColor(BACKGROUNDCOLOR);
                //draw rectangle with a different background for the numbers that are predefined by file
                painter.fillRect(col * (600.0 / 9.0) + x_offset , row * (600.0 / 9.0) + y_offset, 600.0 / 9.0 ,
                                 600.0 / 9.0 , backgroundColor);


                //code to print numbers
                QString buffer = QString(sud.getCell(row,col));
                painter.drawText((GRID / GRID_SIZE * col + GRID / ((GRID_SIZE * 2) + 2)) + OFFSET,
                                 (GRID / GRID_SIZE * row + GRID / ((GRID_SIZE * 2) - 5)) + OFFSET, buffer);
            }
        }
    }

    //draw grid after backgound as the rectangles hide the grid
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
    //get where the mouse is clicked, which cell is it
    int row = event->y() / (GRID/GRID_SIZE);
    int col = event->x() /(GRID/GRID_SIZE);
    if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE)
    {
        //emit a signal with the row and column of the clicked cell
        emit cellClicked(row, col);
    }
}

//slots to handle buttons
void Window::openButtonClicked(){
    qDebug() << "Open button clicked";
    //dialog to select file
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Puzzle"), "D:\\games", tr("Text Files (*.txt)"));
    //call the setBaord from file for the original sudoku which is declared as game
    sud.setBoardFromFile(fileName.toStdString());

    predefinedCells();

    //must call update(), otherwise widget will not be updated
    update();
}

void Window::checkButtonClicked(){
    QString msg;
    qDebug() << "Check button clicked";
    bool isPredefined;
    mistakes = 0;
    for(int row = 0; row < 9; row++) {
        for(int col = 0; col < 9; col++) {
            isPredefined = noEdit[row][col];
            if (sud.getCell(row, col) != '0' && !sud.isValidCell(row, col) && !isPredefined) {
                mistakes++;
            }
        }
    }

    if(sud.isBoardComplete() && sud.isBoardValid())
        msg = "YOU WON!!";
    else if(sud.isBoardValid())
        msg = "Board is not complete, but no mistakes!";
    else if(sud.isBoardComplete())
        msg = "Your board is complete with " + QString::number(mistakes) +" mistakes";
    else
        msg = "Board not complete and you have " + QString::number(mistakes) + " mistakes.";

    QMessageBox::information(this, "Check board", msg);
}

void Window::clearButtonClicked(){
    qDebug() << "Clear button clicked";
    //clear the sudoku board
    sud.clearBoard();
    update();
}

void Window::handleClickedCell(int row, int col) {
    if (cellBeingEdited) {
        // Close the current QLineEdit
        delete userInput;
        cellBeingEdited = false;
    }

    // Check if cell can be edited or not
    if (noEdit[row][col]) {
        // Cell cannot be edited, return early
        //this is to prevent the program from crashing habibty okay
        return;
    }

    // Create a new QLineEdit for user input
    userInput = new QLineEdit(this);

    //calculate sizes and coordinates
    int textBoxSize = cellSize * 0.7;
    int x = col * cellSize + OFFSET + (cellSize - textBoxSize) / 2;
    int y = row * cellSize + OFFSET + (cellSize - textBoxSize) / 2;

    //set validator to only accept values 1-9
    userInput->setValidator(new QIntValidator(1, 9, this));
    //setting the alignment in the centre centres the text in the line edit
    userInput->setAlignment(Qt::AlignCenter);
    //change properties of the font appearing in the line edit
    QFont font;
    QPalette fontPallete;
    fontPallete.setColor(QPalette::Text, QColor(BOARDTEXTCOLOR));
    font.setPixelSize(25);
    userInput->setFont(font);
    //set geometry of the line edit and show it
    userInput->setGeometry(x, y, textBoxSize, textBoxSize);
    userInput->show();
    cellBeingEdited = true;

    // Connect returnPressed signal to handle return pressed slot
    connect(userInput, &QLineEdit::returnPressed, this, [this, row, col]() {
        handleReturnPressed(row, col);
    });
}

void Window::handleReturnPressed(int row, int col) {
    // Get the input value
    QString input = userInput->text();
    if (!input.isEmpty()) {
        //update sudoku
        sud.setCell(input.at(0).toLatin1(), row, col);
        update();
    }
    //after finishing delete the line edit and assign cellBeingEdited a value of false
    delete userInput;
    cellBeingEdited = false;
}

void Window::randomButtonClicked(){
    qDebug() << "Random button clicked";
    //9 is the grid size and the other number is the number of empty cells
    sud.generateRandom(9,46);
    //sud.setBoardFromFile("D:\\games\\randomGame.txt");
    predefinedCells();
    update();
}

void Window::predefinedCells(){
    //populate the noEdit array here to indicate whether this cell can be edited or not
    //if a cell can be edited, 0, if a cell can't 1

    for(int row=0; row<GRID_SIZE; row++){
        for(int col=0; col<GRID_SIZE; col++){
            if(sud.getCell(row, col) == '0'){
                noEdit[row][col] = false;
            }else{
                noEdit[row][col] = true;
            }
        }
    }
}

void Window::solveButtonClicked(){
    qDebug() << "Solve button clicked";
}
