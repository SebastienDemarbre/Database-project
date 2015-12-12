#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QTableWidgetItem>
#include <QDialog>
#include <QMessageBox>
#include <QDate>
#include <QDebug>
#include <QCheckBox>
#include <fstream>
#include <QFile>
#include <QTextStream>
#include <QTextEdit>
#include <iostream>

using namespace std;

#define q2c(string) string.toStdString()


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabaseName("test2");
    if(db.open())
    {

        QDate date;
        QMessageBox::about(this,"Connexion réussie","Connexion à la base de données réussie");
        ui->setupUi(this);
        this->setFixedSize(this->geometry().width(),this->geometry().height());
        ui->dateHome->setText(date.currentDate().toString(Qt::SystemLocaleLongDate));
        ui->Contact->hide();
        ui->Evenements->hide();
        ui->Projet->hide();
        ui->Commande->hide();
        ui->Deconnexion->hide();
        ui->Back->hide();
        //ui->pageLogin->hide();
        //ui->Back->hide();
        ui->SupprEmploy->hide();
        ui->modifEmploy->hide();
        ui->modifClient->hide();
        ui->SupprClient->hide();
        ui->modifFour->hide();
        ui->supprFour->hide();
        ui->modifProjet->hide();
        ui->supprProjet->hide();
        ui->ValiderProjet->hide();
        ui->validerChoixEmploy->hide();
        ui->deselectionChoixEmploy->hide();
        ui->supprEvent->hide();
        ui->ModifEvent->hide();
        ui->ValiderChoixEmployEvent->hide();
        ui->DeselectionEmployEvent->hide();
        ui->ValiderFourProd->hide();
        ui->DeselectFourProd->hide();
        ui->SelectionProduitAddCommande->hide();
        ui->DeselectionProduitAddCommande->hide();
        ui->SelectionProjetAddCommande->hide();
        ui->DeselectionProjetAddCommande->hide();
        ui->SupprCommande->hide();
        ui->supprProduit->hide();
        ui->okHeure->hide();


        actualiserClient();
        actualiser();
        actualiserFour();
        actualiserProjet();
        actualiserEvent();
        actualiserProduit();
        actualiserCommande();

    }
    else
    {
        QMessageBox::critical(this,"Connexion impossible","La connexion a échouée");

    }


}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Contact_clicked()
{
    ui->stackedWidget->setCurrentIndex(13);
    ui->Back->show();

}

void MainWindow::on_Projet_clicked()
{
    ui->Back->show();
    ui->stackedWidget->setCurrentIndex(8);
    actualiserProjet();
}


void MainWindow::on_Evenements_clicked()
{
    ui->Back->show();
    ui->stackedWidget->setCurrentIndex(22);
}

void MainWindow::on_Back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->frame->hide();
    ui->Back->hide();

}

void MainWindow::on_Add_clicked()
{
    if (ui->Client->isChecked())
        {
            ui->stackedWidget->setCurrentIndex(15);
        }
    if (ui->Four->isChecked())
        {
            ui->stackedWidget->setCurrentIndex(16);
        }
    if (ui->Employ->isChecked())
        {
            ui->stackedWidget->setCurrentIndex(14);

        }

}

void MainWindow::on_ValidClient_clicked()
{
    ui->stackedWidget->setCurrentIndex(13);

    QString nom,prenom,nomContact,prenomContact,email, tel,telContact,tva,rue,num,ville,code;

    ui->ajoutemploye->hide();
    ui->contact1->show();

    nom=ui->NomClient->text();
    prenom=ui->PrenomClient->text();
    tel=ui->TelClient->text();
    tva=ui->TVAClient->text();
    nomContact=ui->NomContactClient->text();
    prenomContact=ui->PrenomContactClient->text();
    email=ui->EmailContactClient->text();
    telContact=ui->TelContactClient->text();
    rue=ui->RueClient->text();
    num=ui->NumClient->text();
    ville=ui->VilleClient->text();
    code=ui->CodePostalClient->text();


    QSqlQuery query;
    QString idtmp;
    bool tmp=false;
    //db.transaction();
        if(query.exec("SELECT * FROM Adresse ")){
            while(query.next()){
                if(query.value(1).toString()==rue && query.value(2).toString()==num && query.value(3).toString()==code && query.value(4).toString()==ville){
                    tmp=true;
                }

            }
        }
        //db.commit();
    if(!tmp){
        query.exec("INSERT INTO Adresse (Rue,Numero,CodePostal,Ville) VALUES ('"+rue+"','"+num+"','"+code+"','"+ville+"')");
    }
    if(query.exec("SELECT idAdresse FROM Adresse WHERE Rue='"+rue+"' AND Numero='"+num+"' AND CodePostal='"+code+"' AND Ville='"+ville+"'")){
        while(query.next()){
            idtmp=query.value(0).toString();
        }
    }
    query.exec("INSERT INTO Client (Nom, Prenom, Telephone, TVA, NomContact, PrenomContact, EmailContact, TelephoneContact, idAdresse) VALUES ('"+nom+"', '"+prenom+"', '"+tel+"', '"+tva+"', '"+nomContact+"', '"+prenomContact+"', '"+email+"', '"+telContact+"','"+idtmp+"' )");
    actualiserClient();
}

void MainWindow::on_ValidCEmploy_clicked()
{
    QString prenom,nom,tel,email,fonc,anniv,salaire,rue,num,code,ville;

    ui->stackedWidget->setCurrentIndex(13);

    nom=ui->NomEpmloy->text();
    prenom=ui->PrenomEmploy->text();
    tel=ui->TelEmploy->text();
    email=ui->EmailEmploy->text();
    fonc=ui->FonctEmploy->text();
    anniv=ui->AnnivEmploy->text();
    salaire=ui->SalaireEmploy->text();
    rue=ui->RueEmploy->text();
    num=ui->NumEmploy->text();
    code=ui->CodePostalEmploy->text();
    ville=ui->VilleEmploy->text();

    QSqlQuery query;
    QString idtmp;
    bool tmp=false;
    if(query.exec("SELECT * FROM Adresse ")){
        while(query.next()){
            if(query.value(1).toString()==rue && query.value(2).toString()==num && query.value(3).toString()==code && query.value(4).toString()==ville){
                tmp=true;
            }

        }
    }
    if(!tmp){
        query.exec("INSERT INTO Adresse (Rue,Numero,CodePostal,Ville) VALUES ('"+rue+"','"+num+"','"+code+"','"+ville+"')");
    }
    if(query.exec("SELECT idAdresse FROM Adresse WHERE Rue='"+rue+"' AND Numero='"+num+"' AND CodePostal='"+code+"' AND Ville='"+ville+"'")){
        while(query.next()){
            idtmp=query.value(0).toString();
        }
    }
    query.exec("INSERT INTO Employe (Nom,Prenom,Telephone,Email,Fonction,Anniversaire,Salaire,idAdresse) VALUES ('"+nom+"','"+prenom+"','"+tel+"','"+email+"','"+fonc+"','"+anniv+"','"+salaire+"','"+idtmp+"')");


    QString idt;
    if(query.exec("SELECT * FROM Employe WHERE Nom='"+nom+"' AND Prenom='"+prenom+"'")){
        while(query.next()){
            idt=query.value(0).toString();
        }
    }


    std::ofstream ofs;
    QString mot,mot2,mot3,mot5;
    std::string mot4;

    mot=prenom;
    mot3=idt;

    mot2=mot+mot3;

    ofs.open ("C:/Users/Seb/Desktop/mdp.txt", std::ofstream::out | std::ofstream::app);
    mot5="\n"+mot+" "+mot2+" "+mot3;
    mot4=mot5.toStdString();

    ofs<<mot4;
    ofs.close();

    actualiser();


}


void MainWindow::on_ValidAjoutFour_clicked()
{
    ui->stackedWidget->setCurrentIndex(13);

    QString nom,nomContact,prenomContact,email, tel,telContact,tva,rue,num,ville,code;

    ui->ajoutemploye->hide();
    ui->contact1->show();

    nom=ui->NomFour->text();
    tel=ui->TelFour->text();
    tva=ui->TVAFour->text();
    nomContact=ui->NomContactFour->text();
    prenomContact=ui->PrenomContactFour->text();
    email=ui->EmailContactFour->text();
    telContact=ui->TelContactFour->text();
    rue=ui->RueFour->text();
    num=ui->NumFour->text();
    ville=ui->VilleFour->text();
    code=ui->CodePostalFour->text();

    QSqlQuery query;
    QString idtmp;
    bool tmp=false;
    if(query.exec("SELECT * FROM Adresse")){
        while(query.next()){
            if(query.value(1).toString()==rue && query.value(2).toString()==num && query.value(3).toString()==code && query.value(4).toString()==ville){
                tmp=true;
            }

        }
    }
    if(!tmp){
        query.exec("INSERT INTO Adresse (Rue,Numero,CodePostal,Ville) VALUES ('"+rue+"','"+num+"','"+code+"','"+ville+"')");
    }
    if(query.exec("SELECT idAdresse FROM Adresse WHERE Rue='"+rue+"' AND Numero='"+num+"' AND CodePostal='"+code+"' AND Ville='"+ville+"'")){
        while(query.next()){
            idtmp=query.value(0).toString();
        }
    }
    query.exec("INSERT INTO Fournisseur (Nom, Telephone, TVA, NomContact, PrenomContact, EmailContact, TelephoneContact, idAdresse) VALUES ('"+nom+"','"+tel+"', '"+tva+"', '"+nomContact+"', '"+prenomContact+"', '"+email+"', '"+telContact+"','"+idtmp+"' )");

    actualiserFour();
}

void MainWindow::on_TimeSheet_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
    ui->okHeure->hide();

    QSqlQuery query;
    while(ui->tableTimesheet->rowCount()>0){
        ui->tableTimesheet->removeRow(0);
    }
    if(query.exec("SELECT * FROM Projet INNER JOIN (Travailler INNER JOIN Employe ON Travailler.Employe_idEmploye=Employe.idEmploye)ON Projet.idProjet=Travailler.Projet_idProjet"))
    {
        ui->tableTimesheet->setRowCount((query.size()));
        int i=0;

        while(query.next())
           {
            QTableWidgetItem *newItem= new QTableWidgetItem ();
            newItem->setText(query.value(1).toString());
            QTableWidgetItem *newItem2= new QTableWidgetItem ();
            newItem2->setText(query.value(0).toString());
            ui->tableTimesheet->setItem(i,0,newItem);
            ui->tableTimesheet->setItem(i,1,newItem2);
            i++;


           }
    }else{
        QMessageBox::warning(this,"Opération impossible","Requête impossible");
    }

}

