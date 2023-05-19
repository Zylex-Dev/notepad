#include "mainwindow.h"
#include "ui_mainwindow.h"
QString filePath = "";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this->setCentralWidget(ui->textEdit); // привязка поля текста к размерам окна
    QWidget::setWindowTitle("Безымянный - Блокнот");

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Menu_Open_triggered() // меню ОТКРЫТЬ
{
    is_modified = false;
    QString filePath = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "", tr("Text files (*.txt)"));

    if (!filePath.isEmpty())
    {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            in.setCodec("UTF-8");
            ui->textEdit->setText(in.readAll());
            file.close();
            QString fileName = QFileInfo(filePath).fileName();
            setWindowTitle(fileName);

        }
        else {
            QMessageBox::critical(this, "Ошибка", "Невозможно открыть файл", QMessageBox::Ok);
        }
    }
    else {
        QMessageBox::critical(this, "Ошибка", "Файл не выбран", QMessageBox::Ok);
    }

}

void MainWindow::on_Menu_Save_As_triggered() // меню СОХРАНИТЬ КАК
{

//    QString fileName; // строка для имени файла

//    // вариант 1 Winfows style - экранируем слеши
//    fileName = QFileDialog::getSaveFileName(this, tr("Сохранить как"),"Новый текстовый документ - Блокнот", tr("Text files (*.txt)"));

//    if (fileName.isEmpty()) // Файл не выбран
//    {
//        QMessageBox::information(this, "Внимание!", "Файл не выбран");


//    }
//    else
//    {
//        QFile file; // класс файлов
//        file.setFileName(fileName); // связываем имя с файлом

//        file.open(QIODevice::WriteOnly); // открываем имя с файлом (WriteOnly)

//        file.write(ui->textEdit->toPlainText().toUtf8( )); // запись в файл через цепочку преобразований

//        QWidget::setWindowTitle(fileName);

//        file.close(); // закрываем файл
//    }

    QString fileName = QFileDialog::getSaveFileName(this, "Cохранить файл", ".", tr ("Text files (*.txt)"));
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << ui->textEdit->toPlainText().toUtf8();
            file.close();
            setWindowTitle(QFileInfo(fileName).fileName() + "- Блокнот");
            filePath = fileName;
            is_modified = false;
        }
        else
        {
            QMessageBox::critical(this, "Ошибка", "Невозможно сохранить файл", QMessageBox::Ok);
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event) //ОБРАБОТЧИК ЗАКРЫТИЯ ФОРМЫ
{
    if (is_modified)
    {
        if (QMessageBox::question(this, "Блокнот", "Файл был изменен, Вы хотите сохранить изменения?", QMessageBox::Yes |QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)
        {//YES
            on_Menu_Save_triggered();
            event->accept(); // принимаем сигнал
        }
        else
        {
            event->accept(); // игнорируем сигнал
        }
    }
    else
    {
        event->accept();
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
    if (is_modified)
    {
        QMessageBox::StandardButton response = QMessageBox::warning(this, "Сохранить изменения?", "Файл был изменен. Сохранить изменения перед созданием нового файла?", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (response == QMessageBox::Save)
        {
            on_Menu_Save_As_triggered();
        }
        else if (response == QMessageBox::Discard)
        {
            is_saved = false;
        }
        else
        {
            return;
        }
    }
    ui->textEdit->clear();
    filePath.clear();
    is_saved = false;
    is_modified = false;

}



void MainWindow::on_Menu_Save_triggered() // МЕНЮ СОХРАНИТЬ
{

//    QString fileName;

//    QFile file; // класс файлов
//    file.setFileName(fileName); // связываем имя с файлом

//    file.open(QIODevice::WriteOnly); // открываем имя с файлом

//    file.write(ui->textEdit->toPlainText().toUtf8( )); // запись в файл через цепочку преобразований

//    file.close(); // закрываем файл

    //если файл еще не был сохранен, то вызываем диалоговое окно "Сохранить как"
    if (filePath.isEmpty())
    {
        on_Menu_Save_As_triggered();
        return;
    }
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << ui->textEdit->toPlainText().toUtf8();
        file.close();
        setWindowTitle(QFileInfo(filePath).fileName() + "- Блокнот");
        is_modified = false;
    }
    else
    {
        QMessageBox::critical(this, "Ошибка", "Невозможно сохранить файл", QMessageBox::Ok);
    }

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

void MainWindow::on_textEdit_textChanged()
{
    if (!is_modified)
    {
        is_modified = true;
        SetText(filePath.split("/").last());
    }
}

void MainWindow::SetText(const QString &name)
{
    QString text;
    if (is_modified)
    {
        text = "*";
    }
    text = text + name;
    setWindowTitle(text + "- Блокнот");
}

