#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QVBoxLayout"
#include "QTableWidget"
#include "QLabel"
#include "QSpinBox"
#include "QPushButton"
#include "QDebug"
#include <string>
#include "QTimer"
#include <functional>
#include <thread>  // Include for std::thread and std::this_thread
#include <chrono>
#include "QScrollBar"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->changeDimensionBtn, &QPushButton::clicked, this, &MainWindow::colorsElevatorsAndFloors);

    connect(ui->fireButton, &QPushButton::clicked, this, &MainWindow::fireBtnClicked);
    connect(ui->powerOutageBtn, &QPushButton::clicked, this, &MainWindow::powerBtnClicked);
    connect(ui->upButton, &QPushButton::clicked, this, &MainWindow::upButtonClicked);
    connect(ui->downButton, &QPushButton::clicked, this, &MainWindow::upButtonClicked);
    connect(ui->blockDoor, &QPushButton::clicked, this, &MainWindow::blockDoorClicked);
    connect(ui->closeDoor, &QPushButton::clicked, this, &MainWindow::closeDoorClicked);
    connect(ui->openDoor, &QPushButton::clicked, this, &MainWindow::openDoorClicked);
    connect(ui->helpButton, &QPushButton::clicked, this, &MainWindow::helpBtnClicked);




    //disable elevator buttons because the user is not in it yet
    disableElevatorButtons();

    resize(800, 600);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::colorsElevatorsAndFloors()
{

    int numFloors = ui->floorsValue->value();
    int numElevators = ui->elevatorValue->value();
    std::string messageString = "Floor Dimensions Have been set to: "+std::to_string(numFloors) +" Floors and  " + std::to_string(numElevators) + " Elevators\n";
    logMessage(messageString);

    //set the value of the possible starting floor
    ui->startingFloorInput->setMaximum(numFloors-1);

    // Iterate over all possible floors and elevators
    for (int i = 0; i < 8; i++) {
        for (int x = 0; x < 8; x++) {
            std::string floorName = "floor_" + getFloorIndex(i, x);
            const char* floorNameCStr = floorName.c_str();

            // Find the widget by object name
            QWidget *child = this->findChild<QWidget*>(floorNameCStr);

            // Check if the widget was found
            if (child) {
                // Set the style sheet based on the condition
                if (i < numFloors && x < numElevators) {
                    if (i == 0) {
                        child->setStyleSheet("background-color: yellow; border: 1px solid black;");
                    } else {
                        child->setStyleSheet("background-color: lightgrey; border: 1px solid black;");
                    }
                } else {
                    // Reset the color for unused widgets
                    child->setStyleSheet("background-color: grey; border: 1px solid black;");
                }
            } else {
                qDebug() << "Widget not found:" << floorNameCStr;
            }
        }
    }
    //initialize the array positions
    initializeElevatorArrayPositions();
}
void MainWindow::initializeElevatorArrayPositions(){
    int numElevators = ui->elevatorValue->value();
    elevatorPosition.resize(numElevators);
    // Fill each sub-vector with values [0, 1], [0, 2], ..., [0, numElevators-1]
    for (int i = 0; i < numElevators; i++) {
        elevatorPosition[i].resize(2);  // Each sub-vector has two elements
        elevatorPosition[i][0] = 0;     // First element is always 0
        elevatorPosition[i][1] = i; // Second element is 1, 2, ..., numElevators
    }
    //printElevatorArrayPositions();
}
void MainWindow::blockDoorClicked(){
    std::string message = "Elevator Door is blocked, remove obstacle to proceed\n";
    logMessage(message);
    std::string stateDisplayString = "elevatorStateDisplay";
    QTextEdit *stateDisplay = this->findChild<QTextEdit*>(stateDisplayString.c_str());
    std::string stateString = "Door Blocked";
    stateDisplay->setText(QString::fromStdString(stateString));
    stateDisplay->setAlignment(Qt::AlignCenter);
    stateDisplay->setStyleSheet("color:red;background-color: black");
}
void MainWindow::closeDoorClicked(){
    std::string message = "Close door button has been pressed\n";
    logMessage(message);
}
void MainWindow::openDoorClicked(){
    std::string message = "Open door button has been pressed\n";
    logMessage(message);
}
void MainWindow::helpBtnClicked(){
    std::string message = "User pressed the help button\nCalling help...\n";
    logMessage(message);
    std::string stateDisplayString = "elevatorStateDisplay";
    QTextEdit *stateDisplay = this->findChild<QTextEdit*>(stateDisplayString.c_str());
    std::string stateString = "Calling Help";
    stateDisplay->setText(QString::fromStdString(stateString));
    stateDisplay->setAlignment(Qt::AlignCenter);
    stateDisplay->setStyleSheet("color:red;background-color: black");
}
void MainWindow::printElevatorArrayPositions() const {
    for (const auto &elevator : elevatorPosition) {
//        qDebug() << "[" << std::to_string(elevator[0]) << ", " << std::to_string(elevator[1]) << "]";
        qDebug() << "[" << QString::number(elevator[0]) << ", " << QString::number(elevator[1]) << "]";

    }
}
std::string MainWindow::getFloorIndex(int numFloors, int numElevators)
{
    return std::to_string(numFloors) + std::to_string(numElevators);
}

