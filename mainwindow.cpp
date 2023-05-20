#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this->setCentralWidget(ui->textEdit); // привязка поля текста к размерам окна
    setWindowTitle(fileName);

}


MainWindow::~MainWindow()
{
    delete ui;
}

// основные действия (функции)

void MainWindow::on_Menu_Open_triggered() // меню ОТКРЫТЬ
{
    QString oldPath = this->windowTitle();

    if (count(oldPath.begin(), oldPath.end(), "*")) // если были изменения
    {
        QMessageBox quastion;
        quastion.setWindowTitle("Блокнот");
        quastion.setText("Вы хотите сохранить изменения в файле? \n" + fileName + "?");
        quastion.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        quastion.setDefaultButton(QMessageBox::Save);
        int res = quastion.exec();
        switch (res)
        {
            case QMessageBox::Save:
            {
                if (fileExits(fileName))
                    on_Menu_Save_triggered();
                else
                {/*
                    QString fileSaveName(fileName);

                    fileName = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), "", tr("Текстовые файлы (*.txt)")); //сохранить файл

                    if (!fileName.isEmpty()) //проверка на название файла
                    {
                        QFile file(fileName); //читаем название

                        if (!file.open(QIODevice::WriteOnly)) //если ошибка в файле
                        {
                            QMessageBox::warning(this, tr("Ошибка"), tr("Не могу сохранить файл") + file.errorString());
                            return;
                        }
                        else
                        {//нет ошибок
                            QString fileTitle = changedTitle(fileName);
                            QTextStream stream(&file); //сохранение текста
                            stream.setCodec("UTF-8"); //записываем в кодеке ЮТФ-8
                            stream << ui->textEdit->toPlainText(); //записывание текста
                            file.close(); //закрыли файл
                            setWindowTitle(fileTitle); //поменяли название окна
                        }
                    }
                    else //если нажали отмена
                    {
                        if (!count(oldPath.begin(), oldPath.end(), "*"))
                        {
                            fileName = fileSaveName;
                            QString fileTitle = changedTitle(fileSaveName);
                            setWindowTitle(fileTitle);
                            // если пустой файл сохранить и нажать отмена то появится звезда - баг в функции СОХРАНИТЬ КАК
                            // или если файл уже сохранен и опять нажать кнопку СОХРАНИТЬ КАК и отмена то опять появится звезда
                        }
                        else
                        {
                            fileName = fileSaveName;
                            QString fileTitle = changedTitle(fileSaveName);
                            setWindowTitle("*" + fileTitle);
                        }
                        break;
                    }*/
                    on_Menu_Save_As_triggered();
                    break;

                }


                setWindowTitle(oldPath.remove("*"));
                on_Menu_Open_triggered();
                break;
            }
            case QMessageBox::Discard:
            {
                QString fileOpenName(fileName);
                fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "", tr("Текстовые файлы (*.txt)")); //открытие файла
                if (!fileName.isEmpty()) // проверка на название файла
                {
                    QFile file(fileName); //читаем файл название
                    if(!file.open(QIODevice::ReadOnly)) // если ошибка в файле
                    {
                        QMessageBox::critical(this, tr("Ошибка!"), tr("Не могу открыть файл") + file.errorString());
                        return;
                    }
                    QString fileTitle = changedTitle(fileName);
                    QTextStream in(&file); // открытие файла
                    in.setCodec("UTF-8"); // кодек
                    text = in.readAll();
                    ui->textEdit->setText(text); // чтение файла
                    file.close(); // close
                    setWindowTitle(fileTitle); // change file title
                }
                else
                { // если нажали отмена
                    if (!count(oldPath.begin(), oldPath.end(), "*"))
                    {
                        fileName = fileOpenName;
                        QString fileTitle = changedTitle(fileOpenName);
                        setWindowTitle(fileTitle);
                        // если пустой файл сохранить и нажать отмена то появится звезда - баг в функции СОХРАНИТЬ КАК
                        // или если файл уже сохранен и опять нажать кнопку СОХРАНИТЬ КАК и отмена то опять появится звезда
                    }
                    else
                    {
                        fileName = fileOpenName;
                        QString fileTitle = changedTitle(fileOpenName);
                        setWindowTitle("*" + fileTitle);
                    }
                }

                break;
            }
            case QMessageBox::Cancel:
            {
                break;
            }
        }
    }
    else
    { // если никаких изменений в файле не было (или он сохранен)
        QString fileOpenName(fileName);

        fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "", tr("Текстовые файлы (*.txt)")); //открываем файл

        if (!fileName.isEmpty()) //проверка на название файла
        {
            QFile file(fileName); //читаем название

            if (!file.open(QIODevice::ReadOnly)) //если ошибка в файле
            {
                QMessageBox::warning(this, tr("Ошибка"), tr("Не могу открыть файл") + file.errorString());
                return;
            }
            QString fileTitle = changedTitle(fileName);
            QTextStream in(&file); //открытие файла
            in.setCodec("UTF-8"); //смена кодека на ЮТФ-8 для чтения русских файлов
            text = in.readAll();
            ui->textEdit->setText(text); //чтение файла
            file.close(); //закрыли файла
            setWindowTitle(fileTitle); //смена названия файла
        }
        else //если нажали отмена
        {
            if (!count(oldPath.begin(), oldPath.end(), "*"))
            {
                fileName = fileOpenName;
                QString fileTitle = changedTitle(fileOpenName);
                setWindowTitle(fileTitle);
                // если пустой файл сохранить и нажать отмена то появится звезда - баг в функции СОХРАНИТЬ КАК
                // или если файл уже сохранен и опять нажать кнопку СОХРАНИТЬ КАК и отмена то опять появится звезда
            }
            else
            {
                fileName = fileOpenName;
                QString fileTitle = changedTitle(fileOpenName);
                setWindowTitle("*" + fileTitle);
            }
        }
    }
}

