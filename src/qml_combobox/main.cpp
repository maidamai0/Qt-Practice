#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStringList>

class ComboModel : public QObject {
  Q_OBJECT;

  Q_PROPERTY(QStringList strings READ strings WRITE setStrings NOTIFY stringsChanged)
public:
  ComboModel() {
    strings_ << "One"
             << "Two"
             << "Three"
             << "Four"
             << "Five"
             << "Six"
             << "Seven"
             << "Eight"
             << "Nine"
             << "Ten"
             << "New";
  }
public slots:
  int addString(const QString& string) {
    strings_.insert(strings_.size() - 1, string);
    qDebug() << "model changed to " << strings_;
    emit stringsChanged();

    return strings_.size() - 2;
  }

  QStringList strings() const {
    return strings_;
  }

  void setStrings(const QStringList& strings) {
    strings_ = strings;
    emit stringsChanged();
  }

signals:
  void stringsChanged();

private:
  QStringList strings_;
};

auto main(int argc, char* argv[]) -> int {
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("comboModel", new ComboModel);
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(
    &engine, &QQmlApplicationEngine::objectCreated, &app,
    [url](QObject* obj, const QUrl& objUrl) {
      if (!obj && url == objUrl)
        QCoreApplication::exit(-1);
    },
    Qt::QueuedConnection);
  engine.load(url);

  return QGuiApplication::exec();
}

#include "main.moc"
