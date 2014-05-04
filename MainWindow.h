#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"
#include "Emulator.h"

#include <QtWidgets/QMainWindow>
#include <QtGui/QKeyEvent>

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

protected:
	void keyPressEvent(QKeyEvent *e) override;
	void keyReleaseEvent(QKeyEvent *e) override;

private:
	Ui::MainWindow ui;

	Chip8::Emulator emu;
};
}

#endif // MAINWINDOW_H
