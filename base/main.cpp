#include <iostream>
#include <windows.h>
#include <string>
#include <cstdio>
#include <cmath>
using namespace std;

void MoveXY(short const x,short const y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

#define mWidth 80
#define mHeight 25

struct TMap{
    char map1[mHeight][mWidth+1];
    void Clear();
    void Show();
};

void TMap::Clear() {
    for(int i=0;i<mWidth;i++)
        map1[0][i] = ' ';
    map1[0][mWidth] = '\0';
    for(int j=1;j<mHeight;j++)
        strncpy(map1[j],map1[0],mWidth+1);
    map1[12][20] = '*';
    map1[12][60] = '*';
    map1[5][40] = '*';
    map1[20][40] = '*';
}

void TMap::Show() {
    MoveXY(0,0);
    map1[mHeight-1][mWidth-1] = '\0';
    for(int j=0;j<mHeight;j++)
        cout << map1[j];
}

enum TDirection {dirLeft,dirRight,dirUp,dirDown};
enum TResult {reOK,reKill};

#define sLen 1000

class TSnake
{
    int x,y;
    TMap *mp;
    TDirection dir;
    POINT tail[sLen];
    int len;
    int score;
    POINT OutTextPos;
public:
    void AddTail(int _x,int _y);
    void MoveTail(int _x,int _y);
    void AddTailCnt(int _x,int _y,int cnt);
    TSnake(TMap *_mp,int outX,int outY);
    void Init(int _x,int _y,TDirection _dir);
    void PutOnMap();
    TResult UserControl(char w,char s,char a,char d);
    void IncScore();
};

void TSnake::AddTail(int _x, int _y) {
    MoveTail(_x,_y);
    len++;
    if(len>=sLen) len = sLen-1;
}

void TSnake::MoveTail(int _x, int _y) {
    for(int i=len-1;i>=0;i--)
        tail[i+1] = tail[i];
    tail[0].x = _x;
    tail[0].y = _y;
}

void TSnake::AddTailCnt(int _x, int _y, int cnt) {
    for(int i=0;i<cnt;i++)
        AddTail(_x,_y);
}

TSnake::TSnake(TMap *_mp, int outX, int outY) {
    mp = _mp;
    Init(0,0,dirRight);
    score = 0;
    OutTextPos.x = outX;
    OutTextPos.y = outY;
}

void TSnake::Init(int _x, int _y, TDirection _dir) {
    x = _x;
    y = _y;
    dir = _dir;
    len = 0;
}

void TSnake::PutOnMap() {
    char str[10];
    sprintf(str,"%d",score);
    mp->map1[y][x] = '@';
    for(int i=0;i< strlen(str);i++)
        mp->map1[OutTextPos.y][OutTextPos.x+i] = str[i];
    for (int i=0;i<len;i++)
        mp->map1[tail[i].y][tail[i].x] = '+';
}

TResult TSnake::UserControl(char w, char s, char a, char d) {
    POINT old;
    old.x = x;
    old.y = y;
    if(GetKeyState(w)<0) dir = dirUp;
    if(GetKeyState(s)<0) dir = dirDown;
    if(GetKeyState(a)<0) dir = dirLeft;
    if(GetKeyState(d)<0) dir = dirRight;

    switch (dir) {
        case dirLeft:
            x--;
            break;
        case dirRight:
            x++;
            break;
        case dirUp:
            y--;
            break;
        case dirDown:
            y++;
            break;
    }

    if((x<0)||(x>mWidth)||(y<0)||(y>mHeight)||(mp->map1[y][x]=='+'))
        return reKill;

    if(mp->map1[y][x]=='*')
        AddTailCnt(old.x,old.y,5);
    else
        MoveTail(old.x,old.y);

    return reOK;
}

void TSnake::IncScore() {
    score++;
}


namespace abcd{
    int z = 1;
    float f = 3.1413;
}

using namespace abcd;

struct TPoint
{
    int x;
private:
    int y;
public:
    void SetY(int y1)
    {
        y = y1;
    }
    int GetY()
    {
        return y;
    }
};

class TPoint1
{
    int y;
public:
    int x;
    void SetY(int y1);
    int GetY()
    {
        return y;
    }
};

void TPoint1::SetY(int y1) {
    y = y1;
}

class Test{
    int num;
public:
    Test(int _num,char c)
    {
        num = _num;
        cout << num << ' ' << c << "自动运行\n";
    }
    ~Test()
    {
        cout << num << ' ' << "最后运行\n";
    }
    void Print() const
    {
        cout << num << ' ' <<"print\n";
    }
};

struct Tabs{
    int i;
    Tabs() {cout<<"con\n";}
    ~Tabs() {cout<<"des\n";}
    void Show() {cout <<i<<endl;}
};

class Tkvk{
    float val,valSqr,valSqrt;
public:
    void SetVal(float f)
    {
        val = f;
        valSqr = val*val;
        valSqrt = sqrt(val);
    }
    float GetSqr() {return valSqr;}
    float GetSqrt() {return valSqrt;}
    void Show()
    {
        cout << "val=" << val<< " sqr=" << GetSqr()<<" Sqrt="<<GetSqrt()<<endl;
    }
};

void Show(Tkvk obj)
{
    obj.Show();
}

class Tbar
{
    struct {int x,y;}p1,p2;
public:
    Tbar(int x1,int y1,int x2,int y2);
    ~Tbar();
};

Tbar::Tbar(int x1, int y1, int x2, int y2) {
    p1.x = x1;
    p1.y = y1;
    p2.x = x2;
    p2.y = y2;
}

Tbar::~Tbar() {
    cout << "(" << p1.x <<","<<p1.y<<") ";
    cout << "(" << p2.x <<","<<p2.y<<") ";
    cout <<sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2))<<endl;
}

