#include <iostream>
#include <conio.h>   // برای _getch و getch
#include <cstdlib>  // برای srand و system
#include <string>
#include <ctime>    // برای time
#include <windows.h>  // برای رنگ
using namespace std;
// طول و عرض ماز 
const int H = 51;
const int W = 76;

int step_per_step = 10; //    سرعت پیشفرض روح ها
long long int step = 0; // تعداد جابه جایی کاراکتر
int HP = 3;
int last_player = 0; // اندیس بازیکن فعلی در لیست بازیکنان 
int char_xind = 1, char_yind = 1; // مکان اولیه کاراکتر 
int ghost1[2], ghost2[2], ghost3[2]; // آرایه برای ذخیره مکان روح ها 

bool starting; // اعتبارسنجی اجرای بازی شروع و پایان بازی 

int player_xp[100] = {}; // امتیاز هر بازیکن 
string player_names[100]; // لیست بازیکنان 

char maze[5][40] = {
    " ***     ***      *     ******   ***** ",
    " *  *   *  *     * *        *    *     ",
    " *   * *   *    *****      *     ***** ",
    " *    *    *   *     *    *      *     ",
    " *         *  *       *  ******  ***** "
};

char historyl[5][40] = {
    " *  *  *  **** ***** *****  ***** *   *",
    " *  *  *  *      *   |   |  *   *  * * ",
    " ****  *  ****   *   |   |  *****   *  ",
    " *  *  *     *   *   |   |  *  *    *  ",
    " *  *  *  ****   *   *****  *   *   *  "    
};

char menul[5][40] = {
    " /-----------------------------------\\ ",
    " |           1. START GAME           | ",
    " |           2. HISTORY              | ",
    " |           3. EXIT                 | ",
    " \\-----------------------------------/ "
};

char wonl[5][52] = {
    " *   *  *****  *   *  *           * *****  *     * ",
    "  * *   *   *  *   *   *         *  *   *  * *   * ",
    "   *    *   *  *   *    *   *   *   *   *  *  *  * ",
    "   *    *   *  *   *     * * * *    *   *  *   * * ",
    "   *    *****  *****      *   *     *****  *     * "
};

char lostl[5][49] = {
    " *   *  *****  *   *  *      *****  *****  *****",
    "  * *   *   *  *   *  *      *   *  *        *  ",
    "   *    *   *  *   *  *      *   *  *****    *  ",
    "   *    *   *  *   *  *      *   *      *    *  ",
    "   *    *****  *****  *****  *****  *****    *  "
};

