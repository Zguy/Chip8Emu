#include "DisplayWidget.h"
#include "Display.h"

#include <QtGui/QPainter>

namespace Chip8GUI
{
DisplayWidget::DisplayWidget(QWidget *parent) : QWidget(parent), pixels(nullptr)
{
}
DisplayWidget::~DisplayWidget()
{
}

void DisplayWidget::paintEvent(QPaintEvent*)
{
	using Chip8::Display;
	using Chip8::byte_t;

	qreal scaleX = (static_cast<qreal>(width()) / static_cast<qreal>(Display::WIDTH));
	qreal scaleY = (static_cast<qreal>(height()) / static_cast<qreal>(Display::HEIGHT));

	QPainter painter(this);
	painter.scale(scaleX, scaleY);
	painter.fillRect(0,0,Display::WIDTH,Display::HEIGHT,Qt::black);

	for (unsigned int y = 0; y < Display::HEIGHT; ++y)
	{
		for (unsigned int x = 0; x < Display::WIDTH; ++x)
		{
			byte_t pixel = pixels[y * Display::WIDTH + x];
			if (pixel != 0)
			{
				painter.fillRect(x-1,y-1,1,1,Qt::white);
			}
		}
	}
}
}
