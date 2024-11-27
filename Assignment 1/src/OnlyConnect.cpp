/* File: OnlyConnect.cpp
 *
 * TODO: Edit these comments to describe anything interesting or noteworthy in your implementation.
 *
 * TODO: Edit these comments to leave a puzzle for your section leader to solve!
 */
#include "OnlyConnect.h"
#include "GUI/SimpleTest.h"
using namespace std;

bool shouldSkip(char ch);

string removeVowelLetter(string str, int index, int len);

string onlyConnectize(string phrase) {
    return removeVowelLetter(phrase, 0, phrase.length());
}

bool shouldSkip(char ch) {
    if (!isalpha(ch)) {
        return true;
    }

    ch = toupper(ch);
    if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' || ch == 'Y') {
        return true;
    }

    return false;
}

string removeVowelLetter(string str, int index, int len) {
    if (index >= len) {
        return "";
    }
    string result = removeVowelLetter(str, index + 1, len);

    char ch = toupper(str[index]);
    if (!shouldSkip(ch)) {
        return ch + result;
    }

    return result;
}

/*
 * replace locally without any external space cost.
 * Time: O(n) Space O(1)
 */
// string onlyConnectize(string phrase) {
//     int low = 0;
//     int fast = 0;
//     for (; fast < phrase.length(); ) {
//         char ch = phrase[fast];
//         if (shouldSkip(ch)) {
//             fast++;
//         } else {
//             ch = toupper(ch);
//             phrase[low] = ch;
//             low++;
//             fast++;
//         }
//     }
//     return phrase.substr(0, low);
// }
/* * * * * * Provided Test Cases * * * * * */

PROVIDED_TEST("Converts lower-case to upper-case.") {
    EXPECT_EQUAL(onlyConnectize("lowercase"), "LWRCS");
    EXPECT_EQUAL(onlyConnectize("uppercase"), "PPRCS");
}

PROVIDED_TEST("Handles non-letter characters properly.") {
    EXPECT_EQUAL(onlyConnectize("2.718281828459045"), "");
    EXPECT_EQUAL(onlyConnectize("'Hi, Mom!'"), "HMM");
}

PROVIDED_TEST("Handles single-character inputs.") {
    EXPECT_EQUAL(onlyConnectize("A"), "");
    EXPECT_EQUAL(onlyConnectize("+"), "");
    EXPECT_EQUAL(onlyConnectize("Q"), "Q");
}

PROVIDED_TEST("Own test.") {
    EXPECT_EQUAL(onlyConnectize(""), "");
    EXPECT_EQUAL(onlyConnectize("AAAAAAAAAAAA"), "");
    EXPECT_EQUAL(onlyConnectize("QQQQQQQQQQQ"), "QQQQQQQQQQQ");
    EXPECT_EQUAL(onlyConnectize("QAQBQQCQQDQ"), "QQBQQCQQDQ");
    EXPECT_EQUAL(onlyConnectize("中文"), "");
    EXPECT_EQUAL(onlyConnectize("😅"), "");
    EXPECT_EQUAL(onlyConnectize("\n"), "");
}




