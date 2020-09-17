#ifndef SJUVEKAR_HOMEPAGE_CPPCODINGZEN_TIC_TAC_TOE_H
#define SJUVEKAR_HOMEPAGE_CPPCODINGZEN_TIC_TAC_TOE_H

#include "strategy.h"

#include <memory>
#include <string>
#include <vector>

namespace game {

class TicTacToe {

public:
  TicTacToe();
  virtual ~TicTacToe() {}
  TicTacToe(const TicTacToe&) =delete;
  TicTacToe& operator=(const TicTacToe&) =delete;

  std::string Display() const;
  void SetStrategy(strategy::Strategy* s);
  bool UserMove(int i, int j);
  void ComputerMove();
  bool IsWinner(strategy::Player p) const;

private:
  const unsigned sz = 3;
  std::vector<std::vector<strategy::Player> > board;
  strategy::Strategy* strat = nullptr;
};

}  // namespace game

#endif  // SJUVEKAR_HOMEPAGE_CPPCODINGZEN_TIC_TAC_TOE_H