char MAP[H][W+1] = {
",-----------.-----------.--------------------.-----------.-----------------.",
"|           |           |                    |           |                 |",
"|  ,-----   |  ,-----.  |  .  ,-----------.  `--------   |  ,--.  .  ,--   |",
"|  |        |  |     |  |  |  |           |              |  |  |  |  |     |",
"|  |  ,-----'  |  .  |  |  `--\"--------.  \"  ,-----------'  \"  |  `--\"-----:",
"|  |  |        |  |  |  |              |     |                 |           |",
"|  |  |   --.  |  `--:  |  ,--------.  |  ,--:  ,--.-----------\"--------   |",
"|  |  |     |  |     |  |  |        |  |  |  |  |  |                       |",
"|  |  `-----'  |   --'  |  `-----   |  |  |  |  |  |  ,--------.--------.  |",
"|  |           |        |           |  |  |  |  |  |  |        |        |  |",
"|  `-----------\"-----.  `-----------:  |  \"  |  |  |  |  ,--   |  ,--.  |  |",
"|                    |              |  |     |  |  |  |  |     |  |  |  |  |",
"|  ,--------------.  :-----------.  |  `-----:  |  |  |  `-----'  \"  |  |  |",
"|  |              |  |           |  |        |  |  |  |              |  |  |",
"|  |  ,--------.  |  |  ,-----.  |  :-----   |  |  |  `--------------:  \"  |",
"|  |  |        |  |  |  |     |  |  |        |  |  |                 |     |",
"|  |  `-----   |  |  |  |  .  |  |  |  ,-----'  |  `--------------.  `-----:",
"|  |           |  |  |  |  |  |  |  |  |        |                 |        |",
"|  `-----------'  |  |  |  |  |  |  |  |  ,-----'  ,-----------.  :--.  .  |",
"|                 |  |  |  |  |  |  |  |  |        |           |  |  |  |  |",
":-----------------'  |  |  |  |  |  |  |  |  ,--.  |   -----.  |  |  |  |  |",
"|                    |  |  |  |  |  |  |  |  |  |  |        |  |  |  |  |  |",
"|  ,--------   ,-----:  |  |  \"  |  |  |  |  \"  |  |  ,-----'  |  \"  |  |  |",
"|  |           |     |  |  |     |  |  |  |     |  |  |        |     |  |  |",
"|  `-----------'  .  :--'  `-----'  \"  |  :--.  |  :--'  ,--   `--.  |  |  |",
"|                 |  |                 |  |  |  |  |     |        |  |  |  |",
"|  ,-----.--------'  |   -----.   --.  |  |  \"  |  |   --\"--------'  |  |  |",
"|  |     |           |        |     |  |  |     |  |                 |  |  |",
"|  `--   |  ,-----.  :--------\"-----\"--'  |   --:  :-----------------'  |  |",
"|        |  |     |  |                    |     |  |                    |  |",
":-----.  |  |   --:  |  ,-----------.-----\"-----'  |  ,--.--------------'  |",
"|     |  |  |     |  |  |           |              |  |  |                 |",
"|  .  |  |  |  .  \"  |  :--------   `--   ,-----.  |  |  |  ,-----------.--:",
"|  |  |  |  |  |     |  |                 |     |  |  |  |  |           |  |",
"|  `--:  |  `--\"-----'  \"  .  ,--   ,-----'   --'  |  |  \"  |  .   --.  \"  |",
"|     |  |                 |  |     |              |  |     |  |     |     |",
"|  .  |  :-----.-----------\"--\"-----\"--.   --------:  :--.  `--\"--.  `-----:",
"|  |  |  |     |                       |           |  |  |        |        |",
"|  |  |  |  .  |  ,-----------------.  `-----------'  |  `--.--.  |  ,--.  |",
"|  |  |  |  |  |  |                 |                 |     |  |  |  |  |  |",
"|  `--'  |  `--:  |  ,--------------\"--------------.--'  .  |  |  |  |  |  |",
"|        |     |  |  |                             |     |  |  |  |  |  |  |",
"|  ,-----'  .  |  |  |  ,--------.-----.  ,-----.  |  .  |  |  |  |  |  |  |",
"|  |        |  |  |  |  |        |     |  |     |  |  |  |  |  |  |  |  |  |",
"|  `--------:  |  |  |  |  .  .  `--   |  |   --'  |  |  |  \"  |  |  |  |  |",
"|           |  |  |  |  |  |  |        |  |        |  |  |     |  |  |  |  |",
":--------.  |  |  |  \"  `--'  :--------:  |   -----:  |  `-----'  |  \"  |  |",
"|        |  |  |  |           |        |  |        |  |           |     |  |",
"|   -----'  \"  |  `-----------'   --.  |  `--------'  `-----.   --\"-----'  |",
"|              |                    |  |                    |              |",
"`--------------\"--------------------'O `--------------------\"--------------'"
};

void check_xp(bool iswon){ //---------------------بررسی امتیاز--------------------
    if(iswon)
        player_xp[last_player] += 20;
    else if(!iswon){
        if(HP == 2)
            player_xp[last_player] = max(0, player_xp[last_player]-5);
        else if(HP == 1)
            player_xp[last_player] = max(0, player_xp[last_player]-5);
        else if(HP == 0)
            player_xp[last_player] = 0;
    }
}

