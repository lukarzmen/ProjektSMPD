#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include "iostream"
#include <QImage>
#include <QDebug>


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("SMPD Project by L. Medyk");
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
                                                    tr("Open data file"), "//", tr("Texts Files (*.txt)"));

    if ( !database.load(fileName.toStdString()) )
        QMessageBox::warning(this, "Warning", "Cannot read file!!!");
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

    map<int,FicherElement> combinationsMap = getCombinationsMap(numberOfFeatures, dimension);


    if( ui->FSradioButtonFisher ->isChecked())
    {
        float minFischerValue = std::numeric_limits<float>::max();
        int minFischerMapKey = 0;
        if (numberOfClass == 2)
        {

            vector<Object> all_obj = database.getObjects();
            vector<Object_model> objectModels = getObject_Models(all_obj);
            //todo: przeiterować po kombinacjach i wyliczyć dla każdej combination fischerValue
            for (auto &combination : combinationsMap)
            {
                //std::map<std::string, int> classNames = database.getClassNames();
                const std::vector<int> arrayFeatureOfCombinations = combination.second.getVectorOfFeatureCombinations();
                const int* singleCombinationArray = arrayFeatureOfCombinations.data();
                int singleCombinationArraySize = arrayFeatureOfCombinations.size();


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

                    //tmp = std::abs(classAverages[ database.getClassNames()[0] ] - classAverages[database.getClassNames()[1]]) / (classStds[database.getClassNames()[0]] + classStds[database.getClassNames()[1]]);

                }

                //ui->FStextBrowserDatabaseInfo->append("max_ind: "  +  QString::number(max_ind) + " " + QString::number(FLD));

                float fischerValue = 0.0f;
                if(fischerValue < minFischerValue)
                    minFischerValue = fischerValue;

                combination.second.setFischerValue(fischerValue);
            }
        }
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

map<int,FicherElement> MainWindow::getCombinationsMap(int numberOfFeatures, int dimension){
    Combinations* combinations = new Combinations();
    vector<vector<int>> arrayOfCombinations = combinations->generateCombinations(numberOfFeatures, dimension);
    delete combinations;
    //for developer tests
    printCombinations(arrayOfCombinations);

    map<int,FicherElement> combinationsMap;

    for (int i = 0; i < arrayOfCombinations.size(); i++)
    {
        FicherElement ficherElementToInsert = FicherElement(arrayOfCombinations[i]);
        combinationsMap.insert(pair<int, FicherElement>(i, ficherElementToInsert));
    }

    return combinationsMap;
}

vector<Object_model> MainWindow::getObject_Models(vector<Object> &databaseObjects){
    map<string, vector<vector<float>>> classesWithFeatures;

    for (uint i = 0; i < databaseObjects.size(); i++) {
        string classNameKey = databaseObjects[i].getClassName();
        vector<float> features = databaseObjects[i].getFeatures();

        map<string,vector<vector<float>>>::iterator mapIterator = classesWithFeatures.find(classNameKey);
        if(mapIterator == classesWithFeatures.end())
        {
            std::vector<std::vector<float>> newArrayOfFeatures;
            newArrayOfFeatures.push_back(features);
            pair<string, vector<vector<float>>> newMapElement = pair<string, vector<vector<float>>>(classNameKey, newArrayOfFeatures);
            classesWithFeatures.insert(newMapElement);
        }
        else
            mapIterator->second.push_back(features);
    }

    vector<Object_model> objects;
    foreach (auto &classWithFeatures, classesWithFeatures) {
        string className = classWithFeatures.first;
        vector<std::vector<float>> arrayOfFeatures = classWithFeatures.second;
        vector<float> featureAverages;
        vector<float> featureStds;

        float featuresSum = 0.0f;
        for (uint i = 0; i < arrayOfFeatures.size(); ++i){

            featuresSum = 0;
        }
        Object_model object_model = Object_model(className);
        object_model.setFeatures(arrayOfFeatures);
        objects.push_back(object_model);
    }

    return objects;
}



