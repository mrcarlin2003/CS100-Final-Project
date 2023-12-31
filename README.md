# 2048 Development Project
Authors: [Michael Carlin](https://github.com/mrcarlin2003), [Niko Udria](https://github.com/NikOhNo), [Matthew Cedeno](https://github.com/MCdialing14), and [Mark Sapugay](https://github.com/MarkSapugay).

## Project Description
A 2048 C++ game is interesting to us because we all have an interest of making games, and want to see how we can maximize the experience for the player while using terminal based navigation. We plan to use C++ for our project, while Unity and other options were considered, we decided the best course of action was C++. The input will be boxes sliding across the screen and the output will be boxes merging and adding up. We will also output a game over, leaderboard, and setting screens which are more like features. The features the project provides are the ability to restart the game when the player loses, an arcade style leaderboard, score keeping, and a quit game option in game.

## User Interface Specification
### Navigation Diagram
<p align="center">
  <img src="/Diagrams/NavigationDiagram.png?raw=true" alt="Navigation Diagram" height="350">
</p>
<p align="center">Navigation Diagram</p>
<p>This diagram displays how our game screens flow into each other. User's enter the program from where "start" is located. From here they can choose to start a new game, go into non-game menus like settings/ leaderboard/ credits, or quit the program. Some menus such as the settings or credits are simple and lead back into menu while others may have a circular pattern like the game and game over where users can keep restarting until they wish to break out by returning to mean or going to the leaderboard/ credits which also ultimately lead to the main menu. The goal is to have all paths lead back to the main menu so the user can easily quit the program or adjust settings at any time.</p>

### Screen Layouts
<img src="/Diagrams/ScreenLayout/MainMenu.png?raw=true" alt="Main Menu" height="350">
<p>This menu is intended to be a center of control for the game. From here, you can input which menu you would like to go to or quit the program. Many menus lead back to here.</p>

<img src="/Diagrams/ScreenLayout/UpdatedInGame.PNG?raw=true" alt="Game Menu" height="350">
<p>This menu is where the actual gameplay will occur. The user will input which direction they would like the blocks to slide, and they will either combine or collide, and the game area will update to reflect that. The user will also have the option to quit to the menu available at all times.</p>

<img src="/Diagrams/ScreenLayout/UpdatedGameOver.PNG?raw=true" alt="Game Over Menu" height="350">
<p>This menu will occur when the game has concluded (blocks have filled all spaces on the board and no possible moves that could combine). The final score will be calculated and displayed from the last board state. The user can input whether to start a new game, view the leaderboard, or return to the menu from here.</p>

<img src="/Diagrams/ScreenLayout/UpdatedLeaderboard.PNG?raw=true" alt="Leaderboard Menu" height="350">
<p>This menu will display the high scores for the game (either locally or online depending on time constraints). From here, users can input whether to return to the main menu or view credits.</p>

<img src="/Diagrams/ScreenLayout/CreditsMenu.png?raw=true" alt="Credits Menu" height="350">
<p>This is a simple menu that can be accessed either through the main menu or after a game. It simply directs back to the main menu upon input so users can start a new game or do any of the other options from there.</p>

<img src="/Diagrams/ScreenLayout/UpdatedSettings.PNG?raw=true" alt="Settings Menu" height="350">
<p>This menu allows users to specify the volume level (from 0 to 100) to play background music and sound effects at. The changes will only be staged until they are applied with the apply input, and the user can return to default settings if they make an unwanted change. It navigates back to the main menu.</p>

## Class Diagram
<p align="center">
  <img src="/Diagrams/FinalUMLDiagram.png?raw=true" alt="Class Diagram" height="700">
</p>
<p align="center">Class Diagram</p>
<p>This diagram lays out the way we want classes to control the logic of our game and menus. The abstract InputManager is what all menus derive from. Each menu should provide how they want to handle input as described in the screen layouts. The leaderboard is the most complicated menu though. It displays an array of Entry[] which are a simple pair of names and their highscore that get stored across sessions. For the gameplay related classes, there is the overhead game manager that controls the gameplay loop until the player loses (there is no winning in a game like 2048). The loop is essentially to spawn a block, check if the player lost (no possible moves to make), handle input, and use its child objects to shift the blocks. It creates the board and gives a reference of it to its child helper objects like block shifter or block spawener. Block spawner handles the logic to put new blocks on the board, while block shifter moves them in the direction of input (if such a move is possible which is why the shiftBlocks function returns a bool so we can recognize invalid moves and not progress the loop when necessary). The class coordinate is mostly used for the spawning of blocks. The spawner can analyze the board and find coordinates in the board that don't have a block. Then it will create a block with a random value of 2 or 4 and place it at one of those empty coordinates. And the block of course is the base of most of this functionality. Many classes work with it as described previously.</p>

### Updates to UML Class Diagram
**Block Shifter**  
We applied the single responsibility principle and open closed principle to better consider memory management and the openness to modifiability of our classes. Originally, this was going to be included in the board, but we thought it better to move it up to the game manager and let that system determine when to modify the board. The board should really just be a simple representation of where blocks are in the game, not responsible for moving its own blocks. We also changed it to use pointers to avoid double deallocations. This change decoupled the board and block shifter and also made it a much better tool for the game manager. It's clear that this class's purpose now is to shift blocks while maintaining the rules when asked rather than it being possible to shift within the board at any time.

**Block Spawner**  
This had a similar change to the Block Shifter and applied the same principles. It was also changed to use pointers to avoid making a copy of the board which would have caused double deallocations. The only responsibility it has is to add blocks to the _shared_ board passed around as a pointer under our conditions. This change helped define this class's role within the program much better as we now know the only thing it can and will do is add blocks to the shared board at random positions when asked.

**Board**  
Changes here once again mostly related to building its sense of the single responsibility principle and open closed principle. Functions were added that allow outside classes to view the values that were within it, but we very clearly closed off what we did not want changed such as the number of rows and columns. This change really helped us understand what the purpose of the board was rather than it being vague and performing unexpected behavior like shifting the blocks on its own.

**Input Manager**
The change here is the inclusion of another public function that can return the value of the protected variables of user input. This is a part of the single responsibility and open-closed principles in relation to SOLID. In order to compare the user input to a specific letter for menu navigation, we need to access the protected variables in the Input Manager class. In doing so we modify the class to perform another action related to input managing without removing another functionality. 

 ## Screenshots
 <img src="/Diagrams/InputOutputScreens/StartingScreen.PNG?raw=true" alt="Start Screen" height="350">
<p>The starting screen of our 2048 game. It takes in the char g, l, c, s, or q. </p>

<img src="/Diagrams/InputOutputScreens/cs100_2048_game_screen.png?raw=true" alt="In game Screen" height="350">
<p>The game screen takes in the inputs wasd as directional shifts of the board. </p>

<img src="/Diagrams/InputOutputScreens/cs100_2048_game_over_screen.png?raw=true" alt="Game over Screen" height="350">
<p>The game over takes in l, c, or m to advance to the next screen. </p>

<img src="/Diagrams/InputOutputScreens/LeaderboardScreen.PNG?raw=true" alt="Leaderboard Screen" height="350">
<p>The leaderboard takes in a name if called from game over and displays it in a ranking list. Then you can return to menu or view credits.</p>

<img src="/Diagrams/InputOutputScreens/CreditsScreen.PNG?raw=true" alt="Credits Screen" height="350">
<p>The credits screen displays the names of th developers and can return back to main menu. </p>

<img src="/Diagrams/InputOutputScreens/SettingsScreen.PNG?raw=true" alt="Settings Screen" height="350">
<p>The settings takes a multitude of inputs and updates values based on user inputs. </p>

 ## Installation/Usage
 <p>We use cmake . in the root directory and run make to create the executable in our bin folder. Then we run the command "./bin/game" to run and play the game.</p>

 ## Testing
 <p>We mostly ran the program through g-test and created a test for every function of the project. Some functions need more testing which we will do in more branches.</p>
 
