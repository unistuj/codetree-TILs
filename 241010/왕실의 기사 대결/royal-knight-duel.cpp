#include <iostream>
#include <map>
#include <memory.h>
#include <queue>
#include <tuple>
using namespace std;

struct Soldier{
    int r;
    int c;
    int h;
    int w;
    int k;
};
int chess[42][42];
int Bsol[42][42];
int Asol[42][42];
int l, n, q, solId, dir;
map<int, Soldier> sMap;
map<int, Soldier> tempSMap;
int outsol[31];
const int dy[4] = {1, 0, -1, 0};
const int dx[4] = {0, 1, 0, -1};
int visited[31];
bool flag = true;
int tempAnswer = 0;
int answer = 0;

void moveSol(){
    flag =true;
    tempAnswer = 0;
    memset(visited, 0, sizeof(visited));
    queue<int> orderedSolId;
    orderedSolId.push(solId);
    queue<pair<int, int>> movedSolId;
    tempSMap = sMap;
    visited[solId] = 1;
    while(orderedSolId.size()){
        solId = orderedSolId.front();
        orderedSolId.pop();
        queue<pair<int, int>> q;
        Soldier& soldier = tempSMap[solId];
        for(int a = soldier.r; a < soldier.r + soldier.h; a++){
            for(int b = soldier.c; b < soldier.c + soldier.w; b++){
                q.push({a,b});
            }
        }
        int ban = q.size();
        for(int i = 0; i < ban; i++){
            int y, x;
            tie(y, x)= q.front();
            q.pop();
            int ny = y+dy[dir];
            int nx = x+dx[dir];
            if(ny <= 0 || ny >= l || nx <=0 || nx >= l){
                flag = false;
                return;
            }
            if(chess[ny][nx] == 2){
                flag = false;
                return;
            }
            if(chess[ny][nx] == 1){
                soldier.k -=1;
                tempAnswer += 1;
            }
            if(Bsol[ny][nx] != 0){
                if(visited[Bsol[ny][nx]]){
                    orderedSolId.push(Bsol[ny][nx]);
                    visited[Bsol[ny][nx]] = 1;
                }
            }
            Asol[ny][nx] = solId;
        }
        soldier.r += dy[dir];
        soldier.c += dx[dir];
        if(soldier.k <= 0){
            for(int a = soldier.r; a < soldier.r + soldier.h; a++){
                for(int b = soldier.c; b < soldier.c + soldier.w; b++){
                    Asol[a][b] = 0;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> l >> n >> q;
    for(int i = 1; i <= l ; i++){
        for(int j = 1; j <= l; j++){
            cin >> chess[i][j];
        }
    }
    for(int i = 1; i <= n; i++){
        Soldier soldier;
        cin >> soldier.r >> soldier.c>> soldier.h >> soldier.w>> soldier.k;
        sMap[i] = soldier;
        for(int y = soldier.r; y < soldier.r + soldier.h; y++){
            for(int x = soldier.c; x < soldier.c + soldier.w; x++){
                Bsol[y][x] = i;
            }
        }
    }
    for(int i = 0; i < q; i++){
        cin >> solId >> dir;
        if(outsol[solId])continue;
        memset(Asol, 0, sizeof(Asol));
        moveSol();
        if(flag){
            sMap = tempSMap;
            memcpy(Bsol, Asol, sizeof(Bsol));
            answer += tempAnswer;
        }
    }
    
    cout << answer;
    return 0;
}