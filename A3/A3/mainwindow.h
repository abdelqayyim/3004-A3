#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void onButton1Clicked();
    void printElevatorArrayPositions() const;
    std::vector<int>findClosestElevator(int userFloor) const;
    void moveElevator(const std::string &currentPosition);
    int getUserFloor();

private slots:
    void fireBtnClicked();
    void powerBtnClicked();
    void blockDoorClicked();
    void closeDoorClicked();
    void openDoorClicked();
    void helpBtnClicked();
    void upButtonClicked();
    void downButtonClicked();
    void colorsElevatorsAndFloors();
    std::string getFloorIndex(int numFloors, int numElevators);
    void initializeElevatorArrayPositions();
    int setUserFloor(int newValue);
    void setTimeout(std::function<void()> function, int delay);

private:
    std::vector<std::vector<int>> elevatorPosition;
    void updatePosition(const std::string& oldPosition, const std::string& newPosition);
    void elevatorButtonClicked();
    void disableElevatorButtons();
    void enableElevatorButtons();
    void logMessage(std::string newMessage);

    QPushButton* elevatorButtons[8];
    QTimer *moveTimer;
    int userFloor;
    std::string occupiedElevator; // ex: "10"

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
