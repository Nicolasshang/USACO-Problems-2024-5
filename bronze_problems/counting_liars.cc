#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

#define USE_FREOPEN

int Solve(std::vector<std::pair<int, std::string>> cows, int N) {
  std::vector<int> num_liars_left(N);
  std::vector<int> num_liars_right(N);

  std::sort(cows.begin(), cows.end());

  for (int i = 1; i < cows.size(); i++) {
    num_liars_left[i] = num_liars_left[i - 1];

    // If the left cow's direction says that the hiding spot is less than our
    // current position, and their index is smaller than ours, they're lying.
    if (cows[i - 1].second == "L" && cows[i - 1].first < cows[i].first) {
      num_liars_left[i]++;
    }
  }

  for (int i = cows.size() - 1; i >= 0; i--) {
    num_liars_right[i] = num_liars_right[i + 1];

    // Same thing but with the right side
    if (cows[i + 1].second == "G" && cows[i + 1].first > cows[i].first) {
      num_liars_right[i]++;
    }
  }

  int num_liars_min{10'000'000};
  for (int i = 0; i < N; i++) {
    num_liars_min =
        std::min(num_liars_min, num_liars_left[i] + num_liars_right[i]);
  }

  return num_liars_min;
}

int main() {
#ifdef USE_FREOPEN
  freopen("liars.in", "r", stdin);
  freopen("liars.out", "w", stdout);
#endif

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int N{};
  std::cin >> N;

  int position{};
  std::string relation{};
  std::vector<std::pair<int, std::string>> cows;

  for (int i = 0; i < N; i++) {
    std::cin >> relation >> position;
    cows.push_back(std::make_pair(position, relation));
  }

  std::cout << Solve(cows, N) << '\n';
}