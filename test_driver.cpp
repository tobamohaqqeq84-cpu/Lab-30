//-----Test_driver.cpp-------
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
    if (line.empty()) return true;
    string plot, stageStr, plantId;
    stringstream ss(line);
    if(!getline(ss, plot, ',')) return false;
    if(!getline(ss, stageStr, ',')) return false;
    if(!getline(ss, plantId, ',')) return false;

    int st = stage_from_string(stageStr);
    if (st < 0) return false;
    env[plot][st].push_back(plantId);
    return true;

}
int main(){
    cout << "Testing stage_from_string";
    if (stage_from_string("SEEDLING") != SEEDLING) 
        cout << "FAIL" << endl;

    if(stage_from_string("GROWING") != GROWING)
        cout << "FAIL" << endl;
    if(stage_from_string("MATURE") != MATURE)
        cout << "FAIL" << endl;
    if(stage_from_string("TREE") != -1)
        cout << "FAIL" << endl;
    else
        cout << "All tests passed" << endl;
    cout << "\nTesting insert_from_csv_line()..." << endl;
    Env env;

    insert_from_csv_line("PLOT-A,SEEDLING,S001", env);
    insert_from_csv_line("PLOT-A,GROWING,S011", env);
    insert_from_csv_line("PLOT-A,MATURE,S016", env);
    insert_from_csv_line("PLOT-B,SEEDLING,S021", env);
    insert_from_csv_line("PLOT-C,WRONG,S099", env);

    cout << "Plot-A SEEDLING count: " << env["PLOT-A"][SEEDLING].size() << endl;
    cout << "Plot-A GROWING count: " << env["PLOT-A"][GROWING].size() << endl;    
    cout << "Plot-A MATURE count: " << env["PLOT-A"][MATURE].size() << endl;
    cout << "Plot-B SEEDLING count: " << env["PLOT-B"][SEEDLING].size() << endl;
    cout << "Plot-C MATURE count: " << env["PLOT-C"][MATURE].size() << endl;

cout << "\nIf all counts look correct, the test passed." << endl;
    return 0;
}