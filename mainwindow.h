#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void choose_folder();

    void on_button_next_clicked();

    void on_button_back_clicked();

    void on_button_add_clicked();

    void on_pushButton_show_tegs_clicked();

private:
    void load_image(QImage& image, QLabel& label_image, int i);
    Ui::MainWindow *ui;
    QSplitter* splitter_images;
    QLabel* label_image_back;
    QLabel* label_image_next;
    QLabel* label_image;
    QPicture* first;
    QStringList list_images;
    QStringList list_tegs;
    int index_middle_image;
    QUrl* name_folder;
    bool scroll_to_right;
    bool scroll_to_left;
};
#endif // MAINWINDOW_H
