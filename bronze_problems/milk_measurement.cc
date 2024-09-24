#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#define USE_FREOPEN

int solve(std::vector<std::tuple<int, std::string, int>> measurements) {
  std::sort(measurements.begin(), measurements.end());

  int num_picture_switches{};
  std::vector<bool> pictures{true, true, true};  // Bessie, Elsie, Mildred
  std::vector<int> milk_amount{7, 7, 7};

  for (std::tuple<int, std::string, int> measurement : measurements) {
    std::string current_name = std::get<1>(measurement);
    int current_milk_change = std::get<2>(measurement);
    bool switch_picture = false;

    if (current_name == "Bessie") {
      milk_amount[0] += current_milk_change;
    } else if (current_name == "Elsie") {
      milk_amount[1] += current_milk_change;
    } else if (current_name == "Mildred") {
      milk_amount[2] += current_milk_change;
    }

    int max_milk_amount = *max_element(milk_amount.begin(), milk_amount.end());

    for (int i = 0; i < 3; i++) {
      if (milk_amount[i] < max_milk_amount && pictures[i]) {
        pictures[i] = false;
        switch_picture = true;
      } else if (milk_amount[i] == max_milk_amount && !pictures[i]) {
        pictures[i] = true;
        switch_picture = true;
      }
    }

    if (switch_picture) {
      num_picture_switches++;
    }
  }

  return num_picture_switches;
}

int main() {
#ifdef USE_FREOPEN
  freopen("measurement.in", "r", stdin);
  freopen("measurement.out", "w", stdout);
#endif

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n{};
  std::cin >> n;
  std::vector<std::tuple<int, std::string, int>> measurements;

  int date{};
  std::string name{};
  int milk_change{};

  for (int i = 0; i < n; i++) {
    std::cin >> date >> name >> milk_change;
    std::tuple<int, std::string, int> temp_tuple{tie(date, name, milk_change)};

    measurements.push_back(temp_tuple);
  }

  std::cout << solve(measurements) << "\n";  // Should output 3
}