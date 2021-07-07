#include "qabstractitemmodel.h"
#include "qstandarditemmodel.h"
#include <QApplication>
#include <QtQml>
#include <QtWidgets>

class IndividualModel : public QStandardItemModel {
public:
  IndividualModel(QObject* parent = nullptr) : QStandardItemModel(4, 2, parent) {
    for (int row = 0; row < 4; ++row) {
      QStandardItem* item0 = new QStandardItem;
      item0->setData(QString("row %1, column 0").arg(row), TitleRole);
      setItem(row, 0, item0);

      QStandardItem* item1 = new QStandardItem;
      item1->setData(QString("row %1, column 1").arg(row), AuthorRole);
      setItem(row, 1, item1);
    }
  }

  QVariant data(const QModelIndex& _index, int role = Qt::DisplayRole) const override {
    switch (role) {
      case TitleRole:
        return QStandardItemModel::data(index(_index.row(), 0, QModelIndex{}), role);
      case AuthorRole:
        return QStandardItemModel::data(index(_index.row(), 1, QModelIndex{}), role);
    }
  }

  QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override {
    return QStandardItemModel::index(row, column, parent);
  }

  enum { TitleRole = Qt::UserRole, AuthorRole };

  QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE {
    QHash<int, QByteArray> names;
    names[TitleRole] = "title";
    names[AuthorRole] = "author";
    return names;
  }
};

class CompositeModel : public QAbstractItemModel {
public:
  CompositeModel() {
    for (int i = 0; i < 3; ++i) {
      QStandardItemModel* model = new IndividualModel(this);
      mModels.append(model);
    }
  }

  enum { ModelRole = Qt::UserRole };

  QVariant data(const QModelIndex& index, int role) const Q_DECL_OVERRIDE {
    if (!index.isValid())
      return QVariant();

    if (role != ModelRole)
      return QVariant();

    return QVariant::fromValue(mModels.at(index.row()));
  }

  QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE {
    if (!hasIndex(row, column, parent))
      return QModelIndex();

    return createIndex(row, column);
  }

  QModelIndex parent(const QModelIndex&) const Q_DECL_OVERRIDE {
    return QModelIndex();
  }

  int rowCount(const QModelIndex& = QModelIndex()) const Q_DECL_OVERRIDE {
    return mModels.size();
  }

  int columnCount(const QModelIndex& = QModelIndex()) const Q_DECL_OVERRIDE {
    return 1;
  }

  QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE {
    QHash<int, QByteArray> names;
    names[ModelRole] = "individualModel";
    return names;
  }

private:
  Q_DISABLE_COPY(CompositeModel)

  QVector<QStandardItemModel*> mModels;
};

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  QQmlApplicationEngine engine;

  CompositeModel compositeModel;
  engine.rootContext()->setContextProperty("compositeModel", QVariant::fromValue(&compositeModel));

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  return app.exec();
}