#pragma once

#include <QQuickItem>

class QSGSimpleRectNode;

class MySGRect : public QQuickItem {
  Q_OBJECT
public:
  MySGRect();

signals:

public slots:

  // QQuickItem interface
protected:
  QSGNode* updatePaintNode(QSGNode*, UpdatePaintNodeData*) override;

private:
  QSGSimpleRectNode* child_node_ = nullptr;
};
