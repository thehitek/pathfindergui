#include <QRandomGenerator>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gridcell.h"
#include <algorithm>
#include "bfs.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_scene;
}

void MainWindow::initConnections()
{
    connect(ui->generateButton, &QPushButton::clicked, this, &MainWindow::onGenerateButtonClicked);
}

void MainWindow::onGenerateButtonClicked()
{
    if (m_scene != nullptr) delete m_scene;
    m_scene = new QGraphicsScene();

    const int maxHeight = ui->heightSpinBox->value();
    const int maxWidth = ui->widthSpinBox->value();
    const int obstacleSpawnPercent = ui->obstaclesPercentSpinBox->value();
    const int cellSize = 30;

    auto randomizer = QRandomGenerator::global();
    DDArray<bool> cellAvailability(maxWidth);
    cellAvailability.fill(QList<bool>(maxHeight));

    for (int i = 0; i < maxWidth; i++){
        for (int j = 0; j < maxHeight; j++){
            int randomPercent = randomizer->bounded(0, 100);
            bool isObstacle = randomPercent < obstacleSpawnPercent;

            cellAvailability[i][j] = !isObstacle;

            GridCell* cell = new GridCell(i, j, isObstacle, cellSize);
            m_scene->addItem(cell);
        }
    }

    const auto items = m_scene->items();

    QList<GridCell *> cells(maxHeight * maxWidth);
    std::transform(items.begin(),
                   items.end(),
                   cells.begin(),
                   [](QGraphicsItem* item)
                   {
                        // qDebug() << item->scenePos();
                        return static_cast<GridCell *>(item);
                   });

    // qDebug() << "Cells: " << cells.length();
    ui->graphicsView->setScene(m_scene);

    BFS bfs(cellAvailability, IntPair(0, 0), IntPair(maxWidth - 1, maxHeight - 1));
    bfs.calculate();

    const auto p = bfs.getPath();
    // qDebug() << p;

    for (const auto &cell: p) {
        auto item = m_scene->itemAt(QPointF(cell.first * cellSize, cell.second * cellSize), QTransform());
        if (item != nullptr) {
            auto cell = static_cast<QGraphicsRectItem *>(item);
            cell->setBrush(QBrush(Qt::green));
        }
    }
}
