#ifndef STRIPE_H
#define STRIPE_H

#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QStringList>

class Stripe : public QWidget
{
public:
	Stripe(QWidget *parent = 0);
	void setFont(const QFont &);
	void setFontColor(const QColor &);
	void setBackgroundColor(const QColor &);
	void setInterval(int);
	void setDictionary(const QString &);
	const QFont& font();
	const QColor& fontColor();
	const QColor& backgroundColor();
	int interval();
	void exitHandler();
protected:
	void mousePressEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
private:
	QString ini_;
	QString dictionary_;
	QLabel *textstring_;
	QPoint clickpos_;
	int interval_;
	QStringList *textstrings_;
	void runHypno_();
	bool update_;
	bool exit_;
};

#endif // STRIPE_H
