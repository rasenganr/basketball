#include "query_funcs.h"

#include <fstream>
#include <iomanip>

// -------------------------------------------
// Drop previous database and create a new one
// -------------------------------------------
void setupDatabase() {
  string sql = "DROP DATABASE IF EXISTS \"ACC_BBALL\"; CREATE DATABASE \"ACC_BBALL\";";
}

// -------------------------------------------
// Drop previous relations and create new ones
// -------------------------------------------
void setupTables(connection * C) {
  string sql = "DROP TABLE IF EXISTS PLAYER CASCADE;"
               "CREATE TABLE PLAYER (PLAYER_ID INT NOT NULL, TEAM_ID INT NOT NULL, "
               "UNIFORM_NUM INT NOT NULL, FIRST_NAME VARCHAR(30) NOT NULL, LAST_NAME "
               "VARCHAR(30) "
               "NOT NULL, MPG "
               "INT, PPG INT, RPG INT, APG INT, SPG FLOAT, BPG FLOAT, PRIMARY "
               "KEY(PLAYER_ID), FOREIGN KEY(TEAM_ID) REFERENCES TEAM(TEAM_ID) ON "
               "DELETE CASCADE);"
               "DROP TABLE IF EXISTS TEAM CASCADE; CREATE TABLE TEAM (TEAM_ID INT NOT "
               "NULL, NAME "
               "VARCHAR(30) NOT NULL, STATE_ID INT NOT NULL, COLOR_ID INT NOT NULL, "
               "WINS INT NOT "
               "NULL, LOSSES INT NOT NULL, PRIMARY KEY(TEAM_ID), FOREIGN "
               "KEY(STATE_ID) REFERENCES "
               "STATE(STATE_ID) ON DELETE CASCADE, FOREIGN KEY(COLOR_ID) REFERENCES "
               "COLOR(COLOR_ID) ON DELETE CASCADE);"
               "DROP TABLE IF EXISTS STATE CASCADE;"
               "CREATE TABLE STATE (STATE_ID INT NOT NULL, NAME VARCHAR(30) NOT NULL, "
               "PRIMARY "
               "KEY(STATE_ID));"
               "DROP TABLE IF EXISTS COLOR CASCADE;"
               "CREATE TABLE COLOR (COLOR_ID INT NOT NULL, NAME VARCHAR(30) NOT NULL, "
               "PRIMARY KEY "
               "(COLOR_ID));";
  work W(*C);
  W.exec(sql);
  W.commit();
}

// ---------------------
// Add a tuple to PLAYER
// ---------------------
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
               to_string(team_id) + ", " + to_string(jersey_num) + ", \'" + first_name +
               "\', \'" + last_name + "\', " + to_string(mpg) + ", " + to_string(ppg) +
               ", " + to_string(rpg) + ", " + to_string(apg) + ", " + to_string(spg) +
               ", " + to_string(bpg) + ");";
  work W(*C);
  W.exec(sql);
  W.commit();
  ++player_id;
}

// -------------------
// Add a tuple to TEAM
// -------------------
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
  ++team_id;
}

// --------------------
// Add a tuple to STATE
// --------------------
void add_state(connection * C, string name) {
  static int state_id = 1;
  string sql =
      "INSERT INTO STATE VALUES (" + to_string(state_id) + ", \'" + name + "\');";
  work W(*C);
  W.exec(sql);
  W.commit();
  ++state_id;
}

// --------------------
// Add a tuple to COLOR
// --------------------
void add_color(connection * C, string name) {
  static int color_id = 1;
  string sql =
      "INSERT INTO COLOR VALUES (" + to_string(color_id) + ", \'" + name + "\');";
  work W(*C);
  W.exec(sql);
  W.commit();
  ++color_id;
}

// --------------------------------------
// Generate "BETWEEN" sentence for query1
// --------------------------------------
template<typename T>
string getBetween(int use, T min, T max, string str) {
  string res;
  if (use) {
    res = " (" + str + " BETWEEN " + to_string(min) + " AND " + to_string(max) + ") AND ";
  }
  return res;
}

