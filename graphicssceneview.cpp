#include <QMessageBox>

#include "graphicssceneview.h"
#include "gridcell.h"
#include "bfs.h"


GraphicsSceneView::GraphicsSceneView(QWidget *parent)
    : QGraphicsView(parent)
{
    m_scene = new QGraphicsScene(this);
    setScene(m_scene);
    qRegisterMetaType<CellItem>("CellItem");
}

GraphicsSceneView::~GraphicsSceneView()
{
    delete m_scene;
}

void GraphicsSceneView::setModel(GridModel *model)
{
    m_model = model;
}

void GraphicsSceneView::onGenerateButtonClick()
{
    m_scene->clear();
    m_cellFrom.reset();
    m_cellTo.reset();

    // get data from the model
    const int  maxWidth = m_model->columnCount();
    const int maxHeight = m_model->rowCount();
    const int cellSize = m_model->cellSize();


    for (int i = 0; i < maxWidth; i++){
        for (int j = 0; j < maxHeight; j++){
            auto qvar = m_model->data(m_model->index(i, j), Qt::DisplayRole);
            CellItem *item = qvar.value<CellItem *>();

            m_scene->addItem(new GridCell(item->row(), item->column(), item->obstacle(), cellSize));
        }
    }
}


void GraphicsSceneView::wheelEvent(QWheelEvent *event) {
    const QPoint angleDelta = event->angleDelta();

    // scale calc
    const double scaleFactor = 1.05;

    if (angleDelta.y() > 0) {
        scale(
            scaleFactor,
            scaleFactor
        );
    } else if (angleDelta.y() < 0) {
        scale(
            1.0 / scaleFactor,
            1.0 / scaleFactor
        );
    }

    event->accept();
}

GridModel *GraphicsSceneView::model() const
{
    return m_model;
}

QGraphicsScene *GraphicsSceneView::scene() const
{
    return m_scene;
}


void GraphicsSceneView::onSceneSelectionChange() {
    auto selectedItems = m_scene->selectedItems();
    if (selectedItems.isEmpty()) return;

    auto selectedCell = static_cast<GridCell *>(selectedItems.first());

    if (selectedCell->isObstacle()) {
        QMessageBox msgBox;
        msgBox.setText("This cell is an obstacle, please select another one.");
        msgBox.exec();
        return;
    }

    if (m_cellFrom == std::nullopt && m_cellTo == std::nullopt) {
        selectedCell->setPen(QPen(Qt::yellow, 2));
        m_cellFrom = IntPair(selectedCell->xPos(), selectedCell->yPos());
    }
    else if (m_cellFrom != std::nullopt && m_cellTo == std::nullopt) {
        selectedCell->setPen(QPen(Qt::blue, 2));
        m_cellTo = IntPair(selectedCell->xPos(), selectedCell->yPos());

        const int  maxWidth = m_model->columnCount();
        const int maxHeight = m_model->rowCount();

        const int cellSize = m_model->cellSize();

        DDArray<bool> cellAvailability(maxWidth);
        cellAvailability.fill(QList<bool>(maxHeight));

        const auto items = m_scene->items();

        for (auto item: items) {
            auto cell = static_cast<GridCell *>(item);
            cellAvailability[cell->xPos()][cell->yPos()] = !cell->isObstacle();
        }

        BFS bfs(cellAvailability, m_cellFrom.value(), m_cellTo.value());
        bfs.calculate();

        const auto p = bfs.getPath();

        for (const auto &cell: p) {
            auto item = m_scene->itemAt(QPointF(cell.first * cellSize, cell.second * cellSize), QTransform());
            if (item != nullptr) {
                auto cell = static_cast<QGraphicsRectItem *>(item);
                cell->setBrush(QBrush(Qt::green));
            }
        }
    }
}
