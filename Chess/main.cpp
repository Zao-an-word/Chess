#include <graphics.h>
#include<iostream>
#include <conio.h>
#include<random>
#include<time.h>
#include<string>
#include<mmsystem.h>
#  pragma comment(lib,"winmm.lib")

#define w 40
using namespace std;
int who = 0;
int chess[15][15] = { 0 };
int v = 0;
int set = 0;
int ai = 2, aicol = 225;
int human = 1, humancol = 0;
int ri;
int lv = 4;
bool running = true;
//是否开始
bool is_game_started = false;
int humannum = 0;
int ainum = 0;
int emnum = 225;
int chessnum = 0;
//天元构建
void tiyu() {
    setfillcolor(RGB(0, 0, 0));
    solidcircle(8 * w, 8 * w, 7);
    solidcircle(4 * w, w * 4, 7);
    solidcircle(4 * w, 12 * w, 7);
    solidcircle(12 * w, 4 * w, 7);
    solidcircle(12 * w, 12 * w, 7);
}
//棋盘格子
void block() {
    setlinecolor(RGB(0, 0, 0));
    int n = 0;
    while (n <= 600) {
        int pts[] = { 40,n , 600, n };
        polyline((POINT*)pts, 2);
        n += w;
    }//格子构造
    n = 0;
    while (n <= 600) {
        int pts[] = { n ,40 , n , 600 };
        polyline((POINT*)pts, 2);
        n += w;
    }//格子构造
}
//文本展示
void text() {
    settextcolor(RGB(0, 0, 0));
    settextstyle(20, 0, _T("Consolas"));
    char a[15];
    for (int i = 0; i < 15; i++) {
        a[i] = 'A' + i;
        outtextxy(i * w + w, 20, a[i]);
    }
    int b;
    for (int i = 0; i < 15; i++) {
        b = i + 1;
        TCHAR s[3];
        _stprintf_s(s, _T("%d"), b);
        outtextxy(22, i * w + w, s);
    }
}
//棋子（已下）展示
void showpiece() {
    void piece(int x, int y, int who);
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (chess[i][j] == 1) {
                piece((i + 1) * w, (j + 1) * w, 0);
            }
            else if (chess[i][j] == 2) {
                piece((i + 1) * w, (j + 1) * w, 225);
            }
        }
    }
}

void level() {
    setfillcolor(RGB(100, 100, 100));
    fillrectangle(140, 610, 340, 630);
    setfillcolor(RGB(0, 0, 0));
    solidrectangle(140, 612, 140 + ri, 628);
    switch (lv) {
    case 1:
        solidcircle(3 * w, 15 * w + 20, 10);
        break;
    case 2:
        solidcircle(3 * w - 20, 15 * w + 20, 10);
        solidcircle(3 * w, 15 * w + 20, 10);
        break;
    case 3:
        solidcircle(3 * w - 20, 15 * w + 10, 10);
        solidcircle(3 * w, 15 * w + 10, 10);
        solidcircle(3 * w - 10, 15 * w + 30, 10);
        break;
    case 4:
        setfillcolor(RGB(225, 225, 225));
        solidcircle(3 * w, 15 * w + 20, 10);
        break;
    }
}

