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

    map<int,FicherElement> combinationsMap = fischer.getCombinationsMap(numberOfFeatures, dimension);


    if( ui->FSradioButtonFisher ->isChecked())
    {
        float minFischerValue = std::numeric_limits<float>::max();
        int minFischerMapKey = 0;
        if (numberOfClass == 2)
        {

            vector<Object> all_obj = database.getObjects();
            vector<Object_model> objectModels = fischer.getObject_Models(all_obj);
            //todo: przeiterować po kombinacjach i wyliczyć dla każdej combination fischerValue
            for (auto &combination : combinationsMap)
            {
                //std::map<std::string, int> classNames = database.getClassNames();
                const std::vector<int> arrayFeatureOfCombinations = combination.second.getVectorOfFeatureCombinations();

                float Sm, Sw;

                //wpakować macierze rozrzutu i średnie do obiektu
                bnu::matrix<float> covarianceA;
                bnu::matrix<float> covariannceB;
                std::vector<float> meanA;
                std::vector<float> meanB;

                for (auto &feature : arrayFeatureOfCombinations)
                {
                    for (auto const &ob : objectModels)
                    {
                        int a =1;
                        a--;
                    }
                }

                float fischerValue = 0.0f;
                fischerValue = Sm/Sw;
                //ui->FStextBrowserDatabaseInfo->append("max_ind: "  +  QString::number(max_ind) + " " + QString::number(FLD));

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




