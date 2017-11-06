#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include "iostream"
#include "combination.h"
#include "ficherelement.h"
#include <QImage>
#include <QDebug>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Projekt Statystyczne Metody Przetwarzania Danych");
    this->setWindowIcon(QIcon(":/icons/icon.png"));
    FSupdateButtonState();
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
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open TextFile"), "", tr("Texts Files (*.txt)"));

    if ( !database.load(fileName.toStdString()) )
        QMessageBox::warning(this, "Warning", "File corrupted !!!");
    else
        QMessageBox::information(this, fileName, "File loaded !!!");

    FSupdateButtonState();
    updateDatabaseInfo();
}

void MainWindow::on_FSpushButtonCompute_clicked()
{
    int dimension = ui->FScomboBox->currentText().toInt();
    int numberOfClass = database.getNoClass();
    int numberOfFeatures = database.getNoFeatures();

    Combinations* combinations = new Combinations();
    std::vector<std::vector<int>> arrayOfCombinations = combinations->generateCombinations(numberOfFeatures, dimension);
    delete combinations;
    //for developer tests
    printCombinations(arrayOfCombinations);

    std::map<int,FicherElement> combinationsMap;

    for (int i = 0; i < arrayOfCombinations.size(); i++)
    {
        FicherElement ficherElementToInsert = FicherElement(&arrayOfCombinations[i]);
        combinationsMap.insert(std::pair<int, FicherElement>(i, ficherElementToInsert));
    }

    if( ui->FSradioButtonFisher ->isChecked())
    {
        float minFischerValue = std::numeric_limits<float>::max();
        int minFischerMapKey = 0;

        //todo: przeiterować po kombinacjach i wyliczyć dla każdej combination fischerValue
        for (auto &combination : combinationsMap)
        {
            if (numberOfClass == 2)
            {
                float FLD = 0, tmp;
                int max_ind = -1;

                //std::map<std::string, int> classNames = database.getClassNames();
                const std::vector<int> *arrayFeatureOfCombinations = combination.second.getVectorOfFeatureCombinations();
                const int* singleCombinationArray = arrayFeatureOfCombinations->data();
                int singleCombinationArraySize = arrayFeatureOfCombinations->size();

                for (uint i = 0; i < singleCombinationArraySize; ++i)
                {
                    std::map<std::string, float> classAverages;
                    std::map<std::string, float> classStds;

                    int indexOfFeature = singleCombinationArray[i];
                    for (auto const &ob : database.getObjects())
                    {
                        classAverages[ob.getClassName()] += ob.getFeatures()[indexOfFeature];
                        classStds[ob.getClassName()] += ob.getFeatures()[indexOfFeature] * ob.getFeatures()[indexOfFeature];
                    }

                    std::for_each(database.getClassCounters().begin(), database.getClassCounters().end(), [&](const std::pair<std::string, int> &it)
                    {
                        classAverages[it.first] /= it.second;
                        classStds[it.first] = std::sqrt(classStds[it.first] / it.second - classAverages[it.first] * classAverages[it.first]);
                    });

                    tmp = std::abs(classAverages[ database.getClassNames()[0] ] - classAverages[database.getClassNames()[1]]) / (classStds[database.getClassNames()[0]] + classStds[database.getClassNames()[1]]);

                    if (tmp > FLD)
                    {
                        FLD = tmp;
                        max_ind = i;
                    }
                }

                ui->FStextBrowserDatabaseInfo->append("max_ind: "  +  QString::number(max_ind) + " " + QString::number(FLD));
            }
            float fischerValue = 0.0f;
            if(fischerValue < minFischerValue)
                minFischerValue = fischerValue;

            combination.second.setFischerValue(fischerValue);
        }
    }
}




void MainWindow::on_FSpushButtonSaveFile_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Open TextFile"), "D:\\Users\\Krzysiu\\Documents\\Visual Studio 2015\\Projects\\SMPD\\SMPD\\Debug\\", tr("Texts Files (*.txt)"));

    QMessageBox::information(this, "My File", fileName);
    database.save(fileName.toStdString());
}

void MainWindow::on_PpushButtonSelectFolder_clicked()
{
}

void MainWindow::on_CpushButtonOpenFile_clicked()
{

}

void MainWindow::on_CpushButtonSaveFile_clicked()
{

}

void MainWindow::on_CpushButtonTrain_clicked()
{

}

void MainWindow::on_CpushButtonExecute_clicked()
{

}

void MainWindow::printCombinations(std::vector<std::vector<int>> &arrayOfCombinations){
    int sizeOfCombinationsVectorsArray = arrayOfCombinations.size();
    for (int i = 0; i < sizeOfCombinationsVectorsArray; i++)
    {
        int vectorSize = arrayOfCombinations[i].size();
        for (int j = 0; j < vectorSize; j++)
        {
            std::cout << arrayOfCombinations.at(i).at(j);
            if(j < vectorSize - 1)
                std::cout << " ";
            else
                std::cout << ';' << endl;
        }

    }
}



