#include "mainwindow.h"

#include "./ui_mainwindow.h"

using namespace s21;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  t = new QTimer(this);
  gif_file = nullptr;

  setWindowTitle("3D Viewer");
  ui->MainStackedWidget->setCurrentIndex(I_ONE);
  connect(t, &QTimer::timeout, this, &MainWindow::new_frame);

  openGLWidget = ui->openGLWidget;
  controller.setupOpenGL(openGLWidget);
  updateInfoLabel();
  update_edges();
  update_vertex();
  update_trans();
  update_rotate();
  update_scale();
}

MainWindow::~MainWindow() {
  delete ui;
  delete t;
  if (gif) delete gif;
}

void MainWindow::on_OpenFileButton_clicked() {
  QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "",
                                                  "OBJ files (*.obj)");
  controller.update_model_info(fileName);
  updateInfoLabel();
}

void MainWindow::on_SaveButton_clicked() {
  controller.update_setting_info(true);
}

void MainWindow::on_ScreenButton_clicked() {
  QScreen *screen = QGuiApplication::primaryScreen();
  if (const QWindow *window = windowHandle()) screen = window->screen();
  if (screen) {
    QPixmap pixmap = get_screen();

    QString defaultName =
        QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss") + ".png";
    QString fileName = QFileDialog::getSaveFileName(
        this, tr("Сохранить скриншот"), QDir::homePath() + "/" + defaultName,
        tr("Изображения (*.png *.jpg *.bmp)"));

    if (!fileName.isEmpty()) pixmap.save(fileName);
  }
}

void MainWindow::on_GifButton_clicked() {
  QString defaultName =
      QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss") + ".gif";
  gif_file = QFileDialog::getSaveFileName(this, tr("Сохранить gif"),
                                          QDir::homePath() + "/" + defaultName,
                                          tr("Gif (*.gif)"));

  if (!gif_file.isEmpty()) {
    if (!gif) gif = new QGifImage((QSize(640, 480)));
    ui->GifButton->setEnabled(false);
    ui->SaveButton->setEnabled(false);
    ui->OpenFileButton->setEnabled(false);
    ui->ScreenButton->setEnabled(false);
    t->start(100);
  }
}

void MainWindow::on_BackgroundColorButton_clicked() {
  QColor color = QColorDialog::getColor();
  controller.update_setting_info(color);
}

void MainWindow::on_VertexButton_clicked() {
  ui->MainStackedWidget->setCurrentIndex(I_THREE);
  update_vertex();
}

void MainWindow::on_EdgesButton_clicked() {
  ui->MainStackedWidget->setCurrentIndex(I_TWO);
  update_edges();
}

void MainWindow::on_TransposeScrollBar_x_valueChanged(int value) {
  ui->TransposeLineEdit_x->setText(QString::number(value));
  controller.update_model_info('t', 'x', value);
  updateInfoLabel();
}

void MainWindow::on_TransposeScrollBar_y_valueChanged(int value) {
  ui->TransposeLineEdit_y->setText(QString::number(value));
  controller.update_model_info('t', 'y', value);
  updateInfoLabel();
}

void MainWindow::on_TransposeScrollBar_z_valueChanged(int value) {
  ui->TransposeLineEdit_z->setText(QString::number(value));
  controller.update_model_info('t', 'z', value);
  updateInfoLabel();
}

void MainWindow::on_TransposeLineEdit_x_textChanged(const QString &text) {
  bool ok;
  int value = text.toInt(&ok);
  if (ok && value >= 0 && value <= 100) {
    ui->TransposeScrollBar_x->setValue(value);
    controller.update_model_info('t', 'x', value);
    updateInfoLabel();
  }
}

void MainWindow::on_TransposeLineEdit_y_textChanged(const QString &text) {
  bool ok;
  int value = text.toInt(&ok);
  if (ok && value >= 0 && value <= 100) {
    ui->TransposeScrollBar_y->setValue(value);
    controller.update_model_info('t', 'y', value);
    updateInfoLabel();
  }
}

void MainWindow::on_TransposeLineEdit_z_textChanged(const QString &text) {
  bool ok;
  int value = text.toInt(&ok);
  if (ok && value >= 0 && value <= 100) {
    ui->TransposeScrollBar_z->setValue(value);
    controller.update_model_info('t', 'z', value);
    updateInfoLabel();
  }
}

void MainWindow::on_RotateScrollBar_x_valueChanged(int value) {
  ui->RotateLineEdit_x->setText(QString::number(value));
  controller.update_model_info('r', 'x', value);
  updateInfoLabel();
}