void MainWindow::on_Consult_clicked()
{
    if (ui->Client->isChecked())
        {
            ui->stackedWidget->setCurrentIndex(4);
        }
    if (ui->Four->isChecked())
        {
            ui->stackedWidget->setCurrentIndex(5);
        }
    if (ui->Employ->isChecked())
        {
            ui->stackedWidget->setCurrentIndex(1);
        }



}


void MainWindow::on_tableEmploy_cellClicked(int row, int column)
{
   QString nom,prenom,id;
   QSqlQuery query;
   ui->SupprEmploy->show();
   ui->modifEmploy->show();
    nom=ui->tableEmploy->item(row,0)->text();
    prenom=ui->tableEmploy->item(row,1)->text();
    id=ui->tableEmploy->item(row,2)->text();
    if(query.exec("SELECT * FROM Employe WHERE idEmploye='"+id+"'"))
    {

        while(query.next()){
            ui->NomEpmloy_3->setText(query.value(1).toString());
            ui->PrenomEmploy_3->setText(query.value(2).toString());
            ui->TelEmploy_3->setText(query.value(4).toString());
            ui->EmailEmploy_3->setText(query.value(5).toString());
            ui->FonctEmploy_3->setText(query.value(3).toString());
            ui->AnnivEmploy_3->setText(query.value(6).toString());
            ui->SalaireEmploy_3->setText(query.value(7).toString());

        }

    }else{
        QMessageBox::warning(this,"Opération impossible","Requête impossible");
    }
    if(query.exec("SELECT * FROM Adresse WHERE idAdresse=(SELECT idAdresse FROM Employe WHERE idEmploye='"+id+"')"))
    {
        while(query.next()){
            ui->VilleEmploy_3->setText(query.value(4).toString());
            ui->RueEmploy_3->setText(query.value(1).toString());
            ui->NumEmploy_3->setText(query.value(2).toString());
            ui->CodePostalEmploy_3->setText(query.value(3).toString());

        }

    }else{
        QMessageBox::warning(this,"Opération impossible","Requête impossible");
    }
}

void MainWindow::on_SupprEmploy_clicked()
{
    QSqlQuery query;
    QString id;
    id=ui->tableEmploy->item(ui->tableEmploy->currentRow(),2)->text();

    query.exec("DELETE FROM Event_has_employe WHERE Employe_idEmploye='"+id+"'");
    query.exec("DELETE FROM Travailler WHERE Employe_idEmploye='"+id+"'");
    query.exec("DELETE FROM Employe_has_commande WHERE Employe_idEmploye='"+id+"'");
    query.exec("DELETE FROM Employe WHERE idEmploye='"+id+"'");

    actualiser();

}



void MainWindow::actualiser()
{
    QSqlQuery query;
    while(ui->tableEmploy->rowCount()>0){
        ui->tableEmploy->removeRow(0);
    }
    if(query.exec("SELECT * FROM Employe"))
    {
        ui->tableEmploy->setRowCount(query.size());
        int i=0;

        while(query.next())
           {
            QTableWidgetItem *newItem= new QTableWidgetItem ();
            newItem->setText(query.value(1).toString());
            QTableWidgetItem *newItem2= new QTableWidgetItem ();
            newItem2->setText(query.value(2).toString());
            ui->tableEmploy->setItem(i,0,newItem);
            ui->tableEmploy->setItem(i,1,newItem2);
            QTableWidgetItem *newItem3= new QTableWidgetItem ();
            newItem3->setText(query.value(0).toString());
            ui->tableEmploy->setItem(i,2,newItem3);
            i++;


           }
    }else{
        QMessageBox::warning(this,"Opération impossible","Requête impossible");
    }


}

void MainWindow::actualiserClient(){
    QSqlQuery query;
    while(ui->tableClient->rowCount()>0){
        ui->tableClient->removeRow(0);
    }
    if(query.exec("SELECT * FROM Client"))
    {
        ui->tableClient->setRowCount(query.size());
        int i=0;
        while(query.next())
           {
            QTableWidgetItem *newItem= new QTableWidgetItem ();
            newItem->setText(query.value(1).toString());
            QTableWidgetItem *newItem2= new QTableWidgetItem ();
            newItem2->setText(query.value(2).toString());
            ui->tableClient->setItem(i,0,newItem);
            ui->tableClient->setItem(i,1,newItem2);
            QTableWidgetItem *newItem3= new QTableWidgetItem ();
            newItem3->setText(query.value(0).toString());
            ui->tableClient->setItem(i,2,newItem3);
            i++;


           }
    }else{
        QMessageBox::warning(this,"Opération impossible","Requête impossible");
    }
}

void MainWindow::actualiserFour(){
    QSqlQuery query;
    while(ui->tableFour->rowCount()>0){
        ui->tableFour->removeRow(0);
    }
    if(query.exec("SELECT * FROM Fournisseur"))
    {
        ui->tableFour->setRowCount(query.size());
        int i=0;
        while(query.next())
           {
            QTableWidgetItem *newItem= new QTableWidgetItem ();
            newItem->setText(query.value(1).toString());
            QTableWidgetItem *newItem2= new QTableWidgetItem ();
            newItem2->setText(query.value(0).toString());
            ui->tableFour->setItem(i,0,newItem);
            ui->tableFour->setItem(i,1,newItem2);
            i++;


           }
    }else{
        QMessageBox::warning(this,"Opération impossible","Requête impossible");
    }
}

void MainWindow::actualiserProjet(){
    QSqlQuery query;
    while(ui->tableProjet->rowCount()>0){
        ui->tableProjet->removeRow(0);
    }
    if(query.exec("SELECT * FROM Projet"))
    {
        ui->tableProjet->setRowCount(query.size());
        int i=0;

        while(query.next())
           {
            QTableWidgetItem *newItem= new QTableWidgetItem ();
            newItem->setText(query.value(1).toString());
            QTableWidgetItem *newItem2= new QTableWidgetItem ();
            newItem2->setText(query.value(0).toString());
            QTableWidgetItem *newItem3= new QTableWidgetItem ();
            newItem3->setText(query.value(2).toString());
            ui->tableProjet->setItem(i,2,newItem3);
            ui->tableProjet->setItem(i,0,newItem);
            ui->tableProjet->setItem(i,1,newItem2);
            i++;


           }

    }else{
        QMessageBox::warning(this,"Opération impossible","Requête impossible");
    }
}

void MainWindow::actualiserEvent()
{
    int year,month,day;
    QDateTime Dt;
    QDate D;

     year =ui->calendEvent->selectedDate().year();
     month=ui->calendEvent->selectedDate().month();
     day=ui->calendEvent->selectedDate().day();
     D.setDate(year,month,day);
     Dt.setDate(D);

     QString tmp=D.toString("yyyy-MM-dd");


     QSqlQuery query;
         while(ui->tableEvent->rowCount()>0){
             ui->tableEvent->removeRow(0);
         }
         if(query.exec("SELECT * FROM Event WHERE Date>='"+tmp+" 00:00:00' AND Date<='"+tmp+" 24:00:00'")==true){
             ui->tableEvent->setRowCount(query.size());
             int i=0;
             while(query.next())
                {
                 QTableWidgetItem *newItem= new QTableWidgetItem ();
                 newItem->setText(query.value(0).toString());

                 QTableWidgetItem *newItem2= new QTableWidgetItem ();
                 newItem2->setText(query.value(1).toString());

                 QTableWidgetItem *newItem3= new QTableWidgetItem ();
                 newItem3->setText(query.value(2).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                 ui->tableEvent->setItem(i,2,newItem);
                 ui->tableEvent->setItem(i,0,newItem2);
                 ui->tableEvent->setItem(i,1,newItem3);

                 i++;


                }
         }else{
             QMessageBox::warning(this,"Opération impossible","Requête impossible : "+query.lastError().text());
         }


}

void MainWindow::actualiserProduit(){
    QSqlQuery query;
    while(ui->tableProduit->rowCount()>0){
        ui->tableProduit->removeRow(0);
    }
    if(query.exec("SELECT * FROM Produit"))
    {
        ui->tableProduit->setRowCount(query.size());
        int i=0;
        while(query.next())
           {
            QTableWidgetItem *newItem= new QTableWidgetItem ();
            newItem->setText(query.value(0).toString());
            QTableWidgetItem *newItem2= new QTableWidgetItem ();
            newItem2->setText(query.value(1).toString());
            ui->tableProduit->setItem(i,1,newItem);
            ui->tableProduit->setItem(i,0,newItem2);
            i++;


           }
    }else{
        QMessageBox::warning(this,"Opération impossible","Requête impossible");
    }
}

void MainWindow::actualiserCommande(){
    QSqlQuery query;
    while(ui->tableCommande->rowCount()>0){
        ui->tableCommande->removeRow(0);
    }
    if(query.exec("SELECT * FROM Commande"))
    {
        ui->tableCommande->setRowCount(query.size());
        int i=0;
        while(query.next())
           {
            QTableWidgetItem *newItem= new QTableWidgetItem ();
            newItem->setText(query.value(0).toString());
            QTableWidgetItem *newItem2= new QTableWidgetItem ();
            newItem2->setText(query.value(1).toString());
            ui->tableCommande->setItem(i,0,newItem);
            ui->tableCommande->setItem(i,1,newItem2);
            i++;


           }
    }else{
        QMessageBox::warning(this,"Opération impossible","Requête impossible");
    }
}


void MainWindow::on_modifEmploy_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

    ui->NomEpmloy_4->setText(ui->NomEpmloy_3->text());
    ui->PrenomEmploy_4->setText(ui->PrenomEmploy_3->text());
    ui->EmailEmploy_4->setText(ui->EmailEmploy_3->text());
    ui->TelEmploy_4->setText(ui->TelEmploy_3->text());
    ui->SalaireEmploy_4->setText(ui->SalaireEmploy_3->text());
    ui->FonctEmploy_4->setText(ui->FonctEmploy_3->text());
    ui->AnnivEmploy_4->setText(ui->AnnivEmploy_3->text());
    ui->RueEmploy_4->setText(ui->RueEmploy_3->text());
    ui->NumEmploy_4->setText(ui->NumEmploy_3->text());
    ui->VilleEmploy_4->setText(ui->VilleEmploy_3->text());
    ui->CodePostalEmploy_4->setText(ui->CodePostalEmploy_3->text());


}