//竖直方向胜利方5子连线
void ver(int i, int j) {
    int wh = 0;
    int b = 0;
    setlinecolor(RED);
    for (int k = j; k < j + 5; k++) {
        if (chess[i][k] == 1) {
            wh++;
        }
        else if (chess[i][k] == 2) {
            b++;
        }
    }
    if (wh == 5) {
        v = 1;
        line(i * w + w, j * w + w, i * w + w, (j + 5) * w);
    }
    if (b == 5) {
        v = 2;
        line(i * w + w, j * w + w, i * w + w, (j + 5) * w);
    }
}
//横向胜利方5子连线
void cro(int i, int j) {
    int wh = 0;
    int b = 0;
    setlinecolor(RED);
    for (int k = i; k < i + 5; k++) {
        if (chess[k][j] == 1) {
            wh++;
        }
        else if (chess[k][j] == 2) {
            b++;
        }
    }
    if (wh == 5) {
        v = 1;
        line(i * w + w, j * w + w, (i + 5) * w, j * w + w);
    }
    if (b == 5) {
        v = 2;
        line(i * w + w, j * w + w, (i + 5) * w, j * w + w);
    }
}
//右下斜线胜利方5子连线
void xie1(int i, int j) {
    int wh = 0;
    int b = 0;
    setlinecolor(RED);
    for (int k = 0; k < 5; k++) {
        if (chess[i + k][j + k] == 1 && i + k < 15 && j + k < 15) {
            wh++;
        }
        else if (chess[i + k][j + k] == 2 && i + k < 15 && j + k < 15) {
            b++;
        }
    }
    if (wh == 5) {
        v = 1;
        line(i * w + w, j * w + w, (i + 5) * w, (j + 5) * w);
    }
    if (b == 5) {
        v = 2;
        line(i * w + w, j * w + w, (i + 5) * w, (j + 5) * w);
    }
}

void xie2(int i, int j) {
    int wh = 0;
    int b = 0;
    setlinecolor(RED);
    for (int k = 0; k < 5; k++) {
        if (i + k < 15 && j - k >= 0 && chess[i + k][j - k] == 1) {
            wh++;
        }
        else if (i + k < 15 && j - k >= 0 && chess[i + k][j - k] == 2) {
            b++;
        }
    }
    if (wh == 5) {
        v = 1;
        line(i * w + w, j * w + w, (i + 5) * w, (j - 5) * w);
    }
    if (b == 5) {
        v = 2;
        line(i * w + w, j * w + w, (i + 5) * w, (j - 5) * w);
    }
}//右上斜线胜利方5子连线
//判断是否满足胜利（不含棋子颜色）
int vic() {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            ver(i, j);
            cro(i, j);
            xie1(i, j);
            xie2(i, j);
        }
    }
    return v;
}
//背景设置
void bk() {
    setbkcolor(RGB(204, 129, 54));
    cleardevice();
    tiyu();
    level();
    block();
    text();
    showpiece();
}

int ck = 1;
void vicshow() {
    HWND hwnd = GetHWnd();
    int ret = 0;
    if (v == 1) {
        if (human == 1) {
            ri += 40;
            if (ri == 200) {
                ri = 0;
                lv++;
            }
        }
        else if (human == 2) {
            if (lv == 0) {
                ri += 40;
                if (ri == 200) {
                    ri = 0;
                    lv++;
                }
            }
        }
        // ensure victory line is visible, wait a bit before showing the dialog
        FlushBatchDraw();
        Sleep(1000);
        ret = MessageBox(hwnd, L"黑旗获胜\n选择下一局：\n是: 双人 对战\n否: 人机 对战\n取消: 退出", L"游戏结束", MB_YESNOCANCEL | MB_ICONQUESTION);
        if (ret == IDYES) {
            set = 1; // 双人
        } else if (ret == IDNO) {
            set = 2; // 人机
        } else {
            set = 0; // 退出
        }
    }
    else if (v == 2) {
        if (human == 2) {
            ri += 40;
            if (ri == 200) {
                ri = 0;
                lv++;
            }
        }
        else if (human == 1) {
            if (lv == 0) {
                ri += 40;
                if (ri == 200) {
                    ri = 0;
                    lv++;
                }
            }
        }
        // ensure victory line is visible, wait a bit before showing the dialog
        FlushBatchDraw();
        Sleep(1000);
        ret = MessageBox(hwnd, L"白旗获胜\n选择下一局：\n是: 双人 对战\n否: 人机 对战\n取消: 退出", L"游戏结束", MB_YESNOCANCEL | MB_ICONQUESTION);
        if (ret == IDYES) {
            set = 1; // 双人
        } else if (ret == IDNO) {
            set = 2; // 人机
        } else {
            set = 0; // 退出
        }
    }
    // break current match loop so main can switch modes or exit
    ck = 0;
}//胜利展示以及下一局重开


