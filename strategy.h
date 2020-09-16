#ifndef SJUVEKAR_HOMEPAGE_CPPCODINGZEN_STRATEGY_H
#define SJUVEKAR_HOMEPAGE_CPPCODINGZEN_STRATEGY_H

#include <unordered_map>
#include <string>
#include <vector>

namespace strategy {

enum Player {
  NONE = 0,
  USER = 1,
  COMPUTER = 2,
};

std::string Display(const std::vector<std::vector<Player> >& board);
bool IsWinner(const std::vector<std::vector<Player> >& board, Player p);

struct Move {
  const int row=0;
  const int col=0;

  Move(int r, int c) : row(r), col(c) {}
};

class Strategy {
public:
  virtual ~Strategy() {};
  virtual const Move GetMove(const std::vector<std::vector<Player> >& board) = 0;
};

class SimpleStrategy : public Strategy {
public:
  SimpleStrategy() = default;
  virtual ~SimpleStrategy() {}
  const Move GetMove(const std::vector<std::vector<Player> >& board) override;
};

class DecisionTreeStrategy : public Strategy {
public:
  DecisionTreeStrategy() = default;
  virtual ~DecisionTreeStrategy() {}
  const Move GetMove(const std::vector<std::vector<Player> >& board) override;

private:
  int ComputeScore(int r, int c, Player curr,
    std::vector<std::vector<Player> >* board);
  std::unordered_map<std::string, int> scores;
};

}  // namespace strategy

#endif  // SJUVEKAR_HOMEPAGE_CPPCODINGZEN_STRATEGY_H