void MainWindow::on_Menu_Save_As_triggered() // меню СОХРАНИТЬ КАК
{
    QString oldPath = this->windowTitle(); //старое название документа
    QString fileSaveName(fileName);

    fileName = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), "", tr("Text files (*.txt)")); // окно сохранения файла

    if (!fileName.isEmpty()) // проверка на название документв
    {
        QFile file(fileName.remove("*"));

        if (!file.open(QIODevice::WriteOnly)) // если ошибка в файле
        {
            QMessageBox::critical(this, tr("Ошибка"), tr("Не могу сохранить файл") + file.errorString());
            return;
        }
        else // нет ошибок
        {
            QString fileTitle = changedTitle(fileName);
            QTextStream in(&file); // сохранение текста
            in.setCodec("UTF-8");
            in << ui->textEdit->toPlainText(); // записывание текста
            file.close();
            setWindowTitle(fileTitle); // меняем название окна
        }
    }
    else // если пользоватеь нажимает кнопку отмена
    {
        if (!count(oldPath.begin(), oldPath.end(), "*"))
        {
            fileName = fileSaveName;
            QString fileTitle = changedTitle(fileSaveName);
            setWindowTitle(fileTitle);
            // если пустой файл сохранить и нажать отмена то появится звезда - баг в функции СОХРАНИТЬ КАК
            // или если файл уже сохранен и опять нажать кнопку СОХРАНИТЬ КАК и отмена то опять появится звезда
        }
        else
        {
            fileName = fileSaveName;
            QString fileTitle = changedTitle(fileSaveName);
            setWindowTitle("*" + fileTitle);

        }
    }

}