void MainWindow::on_validerModif_clicked()
{
    QString nom,prenom,email, tel,salaire,fonc,anniv,rue,num,ville,code, id, lastid,lastidEmploye;
    bool trouve=false;
    id=ui->tableEmploy->item(ui->tableEmploy->currentRow(),2)->text();
    nom=ui->NomEpmloy_4->text();
    prenom=ui->PrenomEmploy_4->text();
    email=ui->EmailEmploy_4->text();
    tel=ui->TelEmploy_4->text();
    salaire=ui->SalaireEmploy_4->text();
    fonc=ui->FonctEmploy_4->text();
    anniv=ui->AnnivEmploy_4->text();
    rue=ui->RueEmploy_4->text();
    num=ui->NumEmploy_4->text();
    ville=ui->VilleEmploy_4->text();
    code=ui->CodePostalEmploy_4->text();

     //Créer une adresse pour générer idadresse puis l'associer a l'employe modifie, supprimer l'ancienne adresse si elle n'et associée a personne
    QSqlQuery query;
    query.exec("INSERT INTO Adresse (Rue,Numero,Ville,CodePostal) VALUES ('"+rue+"','"+num+"','"+ville+"','"+code+"')");
    if(query.exec("SELECT idAdresse FROM Adresse WHERE Rue='"+rue+"' AND Numero='"+num+"' AND Ville='"+ville+"' AND CodePostal='"+code+"' ")){
        while(query.next()){
            lastid=query.value(0).toString();
        }
    }
    query.exec("UPDATE Employe SET Nom='"+nom+"', Prenom='"+prenom+"', Telephone='"+tel+"', Email='"+email+"', Salaire='"+salaire+"', Fonction='"+fonc+"', Anniversaire='"+anniv+"' WHERE idEmploye='"+id+"'");
    if(query.exec("SELECT idAdresse FROM  Employe WHERE idEmploye='"+id+"'")){
        while(query.next()){
            lastidEmploye=query.value(0).toString();
        }
    }
    query.exec("UPDATE Employe  SET idAdresse='"+lastid+"' WHERE idEmploye='"+id+"'");
    if(query.exec("SELECT idAdresse FROM Employe")){
        trouve=false;
        while(query.next()){
            if(lastidEmploye==query.value(0).toString()){
                trouve=true;
            }
        }
    }
    if(!trouve){
        query.exec(("DELETE FROM Adresse WHERE idAdresse='"+lastidEmploye+"' "));
    }
    actualiser();

    ui->stackedWidget->setCurrentIndex(1);

}


void MainWindow::on_tableClient_cellClicked(int row, int column)
{
    QString nom,prenom,id;
    QSqlQuery query;
    ui->SupprClient->show();
    ui->modifClient->show();
     nom=ui->tableClient->item(row,0)->text();
     prenom=ui->tableClient->item(row,1)->text();
     id=ui->tableClient->item(row,2)->text();
     if(query.exec("SELECT * FROM Client WHERE idClient='"+id+"'"))
     {

         while(query.next()){
             ui->NomClient_2->setText(query.value(1).toString());
             ui->PrenomClient_2->setText(query.value(2).toString());
             ui->TelClient_2->setText(query.value(3).toString());
             ui->TVAClient_2->setText(query.value(4).toString());
             ui->NomContactClient_2->setText(query.value(5).toString());
             ui->PrenomContactClient_2->setText(query.value(6).toString());
             ui->EmailContactClient_2->setText(query.value(7).toString());
             ui->TelContactClient_2->setText(query.value(8).toString());

         }

     }else{
         QMessageBox::warning(this,"Opération impossible","Requête impossible");
     }
     if(query.exec("SELECT * FROM Adresse WHERE idAdresse=(SELECT idAdresse FROM Client WHERE idClient='"+id+"')"))
     {
         while(query.next()){
             ui->VilleClient_2->setText(query.value(4).toString());
             ui->RueClient_2->setText(query.value(1).toString());
             ui->NumClient_2->setText(query.value(2).toString());
             ui->CodePostalClient_2->setText(query.value(3).toString());

         }

     }else{
         QMessageBox::warning(this,"Opération impossible","Requête impossible");
     }
}


void MainWindow::on_SupprClient_clicked()
{
    QSqlQuery query;
    QString id;
    id=ui->tableClient->item(ui->tableClient->currentRow(),2)->text();
    query.exec("DELETE FROM Commander WHERE Client_idClient='"+id+"'");
    query.exec("DELETE FROM Client WHERE idClient='"+id+"'");
    actualiserClient();
}


void MainWindow::on_modifClient_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);

    ui->NomClient_5->setText(ui->NomClient_2->text());
    ui->PrenomClient_4->setText(ui->PrenomClient_2->text());
    ui->TelClient_5->setText(ui->TelClient_2->text());
    ui->TVAClient_5->setText(ui->TVAClient_2->text());
    ui->NomContactClient_5->setText(ui->NomContactClient_2->text());
    ui->PrenomContactClient_4->setText(ui->PrenomContactClient_2->text());
    ui->TelContactClient_5->setText(ui->TelContactClient_2->text());
    ui->EmailContactClient_5->setText(ui->EmailContactClient_2->text());
    ui->RueClient_5->setText(ui->RueClient_2->text());
    ui->NumClient_5->setText(ui->NumClient_2->text());
    ui->VilleClient_5->setText(ui->VilleClient_2->text());
    ui->CodePostalClient_5->setText(ui->CodePostalClient_2->text());
}


void MainWindow::on_validerModifClient_clicked()
{
    QString nom,prenom,nomContact,PrenomContact,email, tel,telContact,tva,rue,num,ville,code, id, lastid,lastidClient;
    bool trouve=false;
    id=ui->tableClient->item(ui->tableClient->currentRow(),2)->text();
    nom=ui->NomClient_5->text();
    prenom=ui->PrenomClient_4->text();
    email=ui->EmailContactClient_5->text();
    tel=ui->TelClient_5->text();
    tva=ui->TVAClient_5->text();
    nomContact=ui->NomContactClient_5->text();
    PrenomContact=ui->PrenomContactClient_4->text();
    telContact=ui->TelContactClient_5->text();
    rue=ui->RueClient_5->text();
    num=ui->NumClient_5->text();
    ville=ui->VilleClient_5->text();
    code=ui->CodePostalClient_5->text();

     //Créer une adresse pour générer idadresse puis l'associer a l'employe modifie, supprimer l'ancienne adresse si elle n'et associée a personne
    QSqlQuery query;
    query.exec("INSERT INTO Adresse (Rue,Numero,Ville,CodePostal) VALUES ('"+rue+"','"+num+"','"+ville+"','"+code+"')");
    if(query.exec("SELECT idAdresse FROM Adresse WHERE Rue='"+rue+"' AND Numero='"+num+"' AND Ville='"+ville+"' AND CodePostal='"+code+"' ")){
        while(query.next()){
            lastid=query.value(0).toString();
        }
    }
    query.exec("UPDATE Client SET Nom='"+nom+"', Prenom='"+prenom+"', Telephone='"+tel+"', EmailContact='"+email+"', TVA='"+tva+"', NomContact='"+nomContact+"', PrenomContact='"+PrenomContact+"', TelephoneContact='"+telContact+"' WHERE idClient='"+id+"'");
    if(query.exec("SELECT idAdresse FROM  Client WHERE idClient='"+id+"'")){
        while(query.next()){
            lastidClient=query.value(0).toString();
        }
    }
    query.exec("UPDATE Client  SET idAdresse='"+lastid+"' WHERE idClient='"+id+"'");
    if(query.exec("SELECT idAdresse FROM Client")){
        trouve=false;
        while(query.next()){
            if(lastidClient==query.value(0).toString()){
                trouve=true;
            }
        }
    }
    if(!trouve){
        query.exec(("DELETE FROM Adresse WHERE idAdresse='"+lastidClient+"' "));
    }
    actualiserClient();
	
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_tableFour_cellClicked(int row, int column)
{
    QString nom,id;
    QSqlQuery query;
    ui->modifFour->show();
    ui->supprFour->show();
    nom=ui->tableFour->item(row,0)->text();
    id=ui->tableFour->item(row,1)->text();
    if(query.exec("SELECT * FROM Fournisseur WHERE idFournisseur='"+id+"'"))
    {

        while(query.next()){
            ui->NomFour_2->setText(query.value(1).toString());
            ui->TelFour_2->setText(query.value(2).toString());
            ui->TVAFour_2->setText(query.value(3).toString());
            ui->NomContactFour_2->setText(query.value(4).toString());
            ui->PrenomContactFour_2->setText(query.value(5).toString());
            ui->TelContactFour_2->setText(query.value(6).toString());
            ui->EmailContactFour_2->setText(query.value(7).toString());


        }

    }else{
        QMessageBox::warning(this,"Opération impossible","Requête impossible");
    }
    if(query.exec("SELECT * FROM Adresse WHERE idAdresse=(SELECT idAdresse FROM Fournisseur WHERE idFournisseur='"+id+"')"))
    {
        while(query.next()){
            ui->VilleFour_2->setText(query.value(4).toString());
            ui->RueFour_2->setText(query.value(1).toString());
            ui->NumFour_2->setText(query.value(2).toString());
            ui->CodePostalFour_2->setText(query.value(3).toString());

        }

    }else{
        QMessageBox::warning(this,"Opération impossible","Requête impossible");
    }
}


void MainWindow::on_supprFour_clicked()
{
    QSqlQuery query;
    QString id;
    id=ui->tableFour->item(ui->tableFour->currentRow(),1)->text();
    query.exec("DELETE FROM Produit_has_fournisseur WHERE Fournisseur_idFournisseur='"+id+"'");
    query.exec("DELETE FROM Fournisseur WHERE idFournisseur='"+id+"'");
    actualiserFour();
}


void MainWindow::on_modifFour_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);

    ui->NomFour_3->setText(ui->NomFour_2->text());
    ui->TelFour_3->setText(ui->TelFour_2->text());
    ui->TVAFour_3->setText(ui->TVAFour_2->text());
    ui->NomContactFour_3->setText(ui->NomContactFour_2->text());
    ui->PrenomContactFour_3->setText(ui->PrenomContactFour_2->text());
    ui->TelContactFour_3->setText(ui->TelContactFour_2->text());
    ui->EmailContactFour_3->setText(ui->EmailContactFour_2->text());
    ui->RueFour_3->setText(ui->RueFour_2->text());
    ui->NumFour_3->setText(ui->NumFour_2->text());
    ui->VilleFour_3->setText(ui->VilleFour_2->text());
    ui->CodePostalFour_3->setText(ui->CodePostalFour_2->text());
}


