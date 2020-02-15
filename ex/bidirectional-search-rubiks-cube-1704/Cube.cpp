/*
  참조 : https://github.com/jmm140330/Rubik
*/

#include "Cube.hpp"
#include <iostream>

bool cube_is_correct (int cubies[9][6]) {
 for (int sticker=0; sticker<9; ++sticker) {
   for (int side=0; side<6; ++side) {
     if (cubies[sticker][side] != side) return false;
   }
 }
 return true;
}

void cube_init (int cubies[9][6]) {
  for (int sticker=0; sticker<9; ++sticker) {
    for (int side=0; side<6; ++side) {
      if (side==0) {
        cubies[sticker][side] = 0; //White
      }
      else if(side==1) {
        cubies[sticker][side] = 1; //Yellow
      }
      else if(side==2) {
        cubies[sticker][side] = 2; //Red
      }
      else if(side==3) {
        cubies[sticker][side] = 3; //Green
      }
      else if(side==4) {
        cubies[sticker][side] = 4; //Orange
      }
      else if(side==5) {
        cubies[sticker][side] = 5; //Blue
      }
    }
  }
}


void cube_output(int cubies[9][6]) {
  std::cout << "White:" << std::endl;
  for (int i=0; i<9; i+=0) {
    for (int j=0; j<3; ++j) {
      std::cout << cubies[i][0];
      ++i;
    }
    std::cout << std::endl;
  }
  std::cout << "Yellow:" << std::endl;
  for (int i=0; i<9; i+=0) {
    for (int j=0; j<3; ++j) {
      std::cout << cubies[i][1];
      ++i;
    }
    std::cout << std::endl;
  }
  std::cout << "Red:" << std::endl;
  for (int i=0; i<9; i+=0) {
    for (int j=0; j<3; ++j) {
      std::cout << cubies[i][2];
      ++i;
    }
    std::cout << std::endl;
  }
  std::cout << "Green:" << std::endl;
  for (int i=0; i<9; i+=0) {
    for (int j=0; j<3; ++j) {
      std::cout << cubies[i][3];
      ++i;
    }
    std::cout << std::endl;
  }
  std::cout << "Orange:" << std::endl;
  for (int i=0; i<9; i+=0) {
    for (int j=0; j<3; ++j) {
      std::cout << cubies[i][4];
      ++i;
    }
    std::cout << std::endl;
  }
  std::cout << "Blue:" << std::endl;
  for (int i=0; i<9; i+=0) {
    for (int j=0; j<3; ++j) {
      std::cout << cubies[i][5];
      ++i;
    }
    std::cout << std::endl;
  }

}


void cube_R(int n, int cubies[9][6]) {

  int newCubies[9][6];
  for (int i=0;i<9;++i) {
    for (int j=0;j<6;++j) {
      newCubies[i][j] = cubies[i][j];
    }
  }

  if (n>=0) {
    for (int x=0; x<n; ++x) {

      //Orange->White
      newCubies[2][0] = cubies[6][4];
      newCubies[5][0] = cubies[3][4];
      newCubies[8][0] = cubies[0][4];

      //White->Red
      newCubies[2][2] = cubies[2][0];
      newCubies[5][2] = cubies[5][0];
      newCubies[8][2] = cubies[8][0];

      //Red->Yellow
      newCubies[2][1] = cubies[2][2];
      newCubies[5][1] = cubies[5][2];
      newCubies[8][1] = cubies[8][2];

      //Yellow->Orange
      newCubies[6][4] = cubies[2][1];
      newCubies[3][4] = cubies[5][1];
      newCubies[0][4] = cubies[8][1];

      //Rotate Green
      newCubies[0][3] = cubies[6][3];
      newCubies[1][3] = cubies[3][3];
      newCubies[2][3] = cubies[0][3];
      newCubies[3][3] = cubies[7][3];
      newCubies[5][3] = cubies[1][3];
      newCubies[6][3] = cubies[8][3];
      newCubies[7][3] = cubies[5][3];
      newCubies[8][3] = cubies[2][3];

      for (int i=0;i<9;++i) {
        for (int j=0;j<6;++j) {
          cubies[i][j] = newCubies[i][j];
        }
      }

    }
  }



}

