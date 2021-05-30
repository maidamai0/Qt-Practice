#include "drag_widget.h"
#include "qframe.h"
#include "qgesture.h"
#include "qnamespace.h"

#include <QDrag>
#include <QDragEnterEvent>
#include <QFrame>
#include <QLabel>
#include <QMimeData>
#include <QPainter>
#include <QPixmap>

DraggableWidget::DraggableWidget(QWidget* parent) : QFrame(parent) {
  setMinimumSize(200, 200);
  // setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
  setAcceptDrops(true);

  auto* boat_icon = new QLabel(this);
  boat_icon->setPixmap(QPixmap(":/boat.png"));
  boat_icon->move(10, 10);
  boat_icon->show();
  boat_icon->setAttribute(Qt::WA_DeleteOnClose);

  auto* car_icon = new QLabel(this);
  car_icon->setPixmap(QPixmap(":/car.png"));
  car_icon->move(100, 10);
  car_icon->show();
  car_icon->setAttribute(Qt::WA_DeleteOnClose);

  auto* house_icon = new QLabel(this);
  house_icon->setPixmap(QPixmap(":/house.png"));
  house_icon->move(10, 80);
  house_icon->show();
  house_icon->setAttribute(Qt::WA_DeleteOnClose);

  grabGesture(Qt::TapAndHoldGesture);
}

void DraggableWidget::dragEnterEvent(QDragEnterEvent* event) {
  if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
    if (event->source() == this) {
      event->setDropAction(Qt::MoveAction);
      event->accept();
    } else {
      event->acceptProposedAction();
    }
  } else {
    event->ignore();
  }
}

void DraggableWidget::dragMoveEvent(QDragMoveEvent* event) {
  if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
    if (event->source() == this) {
      event->setDropAction(Qt::MoveAction);
      event->accept();
    } else {
      event->acceptProposedAction();
    }
  } else {
    event->ignore();
  }
}

// void DraggableWidget::dropEvent(QDropEvent* event) {
//   if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
//     QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
//     QDataStream dataStream(&itemData, QIODevice::ReadOnly);

//     QPixmap pixmap;
//     QPoint offset;
//     dataStream >> pixmap >> offset;

//     auto* newIcon = new QLabel(this);
//     newIcon->setPixmap(pixmap);
//     newIcon->move(event->pos() - offset);
//     newIcon->show();
//     newIcon->setAttribute(Qt::WA_DeleteOnClose);

//     if (event->source() == this) {
//       event->setDropAction(Qt::MoveAction);
//       event->accept();
//     } else {
//       event->acceptProposedAction();
//     }
//   } else {
//     event->ignore();
//   }
// }

// void DraggableWidget::mousePressEvent(QMouseEvent* event) {
//   // return QFrame::mousePressEvent(event);

//   QLabel* child = static_cast<QLabel*>(childAt(event->pos()));
//   if (child == nullptr)
//     return;

//   QPixmap pixmap = *child->pixmap();

//   QByteArray itemData;
//   QDataStream dataStream(&itemData, QIODevice::WriteOnly);
//   dataStream << pixmap << QPoint(event->pos() - child->pos());

//   auto* mimeData = new QMimeData;
//   mimeData->setData("application/x-dnditemdata", itemData);

//   auto* drag = new QDrag(this);
//   drag->setMimeData(mimeData);
//   drag->setPixmap(pixmap);
//   drag->setHotSpot(event->pos() - child->pos());

//   if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
//     child->close();
//   } else {
//     child->show();
//     child->setPixmap(pixmap);
//   }
// }

bool DraggableWidget::event(QEvent* event) {
  if (event->type() == QEvent::Gesture) {
    return gesture_event(dynamic_cast<QGestureEvent*>(event));
  }

  return QFrame::event(event);
}

bool DraggableWidget::gesture_event(QGestureEvent* event) {
  if (event->gesture(Qt::TapAndHoldGesture)) {
    on_tap_and_hold(event);
  }
  return true;
}

void DraggableWidget::on_tap_and_hold(QGestureEvent* event) {
  auto* gesture = dynamic_cast<QTapAndHoldGesture*>(event->gesture(Qt::TapAndHoldGesture));
  if (!gesture) {
    // TODO tonghao log here
    //    LOG_W("can not create gesture from gesture event");
    return;
  }

  const auto pos = mapFromGlobal(gesture->position().toPoint());
  auto* child = static_cast<QLabel*>(childAt(pos));
  if (child == nullptr)
    return;

  QPixmap pixmap = child->pixmap();

  QByteArray itemData;
  QDataStream dataStream(&itemData, QIODevice::WriteOnly);
  dataStream << pixmap << QPoint(pos - child->pos());

  auto* mimeData = new QMimeData;
  mimeData->setData("application/x-dnditemdata", itemData);

  auto* drag = new QDrag(this);
  drag->setMimeData(mimeData);
  drag->setPixmap(pixmap);
  drag->setHotSpot(pos - child->pos());

  if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
    child->close();
  } else {
    child->show();
    child->setPixmap(pixmap);
  }
}