// -----------------------------
// Execute SQL and print results
// -----------------------------
void print(connection * C, string sql) {
  work W(*C);
  result res = W.exec(sql);
  for (pqxx::result::iterator i = res.begin(); i != res.end(); ++i) {
    int ind = 0;
    for (pqxx::tuple::iterator j = i->begin(); j < i->end(); ++j) {
      if (ind < 10) {
        cout << j << " ";
      }
      else {
        cout << fixed << setprecision(1) << j->as<double>() << " ";
      }
      ++ind;
    }
    cout << endl;
  }
}

// ----------------------------------------------------------------------------
// Query 1: Show all attributes of each player with average statistics that
//          fall between the min and max (inclusive) for each enabled statistic
// ----------------------------------------------------------------------------
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
  string sql = "SELECT * FROM PLAYER WHERE";
  sql += getBetween<int>(use_mpg, min_mpg, max_mpg, "MPG");
  sql += getBetween<int>(use_ppg, min_ppg, max_ppg, "PPG");
  sql += getBetween<int>(use_rpg, min_rpg, max_rpg, "RPG");
  sql += getBetween<int>(use_apg, min_apg, max_apg, "APG");
  sql += getBetween<double>(use_spg, min_spg, max_spg, "SPG");
  sql += getBetween<double>(use_bpg, min_bpg, max_bpg, "BPG");
  if (use_mpg || use_ppg || use_rpg || use_apg || use_spg || use_bpg) {
    sql.erase(sql.length() - 5, 5);
  }
  sql += ";";

  cout << "PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG"
       << endl;
  print(C, sql);
}

// ---------------------------------------------------------------------
// Query 2: Show the name of each team with the indicated uniform color.
// ---------------------------------------------------------------------
void query2(connection * C, string team_color) {
  string sql = "SELECT TEAM.NAME FROM TEAM, COLOR WHERE "
               "TEAM.COLOR_ID = COLOR.COLOR_ID "
               "AND COLOR.NAME = \'" +
               team_color + "\';";

  cout << "TEAM.NAME" << endl;
  print(C, sql);
}

// --------------------------------------------------------------------
// Query 3: Show the first and last name of each player that plays for
//          the indicated team, ordered from highest to lowest ppg.
// --------------------------------------------------------------------
void query3(connection * C, string team_name) {
  string sql = "SELECT FIRST_NAME, LAST_NAME FROM PLAYER, TEAM WHERE "
               "PLAYER.TEAM_ID = "
               "TEAM.TEAM_ID AND TEAM.NAME = \'" +
               team_name + "\' ORDER BY PLAYER.PPG DESC;";

  cout << "FIRST_NAME LAST_NAME" << endl;
  print(C, sql);
}

// --------------------------------------------------------------------
// Query 4: Show first name, last name and jersey number of each player
//          that playes in the indicated state and wears the indicated
//          uniform color.
// --------------------------------------------------------------------
void query4(connection * C, string team_state, string team_color) {
  string sql = "SELECT FIRST_NAME, LAST_NAME, UNIFORM_NUM FROM PLAYER, "
               "TEAM, STATE, "
               "COLOR WHERE PLAYER.TEAM_ID = TEAM.TEAM_ID AND "
               "TEAM.STATE_ID = "
               "STATE.STATE_ID AND TEAM.COLOR_ID = "
               "COLOR.COLOR_ID AND STATE.NAME = \'" +
               team_state + "\' AND COLOR.NAME = \'" + team_color + "\';";

  cout << "FIRST_NAME LAST_NAME UNIFORM_NUM" << endl;
  print(C, sql);
}

// --------------------------------------------------------------------
// Query 5: Show first name and last name of each player, and team name
//          and number of wins for each team that has won more than the
//          indicated number of games.
// --------------------------------------------------------------------
void query5(connection * C, int num_wins) {
  string sql = "SELECT FIRST_NAME, LAST_NAME, TEAM.NAME, WINS FROM "
               "PLAYER, TEAM WHERE "
               "PLAYER.TEAM_ID = TEAM.TEAM_ID AND WINS > " +
               to_string(num_wins) + ";";

  cout << "FIRST_NAME LAST_NAME TEAM.NAME WINS" << endl;
  print(C, sql);
}

