#include <QSettings>

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initConnections();
    readSettings();

    m_gridModel = new GridModel(this);
    ui->graphicsView->setModel(m_gridModel);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initConnections()
{
    connect(ui->generateButton, &QPushButton::clicked, this, [&](){
        // pass required values into model and call the handler
        const int sz = ui->cellSizeSpinBox->value();
        const int rate = ui->obstaclesPercentSpinBox->value();
        const int w = ui->widthSpinBox->value();
        const int h = ui->heightSpinBox->value();

        ui->graphicsView->model()->setCellSize(sz);
        ui->graphicsView->model()->setObstacleSpawnRate(rate);
        ui->graphicsView->model()->setRowsAndColumns(h, w);
        ui->graphicsView->onGenerateButtonClick();
    });
    connect(ui->graphicsView->scene(), &QGraphicsScene::selectionChanged, ui->graphicsView, &GraphicsSceneView::onSceneSelectionChange);

}


void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings(QString("config.ini"), QSettings::IniFormat);
    settings.setValue("geometry", saveGeometry());
    QMainWindow::closeEvent(event);
}


void MainWindow::readSettings()
{
    QSettings settings(QString("config.ini"), QSettings::IniFormat);
    restoreGeometry(settings.value("geometry").toByteArray());
}