class TMas{
    int a[3];
    int target = 1;
public:
    TMas(int a0,int a1,int a2)
    {
        a[0]=a0;
        a[1]=a1;
        a[2]=a2;
    }
    void Up()
    {
        target += target<2?1:0;
    }
    void Down()
    {
        target += target>0?-1:0;
    }
    int Get()
    {
        return a[target];
    }
};

class TPoint2{
    int x,y;
public:
    void Init(int _x,int _y)
    {
        x = _x;
        y = _y;
    }
    void Show()
    {
        cout << x << "," << y <<endl;
    }
};

struct TMap1
{
    char map1[mHeight][mWidth+1];
    void Clear();
    void Show();
    bool IsFreeCell(int x,int y);
    bool CellInMap(int x,int y);
};

void TMap1::Clear() {
    for(int i=0;i<mWidth;i++)
        map1[0][i] = ' ';
    map1[0][mWidth] = '\0';
    for (int j=1;j<mHeight;j++)
        strncpy(map1[j],map1[0],mWidth+1);
    map1[12][20] = '*';
    map1[12][60] = '*';
    map1[5][40] = '*';
    map1[20][40] = '*';
}

void TMap1::Show() {
    MoveXY(0,0);
    map1[mHeight-1][mWidth-1] = '\0';
    for(int j=0;j<mHeight;j++)
        cout << map1[j];
}

bool TMap1::IsFreeCell(int x, int y) {
    if(!CellInMap(x,y)) return false;
    return (map1[y][x]!='@') && (map1[y][x]!='+');
}

bool TMap1::CellInMap(int x, int y) {
    return (x>=0)&&(x<mWidth)&&(y>=0)&&(y<mHeight);
}

class TSnake1{
    int x,y;
    TMap1 *mp;
    TDirection dir;
    POINT tail[sLen];
    int len;
    int score;
    POINT OutTextPos;
public:
    void AddTail(int _x,int _y);
    void MoveTail(int _x,int _y);
    void AddTailCnt(int _x,int _y,int cnt);
    TSnake1(TMap1 *_mp,int outX,int outY);
    void Init(int _x,int _y,TDirection _dir);
    void PutOnMap();
    TResult UserControl(char w,char s,char a,char d,bool ii);
    TResult IIControl();
    TResult Move();
    void IncScore();
};

void TSnake1::AddTail(int _x, int _y) {
    MoveTail(_x,_y);
    len++;
    if (len>=sLen) len = sLen-1;
}

