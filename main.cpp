#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <array>
#include <list>
    using namespace std;

enum Stage {SEEDLING = 0, GROWING =1, MATURE = 2};

using Buckets = array<list<string>, 3>;
using Env = map<string, Buckets>;

int stage_from_string(const string& s) {
    if (s == "SEEDLING") return SEEDLING;
    if (s == "GROWING")  return GROWING;
    if (s == "MATURE")   return MATURE;
    return -1;
}
bool insert_from_csv_line(const string& line, Env& env){
    if (!line.empty()) return true;
    istringstream ss(line);
    if(!getline(ss, plot, ',')) return false;
    if(!getline(ss, stageStr, ',')) return false;
    if(!getline(ss, plantId, ',')) return false;
    
    int st = stage_from_string(stageStr);
    if (st < 0) return false;
    env[plot][st].push_back(plantId);
    return true;

}
nt main(){
    cout << "Testing stage_from_string" << endl;
}
}
