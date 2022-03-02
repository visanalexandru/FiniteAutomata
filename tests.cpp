//
// Created by visan on 2/25/22.
//

#define CATCH_CONFIG_MAIN

#include"catch.hpp"
#include"DFA.h"
#include"EN-DFA.h"

TEST_CASE("DFA-Words that start with 0 and end in 1") {
    DFA dfa;
    dfa.add_edge(1, 4, '1');
    dfa.add_edge(4, 4, '1');
    dfa.add_edge(4, 4, '0');
    dfa.add_edge(1, 2, '0');
    dfa.add_edge(2, 2, '0');
    dfa.add_edge(2, 3, '1');
    dfa.add_edge(3, 2, '0');
    dfa.add_edge(3, 3, '1');
    dfa.set_final(3);

    REQUIRE(dfa.valid("0000101010101111", 1).valid == true);
    REQUIRE(dfa.valid("0000101010101111", 1).path ==
            std::vector<int>{1, 2, 2, 2, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 3, 3, 3});
    REQUIRE(dfa.valid("10111010101", 1).valid == false);
    REQUIRE(dfa.valid("00", 1).valid == false);
    REQUIRE(dfa.valid("001", 1).valid == true);
    REQUIRE(dfa.valid("001", 1).path == std::vector<int>{1, 2, 2, 3});
    REQUIRE(dfa.valid("01000000", 1).valid == false);
    REQUIRE(dfa.valid("01101001", 1).path == std::vector<int>{1, 2, 3, 3, 2, 3, 2, 2, 3});
}

TEST_CASE("DFA-Words that start with an odd-number of 0s, followed by a one, and 1 or more additional letters.") {
    DFA dfa;
    dfa.add_edge(1, 2, '0');
    dfa.add_edge(2, 1, '0');
    dfa.add_edge(1, 5, '1');
    dfa.add_edge(5, 5, '0');
    dfa.add_edge(5, 5, '1');
    dfa.add_edge(2, 3, '1');
    dfa.add_edge(3, 4, '0');
    dfa.add_edge(3, 4, '1');
    dfa.add_edge(4, 4, '1');
    dfa.add_edge(4, 4, '0');
    dfa.set_final(4);
    REQUIRE(dfa.valid("00010001010010", 1).valid == true);
    REQUIRE(dfa.valid("0010001010010", 1).valid == false);
    REQUIRE(dfa.valid("000", 1).valid == false);
    REQUIRE(dfa.valid("0001", 1).valid == false);
    REQUIRE(dfa.valid("00010", 1).valid == true);
    REQUIRE(dfa.valid("100001", 1).valid == false);
}

TEST_CASE("DFA-Words that start with 0 and have an odd length, or words that start with 1 and have an even length") {
    DFA dfa;
    dfa.add_edge(1, 2, '0');
    dfa.add_edge(2, 3, '0');
    dfa.add_edge(2, 3, '1');
    dfa.add_edge(3, 2, '0');
    dfa.add_edge(3, 2, '1');
    dfa.add_edge(1, 4, '1');
    dfa.add_edge(4, 5, '0');
    dfa.add_edge(4, 5, '1');
    dfa.add_edge(5, 4, '0');
    dfa.add_edge(5, 4, '1');
    dfa.set_final(2);
    dfa.set_final(5);
    REQUIRE(dfa.valid("0101010111100", 1).valid == true);
    REQUIRE(dfa.valid("0010111100", 1).valid == false);
    REQUIRE(dfa.valid("111010101011", 1).valid == true);
    REQUIRE(dfa.valid("101011101100011", 1).valid == false);
}

TEST_CASE("N-DFA-Words that contain 00 or 11 as a substring") {
    N_DFA ndfa;
    ndfa.add_edge(1, 1, '0');
    ndfa.add_edge(1, 1, '1');
    ndfa.add_edge(1, 2, '0');
    ndfa.add_edge(2, 4, '0');
    ndfa.add_edge(1, 3, '1');
    ndfa.add_edge(3, 4, '1');
    ndfa.add_edge(4, 4, '0');
    ndfa.add_edge(4, 4, '1');
    ndfa.set_final(4);
    REQUIRE(ndfa.valid("0101010101", 1).valid == false);
    REQUIRE(ndfa.valid("01011", 1).valid == true);
    REQUIRE(ndfa.valid("01011", 1).path == std::vector<int>{1, 1, 1, 1, 3, 4});
    REQUIRE(ndfa.valid("01", 1).valid == false);
    REQUIRE(ndfa.valid("00", 1).valid == true);
    REQUIRE(ndfa.valid("00", 1).path == std::vector<int>{1, 2, 4});
    REQUIRE(ndfa.valid("10", 1).valid == false);
    REQUIRE(ndfa.valid("10101101010", 1).valid == true);
    REQUIRE(ndfa.valid("10101101010", 1).path == std::vector<int>{1, 1, 1, 1, 1, 3, 4, 4, 4, 4, 4, 4});
}

TEST_CASE("N-DFA-Words that end with 101") {
    N_DFA ndfa;
    ndfa.add_edge(1, 1, '0');
    ndfa.add_edge(1, 1, '1');
    ndfa.add_edge(1, 2, '1');
    ndfa.add_edge(2, 3, '0');
    ndfa.add_edge(3, 4, '1');
    ndfa.set_final(4);

    REQUIRE(ndfa.valid("101011101010", 1).valid == false);
    REQUIRE(ndfa.valid("111111", 1).valid == false);
    REQUIRE(ndfa.valid("01011101", 1).valid == true);
    REQUIRE(ndfa.valid("01011101", 1).path == std::vector<int>{1, 1, 1, 1, 1, 1, 2, 3, 4});
    REQUIRE(ndfa.valid("00000111101", 1).valid == true);
    REQUIRE(ndfa.valid("00000111101", 1).path == std::vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4});
    REQUIRE(ndfa.valid("22101", 1).valid == false);
}

