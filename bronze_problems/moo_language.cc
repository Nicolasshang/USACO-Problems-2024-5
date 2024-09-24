#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define USE_FREOPEN

// Find all sentences of the form [noun] [intransitive verb]
std::vector<std::string> FindAllTypeOneSentences(
    std::vector<std::string>& nouns,
    std::vector<std::string>& intransitive_verbs, int& num_periods) {
  std::vector<std::string> all_type_one_sentences;
  int max_possible_sentences{
      std::min(static_cast<int>(nouns.size()),
               static_cast<int>(intransitive_verbs.size()))};

  for (int i = 0; i < max_possible_sentences; i++) {
    std::string current_sentence = nouns[i] + " " + intransitive_verbs[i] + ".";
    all_type_one_sentences.push_back(current_sentence);
    // One period used for each sentence
    num_periods--;
  }

  // Since we can't repeat words, erase the words we used from the nouns and
  // intransitive verbs
  nouns.erase(nouns.begin(), nouns.begin() + max_possible_sentences);
  intransitive_verbs.erase(intransitive_verbs.begin(),
                           intransitive_verbs.begin() + max_possible_sentences);

  return all_type_one_sentences;
}

// Find all sentences of the form [noun] [transitive verb] [multiple nouns]
std::vector<std::string> FindAllTypeTwoSentences(
    std::vector<std::string> nouns, std::vector<std::string> transitive_verbs,
    int num_commas, int num_periods) {
  std::vector<std::string> all_type_two_sentences;
  int max_possible_sentences{
      std::min(static_cast<int>(nouns.size()) / 2,
               static_cast<int>(transitive_verbs.size()))};

  if (num_periods < max_possible_sentences) {
    max_possible_sentences = num_periods;
  }

  int num_nouns_used{};
  int cur_noun_index{};
  std::vector<std::string> nouns_left;

  for (int i = 0; i < max_possible_sentences; i++) {
    std::string current_sentence =
        nouns[i * 2] + " " + transitive_verbs[i] + " " + nouns[i * 2 + 1];

    all_type_two_sentences.push_back(current_sentence);
    cur_noun_index = i + 2;
    num_nouns_used++;
  }

  // Add the chained nouns after the transitive verb
  if (num_nouns_used < nouns.size() && cur_noun_index < nouns.size() &&
      all_type_two_sentences.size() > 0) {
    int num_nouns_left{static_cast<int>(nouns.size()) - num_nouns_used};
    std::string cur_sentence{all_type_two_sentences[0]};

    for (int i = cur_noun_index; i <= num_nouns_left; i++) {
      cur_sentence += ", " + nouns[i];
    }

    all_type_two_sentences[0] = cur_sentence;
  }

  return all_type_two_sentences;
}

// std::string Concatenate(std::vector<std::string> type_one_sentences,
//                         std::vector<std::string> type_two_sentences) {}

// The main solution function
std::pair<int, std::string> Solve(std::vector<std::string> nouns,
                                  std::vector<std::string> transitive_verbs,
                                  std::vector<std::string> intransitive_verbs,
                                  std::vector<std::string> conjunctions,
                                  int num_words, int num_commas,
                                  int num_periods) {
  int sentence_length{};
  std::string final_sentence{};

  std::vector<std::string> type_one_sentences =
      FindAllTypeOneSentences(nouns, intransitive_verbs, num_periods);

  std::vector<std::string> type_two_sentences =
      FindAllTypeTwoSentences(nouns, transitive_verbs, num_commas, num_periods);

  for (auto x = std::end(type_two_sentences);
       x != std::begin(type_two_sentences);) {
    std::cout << *--x << ' ';
  }

  return std::make_pair(sentence_length, final_sentence);
}

int main() {
#ifdef USE_FREOPEN
  freopen("language.in", "r", stdin);
  freopen("language.out", "w", stdout);
#endif

  int num_instances{};
  std::cin >> num_instances;

  int num_words{};
  int num_commas{};
  int num_periods{};

  for (int i = 0; i < num_instances; i++) {
    std::cin >> num_words >> num_commas >> num_periods;

    std::string word{};
    std::string word_type{};
    std::vector<std::string> nouns;
    std::vector<std::string> transitive_verbs;
    std::vector<std::string> intransitive_verbs;
    std::vector<std::string> conjunctions;

    if (num_words < 2) {
      std::cout << "empty sentence \n";
      continue;
    }

    for (int j = 0; j < num_words; j++) {
      std::cin >> word >> word_type;

      if (word_type == "noun") {
        nouns.push_back(word);
      } else if (word_type == "transitive-verb") {
        transitive_verbs.push_back(word);
      } else if (word_type == "intransitive-verb") {
        intransitive_verbs.push_back(word);
      } else if (word_type == "conjunction") {
        conjunctions.push_back(word);
      }
    }

    std::pair<int, std::string> solution{
        Solve(nouns, transitive_verbs, intransitive_verbs, conjunctions,
              num_words, num_commas, num_periods)};

    std::cout << solution.first << solution.second << '\n';
  }
}