void color(int num){ // ---------------------رنگ متن ها---------------------
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
}
// -----------------------چاپ دیزاین ها------------------------
void mazelogo(){
    system("cls");
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 40; j++){
            color(4);
            cout << maze[i][j];
            color(7);
        }
        cout << "\n";
    }
    cout << "\n";
}

void displayMenu(){
    mazelogo();
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 40; j++){
            color(3);
            cout << menul[i][j];
            color(7);
        }
        cout << "\n";
    }
}

void historylogo(){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 40; j++){
            color(2);
            cout << historyl[i][j];
            color(7);
        }
        cout << "\n";
    }
    cout << "\n";
}

void wonlogo(){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 52; j++){
            color(2);
            cout << wonl[i][j];
            color(7);
        }
        cout << "\n";
    }
    cout << "\n"; 
}

void lostlogo(){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 49; j++){
            color(4);
            cout << lostl[i][j];
            color(7);
        }
        cout << "\n";
    }
    cout << "\n"; 
}
//-----------------------چاپ تاریخچه------------------
void displayHistory(){ 
    mazelogo();
    historylogo();

    for(int x = 1; x <= 100; x++)
        if(!player_names[x-1].empty() && player_names[x-1] != "0"){
            color(3);
            cout << "\t" << x << ". " << player_names[x-1] << "\t\tXP : " << player_xp[x-1] << "\n";
            color(7);
        }
        else
            break;

    cout << "press any key to back to main menu...";

    char cmd = _getch();
    displayMenu();
}

bool won(){ // --------------------پیغام پیروزی-----------------
    system("cls");
    wonlogo();
    cout << "\npress any key to back to main menu...";
    char cmd = _getch();
    displayMenu();
    return true;
}

bool lost(){ //--------------------پیغام شکست-----------------
    system("cls");
    if(HP == 0){
        lostlogo();
        cout << "\npress any key to back to main menu...";
        char cmd = _getch();
        displayMenu();
        starting = false;
    }
    else if(HP > 0){
        lostlogo();
        cout << "\npress any key to try again...\n";
        char cmd = _getch();
        system("cls");
    }
    return false;
}

void exit_g(){ // ---------------------ریست کردن اطلاعات پیشفرض برای خروج از بازی--------------------
    step = 0;
    char_xind = 1;
    char_yind = 1;
    last_player = 0;
    HP = 3;
}

void spawn(){ //---------------------اسپاون کردن روح ها--------------------
    srand(time(0));
    step = 0;

    char_xind = 1;
    char_yind = 1;

    ghost1[0] = - 5 + rand() % 60;
    ghost1[1] = - 5 + rand() % 80;
    ghost2[0] = - 5 + rand() % 60;
    ghost2[1] = - 5 + rand() % 80;
    ghost3[0] = - 5 + rand() % 60;
    ghost3[1] = - 5 + rand() % 80;
}

void check_ghosts(){ //---------------------حرکت دادن روح ها--------------------
    if(step % step_per_step == 0){
      
        if(ghost1[0] < char_xind)
            ghost1[0] += 1;
        else if(ghost1[0] > char_xind)
            ghost1[0] -= 1;

        if(ghost1[1] < char_yind)
            ghost1[1] += 1;
        else if(ghost1[1] > char_yind)
            ghost1[1] -= 1;
//============================================
        if(ghost2[0] < char_xind)
            ghost2[0] += 1;
        else if(ghost2[0] > char_xind)
            ghost2[0] -= 1;

        if(ghost2[1] < char_yind)
            ghost2[1] += 1;
        else if(ghost2[1] > char_yind)
            ghost2[1] -= 1;
//============================================
        if(ghost3[0] < char_xind)
            ghost3[0] += 1;
        else if(ghost3[0] > char_xind)
            ghost3[0] -= 1;

        if(ghost3[1] < char_yind)
            ghost3[1] += 1;
        else if(ghost3[1] > char_yind)
            ghost3[1] -= 1;
    }
    // برخورد روح با کاراکتر 
    if((ghost1[0] == char_xind && ghost1[1] == char_yind) || (ghost2[0] == char_xind && ghost2[1] == char_yind) || (ghost3[0] == char_xind && ghost3[1] == char_yind)){
        HP--;
        check_xp(lost());
        if(HP > 0)
            spawn();
    }
}