// -------------------------------------------------------------------
// Add single quotations to cover original single quotations in string
// -------------------------------------------------------------------
void addQuotation(vector<string> & vec) {
  for (size_t i = 0; i < vec.size(); ++i) {
    size_t ind = 0;
    while ((ind = vec[i].find("\'", ind + 2)) != string::npos) {
      vec[i].insert(ind, "\'");
    }
  }
}

// -------------------------
// Split a line into strings
// -------------------------
vector<string> split(string str) {
  int len = str.length();
  int start = 0, end = 0;
  vector<string> vec;

  while (end < len) {
    while (end < len && str[end] != ' ') {
      ++end;
    }
    vec.push_back(str.substr(start, end - start));
    start = ++end;
  }

  addQuotation(vec);

  return vec;
}

// ------------------------
// Split info of one player
// ------------------------
Player splitPlayer(string str) {
  vector<string> vec = split(str);
  Player res;

  res.player_id = atoi(vec[0].c_str());
  res.team_id = atoi(vec[1].c_str());
  res.uniform_num = atoi(vec[2].c_str());
  res.first_name = vec[3];
  res.last_name = vec[4];
  res.mpg = atoi(vec[5].c_str());
  res.ppg = atoi(vec[6].c_str());
  res.rpg = atoi(vec[7].c_str());
  res.apg = atoi(vec[8].c_str());
  res.spg = atof(vec[9].c_str());
  res.bpg = atof(vec[10].c_str());

  return res;
}

// ----------------------
// Split info of one team
// ----------------------
Team splitTeam(string str) {
  vector<string> vec = split(str);
  Team res;

  res.team_id = atoi(vec[0].c_str());
  res.name = vec[1];
  res.state_id = atoi(vec[2].c_str());
  res.color_id = atoi(vec[3].c_str());
  res.wins = atoi(vec[4].c_str());
  res.losses = atoi(vec[5].c_str());

  return res;
}

// -----------------------
// Split info of one state
// -----------------------
State splitState(string str) {
  vector<string> vec = split(str);
  State res;

  res.state_id = atoi(vec[0].c_str());
  res.name = vec[1];

  return res;
}

// -----------------------
// Split info of one color
// -----------------------
Color splitColor(string str) {
  vector<string> vec = split(str);
  Color res;

  res.color_id = atoi(vec[0].c_str());
  res.name = vec[1];

  return res;
}

/*--------------------------------------------------*/
/*---------- Methods of class TupleReader ----------*/
/*--------------------------------------------------*/
// Read player info from a file
vector<Player> TupleReader::readPlayers(string path) {
  ifstream f;
  f.open(path, ifstream::in);
  string curr;
  vector<Player> res;
  while (getline(f, curr)) {
    Player p = splitPlayer(curr);
    res.push_back(p);
  }
  return res;
}

// Read team info from a file
vector<Team> TupleReader::readTeams(string path) {
  ifstream f;
  f.open(path, ifstream::in);
  string curr;
  vector<Team> res;
  while (getline(f, curr)) {
    Team p = splitTeam(curr);
    res.push_back(p);
  }
  return res;
}

// Read state info from a file
vector<State> TupleReader::readStates(string path) {
  ifstream f;
  f.open(path, ifstream::in);
  string curr;
  vector<State> res;
  while (getline(f, curr)) {
    State p = splitState(curr);
    res.push_back(p);
  }
  return res;
}

// Read color info from a file
vector<Color> TupleReader::readColors(string path) {
  ifstream f;
  f.open(path, ifstream::in);
  string curr;
  vector<Color> res;
  while (getline(f, curr)) {
    Color p = splitColor(curr);
    res.push_back(p);
  }
  return res;
}
