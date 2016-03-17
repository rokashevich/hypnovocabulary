#include "stripe.h"

#include <QMouseEvent>
#include <QVBoxLayout>
#include <QPalette>
#include <QSettings>
#include <QDir>
#include <QCoreApplication>
#include <QTConcurrent>
#include <QThread>
#include <QDebug>
#include <QFile>
#include <QTextStream>

Stripe::Stripe(QWidget *parent)
	: QWidget(parent, Qt::Dialog)
{
	ini_ = QDir::toNativeSeparators(QFileInfo(QCoreApplication::applicationFilePath()).absoluteDir().absolutePath())+QDir::separator()+"settings.ini";
	textstring_ = new QLabel(tr("HypnoVocabulary"));
	textstrings_ = new QStringList;
	update_ = true;
	exit_ = false;
	QVBoxLayout *l = new QVBoxLayout;
	l->addWidget(textstring_);
	this->setLayout(l);
	this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::Tool);
	QSettings settings(ini_, QSettings::IniFormat);
	this->setFont(QFont(settings.value("font-family").toString(), settings.value("font-size","16").toInt(), settings.value("font-weight").toInt()));
	this->setFontColor(QColor(settings.value("font-color","#ffff00").toString()));
	this->setBackgroundColor(QColor(settings.value("background-color","#333333").toString()));
	this->setInterval(settings.value("interval","1").toInt());
	this->setDictionary("dictionary.txt");
	QtConcurrent::run(this, &Stripe::runHypno_);
}

void Stripe::setFont(const QFont &font)
{
	textstring_->setFont(font);
	QSettings settings(ini_, QSettings::IniFormat);
	settings.setValue("font-family", font.family());
	settings.setValue("font-size", font.pointSize());
	settings.setValue("font-weight", font.weight());
}
void Stripe::setFontColor(const QColor &color)
{
	QPalette p = textstring_->palette();
	p.setColor(textstring_->foregroundRole(), color);
	textstring_->setPalette(p);
	QSettings settings(ini_, QSettings::IniFormat);
	settings.setValue("font-color", color.name());
}
void Stripe::setBackgroundColor(const QColor &color)
{
	QPalette p = this->palette();
	p.setColor(this->backgroundRole(), color);
	this->setPalette(p);
	QSettings settings(ini_, QSettings::IniFormat);
	settings.setValue("background-color", color.name());
}

void Stripe::setInterval(int i)
{
	if (i==0) i=1;
	interval_ = i;
	QSettings settings(ini_, QSettings::IniFormat);
	settings.setValue("interval", i);
}

void Stripe::setDictionary(const QString &s)
{
	dictionary_ = QDir::toNativeSeparators(QFileInfo(QCoreApplication::applicationFilePath()).absoluteDir().absolutePath())+QDir::separator()+s;
	textstrings_->clear();
	QFile f(dictionary_);
	if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	QTextStream textStream(&f);
	while (!textStream.atEnd())
	{
		QString line = textStream.readLine();
		line = line.trimmed();
		if (!line.isEmpty())
		{
			textstrings_->append(line);
		}
	}
	update_ = true;
	QSettings settings(ini_, QSettings::IniFormat);
	settings.setValue("dictionary", s);
}

void Stripe::runHypno_()
{
	QThread::sleep(5);
	int i = 0;
	int len = 0;
	while(!exit_)
	{
		if (update_)
		{
			i = 0;
			len = textstrings_->length();
			update_ = false;
		}
		if (len)
		{
			if (i == len) i = 0;
			textstring_->setText(textstrings_->at(i));
			this->activateWindow();
			i++;
		}
		QThread::sleep(interval_);
	}
}

const QFont& Stripe::font(){return textstring_->font();}
const QColor& Stripe::fontColor(){return textstring_->palette().color(textstring_->foregroundRole());}
const QColor& Stripe::backgroundColor(){return this->palette().color(this->backgroundRole());}
int Stripe::interval(){return interval_;}
void Stripe::exitHandler(){exit_ = true;}
void Stripe::mousePressEvent(QMouseEvent *e){if (e->button() == Qt::LeftButton) clickpos_ = e->pos();}
void Stripe::mouseMoveEvent(QMouseEvent *e){if(e->buttons() == Qt::LeftButton)move(mapToParent(e->pos() - clickpos_));}
