//
// Created by visan on 2/26/22.
//
#include"N_DFA.h"

#ifndef FINITE_AUTOMATA_EN_DFA_H
#define FINITE_AUTOMATA_EN_DFA_H

class EN_DFA : public N_DFA {
private:
    //The graph of epsilon-edges.
    std::map<state, std::vector<state>> epsilon_edges;

    /* From a given state, we can reach other states without consuming
     * any tokens using epsilon-edges. This method adds all the states
     * that are reachable from this state by epsilon-edges to the set
     * using a breadth-first search.*/
    void add_epsilon_neighbours(state x, std::set<state> &next);

public:

    //Adds a new epsilon_edge between the two given states to the EN_DFA.
    void add_epsilon_edge(state a, state b);

    //Checks if the given word is accepted by the EN_DFA.
    bool valid(const std::string &word, state start) override;
};

void EN_DFA::add_epsilon_edge(state a, state b) {
    epsilon_edges[a].push_back(b);
}

void EN_DFA::add_epsilon_neighbours(state x, std::set<state> &next) {
    for (state neighbour: epsilon_edges[x]) {
        if (next.find(neighbour) == next.end()) { // We only process the state if it is not already in the set.
            next.insert(neighbour);
            add_epsilon_neighbours(neighbour, next);
        }
    }
}

bool EN_DFA::valid(const std::string &word, state start) {

    std::set<state> states = {start};
    add_epsilon_neighbours(start, states);

    for (letter x: word) {

        // The set for the next iteration of states.
        std::set<state> next;

        // Iterate through all the current states.
        for (state s: states) {
            add_neighbours(s, x, next);
        }

        // Now that we have states we can reach by consuming a token, we add their epsilon-neighbours.
        std::set<state> epsilon_next;
        for (state s: next) {
            add_epsilon_neighbours(s, epsilon_next);
        }

        next.insert(epsilon_next.begin(), epsilon_next.end());

        if (next.empty()) { // if there are no potential matches, reject the pattern.
            return false;
        }
        // The next set of states become the current set of states.
        states.swap(next);
    }

    // Now we need to check if at least one state is final.
    for (state s: states) {
        if (final[s]) {
            return true;
        }
    }
    // We did not find any final states, reject the pattern.
    return false;
}


#endif //FINITE_AUTOMATA_EN_DFA_H