void TSnake1::MoveTail(int _x, int _y) {
    for(int i=len-1;i>=0;i--)
        tail[i+1] = tail[i];
    tail[0].x = _x;
    tail[0].y = _y;
}

void TSnake1::AddTailCnt(int _x, int _y, int cnt) {
    for(int i=0;i<cnt;i++)
        AddTail(_x,_y);
}

TSnake1::TSnake1(TMap1 *_mp, int outX, int outY) {
    mp = _mp;
    Init(0,0,dirRight);
    score = 0;
    OutTextPos.x = outX;
    OutTextPos.y = outY;
}

void TSnake1::Init(int _x, int _y, TDirection _dir) {
    x = _x;
    y = _y;
    dir = _dir;
    len = 0;
}

void TSnake1::PutOnMap() {
    char str[10];
    sprintf(str,"%d",score);
    mp->map1[y][x] = '@';
    for (int i=0;i<strlen(str);i++)
        mp->map1[OutTextPos.y][OutTextPos.x+i] = str[i];

    for (int i=0;i<len;i++)
        mp->map1[tail[i].y][tail[i].x] = '+';
}

TResult TSnake1::UserControl(char w, char s, char a, char d,bool ii) {

    if (ii)
        return IIControl();
    else
    {
        if(GetKeyState(w)<0) dir = dirUp;
        if(GetKeyState(s)<0) dir = dirDown;
        if(GetKeyState(a)<0) dir = dirLeft;
        if(GetKeyState(d)<0) dir = dirRight;

        return Move();
    }
}

void TSnake1::IncScore() {
    score++;
}

TResult TSnake1::Move() {
    POINT old;
    old.x = x;
    old.y = y;
    if(dir==dirLeft) x--;
    if(dir==dirRight) x++;
    if(dir==dirUp) y--;
    if(dir==dirDown) y++;

    if(!mp->IsFreeCell(x,y))
        return reKill;
    if(mp->map1[y][x]=='*')
        AddTailCnt(old.x,old.y,5);
    else
        MoveTail(old.x,old.y);
    return reOK;
}

TResult TSnake1::IIControl() {
    if((dir==dirLeft)||(dir==dirRight))
    {
        int i;
        for(i=0;i<mHeight;i++)
        {
            if(mp->map1[i][x]=='*')
                break;
        }
        if(i<mHeight)
            dir = (i<y)?dirUp:dirDown;
    }
    if((dir==dirUp)||(dir==dirDown))
    {
        int i;
        for(i=0;i<mWidth;i++)
        {
            if(mp->map1[y][i]=='*')
                break;
        }
        if(i<mWidth)
            dir = (i<x)?dirLeft:dirRight;
    }
    POINT pos = {x,y};
    if(dir==dirLeft) pos.x--;
    if(dir==dirRight) pos.x++;
    if(dir==dirUp) pos.y--;
    if(dir==dirDown) pos.y++;

    if(!mp->IsFreeCell(pos.x,pos.y))
    {
        if((dir==dirDown)||(dir==dirUp))
            dir = mp->IsFreeCell(x-1,y) ? dirLeft:dirRight;
        else if((dir==dirLeft)||(dir==dirRight))
            dir = mp->IsFreeCell(x,y-1) ? dirUp:dirDown;
    }

    return Move();
}

void Mult2(int &val)
{
    val *= 2;
}

int p;

int &GetParam()
{
    return p;
}

struct point{
    int x,y;
};

void proc()
{
    cout << "proc" <<endl;
}
int proc(int a,char b='-',int c=10)
{
    cout << a << b << c <<endl;
}

void proc(double a)
{
    cout << "proc (double)"<<endl;
}

class T1
{
public:
    void show()
    {
        cout << "show()" <<endl;
    }
    void show(int a,int b=7)
    {
        cout << "show(int a,int b)" <<endl;
    }
    T1()
    {
        cout << "constructor T1" <<endl;
    }
    T1(int a)
    {
        cout << "constructor T1(int a)" <<endl;
    }
    T1(const T1 &a)
    {
        cout <<  "constructor of copy" <<endl;
    }
    ~T1()
    {
        cout << "destructor T1" <<endl;
    }
};

