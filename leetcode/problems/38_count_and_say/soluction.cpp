#include <iostream>
#include <assert.h>
using namespace std;

class Solution {
public:
    string countAndSay(int n) {
        string result = "1";

        for (int i = 0; i + 1 < n; i++) {
            string buff = "";
            int result_size = static_cast<int>(result.size());
            for (int index = 0; index < result_size; index++) {
                int count = 1;
                while (index + 1 < result_size && result[index] == result[index+1]) {
                    count++;
                    index++;
                }
                assert(count < 10);
                buff.push_back(count + '0');
                buff.push_back(result[index]);
            }

            result = buff;
        }

        return result;
    }
};

void test() {
    Solution s;
    string count_str;
    count_str = s.countAndSay(1);
    assert("1" == count_str);

    count_str = s.countAndSay(4);
    assert("1211" == count_str);

    count_str = s.countAndSay(9);
    assert("31131211131221" == count_str);
}

int main() {
    test();
    return 0;
}
