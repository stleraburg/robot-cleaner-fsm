#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsPixmapItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void on_dockButton_clicked();
    void updateFSMFrame();

private:
    Ui::MainWindow *ui;

    // Graphics items
    QGraphicsPixmapItem *robotItem;
    QGraphicsPixmapItem *dustItem;
    QGraphicsPixmapItem* dockItem;
    QList<QGraphicsPixmapItem*> dustItems;
    QGraphicsPixmapItem *batteryItem;
    QGraphicsPixmapItem *catItem;
    QGraphicsScene* mapGraphicsScene;

    // FSM animation
    QTimer* fsmTimer;
    QStringList fsmFrames;
    int currentFSMFrame;
    bool catHasReacted = false;


    int currentChargeStep;

    // Robot movement
    QTimer* moveTimer;
    QPointF moveTarget;

    // Battery logic
    int batteryLevel;
    QTimer* batteryDrainTimer;
    QTimer* batteryChargeTimer;
    QTimer* batteryTimer;

    QTimer* idleTimer;            // For generating new dust after 5s
    QTimer* chargingStepTimer;    // Step-by-step battery charging
    bool isInterrupted;           // Track if Return to Dock was clicked

    // Function declarations
    void animateRobotTo(QPointF position, std::function<void()> onArrive = nullptr);
    QPointF getRandomDustPosition();
    void startFSMVibration(const QStringList &frames);

    void updateBattery();
    void startBatteryDrain();
    void chargeBattery();
    void cleanDustOneByOne(int index);
    void goToDock();
    void generateInitialDust();
    void updateFSMToIdle();


};

#endif // MAINWINDOW_H
