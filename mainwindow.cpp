#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include "iostream"
#include <QImage>
#include <QDebug>


using namespace std;
namespace bnu = boost::numeric::ublas;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("SMPD Project by L. Medyk");
    this->setWindowIcon(QIcon(":/icons/icon.png"));
    FSupdateButtonState();
    addClassfiers();
    addItemsToKComboBox(7);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDatabaseInfo()
{
    ui->FScomboBox->clear();
    for(unsigned int i=1; i<=database.getNoFeatures(); ++i)
        ui->FScomboBox->addItem(QString::number(i));

    ui->FStextBrowserDatabaseInfo->setText("Number of classes: " +  QString::number(database.getNoClass()));
    ui->FStextBrowserDatabaseInfo->append("Number of objects: "  +  QString::number(database.getNoObjects()));
    ui->FStextBrowserDatabaseInfo->append("Number of features: "  +  QString::number(database.getNoFeatures()));

}

void MainWindow::FSupdateButtonState(void)
{
    if(database.getNoObjects()==0)
    {
        FSsetButtonState(false);
    }
    else
        FSsetButtonState(true);

}


void MainWindow::FSsetButtonState(bool state)
{
    ui->FScomboBox->setEnabled(state);
    ui->FSpushButtonCompute->setEnabled(state);
    ui->FSpushButtonSaveFile->setEnabled(state);
    ui->FSradioButtonFisher->setEnabled(state);
    ui->FSradioButtonSFS->setEnabled(state);
}

void MainWindow::on_FSpushButtonOpenFile_clicked()
{
    OpenFile();

    FSupdateButtonState();
    updateDatabaseInfo();
}

void MainWindow::on_FSpushButtonCompute_clicked()
{
    int dimension = ui->FScomboBox->currentText().toInt();
    int numberOfClass = database.getNoClass();

    if( ui->FSradioButtonFisher ->isChecked() && numberOfClass == 2)
    {       
        this->bestFischerElement = fischer.getBestFischerElement(database, dimension);
        float bestFischerValue = bestFischerElement.getFischerValue();
        std::vector<int> bestCombinationOfFeatures = bestFischerElement.getVectorOfFeatureCombinations();
        string bestCombinationOfFeaturesString = vectorUtil.vectorToString(bestCombinationOfFeatures);

        ui->FStextBrowserDatabaseInfo->append("Best features combination for Fischer: ["  +  QString::fromStdString(bestCombinationOfFeaturesString) + "] : " + QString::number(bestFischerValue));
    }
    if(ui->FSradioButtonSFS -> isChecked() && numberOfClass == 2)
    {
        this->bestFischerElement = fischer.getBestFischerElementSFC(database, dimension);
        float bestFischerValue = bestFischerElement.getFischerValue();
        std::vector<int> bestCombinationOfFeatures = bestFischerElement.getVectorOfFeatureCombinations();
        string bestCombinationOfFeaturesString = vectorUtil.vectorToString(bestCombinationOfFeatures);
        ui->FStextBrowserDatabaseInfo->append("Best features combination for SFS: ["  +  QString::fromStdString(bestCombinationOfFeaturesString) + "] : " + QString::number(bestFischerValue));
    }
}




void MainWindow::on_FSpushButtonSaveFile_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Open data file"), QDir::homePath(), tr("Texts files (*.txt)"));

    QMessageBox::information(this, "My file", fileName);
    database.save(fileName.toStdString());
}

void MainWindow::on_PpushButtonSelectFolder_clicked()
{
}

void MainWindow::on_CpushButtonOpenFile_clicked()
{
    OpenFile();
}

void MainWindow::on_CpushButtonSaveFile_clicked()
{

}

