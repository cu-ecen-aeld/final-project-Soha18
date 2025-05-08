#include "mainwindow.h"
#include <QApplication>
#include <QRegularExpression>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set window background color to light blue
    //this->setFixedSize(480, 320);
    this->setStyleSheet("background-color: lightblue;");

    // Connect Exit button
    connect(ui->pushButton, &QPushButton::clicked, this, [this]() {
        this->close();
        qApp->quit();
    });

    // Set label texts
    ui->label->setText("Temperature (°C):");
    ui->label_2->setText("Pressure (hPa):");
    ui->label_3->setText("Humidity (%):");

    // Optional: Style LCD numbers
    ui->lcdNumber->setStyleSheet("background-color: white; color: black;");
    ui->lcdNumber_2->setStyleSheet("background-color: white; color: black;");
    ui->lcdNumber_3->setStyleSheet("background-color: white; color: black;");

    // Start timer to read sensor values
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::readSensorValues);
    timer->start(1000);  // Every 1 seconds
}

void MainWindow::readSensorValues()
{
    QFile file("/tmp/bme280_values.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
	QString lastLine;
        while (!in.atEnd())
            lastLine = in.readLine();

        // Example: "Temp: 23.61°C  Pressure: 984.99 hPa  Humidity: 39.69 %rH"
        QStringList values = lastLine.split(QRegExp("\\s+"), Qt::SkipEmptyParts);
        qDebug() << "Split values:" << values;
        if (values.size() >= 8) {
            bool ok1, ok2, ok3;
    	    double temp = values[1].replace(QRegularExpression("[^\\d\\.]+"), "").toDouble(&ok1);
    	    double press = values[3].toDouble(&ok2);
    	    double humid = values[6].toDouble(&ok3);
	    qDebug() << "Temp:" << temp << "Press:" << press << "Humid:" << humid;

            if (ok1) ui->lcdNumber->display(temp);
            if (ok2) ui->lcdNumber_2->display(press);
            if (ok3) ui->lcdNumber_3->display(humid);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

