#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include "Types.h"

#include <QtWidgets/QWidget>

namespace Chip8GUI
{
class DisplayWidget : public QWidget
{
	Q_OBJECT
public:
	explicit DisplayWidget(QWidget *parent = nullptr);
	~DisplayWidget();

	void setPixels(const Chip8::byte_t *pixels) { this->pixels = pixels; }

protected:
	void paintEvent(QPaintEvent*) override;

private:
	const Chip8::byte_t *pixels;
};
}

#endif // DISPLAYWIDGET_H
