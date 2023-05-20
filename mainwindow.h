#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QFileDialog> // Библиотека с диалоговыми окнами для работы с файлами
#include <QMessageBox>
#include <QCloseEvent> // библиотека с функциями обработчика закрытия окна
#include <QTextStream>
#include <QFile>
#include <QTextEdit>
#include <QString>
#include <iostream>
#include <string>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_Menu_Open_triggered();

    void on_Menu_Save_As_triggered();

    void closeEvent(QCloseEvent *event); // будем изменять обработчик закрытия формы

    void on_Menu_Create_triggered();

    void on_Menu_Save_triggered();

    void on_Menu_Exit_triggered();

    void on_Menu_Cut_triggered();

    void on_Menu_Copy_triggered();

    void on_Menu_Paste_triggered();

    void on_Menu_Undo_triggered();

    void on_Menu_Redo_triggered();

    void on_Menu_About_triggered();



    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;

    QString text = ""; //считывание текста документа для того чтобы проверить пустой ли документ
    QString fileName = "Безымянный - Блокнот"; // считывание названия документа

    bool fileExits(QString path) // функция существования документа в системе
    {
        QFileInfo check_file(path);
        return check_file.exists() && check_file.isFile();
    }

    QString changedTitle(QString path) // обработка пути до названия
    {
        int lastIndex = path.lastIndexOf("/"); // - последний индекс
        QString fileTitle = path; // обрезали до названия документа
        fileTitle = fileTitle.remove(0, lastIndex+1); // изменили название
        return fileTitle;
    }

};

#endif // MAINWINDOW_H
