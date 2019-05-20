// Forward declaration of the knows API.
bool knows(int a, int b);

class Solution {
public:
    /**
     * @param n a party with n people
     * @return the celebrity's label or -1
     */
    int findCelebrity(int n) {
        // Write your code here

        /**
         *  knows(a, b)
         *  -> true  -> a knows b -> a is not the celebrity.
         *  -> false -> a does not know b -> b is not the celebrity.
         */

        int a = 0, b = n - 1;
        while (a < b) {
            if (knows(a, b)) {
                ++a;
            } else {
                --b;
            }
        }

        for (int i = 0 ; i < n - 1 ; ++i) {
            if (i == a) {
                continue;
            }

            if (knows(a, i) || !knows(i, a)) {
                return -1;
            }
        }

        return a;
    }
};