void MainWindow::fireBtnClicked()
{
    std::string stateDisplayString = "elevatorStateDisplay";
    QTextEdit *stateDisplay = this->findChild<QTextEdit*>(stateDisplayString.c_str());
    std::string stateString = "FIRE";
    stateDisplay->setText(QString::fromStdString(stateString));
    stateDisplay->setAlignment(Qt::AlignCenter);
    stateDisplay->setStyleSheet("color:red;background-color: black");

    //wait 2 seconds, then proceed
    std::this_thread::sleep_for(std::chrono::seconds(2));


    QTimer::singleShot(2000, this, [this]() {
        logMessage("Fire button has been pressed ,moving all elevators to ground floor\n");
        int numElevators = ui->elevatorValue->value();
        //set destination to ground floor
        this->userFloor = 0;
        qDebug() << "Fire Button has been pressed";
        for(int i=0; i<numElevators; i++){
            int elevatorFloor = elevatorPosition[i][0];
            int elevatorNumber = elevatorPosition[i][1];
            std::string ind = getFloorIndex(elevatorFloor, elevatorNumber);
            moveElevator(ind);
        }
        printElevatorArrayPositions();
    });

    // Allow the event loop to continue processing events
    QCoreApplication::processEvents();
}
void MainWindow::powerBtnClicked()
{
    std::string stateDisplayString = "elevatorStateDisplay";
    QTextEdit *stateDisplay = this->findChild<QTextEdit*>(stateDisplayString.c_str());
    std::string stateString = "POWER OUTAGE";
    stateDisplay->setText(QString::fromStdString(stateString));
    stateDisplay->setAlignment(Qt::AlignCenter);
    stateDisplay->setStyleSheet("color:red;background-color: black");

    //wait 2 seconds, then proceed
    std::this_thread::sleep_for(std::chrono::seconds(2));


    QTimer::singleShot(2000, this, [this]() {
        logMessage("Fire button has been pressed ,moving all elevators to ground floor\n");
        int numElevators = ui->elevatorValue->value();
        //set destination to ground floor
        this->userFloor = 0;
        qDebug() << "Fire Button has been pressed";
        for(int i=0; i<numElevators; i++){
            int elevatorFloor = elevatorPosition[i][0];
            int elevatorNumber = elevatorPosition[i][1];
            std::string ind = getFloorIndex(elevatorFloor, elevatorNumber);
            moveElevator(ind);
        }
        //printElevatorArrayPositions();
    });

    // Allow the event loop to continue processing events
    QCoreApplication::processEvents();
}
std::vector<int> MainWindow::findClosestElevator(int userFloor) const {
    if (elevatorPosition.empty()) {
        qDebug() << "Elevator positions not initialized.";
        return {};  // Return an empty vector if elevator positions are not initialized
    }

    int minDistance = std::abs(userFloor - elevatorPosition[0][0]);
    std::vector<int> closestElevator = elevatorPosition[0];

    for (const auto &elevator : elevatorPosition) {
        int distance = std::abs(userFloor - elevator[0]);
        if (distance < minDistance) {
            minDistance = distance;
            closestElevator = elevator;
        }
    }

    return closestElevator;
}
void MainWindow::upButtonClicked()
{
   //check weight before proceeding
    std::string inElevatorString = "weightSection";
    QTextEdit *weight = this->findChild<QTextEdit*>(inElevatorString.c_str());
    int weightValue = weight->toPlainText().toInt();

    std::string stateDisplayString = "elevatorStateDisplay";
    QTextEdit *stateDisplay = this->findChild<QTextEdit*>(stateDisplayString.c_str());

    if (weightValue > 450) {
        std::string weightOverloadMessage = "There is a weight overload in the elevator";
        logMessage(weightOverloadMessage);
        // Display in the elevator
        std::string stateString = "Weight Overload";
        stateDisplay->setText(QString::fromStdString(stateString));
        stateDisplay->setAlignment(Qt::AlignCenter);
        stateDisplay->setStyleSheet("color:red;background-color: black");
        return;
    }


    int userFloor = ui->startingFloorInput->value();
    setUserFloor(userFloor);

//    // Find the closest elevator to the user's floor
    std::vector<int> closestElevator = findClosestElevator(userFloor);
    // Convert elements to integers
    int elevatorFloor = closestElevator[0];
    int elevatorNumber = closestElevator[1];
    std::string ind = getFloorIndex(elevatorFloor, elevatorNumber);

    std::string floorName = "floor_" + ind;
    //const char* floorNameCStr = floorName.c_str();

    std::string first = "An Elevator is requested on floor "+std::to_string(userFloor)+"\n";
    std::string second = "And the closest elevator to that floor is Elevator: "+std::to_string(elevatorNumber)+"\n";
    std::string message = first + second;
    logMessage(message);
    moveElevator(ind);
//    setElevatorDisplayPositions();
}

