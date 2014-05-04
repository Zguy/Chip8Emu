#include "MainWindow.h"

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtCore/QElapsedTimer>

namespace Chip8GUI
{
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.actionOpen, &QAction::triggered, this, &MainWindow::openROM);
	connect(ui.actionClose, &QAction::triggered, this, &MainWindow::closeROM);

	connect(ui.actionAbout, &QAction::triggered, this, &MainWindow::about);

	ui.display->setPixels(emu.getDisplay().getPixels());
}
MainWindow::~MainWindow()
{
}

void MainWindow::openROM()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open..."));
	if (filename.isNull())
		return;

	emu.open(filename.toStdString());

	QElapsedTimer timer;
	timer.start();

	while (true)
	{
		float elapsedSeconds = static_cast<float>(timer.restart()) / 1000.f;
		emu.step(elapsedSeconds);

		ui.display->update();

		QApplication::processEvents();
	}
}
void MainWindow::closeROM()
{
	emu.close();
}

void MainWindow::about()
{
	QMessageBox::about(this, tr("About Chip8Emu"), tr("Chip-8 Emulator"));
}
}
