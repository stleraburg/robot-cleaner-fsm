#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>
#include <QPixmap>
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), robotItem(nullptr), dockItem(nullptr), moveTimer(nullptr), fsmTimer(nullptr), batteryTimer(nullptr), batteryLevel(100), currentFSMFrame(0)
{
    ui->setupUi(this);

    // FSM DIAGRAM VIEW (TOP)
    QGraphicsScene* scene = new QGraphicsScene(this);
    QPixmap pixmap("C:/Users/tactile_lab/Downloads/Idle/1.png");
    scene->addPixmap(pixmap);
    ui->fsmView->setScene(scene);

    // BATTERY ICON (TOP RIGHT)
    QGraphicsScene* batteryScene = new QGraphicsScene(this);
    batteryItem = batteryScene->addPixmap(QPixmap("C:/Users/tactile_lab/Downloads/Idle/10.png"));
    batteryItem->setScale(0.2);
    ui->batteryView->setScene(batteryScene);

    // MAP VIEW (BOTTOM)
    QGraphicsScene* mapScene = new QGraphicsScene(this);
    QPixmap carpet("C:/Users/tactile_lab/Downloads/Idle/17.png");
    mapScene->setSceneRect(0, 0, carpet.width(), carpet.height());
    mapScene->addPixmap(carpet);

    // Dock
    QPixmap dockPixmap("C:/Users/tactile_lab/Downloads/Idle/dock.png");
    dockItem = mapScene->addPixmap(dockPixmap);
    QTransform flip;
    flip.scale(-1, 1);
    dockItem->setTransform(flip, true);
    dockItem->setScale(0.3);
    dockItem->setPos(1550, 500);

    // Robot
    QPixmap robotImg("C:/Users/tactile_lab/Downloads/Idle/16.png");
    robotItem = mapScene->addPixmap(robotImg);
    robotItem->setScale(0.2);
    robotItem->setPos(1050, 600);

    // Cat (Sleeping Initially)
    QPixmap catSleeping("C:/Users/tactile_lab/Downloads/Idle/cat_sleep.png");
    catItem = mapScene->addPixmap(catSleeping);
    catItem->setScale(0.2);
    catItem->setPos(getRandomDustPosition());
    catItem->setZValue(1);
    catItem->setVisible(true);

    ui->mapView->setScene(mapScene);
    mapGraphicsScene = mapScene;

    // FSM Timer
    fsmTimer = new QTimer(this);
    connect(fsmTimer, &QTimer::timeout, this, &MainWindow::updateFSMFrame);

    // Battery Timer
    batteryTimer = new QTimer(this);
    connect(batteryTimer, &QTimer::timeout, this, &MainWindow::updateBattery);

    idleTimer = new QTimer(this);
    idleTimer->setSingleShot(true);

    connect(idleTimer, &QTimer::timeout, this, [this]() {
        generateInitialDust();
        updateFSMToIdle();
        if (!catHasReacted) {
            catItem->setPixmap(QPixmap("C:/Users/tactile_lab/Downloads/Idle/cat_sleep.png"));
        }
        catItem->setVisible(true);
    });

    chargingStepTimer = new QTimer(this);
    isInterrupted = false;

    generateInitialDust();
    updateFSMToIdle();

}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_startButton_clicked() {
    isInterrupted = false;
    if (dustItems.isEmpty()) return;
    cleanDustOneByOne(0);
}

void MainWindow::cleanDustOneByOne(int index) {
    if (index >= dustItems.size()) {
        goToDock();
        return;
    }

    QGraphicsPixmapItem* targetDust = dustItems[index];
    if (!targetDust || batteryLevel <= 0) {
        goToDock();
        return;
    }

    startFSMVibration({
        "C:/Users/tactile_lab/Downloads/Idle/1.png",
        "C:/Users/tactile_lab/Downloads/Idle/3.png",
        "C:/Users/tactile_lab/Downloads/Idle/7.png",
        "C:/Users/tactile_lab/Downloads/Idle/3.png",
        "C:/Users/tactile_lab/Downloads/Idle/1.png"
    });

    animateRobotTo(targetDust->pos(), [=]() {
        targetDust->setVisible(false);
        batteryLevel = std::max(0, batteryLevel - 20);
        updateBattery();

        if (batteryLevel <= 0 || isInterrupted) {
            goToDock();
            return;
        }

        cleanDustOneByOne(index + 1);
    });
}

