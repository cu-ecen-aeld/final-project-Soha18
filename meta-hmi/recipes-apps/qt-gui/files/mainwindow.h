#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void toggleFan();
    void manualControlToggled(bool checked);
    void adjustFanSpeed(int speed);
    void updateUI();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    bool fanOn;
    bool manualMode;
    
    // Helper functions
    void initializeModeFiles();
    void readSensorValues();
    void updateFanStatusDisplay();
    bool writeToFile(const QString &filepath, const QString &content);
    QString readFromFile(const QString &filepath);
};

#endif // MAINWINDOW_H