void cube_L(int n, int cubies[9][6]) {

  int newCubies[9][6];
  for (int i=0;i<9;++i) {
    for (int j=0;j<6;++j) {
      newCubies[i][j] = cubies[i][j];
    }
  }

  if (n>=0) {

    for (int x=0; x<n; ++x) {

      //White->Orange
      newCubies[2][4] = cubies[6][0];
      newCubies[5][4] = cubies[3][0];
      newCubies[8][4] = cubies[0][0];

      //Orange->Yellow
      newCubies[6][1] = cubies[2][4];
      newCubies[3][1] = cubies[5][4];
      newCubies[0][1] = cubies[8][4];

      //Yellow->Red
      newCubies[0][2] = cubies[0][1];
      newCubies[3][2] = cubies[3][1];
      newCubies[6][2] = cubies[6][1];

      //Red->White
      newCubies[0][0] = cubies[0][2];
      newCubies[3][0] = cubies[3][2];
      newCubies[6][0] = cubies[6][2];

      //Rotate Blue
      newCubies[0][5] = cubies[6][5];
      newCubies[1][5] = cubies[3][5];
      newCubies[2][5] = cubies[0][5];
      newCubies[3][5] = cubies[7][5];
      newCubies[5][5] = cubies[1][5];
      newCubies[6][5] = cubies[8][5];
      newCubies[7][5] = cubies[5][5];
      newCubies[8][5] = cubies[2][5];

      for (int i=0;i<9;++i) {
        for (int j=0;j<6;++j) {
          cubies[i][j] = newCubies[i][j];
        }
      }

    }
  }


}

void cube_U(int n, int cubies[9][6]) {

  int newCubies[9][6];
  for (int i=0;i<9;++i) {
    for (int j=0;j<6;++j) {
      newCubies[i][j] = cubies[i][j];
    }
  }

  if (n>=0) {

    for (int x=0; x<n; ++x) {

      //Orange->Green
      newCubies[0][3] = cubies[0][4];
      newCubies[1][3] = cubies[1][4];
      newCubies[2][3] = cubies[2][4];

      //Green->Red
      newCubies[0][2] = cubies[0][3];
      newCubies[1][2] = cubies[1][3];
      newCubies[2][2] = cubies[2][3];

      //Red->Blue
      newCubies[0][5] = cubies[0][2];
      newCubies[1][5] = cubies[1][2];
      newCubies[2][5] = cubies[2][2];

      //Blue->Orange
      newCubies[0][4] = cubies[0][5];
      newCubies[1][4] = cubies[1][5];
      newCubies[2][4] = cubies[2][5];

      //Rotate Yellow
      newCubies[0][1] = cubies[6][1];
      newCubies[1][1] = cubies[3][1];
      newCubies[2][1] = cubies[0][1];
      newCubies[3][1] = cubies[7][1];
      newCubies[5][1] = cubies[1][1];
      newCubies[6][1] = cubies[8][1];
      newCubies[7][1] = cubies[5][1];
      newCubies[8][1] = cubies[2][1];

      for (int i=0;i<9;++i) {
        for (int j=0;j<6;++j) {
          cubies[i][j] = newCubies[i][j];
        }
      }

    }
  }

}

