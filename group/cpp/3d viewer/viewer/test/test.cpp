#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "../obj/obj.hpp"
#include "../obj/parse.h"

using namespace std;
using namespace s21;

void paint_tyan();

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  if (RUN_ALL_TESTS() == 0) {
    paint_tyan();
  }

  return 0;
}

TEST(Parse_and_normalize, cube) {
  string path = "samples/cube.obj";
  vector<size_t> res = parse_file(path);
  EXPECT_EQ(res[0], 8);
  EXPECT_EQ(res[1], 16);

  Figure fig = *get_figure();
  EXPECT_NEAR(fig.points[0], -0.58, 1e-6);
  EXPECT_NEAR(fig.points[1], -0.55, 1e-6);
  EXPECT_NEAR(fig.points[2], -0.34, 1e-6);

  EXPECT_NEAR(fig.points[3], 0.17, 1e-6);
  EXPECT_NEAR(fig.points[4], -0.11, 1e-6);
  EXPECT_NEAR(fig.points[5], -0.84, 1e-6);

  EXPECT_NEAR(fig.points[6], -0.05, 1e-6);
  EXPECT_NEAR(fig.points[7], 0.76, 1e-6);
  EXPECT_NEAR(fig.points[8], -0.41, 1e-6);

  EXPECT_NEAR(fig.points[9], -0.80, 1e-6);
  EXPECT_NEAR(fig.points[10], 0.33, 1e-6);
  EXPECT_NEAR(fig.points[11], 0.09, 1e-6);

  EXPECT_NEAR(fig.points[12], 0.05, 1e-6);
  EXPECT_NEAR(fig.points[13], -0.76, 1e-6);
  EXPECT_NEAR(fig.points[14], 0.41, 1e-6);

  EXPECT_NEAR(fig.points[15], 0.80, 1e-6);
  EXPECT_NEAR(fig.points[16], -0.33, 1e-6);
  EXPECT_NEAR(fig.points[17], -0.09, 1e-6);

  EXPECT_NEAR(fig.points[18], 0.58, 1e-6);
  EXPECT_NEAR(fig.points[19], 0.55, 1e-6);
  EXPECT_NEAR(fig.points[20], 0.34, 1e-6);

  EXPECT_NEAR(fig.points[21], -0.17, 1e-6);
  EXPECT_NEAR(fig.points[22], 0.11, 1e-6);
  EXPECT_NEAR(fig.points[23], 0.84, 1e-6);

  fig.normalize();

  EXPECT_EQ(fig.edges[0], 0);
  EXPECT_EQ(fig.edges[1], 1);
  EXPECT_EQ(fig.edges[2], 1);
  EXPECT_EQ(fig.edges[3], 2);
  EXPECT_EQ(fig.edges[4], 2);
  EXPECT_EQ(fig.edges[5], 3);
  EXPECT_EQ(fig.edges[6], 3);
  EXPECT_EQ(fig.edges[7], 0);

  EXPECT_EQ(fig.edges[8], 4);
  EXPECT_EQ(fig.edges[9], 5);
  EXPECT_EQ(fig.edges[10], 5);
  EXPECT_EQ(fig.edges[11], 6);
  EXPECT_EQ(fig.edges[12], 6);
  EXPECT_EQ(fig.edges[13], 7);
  EXPECT_EQ(fig.edges[14], 7);
  EXPECT_EQ(fig.edges[15], 4);

  EXPECT_EQ(fig.edges[16], 0);
  EXPECT_EQ(fig.edges[17], 4);
  EXPECT_EQ(fig.edges[18], 4);
  EXPECT_EQ(fig.edges[19], 7);
  EXPECT_EQ(fig.edges[20], 7);
  EXPECT_EQ(fig.edges[21], 3);
  EXPECT_EQ(fig.edges[22], 3);
  EXPECT_EQ(fig.edges[23], 0);

  EXPECT_EQ(fig.edges[24], 1);
  EXPECT_EQ(fig.edges[25], 5);
  EXPECT_EQ(fig.edges[26], 5);
  EXPECT_EQ(fig.edges[27], 6);
  EXPECT_EQ(fig.edges[28], 6);
  EXPECT_EQ(fig.edges[29], 2);
  EXPECT_EQ(fig.edges[30], 2);
  EXPECT_EQ(fig.edges[31], 1);
}

