#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include <QSystemTrayIcon>
#include <QCloseEvent>

#include "stripe.h"

class MainWidget : public QWidget
{
	Q_OBJECT

public:
	MainWidget(QWidget *parent = 0);
private:
	Stripe *stripe_;
	QPushButton *buttonFont_;
	QPushButton *buttonFontColor_;
	QPushButton *buttonBackgroundColor_;
	QPushButton *buttonOpenDictionary_;
	QPushButton *buttonReloadDictionary_;
	QSpinBox *spinboxInterval_;
	QSystemTrayIcon *tray_;

private slots:
	void onButtonFontClicked_();
	void onButtonFontColorClicked_();
	void onButtonBackgroundColorClicked_();
	void onButtonOpenDictionary_();
	void onButtonReloadDictionary_();
	void onIntervalClicked_(int);
	void toggle(QSystemTrayIcon::ActivationReason);
	void exitHandler();
};

#endif // MAINWINDOW_H
