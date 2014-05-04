#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"
#include "Emulator.h"

#include <QtWidgets/QMainWindow>

namespace Chip8GUI
{
class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

public slots:
	void openROM();
	void closeROM();

	void about();

private:
	Ui::MainWindow ui;

	Chip8::Emulator emu;
};
}

#endif // MAINWINDOW_H
