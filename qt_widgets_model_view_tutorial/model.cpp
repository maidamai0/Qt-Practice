#include "model.h"

#include "qabstractitemmodel.h"
#include "qbrush.h"
#include "qcolor.h"
#include "qdatetime.h"
#include "qdebug.h"
#include "qfont.h"
#include "qglobal.h"
#include "qnamespace.h"
#include "qobjectdefs.h"
#include "qtimer.h"
#include "qvariant.h"

Model::Model(QObject* parent) : QAbstractTableModel(parent) {
  timer_.start(1000);
  connect(&timer_, &QTimer::timeout, this, &Model::time_out);
}

auto Model::rowCount(const QModelIndex& parent) const -> int {
  return 2;
}

auto Model::columnCount(const QModelIndex& parent) const -> int {
  return 3;
}

auto Model::data(const QModelIndex& index, int role) const -> QVariant {
  const auto row = index.row();
  const auto column = index.column();
  qDebug() << QString("row %1, col %2, role %3").arg(row).arg(column).arg(role);

  switch (role) {
    case Qt::DisplayRole: {
      if (row == 0 && column == 1) {
        return QString("<--left");
      }

      if (row == 1 && column == 1) {
        return QString("Right-->");
      }

      if (row == 0 && column == 0) {
        return QTime::currentTime().toString();
      }

      return grid_[row][column];
    }
    case Qt::FontRole: {
      if (row == 0 && column == 0) {
        QFont bold;
        bold.setBold(true);
        return bold;
      }
    }
    case Qt::BackgroundRole: {
      if (row == 1 && column == 2) {
        return QBrush(Qt::red);
      }
    }
    case Qt::TextAlignmentRole: {
      if (row == 1 && column == 1) {
        return QVariant(Qt::AlignRight | Qt::AlignVCenter);
      }
    }
    case Qt::CheckStateRole: {
      if (row == 1 && column == 1) {
        return Qt::Checked;
      }
    }
    default: {
      return QVariant();
    }
  }
}

auto Model::headerData(int section, Qt::Orientation orentation, int role) const -> QVariant {
  if (role == Qt::DisplayRole) {
    if (orentation == Qt::Horizontal) {
      switch (section) {
        case 0:
          return QString("first");
        case 1:
          return QString("second");
        case 2:
          return QString("third");
      }
    }

    if (orentation == Qt::Vertical) {
      switch (section) {
        case 0:
          return QString("one");
        case 1:
          return QString("two");
        case 2:
          return QString("three");
      }
    }
  }

  return {};
}

auto Model::setData(const QModelIndex& index, const QVariant& value, int role) -> bool {
  if (role == Qt::EditRole) {
    if (!checkIndex(index)) {
      return false;
    }

    grid_[index.row()][index.column()] = value.toString();

    QString result;
    for (const auto& rows : grid_) {
      for (const auto& data : rows) {
        result += data + " ";
      }
    }

    emit editCompleted();
    return true;
  }

  return false;
}

auto Model::flags(const QModelIndex& index) const -> Qt::ItemFlags {
  return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

void Model::time_out() {
  auto top_left = createIndex(0, 0);
  emit dataChanged(top_left, top_left, {Qt::DisplayRole});
}