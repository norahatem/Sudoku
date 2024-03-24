this project uses C++ and Qt libraries to produce a sudoku GUI. It is meant to run on an Rpi but to do this the path to look into in the QFileDialog in the openButtonClickes will need to be changed, otherwise everything is ok.
This project as of now has few functionalities and a few bugs that will need to be addressed. One of the big bugs that must be addressed is the fact the initial values of the sudoku board can be edited by the user. I haven't implemented the logic to prevent the user from editing-willingly or mistakingly- the original values of the sudoku board.
functionalities:
Allows user to choose their game
Allows user to check board
Allows user to clear everything
When user checks board, they get the number of mistakes. These mistakes are also printed in red to alter the user.
The user can input a number only from 1-9 in an attempt to solve the board.
one more issue-not really- that needs to be addressed, is the fact that the user cannot close the line edit unless a value is entered, and this value must be 1-9. however, the user can open another line edit so it is fine.
![image](https://github.com/norahatem/Sudoku/assets/143084381/76a95e22-b300-447a-b86e-cfd93c32fc6f)
![image](https://github.com/norahatem/Sudoku/assets/143084381/fbc35e03-c233-447a-9972-9607f13fd244)
![image](https://github.com/norahatem/Sudoku/assets/143084381/cf47d58d-e97b-4d9c-a827-cbf92fd8d217)
![image](https://github.com/norahatem/Sudoku/assets/143084381/8362a25d-e3d6-4b1e-978d-7910685ae2da)
![image](https://github.com/norahatem/Sudoku/assets/143084381/746ce685-2f44-4ceb-9cb7-db597fc78953)
