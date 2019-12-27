#include<bits/stdc++.h>

struct Info {
    int Y, M, D, h, m;
    std::string str;
};

struct Guard {
    int id;
    std::vector<std::vector<bool>> asleep;
    int totalSleep;
    Guard(int ID = 0) : id(ID), totalSleep(0) {}
};

int part1(std::map<int, Guard> &Map) {
    Guard maxSleepGuard;
    int maxSleep = -1;
    for(auto &p : Map) {
        if(p.second.totalSleep > maxSleep) {
            maxSleepGuard = p.second;
            maxSleep = p.second.totalSleep;
        }
    }
    int mostAsleepMinute = -1;
    int mostAsleep = 0;
    for(int i = 0; i < 60; ++i) {
        int sleepTime = 0;
        for(auto &x : maxSleepGuard.asleep) {
            sleepTime += x[i];
        }
        if(sleepTime > mostAsleep) {
            mostAsleep = sleepTime;
            mostAsleepMinute = i;
        }
    }
    return maxSleepGuard.id * mostAsleepMinute;
}

int part2(std::map<int, Guard> &Map) {
    int mostFreqMinute = -1;
    int mostFreq = 0;
    int mostFreqGuardId = -1;
    for(auto &p : Map) {
        int freqMinute = -1;
        int freq = 0;
        for(int i = 0; i < 60; ++i) {
            int t = 0;
            for(auto &x : p.second.asleep) {
                t += x[i];
            }
            if(t > freq) {
                freq = t;
                freqMinute = i;
            }
        }
        if(freq > mostFreq) {
            mostFreq = freq;
            mostFreqMinute = freqMinute;
            mostFreqGuardId = p.first;
        }
    }
    return mostFreqMinute * mostFreqGuardId;
}

int main() {
    // read input
    std::string line;
    std::vector<Info> logs;
    while(std::getline(std::cin, line)) {
        Info info;
        info.Y = stoi(line.substr(1, 4));
        info.M = stoi(line.substr(6, 2));
        info.D = stoi(line.substr(9, 2));
        info.h = stoi(line.substr(12, 2));
        info.m = stoi(line.substr(15, 2));
        info.str = line.substr(19);
        logs.push_back(info);
    }
    // sort by time
    std::sort(logs.begin(), logs.end(), [](const Info &a, const Info &b) {
        if(a.Y == b.Y) {
            if(a.M == b.M) {
                if(a.D == b.D) {
                    if(a.h == b.h) {
                        return a.m < b.m;
                    }
                    return a.h < b.h;
                }
                return a.D < b.D;
            }
            return a.M < b.M;
        }
        return a.Y < b.Y;
    });
    
    std::map<int, Guard> Map;
    int currGuardId = -1;
    std::vector<bool> sleepInfo(60, false);
    int ssleep = 0, esleep = 0;
    for(auto &info : logs) {
        if(info.str[0] == 'G') { // Guard #??? begin shift
            if(currGuardId != -1) {
                Map[currGuardId].asleep.push_back(sleepInfo);
                sleepInfo.assign(60, false);
            }
            currGuardId = stoi(info.str.substr(7, info.str.find('b', 7) - 8));
            if(Map.find(currGuardId) == Map.end()) {
                Guard guard(currGuardId);
                Map[currGuardId] = guard;
            }
        } else if(info.str[0] == 'f') {
            ssleep = info.m;
        } else if(info.str[0] == 'w') {
            esleep = info.m;
            for(int i = ssleep; i < esleep; ++i) sleepInfo[i] = true;
            Map[currGuardId].totalSleep += esleep - ssleep;
        }
    }
    // For debuging
    for(auto &p : Map) {
        std::cout << "Guard ID : " << p.first << "\t totalSleep : " << p.second.totalSleep << "\n";
        for(auto &x : p.second.asleep) {
            for(int i = 0; i < 60; ++i) {
                std::cout << (x[i] ? '#' : '.');
            }
            std::cout << std::endl;
        }
    }
    Map[currGuardId].asleep.push_back(sleepInfo);
    
    // part1
    std::cout << "the answer of part 1 is ";
    std::cout << part1(Map) << std::endl;
    
    // part2
    std::cout << "the answer of part 2 is ";
    std::cout << part2(Map) << std::endl;
}
