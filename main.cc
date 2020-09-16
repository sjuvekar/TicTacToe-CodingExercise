#include "strategy.h"
#include "tic_tac_toe.h"

#include <iostream>

int main (int argc, char *argv[]) {
  TicTacToe t;
  strategy::DecisionTreeStrategy strat;
  t.SetStrategy(&strat);
  std::cout << t.Display();
  while (true) {
    std::cout << "Enter row and column number ->\n";
    int i, j;
    std::cin >> i >> j;
    if (!t.UserMove(i, j)) {
      std::cout << "That move is not valid. ";
    } else {
      if (t.IsWinner(strategy::USER)) {
        std::cout << t.Display();
        std::cout << "Congratulations! You won!\n";
        break;
      }
      t.ComputerMove();
      std::cout << t.Display();
      if (t.IsWinner(strategy::COMPUTER)) {
        std::cout << "Sorry! You lost!\n";
        break;
      }
    }
  }
}
