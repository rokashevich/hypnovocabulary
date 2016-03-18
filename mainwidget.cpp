#include "mainwidget.h"
#include <QFontDialog>
#include <QColorDialog>
#include <QHBoxLayout>
#include <QFrame>
#include <QIcon>
#include <QProcess>
#include <QDir>
#include <QCoreApplication>

MainWidget::MainWidget(QWidget *parent)
	: QWidget(parent)
{
	QCoreApplication::setApplicationName(tr("HypnoVocabulary"));
	QCoreApplication::setApplicationVersion(VERSION);
	this->setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);

	stripe_ = new Stripe;

	buttonFont_            = new QPushButton(tr("Choose font"));
	buttonFontColor_       = new QPushButton(tr("Choose font color"));
	buttonBackgroundColor_ = new QPushButton(tr("Choose background color"));
	QHBoxLayout *hl1 = new QHBoxLayout;
	buttonOpenDictionary_  = new QPushButton(tr("Open dictionary"));
	buttonReloadDictionary_= new QPushButton(tr("✅"));
	hl1->addWidget(buttonOpenDictionary_);
	hl1->addWidget(buttonReloadDictionary_);

	QHBoxLayout *hl2 = new QHBoxLayout;
	spinboxInterval_ = new QSpinBox();
	spinboxInterval_->setValue(stripe_->interval());
	spinboxInterval_->setRange(1,86400);
	hl2->addWidget(new QLabel(tr("Interval (sec.)")));
	hl2->addWidget(spinboxInterval_);

	QFrame *f = new QFrame();
	f->setFrameShape(QFrame::HLine);
	QLabel *l = new QLabel(tr("HypnoVocabulary")+" "+QString("(%1)").arg(VERSION)+"<br><a href='http://github.com/rokashevich/hypnovocabulary'>github.com/rokashevich/hypnovocabulary</a>");
	l->setOpenExternalLinks(true);

	QVBoxLayout *vl = new QVBoxLayout;
	vl->addWidget(buttonFont_);
	vl->addWidget(buttonFontColor_);
	vl->addWidget(buttonBackgroundColor_);
	vl->addLayout(hl1);
	vl->addLayout(hl2);
	vl->addWidget(f);
	vl->addWidget(l);
	this->setLayout(vl);

	tray_ = new QSystemTrayIcon();
	tray_->setIcon(QIcon(":/hypnovocabulary.ico"));
	tray_->show();

	connect(buttonFont_,            SIGNAL(clicked()), this, SLOT(onButtonFontClicked_()));
	connect(buttonFontColor_,       SIGNAL(clicked()), this, SLOT(onButtonFontColorClicked_()));
	connect(buttonBackgroundColor_, SIGNAL(clicked()), this, SLOT(onButtonBackgroundColorClicked_()));
	connect(buttonOpenDictionary_,  SIGNAL(clicked()), this, SLOT(onButtonOpenDictionary_()));
	connect(buttonReloadDictionary_,  SIGNAL(clicked()), this, SLOT(onButtonReloadDictionary_()));
	connect(tray_,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(toggle(QSystemTrayIcon::ActivationReason)));
	connect(spinboxInterval_,SIGNAL(valueChanged(int)),this,SLOT(onIntervalClicked_(int)));
}

void MainWidget::onButtonFontClicked_()
{
	bool ok;
	QFont font = QFontDialog::getFont(&ok, stripe_->font(), this);
	if (ok) stripe_->setFont(font);
}
void MainWidget::onButtonFontColorClicked_()
{
	QColor color = QColorDialog::getColor(stripe_->fontColor());
	if (color.isValid()) stripe_->setFontColor(color);
}
void MainWidget::onButtonBackgroundColorClicked_()
{
	QColor color = QColorDialog::getColor(stripe_->backgroundColor());
	if (color.isValid()) stripe_->setBackgroundColor(color);
}

void MainWidget::onButtonOpenDictionary_()
{
	QString s = QDir::toNativeSeparators(QFileInfo(QCoreApplication::applicationFilePath()).absoluteDir().absolutePath())+QDir::separator()+"dictionary.txt";
	QProcess *proc = new QProcess(this);
	proc->start("notepad.exe "+s);
}

void MainWidget::onButtonReloadDictionary_()
{
	QString s = "dictionary.txt";
	stripe_->setDictionary(s);
}

void MainWidget::onIntervalClicked_(int i)
{
	stripe_->setInterval(i);
}

void MainWidget::toggle(QSystemTrayIcon::ActivationReason r) {
	if (r==QSystemTrayIcon::Trigger)
	{
		if (!this->isVisible())
		{
			this->show();
			this->setFocusPolicy(Qt::StrongFocus);
		} else
		{
			this->hide();
		}
	}
}

void MainWidget::exitHandler()
{
	tray_->hide();
	stripe_->exitHandler();
}
