#pragma once

/**
 * @file model.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief first simple model
 * @version 0.1
 * @date 2020-03-03
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "qabstractitemmodel.h"
#include "qnamespace.h"
#include "qobject.h"
#include "qobjectdefs.h"
#include "qtimer.h"
#include "qvariant.h"
#include <QAbstractTableModel>
#include <array>

namespace {
constexpr size_t col = 3;
constexpr size_t row = 2;
} // namespace

class Model : public QAbstractTableModel {
  Q_OBJECT
public:
  Model(QObject* parent = nullptr);
  auto rowCount(const QModelIndex& parent = QModelIndex()) const
    -> int override;
  auto columnCount(const QModelIndex& parent = QModelIndex()) const
    -> int override;
  auto data(const QModelIndex& index, int role = Qt::DisplayRole) const
    -> QVariant override;

  auto headerData(int section, Qt::Orientation orentation, int role) const
    -> QVariant override;

  auto setData(const QModelIndex& index, const QVariant& value,
               int role = Qt::EditRole) -> bool override;
  auto flags(const QModelIndex& index) const -> Qt::ItemFlags override;

signals:
  void editCompleted();

private:
  void time_out();

private:
  QTimer timer_;
  std::array<std::array<QString, col>, row> grid_;
};