void MainWindow::on_RotateScrollBar_y_valueChanged(int value) {
  ui->RotateLineEdit_y->setText(QString::number(value));
  controller.update_model_info('r', 'y', value);
  updateInfoLabel();
}

void MainWindow::on_RotateScrollBar_z_valueChanged(int value) {
  ui->RotateLineEdit_z->setText(QString::number(value));
  controller.update_model_info('r', 'z', value);
  updateInfoLabel();
}

void MainWindow::on_RotateLineEdit_x_textChanged(const QString &text) {
  bool ok;
  int value = text.toInt(&ok);
  if (ok && value >= 0 && value <= 360) {
    ui->RotateScrollBar_x->setValue(value);
    controller.update_model_info('r', 'x', value);
    updateInfoLabel();
  }
}

void MainWindow::on_RotateLineEdit_y_textChanged(const QString &text) {
  bool ok;
  int value = text.toInt(&ok);
  if (ok && value >= 0 && value <= 360) {
    ui->RotateScrollBar_y->setValue(value);
    controller.update_model_info('r', 'y', value);
    updateInfoLabel();
  }
}

void MainWindow::on_RotateLineEdit_z_textChanged(const QString &text) {
  bool ok;
  int value = text.toInt(&ok);
  if (ok && value >= 0 && value <= 360) {
    ui->RotateScrollBar_z->setValue(value);
    controller.update_model_info('r', 'z', value);
    updateInfoLabel();
  }
}

void MainWindow::on_ScaleScrollBar_valueChanged(int value) {
  ui->ScaleLineEdit->setText(QString::number(value));
  controller.update_model_info(value);
  updateInfoLabel();
}

void MainWindow::on_ScaleLineEdit_textChanged(const QString &text) {
  bool ok;
  int value = text.toInt(&ok);
  if (ok && value >= 0 && value <= 100) {
    ui->ScaleScrollBar->setValue(value);
    controller.update_model_info(value);
    updateInfoLabel();
  }
}

void MainWindow::on_CancelEdgesButton_clicked(QAbstractButton *button) {
  controller.update_setting_info(
      ui->CancelEdgesButton->standardButton(button) == QDialogButtonBox::Ok,
      ui->SolidEdgesRadioButton->isChecked(), std::move(temp),
      ui->SizeEdgesScrollBar->value());
  updateInfoLabel();
  update_trans();
  update_rotate();
  update_scale();
  ui->MainStackedWidget->setCurrentIndex(I_ONE);
}

void MainWindow::on_ColorEdgesButton_clicked() {
  QColor color = QColorDialog::getColor();
  if (color.isValid()) {
    QString colorStr = color.name();
    temp = std::make_unique<std::string>(colorStr.toStdString());
  }
}

void MainWindow::on_SizeEdgesScrollBar_valueChanged(int value) {
  ui->EdgesLineEdit->setText(QString::number(value));
}

void MainWindow::on_EdgesLineEdit_textChanged(const QString &text) {
  bool ok;
  int value = text.toInt(&ok);
  if (ok && value >= 1 && value <= 10) {
    ui->SizeEdgesScrollBar->setValue(value);
  }
}

void MainWindow::on_CancelVertexButton_clicked(QAbstractButton *button) {
  controller.update_setting_info(
      ui->CancelVertexButton->standardButton(button) == QDialogButtonBox::Ok,
      ui->NoneVertexRadioButton->isChecked(),
      ui->CercleVertexRadioButton->isChecked(),
      ui->SquareVertexRadioButton->isChecked(), std::move(temp),
      ui->SizeVertexScrollBar->value());
  updateInfoLabel();
  update_trans();
  update_rotate();
  update_scale();
  ui->MainStackedWidget->setCurrentIndex(I_ONE);
}

void MainWindow::on_ColorVertexButton_clicked() {
  QColor color = QColorDialog::getColor();
  if (color.isValid()) {
    QString colorStr = color.name();
    temp = std::make_unique<std::string>(colorStr.toStdString());
  }
}

void MainWindow::on_SizeVertexScrollBar_valueChanged(int value) {
  ui->VertexLineEdit->setText(QString::number(value));
}

void MainWindow::on_VertexLineEdit_textChanged(const QString &text) {
  bool ok;
  int value = text.toInt(&ok);
  if (ok && value >= 1 && value <= 100) {
    ui->SizeVertexScrollBar->setValue(value);
  }
}

void MainWindow::on_ParallelButton_clicked() {
  controller.update_setting_info(V_PARALLEL);
  updateInfoLabel();
}

void MainWindow::on_CenterButton_clicked() {
  controller.update_setting_info(V_CENTER);
  updateInfoLabel();
}

