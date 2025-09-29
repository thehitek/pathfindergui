#ifndef GRAPHICSSCENEVIEW_H
#define GRAPHICSSCENEVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>

#include "gridmodel.h"
#include "types.h"

class GraphicsSceneView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsSceneView(QWidget *parent = nullptr);
    ~GraphicsSceneView();

    void setModel(GridModel *model);

    QGraphicsScene *scene() const;
    GridModel *model() const;

public slots:
    void onGenerateButtonClick();
    void onSceneSelectionChange();

protected:
    void wheelEvent(QWheelEvent *event);

private:
    QGraphicsScene *m_scene = nullptr;
    GridModel      *m_model = nullptr;

    std::optional<IntPair> m_cellFrom = std::nullopt;
    std::optional<IntPair>   m_cellTo = std::nullopt;
};

#endif // GRAPHICSSCENEVIEW_H
