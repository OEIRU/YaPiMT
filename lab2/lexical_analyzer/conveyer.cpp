#include <algorithm>

#include "conveyer.h"

bool validate_transition(TRANSITION& transition, char symbol);

int levenshtein_distance(const string& s1, const string& s2) {
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            dp[i][j] = min({ dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost });
        }
    }
    return dp[m][n];
}

bool is_permutation(const string& s1, const string& s2) {
    if (s1.length() != s2.length()) return false;
    string sorted_s1 = s1, sorted_s2 = s2;
    sort(sorted_s1.begin(), sorted_s1.end());
    sort(sorted_s2.begin(), sorted_s2.end());
    return sorted_s1 == sorted_s2;
}

pair<string, int> find_closest_keyword(const string& lexeme, STATIC_TCONTROLLER& tstatic) {
    string closest_word;
    int closest_index = -1;
    int min_distance = 2; 

    vector<string>& keywords = tstatic.get_table(WORDS);
    for (int i = 0; i < keywords.size(); i++) {
        string keyword = keywords[i];

        int distance = levenshtein_distance(lexeme, keyword);
        
        if (distance < min_distance) {
            min_distance = distance;
            closest_word = keyword;
            closest_index = i;
        }
        
        else if (distance == min_distance && is_permutation(lexeme, keyword)) {
            closest_word = keyword;
            closest_index = i;
        }
    }

    if (min_distance <= 1 || closest_index != -1) {
        return { closest_word, closest_index };
    }

    return { "", -1 };
}

string CONVEYER::build() {
    char symbol;
    // тип лексемы : идентификатор
    vector<pair<TABLE_TYPE, int>> result;
    string not_published_word;

    cout << not_published_word << endl;

    lexical_exception *error = nullptr;

    do {
        symbol = input_stream.get();
        STATE next = get_next_state(symbol);
        cout << current_state << " \"" << string(collected_characters.data(), collected_characters.size()) << "\"" << endl;

        if (next == START) {
            string lexeme(collected_characters.data(), collected_characters.size());

            collected_characters.clear();

            if (current_state == WORD) {
                int keyword_position = tstatic.search(WORDS, lexeme);
                if (keyword_position != -1) {
                    // Проверка на составное ключевое слово (напр. else if)
                    if (result.size() > 0 && result[result.size() - 1].first == WORDS) {
                        int prev_keyword_index = result[result.size() - 1].second;
                        string prev_keyword = tstatic.get(WORDS, prev_keyword_index);
                        string combined_keyword = prev_keyword + " " + lexeme;
                        int combined_keyword_position = tstatic.search(WORDS, combined_keyword);
                        if (combined_keyword_position != -1) {
                            result.pop_back();
                            result.push_back({WORDS, combined_keyword_position});
                        }
                    } else {
                        result.push_back({WORDS, keyword_position});
                    }
                } else {
                    bool found = false;
                    TVARIABLE* res = &tvariables.search(lexeme, found);
                    if (!found) {
                        res = &tvariables.init(lexeme);
                        
                        auto closest_keyword = find_closest_keyword(lexeme, tstatic);
                        if (closest_keyword.second != -1) {
                            cout << "Предупреждение: не найдена лексема \"" << lexeme << "\". "
                                << "Возможно, Вы имели ввиду \"" << closest_keyword.first << "\"?";
                        }
                    }

                    result.push_back({VARIABLES, res->index});
                }
                
            } else if (current_state == OPERATOR) {
                int operator_position = tstatic.search(OPERATORS, lexeme);
                if (operator_position == -1) {
                    error = new lexical_exception("Не найден оператор " + lexeme + ".");
                    break;
                }
                result.push_back({OPERATORS, operator_position});
            } else if (current_state == NUMBER || current_state == DOUBLE) {
                bool found = false;
                TVARIABLE* res = &tconstants.search(lexeme, found);
                if (!found) {
                    res = &tconstants.init(lexeme);
                }
                result.push_back({CONSTANTS, res->index});
            } else if (current_state == SEPARATOR) {
                int symbol_position = tstatic.search(SYMBOLS, lexeme);
                result.push_back({SYMBOLS, symbol_position});
            }

            current_state = next;
            next = get_next_state(symbol);
        } else if (current_state == ERROR_WRONG_NUMBER) {
            cout << "Пошёл нахуй";
        }

        current_state = next;
        if (next != SPACE) collected_characters.push_back(symbol);
    } while (!input_stream.eof());

    ostringstream oss;
    bool first = true;

    for (const auto& pair : result) {
        if (!first) {
            oss << " ";
        }
        oss << static_cast<int>(pair.first) << ":" << pair.second;
        first = false;
    }

    return oss.str(); 
};


STATE CONVEYER::get_next_state(char symbol) {
    vector<TRANSITION>& transitions = states[current_state];
    for (int i = 0; i < transitions.size(); i++) {
        TRANSITION& transition = transitions[i];
        if (validate_transition(transition, symbol)) {
            return transition.to;
        }
    }

    throw lexical_exception("Avaliable transition not found");
}

bool validate_transition(TRANSITION& transition, char symbol) {
    bool found = transition.possible_chars.find(symbol) != transition.possible_chars.end();
    return found == !transition.excluding;
}