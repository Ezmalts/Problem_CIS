const int k_inf = 100000; //big magic number

void make_dp(const std::vector<int>& matrix)
 {
     //get current state
     int state = get_state(matrix);

     //get win state
     std::vector<int> state_win_0 = get_win_0(state);
     std::vector<int> state_win_1 = get_win_1(state);

     //init dp
     const int state_size = get_size_state(matrix); // max number of state
     int dp[state_size][k_inf][2];

     //0 player
     std::queue< std::pair<int, int> > states_0;
     for (auto state_ : state_win_0) {
        for (int k = 0; k < k_inf; ++k)
            dp[state_][k][0] = 1;
        states_0.push(std::make_pair(state_, 0));
     }

     //1 player
     std::queue< std::pair<int, int> > states_1;
     for (auto state_ : state_win_1) {
        for (int k = 0; k < k_inf; ++k)
            dp[state_][k][1] = 1;
        states_1.push(std::make_pair(state_, 0));
     }

     //count dp
     std::vector <bool> used(state_size, false);
     while(!states_0.empty()) {
        std::pair<int, int> cur_state = states_0.front();
        states_0.pop();
        used[cur_state.first] = true;

        std::vector<int> states = get_next_states(cur_state.first);

        for (auto state : states) {
            for (int k = cur_state.second + 1; k < k_inf; ++k)
            dp[state][k][0] = 1;
            if (used[state] == false) {
                states_0.push(state);
            }
        }
     }

     used.resize(state_size, false);
     while(!states_1.empty()) {
        std::pair<int, int> cur_state = states_1.front();
        states_1.pop();
        used[cur_state.first] = true;

        std::vector<int> states = get_next_states(cur_state.first);

        for (auto state : states) {
            for (int k = cur_state.second + 1; k < k_inf; ++k)
            dp[state][k][1] = 1;
            if (used[state] == false) {
                states_1.push(state);
            }
        }
     }
 }
