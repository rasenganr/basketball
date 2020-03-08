#include "query_funcs.h"

void setupTables(connection * C) {
  string sql_create_player =
      "DROP TABLE IF EXISTS PLAYER;"
      "CREATE TABLE PLAYER (PLAYER_ID INT NOT NULL, TEAM_ID INT NOT NULL, "
      "UNIFORM_NUM INT NOT NULL, FIRST_NAME VARCHAR(15) NOT NULL, LAST_NAME VARCHAR(15) "
      "NOT NULL, MPG "
      "FLOAT, PPG FLOAT, RPG FLOAT, APG FLOAT, SPG FLOAT, BPG FLOAT, PRIMARY "
      "KEY(PLAYER_ID));";
  work W(*C);
  W.exec(sql_create_player);
  W.commit();
  cout << "PLAYER created" << endl;
}

void add_player(connection * C,
                int team_id,
                int jersey_num,
                string first_name,
                string last_name,
                int mpg,
                int ppg,
                int rpg,
                int apg,
                double spg,
                double bpg) {
}

void add_team(connection * C,
              string name,
              int state_id,
              int color_id,
              int wins,
              int losses) {
}

void add_state(connection * C, string name) {
}

void add_color(connection * C, string name) {
}

void query1(connection * C,
            int use_mpg,
            int min_mpg,
            int max_mpg,
            int use_ppg,
            int min_ppg,
            int max_ppg,
            int use_rpg,
            int min_rpg,
            int max_rpg,
            int use_apg,
            int min_apg,
            int max_apg,
            int use_spg,
            double min_spg,
            double max_spg,
            int use_bpg,
            double min_bpg,
            double max_bpg) {
}

void query2(connection * C, string team_color) {
}

void query3(connection * C, string team_name) {
}

void query4(connection * C, string team_state, string team_color) {
}

void query5(connection * C, int num_wins) {
}
