#include <QRandomGenerator>
#include <QSettings>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gridcell.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initConnections();
    readSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_scene;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings(QString("config.ini"), QSettings::IniFormat);
    settings.setValue("geometry", saveGeometry());
    QMainWindow::closeEvent(event);
}

void MainWindow::initConnections()
{
    connect(ui->generateButton, &QPushButton::clicked, this, &MainWindow::onGenerateButtonClicked);
}

void MainWindow::readSettings()
{
    QSettings settings(QString("config.ini"), QSettings::IniFormat);
    restoreGeometry(settings.value("geometry").toByteArray());
}

void MainWindow::onGenerateButtonClicked()
{
    if (m_scene != nullptr) delete m_scene;
    m_cellFrom.reset();
    m_cellTo.reset();

    m_scene = new QGraphicsScene(ui->graphicsView);
    connect(m_scene, &QGraphicsScene::selectionChanged, this, &MainWindow::onSceneSelectionChanged);

    const int maxHeight = ui->heightSpinBox->value();
    const int maxWidth = ui->widthSpinBox->value();
    const int obstacleSpawnPercent = ui->obstaclesPercentSpinBox->value();
    const int cellSize = ui->cellSizeSpinBox->value();

    auto randomizer = QRandomGenerator::global();

    for (int i = 0; i < maxWidth; i++){
        for (int j = 0; j < maxHeight; j++){
            int randomPercent = randomizer->bounded(0, 100);
            bool isObstacle = randomPercent < obstacleSpawnPercent;
            GridCell* cell = new GridCell(i, j, isObstacle, cellSize);
            m_scene->addItem(cell);
        }
    }

    ui->graphicsView->setScene(m_scene);
}

void MainWindow::onSceneSelectionChanged() {
    auto selectedItems = m_scene->selectedItems();
    if (selectedItems.isEmpty()) return;

    auto selectedCell = static_cast<GridCell *>(selectedItems.first());
    qDebug() << selectedCell;

    if (m_cellFrom == std::nullopt && m_cellTo == std::nullopt) {
        selectedCell->setPen(QPen(Qt::yellow, 2));
        m_cellFrom = IntPair(selectedCell->xPos(), selectedCell->yPos());
    }
    else if (m_cellFrom != std::nullopt && m_cellTo == std::nullopt) {
        selectedCell->setPen(QPen(Qt::blue, 2));
        m_cellTo = IntPair(selectedCell->xPos(), selectedCell->yPos());

        const int maxHeight = ui->heightSpinBox->value();
        const int maxWidth = ui->widthSpinBox->value();
        const int cellSize = ui->cellSizeSpinBox->value();

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
