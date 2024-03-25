this project uses C++ and Qt libraries to produce a sudoku GUI. It is meant to run on an Rpi but to do this the path to look into in the QFileDialog in the openButtonClickes will need to be changed, otherwise everything is ok. -InshaAllah-
This project as of now has few functionalities.
functionalities:
Allows user to choose their game
Allows user to check board
Allows user to clear everything
When user checks board, they get the number of mistakes. These mistakes are also printed in red to alter the user.
The user can input a number only from 1-9 in an attempt to solve the board.
one more issue-not really- that needs to be addressed, is the fact that the user cannot close the line edit unless a value is entered, and this value must be 1-9. however, the user can open another line edit so it is fine. Also if the user clicks on one of the predefined cells this closes the other line edit.
![Screenshot 2024-03-25 112713](https://github.com/norahatem/Sudoku/assets/143084381/88b9a82a-950e-4043-bf21-a19fd983c86b)
![Screenshot 2024-03-25 112024](https://github.com/norahatem/Sudoku/assets/143084381/8fa69e40-5667-46b2-a3fd-10d3a5732f70)
![Screenshot 2024-03-25 111733](https://github.com/norahatem/Sudoku/assets/143084381/467718c9-95fb-49c4-a1da-27f92b279696)
![Screenshot 2024-03-25 111720](https://github.com/norahatem/Sudoku/assets/143084381/0a02dd2b-8dd7-4e60-996e-d696e0ed90a5)
![Screenshot 2024-03-25 111651](https://github.com/norahatem/Sudoku/assets/143084381/e5da76c8-5eb1-4d78-bf45-0adbfd2b1815)
![Screenshot 2024-03-25 111556](https://github.com/norahatem/Sudoku/assets/143084381/8054309a-ad87-4b39-b344-f213e5899cd4)
