#include <iostream>
#include <conio.h>   // برای _getch و getch
#include <cstdlib>  // برای srand و system
#include <string>
#include <ctime>    // برای time
#include <windows.h>  // برای رنگ


/* <<<<<<< GITHUB LINK : https://github.com/MaT-Bh1221/MAZE >>>>>>> */

using namespace std;

// طول و عرض ماز 
const int H = 51;
const int W = 76;

int step_per_step = 10; //    سرعت پیشفرض روح ها
long long int step = 0; // تعداد جابه جایی کاراکتر
int HP = 3;
int last_player = 0; // اندیس بازیکن فعلی در لیست بازیکنان 
int char_xind = 1, char_yind = 1; // مکان اولیه کاراکتر 

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
    "*  *  *   **** ***** +---+  ***** *   *",
    "*  *  *  *       *   |   |  *   *  * * ",
    "****  *  ****    *   |   |  *****   *  ",
    "*  *  *     *    *   |   |  *  *    *  ",
    "*  *  * ****     *   +---+  *   *   *  "    
};

char menul[5][40] = {
    " /-----------------------------------\\ ",
    " |           1. START GAME           | ",
    " |           2. HISTORY              | ",
    " |           3. EXIT                 | ",
    " \\-----------------------------------/ "
};

char wonl[5][52] = {
    " *   *   ***   *   *  *           * +---+  *     * ",
    "  * *   *   *  *   *   *         *  |   |  * *   * ",
    "   *    *   *  *   *    *   *   *   |   |  *  *  * ",
    "   *    *   *  *   *     * * * *    |   |  *   * * ",
    "   *     ***    ***       *   *     +---+  *     * "
};

char lostl[5][49] = {
    " *   *   ***   *   *  *       ***    ****  *****",
    "  * *   *   *  *   *  *      *   *  *        *  ",
    "   *    *   *  *   *  *      *   *  *****    *  ",
    "   *    *   *  *   *  *      *   *      *    *  ",
    "   *     ***    ***   *****   ***   ****     *  "
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

void check_xp(bool iswon, int num){ //---------------------بررسی امتیاز--------------------
    int neg = 5; // مقدار امتیاز منفی 

    if(iswon){
        if(num == 3)
            player_xp[last_player] += 20;
        else if(num == 4)
            player_xp[last_player] += 25;
        else if(num == 5)
            player_xp[last_player] += 30;
    }

    else if(!iswon){
        if(HP == 2)
            player_xp[last_player] = max(0, player_xp[last_player]-neg);
        else if(HP == 1)
            player_xp[last_player] = max(0, player_xp[last_player]-neg);
        else if(HP == 0)
            player_xp[last_player] = 0;
    }
}

void color(int num){ // ---------------------رنگ متن ها---------------------
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
}
// -----------------------چاپ لوگو ها------------------------
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
    
    for(int x = 1, counter = 0, charcounter = 0; x <= 100; x++)
        if(!player_names[x-1].empty() && player_names[x-1] != "0"){
            counter++;

            color(3);
            cout << "  " << x << ". " << player_names[x-1] << "  --  XP : " << player_xp[x-1] << "\n";
            color(7);
        }
        else{
            if(counter == 0)
                cout << "\t  < LIST IS EMPTY >";
            break;
        }
    cout << "\n\n< press any key to back to main menu... >";

    char cmd = _getch();
    displayMenu();
}

int random(int min, int max){ // تابع تولید عدد رندوم در بازه دلخواه 
    return ((min) + rand() % (max - min + 1));
}

void spawn(int ghosts[][2], int num){ //---------------------اسپاون کردن روح ها--------------------
    srand(time(0));

    step = 0;
    char_xind = 1;
    char_yind = 1;

    for(int i = 0; i < num; i++){
        ghosts[i][0] = random(-4,55);
        ghosts[i][1] = random(-4,80);
        if(ghosts[i][0] == char_xind && ghosts[i][1] == char_yind)
            i--;
    }
}

bool won(){ // --------------------پیغام پیروزی-----------------
    system("cls");
    wonlogo();
    cout << "\npress any key to back to main menu...";
    char cmd = _getch();
    displayMenu();
    return true;
}

void lost(int ghosts[][2], int num){ //--------------------پیغام شکست-----------------
    HP--;
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
        spawn(ghosts, num);
    }
    check_xp(false, num);
}

void exit_g(){ // ---------------------ریست کردن اطلاعات پیشفرض برای خروج از بازی--------------------
    step = 0;
    char_xind = 1;
    char_yind = 1;
    player_xp[last_player] = 0;
    last_player = 0;
    HP = 3;
}

void check_ghosts(int ghosts[][2], int num){ //---------------------حرکت دادن روح ها--------------------
    if(step % step_per_step == 0){

        for(int i = 0; i < num; i++){
      
            if(ghosts[i][0] < char_xind)
                ghosts[i][0] += 1;
            else if(ghosts[i][0] > char_xind)
                ghosts[i][0] -= 1;

            if(ghosts[i][1] < char_yind)
                ghosts[i][1] += 1;
            else if(ghosts[i][1] > char_yind)
                ghosts[i][1] -= 1;

            if((ghosts[i][0] == char_xind && ghosts[i][1] == char_yind))     // برخورد روح با کاراکتر 
                lost(ghosts, num);
        }
    }
}

