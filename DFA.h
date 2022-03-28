//
// Created by visan on 2/17/22.
//

#ifndef FINITE_AUTOMATA_DFA_H
#define FINITE_AUTOMATA_DFA_H

#include<map>
#include<vector>
#include<algorithm>
#include"NFA.h"

// This class implements a deterministic finite automaton
// Derives from NFA
class DFA : public NFA {
public:
    //Checks if the given word is accepted by the DFA.
    Result valid(const std::string &word, state start) override;
};

DFA::Result DFA::valid(const std::string &word, state start) {
    state current = start;

    // previous[state]-the previous state in the dfa path to a final node.
    std::map<std::pair<state, unsigned>, state> previous;
    unsigned depth = 1;

    for (letter x: word) {
        bool found = false;

        //Iterate through all the edges of the current state, see if an edge with the current symbol exists.
        for (const Edge &edge: graph[current]) {
            if (edge.transition == x) {
                found = true;
                previous[{edge.next, depth++}] = current;
                current = edge.next;
                break;
            }
        }
        //If we didn't find any edge for the current symbol, reject the word.
        if (!found) {
            return {false, {}};
        }
    }

    // If the current state is not final, the word is not accepted.
    if (!final[current]) {
        return {false, {}};
    }

    //Rebuild the path
    std::vector<state> path;
    state now = current;
    unsigned current_depth = word.size();
    while (current_depth > 0) {
        path.push_back(now);
        now = previous[{now, current_depth}];
        current_depth--;
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return {true, path};
}

#endif //FINITE_AUTOMATA_DFA_H
