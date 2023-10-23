#include <stdio.h>
#include <string.h>
#include "nerdle.h"


bool exiting = false;
void helpTips(char program_name[]) {
    printf("Usage: \"%s\" [commands]\n", program_name);
    printf("Commands:\n\t--play Play Nerdle.\n\t--solve Start Nerdle Solver\n\t--play-by-itself: You enter a template and let it play by itself\n\t--play-online: Get the nerdle today and play.\n\t--solve-online: Get the nerdle today and solve it automatically\n\t-h/--help: Open this page\n");
}

void solveGame() {
    Word previous_situation_list[NERDLE_WORD_MAX_COUNT] = { 0 };
    int previous_situation_list_count = 0;
    long long current_score = 0;
    char selected_word[NERDLE_WORD_LENGTH + 1];
    //char state_input[INPUT_BUF_LENGTH] = { 0 }, state[NERDLE_WORD_LENGTH + 1] = { 0 };
    Word new_word = { 0 };

    printf("\nPLEASE USE CAPS LOCK\nE for Excluded, C for Contained but misplaced and P for Properly placed.\n\n");

    for (int index = 0; index < NERDLE_WORD_MAX_COUNT; index++) {
        printf("\n");
        bool succeeded = getNextGuess(previous_situation_list, previous_situation_list_count, selected_word, &current_score);

        if (succeeded == false) {
            printf("No hits found. Please check your input.");
            break;
        }
        else {
            new_word = formNotJudgedWord(selected_word);
            inputState(&new_word, printWord);

            if (isWordProper(new_word)) {
                printf("\n< Hurray!\n");
                break;
            }

            previous_situation_list[index] = new_word;
            previous_situation_list_count++;
        }
    }
}

void solveGameBrowser() {
    initDetectModule();
    Word previous_situation_list[NERDLE_WORD_MAX_COUNT] = { 0 };
    int previous_situation_list_count = 0;
    long long current_score = 0;
    char selected_word[NERDLE_WORD_LENGTH + 1];
    State current_states[NERDLE_WORD_LENGTH];
    //char state_input[INPUT_BUF_LENGTH] = { 0 }, state[NERDLE_WORD_LENGTH + 1] = { 0 };
    Word new_word = { 0 };

    printf("\nPlease open your browser tap, and press any key to start.");
    system("pause");

    for (int index = 0; index < NERDLE_WORD_MAX_COUNT; index++) {
        printf("[next guess computing]\n");
        bool succeeded = getNextGuess(previous_situation_list, previous_situation_list_count, selected_word, &current_score);

        if (succeeded == false) {
            printf("No hits found. Please check your input.");
            break;
        }
        else {
            new_word = formNotJudgedWord(selected_word);
            
            // send the word
            sendAnswer(selected_word);

            // get the state
            scanFrameStates();
            getLineStates(index, current_states);

            // form the word
            for (int i = 0; i < NERDLE_WORD_LENGTH; i ++) {
                new_word.cells[i].state = current_states[i];
            }

            if (isWordProper(new_word)) {
                printf("\n< Hurray!\n");
                break;
            }

            previous_situation_list[index] = new_word;
            previous_situation_list_count++;
        }
    }
    releaseDetectModule();
}

long long solveTemplate(char template_input[INPUT_BUF_LENGTH], bool doPrint) {
    Word word_list[NERDLE_WORD_MAX_COUNT] = { 0 };
    int word_list_count = 0;
    long long current_score = 0;
    char selected_word[NERDLE_WORD_LENGTH + 1];
    char template[NERDLE_WORD_LENGTH] = { 0 };
    Word current_word;
    strncpy(template, template_input, NERDLE_WORD_LENGTH);

    for (int i = 0; i < NERDLE_WORD_MAX_COUNT; i++) {
        bool succeeded = getNextGuess(word_list, word_list_count, selected_word, &current_score);

        if (succeeded == false) {
            printf("No appropriate answer found!\n");
            break;
        }

        current_word = judgeWord(selected_word, template);
        if (doPrint) {
            printWord(current_word);
            printf("\n\n");
        }

        if (isWordProper(current_word)) {
            if (doPrint) {
                printf("SUCCESS!\n");
            }
            return i + 1;
        }
        else {
            word_list[i] = current_word;
            word_list_count++;
        }
    }
    return 1145141919810;
}



