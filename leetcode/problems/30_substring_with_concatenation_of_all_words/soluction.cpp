#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;
        if (words.size() == 0 || s.size() == 0) {
            return result;
        }

        unordered_map<string, int> words_map;
        for (int i = 0; i < words.size(); ++i) {
            words_map[words[i]]++;
        }

        int words_width = words[0].size();
        for (int  i = 0; i < words_width; ++i) {
            int left_index = i;
            int count = 0;
            unordered_map<string, int> check_map;
            for(int j = i; j <= (int)s.size() - words_width; j += words_width) {
                string check_s = s.substr(j, words_width);
                if (words_map.count(check_s) > 0) {
                    // matched in words_map
                    ++check_map[check_s];
                    // check valid
                    if (check_map[check_s] <= words_map[check_s]) {
                        ++count;
                    } else {
                        // not valid, left advance one more words
                        while (check_map[check_s] > words_map[check_s]) {
                            string check_s_left = s.substr(left_index, words_width);
                            --check_map[check_s_left];
                            if (check_map[check_s_left] < words_map[check_s_left]) {
                                --count;
                            }
                            left_index += words_width;
                        }
                    }

                    // result
                    if (words.size() == count) {
                        result.push_back(left_index);
                        --check_map[s.substr(left_index, words_width)];
                        left_index += words_width;
                        --count;
                    }
                } else {
                    // not match, reset
                    count = 0;
                    left_index = j + words_width;
                    check_map.clear();
                }
            }         
        }

        return result; 
    }
};

void test() {
    Solution sol;
// Input:
//   s = "barfoothefoobarman",
//   words = ["foo","bar"]
// Output: [0,9]
    vector<string> w1{"foo", "bar"};
    string s1 = "barfoothefoobarman";
    vector<int> result1 = sol.findSubstring(s1, w1);
    for (int i = 0; i < result1.size(); ++i) {
        cout << result1[i] << " ";
    }
    cout << endl;
// Input:
//   s = "wordgoodgoodgoodbestword",
//   words = ["word","good","best","word"]
// Output: []
    vector<string> w2{"word","good","best","word"};
    string s2 = "wordgoodgoodgoodbestword";
    vector<int> result2 = sol.findSubstring(s2, w2);
    for (int i = 0; i < result2.size(); ++i) {
        cout << result2[i] << " ";
    }
    cout << endl;

//     "barfoofoobarthefoobarman"
// ["bar","foo","the"]
// [6,9,12]
    vector<string> w3{"bar","foo","the"};
    string s3 = "barfoofoobarthefoobarman";
    vector<int> result3 = sol.findSubstring(s3, w3);
    for (int i = 0; i < result3.size(); ++i) {
        cout << result3[i] << " ";
    }
    cout << endl;

// "wordgoodgoodgoodbestword"
// ["word","good","best","good"]
// [8]
    vector<string> w4{"word","good","best","good"};
    string s4 = "wordgoodgoodgoodbestword";
    vector<int> result4 = sol.findSubstring(s4, w4);
    for (int i = 0; i < result4.size(); ++i) {
        cout << result4[i] << " ";
    }
    cout << endl;
// Input
// "aaaaaaaa"
// ["aa","aa","aa"]
// Expected
// [0,1,2]
    vector<string> w5{"aa","aa","aa"};
    string s5 = "aaaaaaaa";
    vector<int> result5 = sol.findSubstring(s5, w5);
    for (int i = 0; i < result5.size(); ++i) {
        cout << result5[i] << " ";
    }
    cout << endl;
}

int main() {
    test();
    return 0;
}