void MainWindow::chargeBattery() {
    currentChargeStep = 0;
    int neededSteps = (100 - batteryLevel) / 20;

    fsmTimer->stop();
    // fsmTimer->disconnect();

    startFSMVibration({
        "C:/Users/tactile_lab/Downloads/Idle/1.png",
        "C:/Users/tactile_lab/Downloads/Idle/5.png",
        "C:/Users/tactile_lab/Downloads/Idle/9.png",
        "C:/Users/tactile_lab/Downloads/Idle/5.png",
        "C:/Users/tactile_lab/Downloads/Idle/1.png"
    });

    chargingStepTimer->start(1500);
    connect(chargingStepTimer, &QTimer::timeout, this, [=]() {
        if (currentChargeStep < neededSteps) {
            batteryLevel = std::min(100, batteryLevel + 20);
            updateBattery();
            currentChargeStep++;
        } else {
            chargingStepTimer->stop();
            chargingStepTimer->disconnect();
            updateBattery();
            catItem->setPixmap(QPixmap("C:/Users/tactile_lab/Downloads/Idle/cat_sleep.png"));
            catHasReacted = false;
            idleTimer->start(5000);
        }
    });
}



void MainWindow::goToDock() {
    startFSMVibration({
        "C:/Users/tactile_lab/Downloads/Idle/1.png",
        "C:/Users/tactile_lab/Downloads/Idle/4.png",
        "C:/Users/tactile_lab/Downloads/Idle/8.png",
        "C:/Users/tactile_lab/Downloads/Idle/4.png",
        "C:/Users/tactile_lab/Downloads/Idle/1.png"
    });

    animateRobotTo(QPointF(1050, 600), [this]() {
        if (batteryLevel < 100) {
            startFSMVibration({
                "C:/Users/tactile_lab/Downloads/Idle/1.png",
                "C:/Users/tactile_lab/Downloads/Idle/5.png",
                "C:/Users/tactile_lab/Downloads/Idle/9.png",
                "C:/Users/tactile_lab/Downloads/Idle/5.png",
                "C:/Users/tactile_lab/Downloads/Idle/1.png"
            });
            chargeBattery();
        } else {
            startFSMVibration({"C:/Users/tactile_lab/Downloads/Idle/1.png"});
        }
    });
}

