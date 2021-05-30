#include "mainwindow.h"
#include "qlist.h"
#include "qtreeview.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent),
    tree_view_(new QTreeView(this)),
    standard_item_model_(new QStandardItemModel(this)) {
  setCentralWidget(tree_view_);

  const auto row = prepare_window_row("first", "second", "third");
  auto* item = standard_item_model_->invisibleRootItem();
  item->appendRow(row);

  const auto second_row = prepare_window_row("111", "222", "333");
  row.first()->appendRow(second_row);

  const auto third_row = prepare_window_row("aaa", "bbb", "ccc");
  row.first()->appendRow(third_row);

  tree_view_->setModel(standard_item_model_);
  tree_view_->expandAll();
}

auto MainWindow::prepare_window_row(const QString& first, const QString& second,
                                    const QString& third) const
  -> QList<QStandardItem*> {
  return {new QStandardItem(first), new QStandardItem(second),
          new QStandardItem(third)};
}