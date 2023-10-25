# C-Nerdle-Solver
C2 Assignment of C Programing Class (H), USTC



## Functions

Double-clicking the program, you may check the menu (which will be shown below)

```
Welcome to Nerdle Solver by Frigus27!
Select mode.
1. Play Nerdle
2. Start Nerdle Solver (Manually)
3. Watch the solver beats itself
4. Play today's online game
5. Auto-solve today's online game
6. Auto-solve today's online game IN BROWSER TAB
7. Exit
```

Selection 1,2,3,6 are the requirements in the assignment.

### 1. Play Nerdle

Play offline Nerdle game.

### 2. Start Nerdle Solver (Manually)

You choose a valid answer. The program gives its answer and you input the state of the answer (excluded, contained but misplaced & proper)

### 3. Watch the solver beats itself

You enter a "template" (which means the solution of the game), and let the program guess it with its algorithm.

### 4. Play today's online game

The program gets today's online game answer and you play it.

### 5. Auto-solve today's online game

The program gets today's online game answer and guess it with its algorithm.

### 6. Auto-solve today's online game IN BROWSER TAB (Only available in my computer)

You open a tab and place it in a specific area, and the program will try to solve it by clicking and detecting the color in specific positions defined in the configuration files.

## Commands in Console Window

Supported commands are shown below.

```
Usage: "D:\Personal Data\Documents\Homework\Freshman Autumn\Computer\C-Nerdle-Solver\main.exe" [commands]
Commands:
        --play Play Nerdle.
        --solve Start Nerdle Solver
        --play-by-itself: You enter a template and let it play by itself
        --play-online: Get the nerdle today and play.
        --solve-online: Get the nerdle today and solve it automatically
        -h/--help: Open this page
```

Note: Mode 6 doesn't have its command switch because we regard it a dangerous operation.

## Compilation

```shell
gcc.exe -fdiagnostics-color=always -g main.c -o main.exe -Wall -Werror -lwsock32 -lgdi32
```

## File Structure

If you want to use the program, you are supposed to keep the file structure as shown below:

```
main.exe (or in any name)
data/
|--- valid_expressions.txt
|--- answer_list.txt
|--- pos_list.txt
```

The file `valid_expressions.txt` keeps all the accepted input, `answer_list.txt` all the appropriate answers (used in the mode 1) and `pos_list.txt` all the positions that the program needed in the mode 6.

### valid_expressions.txt & answer_list.txt

These files save the accepted input and all the answers.

Every identity is treated as a "word" in order to adapt to our algorithm. Every line consists of only one word.

### pos_list.txt

The file saves all the positions that is required by Mode 6, wherein the program solve the game in a browser tab. The default data is for my own Microsoft Edge InPrivate Tab. If you want to adapt it to your browser, you may change its content by filling in the following structure.

The default data is shown below.

```
395 477 566 648 731 812 900 981
339 417 503 581 661 740
245 290 332 381 425 462 513 554 596 647
555
286 335 371 417 459 523 601
607
117 215
```

To explain the data, we introduce two concepts:

* **GDI pos:** The coordinate that is used in the GDI modules, which is the actual pixel position on the screen.
* **Cursor pos**: The coordinate that is used in `GetCursorPos` and `SetCursorPos` functions, referring to a type of scaled position for a screen. It may be changed when the scale percentage of a screen is changed.

Then we can talk about the data structure.

1. In line 1&2 we set the *GDI pos-es* of points where we check the color of a frame in Nerdle web tab. The number in the first line is about the x-coordinate of every columns of the Nerdle frame. The number in the second line is about the y-coordinate.

   e.g. To test the color of the frame $(3,4)$, we check the table and learn that we should check the color of the pixel $(566,581)$.

2. In line 3&4 we set the *Cursor pos-es* of points where we click the number buttons. The first line is the x-coordinate of every number button, and the second line (only one number) is for the y-coordinate of them.

3. In line 5&6 we set the *Cursor pos-es* where we click the operation buttons. The structure of it is similar to line 3&4.

4. In line 7 we set a *Cursor pos* where we click to activate the browser, preventing it from being deactivated and blocking our input.

## Algorithm

To solve a game, we use an algorithm related to Informational Entropy which is introduced by 3Blue1Brown in [his video](https://www.bilibili.com/video/BV1zZ4y1k7Jw). This video talks about Wordle, and I used it on Nerdle by storing all the possible answers as "words".

* All the possible answers are found by firstly classifying all their types by hand, and then brutally searching for it.

For the web module which is now excluded from the assignment requirement, we introduce python from external environment to fetch the answer of the day.

* You may found a deserted implementation with  `winsock`.  Why abandon it is for the reason that the original website is protected by CDN, and I could not get the IP address of its server, resulting that I cannot establish a channel between my client and the server.
* Due to the abolishment of the requirement, I will no longer maintain it but not removing it from my program. The function is left just for fun.

## Special Thanks

* My TAs. They offered a lot of help when I was implementing the web-related functions. Despite of the abolishment of the requirement, I am grateful to them for teaching me a lot of web-related techs.
* The boss of NSRL 8348. I struggled in the cafeteria for the assignment for about a month, and their coffee and the comfortable environment here helped ignited many of my ideas. The coffee here is tasty, and its cost is much less than those from USTC1958.
* My sleepless dormmates. Their relentlessly staying up to fight against their program designing homework ruthlessly spoiled my happy sleeping time, and I had to accompany them on their homework. This experience, though painful, actually helped fixed some bugs in my program due to my unfamiliarity of precise differences between C and C++, where I worked long before I entered the university.
