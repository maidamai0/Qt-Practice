#include <QApplication>
#include <QHBoxLayout>

#include "drag_widget.h"
#include "qboxlayout.h"
#include "qglobal.h"
#include "qobject.h"
#include "qwidget.h"

auto main(int argc, char** argv) -> int {
  //   Q_INIT_RESOURCE(resource);

  QApplication app(argc, argv);

  QWidget main_windget;
  auto* layout = new QHBoxLayout(&main_windget);
  layout->addWidget(new DraggableWidget);
  layout->addWidget(new DraggableWidget);

  main_windget.setWindowTitle(QObject::tr("Draggable Icons"));
  main_windget.show();

  return QApplication::exec();
}