long long playTemplate(char template_input[INPUT_BUF_LENGTH], bool doPrint) {
    char selected_word[NERDLE_WORD_LENGTH + 1];
    char template[NERDLE_WORD_LENGTH] = { 0 };
    Word current_word;
    strncpy(template, template_input, NERDLE_WORD_LENGTH);

    printf("\n\n");
    for (int i = 0; i < NERDLE_WORD_MAX_COUNT; i++) {
        while (true) {
            memset(selected_word, 0, sizeof(selected_word));
            inputWord(selected_word, printWord);

            if (isWordInBank(selected_word)) {
                printf("\r                                          \r");
                break;
            }


            //FILE *notstdout = fopen("1.log","w+");
            //fprintf(notstdout, "%s", selected_word);
            //fclose(notstdout);


            printf("  <-- This input does not compute!");
        }

        current_word = judgeWord(selected_word, template);
        if (doPrint) {
            printf("\r");
            printWord(current_word);
            printf("\n\n");
        }

        if (isWordProper(current_word)) {
            if (doPrint) {
                printf("SUCCESS!\n");
            }
            return i + 1;
        }
    }
    return 1145141919810;
}

void playGame() {
    char template[128] = { 0 };
    pickTemplate(template);
    playTemplate(template, true);
}

void playByItself() {
    bool flag = true;
    char template_input[INPUT_BUF_LENGTH] = { 0 };
    do {
        printf("Enter template: ");
        scanf("%s", template_input);
        flag = isWordInputValid(template_input);
        if (flag == true) {
            break;
        }
        else {
            printf("This input does not compute! ");
        }
    } while (true);
    solveTemplate(template_input, true);
}

void solveOnline() {
    char buf[INPUT_BUF_LENGTH] = { 0 };
    getNerdleToday(buf);
    solveTemplate(buf, true);
}

void playOnline() {
    char buf[INPUT_BUF_LENGTH] = { 0 };
    getNerdleToday(buf);
    playTemplate(buf, true);
}

void benchmark() {
    long long sum;
    for (int i = 0; i < TOTAL_WORD_COUNT; i++) {
        sum += solveTemplate(TotalWordList[i], false);
        printf("\r%2.2lf %d/%d\tavg:%.2lf", (double)i / TOTAL_WORD_COUNT * 100, i, TOTAL_WORD_COUNT, (double)sum / i);
    }
    printf("\n%lf\n", (double)sum / TOTAL_WORD_COUNT);
}

void bye() {
    exiting = true;
    printf("Bye!\n");
}

void start() {
    system("cls");
    printf("Welcome to Nerdle Solver by Frigus27!\nSelect mode.\n1. Play Nerdle\n2. Start Nerdle Solver (Manually)\n3. Watch the solver beats itself\n4. Play today's online game\n5. Auto-solve today's online game\n6. Auto-solve today's online game IN BROWSER TAB\n7. Exit\n");
    switch (getch()) {
    case '1':
        playGame();
        break;
    case '2':
        solveGame();
        break;
    case '3':
        playByItself();
        break;
    case '4':
        playOnline();
        break;
    case '5':
        solveOnline();
        break;
    case '6':
        solveGameBrowser();
        break;
    case '7':
        bye();
        break;
    default:
        break;
    }
}


int main(int argc, char* argv[]) {
    initWordList();
    initPos();
    if (argc == 1) {
        while (!exiting) {
            start();
            system("pause");
        }
    }
    else if (argc == 2 && strcmp(argv[1], "--play") == 0) {
        solveGame();
    }
    else if (argc == 2 && strcmp(argv[1], "--solve") == 0) {
        solveGame();
    }
    else if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        helpTips(argv[0]);
    }
    else if (argc == 2 && strcmp(argv[1], "--play-by-itself") == 0) {
        playByItself();
    }
    else if (argc == 2 && strcmp(argv[1], "--play-online") == 0) {
        playOnline();
    }
    else if (argc == 2 && strcmp(argv[1], "--solve-online") == 0) {
        solveOnline();
    }
    /*
    else if (argc == 2 && strcmp(argv[1], "--benchmark") == 0) {
        benchmark();
    }
    */
    else {
        printf("Wrong arguments.\n");
        helpTips(argv[0]);
    }
    return 0;
}