void MainWindow::updateOpenGLWidget() { openGLWidget->update(); }

QPixmap MainWindow::get_screen() {
  QScreen *screen = QGuiApplication::primaryScreen();
  const QWindow *window = windowHandle();
  screen = window ? window->screen() : screen;

  return screen ? screen->grabWindow(winId(), ui->openGLWidget->x() + 9,
                                     ui->openGLWidget->y() + 9,
                                     ui->openGLWidget->width(),
                                     ui->openGLWidget->height())
                : QPixmap();
}

void MainWindow::new_frame() {
  static int counter = 0;
  QPixmap pixmap = get_screen();
  if (!pixmap.isNull()) {
    QImage image = pixmap.toImage();
    gif->addFrame(image);
    gif->setDefaultDelay(100);
  }
  counter++;

  if (counter == 50) {
    counter = 0;
    gif->save(gif_file);
    t->stop();
    ui->GifButton->setEnabled(true);
    ui->SaveButton->setEnabled(true);
    ui->OpenFileButton->setEnabled(true);
    ui->ScreenButton->setEnabled(true);
    QMessageBox::information(this, tr("Уведомление"),
                             tr("Запись gif завершена"));
    delete gif;
    gif = nullptr;
  }
}

void MainWindow::updateInfoLabel() {
  QString info;
  info += QString("Файл: %1\n")
              .arg(controller.get_filename() ? [](const std::string &path) {
                std::filesystem::path filepath(path);
                return QString::fromStdString(filepath.filename().string());
              }(*controller.get_filename())
                                             : "Не выбран");

  info += QString("Вершины: %1\n").arg(controller.get_vertices());
  info += QString("Рёбра: %1\n\n").arg(controller.get_edges());
  info += QString("Масштаб: %1\n").arg(controller.get_scale());
  info += QString("Смещение: (%1, %2, %3)\n")
              .arg(controller.get_trans_x())
              .arg(controller.get_trans_y())
              .arg(controller.get_trans_z());
  info += QString("Поворот: (%1, %2, %3)\n\n")
              .arg(controller.get_rotate_x())
              .arg(controller.get_rotate_y())
              .arg(controller.get_rotate_z());
  info += QString("Тип проекции: %1\n\n")
              .arg(!controller.get_projection_type() ? "Параллельная"
                                                     : "Центральная");

  info += QString("Тип рёбер: %1\n")
              .arg(!controller.get_edges_type() ? "Сплошные" : "Пунктирные");
  info += QString("Толщина рёбер: %1\n\n").arg(controller.get_edge_thickness());

  info += QString("Тип вершин: %1\n")
              .arg(!controller.get_vertex_type()            ? "Нет"
                   : controller.get_vertex_type() == CERCLE ? "Круг"
                                                            : "Квадрат");
  info += QString("Размер вершин: %1\n").arg(controller.get_vertex_size());

  ui->InfoLabel->setText(info);
}

void MainWindow::update_edges() {
  ui->SizeEdgesScrollBar->setValue(controller.get_edge_thickness());
  ui->EdgesLineEdit->setText(QString::number(controller.get_edge_thickness()));
}

void MainWindow::update_vertex() {
  ui->SizeVertexScrollBar->setValue(controller.get_vertex_size());
  ui->VertexLineEdit->setText(QString::number(controller.get_vertex_size()));
}

void MainWindow::update_trans() {
  ui->TransposeScrollBar_x->setValue(controller.get_trans_x());
  ui->TransposeLineEdit_x->setText(QString::number(controller.get_trans_x()));
  ui->TransposeScrollBar_y->setValue(controller.get_trans_y());
  ui->TransposeLineEdit_y->setText(QString::number(controller.get_trans_y()));
  ui->TransposeScrollBar_z->setValue(controller.get_trans_z());
  ui->TransposeLineEdit_z->setText(QString::number(controller.get_trans_z()));
}

void MainWindow::update_rotate() {
  ui->RotateScrollBar_x->setValue(controller.get_rotate_x());
  ui->RotateLineEdit_x->setText(QString::number(controller.get_rotate_x()));
  ui->RotateScrollBar_y->setValue(controller.get_rotate_y());
  ui->RotateLineEdit_y->setText(QString::number(controller.get_rotate_y()));
  ui->RotateScrollBar_z->setValue(controller.get_rotate_z());
  ui->RotateLineEdit_z->setText(QString::number(controller.get_rotate_z()));
}

void MainWindow::update_scale() {
  ui->ScaleScrollBar->setValue(controller.get_scale());
  ui->ScaleLineEdit->setText(QString::number(controller.get_scale()));
}