void show_map(){  //---------------------چاپ ماز--------------------

    system("cls");
    check_ghosts();

    int x = char_xind, y = char_yind; 

    color(6);
    cout << "\n\nName : " << player_names[last_player] << "\tHP : " << HP << "\t\tXP : " << player_xp[last_player] << "\t\tSteps : " << step << "\tMove with W A S D | exit with 0" << "\n";
    color(7);
    
    for(int i = 0; i < H; i++){
        if(starting == false)
            break;
        for(int j = 0; j < W; j++){
            if(i == x && j == y){
                color(6); //yellow
                cout << "@";
                color(7); //white
            }

            else{
                if(MAP[i][j] == 'O'){
                    color(2); //green
                    cout << MAP[i][j];
                    color(7);
                }

                else{
                    if((ghost1[0] == i && ghost1[1] == j) || (ghost2[0] == i && ghost2[1] == j) || (ghost3[0] == i && ghost3[1] == j)){
                        color(4); //red
                        cout << 'X';
                        color(7);
                    }
                    else{
                        color(3); //blue
                        cout << MAP[i][j];
                        color(7);
                    }
                }               
            }
        }
        cout << "\n";
    }
}

void game(int p_idx) { //---------------------فرایند اجرای بازی-------------------
    
    while(starting){
        
        show_map();

        char cmd1 = _getch(); // برای اینکه ورودی کاربر را بدون نیاز به enter زدن بگیریم

        if (cmd1 == '0') { // خروج از بازی 
            system("cls");
            color(6);
            cout << "are you sure about back to main menu? your XPs will burn.(press y for exit)";
            color(7);
            char cmd1 = _getch();
            if(cmd1 == 'y' || cmd1 == 'Y'){
                displayMenu();
                player_xp[last_player] = 0;
                exit_g();
                break;
            }
            else
                continue;
        }

        else if (cmd1 == 'w' || cmd1 == 'W') {
            step++;

            if(MAP[char_xind-1][char_yind] == 'O'){
                check_xp(won());
                break;
            }
            // برخورد کاراکتر با روح 
            else if(((char_xind-1 == ghost1[0] && char_yind == ghost1[1]) || (char_xind-1 == ghost2[0] && char_yind == ghost2[1]) || (char_xind-1 == ghost3[0] && char_yind == ghost3[1])) && MAP[char_xind][char_yind-1] == ' '){
                HP--;
                check_xp(lost());
                if(HP == 0)
                    break;
                else
                    spawn();
            }

            if(MAP[char_xind-1][char_yind] == ' '){
                char_xind -= 1;
            }
        }

        else if (cmd1 == 's' || cmd1 == 'S') {
            step++;

            if(MAP[char_xind+1][char_yind] == 'O'){
                check_xp(won());
                break;
            }

            else if(((char_xind+1 == ghost1[0] && char_yind == ghost1[1]) || (char_xind+1 == ghost2[0] && char_yind == ghost2[1]) || (char_xind+1 == ghost3[0] && char_yind == ghost3[1])) && MAP[char_xind+1][char_yind] == ' '){
                HP--;
                check_xp(lost());
                if(HP == 0)
                    break;
                else
                    spawn();
            }

            if(MAP[char_xind+1][char_yind] == ' '){
                char_xind += 1;
            }
        }

        else if (cmd1 == 'a' || cmd1 == 'A') {
            step++;

            if(MAP[char_xind][char_yind-1] == 'O'){
                check_xp(won());
                break;
            }
 
            else if(((char_xind == ghost1[0] && char_yind-1 == ghost1[1]) || (char_xind == ghost2[0] && char_yind-1 == ghost2[1]) || (char_xind == ghost3[0] && char_yind-1 == ghost3[1])) && MAP[char_xind][char_yind-1] == ' '){
                HP--;
                check_xp(lost());
                if(HP == 0)
                    break;
                else
                    spawn();
            }

            if(MAP[char_xind][char_yind-1] == ' '){
                char_yind -= 1;
            }
        }

        else if (cmd1 == 'd' || cmd1 == 'D') {
            step++;

            if(MAP[char_xind][char_yind+1] == 'O'){
                check_xp(won());
                break;
            }

            else if(((char_xind == ghost1[0] && char_yind+1 == ghost1[1]) || (char_xind == ghost2[0] && char_yind+1 == ghost2[1]) || (char_xind == ghost3[0] && char_yind+1 == ghost3[1])) && MAP[char_xind][char_yind+1] == ' '){
                HP--;
                check_xp(lost());
                if(HP == 0)
                    break;
                else
                    spawn();
            }

            if(MAP[char_xind][char_yind+1] == ' '){
                char_yind += 1;
            }
        }

        else{
            step++;
            continue;
        }
    }
}
int startGame_name(){ //-------------------گرفتن نام کاربر برای اجرای بازی-----------------

    system("cls"); // پاک کردن صفحه 
    string name;

    color(6);
    cout << "enter your name(0 to back menu) : ";
    color(7);

    getline(cin, name);

    if (name == "0"){
        displayMenu();
        return 101;
    }

    else{
    //========================ذخیره نام و اسپاون کاراکتر ها======================
        spawn();

        for (int i = 0; i < 100; i++) {
            if(player_names[i] == name) {
                return i;
            }
        }
        for (int i = 0; i < 100; i++) {
            if(player_names[i].empty() || player_names[i] == "0") {
                player_names[i] = name;
                return i;
            }
        }
    }
    return -101;
}