void MainWindow::on_ValiderFour_clicked()
{
    QString nom,nomContact,PrenomContact,email, tel,telContact,tva,rue,num,ville,code, id, lastid,lastidFour;
    bool trouve=false;
    id=ui->tableFour->item(ui->tableFour->currentRow(),1)->text();
    nom=ui->NomFour_3->text();
    email=ui->EmailContactFour_3->text();
    tel=ui->TelFour_3->text();
    tva=ui->TVAFour_3->text();
    nomContact=ui->NomContactFour_3->text();
    PrenomContact=ui->PrenomContactFour_3->text();
    telContact=ui->TelContactFour_3->text();
    rue=ui->RueFour_3->text();
    num=ui->NumFour_3->text();
    ville=ui->VilleFour_3->text();
    code=ui->CodePostalFour_3->text();

     //Créer une adresse pour générer idadresse puis l'associer a l'employe modifie, supprimer l'ancienne adresse si elle n'et associée a personne
    QSqlQuery query;
    query.exec("INSERT INTO Adresse (Rue,Numero,Ville,CodePostal) VALUES ('"+rue+"','"+num+"','"+ville+"','"+code+"')");
    if(query.exec("SELECT idAdresse FROM Adresse WHERE Rue='"+rue+"' AND Numero='"+num+"' AND Ville='"+ville+"' AND CodePostal='"+code+"' ")){
        while(query.next()){
            lastid=query.value(0).toString();
        }
    }
    query.exec("UPDATE Fournisseur SET Nom='"+nom+"', Telephone='"+tel+"', EmailContact='"+email+"', TVA='"+tva+"', NomContact='"+nomContact+"', PrenomContact='"+PrenomContact+"', TelephoneContact='"+telContact+"' WHERE idFournisseur='"+id+"'");
    if(query.exec("SELECT idAdresse FROM  Fournisseur WHERE idFournisseur='"+id+"'")){
        while(query.next()){
            lastidFour=query.value(0).toString();
        }
    }
    query.exec("UPDATE Fournisseur  SET idAdresse='"+lastid+"' WHERE idFournisseur='"+id+"'");
    if(query.exec("SELECT idAdresse FROM Fournisseur")){
        trouve=false;
        while(query.next()){
            if(lastidFour==query.value(0).toString()){
                trouve=true;
            }
        }
    }
    if(!trouve){
        query.exec(("DELETE FROM Adresse WHERE idAdresse='"+lastidFour+"' "));
    }
    actualiserFour();
    ui->stackedWidget->setCurrentIndex(5);
}




void MainWindow::on_supprProjet_clicked()
{
    QSqlQuery query;
    QString id,stat;
    id=ui->tableProjet->item(ui->tableProjet->currentRow(),1)->text();
    if(query.exec("SELECT Statut FROM Projet WHERE idProjet='"+id+"'")){
        while(query.next()){
            stat=query.value(0).toString();
        }
    }
    if(stat=="5" || stat=="6" || stat=="7"){
        query.exec("DELETE FROM Commander WHERE Projet_idProjet='"+id+"'");
        query.exec(("DELETE FROM Travailler WHERE Projet_idProjet='"+id+"'"));
        query.exec(("DELETE FROM Employe_has_commande WHERE Projet_idProjet='"+id+"'"));
        query.exec("DELETE FROM Projet WHERE idProjet='"+id+"'");
        actualiserProjet();
    }else{
        QMessageBox::warning(this,"Suppression impossible","Suppression impossible");
    }
}


void MainWindow::on_tableProjet_cellClicked(int row, int column)
{
    ui->modifProjet->show();
    ui->supprProjet->show();

    QString id;
    QSqlQuery query;

    id=ui->tableProjet->item(row,1)->text();
    if(query.exec("SELECT * FROM Projet WHERE idProjet='"+id+"'"))
    {

        while(query.next()){
            ui->NomProjet->setText(query.value(1).toString());
            ui->EtatProjet->setText(query.value(2).toString());
            ui->CategProjet->setText(query.value(3).toString());
            ui->StartProjet->setText(query.value(4).toString());
            ui->DeadProjet->setText(query.value(5).toString());
        }

    }else{

    }
    if(query.exec("SELECT Client.Nom FROM Client INNER JOIN(Commander INNER JOIN Projet ON Commander.Projet_idProjet='"+ui->tableProjet->item(row,1)->text()+"') ON Client.idClient=Commander.Client_idClient "))
    {

        while(query.next()){
            ui->ClientProjet->setText(query.value(0).toString());
        }

    }else{
        QMessageBox::warning(this,"Opération impossible","Requête impossible");
    }


}


void MainWindow::on_modifProjet_clicked()
{
    ui->stackedWidget->setCurrentIndex(12);
    ui->NomProjet_2->setText(ui->NomProjet->text());
    ui->CategProjet_2->setText(ui->CategProjet->text());
    ui->EtatProjet_2->setText(ui->EtatProjet->text());
    ui->ClientProjet_2->setText(ui->ClientProjet->text());
    ui->StartProjet_2->setText(ui->StartProjet->text());
    ui->DeadProjet_2->setText(ui->DeadProjet->text());

}


void MainWindow::on_ValiderProjet_clicked()
{
    QString id,nom,categ,etat,client,start,dead,idClient;

    id=ui->tableProjet->item(ui->tableProjet->currentRow(),1)->text();
    nom=ui->NomProjet_2->text();
    categ=ui->CategProjet_2->text();
    etat=ui->EtatProjet_2->text();
    client=ui->ClientProjet_2->text();
    start=ui->StartProjet_2->text();
    dead=ui->DeadProjet_2->text();
    idClient=ui->tableClientProjet->item(ui->tableClientProjet->currentRow(),1)->text();

    QSqlQuery query;
    query.exec("UPDATE Projet SET Nom='"+nom+"', Statut='"+etat+"', Categorie='"+categ+"', StartLine='"+start+"', DeadLine='"+dead+"' WHERE idProjet='"+id+"'");
    query.exec("UPDATE Commander SET Client_idClient='"+idClient+"' WHERE Projet_idProjet='"+id+"'");
    actualiserProjet();

    ui->stackedWidget->setCurrentIndex(8);
}


void MainWindow::on_tableClientProjet_cellClicked(int row, int column)
{
    ui->ValiderProjet->show();
    if(ui->tableClientProjet->item(row,0)!=NULL){
        ui->ClientProjet_2->setText(ui->tableClientProjet->item(row,0)->text());
    }else{
        ui->ClientProjet_2->setText("");
    }

}


void MainWindow::on_SearchClient_clicked()
{
    QSqlQuery query;
    QString tmp;
    ui->ValiderProjet->hide();
    tmp=ui->ClientProjet_2->text();
    while(ui->tableClientProjet->rowCount()>0){
        ui->tableClientProjet->removeRow(0);
    }
    if(query.exec("SELECT * FROM Client WHERE Nom LIKE '"+tmp+"%'"))
    {
        ui->tableClientProjet->setRowCount(query.size());
        int i=0;
        while(query.next())
           {
                QTableWidgetItem *newItem= new QTableWidgetItem ();
                newItem->setText(query.value(0).toString());
                QTableWidgetItem *newItem2= new QTableWidgetItem ();
                newItem2->setText(query.value(1).toString());
                ui->tableClientProjet->setItem(i,1,newItem);
                ui->tableClientProjet->setItem(i,0,newItem2);
                QTableWidgetItem *newItem3= new QTableWidgetItem ();
                newItem3->setText(query.value(5).toString());
                ui->tableClientProjet->setItem(i,2,newItem3);

                i++;


           }

    }else{
        QMessageBox::warning(this,"Opération impossible","Requête impossible");
    }
}


void MainWindow::on_NextAjout1_clicked()
{
    QString nom,etat,categorie,start,end;


   nom=ui->NomProjet_3->text();
   etat=ui->EtatProjet_3->text();
   categorie=ui->CategProjet_3->text();
   start=ui->StartProjet_3->date().toString("yyyy-MM-dd");
   end=ui->DeadProjet_3->date().toString("yyyy-MM-dd");

    QSqlQuery query;
    query.exec("INSERT INTO Projet (Nom,Statut,Categorie,StartLine,DeadLine) VALUES ('"+nom+"','"+etat+"','"+categorie+"','"+start+"','"+end+"')");

    actualiserProjet();

    while(ui->tableEmployProjet->rowCount()>0){
        ui->tableEmployProjet->removeRow(0);
    }
    if(query.exec("SELECT * FROM Employe"))
    {
        ui->tableEmployProjet->setRowCount(query.size());
        int i=0;

        while(query.next())
           {
            QTableWidgetItem *newItem= new QTableWidgetItem ();
            newItem->setText(query.value(0).toString());
            QTableWidgetItem *newItem2= new QTableWidgetItem ();
            newItem2->setText(query.value(1).toString());
            ui->tableEmployProjet->setItem(i,0,newItem);
            ui->tableEmployProjet->setItem(i,1,newItem2);
            QTableWidgetItem *newItem3= new QTableWidgetItem ();
            newItem3->setText(query.value(2).toString());
            ui->tableEmployProjet->setItem(i,2,newItem3);
            QTableWidgetItem *newItem4= new QTableWidgetItem ();
            newItem4->setText("Non");
            ui->tableEmployProjet->setItem(i,3,newItem4);
            i++;


           }
    }else{
        QMessageBox::warning(this,"Opération impossible","Requête impossible");
    }

    ui->stackedWidget->setCurrentIndex(10);
}


