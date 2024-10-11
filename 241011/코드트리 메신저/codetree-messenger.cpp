#include <iostream>
#include <map>
#include <vector>
#include <tuple>
using namespace std;
int n, q;
int parents[100001];
int authority[100001];
int alarm[100001];
bool mute[100001] = { false };
map<int, vector<int>> cMap;
int alarmStatus[100001][22];


void countAlarm(int number){
    if(cMap[number].size()){
        for(int i = 0; i < cMap[number].size(); i++){
            countAlarm(cMap[number][i]);
            for(int j = 1; j < 22; j++){
            alarmStatus[number][j-1] += alarmStatus[cMap[number][i]][j];
            }
        }
        for(int i = 0; i < 22; i++){
            alarm[number]+=alarmStatus[number][i];
        }
    }
    if(number != 0 ){
        if(authority[number] > 20){
            alarmStatus[parents[number]][21] +=1;    
        }else{
            alarmStatus[parents[number]][authority[number]-1] +=1;
        }
    }
}

void muteRoom(int room, int mRoom, int auth, int number, bool isMute){
    if(room == 0)return;
    if(isMute){
        for(int j = number; j < 22; j++){
            alarmStatus[room][j-number] -= alarmStatus[mRoom][j];
            alarm[room] -= alarmStatus[mRoom][j];
        }
        if(auth >= 0){
            alarmStatus[room][auth] -= 1;
            alarm[room] -= 1;
        }
    }else{
        for(int j = number; j < 22; j++){
            alarmStatus[room][j-number] += alarmStatus[mRoom][j];
            alarm[room] += alarmStatus[mRoom][j];
        }
        if(auth >= 0){
            alarmStatus[room][auth] += 1;
            alarm[room] += 1;
        }
    }
    muteRoom(parents[room], mRoom, auth-1, number+1, isMute);   
}

void changePower(int room, int beforePower, int afterPower){
    if(room == 0)return;
    if(beforePower < 0 && afterPower < 0)return;
    if(beforePower >= 0){
        alarmStatus[room][beforePower] -= 1;
        alarm[room] -= 1;
    }
    if(afterPower >= 0){
        alarmStatus[room][afterPower] += 1;
        alarm[room] += 1;
    }
    if(mute[room])return;
    changePower(parents[room], beforePower-1, afterPower-1);
}

void changeRoom(int PRoom, int afterRoom, int beforeRoom, bool afterRoomMute, bool beforeRoomMute, int number, int afterAuth, int beforeAuth){
    if(PRoom == 0)return;
    if(beforeRoomMute == false){
        for(int j = number; j < 22; j++){
            alarmStatus[PRoom][j-number] -= alarmStatus[beforeRoom][j];
            alarm[PRoom] -= alarmStatus[beforeRoom][j];
        }
        if(beforeAuth >= 0){
            alarmStatus[PRoom][beforeAuth] -= 1;
            alarm[PRoom] -= 1;
        }
    }
    if(afterRoomMute == false){
        for(int j = number; j < 22; j++){
            alarmStatus[PRoom][j-number] += alarmStatus[afterRoom][j];
            alarm[PRoom] += alarmStatus[afterRoom][j];
        }
        if(afterAuth >= 0){
            alarmStatus[PRoom][afterAuth] += 1;
            alarm[PRoom] += 1;
        }
    }
    if(mute[PRoom])return;
    PRoom = parents[PRoom];
    changeRoom(PRoom, afterRoom, beforeRoom, afterRoomMute, beforeRoomMute, number+1, afterAuth-1, beforeAuth-1);
}

int main() {
   ios_base::sync_with_stdio(false);
   cin.tie(NULL); cout.tie(NULL);
    cin >> n >> q;
    for(int i = 0; i < q; i++){
        int order;
        cin >> order;
        if(order == 100){
            for(int j = 1; j <= n; j++){
                int p;
                cin >> p;
                parents[j] = p;
                cMap[p].push_back(j);
            }
            for(int j = 1; j <= n; j++){
                cin >> authority[j];
            }
            countAlarm(0);
        }else if(order == 200){
            int cRoom;
            cin >> cRoom;
            mute[cRoom] = !mute[cRoom];
            if(mute[cRoom]){
                muteRoom(parents[cRoom], cRoom, authority[cRoom]-1, 1, true);
            }else{
                muteRoom(parents[cRoom], cRoom, authority[cRoom]-1, 1, false);
            }
        }else if(order == 300){
            int cRoom, power;
            cin >> cRoom >> power;
            if(mute[cRoom] == false)changePower(parents[cRoom], authority[cRoom]-1, power-1);
            authority[cRoom] = power;
        }else if(order == 400){
            int aRoom, bRoom;
            cin >> aRoom >> bRoom;
            vector<int> v = cMap[parents[aRoom]];
            for(int j = 0; j < v.size(); j++){
                if(aRoom == v[j]){
                    v.erase(v.begin() + j);
                    v.push_back(bRoom);
                    break;
                }    
            }
            v = cMap[parents[bRoom]];
            for(int j = 0; j < v.size(); j++){
                if(bRoom == v[j]){
                    v.erase(v.begin() + j);
                    v.push_back(aRoom);
                    break;
                }    
            }
            int tempParents = parents[aRoom];
            parents[aRoom] = parents[bRoom];
            parents[bRoom] = tempParents;

            changeRoom(parents[aRoom], aRoom, bRoom, mute[aRoom], mute[bRoom], 1, authority[aRoom]-1, authority[bRoom]-1);
            changeRoom(parents[bRoom], bRoom, aRoom, mute[bRoom], mute[aRoom], 1, authority[bRoom]-1, authority[aRoom]-1);
            
        }else{
            int cRoom;
            cin >> cRoom;
            cout << alarm[cRoom] << "\n";
        }
    }
    
    return 0;
}