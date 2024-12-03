#include "WhatAreYouDoing.h"
#include "cctype"
#include "strlib.h"

using namespace std;

void backtracking(vector<string>& words, vector<string>& collector, vector<vector<string>>& result, int index);
bool isWord(const string& str);
Set<string> collectToResult(vector<vector<string>>& allConditionCase, vector<string>& separators);
Set<string> allEmphasesOf(const string& sentence) {
    Vector<string> sentences = tokenize(sentence);

    vector<string> words;
    vector<string> separators;
    for (string sentence : sentences) {
        if (isWord(sentence)) {
            separators.push_back("");
            words.push_back(toLowerCase(sentence));
        } else {
            separators.push_back(sentence);
        }
    }

    vector<vector<string>> allConditionCase;
    vector<string> collection;
    backtracking(words, collection, allConditionCase, 0);

    Set<string> result = collectToResult(allConditionCase, separators);
    return result;
}

Set<string> collectToResult(vector<vector<string>>& allConditionCase, vector<string>& separators) {
    Set<string> answer;
    for (vector<string> iter : allConditionCase) {
        vector<string> vec = vector<string>(separators.begin(), separators.end());

        int i = 0;
        for (string& s : vec) {
            if (s == "") {
                s = iter[i++];
            }
        }

        string result;
        for (string& s : vec) {
            result += s;
        }

        answer.add(result);
    }

    return answer;
}

bool isWord(const string& str) {
    for (char ch : str) {
        if (!isalpha(ch)) {
            return false;
        }
    }
    return true;
}


void backtracking(vector<string>& words, vector<string>& collector, vector<vector<string>>& result, int index) {
    if (index >= words.size()) {
        result.push_back(collector);
        return;
    }

    //Left branch add upper case
    string upperCase = toUpperCase(words[index]);
    collector.push_back(upperCase);
    backtracking(words, collector, result, index + 1);
    collector.pop_back();


    //Right branch add lower case
    string lowerCase = toLowerCase(words[index]);
    collector.push_back(lowerCase);
    backtracking(words, collector, result, index + 1);
    collector.pop_back();
}
/* * * * * * Test Cases * * * * * */
#include "GUI/SimpleTest.h"

/* * * * * * Test cases from the starter files below this point. * * * * * */

PROVIDED_TEST("Enumerates all options in a simple case.") {
    Set<string> expected = {
        "hello",
        "HELLO",
    };

    EXPECT_EQUAL(allEmphasesOf("Hello"), expected);
}

PROVIDED_TEST("Each option has the right length.") {
    string sentence = "Hello, world!";
    for (string option: allEmphasesOf(sentence)) {
        EXPECT_EQUAL(option.length(), sentence.length());
    }
}

PROVIDED_TEST("Enumerates all options in a more typical case.") {
    Set<string> expected = {
        "you are?",
        "you ARE?",
        "YOU are?",
        "YOU ARE?"
    };

    EXPECT_EQUAL(allEmphasesOf("You Are?"), expected);
}

STUDENT_TEST("Enumerates all options for 'what ARE you doing?'") {
    Set<string> expected = {
        "what are you doing?",
        "what are YOU doing?",
        "what ARE you doing?",
        "what ARE YOU doing?",
        "WHAT are you doing?",
        "WHAT are YOU doing?",
        "WHAT ARE you doing?",
        "WHAT ARE YOU doing?",
        "what are you DOING?",
        "what are YOU DOING?",
        "what ARE you DOING?",
        "what ARE YOU DOING?",
        "WHAT are you DOING?",
        "WHAT are YOU DOING?",
        "WHAT ARE you DOING?",
        "WHAT ARE YOU DOING?"
    };

    EXPECT_EQUAL(allEmphasesOf("what ARE you doing?"), expected);
}

PROVIDED_TEST("Stress Test: Recursion only branches on words (should take under a second)") {
    /* We're producing a string consisting of fifty copies of the * character. This tokenizes
     * into fifty separate stars. A star is the same whether or not you capitalize it - there
     * is no such thing as an "upper-case" or "lower-case" star. Therefore, your code should
     * not try to form two versions of the sentence, one with the star capitalized and one
     * without, because the two versions will end up being the same and the work to compute
     * both options will dramatically increase the runtime.
     *
     * For reference, if you do try branching the recursion and checking what happens both if
     * you capitalize the star and if you don't, you'll try exploring 2^50 different possible
     * capitalizations. That's 1,125,899,906,842,624 options, and even doing a billion of
     * these a second is going to take over two years to generate them all! And of course,
     * that's all wasted work, since there's only one way to capitalize this sentence, and
     * that's just to leave it as-is.
     *
     * If your code is hanging when this test is running, it likely means that your code is
     * trying to enumerate all of these options. See if you can edit your code so that, if
     * you're given a non-word token, you just leave it as-is and don't change anything.
     */
    string punctuation(50, '*'); // 50 copies of *

    /* The only emphasis is itself. */
    Set<string> expected = {
        punctuation
    };

    EXPECT_EQUAL(allEmphasesOf(punctuation), expected);
}

PROVIDED_TEST("Stress test: Generates each option once (should take at most a few seconds)") {
    /* This sentence has 13 words in it. There are therefore 2^13 = 8192 possible emphases for
     * the words there, which is a big number but not so large that the computer can't handle
     * it if generates each emphasis exactly once.
     *
     * On the other hand, if your code tries to generate the same emphases multiple times,
     * this test may take a very, very long time to complete, and might even appear to freeze
     * up.
     *
     * If your code gets stuck in this test, trace through your code and confirm that you can't
     * produce the same emphasis multiple times. Check to make sure you aren't, for example,
     * looping over every token in the input sentence and deciding which one to capitalize
     * next. The recursion here follows more of an include/exclude type pattern (more like
     * subsets and combinations) than it does a "which is next?" type pattern (more like
     * permutations).
     */
    string yeats = "Turing and turning in a widening gyre / the falcon cannot hear the falconer.";
    EXPECT_EQUAL(allEmphasesOf(yeats).size(), 8192);
}
