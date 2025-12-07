#include <iostream>
#include <conio.h>   // برای _getch و getch
#include <cstdlib>  // برای srand و system
#include <string>
#include <ctime>    // برای time
#include <windows.h>

using namespace std;

const int H = 51;
const int W = 76;
long int step = 0;

int last_player = 0;

int char_xind = 1, char_yind = 1;
int ghost1[2], ghost2[2], ghost3[2]; 

string player_names[100];

char MAP[H][W+1] = {
",-----------.-----------.--------------------.-----------.-----------------.",
"|           |           |                    |           |                 |",
"|O ,-----   |  ,-----.  |  .  ,-----------.  `--------   |  ,--.  .  ,--   |",
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
// He was here...
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

void color(int num){ // ---------------------رنگ متن ها---------------------
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
}

void displayMenu(){ // -----------------------چاپ منو------------------------
    system("cls");
    cout << "\n-------[MAZE-CORE]-------\n1. start new game\n2. game history\n3. exit\n[you] : ";
}

void won(){ // --------------------پیغام پیروزی-----------------
    system("cls");
    cout << "You Won!\npress any key to back to main menu...";
    char cmd = _getch();
    displayMenu();
}

void lost(){ //--------------------پیغام شکست-----------------
    system("cls");
    cout << "You Lost!\npress any key to back to main menu...";
    char cmd = _getch();
    displayMenu();
}

void reset_g(){
    char_xind = 1;
    char_yind = 1;
    player_names[last_player] = "0";
    last_player = 0;
}

void check_ghosts(){
    if(step % 10 == 0){
      
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
}

void show_map(int x, int y){  //---------------------چاپ ماز--------------------


    check_ghosts();

    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            if(i == x && j == y){
                cout << "@";
            }

            else{

                if(MAP[i][j] == 'O'){
                    color(2);
                    cout << MAP[i][j];
                    color(7);
                }

                else{

                    if((ghost1[0] == i && ghost1[1] == j) || (ghost2[0] == i && ghost2[1] == j) || (ghost3[0] == i && ghost3[1] == j)){
                        cout << 'x';
                    }
                    else{
                        color(3);
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

    while(true){
        system("cls");

        show_map(char_xind, char_yind);
        cout << "[MAZE-CORE] Move with W A S D  |  exit = 0" << endl;

        char cmd = _getch(); // برای اینکه ورودی کاربر را بدون نیاز به enter زدن بگیریم

        if (cmd == '0') {
            displayMenu();
            reset_g();
            break;
        }

        else if (cmd == 'w' || cmd == 'W') {
            if(MAP[char_xind-1][char_yind] == 32){
                char_xind -= 1;
                step++;
            }

            else if(MAP[char_xind-1][char_yind] == 'O'){
                won();
                break;
            }

            else if((char_xind-1 == ghost1[0] && char_yind == ghost1[1]) || (char_xind-1 == ghost2[0] && char_yind == ghost2[1]) || (char_xind-1 == ghost3[0] && char_yind == ghost3[1])){
                lost();
                break;
            }
        }

        else if (cmd == 's' || cmd == 'S') {
            if(MAP[char_xind+1][char_yind] == 32){
                char_xind += 1;
                step++;
            }

            else if(MAP[char_xind+1][char_yind] == 'O'){
                won();
                break;
            }

            else if((char_xind+1 == ghost1[0] && char_yind == ghost1[1]) || (char_xind+1 == ghost2[0] && char_yind == ghost2[1]) || (char_xind+1 == ghost3[0] && char_yind == ghost3[1])){
                lost();
                break;
            }
        }

        else if (cmd == 'a' || cmd == 'A') {
            if(MAP[char_xind][char_yind-1] == 32){
                char_yind -= 1;
                step++;
            }

            else if(MAP[char_xind][char_yind-1] == 'O'){
                won();
                break;
            }
 
            else if((char_xind == ghost1[0] && char_yind-1 == ghost1[1]) || (char_xind == ghost2[0] && char_yind-1 == ghost2[1]) || (char_xind == ghost3[0] && char_yind-1 == ghost3[1])){
                lost();
                break;
            }
        }

        else if (cmd == 'd' || cmd == 'D') {
            if(MAP[char_xind][char_yind+1] == 32){
                char_yind += 1;
                step++;
            }

            else if(MAP[char_xind][char_yind+1] == 'O'){
                won();
                break;
            }

            else if((char_xind == ghost1[0] && char_yind+1 == ghost1[1]) || (char_xind == ghost2[0] && char_yind+1 == ghost2[1]) || (char_xind == ghost3[0] && char_yind+1 == ghost3[1]) ){
                lost();
                break;
            }
        }

        else{
            step++;
            continue;
        }
    }
}

void displayHistory() { //-----------------------چاپ تاریخچه------------------
    system("cls");
    cout << "[MAZE-CORE-HISTORY]\n";

    int counter = 1;

    for(int x = 0; x < 100; x++)
        if(!player_names[x].empty() || player_names[x] != "0")
            cout << counter++ << ". " << player_names[x] << "\n";
    cout << "press any key to back to main menu...";

    char cmd = _getch();
    displayMenu();
}

int startGame_name(){ //-------------------گرفتن نام کاربر برای اجرای بازی-----------------

    system("cls"); // پاک کردن صفحه 
    string name;
    cout << "enter your name(0 to back menu) : ";
    getline(cin,name);

    if (name == "0"){
        displayMenu();
        return 101;
    }

    else{
    //========================مشخص کردن محل رندوم روح ها======================
        srand(time(0));

        ghost1[0] = - 5 + rand() % 60;
        ghost1[1] = - 5 + rand() % 80;
        ghost2[0] = - 5 + rand() % 60;
        ghost2[1] = - 5 + rand() % 80;
        ghost3[0] = - 5 + rand() % 60;
        ghost3[1] = - 5 + rand() % 80;

        for (int i = 0; i < 100; i++) {
            if (player_names[i].empty()) {
                player_names[i] = name;
                return i;
            }
        }
    }
}

int main() { //-------------------------اجرای برنامه-----------------------

    displayMenu();

    while(true){

        char choice = _getch();

        if(choice == '1'){
            int ind;
            last_player = ind;
            ind = startGame_name();
            if(ind == 101){
                displayMenu();
                continue;
            }
            else
                game(ind);
        }
        else if(choice == '2')
            displayHistory();

        else if(choice == '3'){
            system("cls");
            cout << "press 3 again if you sure about exit else press 0...\n";

            while(true){

                char cmd = _getch();

                    if(cmd == '3')
                        return 0;

                    else if(cmd == '0'){
                        displayMenu();
                        break;
                    }

                    else
                        cout << "invalid input(3.exit or 0.back)\n";
            }
        }

        else
            cout << "invalid input";
    }


    return 0;
}