void show_map(int ghosts[][2], int num){  //---------------------چاپ ماز--------------------

    system("cls");
    check_ghosts(ghosts, num);

    int x = char_xind, y = char_yind; 
    
    for(int i = 0; i < H; i++){

        if(starting == false)
            break;

        if(i == 0){
            color(6);
            cout << "\n\nName : " << player_names[last_player] << "\t(HP : " << HP << " -- XP : " << player_xp[last_player] << " -- Steps : " << step << ")\tMove with W A S D | exit with 0" << "\n";
            color(7);
        }

        for(int j = 0; j < W; j++){
            bool map_cout = true; // اعتبار سنجی چاپ مپ یا روح

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
                    for(int g = 0; g < num; g++){ // بررسی موجود بودن روح ها در مکان مورد نظر 
                        if(i == ghosts[g][0] && j == ghosts[g][1]){
                            color(4); //red
                            cout << 'X';
                            color(7);
                            map_cout = false;
                            break;
                        }
                    }
                    if(map_cout){
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

void game(int p_idx, int ghosts[][2], int num) { //---------------------فرایند اجرای بازی-------------------
    spawn(ghosts, num);
    while(starting){
        
        show_map(ghosts, num);

        char cmd1 = _getch(); // برای اینکه ورودی کاربر را بدون نیاز به enter زدن بگیریم

        if (cmd1 == '0') { // خروج از بازی 
            system("cls");
            color(6);
            cout << "are you sure about back to main menu? your XPs will burn.(press y for exit)";
            color(7);
            char cmd1 = _getch();
            if(cmd1 == 'y' || cmd1 == 'Y'){
                displayMenu();
                exit_g();
                break;
            }
            else
                continue;
        }

        else if (cmd1 == 'w' || cmd1 == 'W') {
            step++;

            if(MAP[char_xind-1][char_yind] == 'O'){ // رسیدن به خط پایان 
                check_xp(won(), num);
                break;
            }
            // برخورد کاراکتر با روح 
            for(int u = 0; u < num; u++){
                if((char_xind-1 == ghosts[u][0] && char_yind == ghosts[u][1]) && MAP[char_xind][char_yind-1] == ' ')
                    lost(ghosts, num);
            }

            if(MAP[char_xind-1][char_yind] == ' '){ // قدر به حرکت بودن کاراکتر در فضای خالی
                char_xind -= 1;
            }
        }

        else if (cmd1 == 's' || cmd1 == 'S') {
            step++;

            if(MAP[char_xind+1][char_yind] == 'O'){
                check_xp(won(), num);
                break;
            }

            for(int u = 0; u < num; u++){
                if((char_xind+1 == ghosts[u][0] && char_yind == ghosts[u][1]) && MAP[char_xind+1][char_yind] == ' ')
                    lost(ghosts, num);
            }

            if(MAP[char_xind+1][char_yind] == ' '){
                char_xind += 1;
            }
        }

        else if (cmd1 == 'a' || cmd1 == 'A') {
            step++;

            if(MAP[char_xind][char_yind-1] == 'O'){
                check_xp(won(), num);
                break;
            }
 
            for(int u = 0; u < num; u++){
                if((char_xind == ghosts[u][0] && char_yind-1 == ghosts[u][1]) && MAP[char_xind][char_yind-1] == ' ')
                    lost(ghosts, num);
            }

            if(MAP[char_xind][char_yind-1] == ' '){
                char_yind -= 1;
            }
        }

        else if (cmd1 == 'd' || cmd1 == 'D') {
            step++;

            if(MAP[char_xind][char_yind+1] == 'O'){
                check_xp(won(), num);
                break;
            }

            for(int u = 0; u < num; u++){
                if((char_xind == ghosts[u][0] && char_yind+1 == ghosts[u][1]) && MAP[char_xind][char_yind+1] == ' ')
                    lost(ghosts, num);
            }

            if(MAP[char_xind][char_yind+1] == ' '){
                char_yind += 1;
            }
        }

        else{ // با فشردن کلید اشتباه نیز یک حرکت برای کاربر در نظر گرفته میشود 
            step++;
            continue;
        }
    }
}
int startGame_name(){ //-------------------گرفتن نام کاربر برای اجرای بازی-----------------

    system("cls"); // پاک کردن صفحه 
    string name;
    int counter = 0;

    color(6);
    cout << "enter your name(0 to back menu) : ";
    color(7);

    while(true){

        int counter = 0;
        getline(cin, name);

        for(char c : name)
            counter++;

        if(counter > 20){ // محدودیت تعداد کاراکتر های نام
            cout << "your name has more than 20 characters. enter a smaller name : ";
            continue;
        }

        if (name == "0"){
            displayMenu();
            return 101;
        }

        else{

            for (int i = 0; i < 100; i++) { // بررسی وجود پلیر از قبل 
                if(player_names[i] == name) {
                    return i;
                }
            }
            for (int i = 0; i < 100; i++) { // ثبت پلیر جدید 
                if(player_names[i].empty() || player_names[i] == "0") {
                    player_names[i] = name;
                    return i;
                }
            }
        }
        return -101;
    }
}

int ch_difficulty(){ // تعیین درجه سختی بازی 

    int num; // تعداد روح ها 

    color(1);
    cout << "choose difficulty level\n  [1]\t [2]\t [3]\n\t [0]";
    color(7);

    while(true){ // تعیین سرعت روح ها
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

    color(1);
    cout << "\n\nchoose number of ghosts\n  [3]\t [4]\t [5]\n\t [0]";
    color(7);

    while(true){ // تعین تعداد روح ها 
        char cmd1 = _getch();

        if(cmd1 == '3'){
            num = 3;
            break;
        }
        else if(cmd1 == '4'){
            num = 4;
            break;
        }
        else if(cmd1 == '5'){
            num = 5;
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

    return num;
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
                int num = ch_difficulty();
                if(num == 0){
                    player_names[ind] = "0";
                    displayMenu();
                    continue;
                }
                int ghosts[num][2]; // آرایه برای ذخیره مکان روح ها 
                starting = true;
                game(ind, ghosts, num);
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