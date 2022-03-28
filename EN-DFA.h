//
// Created by visan on 2/26/22.
//

#ifndef FINITE_AUTOMATA_EN_DFA_H
#define FINITE_AUTOMATA_EN_DFA_H

#include"NFA.h"
#include<algorithm>

class EN_DFA : public NFA {
private:
    //The graph of epsilon-edges.
    std::map<state, std::vector<state>> epsilon_edges;

    /* From a given state, we can reach other states without consuming
     * any tokens using epsilon-edges. This method adds all the states
     * that are reachable from this state by epsilon-edges to the set
     * using a breadth-first search. It also updates the "previous" map.*/
    void add_epsilon_neighbours(state x, std::set<state> &next, std::map<std::pair<state, unsigned>, state> &previous,
                                state origin, unsigned depth);

public:

    //Adds a new epsilon_edge between the two given states to the EN_DFA.
    void add_epsilon_edge(state a, state b);

    //Checks if the given word is accepted by the EN_DFA.
    Result valid(const std::string &word, state start) override;
};

void EN_DFA::add_epsilon_edge(state a, state b) {
    epsilon_edges[a].push_back(b);
}

void
EN_DFA::add_epsilon_neighbours(state x, std::set<state> &next, std::map<std::pair<state, unsigned>, state> &previous,
                               state origin, unsigned depth) {
    for (state neighbour: epsilon_edges[x]) {
        if (next.find(neighbour) == next.end()) { // We only process the state if it is not already in the set.
            next.insert(neighbour);
            previous[{neighbour, depth}] = origin;
            add_epsilon_neighbours(neighbour, next, previous, origin, depth);
        }
    }
}

EN_DFA::Result EN_DFA::valid(const std::string &word, state start) {

    // previous[state]-the previous state in the en-dfa path to a final node.
    std::map<std::pair<state, unsigned>, state> previous;
    unsigned depth = 1;

    std::set<state> states = {start};
    add_epsilon_neighbours(start, states, previous, start, 0);

    for (letter x: word) {
        // The set for the next iteration of states.
        std::set<state> next;
        //Add epsilon neighbours in this set, and then merge the two.
        std::set<state> epsilon_next;

        // Iterate through all the current states and add their neighbours.
        for (state s: states) {
            for (Edge edge: graph[s]) {
                if (edge.transition == x) {
                    next.insert(edge.next);
                    previous[{edge.next, depth}] = s;
                    add_epsilon_neighbours(edge.next, epsilon_next, previous, s, depth);
                }
            }
        }

        next.insert(epsilon_next.begin(), epsilon_next.end());

        if (next.empty()) { // if there are no potential matches, reject the pattern.
            return {false, {}};
        }
        // The next set of states become the current set of states.
        states.swap(next);
        depth++;
    }

    bool found = false;
    state final_state; //Choose a random final state to rebuild the path.
    // Now we need to check if at least one state is final.
    for (state s: states) {
        if (final[s]) {
            found = true;
            final_state = s;
            break;
        }
    }

    // We did not find any final states, reject the pattern.
    if (!found) {
        return {false, {}};
    }

    std::vector<state> path;
    state now = final_state;
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


#endif //FINITE_AUTOMATA_EN_DFA_H
