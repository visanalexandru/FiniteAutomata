//
// Created by visan on 2/17/22.
//

#ifndef FINITE_AUTOMATA_DFA_H
#define FINITE_AUTOMATA_DFA_H

#include<map>
#include<vector>
#include"N_DFA.h"

// This class implements a deterministic finite automaton
// Derives from N_DFA
class DFA : public N_DFA {
public:
    //Checks if the given word is accepted by the DFA.
    bool valid(const std::string &word, state start) override;
};

bool DFA::valid(const std::string &word, state start) {
    state current = start;
    for (letter x: word) {
        bool found = false;

        //Iterate through all the edges of the current state, see if an edge with the current symbol exists.
        for (const Edge &edge: graph[current]) {
            if (edge.transition == x) {
                found = true;
                current = edge.next;
                break;
            }
        }
        //If we didn't find any edge for the current symbol, reject the word.
        if (!found) {
            return false;
        }
    }
    //We reached the end, the current state must be a final state.
    return final[current];
}

#endif //FINITE_AUTOMATA_DFA_H
