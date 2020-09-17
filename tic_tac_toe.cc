#include "tic_tac_toe.h"

namespace game {

TicTacToe::TicTacToe() {
  for (int i = 0; i < sz; i++) {
    std::vector<strategy::Player> row(sz, strategy::NONE);
    board.push_back(row);
  }
}

std::string TicTacToe::Display() const {
  return strategy::Display(board);
}

void TicTacToe::SetStrategy(strategy::Strategy* s) {
  strat = s;
}

bool TicTacToe::UserMove(int i, int j) {
  if (i < 0 || j < 0 || i >= sz || j >= sz) return false;
  if (board[i][j] != strategy::NONE) return false;
  board[i][j] = strategy::USER;
  return true;
}

void TicTacToe::ComputerMove() {
  const auto& move = strat->GetMove(board);
  board[move.row][move.col] = strategy::COMPUTER;
}

bool TicTacToe::IsWinner(strategy::Player p) const {
  return strategy::IsWinner(board, p);
}

}  // namespace game