int close(int index) {
    int min = 15 * w;
    int result = 0;
    for (int i = 0; i < 15; i++) {
        if (min > (((i + 1) * w) - index) * (((i + 1) * w) - index)) {
            min = (((i + 1) * w) - index) * (((i + 1) * w) - index);
            result = i;
        }
    }
    return result;
}//求最近格点

void piece(int x, int y, int who) {
    setfillcolor(RGB(who, who, who));
    solidcircle(x, y, 16);
}//单个棋子
//一切清除
void clear() {
    who = 0;
    v = 0;
    ainum = 0;
    humannum = 0;
    chessnum = 0;
    emnum = 15 * 15;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            chess[i][j] = 0;
        }
    }
}


int humanscore[15][15] = { 0 };
int aiscore[15][15] = { 0 };
int dir[4][2] = { {0,1},{1,1},{0,1},{-1,1} };
int scoremap[15][15] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
0,1,2,2,2,2,2,2,2,2,2,2,2,1,0,
0,1,2,3,3,3,3,3,3,3,3,3,2,1,0,
0,1,2,3,4,4,4,4,4,4,4,3,2,1,0,
0,1,2,3,4,5,5,5,5,5,4,3,2,1,0,
0,1,2,3,4,5,6,6,6,5,4,3,2,1,0,
0,1,2,3,4,5,6,7,6,5,4,3,2,1,0,
0,1,2,3,4,5,6,6,6,5,4,3,2,1,0,
0,1,2,3,4,5,5,5,5,5,4,3,2,1,0,
0,1,2,3,4,4,4,4,4,4,4,3,2,1,0,
0,1,2,3,3,3,3,3,3,3,3,3,2,1,0,
0,1,2,2,2,2,2,2,2,2,2,2,2,1,0,
0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};
int scoremap_[15][15] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
0,1,2,2,2,2,2,2,2,2,2,2,2,1,0,
0,1,2,3,3,3,3,3,3,3,3,3,2,1,0,
0,1,2,3,4,4,4,4,4,4,4,3,2,1,0,
0,1,2,3,4,5,5,5,5,5,4,3,2,1,0,
0,1,2,3,4,5,6,6,6,5,4,3,2,1,0,
0,1,2,3,4,5,6,7,6,5,4,3,2,1,0,
0,1,2,3,4,5,6,6,6,5,4,3,2,1,0,
0,1,2,3,4,5,5,5,5,5,4,3,2,1,0,
0,1,2,3,4,4,4,4,4,4,4,3,2,1,0,
0,1,2,3,3,3,3,3,3,3,3,3,2,1,0,
0,1,2,2,2,2,2,2,2,2,2,2,2,1,0,
0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};


void begin() {
    initgraph(640, 640);
    BeginBatchDraw();
    ExMessage m;
    IMAGE img;	// 定义 IMAGE 对象
    loadimage(&img, _T("..\\resources\\hovered.jpg"));

    IMAGE img1; 
    loadimage(&img1, _T("..\\resources\\idel.jpg"));

    IMAGE img2;
    loadimage(&img2, _T("..\\resources\\hovered1.jpg"));
    IMAGE img3;
    loadimage(&img3, _T("..\\resources\\idel1.jpg"));
    IMAGE be;
    loadimage(&be, _T("..\\resources\\begin.jpg"));
    putimage(0, 0, &be);
    mciSendString(L"open ..\\resources\\Killigrew - Memories_H.ogg", 0, 0, 0);
    mciSendString(L"play ..\\resources\\Killigrew - Memories_H.ogg", 0, 0, 0);
    while (true)
    {
        // 获取一条鼠标或按键消息
        m = getmessage(EX_MOUSE | EX_KEY);
        if (m.message == WM_MOUSEMOVE) {
            if (m.x <= 11 * w && m.x >= 5 * w && m.y >= 6 * w && m.y <= 7 * w + 20) {
                putimage(5 * w, 6 * w, &img1);
            }
            else putimage(5 * w, 6 * w, &img);
            if (m.x <= 11 * w && m.x >= 5 * w && m.y >= 9 * w && m.y <= 10 * w + 20) {
                putimage(5 * w, 9 * w, &img3);
            }
            else putimage(5 * w, 9 * w, &img2);
        }
        if (m.message == WM_LBUTTONDOWN) {

            if (m.x <= 11 * w && m.x >= 5 * w && m.y >= 6 * w && m.y <= 7 * w + 20) {
                if (lv >= 1) set = 1;
                else set = 2;
            }
            if (m.x <= 11 * w && m.x >= 5 * w && m.y >= 9 * w && m.y <= 10 * w + 20) {
                set = 2;
            }
            break;
        }
        FlushBatchDraw();
    }
}//开始菜单