void MainWindow::on_AjoutProjet_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}


void MainWindow::on_tableEmployProjet_cellClicked(int row, int column)
{
    ui->validerChoixEmploy->show();
    ui->deselectionChoixEmploy->show();
}


void MainWindow::on_validerChoixEmploy_clicked()
{
    QColor color(4,174,218,255);
    QColor color2(255,255,255,255);
    ui->tableEmployProjet->item(ui->tableEmployProjet->currentRow(),3)->setText("Oui");
    ui->tableEmployProjet->item(ui->tableEmployProjet->currentRow(),0)->setBackgroundColor(color);
    ui->tableEmployProjet->item(ui->tableEmployProjet->currentRow(),1)->setBackgroundColor(color);
    ui->tableEmployProjet->item(ui->tableEmployProjet->currentRow(),2)->setBackgroundColor(color);
    ui->tableEmployProjet->item(ui->tableEmployProjet->currentRow(),3)->setBackgroundColor(color);
    ui->tableEmployProjet->item(ui->tableEmployProjet->currentRow(),0)->setTextColor(color2);
    ui->tableEmployProjet->item(ui->tableEmployProjet->currentRow(),1)->setTextColor(color2);
    ui->tableEmployProjet->item(ui->tableEmployProjet->currentRow(),2)->setTextColor(color2);
    ui->tableEmployProjet->item(ui->tableEmployProjet->currentRow(),3)->setTextColor(color2);

}


void MainWindow::on_deselectionChoixEmploy_clicked()
{
    QColor color(255,255,255,255);
    QColor color2(0,0,0,255);
    ui->tableEmployProjet->item(ui->tableEmployProjet->currentRow(),3)->setText("Non");
    ui->tableEmployProjet->item(ui->tableEmployProjet->currentRow(),0)->setBackgroundColor(color);
    ui->tableEmployProjet->item(ui->tableEmployProjet->currentRow(),1)->setBackgroundColor(color);
    ui->tableEmployProjet->item(ui->tableEmployProjet->currentRow(),2)->setBackgroundColor(color);
    ui->tableEmployProjet->item(ui->tableEmployProjet->currentRow(),3)->setBackgroundColor(color);
    ui->tableEmployProjet->item(ui->tableEmployProjet->currentRow(),0)->setTextColor(color2);
    ui->tableEmployProjet->item(ui->tableEmployProjet->currentRow(),1)->setTextColor(color2);
    ui->tableEmployProjet->item(ui->tableEmployProjet->currentRow(),2)->setTextColor(color2);
    ui->tableEmployProjet->item(ui->tableEmployProjet->currentRow(),3)->setTextColor(color2);
}





void MainWindow::on_tableEvent_cellClicked(int row, int column)
{
     QString id;
     QSqlQuery query;

     ui->supprEvent->show();
     ui->ModifEvent->show();


      id=ui->tableEvent->item(row,2)->text();

      if(query.exec("SELECT * FROM Event WHERE idEvent='"+id+"'"))
      {

          while(query.next()){
              ui->EventNom->setText(query.value(1).toString());
              ui->EventDescription->setText(query.value(3).toString());

              ui->EventDate->setDateTime(query.value(2).toDateTime());

          }

      }else{
          QMessageBox::warning(this,"Opération impossible","Requête impossible");
      }


}


void MainWindow::on_supprEvent_clicked()
{
     QSqlQuery query;
     QString id;


      id=ui->tableEvent->item(ui->tableEvent->currentRow(),2)->text();

      if(query.exec("DELETE FROM Event_has_employe WHERE Event_idEvent='"+id+"'")) 
      {

      }else{
          QMessageBox::warning(this,"Opération impossible","Requête impossible");
      }
      if(query.exec("DELETE FROM Event WHERE idEvent='"+id+"'")) 
      {

      }else{
          QMessageBox::warning(this,"Opération impossible","Requête impossible");
      }

      actualiserEvent();


}


void MainWindow::on_addEvent_clicked()
{
    ui->stackedWidget->setCurrentIndex(23);


    QSqlQuery query;
    while(ui->EventAddEmploy->rowCount()>0){
        ui->EventAddEmploy->removeRow(0);
    }
    if(query.exec("SELECT * FROM Employe"))
    {
        ui->EventAddEmploy->setRowCount(query.size());
        int i=0;

        while(query.next())
           {
            QTableWidgetItem *newItem= new QTableWidgetItem ();
            newItem->setText(query.value(1).toString());
            QTableWidgetItem *newItem2= new QTableWidgetItem ();
            newItem2->setText(query.value(2).toString());
            ui->EventAddEmploy->setItem(i,0,newItem);
            ui->EventAddEmploy->setItem(i,1,newItem2);
            QTableWidgetItem *newItem3= new QTableWidgetItem ();
            newItem3->setText(query.value(0).toString());
            ui->EventAddEmploy->setItem(i,2,newItem3);

            QTableWidgetItem *checkBoxItem = new QTableWidgetItem();

            ui->EventAddEmploy->setItem(i, 3, checkBoxItem);
            i++;


           }
    }else{
        QMessageBox::warning(this,"Opération impossible","Requête impossible");
    }
}



void MainWindow::on_calendEvent_clicked(const QDate &date)
{
    actualiserEvent();
}


void MainWindow::on_ValiderAddEvent_clicked()
{
    QDateTime dt;
    QString  nom, description,lastid,date;
    int compteur=0;

    for(int i=0;i<ui->EventAddEmploy->rowCount();i++){
        if(ui->EventAddEmploy->item(i,3)->text()=="Oui"){
            compteur++;
        }
    }
    if(compteur!=0){
        dt=ui->EventDate_2->dateTime();
        nom=ui->EventNom_2->text();
        description=ui->EventDescription_2->toPlainText();
        date=dt.toString("yyyy-MM-dd hh:mm:ss");

        QSqlQuery query;
        query.exec("INSERT INTO Event (Nom,Date,Description) VALUES ('"+nom+"','"+dt.toString(Qt::ISODate)+"','"+description+"')");

        if(query.exec("SELECT idEvent FROM Event WHERE Nom='"+nom+"' AND Description ='"+description+"' AND Date='"+date+"'"))
        {
            while(query.next())
               {

                lastid=query.value(0).toString();

               }
        }else{
            QMessageBox::warning(this,"Opération impossible","Requête impossible");
        }

        int row =ui->EventAddEmploy->rowCount();

        for(int i=0;i<row;i++)
            {   
            if(ui->EventAddEmploy->item(i,3)->text()=="Oui"){
                query.exec("INSERT INTO Event_has_Employe (Event_idEvent,Employe_idEmploye) VALUES ('"+lastid+"','"+ui->EventAddEmploy->item(i,2)->text()+"')");
            }
            }
        actualiserEvent();
    }else{
        QMessageBox::warning(this,"Suppression impossible","Aucun employe selectionne");
    }
}

 void MainWindow::on_ValidEmployProjet_clicked()
{
    QSqlQuery query;
    int row =ui->tableEmployProjet->rowCount(),compteur=0;

    for(int i=0;i<row;i++){
        if(ui->tableEmployProjet->item(i,3)->text()=="Oui"){
            compteur++;
        }
    }
    if(compteur!=0){
        QString lastid,nom,categ,etat,start,dead;
        nom=ui->NomProjet_3->text();
        categ=ui->CategProjet_3->text();
        etat=ui->EtatProjet_3->text();
        start=ui->StartProjet_3->text();
        dead=ui->DeadProjet_3->text();
        if(query.exec("SELECT idProjet FROM Projet WHERE Nom='"+nom+"' AND  Categorie='"+categ+"' AND Statut='"+etat+"'")){
            while(query.next()){
                lastid=query.value(0).toString();
            }
        }
        for(int i=0;i<row;i++){
            if(ui->tableEmployProjet->item(i,3)->text()=="Oui"){

                query.exec("INSERT INTO Travailler (Employe_idEmploye,Projet_idProjet,Qte_Heure) VALUES ('"+ui->tableEmployProjet->item(i,0)->text()+"','"+lastid+"',0)");
            }
        }
        while(ui->tableEmployProjet_2->rowCount()>0){
            ui->tableEmployProjet_2->removeRow(0);
        }
        if(query.exec("SELECT * FROM Client"))
        {
            ui->tableEmployProjet_2->setRowCount(query.size());
            int i=0;

            while(query.next())
               {
                QTableWidgetItem *newItem= new QTableWidgetItem ();
                newItem->setText(query.value(0).toString());
                QTableWidgetItem *newItem2= new QTableWidgetItem ();
                newItem2->setText(query.value(1).toString());
                ui->tableEmployProjet_2->setItem(i,0,newItem);
                ui->tableEmployProjet_2->setItem(i,1,newItem2);
                QTableWidgetItem *newItem3= new QTableWidgetItem ();
                newItem3->setText(query.value(2).toString());
                ui->tableEmployProjet_2->setItem(i,2,newItem3);
                QTableWidgetItem *newItem4= new QTableWidgetItem ();
                newItem4->setText("Non");
                ui->tableEmployProjet_2->setItem(i,3,newItem4);
                i++;


               }
        }else{
            QMessageBox::warning(this,"Opération impossible","Requête impossible");
        }
        ui->stackedWidget->setCurrentIndex(11);
    }else {
        QMessageBox::warning(this,"Aucun employé sélectionné","Sélectionnez un employé");
    }
}


void MainWindow::on_Connexion_clicked()
{
    QFile fichier("C:/Users/Seb/Desktop/mdp.txt");
            QTextStream stream(&fichier);
            fichier.open(QIODevice::ReadOnly | QIODevice::Text);
            QString mot,mot2,mot3;
            while(!stream.atEnd())
            {
                stream >> mot ;
                if(mot==ui->Login->text())
                {
                        stream>>mot2;

                        if(mot2==ui->Mdp->text())
                        {
                                stream>>mot3;
                                idLogged=mot3;

                        }

                }


            }
            if(idLogged!="-1"){
                ui->Contact->show();
                ui->Evenements->show();
                ui->Projet->show();
                ui->Commande->show();
                ui->Deconnexion->show();
                ui->frame->hide();
                fichier.close();
                if(idLogged=="1" || idLogged=="2"){
                    admin=true;
                }
            }else{
                QMessageBox::warning(this,"Erreur","Mauvais identifiant");
            }

}