void MainWindow::downButtonClicked()
{
    //int spinBoxValue = ui->startingFloorInput->value();
}

void MainWindow::moveElevator(const std::string &currentPosition)
{
    //starting position
    int startingRow = currentPosition[0] - '0';
    int startingColumn = currentPosition[1] - '0';

    std::string destinationFloorName = "floor_" + getFloorIndex(this->userFloor, startingColumn);
    //const char* destinationFloorNameCStr = destinationFloorName.c_str();

    //qDebug() << "The current floor is floor_"<<getFloorIndex(startingRow, startingColumn) << "The detination floor is" <<destinationFloorName;

    std::string direction = "DOWN";
    if(this->userFloor - startingRow > 0){
        direction = "UP";
    }
    int delay = 1000;


    // set up variables
    std::string inElevatorString = "inElevatorDisplay";
    QTextEdit *display = this->findChild<QTextEdit*>(inElevatorString.c_str());
    std::string stateDisplayString = "elevatorStateDisplay";
    QTextEdit *stateDisplay = this->findChild<QTextEdit*>(stateDisplayString.c_str());

    if(direction == "UP"){
        for(int i=startingRow; i<this->userFloor;i++){
            setTimeout([i,this, startingColumn,display, stateDisplay](){
                //            //change current to lightgrey
                std::string startingFloorName = "floor_" + getFloorIndex(i, startingColumn);
                const char* startingFloorNameCStr = startingFloorName.c_str();
                QWidget *current = this->findChild<QWidget*>(startingFloorNameCStr);
                current->setStyleSheet("background-color:lightgrey; border: 1px solid black;");

                //now change the one above to red
                std::string nextFloorName = "floor_" + getFloorIndex(i+1, startingColumn);
                const char* nextFloorNameCStr = nextFloorName.c_str();
                QWidget *next = this->findChild<QWidget*>(nextFloorNameCStr);
                next->setStyleSheet("background-color: yellow; border: 1px solid black;");

                //display on the elevator display ->i is what changes
                std::string sFN = "elevatorPosition_" + std::to_string(startingColumn);
                const char* sFNCStr = sFN.c_str();
                //qDebug() << "the position elevator is: "<< sFNCStr;
                QTextEdit *ct = this->findChild<QTextEdit*>(sFNCStr);
                ct->setAlignment(Qt::AlignCenter);
                ct->setStyleSheet("color:green;background-color: black");
                std::string pos = std::to_string(i+1);
                ct->setText(QString::fromStdString(pos));
                ct->setStyleSheet("background-color: black; text-align:center; color:green;");


                std::string stateString = "Floor "+pos;
                stateDisplay->setText(QString::fromStdString(stateString));
                stateDisplay->setAlignment(Qt::AlignCenter);
                stateDisplay->setStyleSheet("color:green;background-color: black");
                std::string displayPos = "Elevator "+std::to_string(startingColumn+1);
                display->setText(QString::fromStdString(displayPos));
                display->setAlignment(Qt::AlignCenter);
                display->setStyleSheet("color:green;background-color: black");


                //the console log message
                std::string first = "Elevator "+std::to_string(startingColumn+1)+": moved up to floor "+std::to_string(i+1)+".\n";
                logMessage(first);

                if(i==this->userFloor-1){
                    std::string m1 = "Elevator "+std::to_string(startingColumn+1)+": has reached destination "+std::to_string(userFloor)+".\n";
                    std::string m2 = "Elevator "+std::to_string(startingColumn+1)+": Bell rings, doors open.\n";
                    logMessage(m1+m2);
                }

            }, delay* (i - startingRow));
        }
    }else{
        for(int i=startingRow; i>this->userFloor;i--){
            setTimeout([i,this, startingColumn, display, stateDisplay](){
                std::string startingFloorName = "floor_" + getFloorIndex(i, startingColumn);
                const char* startingFloorNameCStr = startingFloorName.c_str();
                QWidget *current = this->findChild<QWidget*>(startingFloorNameCStr);
                current->setStyleSheet("background-color:lightgrey; border: 1px solid black;");

                //            //now change the one above to red
                std::string nextFloorName = "floor_" + getFloorIndex(i-1, startingColumn);
                const char* nextFloorNameCStr = nextFloorName.c_str();
                QWidget *next = this->findChild<QWidget*>(nextFloorNameCStr);
                next->setStyleSheet("background-color: yellow; border: 1px solid black;");


                //display on the elevator display ->i is what changes
                std::string sFN = "elevatorPosition_" + std::to_string(startingColumn);
                const char* sFNCStr = sFN.c_str();
                //qDebug() << "the position elevator is: "<< sFNCStr;
                QTextEdit *ct = this->findChild<QTextEdit*>(sFNCStr);
                ct->setAlignment(Qt::AlignCenter);
                ct->setStyleSheet("color:green;background-color: black");
                std::string pos = std::to_string(i-1);
                ct->setText(QString::fromStdString(pos));
                ct->setStyleSheet("background-color: black; text-align:center; color:green;");


                std::string stateString = "Floor "+pos;
                stateDisplay->setText(QString::fromStdString(stateString));
                stateDisplay->setAlignment(Qt::AlignCenter);
                stateDisplay->setStyleSheet("color:green;background-color: black");
                std::string displayPos = "Elevator "+std::to_string(startingColumn+1);
                display->setText(QString::fromStdString(displayPos));
                display->setAlignment(Qt::AlignCenter);
                display->setStyleSheet("color:green;background-color: black");

                //the console log message
                std::string first = "Elevator "+std::to_string(startingColumn+1)+": moved down to floor "+std::to_string(i-1)+".\n";
                logMessage(first);


                if(i==this->userFloor+1){
                    std::string m1 = "Elevator "+std::to_string(startingColumn+1)+": has reached destination "+std::to_string(userFloor)+".\n";
                    std::string m2 = "Elevator "+std::to_string(startingColumn+1)+": Bell rings, doors open.\n";
                    logMessage(m1+m2);
                }
            }, delay* (startingRow - i));
        }
    }
    //set the new value of the elevation position
    updatePosition(currentPosition, getFloorIndex(this->userFloor, startingColumn));
    occupiedElevator = getFloorIndex(this->userFloor, startingColumn);
    //log the message reached destination
    // now allow the user to press the buttons inside the elevator
    enableElevatorButtons();
}
int MainWindow::getUserFloor(){
    return this->userFloor;
}
int MainWindow::setUserFloor(int newValue){
    this->userFloor = newValue;
}
void MainWindow::setTimeout(std::function<void()> function, int delay) {
    QTimer::singleShot(delay, this, function);
}
// Function to update the elevatorPosition
void MainWindow::updatePosition(const std::string& oldPosition, const std::string& newPosition) {
    int oldRow = oldPosition[0] - '0';
    int oldColumn = oldPosition[1] - '0';

    int newRow = newPosition[0] - '0';
    int newColumn = newPosition[1] - '0';

    // Find the old position in elevatorPosition
    auto it = std::find(elevatorPosition.begin(), elevatorPosition.end(), std::vector<int>{oldRow, oldColumn});

    // Check if the old position was found
    if (it != elevatorPosition.end()) {
        // Update the old position with the new values
        (*it)[0] = newRow;
        (*it)[1] = newColumn;

        // Print the updated elevatorPosition for demonstration
        //printElevatorArrayPositions();
    } else {
        qDebug() << "Old position not found in elevatorPosition.";
    }
}
void MainWindow::disableElevatorButtons(){
    for (int i = 1; i < 8; ++i) {
        std::string buttonName = "elevatorButton_" + std::to_string(i);
        const char* formattedName = buttonName.c_str();
        QPushButton* button = this->findChild<QPushButton*>(formattedName);
        if (button) {
            button->setStyleSheet("background-color: darkgrey;");
            disconnect(button, &QPushButton::clicked, 0, 0);
        } else {
//            qDebug() << "Button not found: " << buttonName;
            qDebug() << "Button not found:" << QString::fromStdString(buttonName);

        }
    }
}

