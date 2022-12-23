#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include<vector>
#include"orz.h"
using namespace std;
#define ID_EDIT 1000
#define WM_1 999999
#define WM_2 999998
#define WM_3 999997
#define WM_4 999996
#define WM_5 999995
const int N = 50,M=300,TolC=3000;
const int p[8][14] = {
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,0,0,1,1,2,3,3,4,4,5,6,6,49},
{-1,7,7,8,8,9,10,10,11,11,12,13,13,50},
{-1,14,14,15,15,16,17,17,18,18,19,20,20,51},
{-1,21,21,22,22,23,24,24,25,25,26,27,27,52},
{-1,28,28,29,29,30,31,31,32,32,33,34,34,53},
{-1,35,35,36,36,37,38,38,39,39,40,41,41,54},
{-1,42,42,43,43,44,45,45,46,46,47,48,48,55}
};
int q[8][14];
TCHAR szAppName[] = TEXT("Orz1");
TCHAR szChildName[] = TEXT("Orz2");
TCHAR szChildName2[] = TEXT("Orz3");
HINSTANCE hInstanc;
int Cntid,cxChar, cyChar,NumCors,n,Sigma;
int nk=-1,FocusId,tmp,flag,col[N],Id[TolC],cnt,wtf;
long long Tim[TolC];
int Lis[M][N],nowL[N],ChsId;
vector<int>tim[TolC];
struct Child2 {
    HWND hwnd;
    HMENU id;
    int op,op2,op3;
    TCHAR szName[50];
    int pos[M],cnt;
}ch[N],g[N];
vector<int>a[N];
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWndProc2(HWND, UINT, WPARAM, LPARAM);
struct CoursN {
    TCHAR F[2][M];
}T[TolC];
bool Equal(TCHAR *s1,TCHAR *s2) {
    while (*s1 && (*s1 == *s2))
        s1++, s2++;
    return *s1 == *s2 ? 1 : 0;
}
void PreWork() {
    int i,j;
    for(i=0;Lab[i].F[0][0];i++)
        if (i == 0 || (!Equal(Lab[i].F[1], Lab[i - 1].F[1]) || !Equal(Lab[i].F[2], Lab[i - 1].F[2]))) {
            for (j = 0; j < M; j++)
                T[NumCors].F[0][j] = Lab[i].F[1][j],
                T[NumCors].F[1][j] = Lab[i].F[2][j];
            NumCors++;
        }
}
bool Judge(TCHAR* s, TCHAR* t, int n) {
    int i = 0;
    while (*s && i < n) {
        if (*s == t[i])
            i++;
        s++;
    }
    return i == n;
}
void Insert(int nk, int I) {
    CoursN p = T[Id[I]];
    int i,j;
    for(i=0;i<Sum;i++)
        if (Equal(p.F[0], Lab[i].F[1]) && Equal(p.F[1], Lab[i].F[2])&&Lab[i].F[3][0]&&Lab[i].F[4][0]) {
            for (j = 0; j < ch[nk].cnt; j++) {
                if (i == ch[nk].pos[j])
                    break;
            }
            if (j == ch[nk].cnt) {
                ch[nk].pos[ch[nk].cnt++] = i;
            }
        }
}
int GetnumR(TCHAR *s,int n) {
    int x = 0,t=1;
    while (n >=0 && s[n] >= 48 && s[n] <= 57) {
        x += (s[n] - 48) * t;
        t *= 10;
        n--;
    }
    return x;
}
int GetnumL(TCHAR* s, int n) {
    int x = 0;
    while (s[n] >= 48 && s[n] <= 57) {
        x = x * 10 + s[n] - 48;
        n++;
    }
    return x;
}
void PreWork2() {
    int i, j, k,x,y,t,A;
    TCHAR s[M];
    for (i = 0; i < TolC; i++) {
        if (Lab[i].F[4][0]) {
            for (j = 0; j < M; j++)
                s[j] = Lab[i].F[4][j];
            A = -1; t = 0;
            for (j = 0; j < M&&s[j]; j++) {
                if (s[j] == L')')A = j;
                if (s[j] == L'周') {
                    if (j - A > 3)
                        t = 1;
                    else
                        t = 0;
                }
                if (s[j] == L'('&&t) {
                    x = GetnumR(s, j - 1);
                    k = j;
                    while (s[k]!=L')'&&s[k]) {
                        y = GetnumL(s, ++k);
                        if (x>7||y>13||p[x][y] == -1)break;
                        if ((Tim[i] & (1ll << p[x][y])) == 0)
                            tim[i].push_back(p[x][y]);
                        Tim[i] |= 1ll<<p[x][y];
                        while (s[k] >= 48 && s[k] <= 57)
                            k++;
                    }
                    j = k-1;
                }
            }
        }
    }
    
}
void dfs(int i, long long tag) {
    if (Sigma == 200)return;
    if (i == n) {
        for (i = 0; i < n; i++)
            Lis[Sigma][i] = nowL[i];
        Sigma++;
        return;
    }
    for (int j = 0;(unsigned) j < a[i].size();j++) 
        if((tag&Tim[a[i][j]])==0){
            nowL[i] = a[i][j];
            dfs(i + 1, tag | Tim[a[i][j]]);
    }
}
void Work(){
    n = 0;
    int i, j, k,x;
    for (i = 0; i < N; i++)
        if (ch[i].op&&ch[i].op3==0)
            g[n++] = ch[i];
    for (i = 0; i < n; i++) {
        a[i].clear();
        for (j = 0; j < g[i].cnt; j++) {
            x = g[i].pos[j];
            for (k = 0; (unsigned)k < a[i].size(); k++)
                if (Tim[a[i][k]] == Tim[x])
                    break;
            if (k == a[i].size())
                a[i].push_back(x);
        }
    }
    Sigma = 0;
    long long ban=0;
    for(i=1;i<=7;i++)
        for(j=1;j<=13;j++)
            if (q[i][j]) {
                ban |= 1ll<< p[i][j];
                }
    dfs(0, ban);
    ChsId = -1;
}
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, INT iCmdShow)
{
    PreWork();
    PreWork2();
    hInstanc = hInstance;
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;
    RegisterClass(&wndclass);

    wndclass.lpfnWndProc = ChildWndProc;
    wndclass.hIcon = NULL;
    wndclass.lpszClassName = szChildName;
    RegisterClass(&wndclass);

    wndclass.lpfnWndProc = ChildWndProc2;
    wndclass.hIcon = NULL;
    wndclass.lpszClassName = szChildName2;
    RegisterClass(&wndclass);

    hwnd = CreateWindow(szAppName,
        TEXT("2023春"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL);

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect,rect2;
    TEXTMETRIC tm;
    static HWND hwndEdit,hwndText;
    int i,j,k, xpos, ypos,x,y;
    TCHAR s[M];
    static int cxClient, cyClient,Cnt;
    static struct Bt {
        int  dx, dy,lx,ly;
        TCHAR s[100];
    }t[100];
    switch (message)
    {
    case WM_CREATE:
        hdc = GetDC(hwnd);
        GetTextMetrics(hdc, &tm);
        cxChar = 2 * tm.tmAveCharWidth;
        cyChar = tm.tmHeight + tm.tmExternalLeading;
        ReleaseDC(hwnd, hdc);
        t[0].dx = cxChar * 2;
        t[0].dy = cyChar * 2;
        t[0].lx = cxChar * 13/2;
        t[0].ly = cyChar * 2;
        wsprintf(t[0].s, TEXT("%s"), TEXT("新增课程组"));
        t[1].dx = cxChar * 30;
        t[1].dy = 0;
        t[1].lx = cxChar * 4;
        t[1].ly = cyChar*2;
        wsprintf(t[1].s, TEXT("%s"), TEXT("课堂号"));
        t[2].dx = cxChar * 34;
        t[2].dy = 0;
        t[2].lx = cxChar * 4;
        t[2].ly = cyChar * 2;
        wsprintf(t[2].s, TEXT("%s"), TEXT("课程名"));
        t[3].dx = cxChar * 38;
        t[3].dy = 0;
        t[3].lx = cxChar * 5;
        t[3].ly = cyChar * 2;
        wsprintf(t[3].s, TEXT("%s"), TEXT("开课单位"));
        t[4].dx = cxChar * 43;
        t[4].dy = 0;
        t[4].lx = cxChar * 5;
        t[4].ly = cyChar * 2;
        wsprintf(t[4].s, TEXT("%s"), TEXT("授课教师"));
        t[5].dx = cxChar * 48;
        t[5].dy = 0;
        t[5].lx = cxChar * 5;
        t[5].ly = cyChar * 2;
        wsprintf(t[5].s, TEXT("%s"), TEXT("时间地点"));
        t[6].dx = cxChar * 53;
        t[6].dy = 0;
        t[6].lx = cxChar * 3;
        t[6].ly = cyChar * 2;
        wsprintf(t[6].s, TEXT("%s"), TEXT("确认"));
        t[7].dx = 0;
        t[7].dy = 0;
        t[7].lx = cxChar * 5;
        t[7].ly = cyChar * 2;
        wsprintf(t[7].s, TEXT("%s"), TEXT("增加课程"));
        t[8].dx = cxChar * 20;
        t[8].dy = 0;
        t[8].lx = cxChar * 3;
        t[8].ly = cyChar * 3 / 2;
        wsprintf(t[8].s, TEXT("%s"), TEXT("取消"));
        t[9].dx = cxChar * 2;
        t[9].dy = cyChar * 5;
        t[9].lx = cxChar * 5;
        t[9].ly = cyChar * 2;
        wsprintf(t[9].s, TEXT("%s"), TEXT("生成课表"));
        t[10].dx = cxChar * 0;
        t[10].dy = cyChar * 0;
        t[10].lx = cxChar * 3;
        t[10].ly = cyChar * 2;
        wsprintf(t[10].s, TEXT("%s"), TEXT("返回"));
        t[11].dx = cxChar * 2;
        t[11].dy = cyChar * 8;
        t[11].lx = cxChar * 5;
        t[11].ly = cyChar * 2;
        wsprintf(t[11].s, TEXT("%s"), TEXT("使用指南"));
        for (i = 0; i < N; i++) {
            ch[i].id = (HMENU)++Cntid;
            wsprintf(ch[i].szName, TEXT("%d"), (int)ch[i].id);
            ch[i].hwnd = CreateWindow(
                szChildName, NULL,
                WS_CHILDWINDOW | WS_VISIBLE,
                0, 0, 0, 0,
                hwnd, ch[i].id,
                hInstanc, NULL
            );
        }
             hwndText = CreateWindow(
                szChildName2, NULL,
                WS_CHILDWINDOW | WS_VISIBLE|WS_BORDER|
                 WS_HSCROLL| WS_VSCROLL,
                0, 0, 0, 0,
                hwnd, (HMENU)10002,
                hInstanc, NULL
            );
             hwndEdit = CreateWindow(TEXT("edit"), NULL,
                 WS_CHILD | WS_VISIBLE |
                 WS_BORDER | ES_LEFT |
                 ES_AUTOHSCROLL | ES_AUTOVSCROLL,
                 0, 0, 0, 0, hwnd, (HMENU)ID_EDIT,
                 ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        
        return 0;
    case WM_SETFOCUS:
        if (FocusId)
            SetFocus(hwndEdit);
        else
            SetFocus(hwndText);
        return 0;
    case WM_LBUTTONDOWN:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        GetClientRect(hwnd, &rect);
        if (wtf == 1) {
            wtf = 0;
            SendMessage(hwnd, WM_SIZE, NULL, NULL);
            return 0;
        }
        if (nk == -1) {
            if (flag == 0) {
                if (x >= t[0].dx && x <= t[0].dx + t[0].lx && y >= t[0].dy && y <= t[0].dy + t[0].ly) {
                    if (Cnt == 20) {
                        MessageBox(hwnd, L"选这么多课，你是卷王嘛？", L"警告", 0);
                        return 0;
                    }
                    ch[Cnt++].op = 1;
                    SendMessage(hwnd, WM_SIZE, NULL, NULL);
                    return 0;
                }
                if (x >= t[9].dx && x <= t[9].dx + t[9].lx && y >= t[9].dy && y <= t[9].dy + t[9].ly) {
                    flag = 1;
                    Work();
                    SendMessage(hwnd, WM_SIZE, NULL, NULL);
                    return 0;
                }
                if (x >= t[11].dx && x <= t[11].dx + t[11].lx && y >= t[11].dy && y <= t[11].dy + t[11].ly) {
                    wtf = 1;
                    SendMessage(hwnd, WM_SIZE, NULL, NULL);
                    return 0;
                }
                int px = cxChar * 3, py = cyChar * 3 / 2;
                
                xpos = cxChar * 3; ypos = rect.bottom - py * 13;

                for (i = 1; i <= 7; i++)
                    for (j = 1; j <= 13; j++) {
                        if (x >=xpos+px*(i-1)&&x<=xpos+px*i&&y>=ypos+py*(j-1)&&y<=ypos+py*j ) {
                            q[i][j] ^= 1;
                            
                            InvalidateRect(hwnd, &rect, true);
                            return 0;
                        }
                    }
            }
            else {
                if (x >= t[10].dx && x <= t[10].dx + t[10].lx && y >= t[10].dy && y <= t[10].dy + t[10].ly) {
                    flag = 0;
                    SendMessage(hwnd, WM_SIZE, NULL, NULL);
                    return 0;
                }
                ypos = cyChar * 2;
                for (j = 0; j < 20; j++)
                    for (i = 0; i < 10; i++)
                        if (j * 10 + i < Sigma&&x >= 2 * cxChar * i && x <= 2 * cxChar * (i + 1)&&y>= ypos + 2 * cyChar * j&&y<= ypos + 2 * cyChar * (j + 1)) {
                                ChsId = j * 10 + i;
                                InvalidateRect(hwnd, &rect, true);
                                return 0;
                        }
                ChsId = -1;
                InvalidateRect(hwnd, &rect, true);
            }
            return 0;
        }
        else {
            if (x >= t[6].dx && x <= t[6].dx + t[6].lx && y >= t[6].dy && y <= t[6].dy + t[6].ly&&tmp==0) {
                nk = -1;
                SendMessage(hwnd, WM_SIZE, NULL, NULL);
                return 0;
            }
            for (i = 1; i <= 5; i++) {
                if (x >= t[i].dx && x <= t[i].dx + t[i].lx && y >= t[i].dy && y <= t[i].dy + t[i].ly) {
                    col[i] ^= 1;
                    InvalidateRect(hwnd, &rect, true);
                    WndProc(hwnd, WM_3, 0, 0);
                    return 0;
                }
            }
            if (tmp == 0) {
                if (x >= t[7].dx && x <= t[7].dx + t[7].lx && y >= t[7].dy && y <= t[7].dy + t[7].ly) {
                    tmp = 1;
                    WndProc(hwnd, WM_5, 0, 0);
                    InvalidateRect(hwnd, &rect, true);
                    WndProc(hwnd, WM_1, 0, 0);
                }
                return 0;
            }
            if (tmp == 1) {
                if (x >= t[8].dx && x <= t[8].dx + t[8].lx && y >= t[8].dy && y <= t[8].dy + t[8].ly) {
                    tmp = 0;
                    InvalidateRect(hwnd, &rect, true);
                    WndProc(hwnd, WM_4, 0, 0);
                    return 0;
                }
                ypos = cyChar * 3 / 2;
                int cntm = min(cnt, (rect.bottom - cyChar * 3 / 2) / cyChar);
                for (i = 0; i < cntm; i++) {
                    if (x >= 0 && x <= cxChar * 30 && y >= ypos && y <= ypos + cyChar * 2) {
                        Insert(nk, i);
                        tmp = 0;
                        InvalidateRect(hwnd, &rect, true);
                        WndProc(hwnd, WM_4, 0, 0);
                        WndProc(hwnd, WM_3, 0, 0);
                        return 0;
                    }
                    ypos += cyChar * 2;
                }
                return 0;
            }
            return 0;
        }
    case WM_SIZE:
        MoveWindow(hwndText, 0, 0, 0, 0, true);
        for (i = 0; i < N; i++)
            MoveWindow(ch[i].hwnd, 0, 0, 0, 0, true);
        if (nk == -1&&flag==0) {
            xpos = cxChar * 30;
            ypos = cyChar / 2;
            
            for (i = 0; i < N; i++)
                if (ch[i].op) {
                    MoveWindow(ch[i].hwnd, xpos, ypos, cxChar * 50, cyChar * 9 / 4, true);
                    ypos += cyChar * 11 / 4;
                }
                else
                    MoveWindow(ch[i].hwnd, 0, 0, 0, 0, true);
        }
        if(nk>-1){
            GetClientRect(hwnd, &rect);
            MoveWindow(hwndText, cxChar * 30,cyChar * 2, rect.right-cxChar*30, rect.bottom-(+ cyChar * 2), true);
            
        }
        GetClientRect(hwnd, &rect);
        InvalidateRect(hwnd, &rect, true);
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        GetClientRect(hwnd, &rect);
        HBRUSH hBrush;
        HPEN hPen;
        COLORREF crcolor;
        Rectangle(hdc, 0, 0, rect.right, rect.bottom);
        if (wtf == 1) {
            TCHAR s1[] = L"1.用户可以创建若干个“课程组”。在每个组内，可以任意增加课程，如“数学分析”或“化学原理A+化学原理B+化学原理C+普通化学”等，也可以根据时间上的需要和对老师的好恶，删掉或保留一门课程中的某些课堂。\n";
            TCHAR s2[] = L"2.在组内进行调整时，用户可以选择是否显示“课堂号”，“课程名”，“开课单位”，“授课教师”，“时间地点”以更方便地选择和删除课堂。同时此窗口还添加了两个滚动条以进行滚动。\n";
            TCHAR s3[] = L"3.用户可以修改每个课程组的名称，删除课程组，选择每个课程组是否参与课表生成。\n";
            TCHAR s4[] = L"4.当调整好课程组后，用户可以点击“生成课表”。此时，程序会生成课表，使得在一个课表内每个课程组都恰有一堂课选入课表。每一种方案都会有对应的按钮（但最多显示200个），按下即可查看对应的课表。\n";
            TCHAR s5[] = L"5.若生成的课表方案过多，用户在观察，对照一些方案后，有两个方法减少数量：一是删除某些课堂，减少一个课程组在不同时间段出现的可能性；二是删除某些时间段，删除的时间段就不能再排课。";
            TCHAR s[1000];
            rect2 = rect;
            int p = rect2.right / 5;
            rect.left += p;
            rect.right -= p;
            rect.top += cxChar * 5;
            wsprintf(s, L"%s\n%s\n%s\n%s\n%s\n", s1, s2, s3, s4, s5);

            DrawText(hdc, s, -1, &rect, DT_LEFT| DT_WORDBREAK);
        }
        else
        if (nk == -1) {
            if (flag == 0) {
                Rectangle(hdc, t[11].dx, t[11].dy, t[11].dx + t[11].lx, t[11].dy + t[11].ly);
                TextOut(hdc, t[11].dx + cxChar / 2, t[11].dy + cyChar / 2, t[11].s, wsprintf(t[11].s, TEXT("%s"), t[11].s));
                Rectangle(hdc, t[9].dx, t[9].dy, t[9].dx + t[9].lx, t[9].dy + t[9].ly);
                TextOut(hdc, t[9].dx + cxChar / 2, t[9].dy + cyChar / 2, t[9].s, wsprintf(t[9].s, TEXT("%s"), t[9].s));
                Rectangle(hdc, t[0].dx, t[0].dy, t[0].dx + t[0].lx, t[0].dy + t[0].ly);
                TextOut(hdc, t[0].dx + cxChar / 2, t[0].dy + cyChar / 2, t[0].s, wsprintf(t[0].s, TEXT("%s"), t[0].s));
                int px = cxChar * 3,py=cyChar*3/2;
                xpos = cxChar*3; ypos = rect.bottom - py * 13;
 
                for(i=1;i<=7;i++)
                    for (j = 1; j <= 13; j++) {
                        if (q[i][j]==0)
                            crcolor = RGB(150, 255, 150);
                        else
                            crcolor = RGB(255, 150, 150);
                        hBrush = (HBRUSH)SelectObject(hdc, CreateSolidBrush(crcolor));
                        Rectangle(hdc, xpos + px * (i - 1), ypos + py * (j - 1), xpos + px * i, ypos + py * j);
                        DeleteObject(SelectObject(hdc, hBrush));

                    }
                TCHAR o[30];
                wsprintf(o, L"备注：绿色表示可以排课，红色表示不能");
                TextOut(hdc, cxChar*3, ypos-cyChar*3/2, o, wsprintf(o, L"%s", o));
                SetTextAlign(hdc, TA_RIGHT | TA_TOP);
                for (i = 1; i <= 13; i++) {
                   
                    wsprintf(o, L"%d", i);
                    TextOut(hdc, xpos - cxChar / 2, ypos + py * (i - 1) + cyChar / 4, o, wsprintf(o,L"%s",o));
                }
                SetTextAlign(hdc, TA_LEFT | TA_TOP);
            }
            else {
                Rectangle(hdc, t[10].dx, t[10].dy, t[10].dx + t[10].lx, t[10].dy + t[10].ly);
                TextOut(hdc, t[10].dx + cxChar / 2, t[10].dy + cyChar / 2, t[10].s, wsprintf(t[10].s, TEXT("%s"), t[10].s));
                
                xpos = cxChar * 20; ypos = 1;
                int Height = (rect.bottom-ypos)/13, Width = (rect.right-xpos)/7;
                crcolor = RGB(200, 200, 200);
                hPen = (HPEN)SelectObject(hdc, CreatePen(PS_SOLID, 1, crcolor));
                for(i=1;i<=7;i++)
                    for(j=1;j<=13;j++)
                        Rectangle(hdc, xpos+Width*(i-1), ypos+Height*(j-1),xpos+Width*i, ypos+Height * j);
                DeleteObject(SelectObject(hdc, hPen));
                if (ChsId>=0) {
                    for (i = 0; i < n; i++) {
                        k = Lis[ChsId][i];
                        for (j = 0; (unsigned)j < tim[k].size(); j++) {
                            int lx = 1 << 30, rx = -1, ly = 1 << 30, ry = -1;
                            for (x = 1; x <= 7; x++)
                                for (y = 1; y <= 13; y++)
                                    if (p[x][y] == tim[k][j]) {
                                        lx = min(lx, xpos+Width * (x - 1));
                                        ly = min(ly, ypos + Height * (y - 1));
                                        rx = max(rx, xpos + Width * x);
                                        ry = max(ry, ypos + Height*y);
                                        if (y == 5 || y == 10 || y == 13)
                                            ly -= Height * 2;
                                    }
                            crcolor = RGB(200, 255, 200);
                            hBrush = (HBRUSH)SelectObject(hdc, CreateSolidBrush(crcolor));
                            Rectangle(hdc,lx, ly, rx, ry);
                            SetBkMode(hdc, TRANSPARENT);
                            TCHAR o[20];
                            wsprintf(o, TEXT("%s"), g[i].szName);
                            TextOut(hdc, lx+(rx-lx-lstrlen(o)*cxChar)/2, ly+(ry-ly-cyChar)/2, o, lstrlen(o));
                            DeleteObject(SelectObject(hdc, hBrush));
                            SetBkMode(hdc, OPAQUE);

                        }
                    }
                }
                ypos = cyChar * 2;
                for(j=0;j<20;j++)
                    for(i=0;i<10;i++)
                        if (j * 10 + i < Sigma) {
                            Rectangle(hdc, 2*cxChar*i, ypos + 2*cyChar*j, 2*cxChar*(i+1), ypos+2*cyChar*(j+1));
                            if(j*10+i==ChsId)
                                crcolor = RGB(150, 255, 150);
                            else
                                crcolor = RGB(255, 255, 255);
                            hBrush = (HBRUSH)SelectObject(hdc, CreateSolidBrush(crcolor));
                            Rectangle(hdc, 2 * cxChar * i, ypos + 2 * cyChar * j, 2 * cxChar * (i + 1), ypos + 2 * cyChar * (j + 1));
                            SetBkMode(hdc, TRANSPARENT);
                            TCHAR o[20];
                            wsprintf(o, TEXT("%d"), j * 10 + i+1);
                            TextOut(hdc, 2 * cxChar * i + cxChar / 4, ypos + 2 * cyChar * j+cyChar/2, o, lstrlen(o));
                            DeleteObject(SelectObject(hdc, hBrush));
                            SetBkMode(hdc, OPAQUE);
                        }
                
            }
        }
        else{
            /*右边的*/
            SetTextAlign(hdc, TA_RIGHT | TA_TOP);
            TextOut(hdc, rect.right - cxChar,cyChar/2,ch[nk].szName,lstrlen(ch[nk].szName));
            SetTextAlign(hdc, TA_LEFT | TA_TOP);
            for (i = 1; i <6; i++) {
                if (col[i] == 0)
                    crcolor = RGB(150, 255, 150);
                else
                    crcolor = RGB(255, 150, 150);
                hBrush = (HBRUSH)SelectObject(hdc, CreateSolidBrush(crcolor));
                Rectangle(hdc, t[i].dx, t[i].dy, t[i].dx + t[i].lx, t[i].dy + t[i].ly);
                SetBkMode(hdc, TRANSPARENT);
                TextOut(hdc, t[i].dx + cxChar / 2, t[i].dy + cyChar / 2, t[i].s, wsprintf(t[i].s, TEXT("%s"), t[i].s));
                DeleteObject(SelectObject(hdc, hBrush));
                SetBkMode(hdc, OPAQUE);
            }
            Rectangle(hdc, t[i].dx, t[i].dy, t[i].dx + t[i].lx, t[i].dy + t[i].ly);
            TextOut(hdc, t[i].dx + cxChar / 2, t[i].dy + cyChar / 2, t[i].s, wsprintf(t[i].s, TEXT("%s"), t[i].s));
            /*左边的*/
            if (FocusId == 0) {
               // MessageBox(NULL, L"a", L"b", 0);
                Rectangle(hdc, t[7].dx, t[7].dy, t[7].dx + t[7].lx, t[7].dy + t[7].ly);
                TextOut(hdc, t[7].dx + cxChar / 2, t[7].dy + cyChar / 2, t[7].s, wsprintf(t[7].s, TEXT("%s"), t[7].s));

            }
            else {
                Rectangle(hdc, t[8].dx, t[8].dy, t[8].dx + t[8].lx, t[8].dy + t[8].ly);
                TextOut(hdc, t[8].dx + cxChar / 2, t[8].dy + cyChar / 4, t[8].s, wsprintf(t[8].s, TEXT("%s"), t[8].s));
                GetClientRect(hwnd, &rect);
                Rectangle(hdc, 0, cyChar * 3 / 2, cxChar * 30, rect.bottom);
                ypos = cyChar * 3 / 2;
                k = 0;
                int cntm = min(cnt, (rect.bottom - cyChar * 3 / 2) / cyChar);
                for (i = 0; i < cntm; i++)
                    k = max(k, lstrlen(T[Id[i]].F[0]));
                k = (k + 2) * cxChar;
                for (i = 0; i < cntm; i++) {
                    Rectangle(hdc, 0, ypos, cxChar * 30, ypos+cyChar*2);
                    TextOut(hdc, cxChar / 2, ypos+cyChar / 2, T[Id[i]].F[0], lstrlen(T[Id[i]].F[0]));
                    TextOut(hdc, k, ypos + cyChar / 2, T[Id[i]].F[1], lstrlen(T[Id[i]].F[1]));
                    ypos += cyChar * 2;
                }

            }
        }
        EndPaint(hwnd, &ps);
        return 0;
    case WM_1 :
        FocusId = 1;
        SetFocus(hwnd);
        
        MoveWindow(hwndEdit, 0, 0, cxChar * 20, cyChar * 3 / 2, true);
        return 0;
    case WM_2:
        FocusId = 0;
        SetFocus(hwnd);
        GetWindowText(hwndEdit,ch[(int)wParam].szName,40);
        
        MoveWindow(hwndEdit, 2, 2, 1, 1, true);
        return 0;
    case WM_3:
        GetClientRect(hwnd, &rect);
        MoveWindow(hwndText, 0, 0, 0, 0, true);
        MoveWindow(hwndText, cxChar * 30, cyChar*2, rect.right - cxChar * 30, rect.bottom-( cyChar * 2), true);
        return 0;
    case WM_4:
        FocusId = 0;
        SetFocus(hwnd);
        MoveWindow(hwndEdit, 2, 2, 1, 1, true);
        return 0;
    case WM_COMMAND:
        if (LOWORD(wParam) == ID_EDIT && nk >= 0 && HIWORD(wParam) == EN_UPDATE) {
            WndProc(hwnd, WM_5, 0, 0);
            return 0;
        }
        return 0;
    case WM_5:
        GetWindowText(hwndEdit, s, M);
        for (n = 0; s[n]; n++);
        for (i = 0, k = 0; i < n; i++) {
            s[i - k] = s[i];
            if (s[i] == L' ' || s[i] == L'\t' || s[i] == 'r' || s[i] == '\n')
                k++;
        }
        n -= k;
        s[n] = 0;
        cnt = 0;
        if(n)
        for (i = 0; i < NumCors; i++)
            if (Judge(T[i].F[0], s, n))
                Id[cnt++] = i;
        GetClientRect(hwnd, &rect);
        InvalidateRect(hwnd, &rect, true);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}
LRESULT CALLBACK ChildWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;
    int p, dx, dy, x, y,k;
    TCHAR p1[] = TEXT("重命名"),p2[] = TEXT("确认"),p3[]=TEXT("调整"),p4[]=TEXT("选中");
    switch (message){
    case WM_PAINT:
        HBRUSH hBrush;
        COLORREF crcolor;
        k = 0;
        while (ch[k].hwnd != hwnd)k++;
        hdc = BeginPaint(hwnd, &ps);

        GetClientRect(hwnd, &rect);
        Rectangle(hdc, 0, 0, rect.right, rect.bottom);
        /* 叉号*/
        p = rect.bottom / 3;
        dx = rect.right - p * 3;
        dy = (rect.bottom - p) / 2;
        MoveToEx(hdc, dx, dy, NULL);
        LineTo(hdc, dx + p, dy + p);
        MoveToEx(hdc, dx + p, dy, NULL);
        LineTo(hdc, dx, dy + p);
        /*名字*/
        dy = (rect.bottom - cyChar) / 2;
        dx = cxChar;
        TextOut(hdc, dx, dy, ch[k].szName, wsprintf(ch[k].szName, TEXT("%s"), ch[k].szName));
        /*选中*/
        dx = cxChar * 33;
        dy= (rect.bottom - cyChar * 2) / 2;
        if(ch[k].op3==0)
            crcolor = RGB(200, 255, 200);
        else
            crcolor = RGB(255, 200, 200);
        hBrush = (HBRUSH)SelectObject(hdc, CreateSolidBrush(crcolor));
        Rectangle(hdc, dx, dy, dx+cxChar*3, dy+cyChar*2);
        SetBkMode(hdc, TRANSPARENT);
        TextOut(hdc, dx+cxChar/2, dy+cyChar/2, p4, lstrlen(p4));
        DeleteObject(SelectObject(hdc, hBrush));
        SetBkMode(hdc, OPAQUE);
        /*重命名*/
        dx = cxChar * 37;
        dy= (rect.bottom - cyChar*2) / 2;
        Rectangle(hdc, dx, dy, dx+cxChar*4,dy+cyChar*2);
        if(ch[k].op2==0)
            TextOut(hdc, dx+cxChar/2, dy+ cyChar / 2, p1, wsprintf(p1, TEXT("%s"),p1));
        else
            TextOut(hdc, dx+cxChar / 2, dy+ cyChar / 2, p2, wsprintf(p2, TEXT("%s"), p2));
        /*调整*/
        dx = cxChar * 42;
        dy= (rect.bottom - cyChar * 2) / 2;
        Rectangle(hdc, dx, dy, dx + cxChar * 3, dy + cyChar * 2);
        TextOut(hdc, dx + cxChar / 2, dy + cyChar / 2, p3, wsprintf(p3, TEXT("%s"), p3));
        EndPaint(hwnd, &ps);
        return 0;
    case WM_LBUTTONDOWN:
        k = 0;
        while (ch[k].hwnd != hwnd)k++;
        GetClientRect(hwnd, &rect);
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        /*叉号*/
        p = rect.bottom / 3;
        dx = rect.right - p * 3;
        dy = (rect.bottom - p) / 2;
        if (x >= dx && x <= dx + p && y >= dy && y <= dy + p&&ch[k].op2==0) {
            ch[k].op = 0;
            SendMessage(GetParent(hwnd), WM_SIZE, NULL, NULL);
            return 0;
        }
        dx = cxChar * 33;
        dy= (rect.bottom - cyChar * 2) / 2;
        if (x >= dx && x <= dx + cxChar * 3 && y >= dy && y <= dy + cyChar * 2) {
            ch[k].op3 ^= 1;
            GetClientRect(hwnd, &rect);
            InvalidateRect(hwnd, &rect, 1);
            return 0;
        }
        /*重命名*/
        dx = cxChar * 37;
        dy= (rect.bottom - cyChar * 2) / 2;
        if (x >= dx && x <= dx + cxChar * 4 && y >= dy && y <= dy + cyChar*2) {
           // if(op==0)
           // MessageBox(hwnd, L"qwq", L"qaq", 0);
            if (ch[k].op2 == 0&&FocusId==0) {
                ch[k].op2 ^= 1;
                WndProc(GetParent(hwnd), WM_1, 0, 0);
                GetClientRect(hwnd, &rect);
                InvalidateRect(hwnd,&rect , 1);
            }
            else if(ch[k].op2 ==1&&FocusId==1){
                ch[k].op2 ^= 1;
                WndProc(GetParent(hwnd), WM_2, k, 0);
                GetClientRect(hwnd, &rect);
                InvalidateRect(hwnd, &rect, 1);
            }
            return 0;
        }
        /*调整*/
        dx = cxChar * 42;
        dy = (rect.bottom - cyChar * 2) / 2;
        if (x >= dx && x <= dx + cxChar * 3 && y >= dy && y <= dy + cyChar * 2) {
            nk = k;
            SendMessage(GetParent(hwnd), WM_SIZE, NULL, NULL);
            return 0;
        }
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
LRESULT CALLBACK ChildWndProc2(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static int cxChar, cxCaps, cyChar, cxClient, cyClient, iMaxWidth,NUMLINES,Wid[5];
    HDC hdc;
    int i,j,k, x, y, iVertPos, iHorzPos, iPaintBeg, iPaintEnd,dx,dy,p;
    PAINTSTRUCT ps;
    SCROLLINFO si;
    TEXTMETRIC tm;
    RECT rect;
    switch (message) {
    case WM_CREATE:
        hdc = GetDC(hwnd);
        GetTextMetrics(hdc, &tm);
        cxChar = tm.tmAveCharWidth;
        cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
        cyChar = tm.tmHeight + tm.tmExternalLeading;
        ReleaseDC(hwnd, hdc);
        return 0;
    case WM_SIZE:
        //save the width of the three columns
        if (nk < 0)return 0;
        
        NUMLINES = ch[nk].cnt;
        iMaxWidth = 8;
        for (i = 0; i <5; i++) 
            if(col[i+1]==0){
            k = 0;
            for (j = 0; j < NUMLINES; j++)
                k = max(k,lstrlen( Lab[ch[nk].pos[j]].F[i]));
            Wid[i] = (i>0&&i<4) ? k * 2 : k*3/2;;
            iMaxWidth += Wid[i] + 4;
        }
        iMaxWidth *= cxChar;
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);
        //set vertical scroll bar range and page size
        si.cbSize = sizeof(si);
        si.fMask = SIF_RANGE | SIF_PAGE;
        si.nMin = 0;
        si.nMax = NUMLINES - 1;
        si.nPage = cyClient / cyChar/2;
        SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
        //set horizo scroll bar range and page size
        si.cbSize = sizeof(si);
        si.fMask = SIF_RANGE | SIF_PAGE;
        si.nMin = 0;
        si.nMax = 2 + iMaxWidth / cxChar;
        si.nPage = cxClient / cxChar;
        SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
        return 0;
    case WM_VSCROLL:
        //Get all the vertical scroll bar information
        si.cbSize = sizeof(si);
        si.fMask = SIF_ALL;
        GetScrollInfo(hwnd, SB_VERT, &si);
        //Save the position for comparison  later on
        iVertPos = si.nPos;
        switch (LOWORD(wParam)) {
        case SB_TOP:
            si.nPos = si.nMin;
            break;
        case SB_BOTTOM:
            si.nPos = si.nMax;
            break;
        case SB_LINEUP:
            si.nPos--;
            break;
        case SB_LINEDOWN:
            si.nPos++;
            break;
        case SB_PAGEUP:
            si.nPos -= si.nPage;
            break;
        case SB_PAGEDOWN:
            si.nPos += si.nPage;
            break;
        case SB_THUMBTRACK:
            si.nPos = si.nTrackPos;
            break;
        default:
            break;
        }
        //Set the position and then retrieve it.
        si.fMask = SIF_POS;
        SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
        GetScrollInfo(hwnd, SB_VERT, &si);
        if (si.nPos != iVertPos) {
            ScrollWindow(hwnd, 0, cyChar*2 * (iVertPos - si.nPos), NULL, NULL);
            UpdateWindow(hwnd);
        }
        return 0;
    case WM_HSCROLL:
        //Get all the vertical scroll bar information
        si.cbSize = sizeof(si);
        si.fMask = SIF_ALL;
        GetScrollInfo(hwnd, SB_HORZ, &si);
        //Save the position for comparison  later on
        iHorzPos = si.nPos;
        switch (LOWORD(wParam)) {
        case SB_LINELEFT:
            si.nPos--;
            break;
        case SB_LINERIGHT:
            si.nPos++;
            break;
        case SB_PAGELEFT:
            si.nPos -= si.nPage;
            break;
        case SB_PAGERIGHT:
            si.nPos += si.nPage;
            break;
        case SB_THUMBPOSITION:
            si.nPos = si.nTrackPos;
            break;
        default:
            break;
        }
        //Set the position and then retrieve it.
        si.fMask = SIF_POS;
        SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
        GetScrollInfo(hwnd, SB_HORZ, &si);
        if (si.nPos != iHorzPos) {
            ScrollWindow(hwnd, cxChar * (iHorzPos - si.nPos), 0, NULL, NULL);
            UpdateWindow(hwnd);
        }
        return 0;
    case WM_KEYDOWN:
        switch (wParam) {
        case VK_UP:
            SendMessage(hwnd, WM_VSCROLL, SB_LINEUP, 0);
            break;
        case VK_DOWN:
            SendMessage(hwnd, WM_VSCROLL, SB_LINEDOWN, 0);
            break;
        case VK_LEFT:
            SendMessage(hwnd, WM_HSCROLL, SB_LINELEFT, 0);
            break;
        case VK_RIGHT:
            SendMessage(hwnd, WM_HSCROLL, SB_LINERIGHT, 0);
            break;
        }
        return 0;
    case WM_LBUTTONDOWN:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        GetClientRect(hwnd, &rect);
        //Get vertical scroll bar position
        si.cbSize = sizeof(si);
        si.fMask = SIF_POS;
        GetScrollInfo(hwnd, SB_VERT, &si);
        iVertPos = si.nPos;
        //Get horizontal scroll bar position
        GetScrollInfo(hwnd, SB_HORZ, &si);
        iHorzPos = si.nPos;
        //Find psinting limits
        iPaintBeg = max(0, iVertPos );
        iPaintEnd = min(NUMLINES - 1, iVertPos + rect.bottom / cyChar / 2);
        for (i = iPaintBeg; i <= iPaintEnd; i++) {
            dx = cxChar * (1 - iHorzPos) + cxChar / 2;
            dy = cyChar * 2 * (i - iVertPos) + cyChar / 2;
            p = cyChar;
            if (x >= dx && x <= dx + p && y >= dy && y <= dy + p) {
                ch[nk].pos[0] = ch[nk].pos[i];
                ch[nk].cnt=1;
                WndProc(GetParent(hwnd), WM_3, 0, 0);
                return 0;
            }

            dx += cxChar * 4;
            if (x >= dx && x <= dx + p && y >= dy && y <= dy + p) {
                for (j = i; j + 1 < NUMLINES; j++)
                    ch[nk].pos[j] = ch[nk].pos[j + 1];
                ch[nk].cnt--;
                WndProc(GetParent(hwnd), WM_3, 0, 0);
                return 0;
            }
        }
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        GetClientRect(hwnd, &rect);
        //Get vertical scroll bar position
        si.cbSize = sizeof(si);
        si.fMask = SIF_POS;
        GetScrollInfo(hwnd, SB_VERT, &si);
        iVertPos = si.nPos;
        //Get horizontal scroll bar position
        GetScrollInfo(hwnd, SB_HORZ, &si);
        iHorzPos = si.nPos;
        //Find psinting limits
        iPaintBeg = max(0, iVertPos + ps.rcPaint.top / cyChar/2);
        iPaintEnd = min(NUMLINES - 1, iVertPos + ps.rcPaint.bottom / cyChar/2);
        for (i = iPaintBeg; i <= iPaintEnd; i++) {
            x = cxChar * (1 - iHorzPos);
            y = cyChar *2* (i - iVertPos);
            MoveToEx(hdc, 0, y, NULL);
            LineTo(hdc,rect.right , y);
            /*勾号*/
            dx = x + cxChar /2;
            dy = y + cyChar / 2;
            p = cyChar/2;
            MoveToEx(hdc, dx, dy+p, NULL);
            LineTo(hdc, dx + p, dy + p*2);
            LineTo(hdc, dx + p*2, dy);
            x += cxChar * 4;
            /*叉号*/
            dx = x + cxChar/2;
            dy= y + cyChar/2;
            p = cyChar;
            MoveToEx(hdc, dx, dy, NULL);
            LineTo(hdc, dx + p, dy+ p);
            MoveToEx(hdc, dx, dy+p, NULL);
            LineTo(hdc, dx+p, dy );
            /*课程信息*/
            TCHAR qwq[M];
            wsprintf(qwq, L"%d", i+1);
            x += cxChar * 4;
            TextOut(hdc, x, y + cyChar / 2, qwq, lstrlen(qwq));
            for (j = 0; j < 5; j++) 
                if(col[j+1]==0){
                x += 4*cxChar;
                wsprintf(qwq, L"%s", Lab[ch[nk].pos[i]].F[j]);
                TextOut(hdc, x, y+cyChar/2, qwq, lstrlen(qwq));
                x += Wid[j]*cxChar;
            }
        }
        EndPaint(hwnd, &ps);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
