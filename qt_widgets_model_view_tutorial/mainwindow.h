#pragma once

/**
 * @file mainwindow.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-03-05
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "qlist.h"
#include "qobject.h"
#include "qobjectdefs.h"
#include "qstandarditemmodel.h"
#include "qtreeview.h"
#include "qwidget.h"
#include <qmainwindow.h>

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget* parent = nullptr);

private:
  QList<QStandardItem*>
  prepare_window_row(const QString& first, const QString& second,
                     const QString& third) const;

private:
  QTreeView* tree_view_;
  QStandardItemModel* standard_item_model_;
};