void MainWindow::on_EventAddEmploy_cellClicked(int row, int column)
{
    ui->ValiderChoixEmployEvent->show();
    ui->DeselectionEmployEvent->show();
}


void MainWindow::on_ValiderChoixEmployEvent_clicked()
{
    QColor color(4,174,218,255);
    QColor color2(255,255,255,255);
    ui->EventAddEmploy->item(ui->EventAddEmploy->currentRow(),3)->setText("Oui");
    ui->EventAddEmploy->item(ui->EventAddEmploy->currentRow(),0)->setBackgroundColor(color);
    ui->EventAddEmploy->item(ui->EventAddEmploy->currentRow(),1)->setBackgroundColor(color);
    ui->EventAddEmploy->item(ui->EventAddEmploy->currentRow(),2)->setBackgroundColor(color);
    ui->EventAddEmploy->item(ui->EventAddEmploy->currentRow(),3)->setBackgroundColor(color);
    ui->EventAddEmploy->item(ui->EventAddEmploy->currentRow(),0)->setTextColor(color2);
    ui->EventAddEmploy->item(ui->EventAddEmploy->currentRow(),1)->setTextColor(color2);
    ui->EventAddEmploy->item(ui->EventAddEmploy->currentRow(),2)->setTextColor(color2);
    ui->EventAddEmploy->item(ui->EventAddEmploy->currentRow(),3)->setTextColor(color2);

}


void MainWindow::on_DeselectionEmployEvent_clicked()
{
    QColor color(255,255,255,255);
    QColor color2(0,0,0,255);
    ui->EventAddEmploy->item(ui->EventAddEmploy->currentRow(),3)->setText("Non");
    ui->EventAddEmploy->item(ui->EventAddEmploy->currentRow(),0)->setBackgroundColor(color);
    ui->EventAddEmploy->item(ui->EventAddEmploy->currentRow(),1)->setBackgroundColor(color);
    ui->EventAddEmploy->item(ui->EventAddEmploy->currentRow(),2)->setBackgroundColor(color);
    ui->EventAddEmploy->item(ui->EventAddEmploy->currentRow(),3)->setBackgroundColor(color);
    ui->EventAddEmploy->item(ui->EventAddEmploy->currentRow(),0)->setTextColor(color2);
    ui->EventAddEmploy->item(ui->EventAddEmploy->currentRow(),1)->setTextColor(color2);
    ui->EventAddEmploy->item(ui->EventAddEmploy->currentRow(),2)->setTextColor(color2);
    ui->EventAddEmploy->item(ui->EventAddEmploy->currentRow(),3)->setTextColor(color2);
}


void MainWindow::on_precedent_clicked()
{
    ui->stackedWidget->setCurrentIndex(22);
}



void MainWindow::on_Commande_clicked()
{
    ui->Back->show();
    ui->stackedWidget->setCurrentIndex(17);
}


void MainWindow::on_ConsulterCommande_clicked()
{
    if(ui->radioProduit->isChecked()){
        ui->stackedWidget->setCurrentIndex(21);
    }else if(ui->radioCommande->isChecked()){
        ui->stackedWidget->setCurrentIndex(20);
    }
}


void MainWindow::on_tableProduit_cellClicked(int row, int column)
{
    QSqlQuery query;
    QString id;

    id=ui->tableProduit->item(row,1)->text();
    if(query.exec("SELECT * FROM Produit WHERE idProduit='"+id+"'")){
       while(query.next()){
           ui->NomProduit->setText(query.value(1).toString());
           ui->DescriptProduit->setText(query.value(2).toString());
       }
    }
    ui->supprProduit->show();
}



void MainWindow::on_tableCommande_cellClicked(int row, int column)
{
    QSqlQuery query;
    QString id;

    id=ui->tableCommande->item(row,0)->text();
    if(query.exec(("SELECT * FROM Commande WHERE idCommande='"+id+"'"))){
        while(query.next()){
            ui->NumCommande->setText((query.value(0).toString()));
            ui->DateCommande->setText(query.value(1).toString());
        }
    }
    if(query.exec("SELECT Fournisseur.Nom,Fournisseur.TVA FROM Fournisseur "
                  "INNER JOIN((Commande "
                  "INNER JOIN Comporter ON '"+id+"'=Comporter.Commande_idCommande)"
                  "INNER JOIN Produit ON Comporter.Produit_idProduit=Produit.idProduit "
                  "INNER JOIN Produit_Has_Fournisseur ON Produit.idProduit=Produit_Has_Fournisseur.Produit_idProduit)ON Fournisseur.idFournisseur=Produit_Has_Fournisseur.Fournisseur_idFournisseur " )){
        while(query.next()){
            ui->FourCommande->setText(query.value(0).toString());
            ui->TVAFourCommande->setText(query.value(1).toString());
        }
    }else{
        QMessageBox::warning(this,"Opération Impossible","Requête impossible :"+query.lastError().text());
    }
    if(query.exec("SELECT SUM(Comporter.Quantité*Produit_has_Fournisseur.Prix) FROM (Commande INNER JOIN Comporter ON Comporter.Commande_idCommande=Commande.idCommande ) INNER JOIN Produit_has_Fournisseur ON Comporter.Produit_idProduit=Produit_has_Fournisseur.Produit_idProduit WHERE Commande.idCommande ='"+id+"'")){
        while(query.next()){
            ui->TotalCommande->setText(query.value(0).toString());
        }
    }
    QString tmp,tmp2;
    if(query.exec("SELECT * FROM Produit INNER JOIN Comporter ON Produit.idProduit=Comporter.Produit_idProduit  WHERE Comporter.Commande_idCommande='"+id+"'")){
        while(query.next()){
            tmp+=query.value(1).toString()+"\n";
        }
    }else{
        QMessageBox::warning(this,"Opération Impossible","Requête impossible :"+query.lastError().text());
    }
    if(query.exec("SELECT Comporter.Quantité FROM Comporter INNER JOIN Produit ON Comporter.Produit_idProduit=Produit.idProduit WHERE Comporter.Commande_idCommande='"+id+"'")){
        while(query.next()){
            tmp2+=query.value(0).toString()+"\n";
        }
    }else{
        QMessageBox::warning(this,"Opération Impossible","Requête impossible :"+query.lastError().text());
    }
        ui->DescripCommande->setPlainText(tmp);
        ui->DescripCommande_2->setPlainText(tmp2);

    if(query.exec("SELECT Projet.Nom FROM Projet INNER JOIN(Commande INNER JOIN Employe_has_Commande ON '"+id+"'=Employe_has_Commande.Commande_idCommande)ON Projet.idProjet=Employe_has_Commande.Projet_idProjet")){
        while(query.next()){
            ui->ProjetCommande->setText(query.value(0).toString());
        }
    }else{
        QMessageBox::warning(this,"Opération Impossible","Requête impossible :"+query.lastError().text());
    }
    ui->SupprCommande->show();
}


void MainWindow::on_AddCommande_clicked()
{
    if(ui->radioProduit->isChecked()){
        QSqlQuery query;
        ui->stackedWidget->setCurrentIndex(19);
        while(ui->tableFourProd->rowCount()>0){
            ui->tableFourProd->removeRow(0);
        }
        if(query.exec("SELECT * FROM Fournisseur"))
        {
            ui->tableFourProd->setRowCount(query.size());
            int i=0;
            while(query.next())
               {
                QTableWidgetItem *newItem3= new QTableWidgetItem ();
                newItem3->setText("Non");
                QTableWidgetItem *newItem= new QTableWidgetItem ();
                newItem->setText(query.value(0).toString());
                QTableWidgetItem *newItem2= new QTableWidgetItem ();
                newItem2->setText(query.value(1).toString());
                ui->tableFourProd->setItem(i,1,newItem);
                ui->tableFourProd->setItem(i,0,newItem2);
                ui->tableFourProd->setItem(i,2,newItem3);
                i++;


               }
        }else{
            QMessageBox::warning(this,"Opération impossible","Requête impossible");
        }
    }else if(ui->radioCommande->isChecked()){
        QSqlQuery query,query2,query3;
        ui->stackedWidget->setCurrentIndex(18);
        while(ui->tableAddCommande->rowCount()>0){
            ui->tableAddCommande->removeRow(0);
        }
        if(query.exec("SELECT * FROM Produit_has_fournisseur"))
        {
            ui->tableAddCommande->setRowCount(query.size());
            int i=0;
            while(query.next())
               {
                QTableWidgetItem *newItem= new QTableWidgetItem ();
                newItem->setText(query.value(0).toString());
                QTableWidgetItem *newItem2= new QTableWidgetItem ();
                newItem2->setText(query.value(2).toString());
                ui->tableAddCommande->setItem(i,4,newItem);
                ui->tableAddCommande->setItem(i,2,newItem2);
                if(query2.exec("SELECT Nom FROM Produit WHERE idProduit='"+query.value(0).toString()+"'")){
                    while(query2.next()){
                        QTableWidgetItem *newItem3=new QTableWidgetItem ();
                        newItem3->setText(query2.value(0).toString());
                        ui->tableAddCommande->setItem(i,0,newItem3);
                    }
                }
                if(query3.exec("SELECT Nom FROM Fournisseur WHERE idFournisseur='"+query.value(1).toString()+"'")){
                    while(query3.next()){
                        QTableWidgetItem *newItem4=new QTableWidgetItem ();
                        newItem4->setText(query3.value(0).toString());
                        ui->tableAddCommande->setItem(i,1,newItem4);
                    }
                }
                QTableWidgetItem *newItem5=new QTableWidgetItem ();
                ui->tableAddCommande->setItem(i,5,newItem5);
                QTableWidgetItem *newItem6=new QTableWidgetItem ();
                ui->tableAddCommande->setItem(i,3,newItem6);

                i++;


               }
        }else{
            QMessageBox::warning(this,"Opération impossible","Requête impossible");
        }
    }
}

void MainWindow::on_tableFourProd_cellClicked(int row, int column)
{
    ui->ValiderFourProd->show();
    ui->DeselectFourProd->show();
}

