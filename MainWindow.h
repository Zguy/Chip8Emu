#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"
#include "Emulator.h"

#include <QtCore/QElapsedTimer>
#include <QtCore/QTimer>
#include <QtGui/QKeyEvent>
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

private slots:
	void execute();

protected:
	void keyPressEvent(QKeyEvent *e) override;
	void keyReleaseEvent(QKeyEvent *e) override;

private:
	Ui::MainWindow ui;

	Chip8::Emulator emu;
	QTimer executionTimer;
	QElapsedTimer elapsedTimer;
};
}

#endif // MAINWINDOW_H
