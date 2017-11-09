#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fstream>
#include <QCheckBox>
#include <QFileDialog>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include "object_model.h"
#include "combination.h"
#include "ficherelement.h"


#include"database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    bool loadFile(const std::string &fileName);
    void updateDatabaseInfo();
    void saveFile(const std::string &fileName);

    void FSupdateButtonState(void);
    void FSsetButtonState(bool state);
    void printCombinations(std::vector<std::vector<int>> &arrayOfCombinations);
    std::map<int,FicherElement> getCombinationsMap(int numberOfFeatures, int dimension);
    vector<Object_model> getObject_Models(vector<Object> &databaseObjects);

private slots:
    void on_FSpushButtonOpenFile_clicked();

    void on_FSpushButtonCompute_clicked();

    void on_FSpushButtonSaveFile_clicked();

    void on_PpushButtonSelectFolder_clicked();


    void on_CpushButtonOpenFile_clicked();

    void on_CpushButtonSaveFile_clicked();

    void on_CpushButtonTrain_clicked();

    void on_CpushButtonExecute_clicked();

private:
    Ui::MainWindow *ui;

private:
     Database database;
};

#endif // MAINWINDOW_H
