#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog> // Библиотека с диалоговыми окнами для работы с файлами
#include <QMessageBox>
#include <QCloseEvent> // библиотека с функциями обработчика закрытия окна
#include <QTextStream>
#include <QFile>


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


    void SetText(const QString &name);


private:
    Ui::MainWindow *ui;

    bool is_modified = false;
    bool is_saved = false;


};

#endif // MAINWINDOW_H
