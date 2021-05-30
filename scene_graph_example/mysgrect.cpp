#include "mysgrect.h"
#include <QtQuick/QtQuick>

MySGRect::MySGRect()
{
    setFlag(ItemHasContents);
}

QSGNode *MySGRect::updatePaintNode(QSGNode * oldNode, QQuickItem::UpdatePaintNodeData *)
{
    auto* rootNode = static_cast<QSGTransformNode*>(oldNode);
    if(rootNode==nullptr){
        rootNode = new QSGTransformNode;

        // Set up the background:
        child_node_ = new QSGSimpleRectNode(QRectF(0,0, width(), height()), Qt::red);
        rootNode->appendChildNode(child_node_);
    }else {
        child_node_->setRect(0, 0, width(), height());
    }

    // ==========================================================
    // EXAMPLE 1 : CLIPPING
    QSGSimpleRectNode * childNode = new QSGSimpleRectNode(QRectF(0,0, width(), height()), Qt::black);

    // Create the clipping node:
    QSGClipNode * clipNode = new QSGClipNode;

    // Indicating we want to clip in an area that has a coordinate of (0,0), width same as the
    // QML (QtQuickItem) item and a height of 60 pixesl
    clipNode->setClipRect(QRectF(0,0, width(), 60));
    clipNode->setIsRectangular(true);

    // Add the child node to the clip node
    clipNode->appendChildNode(childNode);

    // Add the clip node to the root node
    rootNode->appendChildNode(clipNode);

    // ==========================================================

    // // SECOND EXAMPLE : TRANFORMATION
    // QSGSimpleRectNode * SecondChildNode = new QSGSimpleRectNode(QRectF(0,0, width(), height()), Qt::blue);

    // // Create the scale matrix
    // QMatrix4x4 scaleMatrix;
    // scaleMatrix.scale(0.5);

    // // Create the transform node
    // QSGTransformNode * transformNode = new QSGTransformNode;

    // // Assign the Matrix
    // transformNode->setMatrix(scaleMatrix);

    // // Add the second child node to the transform node
    // transformNode->appendChildNode(SecondChildNode);

    // // Add the transform node to the root node.
    // rootNode->appendChildNode(transformNode);

    // // ==========================================================

    // // EXAMPLE 3 : SCALE THE ENTIRE TREE IN 2 STEP
    // // Create a matrix and assign scale
    // QMatrix4x4 scaleRootMatrix;
    // scaleRootMatrix.scale(0.5);

    // // set the matrix of the root
    // rootNode->setMatrix(scaleRootMatrix);

    return rootNode;
}
