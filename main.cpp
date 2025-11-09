// Toba Mohaqqeq
// COMSC-210
// LAB-29

#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

using namespace std;

//-------stages and types--------
enum Stage { SEEDLING = 0, GROWING = 1, MATURE = 2 };
using Buckets = array<list<string>, 3>;
using Env = map<string, Buckets>;

// convert stage string to enum
int stage_from_string(const string &s) {
  if (s == "SEEDLING")
    return SEEDLING;
  if (s == "GROWING")
    return GROWING;
  if (s == "MATURE")
    return MATURE;
  return -1;
}
bool load_data(const string &path, Env &env) {
  ifstream file(path);
  if (!file.is_open()) {
    cerr << "Error: Could not open file " << path << endl;
    return false;
  }
  string line;
  size_t lines_read = 0;

  while (getline(file, line)) {
    if (line.empty())
      continue;

    stringstream ss(line);
    string plot, stageStr, plantId;
    if (!getline(ss, plot, ','))
      continue;
    if (!getline(ss, stageStr, ','))
      continue;
    if (!getline(ss, plantId, ','))
      continue;

    int st = stage_from_string(stageStr);
    if (st < 0) {
      cerr << "Warn: bad stage \"" << stageStr << "\" in line " << line << "\n";
      continue;
    }

    env[plot][st].push_back(plantId);
    ++lines_read;

    if (lines_read == 0) {
      cerr << "Error: no data found in file " << path << endl;
    }
    return false;
  }
  return true;
}
void print_env(const Env &env, int period = -1) {
  if (period < 0)
    cout << "\n=== Initial state ===\n";
  else
    cout << "\n=== After period " << period << " ===\n";

  cout << left << setw(10) << "Plot" << right << setw(10) << "SEED" << right
       << setw(12) << "GROW" << right << setw(10) << "MATURE" << endl;
  cout << string(42, '-') << "\n";

  for (const auto &[plot, buckets] : env) {
    cout << left << setw(10) << plot << right << setw(10)
         << buckets[SEEDLING].size() << right << setw(12)
         << buckets[GROWING].size() << right << setw(10)
         << buckets[MATURE].size() << endl;
  }
}

void simulate_step(Env &env, int t) {
  for (auto &[plot, buckets] : env) {

    if (!buckets[GROWING].empty()) {
      string id = buckets[GROWING].front();
      buckets[GROWING].pop_front();
      buckets[MATURE].push_back(id);
    }
    if (!buckets[SEEDLING].empty()) {
      string id = buckets[SEEDLING].front();
      buckets[SEEDLING].pop_front();
      buckets[GROWING].push_back(id);
    }
    if (t % 3 == 0) {
      buckets[SEEDLING].push_back("N" + to_string(t) + "_" + plot);
    }
  }
}

int main() {
  Env env;
  if (!load_data("data.csv", env)) {
    cerr << "HINT: ensure data.csv exists in the same folder. \n";
    return 1;
  }
  print_env(env, -1);
  const int PERIODS = 25;
  for (int t = 1; t <= PERIODS; ++t) {
    simulate_step(env, t);
    print_env(env, t);
  }
  cout << "\nSimulation complete.\n";
  return 0;
}

