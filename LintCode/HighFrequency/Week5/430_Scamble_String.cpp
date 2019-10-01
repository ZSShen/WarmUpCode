class Solution {
public:
    /**
     * @param s1: A string
     * @param s2: Another string
     * @return: whether s2 is a scrambled string of s1
     */
    bool isScramble(string &s1, string &s2) {
        // write your code here

        /**
         *   great
         *   => atgre, eatgr
         *             => tgrea
         *
         *  A scrambled version of a string can be generated by interexchanging
         *  its prefix and suffix. For example, "deabc" is derived from
         *  interexchaning "abc", the prefix, and "de", the suffix, of "abcde".
         *
         *  Given 2 strings, S and T, we can determine if T is a scrambled version
         *  of S by decompsing these 2 strings into 2 parts respectively and
         *  checking if these 2 substrings are equal:
         *
         *      S = Sp + Ss
         *      T = Tp + Ts
         *
         *      => Sp == Tp && Ss == Ts, scrambled one!
         *      => Sp == Ts && Ss == Tp, scrambled one!
         */

        std::unordered_map<std::string,
            std::unordered_map<std::string, bool>> memo;
        return canScramble(s1, s2, memo);
    }


private:
    bool canScramble(const auto& s, const auto& t, auto& memo) {

        // Check the cached result first.
        auto it_s = memo.find(s);
        if (it_s != memo.end()) {
            auto& inner = it_s->second;
            auto it_t = inner.find(t);
            if (it_t != inner.end()) {
                return it_t->second;
            }
        }

        // Check the string lengths.
        int n = s.length();
        int m = t.length();
        if (n != m) {
            return false;
        }

        if (n == 1) {
            bool res = s[0] == t[0];
            memo[s][t] = res;
            return res;
        }

        // Check the character composition.
        std::vector<int> freq_s(26, 0);
        std::vector<int> freq_t(26, 0);
        for (char ch : s) {
            ++freq_s[ch - 'a'];
        }
        for (char ch : t) {
            ++freq_t[ch - 'a'];
        }
        for (int i = 0 ; i < 26 ; ++i) {
            if (freq_s[i] != freq_t[i]) {
                memo[s][t] = false;
                return false;
            }
        }

        for (int i = 0 ; i < n - 1 ; ++i) {

            int l = i + 1;
            bool res =
                (canScramble(s.substr(0, l), t.substr(0, l), memo) &&
                 canScramble(s.substr(l, n - l), t.substr(  l, n - l), memo)) ||
                (canScramble(s.substr(0, l), t.substr(n - l, l), memo) &&
                 canScramble(s.substr(l, n - l), t.substr(0, n - l), memo));

            if (res) {
                memo[s][t] = true;
                return true;
            }
        }

        memo[s][t] = false;
        return false;
    }
};