void MainWindow::enableElevatorButtons(){
    for (int i = 1; i < 8; ++i) {
        std::string buttonName = "elevatorButton_" + std::to_string(i);
        const char* formattedName = buttonName.c_str();
        QPushButton* button = this->findChild<QPushButton*>(formattedName);
        if (button) {
            connect(button, &QPushButton::clicked, this, &MainWindow::elevatorButtonClicked);
        } else {
            //qDebug() << "Button not found: " << buttonName;
            qDebug() << "Button not found:" << QString::fromStdString(buttonName);

        }
    }
}
void MainWindow::elevatorButtonClicked() {
    std::string inElevatorString = "weightSection";
    QTextEdit *weight = this->findChild<QTextEdit*>(inElevatorString.c_str());
    int weightValue = weight->toPlainText().toInt();
    std::string stateDisplayString = "elevatorStateDisplay";
    QTextEdit *stateDisplay = this->findChild<QTextEdit*>(stateDisplayString.c_str());

    if (weightValue > 450) {
        std::string weightOverloadMessage = "There is a weight overload in the elevator";
        logMessage(weightOverloadMessage);
        // Display in the elevator
        std::string stateString = "Weight Overload";
        stateDisplay->setText(QString::fromStdString(stateString));
        stateDisplay->setAlignment(Qt::AlignCenter);
        stateDisplay->setStyleSheet("color:red;background-color: black");
        return;
    }
    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    int buttonText = senderButton->text().toInt();
    //qDebug() << "The occupied elevator is "<<occupiedElevator;
    qDebug() << "Button not found:" << QString::fromStdString(occupiedElevator);


    std::string first = "User is in elevator: " + std::string(1, occupiedElevator[1]) + " and wants to go to floor: " + std::to_string(buttonText) + "\n";
    logMessage(first);
    // now move the elevator to its desired destination
    setUserFloor(buttonText);
    moveElevator(occupiedElevator);
}

void MainWindow::logMessage(std::string newMessage){
    std::string log = "logWindow";
    QTextEdit *logWindow = this->findChild<QTextEdit*>(log.c_str());
    QScrollBar *scrollBar = logWindow->verticalScrollBar();
    std::string oldText = logWindow->toPlainText().toStdString();
    std:: string newText = oldText + newMessage;
    logWindow->setText(QString::fromStdString(newText));
    scrollBar->setValue(scrollBar->maximum());
}
