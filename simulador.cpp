#include "simulador.h"
#include "ui_simulador.h"

simulador::simulador(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::simulador)
{
    ui->setupUi(this);
    setWindowTitle("Simulador UDO-2017");
    setCentralWidget(ui->textEdit);
}

    compilador compilar;
    compilador_sintactico c_sintactico;

simulador::~simulador()
{
    delete ui;
}

void simulador::on_actionNuevo_triggered()
{
    archivo_txt = "";
    ui->textEdit->setPlainText("");
}

void simulador::on_actionAbrir_triggered()
{
    QString nombre_archivo = QFileDialog::getOpenFileName(this, "Abrir un archivo", "", tr("Archivos simulador UDO-2017 (*.udox);;Archivos de texto (*.txt);;Todos los archivos(*.*)"));

    if(!nombre_archivo.isEmpty()){
        QFile archivo_entrada(nombre_archivo);
        if(archivo_entrada.open(QFile::ReadOnly | QFile::Text)){
            archivo_txt = nombre_archivo;
            QTextStream entrada(&archivo_entrada);
            QString _texto = entrada.readAll();
            archivo_entrada.close();
            ui->textEdit->setPlainText(_texto);
        }
        else{
            QMessageBox::critical(this, tr("ERROR"), tr("El archivo no se puede abrir"));
            return;
        }
    }
}

void simulador::on_actionGuardar_triggered()
{
    QFile archivo_salida(archivo_txt);
    if(archivo_salida.open(QFile::WriteOnly | QFile::Text)){
        QTextStream salida(&archivo_salida);
        salida << ui->textEdit->toPlainText();
        archivo_salida.flush();
        archivo_salida.close();
    }

}

void simulador::on_actionGuardar_como_triggered()
{
    QString nombre_archivo = QFileDialog::getSaveFileName(this, tr("Guardar como"), "", tr("Archivos simulador UDO-2017 (*.udox);;Archivos de texto (*.txt);;Todos los archivos(*.*)"));

    if(!nombre_archivo.isEmpty()){
        archivo_txt = nombre_archivo;
        on_actionGuardar_triggered();
    }
}

void simulador::on_actionDeshacer_triggered()
{
    ui->textEdit->undo();
}

void simulador::on_actionRehacer_triggered()
{
    ui->textEdit->redo();
}

void simulador::on_actionCortar_triggered()
{
    ui->textEdit->cut();
}

void simulador::on_actionCopiar_triggered()
{
    ui->textEdit->copy();
}

void simulador::on_actionPegar_triggered()
{
    ui->textEdit->paste();
}

void simulador::on_actionAcerca_de_triggered()
{
    QString about_txt;
    about_txt = "Autor: Jesús Briceño\n";
    about_txt += "Fecha: Febrero 2018\n";
    about_txt += "Versión: 1.0.2";
    QMessageBox::about(this,"Simulador UDO-2017", about_txt);
}

void simulador::on_actionSalir_triggered()
{
    close();
}

void simulador::on_actionCompilar_triggered()
{
    string titulo_archivo = archivo_txt.toStdString();
    if(compilar.analisis_lexico(titulo_archivo))
        c_sintactico.analisis_sintactico();
    else
        c_sintactico.analisis_sintactico();
}