void setai() {
    int ret = MessageBoxA(0, "先手", "模式", MB_YESNO | MB_ICONQUESTION);
    if (ret == IDYES) {
        ai = 2, aicol = 225;
        human = 1, humancol = 0;
    }
    else {
        ai = 1, aicol = 0;
        human = 2, humancol = 225;
    }
}
//对（x,y）处的棋子进行评分
int cal_unit(int x, int y, int worb) {
    int sumscore = 0;
    char u, d, l, r, lu, ld, ru, rd;//u上 d下 l左 r右 lu左上 ld左下 ru右上 rd右下
    int row, col, count1, count2, count3, count4;   //1横 2竖 3斜上 4斜下
    count1 = count2 = count3 = count4 = 1;
    l = r = u = d = lu = ld = ru = rd = 0;
    chess[x][y] = worb;      //模拟下棋

    //横向
    row = x, col = y + 1;
    while (chess[row][col] == worb)
    {
        count1++;
        col++;
    }
    while (chess[row][col] == 0)
    {
        r++;
        col++;
    }
    row = x, col = y - 1;
    while (chess[row][col] == worb)
    {
        count1++;
        col--;
    }
    while (chess[row][col] == 0)
    {
        l++;
        col--;
    }


    //竖向
    row = x + 1, col = y;
    while (chess[row][col] == worb)
    {
        count2++;
        row++;
    }
    while (chess[row][col] == 0)
    {
        d++;
        row++;
    }
    row = x - 1, col = y;
    while (chess[row][col] == worb)
    {
        count2++;
        row--;
    }
    while (chess[row][col] == 0)
    {
        u++;
        row--;
    }

    //斜上
    row = x - 1, col = y + 1;
    while (chess[row][col] == worb)
    {
        count3++;
        col++;
        row--;
    }
    while (chess[row][col] == 0)
    {
        ru++;
        col++;
        row--;
    }
    row = x + 1, col = y - 1;
    while (chess[row][col] == worb)
    {
        count3++;
        col--;
        row++;
    }
    while (chess[row][col] == 0)
    {
        ld++;
        col--;
        row++;
    }


    //斜下
    row = x + 1, col = y + 1;
    while (chess[row][col] == worb)
    {
        count4++;
        col++;
        row++;
    }
    while (chess[row][col] == 0)
    {
        rd++;
        col++;
        row++;
    }
    row = x - 1, col = y - 1;
    while (chess[row][col] == worb)
    {
        count4++;
        col--;
        row--;
    }
    while (chess[row][col] == 0)
    {
        lu++;
        col--;
        row--;
    }

    chess[x][y] = 0;

    if (count1 >= 5 || count2 >= 5 || count3 >= 5 || count4 >= 5)//成五
    {
        return sumscore = 5000000;
    }


    if ((count1 == 4 && count2 == 4 && l >= 1 && r >= 1 && u >= 1 && d >= 1) ||
        (count1 == 4 && count3 == 4 && l >= 1 && r >= 1 && ru >= 1 && ld >= 1) ||
        (count1 == 4 && count4 == 4 && l >= 1 && r >= 1 && rd >= 1 && lu >= 1) ||
        (count2 == 4 && count3 == 4 && u >= 1 && d >= 1 && ru >= 1 && ld >= 1) ||
        (count2 == 4 && count4 == 4 && u >= 1 && d >= 1 && lu >= 1 && rd >= 1) ||
        (count3 == 4 && count4 == 4 && ru >= 1 && ld >= 1 && lu >= 1 && rd >= 1))
        //双活四
    {
        return sumscore = 4000000;
    }


    if ((count1 == 4 && l >= 1 && r >= 1) || (count2 == 4 && u >= 1 && d >= 1) ||
        (count3 == 4 && ru >= 1 && ld >= 1) || (count4 == 4 && lu >= 1 && rd >= 1))
        //活四
    {
        return sumscore = 800000;
    }

    if ((count1 == 4 && ((l == 0 && r >= 1) || (l >= 1 && r == 0)))
        || (count2 == 4 && ((u == 0 && d >= 1) || (u >= 1 && d == 0)))
        || (count3 == 4 && ((ld == 0 && ru >= 1) || (ld >= 1 && ru == 0)))
        || (count4 == 4 && ((lu == 0 && rd >= 1) || (lu >= 1 && rd == 0))))
    {
        sumscore = sumscore + 35000; //成四
    }

    if ((count1 == 3 && count2 == 3 && l >= 1 && r >= 1 && u >= 1 && d >= 1) ||
        (count1 == 3 && count3 == 3 && l >= 1 && r >= 1 && ru >= 1 && ld >= 1) ||
        (count1 == 3 && count4 == 3 && l >= 1 && r >= 1 && rd >= 1 && lu >= 1) ||
        (count2 == 3 && count3 == 3 && u >= 1 && d >= 1 && ru >= 1 && ld >= 1) ||
        (count2 == 3 && count4 == 3 && u >= 1 && d >= 1 && lu >= 1 && rd >= 1) ||
        (count3 == 3 && count4 == 3 && ru >= 1 && ld >= 1 && lu >= 1 && rd >= 1))
        //双活三
    {
        return sumscore + 400000;
    }


    if ((count1 == 3 && l >= 1 && r >= 1) || (count2 == 3 && u >= 1 && d >= 1) ||
        (count3 == 3 && ru >= 1 && ld >= 1) || (count4 == 3 && lu >= 1 && rd >= 1))
        //活三
    {
        sumscore = sumscore + 60000;
        return sumscore;
    }


    if ((count1 == 2 && count2 == 2 && l >= 1 && r >= 1 && u >= 1 && d >= 1) ||
        (count1 == 2 && count3 == 2 && l >= 1 && r >= 1 && ru >= 1 && ld >= 1) ||
        (count1 == 2 && count4 == 2 && l >= 1 && r >= 1 && rd >= 1 && lu >= 1) ||
        (count2 == 2 && count3 == 2 && u >= 1 && d >= 1 && ru >= 1 && ld >= 1) ||
        (count2 == 2 && count4 == 2 && u >= 1 && d >= 1 && lu >= 1 && rd >= 1) ||
        (count3 == 2 && count4 == 2 && ru >= 1 && ld >= 1 && lu >= 1 && rd >= 1))
        //双活二
    {
        sumscore = sumscore + 20000;
    }

    if ((count1 == 2 && l >= 1 && r >= 1) || (count2 == 2 && u >= 1 && d >= 1) ||
        (count3 == 2 && ru >= 1 && ld >= 1) || (count4 == 2 && lu >= 1 && rd >= 1))
        //单活二
    {
        sumscore = sumscore + 10000;
    }
    if ((count1 == 3 && ((l == 0 && r >= 1) || (l >= 1 && r == 0)))
        || (count2 == 3 && ((u == 0 && d >= 1) || (u >= 1 && d == 0)))
        || (count3 == 3 && ((ld == 0 && ru >= 1) || (ld >= 1 && ru == 0)))
        || (count4 == 3 && ((lu == 0 && rd >= 1) || (lu >= 1 && rd == 0))))
    {
        sumscore = sumscore + 5000; //成三
    }
    return sumscore;

}
//遍历棋盘，得到分数最高坐标并下棋
void computer() {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            scoremap[i][j] = scoremap_[i][j];
            aiscore[i][j] = 0;
            humanscore[i][j] = 0;
        }
    }
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (chess[i][j] == 0) {
                cal_unit(i, j, ai);
                cal_unit(i, j, human);
                scoremap[i][j] += cal_unit(i, j, ai) - cal_unit(i, j, human);
            }
        }
    }
    int min = 10000000, max = 0;
    int min_x = 0, min_y = 0, max_x = 0, max_y = 0;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (chess[i][j] != 0) scoremap[i][j] = 0;
            if (chess[i][j] == 0) {
                if (min > scoremap[i][j]) {
                    min = scoremap[i][j];
                    min_x = i;
                    min_y = j;
                }
                if (max < scoremap[i][j]) {
                    max = scoremap[i][j];
                    max_x = i;
                    max_y = j;
                }
            }
        }
    }

    if (max + min < 0) {
        chess[min_x][min_y] = ai;
        piece(min_x, min_y, aicol);
    }
    else {
        chess[max_x][max_y] = ai;
        piece(max_x, max_y, aicol);
    }
}
void pk() {
    // single match of player vs player; after finish vicshow will set 'set' and ck to signal main
    clear();
    bk();
    ExMessage m;

    while (true)
    {
        // 获取一条鼠标或按键消息
        m = getmessage(EX_MOUSE | EX_KEY);
        if (m.message == WM_MOUSEMOVE) {
            cleardevice();
            bk();
            piece(m.x, m.y, who);
        }
        if (m.message == WM_LBUTTONDOWN) {
            cleardevice();
            bk();
            if (chess[close(m.x)][close(m.y)] == 0) {
                piece(close(m.x), close(m.y), who);
                if (who == 0) {
                    chess[close(m.x)][close(m.y)] = 1;
                    who = 225;
                }
                else if (who == 225) {
                    chess[close(m.x)][close(m.y)] = 2;
                    who = 0;
                }
            }
            bk();
        }
        FlushBatchDraw();
        if (vic() != 0) {
            vicshow();
            break;
        }
    }
}//双人对战
//分数地图输出
void showmap() {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            cout << scoremap[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
//人机对战
void aipk() {
    // single match of player vs AI; after finish vicshow will set 'set' and ck to signal main
    clear();
    bk();
    ExMessage m;
    while (true)
    {

        // 获取一条鼠标或按键消息
        m = getmessage(EX_MOUSE | EX_KEY);
        if (ai == 1) {
            chess[7][7] = ai;
            piece(7, 7, aicol);
            bk();
        }
        if (m.message == WM_MOUSEMOVE) {
            cleardevice();
            bk();
            piece(m.x, m.y, humancol);
        }
        if (m.message == WM_LBUTTONDOWN) {
            if (humannum == 0 && ainum == 0)  showmap();
            cleardevice();
            bk();
            if (chess[close(m.x)][close(m.y)] == 0) {
                piece(close(m.x), close(m.y), humancol);
                chess[close(m.x)][close(m.y)] = human;
                humannum++;
                chessnum++;
                emnum--;
            }
            Sleep(100);
            computer();
            showmap();
            bk();
        }
        FlushBatchDraw();
        if (vic() != 0) {
            vicshow();
            break;
        }
    }
}//人机模式
int main() {
    begin();
    // loop: after each match vicshow() will set 'set' to next mode (1=pk,2=aipk,0=exit)
    while (set != 0) {
        if (set == 1) {
            pk();
        }
        else if (set == 2) {
            setai();
            aipk();
        }
        // make sure ck is reset for next match
        ck = 1;
    }
    EndBatchDraw();
    _getch();
    closegraph();
    return 0;
}