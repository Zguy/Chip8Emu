#include "MainWindow.h"
#include "Emulator.h"
#include "Random.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	Random::setRandomSeed();

	QApplication a(argc, argv);

	Chip8GUI::MainWindow w;
	w.show();

	return a.exec();
}
