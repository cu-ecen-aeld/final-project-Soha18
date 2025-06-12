#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , fanOn(false)
    , manualMode(false)
{
    ui->setupUi(this);

    // Set fixed window properties
    this->setFixedSize(800, 480);
    this->setStyleSheet("background-color: lightblue;");
    this->setWindowFlags(Qt::FramelessWindowHint);

    // Connect signals to slots
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::toggleFan);
    connect(ui->checkBox, &QCheckBox::toggled, this, &MainWindow::manualControlToggled);
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::adjustFanSpeed);
    connect(ui->pushButton_2, &QPushButton::clicked, this, []() {
        qApp->quit();
    });

    // Initially disable manual controls
    ui->pushButton->setEnabled(false);
    ui->horizontalSlider->setEnabled(false);

    // Initialize mode files with default values
    initializeModeFiles();

    // Timer to read sensor values and update UI
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateUI);
    timer->start(1000); // Update every second
}

void MainWindow::initializeModeFiles()
{
    // Initialize mode to auto
    writeToFile("/tmp/fan_mode.txt", "auto");
    
    // Initialize manual status to off
    writeToFile("/tmp/fan_manual_status.txt", "off");
    
    qDebug() << "[GUI] Mode files initialized";
}

bool MainWindow::writeToFile(const QString &filepath, const QString &content)
{
    QFile file(filepath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << content;
        file.close();
        return true;
    } else {
        qWarning() << "[GUI] Failed to write to" << filepath;
        return false;
    }
}

QString MainWindow::readFromFile(const QString &filepath)
{
    QFile file(filepath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString content = in.readAll().trimmed();
        file.close();
        return content;
    }
    return QString();
}

void MainWindow::updateUI()
{
    // Read and display sensor values
    readSensorValues();
    
    // Update fan status display (optional - read current fan state if daemon writes it)
    updateFanStatusDisplay();
}

void MainWindow::readSensorValues()
{
    QFile file("/tmp/bme280_values.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString lastLine;
        while (!in.atEnd())
            lastLine = in.readLine();

        QStringList values = lastLine.split(QRegExp("\\s+"), Qt::SkipEmptyParts);
        
        if (values.size() >= 8) {
            bool ok1, ok2, ok3;
            double temp = values[1].replace(QRegularExpression("[^\\d\\.]+"), "").toDouble(&ok1);
            double press = values[3].toDouble(&ok2);
            double humid = values[6].toDouble(&ok3);

            if (ok1) ui->lcdNumber->display(temp);
            if (ok2) ui->lcdNumber_2->display(press);
            if (ok3) ui->lcdNumber_3->display(humid);
        }
        file.close();
    }
}

void MainWindow::updateFanStatusDisplay()
{
    // Optional: If daemon writes current fan state to a file, read and display it
    // This helps show the actual fan state even in auto mode
    QString currentMode = readFromFile("/tmp/fan_mode.txt");
    
    if (currentMode == "auto") {
        ui->pushButton->setText("AUTO MODE");
        ui->pushButton->setStyleSheet("background-color: lightgreen;");
    } else if (manualMode) {
        ui->pushButton->setText(fanOn ? "Fan ON" : "Fan OFF");
        ui->pushButton->setStyleSheet(fanOn ? "background-color: red;" : "background-color: gray;");
    }
}

void MainWindow::toggleFan()
{
    if (!manualMode) {
        qDebug() << "[GUI] Fan toggle ignored - not in manual mode";
        return;
    }

    fanOn = !fanOn;
    
    // Write the manual fan status to file (daemon will read this)
    QString status = fanOn ? "on" : "off";
    if (writeToFile("/tmp/fan_manual_status.txt", status)) {
        qDebug() << "[GUI] Manual fan status set to:" << status;
        ui->pushButton->setText(fanOn ? "Fan ON" : "Fan OFF");
        ui->pushButton->setStyleSheet(fanOn ? "background-color: red;" : "background-color: gray;");
    } else {
        qWarning() << "[GUI] Failed to write manual fan status";
        // Revert the state if file write failed
        fanOn = !fanOn;
    }
}

void MainWindow::manualControlToggled(bool checked)
{
    manualMode = checked;
    
    // Enable/disable manual controls
    ui->pushButton->setEnabled(checked);
    ui->horizontalSlider->setEnabled(checked);
    
    // Write mode to file (daemon will read this)
    QString mode = checked ? "manual" : "auto";
    if (writeToFile("/tmp/fan_mode.txt", mode)) {
        qDebug() << "[GUI] Mode set to:" << mode;
        
        if (!checked) {
            // Switching to auto mode - reset manual controls
            fanOn = false;
            ui->pushButton->setText("AUTO MODE");
            ui->pushButton->setStyleSheet("background-color: lightgreen;");
            // Also reset manual status file
            writeToFile("/tmp/fan_manual_status.txt", "off");
        } else {
            // Switching to manual mode - initialize button text
            ui->pushButton->setText("Fan OFF");
            ui->pushButton->setStyleSheet("background-color: blue;");
        }
    } else {
        qWarning() << "[GUI] Failed to write mode file";
        // Revert checkbox if file write failed
        ui->checkBox->setChecked(!checked);
        manualMode = !checked;
    }
}

void MainWindow::adjustFanSpeed(int speed)
{
    qDebug() << "[GUI] Fan speed set to" << speed << "%";
    
    // Optional: Write fan speed to file if you want to implement variable speed control
    // This would require modifications to the daemon to read and use speed values
    QString speedStr = QString::number(speed);
    writeToFile("/tmp/fan_speed.txt", speedStr);
}

MainWindow::~MainWindow()
{
    // Clean shutdown - set to auto mode and turn off manual fan
    writeToFile("/tmp/fan_mode.txt", "auto");
    writeToFile("/tmp/fan_manual_status.txt", "off");
    
    delete ui;
}
