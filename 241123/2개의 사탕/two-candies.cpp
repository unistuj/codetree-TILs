#include <bits/stdc++.h>
using namespace std;
char box[10][10];
int n,m;
pair<int, int> red;
pair<int, int> blue;
pair<int, int> out;
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};
int answer = 11;

void goCandy(int direction, int y, int x, char type){
    int ny = y + dy[direction];
    int nx = x + dx[direction];
    if(box[ny][nx] == '.'){
        goCandy(direction, ny, nx, type);
    }else{
        box[ny][nx] = type;
        if(type == 'R'){
            red = {y, x};
            if(y == out.first && x == out.second)return;
            box[y][x] = 'R';
        }else{
            blue = {y, x};
            box[y][x] = 'B';
        }
    }
    return;
}

void moveBox(int count, int ry, int rx, int by, int bx){
    if(count >= answer)return;
    
    if(ry < by){
        goCandy(0, ry, rx, 'R');
        goCandy(0, by, bx, 'B');
        box[red.first][red.second] = '.';
        box[blue.first][blue.second] = '.';
        if(blue.first == out.first && blue.second == out.second)return;
        if(red.first == out.first && red.second == out.second){
            answer = count;
            return;
        }
        moveBox(count+1, red.first, red.second, blue.first, blue.second);
        goCandy(1,by, bx, 'B');
        goCandy(1, ry, rx, 'R');
        box[red.first][red.second] = '.';
        box[blue.first][blue.second] = '.';
        if(blue.first == out.first && blue.second == out.second)return;
        if(red.first == out.first && red.second == out.second){
            answer = count;
            return;
        }
        moveBox(count+1, red.first, red.second, blue.first, blue.second);
    }else{
        goCandy(0,by, bx, 'B');
        goCandy(0, ry, rx, 'R');
        box[red.first][red.second] = '.';
        box[blue.first][blue.second] = '.';
        if(blue.first == out.first && blue.second == out.second)return;
        if(red.first == out.first && red.second == out.second){
            answer = count;
            return;
        }
        moveBox(count+1, red.first, red.second, blue.first, blue.second);
        goCandy(1, ry, rx, 'R');
        goCandy(1,by, bx, 'B');
        box[red.first][red.second] = '.';
        box[blue.first][blue.second] = '.';
        if(blue.first == out.first && blue.second == out.second)return;
        if(red.first == out.first && red.second == out.second){
            answer = count;
            return;
        }
        moveBox(count+1, red.first, red.second, blue.first, blue.second);
    }
    if(rx < bx){
        goCandy(2, ry, rx, 'R');
        goCandy(2, by, bx, 'B');
        box[red.first][red.second] = '.';
        box[blue.first][blue.second] = '.';
        if(blue.first == out.first && blue.second == out.second)return;
        if(red.first == out.first && red.second == out.second){
            answer = count;
            return;
        }
        moveBox(count+1, red.first, red.second, blue.first, blue.second);
        goCandy(3,by, bx, 'B');
        goCandy(3, ry, rx, 'R');
        box[red.first][red.second] = '.';
        box[blue.first][blue.second] = '.';
        if(blue.first == out.first && blue.second == out.second)return;
        if(red.first == out.first && red.second == out.second){
            answer = count;
            return;
        }
        moveBox(count+1, red.first, red.second, blue.first, blue.second);
    }else{
        goCandy(2, by, bx, 'B');
        goCandy(2, ry, rx, 'R');
        box[red.first][red.second] = '.';
        box[blue.first][blue.second] = '.';
        if(blue.first == out.first && blue.second == out.second)return;
        if(red.first == out.first && red.second == out.second){
            answer = count;
            return;
        }
        moveBox(count+1, red.first, red.second, blue.first, blue.second);
        goCandy(3, ry, rx, 'R');
        goCandy(3, by, bx, 'B');
        box[red.first][red.second] = '.';
        box[blue.first][blue.second] = '.';
        if(blue.first == out.first && blue.second == out.second)return;
        if(red.first == out.first && red.second == out.second){
            answer = count;
            return;
        }
        moveBox(count+1, red.first, red.second, blue.first, blue.second);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    for(int i = 0; i < n; i++){        
        string temp;
        cin >> temp;
        for(int j = 0; j < m; j++){
            box[i][j] = temp[j];
            if(box[i][j] == 'R'){
                red = {i,j};
                box[i][j] = '.';
            }else if(box[i][j] == 'B'){
                blue = {i,j};
                box[i][j] = '.';
            }else if(box[i][j] == 'O'){
                out = {i,j};
                box[i][j] = '.';
            }else continue;
        }
    }
    
    moveBox(1, red.first, red.second, blue.first, blue.second);
    if(answer == 11){
        cout << -1 << endl;
    }else{
        cout << answer << endl;
    }
    return 0;
}