# 2020-pd2-sokoban
## 1. Video link
### https://youtu.be/cZB5rtYALdU

## 2. How to play
### Controls
**Up**:         **W** or **UP** key

**Down**:       **S** or **DOWN** key

**Left**:       **A** or **LEFT** key

**Right**:      **D** or **RIGHT** key

**Explode**:    **BACKSPACE** or **DELETE** key (on Mac)
### Items
**Player**: Creeper

**Box**: TNT block

**Storage location**: Blue round dot on the ground

## 3. Features
### Main menu
**START**:      Starts game on selected level.

**RESUME**:     Resumes to saved game (if there is one).

**SELECT LVL**: Selects the level in which the game will start on.

**QUIT**:       Exits application.
### Saved game
**Objective**: Saves the game progress so the user can later return by clicking
the RETURN button in the main menu.

**How**: The game data is stored in a txt file that is saved in the build folder.
It is then read when RETURN is clicked.

**Saved data**: Game level, player position, box positions, current step count
### Show number of steps
The number of steps is displayed in the top right corner of the in-game side menu.

## 4. Bonus
### Music & sound effects
**Background music**: Played when the user enters the main menu and continues
playing in the game. Will repeat after music finishes.

**Sound effects**: 
1. Thud when a box is pushed over a storage location
2. Win game cheering
3. Creeper explosion (when the cheat code is activated)

### Cheat code (player can blow up walls)
If the user enters "*creeper*" in the input bar of the in-game side menu, the user can
blow up walls in front of, to the left & right and behind the player by
pressing **BACKSPACE** or **DELETE** (on Mac).
### In-game side menu
Contains:
1. Counter for number of steps taken
2. Cheat code input bar
3. BACK button (goes back to main menu)
4. SAVE button (saves game)
5. QUIT button (exits application)
