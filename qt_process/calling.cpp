#include <QProcess>
#include <iostream>

auto main(int argc, char** argv) -> int {
  QProcess ps;
  ps.setProgram("called");

  std::cout << "start" << std::endl;
  ps.startDetached(); // This API return immeadiately
  std::cout << "end" << std::endl;
}