void MainWindow::on_ValiderFourProd_clicked()
{
    QColor color(4,174,218,255);
    QColor color2(255,255,255,255);
    ui->tableFourProd->item(ui->tableFourProd->currentRow(),2)->setText("Oui");
    ui->tableFourProd->item(ui->tableFourProd->currentRow(),0)->setBackgroundColor(color);
    ui->tableFourProd->item(ui->tableFourProd->currentRow(),1)->setBackgroundColor(color);
    ui->tableFourProd->item(ui->tableFourProd->currentRow(),2)->setBackgroundColor(color);
    ui->tableFourProd->item(ui->tableFourProd->currentRow(),0)->setTextColor(color2);
    ui->tableFourProd->item(ui->tableFourProd->currentRow(),1)->setTextColor(color2);
    ui->tableFourProd->item(ui->tableFourProd->currentRow(),2)->setTextColor(color2);
}

void MainWindow::on_DeselectFourProd_clicked()
{
    QColor color(255,255,255,255);
    QColor color2(0,0,0,255);
    ui->tableFourProd->item(ui->tableFourProd->currentRow(),2)->setText("Non");
    ui->tableFourProd->item(ui->tableFourProd->currentRow(),0)->setBackgroundColor(color);
    ui->tableFourProd->item(ui->tableFourProd->currentRow(),1)->setBackgroundColor(color);
    ui->tableFourProd->item(ui->tableFourProd->currentRow(),2)->setBackgroundColor(color);
    ui->tableFourProd->item(ui->tableFourProd->currentRow(),0)->setTextColor(color2);
    ui->tableFourProd->item(ui->tableFourProd->currentRow(),1)->setTextColor(color2);
    ui->tableFourProd->item(ui->tableFourProd->currentRow(),2)->setTextColor(color2);
}


void MainWindow::on_ValiderProd_clicked()
{
    int compteur=0;
    for(int i=0;i<ui->tableFourProd->rowCount();i++){
        if(ui->tableFourProd->item(i,2)->text()=="Oui"){
            compteur++;
        }
    }
    if(compteur!=0){
        QSqlQuery query,query2,query3,query4,query5;  // MOYEN DE FAIRE MIEUX ?
        bool trouve=false;
        QString id,idFournisseur,tmp,prix;
        if(query.exec("SELECT * FROM Produit")){
            while(query.next()){
               if(query.value(1).toString()==ui->NomAjoutProd->text() && query.value(2).toString()==ui->DescAjoutProd->toPlainText()){
                  if(query2.exec("SELECT * FROM Produit WHERE Nom='"+ui->NomAjoutProd->text()+"' AND Description='"+ui->DescAjoutProd->toPlainText()+"'"))
                      while(query2.next()){
                          id=query2.value(0).toString();
                          for(int i=0;i<ui->tableFourProd->rowCount();i++){
                              if(ui->tableFourProd->item(i,2)->text()=="Oui"){
                                  idFournisseur=ui->tableFourProd->item(i,1)->text();
                                  if(query3.exec("SELECT * FROM Produit_has_fournisseur WHERE Fournisseur_idFournisseur='"+idFournisseur+"' AND Produit_idProduit='"+id+"'") && query3.size()!=0)  //permet de s'assurer qu'il y a au moins un produit, sinon il rentrait (car Selection réussie puisque bonne requete) mais la query avait une taille nulle. Mazis comme trouve devenait true, ca ne fonctionnait pas
                                  {
                                      trouve=true;
                                      while(query3.next()){
                                          QMessageBox::about(this,"Produit déjà existant","Ce produit existe déjà :\nPrix="+query3.value(2).toString()+"\tFournisseur="+query3.value(1).toString()+"\tProduit="+query3.value(0).toString());
                                      }
                                  }
                              }
                          }
                      }
               }
            }
            if(!trouve){
                if(query4.exec("SELECT idProduit FROM Produit WHERE Nom='"+ui->NomAjoutProd->text()+"' AND Description='"+ui->DescAjoutProd->toPlainText()+"'")){
                    for(int i=0;i<ui->tableFourProd->rowCount();i++){
                        if(ui->tableFourProd->item(i,2)->text()=="Oui"){
                            idFournisseur=ui->tableFourProd->item(i,1)->text();
                            prix=ui->PrixAjoutProd->text();
                        }
                    }
                    if(query4.size()==1){
                        QMessageBox::about(this,"Produit déjà existant","Ce produit existe déjà chez un autre fournisseur. Il sera donc ajouté au fournisseur sélectionné");
                        while(query4.next()){
                            tmp=query4.value(0).toString();
                            query5.exec("INSERT INTO Produit_has_fournisseur (Fournisseur_idFournisseur,Produit_idProduit,Prix) VALUES ('"+idFournisseur+"','"+tmp+"','"+prix+"')");
                        }
                    }else if(query4.size()==0){
                        query5.exec("INSERT INTO Produit (Nom,Description) VALUES ('"+ui->NomAjoutProd->text()+"','"+ui->DescAjoutProd->toPlainText()+"')");
                        if(query5.exec("SELECT idProduit FROM Produit WHERE Nom='"+ui->NomAjoutProd->text()+"' AND Description='"+ui->DescAjoutProd->toPlainText()+"'")){
                            while(query5.next()){
                                tmp=query5.value(0).toString();
                            }
                        }
                        query5.exec("INSERT INTO Produit_has_fournisseur (Fournisseur_idFournisseur,Produit_idProduit,Prix) VALUES ('"+idFournisseur+"','"+tmp+"','"+prix+"')");
                    }
                }
                actualiserProduit();
                ui->stackedWidget->setCurrentIndex(17);
        }
    }
    }else{
        QMessageBox::critical(this,"Selectionnez un fournisseur","Aucun fournisseur sélectionné");

    }
}


void MainWindow::on_tableTimesheet_cellClicked(int row, int column)
{
    QString id;
    id=ui->tableTimesheet->item(row,1)->text();
    ui->okHeure->show();
    QSqlQuery query;

    if(query.exec("SELECT Qte_Heure FROM Travailler WHERE Projet_idProjet='"+id+"' AND Employe_idEmploye='"+idLogged+"'")){
        while (query.next()){
            ui->consultHeure->setText(query.value(0).toString());
        }
    }
}

void MainWindow::on_okHeure_clicked()
{
    QSqlQuery query;
    QString tmp,tmp2;
    int test;
    ui->okHeure->hide();
        tmp=ui->heure->text();
        tmp2=ui->tableTimesheet->item(ui->tableTimesheet->currentRow(),1)->text();
        if(query.exec("SELECT Qte_Heure FROM Travailler WHERE Projet_idProjet='"+tmp2+"' AND Employe_idEmploye='"+idLogged+"'")){
            while(query.next()){
                test=tmp.toInt()+query.value(0).toString().toInt();
                tmp=QString::number(test);
            }
        }

        query.exec("UPDATE Travailler SET Qte_Heure='"+tmp+"' WHERE Projet_idProjet='"+tmp2+"' AND Employe_idEmploye='"+idLogged+"'");
        ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_tableAddCommande_cellClicked(int row, int column)
{
    QString idProduit;
    idProduit=ui->tableAddCommande->item(row,4)->text();
    QSqlQuery query;
    if(query.exec("SELECT Description FROM Produit WHERE idProduit='"+idProduit+"'")){
        while(query.next()){
            ui->addCommandeDescriptionProduit->setPlainText(query.value(0).toString());
        }
    }
    ui->SelectionProduitAddCommande->show();
    ui->DeselectionProduitAddCommande->show();
}



void MainWindow::on_SelectionProduitAddCommande_clicked()
{
    QColor color(4,174,218,255);
    QColor color2(255,255,255,255);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),5)->setText("Oui");
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),0)->setBackgroundColor(color);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),1)->setBackgroundColor(color);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),2)->setBackgroundColor(color);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),3)->setBackgroundColor(color);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),4)->setBackgroundColor(color);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),5)->setBackgroundColor(color);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),0)->setTextColor(color2);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),1)->setTextColor(color2);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),2)->setTextColor(color2);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),3)->setTextColor(color2);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),4)->setTextColor(color2);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),5)->setTextColor(color2);
}

void MainWindow::on_DeselectionProduitAddCommande_clicked()
{
    QColor color(255,255,255,255);
    QColor color2(0,0,0,255);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),5)->setText("Non");
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),0)->setBackgroundColor(color);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),1)->setBackgroundColor(color);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),2)->setBackgroundColor(color);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),3)->setBackgroundColor(color);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),4)->setBackgroundColor(color);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),5)->setBackgroundColor(color);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),0)->setTextColor(color2);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),1)->setTextColor(color2);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),2)->setTextColor(color2);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),3)->setTextColor(color2);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),4)->setTextColor(color2);
    ui->tableAddCommande->item(ui->tableAddCommande->currentRow(),5)->setTextColor(color2);
}


void MainWindow::on_NextCommande_clicked()
{
    int compteur=0,compteurQte=0;
    for(int i=0;i<ui->tableAddCommande->rowCount();i++){
        if(ui->tableAddCommande->item(i,5)->text()=="Oui"){
            compteur++;
            if(ui->tableAddCommande->item(i,3)->text()!= ""){
                //QMessageBox::about(this,"Quantité",ui->tableAddCommande->item(i,3)->text());
                compteurQte++;
            }
        }
    }if(compteur!=0 && compteurQte!=0){
        ui->stackedWidget->setCurrentIndex(24);
        QSqlQuery query;
        while(ui->tableProjetCommande->rowCount()>0){
            ui->tableProjetCommande->removeRow(0);
        }
        if(query.exec("SELECT * FROM Projet"))
        {
            ui->tableProjetCommande->setRowCount(query.size());
            int i=0;
            while(query.next())
               {
                QTableWidgetItem *newItem= new QTableWidgetItem ();
                newItem->setText(query.value(1).toString());
                QTableWidgetItem *newItem2= new QTableWidgetItem ();
                newItem2->setText(query.value(0).toString());
                QTableWidgetItem *newItem3= new QTableWidgetItem ();
                ui->tableProjetCommande->setItem(i,0,newItem);
                ui->tableProjetCommande->setItem(i,1,newItem2);
                ui->tableProjetCommande->setItem(i,2,newItem3);
                i++;


               }
        }else{
            QMessageBox::warning(this,"Opération impossible","Requête impossible");
        }
    }else if(compteur==0)
    {
            QMessageBox::warning(this,"Aucun produit sélectionné","Selectionnez d'abord un produit");
    }else if(compteurQte==0){
              QMessageBox::warning(this,"Aucun quantité saisie","Rentrez la quantité de produit souhaitée");
    }
}

