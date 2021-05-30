#include "qreport.h"

#include <QApplication>

auto main(int argc, char** argv) -> int {
  QApplication app(argc, argv); // QImage need this
  QReport report;
  report.MakePDFReport();
}