TEST_CASE("N-DFA-Words that only contain 'a' or words of the form 'ab'*") {
    N_DFA ndfa;
    ndfa.add_edge(1, 2, 'a');
    ndfa.add_edge(2, 2, 'a');
    ndfa.add_edge(1, 3, 'a');
    ndfa.add_edge(3, 4, 'b');
    ndfa.add_edge(4, 3, 'a');
    ndfa.set_final(1);
    ndfa.set_final(2);
    ndfa.set_final(4);
    REQUIRE(ndfa.valid("ababbab", 1).valid == false);
    REQUIRE(ndfa.valid("aaaaaa", 1).valid == true);
    REQUIRE(ndfa.valid("aaaaaa", 1).path == std::vector<int>{1, 2, 2, 2, 2, 2, 2});
    REQUIRE(ndfa.valid("a", 1).valid == true);
    REQUIRE(ndfa.valid("a", 1).path == std::vector<int>{1, 2});
    REQUIRE(ndfa.valid("ababababab", 1).valid == true);
    REQUIRE(ndfa.valid("ababababab", 1).path == std::vector<int>{1, 3, 4, 3, 4, 3, 4, 3, 4, 3, 4});
    REQUIRE(ndfa.valid("bababab", 1).valid == false);
}


TEST_CASE("EN-DFA-All words that end in 0 or that contain only 1s") {
    EN_DFA endfa;
    endfa.add_edge(1, 1, '1');
    endfa.add_epsilon_edge(2, 1);
    endfa.add_epsilon_edge(2, 3);
    endfa.add_edge(3, 3, '0');
    endfa.add_edge(3, 3, '1');
    endfa.add_edge(3, 4, '0');
    endfa.set_final(1);
    endfa.set_final(4);
    REQUIRE(endfa.valid("1110101101", 2).valid == false);
    REQUIRE(endfa.valid("0001010", 2).valid == true);
    REQUIRE(endfa.valid("0001010", 2).path == std::vector<int>{2, 3, 3, 3, 3, 3, 3, 4});
    REQUIRE(endfa.valid("11111110", 2).valid == true);
    REQUIRE(endfa.valid("11111110", 2).path == std::vector<int>{2, 3, 3, 3, 3, 3, 3, 3, 4});
    REQUIRE(endfa.valid("0000000001", 2).valid == false);
    REQUIRE(endfa.valid("11111111111", 2).valid == true);
    REQUIRE(endfa.valid("11111111111", 2).path == std::vector<int>{2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1});
    REQUIRE(endfa.valid("11101111111", 2).valid == false);
}

TEST_CASE("EN-DFA-Words that only contain 'a' or words of the form 'ab'*") {
    EN_DFA endfa;
    endfa.add_epsilon_edge(1, 2);
    endfa.add_edge(2, 2, 'a');
    endfa.add_epsilon_edge(1, 3);
    endfa.add_edge(3, 4, 'a');
    endfa.add_edge(4, 5, 'b');
    endfa.add_epsilon_edge(5, 3);
    endfa.set_final(2);
    endfa.set_final(5);
    REQUIRE(endfa.valid("ababbab", 1).valid == false);
    REQUIRE(endfa.valid("aaaaaa", 1).valid == true);
    REQUIRE(endfa.valid("aaaaaa", 1).path == std::vector<int>{1, 2, 2, 2, 2, 2, 2});
    REQUIRE(endfa.valid("a", 1).valid == true);
    REQUIRE(endfa.valid("a", 1).path == std::vector<int>{1, 2});
    REQUIRE(endfa.valid("ababababab", 1).valid == true);
    REQUIRE(endfa.valid("ababababab", 1).path == std::vector<int>{1, 4, 3, 4, 3, 4, 3, 4, 3, 4, 5});
    REQUIRE(endfa.valid("bababab", 1).valid == false);
}


TEST_CASE("EN-DFA-Words that have either the numbers of 0's odd or the number of 1's not a multiple of 3, or both ") {
    EN_DFA endfa;
    endfa.add_epsilon_edge(1, 2);
    endfa.add_edge(2, 3, '0');
    endfa.add_edge(2, 2, '1');
    endfa.add_edge(3, 2, '0');
    endfa.add_edge(3, 3, '1');
    endfa.add_epsilon_edge(1, 4);
    endfa.add_edge(4, 4, '0');
    endfa.add_edge(4, 5, '1');
    endfa.add_edge(5, 6, '1');
    endfa.add_edge(6, 4, '1');
    endfa.add_edge(6, 6, '0');
    endfa.add_edge(5, 5, '0');
    endfa.set_final(3);
    endfa.set_final(5);
    endfa.set_final(6);

    REQUIRE(endfa.valid("000", 1).valid == true);
    REQUIRE(endfa.valid("000", 1).path == std::vector<int>{1, 3, 2, 3});
    REQUIRE(endfa.valid("0000", 1).valid == false);
    REQUIRE(endfa.valid("010110", 1).valid == true);
    REQUIRE(endfa.valid("010110", 1).path == std::vector<int>{1, 3, 3, 2, 2, 2, 3});
    REQUIRE(endfa.valid("111111", 1).valid == false);
    REQUIRE(endfa.valid("1101111", 1).valid == true);
    REQUIRE(endfa.valid("1101111", 1).path == std::vector<int>{1, 2, 2, 3, 3, 3, 3, 3});
    REQUIRE(endfa.valid("1100", 1).valid == true);
    REQUIRE(endfa.valid("11001", 1).valid == false);
}