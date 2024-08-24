
# Animal Guessing Game

This project engages the user in a game to see if it can guess what animal the user is thinking. The can either load their own game data file or use the default game data file the program provides (the game data file is a text file). As the game continues, it learns how to differentiate how two animals are different through the characteristics it learns from the user.



## How It Works

In processing the game data file into the program, the program reads the file line by line. It is important to note that the data file is structured in the format shown below: 

    Q
    question goes here
    G
    animal guess goes here
    G
    animal guess goes here

If a "Q" is read, the program will know that a question has been detected and obtain the actual question on the next loop (all of this takes place within a while loop to read through the text file). If a "G" is read, the program will know that an animal guess has been detected and obtain the actual animal guess on the next loop.

In between detecting "Q" and "G," the program utilizes a preorder traversal algorithm to build the tree, and several conditions are checked to ensure the tree is being filled out correctly. Subsequently, the data file must be constructed accordingly to allow the program to run correctly. 

After running through each line in the data file and successfully building the tree, the user can begin playing the animal guessing game with the program. The tree comprises of animal nodes that include space for a question, an animal guess, and two pointers: a yes pointer (if the answer is yes) and a no pointer (if otherwise).

If the program wins, the user can either play again or not. However, if the program loses, the user will be asked what animal the user was thinking of. The program will then ask the user to enter a question that will differentiate the program's animal guess from the animal the user was thinking of. Finally, this additional information is added to the tree and saved in the game data file using a preorder tree traversal.






## Challenges

One of the biggest challenges to this project was figuring out how to make the program find another branch to fill in the tree after coming to a "dead end," with both the yes and no pointers pointing to nodes with only animal guesses. I overcame this issue by assigning certain nodes in the tree a specific variable so I could go back to them (since they are all dynamically created). Doing this facilitated my progress in developing a working algorithm to identify a tree branch that needs to be filled in the program.
## Installation & Build Instructions

You can download the project files, ensure CMake is setup on your system/IDE, and edit the CMakePresets.json file, if needed.

It is also important to note that the location of where the program reads the default game data text file may vary depending on your build configuration.