void MainWindow::on_SelectionProjetAddCommande_clicked()
{
    QColor color(4,174,218,255);
    QColor color2(255,255,255,255);
    ui->tableProjetCommande->item(ui->tableProjetCommande->currentRow(),2)->setText("Oui");
    ui->tableProjetCommande->item(ui->tableProjetCommande->currentRow(),0)->setBackgroundColor(color);
    ui->tableProjetCommande->item(ui->tableProjetCommande->currentRow(),1)->setBackgroundColor(color);
    ui->tableProjetCommande->item(ui->tableProjetCommande->currentRow(),2)->setBackgroundColor(color);
    ui->tableProjetCommande->item(ui->tableProjetCommande->currentRow(),0)->setTextColor(color2);
    ui->tableProjetCommande->item(ui->tableProjetCommande->currentRow(),1)->setTextColor(color2);
    ui->tableProjetCommande->item(ui->tableProjetCommande->currentRow(),2)->setTextColor(color2);
}

void MainWindow::on_DeselectionProjetAddCommande_clicked()
{
    QColor color(255,255,255,255);
    QColor color2(0,0,0,255);
    ui->tableProjetCommande->item(ui->tableProjetCommande->currentRow(),2)->setText("Non");
    ui->tableProjetCommande->item(ui->tableProjetCommande->currentRow(),0)->setBackgroundColor(color);
    ui->tableProjetCommande->item(ui->tableProjetCommande->currentRow(),1)->setBackgroundColor(color);
    ui->tableProjetCommande->item(ui->tableProjetCommande->currentRow(),2)->setBackgroundColor(color);
    ui->tableProjetCommande->item(ui->tableProjetCommande->currentRow(),0)->setTextColor(color2);
    ui->tableProjetCommande->item(ui->tableProjetCommande->currentRow(),1)->setTextColor(color2);
    ui->tableProjetCommande->item(ui->tableProjetCommande->currentRow(),2)->setTextColor(color2);
}

void MainWindow::on_tableProjetCommande_cellClicked(int row, int column)
{
    ui->SelectionProjetAddCommande->show();
    ui->DeselectionProjetAddCommande->show();
}

void MainWindow::on_ValiderCommande_clicked()
{
    int compteur=0;
    QString idProjet;
    for(int i=0;i<ui->tableProjetCommande->rowCount();i++){
        if(ui->tableProjetCommande->item(i,2)->text()=="Oui"){
            compteur++;
            idProjet=ui->tableProjetCommande->item(i,1)->text();
        }
    }
    if(compteur==1){
        QDateTime dt=QDateTime::currentDateTime();
        QString date;
        date=dt.toString("yyyy-MM-dd hh:mm:ss");

        QSqlQuery query;
        query.exec("INSERT INTO Commande (Date) VALUES ('"+date+"')");
        QString idCommande;

        if(query.exec("SELECT idCommande FROM Commande WHERE Date='"+date+"'")){
            while(query.next()){
                idCommande=query.value(0).toString();
            }
        }
        for(int i=0;i<ui->tableAddCommande->rowCount();i++){
            if(ui->tableAddCommande->item(i,5)->text()=="Oui"){
                query.exec("INSERT INTO Comporter (Commande_idCommande,Produit_idProduit,Quantité) VALUES ('"+idCommande+"','"+ui->tableAddCommande->item(i,4)->text()+"','"+ui->tableAddCommande->item(i,3)->text()+"')");
            }
        }
        query.exec("INSERT INTO Employe_has_commande (Employe_idEmploye,Commande_idCommande,Projet_idProjet) VALUES ('"+idLogged+"','"+idCommande+"','"+idProjet+"')");
    ui->pageNextCommande->hide();
    ui->acceuil->show();
    }else{
        QMessageBox::about(this,"Plusieurs projets sélectionnés","Ne selectionnez qu'un seul projet");
    }

    actualiserCommande();

}

void MainWindow::on_SupprCommande_clicked()
{
    QSqlQuery query;
    query.exec("DELETE FROM Comporter WHERE Commande_idCommande='"+ui->tableCommande->item(ui->tableCommande->currentRow(),0)->text()+"'");
    query.exec("DELETE FROM Employe_has_Commande WHERE Commande_idCommande='"+ui->tableCommande->item(ui->tableCommande->currentRow(),0)->text()+"'");
    query.exec("DELETE FROM Commande WHERE idCommande='"+ui->tableCommande->item(ui->tableCommande->currentRow(),0)->text()+"'");
    ui->stackedWidget->setCurrentIndex(17);
    actualiserCommande();
}

void MainWindow::on_supprProduit_clicked()
{
    QSqlQuery query;
    query.exec("DELETE FROM Comporter WHERE Produit_idProduit='"+ui->tableProduit->item(ui->tableProduit->currentRow(),1)->text()+"'");
    query.exec("DELETE FROM Produit_has_fournisseur WHERE Produit_idProduit='"+ui->tableProduit->item(ui->tableProduit->currentRow(),1)->text()+"'");
    query.exec("DELETE FROM Produit WHERE idProduit='"+ui->tableProduit->item(ui->tableProduit->currentRow(),1)->text()+"'");
    ui->stackedWidget->setCurrentIndex(17);
    actualiserProduit();
}

void MainWindow::on_tableEmployProjet_2_cellClicked(int row, int column)
{
    ui->validerChoixEmploy_2->show();
    ui->deselectionChoixEmploy_2->show();
}

void MainWindow::on_validerChoixEmploy_2_clicked()
{
    QColor color(4,174,218,255);
    QColor color2(255,255,255,255);
    ui->tableEmployProjet_2->item(ui->tableEmployProjet_2->currentRow(),3)->setText("Oui");
    ui->tableEmployProjet_2->item(ui->tableEmployProjet_2->currentRow(),0)->setBackgroundColor(color);
    ui->tableEmployProjet_2->item(ui->tableEmployProjet_2->currentRow(),1)->setBackgroundColor(color);
    ui->tableEmployProjet_2->item(ui->tableEmployProjet_2->currentRow(),2)->setBackgroundColor(color);
    ui->tableEmployProjet_2->item(ui->tableEmployProjet_2->currentRow(),3)->setBackgroundColor(color);
    ui->tableEmployProjet_2->item(ui->tableEmployProjet_2->currentRow(),0)->setTextColor(color2);
    ui->tableEmployProjet_2->item(ui->tableEmployProjet_2->currentRow(),1)->setTextColor(color2);
    ui->tableEmployProjet_2->item(ui->tableEmployProjet_2->currentRow(),2)->setTextColor(color2);
    ui->tableEmployProjet_2->item(ui->tableEmployProjet_2->currentRow(),3)->setTextColor(color2);

}

void MainWindow::on_deselectionChoixEmploy_2_clicked()
{
    QColor color(255,255,255,255);
    QColor color2(0,0,0,255);
    ui->tableEmployProjet_2->item(ui->tableEmployProjet_2->currentRow(),3)->setText("Non");
    ui->tableEmployProjet_2->item(ui->tableEmployProjet_2->currentRow(),0)->setBackgroundColor(color);
    ui->tableEmployProjet_2->item(ui->tableEmployProjet_2->currentRow(),1)->setBackgroundColor(color);
    ui->tableEmployProjet_2->item(ui->tableEmployProjet_2->currentRow(),2)->setBackgroundColor(color);
    ui->tableEmployProjet_2->item(ui->tableEmployProjet_2->currentRow(),3)->setBackgroundColor(color);
    ui->tableEmployProjet_2->item(ui->tableEmployProjet_2->currentRow(),0)->setTextColor(color2);
    ui->tableEmployProjet_2->item(ui->tableEmployProjet_2->currentRow(),1)->setTextColor(color2);
    ui->tableEmployProjet_2->item(ui->tableEmployProjet_2->currentRow(),2)->setTextColor(color2);
    ui->tableEmployProjet_2->item(ui->tableEmployProjet_2->currentRow(),3)->setTextColor(color2);
}

void MainWindow::on_ValidEmployProjet_2_clicked()
{
    QSqlQuery query;
    int row =ui->tableEmployProjet_2->rowCount(),compteur=0;

    for(int i=0;i<row;i++){
        if(ui->tableEmployProjet_2->item(i,3)->text()=="Oui"){
            compteur++;
        }
    }
    if(compteur!=0){
        QString lastid,nom,categ,etat,start,dead;
        nom=ui->NomProjet_3->text();
        categ=ui->CategProjet_3->text();
        etat=ui->EtatProjet_3->text();
        start=ui->StartProjet_3->date().toString("yyyy-MM-dd");
        dead=ui->DeadProjet_3->date().toString("yyyy-MM-dd");
        if(query.exec("SELECT idProjet FROM Projet WHERE Nom='"+nom+"' AND Categorie='"+categ+"' AND Statut='"+etat+"'")){
            while(query.next()){
                lastid=query.value(0).toString();
            }
        }
        for(int i=0;i<row;i++){
            if(ui->tableEmployProjet_2->item(i,3)->text()=="Oui"){
                query.exec("INSERT INTO Commander (Client_idClient,Projet_idProjet) VALUES ('"+ui->tableEmployProjet_2->item(i,0)->text()+"','"+lastid+"')");
            }
        }
        actualiserProjet();
        ui->stackedWidget->setCurrentIndex(8);
    }else {
        QMessageBox::warning(this,"Aucun client sélectionné","Sélectionnez un client");
    }
}

void MainWindow::on_Deconnexion_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->Contact->hide();
    ui->Evenements->hide();
    ui->Projet->hide();
    ui->Commande->hide();
    ui->frame->show();
    ui->Deconnexion->hide();
    idLogged="-1";
    admin=false;
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    if(e->key()==16777220 || e->key()==16777221){
        if(ui->stackedWidget->currentIndex()==0){
            on_Connexion_clicked();
        }
    }
}




