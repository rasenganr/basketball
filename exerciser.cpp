#include "exerciser.h"

void exercise(connection * C) {
  TupleReader tr;
  vector<Player> players = tr.readPlayers("player.txt");
  vector<Team> teams = tr.readTeams("team.txt");
  vector<State> states = tr.readStates("state.txt");
  vector<Color> colors = tr.readColors("color.txt");

  // Add state tuples
  for (size_t i = 0; i < states.size(); ++i) {
    add_state(C, states[i].name);
  }

  // Add color tuples
  for (size_t i = 0; i < colors.size(); ++i) {
    add_color(C, colors[i].name);
  }

  // Add team tuples
  for (size_t i = 0; i < teams.size(); ++i) {
    add_team(C,
             teams[i].name,
             teams[i].state_id,
             teams[i].color_id,
             teams[i].wins,
             teams[i].losses);
  }

  // Add player tuples
  for (size_t i = 0; i < players.size(); ++i) {
    add_player(C,
               players[i].team_id,
               players[i].uniform_num,
               players[i].first_name,
               players[i].last_name,
               players[i].mpg,
               players[i].ppg,
               players[i].rpg,
               players[i].apg,
               players[i].spg,
               players[i].bpg);
  }

  // Test query 1
  cout << "------------------------------------------------------------------" << endl;
  cout << "----------------------------- Query 1 ----------------------------" << endl;
  cout << "------------------------------------------------------------------" << endl;
  query1(C,
         /*MPG*/ 1,
         10,
         20,
         /*PPG*/ 1,
         0,
         10,
         /*RPG*/ 1,
         0,
         3,
         /*APG*/ 1,
         1,
         3,
         /*SPG*/ 1,
         0.2,
         1.2,
         /*BPG*/ 1,
         0.1,
         1);
  cout << endl << endl;
  query1(C,
         /*MPG*/ 1,
         20,
         30,
         /*PPG*/ 0,
         0,
         10,
         /*RPG*/ 0,
         0,
         3,
         /*APG*/ 1,
         1,
         3,
         /*SPG*/ 1,
         0,
         0.6,
         /*BPG*/ 0,
         0.1,
         1);
  cout << endl << endl;
  query1(C,
         /*MPG*/ 0,
         10,
         20,
         /*PPG*/ 1,
         0,
         5,
         /*RPG*/ 1,
         3,
         10,
         /*APG*/ 1,
         2,
         5,
         /*SPG*/ 0,
         0.2,
         1.2,
         /*BPG*/ 1,
         0.1,
         1);
  cout << endl << endl;

  // Test query 2
  cout << "------------------------------------------------------------------" << endl;
  cout << "----------------------------- Query 2 ----------------------------" << endl;
  cout << "------------------------------------------------------------------" << endl;
  query2(C, "LightBlue");
  cout << endl << endl;
  query2(C, "Orange");
  cout << endl << endl;
  query2(C, "Green");
  cout << endl << endl;
  query2(C, "Red");
  cout << endl << endl;
  query2(C, "DarkBlue");
  cout << endl << endl;
  query2(C, "Gold");
  cout << endl << endl;
  query2(C, "Maroon");
  cout << endl << endl;
  query2(C, "Black");
  cout << endl << endl;

  // Test query 3
  cout << "------------------------------------------------------------------" << endl;
  cout << "----------------------------- Query 3 ----------------------------" << endl;
  cout << "------------------------------------------------------------------" << endl;
  query3(C, "BostonCollege");
  cout << endl << endl;
  query3(C, "Clemson");
  cout << endl << endl;
  query3(C, "Duke");
  cout << endl << endl;
  query3(C, "FloridaState");
  cout << endl << endl;
  query3(C, "GeorgiaTech");
  cout << endl << endl;
  query3(C, "Louisville");
  cout << endl << endl;
  query3(C, "Miami");
  cout << endl << endl;
  query3(C, "NCSU");
  cout << endl << endl;
  query3(C, "NotreDame");
  cout << endl << endl;
  query3(C, "Pittsburgh");
  cout << endl << endl;
  query3(C, "Syracuse");
  cout << endl << endl;
  query3(C, "UNC");
  cout << endl << endl;
  query3(C, "Virginia");
  cout << endl << endl;
  query3(C, "VirginiaTech");
  cout << endl << endl;
  query3(C, "WakeForest");
  cout << endl << endl;

  // Test query 4
  cout << "------------------------------------------------------------------" << endl;
  cout << "----------------------------- Query 4 ----------------------------" << endl;
  cout << "------------------------------------------------------------------" << endl;
  query4(C, "MA", "Maroon");
  cout << endl << endl;
  query4(C, "SC", "Orange");
  cout << endl << endl;
  query4(C, "NC", "DarkBlue");
  cout << endl << endl;
  query4(C, "FL", "Maroon");
  cout << endl << endl;
  query4(C, "GA", "Gold");
  cout << endl << endl;
  query4(C, "KY", "Red");
  cout << endl << endl;
  query4(C, "FL", "Green");
  cout << endl << endl;
  query4(C, "NC", "Red");
  cout << endl << endl;
  query4(C, "IN", "Gold");
  cout << endl << endl;
  query4(C, "PA", "Black");
  cout << endl << endl;

  // Test query 5
  cout << "------------------------------------------------------------------" << endl;
  cout << "----------------------------- Query 5 ----------------------------" << endl;
  cout << "------------------------------------------------------------------" << endl;
  query5(C, 10);
  cout << endl << endl;
  query5(C, 11);
  cout << endl << endl;
  query5(C, 12);
  cout << endl << endl;
}
