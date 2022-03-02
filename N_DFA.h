//
// Created by visan on 2/21/22.
//

#ifndef FINITE_AUTOMATA_N_DFA_H
#define FINITE_AUTOMATA_N_DFA_H

#include<map>
#include<vector>
#include<set>

// This class implements a non-deterministic finite automaton
class N_DFA {

public:
    typedef int state;
    typedef char letter;

    /* This structure is returned from the valid method of the ndfa.*/
    struct Result {
        bool valid; /* if the word is valid. */
        std::vector<state> path; /* the path in the ndfa graph.*/
    };

    //Adds an edge into the graph.
    void add_edge(state a, state b, letter s);

    //Marks the given state as final.
    void set_final(state x);

    //Checks if the given word is accepted by the N_DFA.
    virtual Result valid(const std::string &word, state start);

protected:
    struct Edge {
        state next;
        letter transition;
    };
    // For each state node, we have a list of edges to other states.
    std::map<state, std::vector<Edge>> graph;

    // This map holds information on whether a state is a final state or not.
    std::map<state, bool> final;

    //In an N_DFA, we can have multiple transitions with the same letter. This method
    //takes a state and a transition and adds all the states we can visit
    //using the given transition from the given state into the given set.
    void add_neighbours(state x, letter transition, std::set<state> &next);
};

void N_DFA::add_neighbours(state x, letter transition, std::set<state> &next) {
    for (Edge edge: graph[x]) {
        if (edge.transition == transition) {
            next.insert(edge.next);
        }
    }
}

void N_DFA::add_edge(state a, state b, letter s) {
    graph[a].push_back({b, s});
}


void N_DFA::set_final(state x) {
    final[x] = true;
}

N_DFA::Result N_DFA::valid(const std::string &word, state start) {
    // The set of current states.
    std::set<state> states = {start};

    // previous[state]-the previous state in the dfa path to a final node.
    std::map<std::pair<state, unsigned>, state> previous;
    unsigned depth = 1;

    for (letter x: word) {

        // The set for the next iteration of states.
        std::set<state> next;

        // Iterate through all the current states.
        for (state s: states) {
            for (Edge edge: graph[s]) {
                if (edge.transition == x) {
                    next.insert(edge.next);
                    previous[{edge.next, depth}] = s;
                }
            }
        }

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

#endif //FINITE_AUTOMATA_N_DFA_H