void MainWindow::on_CpushButtonTrain_clicked()
{
    bool isEnabled = false;
    int percentageTrainSetOfDataset = ui->CplainTextEditTrainingPart->toPlainText().toInt();

    if (percentageTrainSetOfDataset <= 0 || percentageTrainSetOfDataset >= 100)
    {
        QMessageBox::warning(this, "Warning", "Percentage value must be in range of 0 and 100");
        return;

    }
    int objectsAmount = database.getNoObjects();
    testObjectSetAmount = (int)round(((float)objectsAmount * ((float)percentageTrainSetOfDataset/100.0)));
    ui->CtextBrowser->append("Object amount: " + QString::number(objectsAmount) + " Test set amount: " + QString::number(testObjectSetAmount));
     isEnabled = true;

     ui->CpushButtonExecute->setEnabled(isEnabled);
}

void MainWindow::on_CpushButtonExecute_clicked()
{
    int k = ui->CcomboBoxK->currentText().toInt();

    int objectsCount = database.getNoObjects();
    int numberOfFeatures = database.getNoFeatures();
    vector<Object> all_obj = database.getObjects();
    vector<Object> objects_afterExtraction;
    vector<int> bestFeatures = bestFischerElement.getVectorOfFeatureCombinations();

    for(int i = 0; i < all_obj.size(); i++){
        vector<float> newVectorOfFeatures;
        vector<float> vectorOfFeatures = all_obj[i].getFeatures();
        for(int j=0; j<bestFeatures.size(); j++)
        {
            int featureID = bestFeatures.at(j);
            newVectorOfFeatures.push_back(vectorOfFeatures.at(featureID));
        }

         Object object_afterExtraction =  Object(all_obj[i].getClassName(), newVectorOfFeatures);
         objects_afterExtraction.push_back(object_afterExtraction);
    }

    random_shuffle(objects_afterExtraction.begin(), objects_afterExtraction.end());

    std::vector<Object>  classified(objects_afterExtraction.begin(), objects_afterExtraction.begin() + testObjectSetAmount);
    std::vector<Object>  trainingSet(objects_afterExtraction.begin()+ testObjectSetAmount, objects_afterExtraction.begin() + all_obj.size());
    std::map<string, vector<vector<float>>> classifiedObjects = converter.getObjectsMap(classified);

    clasiffier *clasifier = new clasiffier();
    double percentage = 0;
    if(ui->CcomboBoxClassifiers->currentText()== "NN"){
        ui->CtextBrowser->append("NN classifier choosen");
        percentage = clasifier->NearestNeighbour(classifiedObjects, trainingSet);

    }
    if(ui->CcomboBoxClassifiers->currentText()== "NM"){
        ui->CtextBrowser->append("NM classifier choosen");
        percentage = clasifier->NearestMean(classifiedObjects, trainingSet);
    }
    if(ui->CcomboBoxClassifiers->currentText()== "k-NN"){
        ui->CtextBrowser->append("k-NN classifier choosen");
        percentage = clasifier->kNearestNeighbour(classifiedObjects, trainingSet, k);
    }
    if(ui->CcomboBoxClassifiers->currentText()== "k-NM"){
        ui->CtextBrowser->append("k-NM classifier choosen");
        percentage = clasifier->kNearestMean(classifiedObjects, trainingSet, k);
    }

    ui->CtextBrowser->append("Elements good classified: "  +  QString::number(percentage) + "%");


}

bool MainWindow::OpenFile(){
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open data file"), "//", tr("Texts Files (*.txt)"));

    if ( !database.load(fileName.toStdString()) )
    {
        QMessageBox::warning(this, "Warning", "Cannot read file!!!");
        return false;
    }
    else
    {
        QMessageBox::information(this, fileName, "File loaded !!!");
        return true;
    }
}

void MainWindow::addClassfiers(){
    ui->CcomboBoxClassifiers->addItems(QStringList()<<"NN"<<"NM"<<"k-NN"<<"k-NM");
}

void MainWindow::addItemsToKComboBox(int k){
    QStringList itemsList = QStringList();
    for(int i =1; i<=k; i++)
        itemsList.append(QString::number(i));
    ui->CcomboBoxK->addItems(itemsList);
}









