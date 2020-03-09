#include "exerciser.h"

void exercise(connection * C) {
  TupleReader tr;
  vector<Player> players = tr.readPlayers("player.txt");
  vector<Team> teams = tr.readTeams("team.txt");
  vector<State> states = tr.readStates("state.txt");
  vector<Color> colors = tr.readColors("color.txt");

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

  for (size_t i = 0; i < teams.size(); ++i) {
    add_team(C,
             teams[i].name,
             teams[i].state_id,
             teams[i].color_id,
             teams[i].wins,
             teams[i].losses);
  }

  for (size_t i = 0; i < states.size(); ++i) {
    add_state(C, states[i].name);
  }

  for (size_t i = 0; i < colors.size(); ++i) {
    add_color(C, colors[i].name);
  }

  query1(C, 0, 0, 0, 1, 0, 3, 1, 0, 3, 0, 0, 0, 1, 0.5, 1.5, 0, 0, 0);
}