void cube_D(int n, int cubies[9][6]) {

  int newCubies[9][6];
  for (int i=0;i<9;++i) {
    for (int j=0;j<6;++j) {
      newCubies[i][j] = cubies[i][j];
    }
  }

  if (n>=0) {

    for (int x=0; x<n; ++x) {

      //Orange->Blue
      newCubies[6][5] = cubies[6][4];
      newCubies[7][5] = cubies[7][4];
      newCubies[8][5] = cubies[8][4];

      //Blue->Red
      newCubies[6][2] = cubies[6][5];
      newCubies[7][2] = cubies[7][5];
      newCubies[8][2] = cubies[8][5];

      //Red->Green
      newCubies[6][3] = cubies[6][2];
      newCubies[7][3] = cubies[7][2];
      newCubies[8][3] = cubies[8][2];

      //Green->Orange
      newCubies[6][4] = cubies[6][3];
      newCubies[7][4] = cubies[7][3];
      newCubies[8][4] = cubies[8][3];

      //Rotate White
      newCubies[0][0] = cubies[6][0];
      newCubies[1][0] = cubies[3][0];
      newCubies[2][0] = cubies[0][0];
      newCubies[3][0] = cubies[7][0];
      newCubies[5][0] = cubies[1][0];
      newCubies[6][0] = cubies[8][0];
      newCubies[7][0] = cubies[5][0];
      newCubies[8][0] = cubies[2][0];

      for (int i=0;i<9;++i) {
        for (int j=0;j<6;++j) {
          cubies[i][j] = newCubies[i][j];
        }
      }

    }
  }


}

void cube_F(int n, int cubies[9][6]) {

  int newCubies[9][6];
  for (int i=0;i<9;++i) {
    for (int j=0;j<6;++j) {
      newCubies[i][j] = cubies[i][j];
    }
  }

  if (n>=0) {

    for (int x=0; x<n; ++x) {

      //Blue->Yellow
      newCubies[8][1] = cubies[2][5];
      newCubies[7][1] = cubies[5][5];
      newCubies[6][1] = cubies[8][5];

      //Yellow->Green
      newCubies[0][3] = cubies[6][1];
      newCubies[3][3] = cubies[7][1];
      newCubies[6][3] = cubies[8][1];

      //Green->White
      newCubies[2][0] = cubies[0][3];
      newCubies[1][0] = cubies[3][3];
      newCubies[0][0] = cubies[6][3];

      //White->Blue
      newCubies[2][5] = cubies[0][0];
      newCubies[5][5] = cubies[1][0];
      newCubies[8][5] = cubies[2][0];

      //Rotate Red
      newCubies[0][2] = cubies[6][2];
      newCubies[1][2] = cubies[3][2];
      newCubies[2][2] = cubies[0][2];
      newCubies[3][2] = cubies[7][2];
      newCubies[5][2] = cubies[1][2];
      newCubies[6][2] = cubies[8][2];
      newCubies[7][2] = cubies[5][2];
      newCubies[8][2] = cubies[2][2];

      for (int i=0;i<9;++i) {
        for (int j=0;j<6;++j) {
          cubies[i][j] = newCubies[i][j];
        }
      }

    }
  }


}

void cube_B(int n, int cubies[9][6]) {

  int newCubies[9][6];
  for (int i=0;i<9;++i) {
    for (int j=0;j<6;++j) {
      newCubies[i][j] = cubies[i][j];
    }
  }

  if (n>=0) {

    for (int x=0; x<n; ++x) {

      //Yellow->Blue
      newCubies[6][5] = cubies[0][1];
      newCubies[3][5] = cubies[1][1];
      newCubies[0][5] = cubies[2][1];

      //Blue->White
      newCubies[6][0] = cubies[0][5];
      newCubies[7][0] = cubies[3][5];
      newCubies[8][0] = cubies[6][5];

      //White->Green
      newCubies[8][3] = cubies[6][0];
      newCubies[5][3] = cubies[7][0];
      newCubies[2][3] = cubies[8][0];

      //Green->Yellow
      newCubies[0][1] = cubies[2][3];
      newCubies[1][1] = cubies[5][3];
      newCubies[2][1] = cubies[8][3];

      //Rotate Orange
      newCubies[0][4] = cubies[6][4];
      newCubies[1][4] = cubies[3][4];
      newCubies[2][4] = cubies[0][4];
      newCubies[3][4] = cubies[7][4];
      newCubies[5][4] = cubies[1][4];
      newCubies[6][4] = cubies[8][4];
      newCubies[7][4] = cubies[5][4];
      newCubies[8][4] = cubies[2][4];

      for (int i=0;i<9;++i) {
        for (int j=0;j<6;++j) {
          cubies[i][j] = newCubies[i][j];
        }
      }

    }
  }


}
