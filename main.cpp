#include <iostream>
#include<fstream>
#include"DFA.h"
#include"L_NFA.h"


void solve_dfa() {
    DFA dfa;
    std::ifstream in("input.txt");
    int n, m;
    in >> n; //read number of states
    for (int i = 0; i < n; i++) {
        in >> m; //skip the states, we don't need them
    }
    in >> m; //number of transitions
    for (int i = 0; i < m; i++) {
        int x, y;
        char l;
        in >> x >> y >> l;
        dfa.add_edge(x, y, l);
    }
    int s, nrf, state;
    in >> s >> nrf; //read start and number of final nodes
    for (int i = 0; i < nrf; i++) {
        in >> state;
        dfa.set_final(state);
    }
    int nrc;
    std::string w;
    in >> nrc; //number of words to check
    for (int i = 0; i < nrc; i++) {
        in >> w;
        std::vector<int> path;
        DFA::Result result = dfa.valid(w, s);
        if (result.valid) {
            std::cout << "YES:";
            for (DFA::state x: result.path) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "NO" << std::endl;
        }
    }
}

//Same as dfa
void solve_nfa() {
    N_DFA nfa;
    std::ifstream in("input.txt");
    int n, m;
    in >> n; //read number of states
    for (int i = 0; i < n; i++) {
        in >> m; //skip the states, we don't need them
    }
    in >> m; //number of transitions
    for (int i = 0; i < m; i++) {
        int x, y;
        char l;
        in >> x >> y >> l;
        nfa.add_edge(x, y, l);
    }
    int s, nrf, state;
    in >> s >> nrf; //read start and number of final nodes
    for (int i = 0; i < nrf; i++) {
        in >> state;
        nfa.set_final(state);
    }
    int nrc;
    std::string w;
    in >> nrc; //number of words to check
    for (int i = 0; i < nrc; i++) {
        in >> w;
        std::vector<int> path;
        N_DFA::Result result = nfa.valid(w, s);
        if (result.valid) {
            std::cout << "YES:";
            for (N_DFA::state x: result.path) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "NO" << std::endl;
        }
    }
}

void solve_lnfa() {
    EN_DFA lnfa;
    std::ifstream in("input.txt");
    int n, m;
    in >> n; //read number of states
    for (int i = 0; i < n; i++) {
        in >> m; //skip the states, we don't need them
    }
    in >> m; //number of normal transitions
    for (int i = 0; i < m; i++) {
        int x, y;
        char l;
        in >> x >> y >> l;
        lnfa.add_edge(x, y, l);
    }
    in >> m;//number of epsilon transitions
    for (int i = 0; i < m; i++) {
        int x, y;
        in >> x >> y;
        lnfa.add_epsilon_edge(x, y);
    }

    int s, nrf, state;
    in >> s >> nrf; //read start and number of final nodes
    for (int i = 0; i < nrf; i++) {
        in >> state;
        lnfa.set_final(state);
    }
    int nrc;
    std::string w;
    in >> nrc; //number of words to check
    for (int i = 0; i < nrc; i++) {
        in >> w;
        std::vector<int> path;
        N_DFA::Result result = lnfa.valid(w, s);
        if (result.valid) {
            std::cout << "YES:";
            for (N_DFA::state x: result.path) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "NO" << std::endl;
        }
    }
}

int main() {
    return 0;
}