void paint_tyan() {
  printf("\033[48;5;93m\033[1;37m  ⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⡠⢴⣴⣾⣿⡿⠓⡠⠀⠀⠀⠀⠠⢄⠁⢀\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⠀⠳⣽⡽⠀⠀⡠⢊⣴⣿⣿⣿⣡⠖⠁⣀⡤⢖⠟⠁⡠⠀⡙⢿⣷⣄\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠐⡀⠀⠀⠀⠀⢠⣾⣿⣿⢽⣿⣿⣿⣥⠖⣻⣯⡾⠃⠀⡔⡀⠀⣷⢸⢿⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⢰⠀⠀⠀⢠⢟⣿⠃⢀⣾⣿⠟⠋⢀⡾⢋⣾⠃⣠⡾⢰⡇⡇⣿⣿⡞⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⡤⣈⡀⠀⢀⠏⣼⣧⡴⣼⠟⠁⠀⠀⡾⠁⣾⡇⣰⢿⠃⢾⣿⣷⣿⣿⣇⢿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠱⠼⠊⠀⠄⡜⣿⣿⡿⠃⠈⠁⠀⢸⠁⢠⡿⣰⢯⠃⠀⠘⣿⣿⣿⣿⣿⠸\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⠀⠀⡘⡀⣸⣿⣱⡤⢴⣄⠀⠈⠀⠘⣷⠏⠌⠢⡀⠀⢿⣿⣿⣿⡟⡄\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⢀⣌⠌⣴⣿⣿⠃⣴⣿⣟⡇⠀⠀⠀⠟⠀⠀⠀⠈⠢⢈⣿⡟⣿⡗⡇\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⢀⡴⡻⣡⣾⠟⢹⡇⠀⡇⢄⢿⠇⠀⠀⠀⠀⠀⠀⣽⣶⣄⡀⠘⢷⡹⣿⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⣧⣾⡿⠋⠁⢀⡜⠙⡄⠓⠐⠁⠀⠀⠀⠀⠀⠀⡼⠛⠻⣟⠛⣆⠈⢷⣿⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⣴⣾⣟⣵⣿⣿⣿⣁⢇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡧⠠⠔⡹⠀⢸⠀⣼⣿⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠿⡽⢫⡉⠀⣠⠔⠁⡀⠕⠠⡀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠖⠊⠀⠀⢊⣾⢿⡿⠉\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠁⠀⡹⢨⠁⠐⠈⢀⡠⠐⠁⠄⠡⡀⡀⠀⠀⠀⠀⠀⠀⠀⠠⠶⢛⡨⠊⠀⠀\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⡜⠀⠈⣂⠀⠀⠀⠀⡠⠐⠉⡆⠀⣀⢀⣀⣀⣀⡀⠀⠀⣀⠴⣁⡀⠤⠀⠀\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠈⠀⠀⠀⡇⠑⢄⠀⠀⠀⠀⣲⢥⡎⠀⢰⠀⢸⠀⢀⠉⠙⣿⣧⣀⣀⣂⣤⣼\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠆⠁⠃⠀⠀⠈⠒⠒⠊⣸⠚⠁⠀⠀⠀⠀⠀⠀⠀⡜⠁⠀⠀⠀⠀⠈⠚\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⠀⠂⠀⠀⠀⠀⠀⢀⠋⢆⠀⠀⠀⠀⠀⠀⠀⡘⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠒⠂⠀⠀⠐⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");

  printf("\033[42m\033[1;37m   YOU'RE AWESOME!  \\(^.^)/   \033[0m\n");
}