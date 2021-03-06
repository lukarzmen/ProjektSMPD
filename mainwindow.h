#ifndef MAINWINDOW_H
#include "ficherelement.h"
#define MAINWINDOW_H

#include <QMainWindow>
#include <fstream>
#include <QCheckBox>
#include <QFileDialog>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include "fischer.h"
#include"database.h"
#include "vectorutil.h"
#include "objectconverter.h"
#include "clasiffier.h"
#include "classifierQuality.h"

class ficherElement;
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
    void addClassfiers();
    void FSupdateButtonState(void);
    void FSsetButtonState(bool state);
    bool OpenFile();
    void addItemsToKComboBox(int k);
    void addItemsToInvervalsComboBox(int k);
    bool isExtracted;
    vector<Object> objects_afterExtraction;


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
    Fischer fischer;
    Database database;
    vectorutil vectorUtil;
    objectConverter converter;
    int testObjectSetAmount = 0;
    ficherElement bestFischerElement;
    vector<vector<Object>> crossvalidationSets;
    int intervals;
    vector<classifier_object> bootstrapSets;
};

#endif // MAINWINDOW_H
