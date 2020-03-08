#include "query_funcs.h"

// -------------------------------------------
// Drop previous relations and create new ones
// -------------------------------------------
void setupTables(connection * C) {
  string sql =
      "DROP TABLE IF EXISTS PLAYER CASCADE;"
      "CREATE TABLE PLAYER (PLAYER_ID INT NOT NULL, TEAM_ID INT NOT NULL, "
      "UNIFORM_NUM INT NOT NULL, FIRST_NAME VARCHAR(15) NOT NULL, LAST_NAME VARCHAR(15) "
      "NOT NULL, MPG "
      "INT, PPG INT, RPG INT, APG INT, SPG FLOAT, BPG FLOAT, PRIMARY "
      "KEY(PLAYER_ID), FOREIGN KEY(TEAM_ID) REFERENCES TEAM(TEAM_ID) ON DELETE CASCADE);"
      "DROP TABLE IF EXISTS TEAM CASCADE; CREATE TABLE TEAM (TEAM_ID INT NOT NULL, NAME "
      "VARCHAR(20) NOT NULL, STATE_ID INT NOT NULL, COLOR_ID INT NOT NULL, WINS INT NOT "
      "NULL, LOSSES INT NOT NULL, PRIMARY KEY(TEAM_ID), FOREIGN KEY(STATE_ID) REFERENCES "
      "STATE(STATE_ID) ON DELETE CASCADE, FOREIGN KEY(COLOR_ID) REFERENCES "
      "COLOR(COLOR_ID) ON DELETE CASCADE);"
      "DROP TABLE IF EXISTS STATE CASCADE;"
      "CREATE TABLE STATE (STATE_ID INT NOT NULL, NAME VARCHAR(20) NOT NULL, PRIMARY "
      "KEY(STATE_ID));"
      "DROP TABLE IF EXISTS COLOR CASCADE;"
      "CREATE TABLE COLOR (COLOR_ID INT NOT NULL, NAME VARCHAR(20) NOT NULL, PRIMARY KEY "
      "(COLOR_ID));";
  work W(*C);
  W.exec(sql);
  W.commit();
  cout << "Relations created" << endl;
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
  static int player_id = 1;
  string sql = "INSERT INTO PLAYER VALUES (" + to_string(player_id) + ", " +
               to_string(team_id) + ", " + to_string(jersey_num) + ", " + "\'" +
               first_name + "\', \'" + last_name + "\', " + to_string(mpg) + ", " +
               to_string(ppg) + ", " + to_string(rpg) + ", " + to_string(apg) + ", " +
               to_string(spg) + ", " + to_string(bpg) + ");";
  work W(*C);
  W.exec(sql);
  W.commit();
  cout << "Player " << player_id << "(" << first_name << " " << last_name << ") added"
       << endl;
  ++player_id;
}

void add_team(connection * C,
              string name,
              int state_id,
              int color_id,
              int wins,
              int losses) {
  static int team_id = 1;
  string sql = "INSERT INTO TEAM VALUES (" + to_string(team_id) + ", \'" + name + "\', " +
               to_string(state_id) + ", " + to_string(color_id) + ", " + to_string(wins) +
               ", " + to_string(losses) + ");";
  work W(*C);
  W.exec(sql);
  W.commit();
  cout << "Team " << team_id << "(" << name << ") added" << endl;
  ++team_id;
}

void add_state(connection * C, string name) {
  static int state_id = 1;
  string sql =
      "INSERT INTO STATE VALUES (" + to_string(state_id) + ", \'" + name + "\');";
  work W(*C);
  W.exec(sql);
  W.commit();
  cout << "State " << state_id << "(" << name << ") added" << endl;
  ++state_id;
}

void add_color(connection * C, string name) {
  static int color_id = 1;
  string sql =
      "INSERT INTO COLOR VALUES (" + to_string(color_id) + ", \'" + name + "\');";
  work W(*C);
  W.exec(sql);
  W.commit();
  cout << "Color " << color_id << "(" << name << ") added" << endl;
  ++color_id;
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