int ch_difficulty(){ // تعیین درجه سختی بازی 

    color(1);
    cout << "choose difficulty level\n  [1]\t [2]\t [3]\n\t [0]";
    color(7);

    while(true){
        char cmd1 = _getch();

        if(cmd1 == '1'){
            step_per_step = 10;
            break;
        }
        else if(cmd1 == '2'){
            step_per_step = 5;
            break;
        }
        else if(cmd1 == '3'){
            step_per_step = 3;
            break;
        }
        else if(cmd1 == '0'){
            return 0;
        }
        else{
            color(6);
            cout << "\n[MAZE CORE] : invalid input";
            color(7);
        }
    }
    return 1;
}

int main() { //-------------------------اجرای برنامه-----------------------

    displayMenu();

    while(true){

        char choice = _getch();

        if(choice == '1'){
            int ind = startGame_name();
            last_player = ind;
            if(ind == 101){
                displayMenu();
                continue;
            }
            else if(ind == -101){ // پیغام پر شدن لیست بازیکن ها 

                color(6);
                cout << "players list is full. press any key to back main menu...";
                color(7);

                char cmd = _getch();
                displayMenu();
                continue;
            }
            else{
                int v = ch_difficulty();
                if(v == 0){
                    player_names[ind] = "0";
                    displayMenu();
                    continue;
                }
                starting = true;
                game(ind);
            }
        }
        else if(choice == '2')
            displayHistory();

        else if(choice == '3'){
            system("cls");

            color(6);
            cout << "press 3 again if you sure about exit else press 0...\n";
            color(7);

            while(true){

                char cmd = _getch();

                    if(cmd == '3')
                        return 0;

                    else if(cmd == '0'){
                        displayMenu();
                        break;
                    }

                    else{
                        color(6);
                        cout << "[MAZE CORE] : invalid input(3.exit or 0.back)\n";
                        color(7);
                    }
            }
        }

        else{
            color(6);
            cout << "[MAZE CORE] : invalid input\n";
            color(7);
        }
    }

    return 0;
}