void MainWindow::animateRobotTo(QPointF position, std::function<void()> callback) {
    if (!robotItem) return;

    moveTarget = position;

    if (!moveTimer) {
        moveTimer = new QTimer(this);
    }

    moveTimer->stop();
    moveTimer->disconnect();

    connect(moveTimer, &QTimer::timeout, this, [=]() {
        QPointF current = robotItem->pos();
        qreal dx = moveTarget.x() - current.x();
        qreal dy = moveTarget.y() - current.y();

        QPointF robotPos = robotItem->pos();
        QPointF catPos = catItem->pos();
        double dist = std::hypot(robotPos.x() - catPos.x(), robotPos.y() - catPos.y());

        if (dist < 70.0 && !catHasReacted) {
            catHasReacted = true;
            catItem->setPixmap(QPixmap("C:/Users/tactile_lab/Downloads/Idle/cat_alert.png"));

            QTimer::singleShot(500, this, [this]() {
                catItem->setPixmap(QPixmap("C:/Users/tactile_lab/Downloads/Idle/cat_run.png"));

                QTimer::singleShot(300, this, [this]() {
                    QPointF robotPos = robotItem->pos();
                    QPointF catPos = catItem->pos();
                    QPointF direction = catPos - robotPos;

                    qreal length = std::hypot(direction.x(), direction.y());
                    if (length == 0) length = 1;
                    QPointF unitDir = direction / length;

                    qreal minX = 450, maxX = 851;
                    qreal minY = 450, maxY = 601;

                    qreal runDistance = 200.0;
                    QPointF newCatPos;
                    bool moved = false;

                    for (int attempts = 0; attempts < 5; ++attempts) {
                        newCatPos = catPos + unitDir * runDistance;
                        newCatPos.setX(std::clamp(newCatPos.x(), minX, maxX));
                        newCatPos.setY(std::clamp(newCatPos.y(), minY, maxY));

                        if ((int)newCatPos.x() != (int)catPos.x() || (int)newCatPos.y() != (int)catPos.y()) {
                            moved = true;
                            break;
                        }

                        runDistance /= 2;
                    }

                    if (!moved) {
                        // Fallback: move to opposite corner
                        qreal midX = (minX + maxX) / 2;
                        qreal midY = (minY + maxY) / 2;
                        newCatPos.setX(catPos.x() < midX ? maxX : minX);
                        newCatPos.setY(catPos.y() < midY ? maxY : minY);
                    }

                    catItem->setPos(newCatPos);
                });

            });
        }


        if (qAbs(dx) < 1 && qAbs(dy) < 1) {
            moveTimer->stop();
            robotItem->setPos(moveTarget);
            if (callback) callback();
            return;
        }

        QPointF step(current.x() + dx * 0.1, current.y() + dy * 0.1);
        robotItem->setPos(step);
    });

    moveTimer->start(22);
}



QPointF MainWindow::getRandomDustPosition() {
    int x = QRandomGenerator::global()->bounded(450, 851);
    int y = QRandomGenerator::global()->bounded(450, 601);
    return QPointF(x, y);
}

void MainWindow::startFSMVibration(const QStringList &frames) {
    fsmFrames = frames;
    currentFSMFrame = 0;
    fsmTimer->start(200);
}

void MainWindow::updateFSMFrame() {
    if (fsmFrames.isEmpty()) return;

    QPixmap pix(fsmFrames[currentFSMFrame]);
    if (!pix.isNull()) {
        ui->fsmView->scene()->clear();
        ui->fsmView->scene()->addPixmap(pix);
    }

    currentFSMFrame = (currentFSMFrame + 1) % fsmFrames.size();
}

void MainWindow::updateBattery() {
    static QStringList levels = {
        "C:/Users/tactile_lab/Downloads/Idle/10.png",
        "C:/Users/tactile_lab/Downloads/Idle/11.png",
        "C:/Users/tactile_lab/Downloads/Idle/12.png",
        "C:/Users/tactile_lab/Downloads/Idle/13.png",
        "C:/Users/tactile_lab/Downloads/Idle/14.png",
        "C:/Users/tactile_lab/Downloads/Idle/15.png"
    };

    int index = qMin(levels.size() - 1, 5 - (batteryLevel / 20));
    batteryItem->setPixmap(QPixmap(levels[index]));
}


void MainWindow::on_dockButton_clicked() {
    isInterrupted = true;
}


void MainWindow::generateInitialDust() {
    int dustCount = QRandomGenerator::global()->bounded(1, 5);
    dustItems.clear();

    for (int i = 0; i < dustCount; ++i) {
        QPixmap dustImg("C:/Users/tactile_lab/Downloads/Idle/18.png");
        QGraphicsPixmapItem* dust = mapGraphicsScene->addPixmap(dustImg);
        dust->setScale(0.1);
        QPointF pos = getRandomDustPosition();
        dust->setPos(pos);
        dustItems.append(dust);
    }
}


void MainWindow::updateFSMToIdle() {
    startFSMVibration({
        "C:/Users/tactile_lab/Downloads/Idle/1.png",
        "C:/Users/tactile_lab/Downloads/Idle/2.png",
        "C:/Users/tactile_lab/Downloads/Idle/6.png",
        "C:/Users/tactile_lab/Downloads/Idle/2.png",
        "C:/Users/tactile_lab/Downloads/Idle/1.png"
    });
}



