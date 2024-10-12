#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <limits.h>
#include <math.h>
using namespace std;

int ground[52][52];
const int dy[8] = {-1, 0, 1, 0, 1, -1, 1, -1};
const int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int stun[31] = { 0 };
bool deadSanta[31] = {false};
pair<int, int> rudolf;
map<int, pair<int, int>> santa;
int n, m, p, c, d;
int hunting;
int answer[31];

int calD(int y1, int  x1, int y2, int x2){
    return (int)pow((y1-y2), 2)+pow((x1-x2), 2);
}

void moveSanta(int direct, int moveSantaNum, bool isRudolf){
    int y, x;
    tie(y, x) = santa[moveSantaNum];
    int ny, nx;
     if(isRudolf){
        ny = y + dy[direct];
        nx = x + dx[direct];
    }else{
        ny = y - dy[direct];
        nx = x - dx[direct];
    }
    if(ny <= 0 || ny > n || nx <= 0 || nx > n){
        deadSanta[moveSantaNum] = true;
        hunting -= 1;
        return;
    }
    if(ground[ny][nx] != 0){
        int nextSantaNum = ground[ny][nx];
        moveSanta(direct, nextSantaNum, isRudolf);
    }
    santa[moveSantaNum] = {ny, nx};
    ground[ny][nx] = moveSantaNum;
}


void bump(int direct, int santaNum, int point, bool isRudolf){
    answer[santaNum] += point;
    stun[santaNum] = 2;
    int y, x;
    tie(y, x)= santa[santaNum];
    ground[y][x] = 0;
    int ny, nx;
    if(isRudolf){
        ny = y + point*dy[direct];
        nx = x + point*dx[direct];
    }else{
        ny = y - point*dy[direct];
        nx = x - point*dx[direct];
    }
    if(ny <= 0 || ny > n || nx <= 0 || nx > n){
        deadSanta[santaNum] = true;
        hunting -= 1;
        return;
    }
    if(ground[ny][nx] != 0){
        int moveSantaNum = ground[ny][nx];
        moveSanta(direct, moveSantaNum, isRudolf);
    }
    santa[santaNum] = {ny, nx};
    ground[ny][nx] = santaNum;
}


void goRudof(int y, int x){
    int tempMax = INT_MAX;
    int santaNum = -1;
    for(int j = 1; j <= p; j++){
        if(deadSanta[j])continue;
        int sy, sx, temp;
        tie(sy, sx) = santa[j];
        temp = calD(y, x, sy, sx);
        if(tempMax < temp)continue;
        if(tempMax > temp){
            santaNum = j;
            tempMax = temp;
            continue;
        }
        int oy, ox;
        tie(oy, ox) = santa[santaNum];
        if(sy > oy){
            santaNum = j;
        }else if(sy == oy){
            if(sx > ox){
                santaNum = j;
            }
        }  
    }
    
    int cy, cx;
    tie(cy, cx) = santa[santaNum];
    int moveD = INT_MAX;
    int next = -1;
    for(int i = 0; i <8; i++){
        int ny = y + dy[i];
        int nx = x + dx[i];
        if(ny <= 0 || ny > n || nx <= 0 || nx > n)continue;
        int temp = calD(ny, nx, cy, cx);
        if(moveD > temp){
            moveD = temp;
            next = i;
        }
    }
    y = y+dy[next];
    x = x+dx[next];
    rudolf = {y, x};
    if(ground[y][x] != 0)bump(next, santaNum, c, true);
}

void goSanta(){
    int rudolfY, rudolfX;
    tie(rudolfY, rudolfX) = rudolf;
    int y, x;
    int closest , next;
    for(int i = 1; i <= p; i++){
        if(deadSanta[i])continue;
        if(stun[i])continue;
        tie(y, x) = santa[i];
        int temp;
        closest = calD(rudolfY, rudolfX, y, x);
        next = -1;
        for(int j = 0; j < 4; j++){
            int ny = y + dy[j];
            int nx = x + dx[j];
            if(ny <= 0 || ny > n || nx <= 0 || nx > n)continue;
            if(ground[ny][nx])continue;
            temp = calD(rudolfY, rudolfX, ny, nx);
            if(closest > temp){
                closest = temp;
                next = j;
            }
        }
        if(next == -1)continue;
        int my = y +dy[next];
        int mx = x +dx[next];
        santa[i] = {my, mx};
        if(rudolfY == my && rudolfX == mx){
        	ground[y][x] = 0;
            bump(next, i, d, false);
        }else{
            ground[y][x] = 0;
            ground[my][mx] = i;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m >> p >> c >> d;
    int y, x;
    cin >> y >> x;
    rudolf = {y, x};
    for(int i = 0; i < p; i++){
        int id;
        cin >> id >> y >> x;
        santa[id] = {y, x};
        ground[y][x] = id;
    }
    hunting = p;
    while(hunting != 0){
        tie(y,x) = rudolf;
        goRudof(y, x);
        goSanta();
        for(int i = 1; i <= p; i++){
        	if(deadSanta[i] == false)answer[i] += 1;
            if(stun[i])stun[i]--;
        }
        m--;
        if(m <= 0)break;
    }
    for(int i = 1; i <= p; i++){
        cout << answer[i] << " ";
    }
    return 0;
}