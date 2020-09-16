#include "strategy.h"

#include <limits>

namespace strategy {

std::string Display(const std::vector<std::vector<Player> >& board) {
  std::string ret = "";
  int sz = board.size();
  for (int i = 0; i < sz; i++) {
    for (int j = 0; j < sz; j++) {
      if (board[i][j] == NONE) ret += "-";
      else if (board[i][j] == USER) ret += "X";
      else ret += "O";
    }
    ret += "\n";
  }
  return ret;
}

bool IsWinner(const std::vector<std::vector<Player> >& board, Player p) {
  int sz = board.size();
  std::vector<int> r_count, c_count;
  r_count.assign(sz, 0);
  c_count.assign(sz, 0);
  int left_diag = 0, right_diag = 0;
  for (int r = 0; r < sz; r++) {
    for (int c = 0; c < sz; c++) {
      if (board[r][c] == p) {
        r_count[r]++;
        if (r_count[r] == sz) return true;
        c_count[c]++;
        if (c_count[c] == sz) return true;
        if (r == c) {
          left_diag++;
          if (left_diag == sz) return true;
        }
        if (r+c == sz-1) {
          right_diag++;
          if (right_diag == sz) return true;
        }
      }
    }
  }
  return false;
}

const Move SimpleStrategy::GetMove(const std::vector<std::vector<Player> >& board) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      if (board[i][j] == NONE) return {i, j};
    }
  }
  return {0, 0};
}

const Move DecisionTreeStrategy::GetMove(const std::vector<std::vector<Player> >& board) {
  auto new_board = board;
  int best_score = std::numeric_limits<int>::min();
  int best_row = 0, best_col = 0;
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      if (board[i][j] == NONE) {
        int score = ComputeScore(i, j, COMPUTER, &new_board);
        if (score > best_score) {
          best_score = score;
          best_row = i;
          best_col = j;
        }
      }
    }
  }
  return {best_row, best_col};
}

int DecisionTreeStrategy::ComputeScore(int r, int c, Player curr,
  std::vector<std::vector<Player> >* board) {
    (*board)[r][c] = curr;
    const std::string key = Display(*board);
    if (scores.find(key) != scores.end()) {
      (*board)[r][c] = NONE;
      return scores[key];
    }
    if (IsWinner(*board, COMPUTER)) {
      (*board)[r][c] = NONE;
      scores[key] = 1;
      return 1;
    }
    if (IsWinner(*board, USER)) {
      (*board)[r][c] = NONE;
      scores[key] = -2;
      return -2;
    }
    Player next = (curr == COMPUTER)? USER : COMPUTER;
    int score = 0;
    for (int i = 0; i < (*board).size(); i++) {
      for (int j = 0; j < (*board)[i].size(); j++) {
        if ((*board)[i][j] == NONE) {
          score += ComputeScore(i, j, next, board);
        }
      }
    }
    scores[key] = score;
    (*board)[r][c] = NONE;
    return score;
}

}  // namespace strategy
