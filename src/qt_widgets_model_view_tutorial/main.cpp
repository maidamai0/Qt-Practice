#include <QApplication>
#include <QListView>
#include <QTableView>
#include <QTreeView>

#include "mainwindow.h"
#include "model.h"

auto main(int argc, char** argv) -> int {
  QApplication app(argc, argv);

  Model model;

  QListView list;
  list.setWindowTitle("List view");
  list.setModel(&model);
  list.show();

  QTreeView tree;
  tree.setWindowTitle("Tree view");
  tree.setModel(&model);
  tree.show();

  QTableView table;
  table.setWindowTitle("Table view");
  table.setModel(&model);
  table.show();

  MainWindow mainwindow;
  mainwindow.show();

  return QApplication::exec();
}