void proc1(T1 x)
{
    cout << "proc" <<endl;
}

#define height 25
#define width 80

#define field ' '
#define fbrick 176
#define fstone 206

#define duloV 179
#define duloH 205
#define tankC 219
#define catter '#'

typedef unsigned char mapHW[height][width];

void SetCurPos(short x,short y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

bool IsCross(RECT a,RECT b)
{
    return (a.right>=b.left) && (a.left<=b.right) && (a.bottom>=b.top) && (a.top<=b.bottom);
}

struct Tmap{
    mapHW map;
    void Clear() {
        memset(map,field,sizeof(map)-1);
    }
    void SetEnd() {map[height-1][width-1]='\0';}
    void Show() { SetCurPos(0,0);SetEnd();cout<<map[0];}
};

enum Tdir {Rup=0,Rdown,Rleft,Rright};
POINT dirInc[] = {{0,-1},{0,1},{-1,0},{1,0}};

class Ttank{
    int x,y;
    int sX,sY;
public:
    Tdir dir;
    Ttank(int startX,int startY)
    {
        dir = Rup;
        sX = startX;
        sY = startY;
        SetToStart();
    }
    void Show(mapHW &map);
    void Move(char w,char s,char a,char d,char fire);
    void SetToStart() {x=sX,y=sY;}
    bool IsHoriz() {return {dir==Rright||dir==Rleft};}
    RECT GetRect() {RECT r={x-1,y-1,x+1,y+1};return r;}
};

enum Tmatter {ttStone,ttBrick};

class Tbrick
{
    RECT rct;
public:
    bool use;
    Tmatter tp;
    Tbrick() {use=false,tp=ttBrick;}
    void Show(mapHW &map);
    void SetPos(int px,int py){RECT r={px-1,py-1,px+1,py+1};rct=r;use=1;}
    RECT GetRect() {return rct;}
};

class Tpula
{
    int x,y;
    int speed;
    Tdir dir;
public:
    bool use;
    Tpula () {use=0;speed=5;}
    void SetPula(int px,int py,Tdir pdir)
    {
        x=px;
        y=py;
        dir = pdir;
        use = 1;
    }
    void Move();
    void Show(mapHW &map)
    {
        if(!use)
        {
            return;
        }
        map[y][x]='*';
    }
};

Tmap scr;
#define tankCnt 2
Ttank tank[tankCnt] = {Ttank(1,11),Ttank(77,11)};
#define brickCnt 300
Tbrick brick[brickCnt];
#define pulaCnt 100
Tpula pula[pulaCnt];

Tpula &GetFreePula()
{
    for(int i=0;i<pulaCnt;i++)
        if(!pula[i].use)
            return pula[i];
    return pula[0];
}

Ttank *CheckCrossAnyTank(RECT rct,Ttank *eccept)
{
    for(int i=0;i<tankCnt;i++)
        if((eccept!=tank+i)&&(IsCross(rct,tank[i].GetRect())))
            return tank+i;
    return nullptr;
}

Tbrick *CheckCrossAnyBrick(RECT rct)
{
    for(int i=0;i<brickCnt;i++)
        if(brick[i].use && IsCross(rct,brick[i].GetRect()))
            return brick+i;
    return 0;
}

RECT areaPula = {0,0,width-1,height-1};
void Tpula::Move() {
    if(!use) return;
    for(int i=1;i<speed;i++)
    {
        x+=dirInc[dir].x;
        y+=dirInc[dir].y;
        RECT rct = {x,y,x,y};
        if(!IsCross(rct,areaPula))
        {
            use=0;
        }
        Tbrick *brick = CheckCrossAnyBrick(rct);
        if(brick)
        {
            use = 0;
            brick->use = (brick->tp == ttStone);
        }
        Ttank *tank = CheckCrossAnyTank(rct,0);
        if(tank)
        {
            use = 0;
            tank->SetToStart();
        }
        if(!use) return;
    }
}

void Tbrick::Show(mapHW &map) {
    if(!use)
        return;
    for(int i=rct.left;i<=rct.right;i++)
        for(int j=rct.top;j<=rct.bottom;j++)
        {
            if(tp==ttBrick)
                map[j][i] = fbrick;
            else
                map[j][i] = fstone;
        }

}

RECT area = {2,2,width-3,height-3};

void Ttank::Move(char w, char s, char a, char d, char fire) {
    char wsad[4] = {w,s,a,d};
    for(int i=0;i<4;i++)
        if(GetKeyState(wsad[i])<0)
            dir = (Tdir)i;
    POINT pt = dirInc[dir];
    Ttank old = *this;
    x += pt.x;
    y += pt.y;
    if(!IsCross(area,GetRect())||(CheckCrossAnyTank(GetRect(), this)!= nullptr)
        ||(CheckCrossAnyBrick(GetRect())!=0))
        *this = old;
    if(GetKeyState(fire)<0)
        GetFreePula().SetPula(x+pt.x*2,y+pt.y*2,dir);
}

void Ttank::Show(mapHW &map) {
    if(IsHoriz())
        for(int i=-1;i<2;map[y-1][x+i]=map[y+1][x+i]=catter,i++);
    else
        for(int i=-1;i<2;map[y+i][x-1]=map[y+i][x+2]=catter,i++);
    map[y][x] = tankC;
    POINT dt = dirInc[dir];
    map[y+dt.y][x+dt.x] = IsHoriz()?duloH:duloV;
}

void CreateBattleField()
{
    int pos = 0;
    for(int i=5;i<width-5;i+=3)
    {
        for(int j=1;j<height-1;j+=3)
        {
            brick[pos].SetPos(i,j);
            if(rand()%5==0) brick[pos].tp = ttStone;
            if(rand()%5==0) brick[pos].use = 0;
            pos++;
        }
    }
}

void Input(char const *c,char *str,int cnt)
{
    while (true)
    {
        cout << "input "<<c<<": ";
        cin.getline(str,cnt);
        if(cin.fail())
        {
            cout << "error ! try again.\n";
            cin.clear();
            cin.ignore(1000,'\n');
        } else
            break;
    }
}

point pp = {111,222};

void selectPart(int *&a)
{
    if(a==&pp.x) a= &pp.y;
    else a=&pp.x;
}

void print(int a=0,int b=0,int c=0)
{
    cout << a << ' ' << b << ' ' << c <<endl;
}

void print(float a=0,float b=0,float c=0)
{
    cout << a << ' ' << b << ' ' << c <<endl;
}

struct TPoint3{
    int x,y;
    TPoint3 operator- () {x = -x;y=-y;return *this;}
    TPoint3 &operator++() {++x,++y;}
    TPoint3 operator+ (int i) {x+=i;y+=i;return *this;}
    TPoint3 &operator= (int i) {x=y=i;return *this;}
};

int operator+ (int i,TPoint3 pnt) {return pnt.x+pnt.y+i;}
//TPoint3 operator- (TPoint3 pnt) {pnt.x=-pnt.x;pnt.y=-pnt.y;return pnt;}

struct TArray{
    int mas[5];
    int &operator[] (int i) {return mas[i];}
};

struct TLevel2
{
    TArray mas[2];
    TArray &operator[] (int i) {return mas[i];}
};

struct TMemory{
    int x;
    int operator() (){return x;}
    void operator() (int a) {x+=a;}
};

struct TPoint4
{
    int x,y;
    operator int ();
    TPoint4 &operator = (int a);
};

TPoint4::operator int() {
    return x+y;
}

TPoint4 & TPoint4::operator=(int a) {
    x=y=a;
    return *this;
}

class Shape
{
public:
    void setWidth(int w)
    {
        width_ = w;
    }
    void setHeight(int h)
    {
        heigth_ = h;
    }

protected:
    int width_;
    int heigth_;
};

class PaintCost
{
public:
    int getCost(int area)
    {
        return area * 70;
    }
};

class Rectange:public Shape,public PaintCost
{
public:
    int getArea()
    {
        return width_*heigth_;
    }
};

int main() {
#if 0
    cout << (abcd::z<<3)<< ' ' << f <<endl;
#endif

#if 0
    TPoint p{};
    p.x = 10;
    p.SetY(44);
    cout << p.x << ' ' << p.GetY() << '\n' <<endl;

    TPoint1 p1{};
    p1.x = 10;
    p1.SetY(44);
    cout << p1.x << ' '<< p1.GetY() << '\n' <<endl;
#endif

#if 0
    Test p(1,'P'),a(2,'B');
    {
        Test c(3,'C');
        c.Print();
    }
    p.Print();
    cout << "最后运行\n";
#endif

#if 0
    int userCnt = 2;
    TMap map1;
    TSnake snake1(&map1,3,1);
    TSnake snake2(&map1,77,1);
    snake1.Init(10,5,dirRight);
    snake2.Init(70,5,dirLeft);
    do {
        bool killl1 = snake1.UserControl('W','S','A','D')==reKill;
        if((killl1)||
        ((userCnt>=2)&&(snake2.UserControl(VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT)==reKill)))
        {
            snake1.Init(10,5,dirRight);
            snake2.Init(70,5,dirLeft);
            if(killl1)
                snake2.IncScore();
            else
                snake1.IncScore();
        }
        map1.Clear();
        snake1.PutOnMap();
        if(userCnt>=2) snake2.PutOnMap();
        map1.Show();
        Sleep(80);
    } while (GetKeyState(VK_ESCAPE)>=0);

    return 0;
#endif

#if 0
    Tabs *t = NULL;
    t = new Tabs;
    t->i = 777;
    t->Show();
    delete t;
    cout << "---------\n";

    t = new Tabs[5];
    delete [] t;
    cout << "---------\n";

    Tabs c;
    Tabs **b;
    b = new Tabs*[5];
    b[0] = new Tabs;
    delete b[0];
    b[1] = &c;
    delete [] b;
    cout << "---------\n";

    int *a = NULL;
    a = new int;
    *a = 5;
    cout << *a << endl;
    delete a;

    a = new int(7);
    cout << *a <<endl;
    delete a;

    a = new int [5];
    a[0] = 9;
    cout << a[0] <<endl;
    delete [] a;
#endif

#if 0
    Tkvk a,b;
    a.SetVal(25);
    b.SetVal(100);
    Show(a);
    Show(b);
#endif

#if 0
    Tbar a(0,0,1,1);
    for(int i=0;i<3;i++)
    {
        cout <<"for_"<<i<<'\n';
        Tbar b(5,5,10+i,10+i);
    }
#endif

#if 0
    TMas a(5,10,15);
    cout << " " <<a.Get() <<endl;

    for(int i=0;i<5;i++)
    {
        a.Up();
        cout << "up "<<a.Get()<<endl;
    }
    for(int i=0;i<5;i++)
    {
        a.Down();
        cout << "down "<<a.Get()<<endl;
    }
#endif

#if 0
    srand(time(NULL));
    int len = (rand()%8)+3;
    int *mas = new int [len];

    if (mas)
    {
        for(int i=0;i<len;i++)
        {
            mas[i] = rand();
            cout << mas[i] <<endl;
        }
        delete [] mas;
    }
#endif

#if 0
    int len = 10;
    TPoint2 *mas = new TPoint2[len];
    if(mas)
    {
        for(int i=0;i<len;i++)
        {
            mas[i].Init(rand(),rand());
            mas[i].Show();
        }
        delete [] mas;
    }
#endif

#if 0
    int userCnt = 2;
    TMap1 map1;
    map1.Clear();
    TSnake1 snake1(&map1,3,1);
    TSnake1 snake2(&map1,77,1);
    snake1.Init(10,5,dirRight);
    snake2.Init(70,5,dirLeft);

    do
    {

        bool killl1 = snake1.UserControl('W','S','A','D', true) == reKill;
        if((killl1)||
                ((userCnt>=2)&&(snake2.UserControl(VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,false)==reKill)))
        {
            snake1.Init(10,5,dirRight);
            snake2.Init(70,5,dirLeft);
            if(killl1)
                snake2.IncScore();
            else
                snake1.IncScore();
        }

        map1.Clear();
        snake1.PutOnMap();
        if(userCnt>=2) snake2.PutOnMap();
        map1.Show();
        Sleep(80);
    } while (GetKeyState(VK_ESCAPE)>=0);
#endif

#if 0
    int a = 1;
    float b;
    cin >> a >> b;
    cout << a <<'\n'<<b<<endl;

    float c,d;
    cin >> c;
    if(cin.fail())
        cin.clear();
    cin.ignore(1000,'\n');
    cin >> d;
    cout << c << '\n' << d <<endl;
#endif

#if 0
    char a[5],b[5],c[5],d[5];
    cin.get(a,5);
    cin.ignore(1000,'\n');
    cin.get(b,5);
    cin.ignore(1000,'\n');

    cin.getline(c,5);
    cin.clear();
    cin.get(d,5);
    cout << a << '\n' << b << '\n' << c << '\n' << d << endl;
#endif

#if 0
    int a;
    a = 7;
    int &x = a;
    x = 44;
    Mult2(x);
    cout << a << endl << &x << endl << &a <<endl;
    p = 1;
    GetParam() = 33;
    cout << p << endl;

    point p1 = {10,20};
    int &x2 = p1.x;
    x2 = 55;
    point &t = p1;
    t.y = 30;
    cout << p1.x << ' '<<p1.y<<endl;

    int a1 = 11;
    int a2 = 22;
    int *p2 = &a1;
    int * &k = p2;
    k = &a2;
//    *k = a2;

    cout << a1 <<' '<< *p2 <<endl;
#endif

#if 0
    double f;
    proc();
    proc(10);
    proc(f);
#endif

#if 0
    T1 a;
    a.show();
    a.show(55);

    T1 b(6);
#endif

#if 0
    T1 b;
    proc1(b);
    T1 c(b);
#endif

#if 0
    SetConsoleOutputCP(437);
    srand(time(0));
    CreateBattleField();
    do
    {
        tank[0].Move('W','S','A','D', VK_SPACE);
        tank[1].Move(38,40,37,39, 13);
        for(int i=0;i<pulaCnt;pula[i++].Move());

        scr.Clear();
        for (int i=0;i<brickCnt;brick[i++].Show(scr.map));
        for (int i=0;i<tankCnt;tank[i++].Show(scr.map));
        for (int i=0;i<pulaCnt;pula[i++].Show(scr.map));
        scr.Show();

        Sleep(100);
    }
    while (GetKeyState(VK_ESCAPE)>=0);
#endif

#if 0
    char x[10],y[10];
    Input("str A",x,10);
    Input("str B",y,10);

    cout << x << ":"<<y<<endl;
#endif

#if 0
    int *p = 0;

    selectPart(p);
    cout << *p << endl;
    selectPart(p);
    cout << *p << endl;
#endif

#if 0
    print(11,2);
    print(.4f,22.3);
#endif

#if 0
    TPoint3 p = {4,6},p2 = {1,2};
    p=-p;
    cout << p.x << ' ' <<p.y<<endl;
    ++p;
    cout << p.x << ' ' <<p.y<<endl;
    p = p+10;
    cout << p.x << ' ' <<p.y<<endl;
    p = 20;
    cout << p.x << ' ' <<p.y<<endl;
    p = 10+(p2+100);
    cout << p.x << ' ' <<p.y<<endl;
    p2 = {1,2};
    p = 10+p2+100;
    cout << p.x << ' ' <<p.y<<endl;
#endif

#if 0
    TArray array = {1,2,3,4,5};
    cout << array[1] << endl;

    TLevel2 a = {1,2,3,4,5, 6,7,8,9,10};
    a[1][2] = 333;
    for(int y=0;y<2;y++)
    {
        for(int x=0;x<5;x++)
            cout << a[y][x] << ' ';
        cout << '\n';
    }

    TMemory mem = {5};
    mem(7);
    cout << mem() <<endl;

    TPoint4 p = {10,20};
    p = 50;
    cout << (int)p<<endl;
#endif

#if 0
    Rectange rect;
    rect.setWidth(20);
    rect.setHeight(40);

    int area_ = rect.getArea();
    cout << rect.getArea() << endl;
    cout << rect.getCost(area_) << endl;
#endif

}
