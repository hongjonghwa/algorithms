/*
  참조 : https://github.com/jmm140330/Rubik
*/

#ifndef CUBE_H
#define CUBE_H

#include <iostream>

bool cube_is_correct (int cubies[9][6]);
void cube_init (int cubies[9][6]);
void cube_output(int cubies[9][6]);
void cube_R(int n, int cubies[9][6]);
void cube_L(int n, int cubies[9][6]);
void cube_U(int n, int cubies[9][6]);
void cube_D(int n, int cubies[9][6]);
void cube_F(int n, int cubies[9][6]);
void cube_B(int n, int cubies[9][6]);
/*
class Cube {

  public: int cubies[9][6];

  public: Cube(bool);

  public: void init();

  private: void scramble();

  public:
  std::string printSequence(std::string);
  void moves(std::string);
  void output();
  void R(int);
  void L(int);
  void U(int);
  void D(int);
  void F(int);
  void B(int);
};
*/
#endif
