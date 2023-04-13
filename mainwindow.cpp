    #include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit); // привязка поля текста к размерам окна
    //QString fileName = ui->textEdit->windowTitle();
    //QWidget::setWindowTitle(fileName);
    // QString CurrentFile (fileName) = "";
    QWidget::setWindowTitle("*Безымянный - Блокнот");






}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Menu_Open_triggered() // меню ОТКРЫТЬ
{

    //QString fileName; // строка для имени файла (file_path)

    // вариант 1 Winfows style - экранируем слеши
    fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"),"", tr("Text files (*.txt)"));

    // вариант 2 Linux style - обратные слеши
    //fileName=QFileDialog::getOpenFileName(this, tr("Открыть файл"),"C:/Users/student/Documents", tr("Text files (*.txt)"));

    if (fileName.isEmpty()) // Файл не выбран
    {
        QMessageBox::information(this, "Ошибка", "Файл не выбран");

    }
    else
    {
        ui->textEdit->append(fileName);
        ui->textEdit->clear(); //очистка поля редактора
        QFile file; // класс файлов
        file.setFileName(fileName); // связываем имя с Файлом

        file.open(QIODevice::ReadOnly); // открываем только на чтение

        QByteArray ba; // массив для передачи данных
        ba.clear();
        long long int size; // размер файла

        size = file.size(); // получаем размер файла

        ba = file.read(size); // чтение из файла

        ui->textEdit->append(QString(ba)); // копируем в поле редактора через QString

        QWidget::setWindowTitle(fileName);

        file.close(); // закрываем файл
    }
}

void MainWindow::on_Menu_Save_As_triggered() // меню СОХРАНИТЬ КАК
{

    //QString fileName; // строка для имени файла

    // вариант 1 Winfows style - экранируем слеши
    fileName = QFileDialog::getSaveFileName(this, tr("Сохранить как"),"Новый текстовый документ - Блокнот", tr("Text files (*.txt)"));

    if (fileName.isEmpty()) // Файл не выбран
    {
        QMessageBox::information(this, "Внимание!", "Файл не выбран");


    }
    else
    {
        QFile file; // класс файлов
        file.setFileName(fileName); // связываем имя с файлом

        file.open(QIODevice::WriteOnly); // открываем имя с файлом

        file.write(ui->textEdit->toPlainText().toUtf8( )); // запись в файл через цепочку преобразований

        QWidget::setWindowTitle(fileName);

        file.close(); // закрываем файл
    }
}

void MainWindow::closeEvent(QCloseEvent *event) //ОБРАБОТЧИК ЗАКРЫТИЯ ФОРМЫ
{
    if (QMessageBox::question(this, "Выход", "Точно выходим?", QMessageBox::Yes |QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)
    {//YES
        event->accept(); // принимаем сигнал
    }
    else
    {
        event->ignore(); // игнорируем сигнал
    }

}

/*
1) доделать остальные пункты меню (уже созданные 5 штук) как в стандартном Блокноте винды
2) сделать привязку поля текста к размерам окна ^^^^^
3) имя файла в заголовке окна
4) работа с русскими буквами ^^^^^
5) проверки на сохранении изменений (не забываем * у имени)
*/

void MainWindow::on_Menu_Create_triggered() // МЕНЮ СОЗДАТЬ
{
    QString fileName = "";
    fileName.clear();
    ui->textEdit->setText(QString());
    QWidget::setWindowTitle("*Безымянный - блокнот");
}



void MainWindow::on_Menu_Save_triggered() // МЕНЮ СОХРАНИТЬ ???????????????????????????????????????????????????????????????
{



    QFile file; // класс файлов
    file.setFileName(fileName); // связываем имя с файлом

    file.open(QIODevice::WriteOnly); // открываем имя с файлом

    file.write(ui->textEdit->toPlainText().toUtf8( )); // запись в файл через цепочку преобразований

    file.close(); // закрываем файл



}



void MainWindow::on_Menu_Exit_triggered() // МЕНЮ ВЫХОД ????????????????????????????????????????????????????????????
{
    QWidget::close();
    //QApplication::quit(); выходит мгновенно без QMessageBox
}

void MainWindow::on_Menu_Cut_triggered() // ВЫРЕЗАТЬ
{
    ui->textEdit->cut();
}

void MainWindow::on_Menu_Copy_triggered() // КОПИРОВАТЬ
{
    ui->textEdit->copy();
}

void MainWindow::on_Menu_Paste_triggered() // ВСТАВИТЬ
{
    ui->textEdit->paste();
}

void MainWindow::on_Menu_Undo_triggered() // ОТМЕНИТЬ
{
    ui->textEdit->undo();
}

void MainWindow::on_Menu_Redo_triggered() // ВОЗВРАТ
{
    ui->textEdit->redo();
}

void MainWindow::on_Menu_About_triggered() // О ПРОГРАММЕ
{
    QString about_text;
    about_text = "Автор : Кривоплясов Илья Николаевич\n";
    about_text += "Дата : 20/02/2023\n";
    about_text += "(C) Notepad :  (R)\n";
    QMessageBox::about(this, "О Программе", about_text);
}