void MainWindow::on_Menu_Create_triggered() // МЕНЮ СОЗДАТЬ
{
    QString oldPath = this->windowTitle(); //узнали название документа

    if (count(oldPath.begin(), oldPath.end(), "*")) //поиск изменения в документе
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Блокнот");
        msgBox.setText("Вы хотите сохранить изменения в файле \n" + fileName + "?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int res = msgBox.exec();
        switch (res)
        {//какую кнопку нажал юзер
            case QMessageBox::Save:
            {// Нажата кнопка Save
                if (fileExits(fileName)) //если файл существует в системе
                    on_Menu_Save_triggered(); //сохраняем файл в системе
                else //если не существует
                {
                    on_Menu_Save_As_triggered();
                    break;
                }
                setWindowTitle(oldPath.remove("*"));
                on_Menu_Create_triggered(); //вызываем создание еще раз
                break;
            }
            case QMessageBox::Discard:
            {// Нажата кнопка Discard
                this->setWindowTitle(fileName.remove("*")); //убрать "*"
                on_Menu_Create_triggered(); //вызываем создание еще раз
                break;
            }
            case QMessageBox::Cancel:
            {// Нажата кнопка Cancel
                break;
            }
        }
    }
    else //если файл сохранен или он не изменялся
    {
        fileName = "Безымянный - Блокнот"; //изменили fileName
        this->setWindowTitle(fileName); //меняем название документа
        ui->textEdit->clear(); //делаем чистый документ
    }
}

void MainWindow::on_Menu_Save_triggered() // МЕНЮ СОХРАНИТЬ
{
    QString oldPath = this->windowTitle(); // старое название

    if (fileExits(fileName)) // если документ есть в системе
    {
        QFile file(fileName); // читаем название

        if (!file.open(QIODevice::WriteOnly)) // если изначально ошибка в файле
        {
            QMessageBox::critical(this, tr("Ошибка"), tr("Не могу сохранить файл") + file.errorString());
            return;
        }
        else  // нет ошибок
        {
            QString fileTitle = changedTitle(oldPath.remove("*")); // изменяем название окна (убираем звездочку при каждом сохранении
            QTextStream in(&file); // сохранение текста
            in.setCodec("UTF-8"); // ставим кодек utf-8
            in << ui->textEdit->toPlainText();
            file.close(); // закрыли файл
            setWindowTitle(fileTitle); // изменили название окна
        }
    }

    else // если файла еще нет в системе(не сохранялся)
    {
        on_Menu_Save_As_triggered(); // то Сохранить как
    }
}


// кнопки

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

// функции

void MainWindow::on_textEdit_textChanged() // звездочка при изменении документа
{
    QString fileTitle = changedTitle(fileName);

//    if(!fileExits(fileName)) // если документа не существует в системе
//    {
//        if (ui->textEdit->toPlainText().length() == 0) // если документ пустой
//            this->setWindowTitle(fileTitle.remove("*")); // ставим заголовок и убираем звездочку
//        else //если в документе что то написано
//            this->setWindowTitle("*" + fileTitle); // добавляем к названию звездочку
//    }
    //else // если документ существует в системе (сохранен)
    //{
    if(ui->textEdit->toPlainText().length() == 0) // считывае документ кодировкой и проверяем на text(пустую строку)
        this->setWindowTitle(fileTitle.remove("*")); // если равен text - документ пуст - убираем звезду
    else // если документ не пустой
        this->setWindowTitle("*" + fileTitle); // добавляем звезлу
    //}
}

void MainWindow::closeEvent(QCloseEvent *event) //ОБРАБОТЧИК ЗАКРЫТИЯ ФОРМЫ
{
    QString oldPath = windowTitle(); // old path

    if (!count(oldPath.begin(), oldPath.end(), "*")) // если в названии нет звездочки, то файл не изменен(пустой), значит можно просто закрыть
        event->accept();
    else // если звезды нет, то
    {
        QMessageBox quastion;
        quastion.setWindowTitle("Блокнот");
        quastion.setText("Вы хотите сохранить изменения в файле? \n" + fileName + "?");
        quastion.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        quastion.setDefaultButton(QMessageBox::Save);
        int res = quastion.exec();
        switch (res)
        {
            case QMessageBox::Save:
            {
                if (fileExits(fileName))
                    on_Menu_Save_triggered();
                else
                    on_Menu_Save_As_triggered();
                break;
            }
            case QMessageBox::Discard:
            {
                event->accept();
                break;
            }
            case QMessageBox::Cancel:
            {
                event->ignore();
                break;
            }
        }
    }
}

