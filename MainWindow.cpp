#include "MainWindow.h"

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

#include <assert.h>

namespace
{
Chip8::byte_t qtToEmu(int key, bool *ok)
{
	assert(ok != nullptr);
	(*ok) = true;
	switch (key)
	{
	case Qt::Key_1: return 0x1;
	case Qt::Key_2: return 0x2;
	case Qt::Key_3: return 0x3;
	case Qt::Key_4: return 0xC;
	case Qt::Key_Q: return 0x4;
	case Qt::Key_W: return 0x5;
	case Qt::Key_E: return 0x6;
	case Qt::Key_R: return 0xD;
	case Qt::Key_A: return 0x7;
	case Qt::Key_S: return 0x8;
	case Qt::Key_D: return 0x9;
	case Qt::Key_F: return 0xE;
	case Qt::Key_Z: return 0xA;
	case Qt::Key_X: return 0x0;
	case Qt::Key_C: return 0xB;
	case Qt::Key_V: return 0xF;
	default: (*ok) = false; return 0x0;
	}
}
}

namespace Chip8GUI
{
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.actionOpen, &QAction::triggered, this, &MainWindow::openROM);
	connect(ui.actionClose, &QAction::triggered, this, &MainWindow::closeROM);

	connect(ui.actionAbout, &QAction::triggered, this, &MainWindow::about);

	executionTimer.setInterval(0);
	connect(&executionTimer, &QTimer::timeout, this, &MainWindow::execute);

	ui.display->setPixels(emu.getDisplay().getPixels());

	QAudioFormat format;
	format.setSampleRate(48000);
	format.setChannelCount(1);
	format.setSampleSize(8);
	format.setCodec("audio/pcm");
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setSampleType(QAudioFormat::SignedInt);

	emu.getSound().setSampleRate(format.sampleRate());
	soundDevice.setInput(&emu.getSound());
	soundDevice.open(QIODevice::ReadOnly);

	audioOutput = new QAudioOutput(format, this);
	audioOutput->start(&soundDevice);
}
MainWindow::~MainWindow()
{
}

void MainWindow::openROM()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open..."), QString(), tr("Chip-8 ROM (*.ch8);;All files (*.*)"));
	if (filename.isNull())
		return;

	if (emu.open(filename.toStdString()))
	{
		elapsedTimer.start();
		executionTimer.start();
	}
}
void MainWindow::closeROM()
{
	emu.close();
	ui.display->update();

	executionTimer.stop();
}

void MainWindow::about()
{
	QMessageBox::about(this, tr("About Chip8Emu"), tr("Chip-8 Emulator"));
}

void MainWindow::execute()
{
	if (elapsedTimer.hasExpired(0))
	{
		float elapsedSeconds = static_cast<float>(elapsedTimer.restart()) / 1000.f;
		emu.step(elapsedSeconds);

		ui.display->update();
	}
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
	bool ok;
	Chip8::byte_t emuKey = qtToEmu(e->key(), &ok);
	if (!ok)
	{
		return QMainWindow::keyPressEvent(e);
	}

	emu.getInput().setPressed(emuKey, true);
}
void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
	bool ok;
	Chip8::byte_t emuKey = qtToEmu(e->key(), &ok);
	if (!ok)
	{
		return QMainWindow::keyReleaseEvent(e);
	}

	emu.getInput().setPressed(emuKey, false);
}
}