void MainWindow::setupConnections() {
  connect(ui->BackgroundColorButton, &QPushButton::clicked, this,
          &MainWindow::on_BackgroundColorButton_clicked);
  connect(ui->OpenFileButton, &QPushButton::clicked, this,
          &MainWindow::on_OpenFileButton_clicked);
  connect(ui->SaveButton, &QPushButton::clicked, this,
          &MainWindow::on_SaveButton_clicked);
  connect(ui->ScreenButton, &QPushButton::clicked, this,
          &MainWindow::on_ScreenButton_clicked);
  connect(ui->GifButton, &QPushButton::clicked, this,
          &MainWindow::on_GifButton_clicked);
  connect(ui->VertexButton, &QPushButton::clicked, this,
          &MainWindow::on_VertexButton_clicked);
  connect(ui->EdgesButton, &QPushButton::clicked, this,
          &MainWindow::on_EdgesButton_clicked);

  connect(ui->TransposeScrollBar_x, &QScrollBar::valueChanged, this,
          &MainWindow::on_TransposeScrollBar_x_valueChanged);
  connect(ui->TransposeLineEdit_x, &QLineEdit::textChanged, this,
          &MainWindow::on_TransposeLineEdit_x_textChanged);
  connect(ui->TransposeScrollBar_y, &QScrollBar::valueChanged, this,
          &MainWindow::on_TransposeScrollBar_y_valueChanged);
  connect(ui->TransposeLineEdit_y, &QLineEdit::textChanged, this,
          &MainWindow::on_TransposeLineEdit_y_textChanged);
  connect(ui->TransposeScrollBar_z, &QScrollBar::valueChanged, this,
          &MainWindow::on_TransposeScrollBar_z_valueChanged);
  connect(ui->TransposeLineEdit_z, &QLineEdit::textChanged, this,
          &MainWindow::on_TransposeLineEdit_z_textChanged);

  connect(ui->RotateScrollBar_x, &QScrollBar::valueChanged, this,
          &MainWindow::on_RotateScrollBar_x_valueChanged);
  connect(ui->RotateLineEdit_x, &QLineEdit::textChanged, this,
          &MainWindow::on_RotateLineEdit_x_textChanged);
  connect(ui->RotateScrollBar_y, &QScrollBar::valueChanged, this,
          &MainWindow::on_RotateScrollBar_y_valueChanged);
  connect(ui->RotateLineEdit_y, &QLineEdit::textChanged, this,
          &MainWindow::on_RotateLineEdit_y_textChanged);
  connect(ui->RotateScrollBar_z, &QScrollBar::valueChanged, this,
          &MainWindow::on_RotateScrollBar_z_valueChanged);
  connect(ui->RotateLineEdit_z, &QLineEdit::textChanged, this,
          &MainWindow::on_RotateLineEdit_z_textChanged);

  connect(ui->ScaleScrollBar, &QScrollBar::valueChanged, this,
          &MainWindow::on_ScaleScrollBar_valueChanged);
  connect(ui->ScaleLineEdit, &QLineEdit::textChanged, this,
          &MainWindow::on_ScaleLineEdit_textChanged);

  connect(ui->CancelEdgesButton, &QDialogButtonBox::clicked, this,
          &MainWindow::on_CancelEdgesButton_clicked);
  connect(ui->ColorEdgesButton, &QPushButton::clicked, this,
          &MainWindow::on_ColorEdgesButton_clicked);
  connect(ui->SizeEdgesScrollBar, &QScrollBar::valueChanged, this,
          &MainWindow::on_SizeEdgesScrollBar_valueChanged);
  connect(ui->EdgesLineEdit, &QLineEdit::textChanged, this,
          &MainWindow::on_EdgesLineEdit_textChanged);

  connect(ui->CancelVertexButton, &QDialogButtonBox::clicked, this,
          &MainWindow::on_CancelVertexButton_clicked);
  connect(ui->ColorVertexButton, &QPushButton::clicked, this,
          &MainWindow::on_ColorVertexButton_clicked);
  connect(ui->SizeVertexScrollBar, &QScrollBar::valueChanged, this,
          &MainWindow::on_SizeVertexScrollBar_valueChanged);
  connect(ui->VertexLineEdit, &QLineEdit::textChanged, this,
          &MainWindow::on_VertexLineEdit_textChanged);

  connect(ui->ParallelButton, &QPushButton::clicked, this,
          &MainWindow::on_ParallelButton_clicked);
  connect(ui->CenterButton, &QPushButton::clicked, this,
          &MainWindow::on_CenterButton_clicked);
}