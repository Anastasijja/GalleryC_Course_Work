#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

QImage image;
QImage image_back;
QImage image_next;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    splitter_images = new QSplitter();
    name_folder = new QUrl();

    label_image = new QLabel();
    label_image_next = new QLabel();
    label_image_back = new QLabel();

    scroll_to_right = false;
    scroll_to_left = false;

    splitter_images->addWidget(label_image);
    splitter_images->addWidget(label_image_next);
    splitter_images->addWidget(label_image_back);

    ui->images->addWidget(label_image_back);
    ui->images->addWidget(label_image);
    ui->images->addWidget(label_image_next);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete splitter_images;
    delete label_image;
    delete name_folder;
}

void MainWindow::load_image(QImage& image, QLabel& label_image, int i)
{
    QString path = name_folder->toString() + "/" + list_images[i];
    bool d = image.load(path);
    if (d)
    {
        image = image.scaledToWidth(label_image.width(), Qt::SmoothTransformation);
        label_image.setPixmap(QPixmap::fromImage(image));
    }
}

void MainWindow::choose_folder()
{
    name_folder->setUrl(QFileDialog::getExistingDirectory(this, tr("Choose folder")));
    QDir directory(name_folder->toString());
    QStringList images = directory.entryList(QStringList() << "*.jpg" <<"*.bmp" << "*.gif"<< "*.GIF"<< "*.png" << "*.PNG" <<"*.JPG" << "*.jpeg", QDir::Files);

    for (int i = 0; i < images.size(); i++) {
        list_images.insert(i, images[i]);
        list_tegs.insert(i, "");
    }

    QString path = name_folder->toString() + "/" + list_images[0];
    bool d = image.load(path);
    if (d)
    {
        image = image.scaledToWidth(label_image->width(), Qt::SmoothTransformation);
        label_image->setPixmap(QPixmap::fromImage(image));
    }

    switch (list_images.size())
    {
    case 3:
    {
        load_image(image_next, *label_image_next, 2);
    }
    case 2:
    {
        load_image(image, *label_image, 1);
    }
    case 1:
    {
        load_image(image_back, *label_image_back, 0);
        ui->button_next->setEnabled(false);
        ui->button_back->setEnabled(false);
        break;
    }
    case 0:
        QMessageBox::warning(this, "Warning", "There is no pictures in the folder");
    default:
    {
        load_image(image_next, *label_image_next, 2);
        load_image(image, *label_image, 1);
        load_image(image_back, *label_image_back, 0);
    }
    }

    index_middle_image = 1;
    repaint();
}



void MainWindow::on_button_next_clicked()
{
    ui->lineEdit_tegs->clear();
    if (index_middle_image + 2 < list_images.size()) {
        index_middle_image = index_middle_image + 1;
        load_image(image_next, *label_image_next, index_middle_image + 1);
        load_image(image, *label_image, index_middle_image);
        load_image(image_back, *label_image_back, index_middle_image - 1);
    }

    else
    {
        if (scroll_to_right)
        {
            scroll_to_right = false;
            index_middle_image = 0;
            load_image(image_next, *label_image_next, index_middle_image + 1);
            load_image(image, *label_image, index_middle_image);
            load_image(image_back, *label_image_back, list_images.size() - 1);
        }
        else
        {
            scroll_to_right = true;
            index_middle_image = list_images.size() - 1;
            load_image(image_next, *label_image_next, 0);
            load_image(image, *label_image, index_middle_image);
            load_image(image_back, *label_image_back, index_middle_image - 1);
        }
    }
    ui->lineEdit_tegs->setText(list_tegs[index_middle_image]);
}

void MainWindow::on_button_back_clicked()
{
    ui->lineEdit_tegs->clear();
    if (index_middle_image > 1) {
        index_middle_image = index_middle_image - 1;
        load_image(image_next, *label_image_next, index_middle_image + 1);
        load_image(image, *label_image, index_middle_image);
        load_image(image_back, *label_image_back, index_middle_image - 1);
    }
    else
    {
        if (scroll_to_left) {
            scroll_to_left = false;
            index_middle_image = list_images.size() - 1;
            load_image(image_next, *label_image_next, 0);
            load_image(image, *label_image, index_middle_image);
            load_image(image_back, *label_image_back, index_middle_image - 1);
        }
        else {

            scroll_to_left = true;
            index_middle_image = 0;
            load_image(image_next, *label_image_next, 1);
            load_image(image, *label_image, index_middle_image);
            load_image(image_back, *label_image_back, list_images.size() - 1);
        }
    }
    ui->lineEdit_tegs->setText(list_tegs[index_middle_image]);

}

void MainWindow::on_button_add_clicked()
{
    ui->lineEdit_tegs->clear();
    list_tegs[index_middle_image] = list_tegs[index_middle_image] + (ui->lineEdit_add_tegs->displayText()) + " ";
    ui->lineEdit_tegs->setText(list_tegs[index_middle_image]);
    ui->lineEdit_add_tegs->clear();
}

void MainWindow::on_pushButton_show_tegs_clicked()
{
    ui->lineEdit_add_tegs->clear();
    list_tegs[index_middle_image] = "";
    ui->lineEdit_tegs->clear();
}
