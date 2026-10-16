/******************************************************************************
 * NAME:    main.cpp
 *
 * PURPOSE: Searchmonkey program entry point.
 *
 * DATE:    October 18, 2009
 *
 * REVISIONS:
 * ---------
 * [101809] adamc- initial coding.
 * [120609] shawno- preprocessor directives
 * [030110] shawno- debug stuff
*******************************************************************************/
#include <iostream>
#include <QApplication>
#include <QCommandLineParser>
#include <QFileInfo>
#include "mainwindow.h"

#ifndef QT_NO_CONCURRENT

bool ABORT_COUNTING_HITS,
	  LEVEL[10];  // debug levels

int main  (int argc, char *argv[]) {
	ABORT_COUNTING_HITS = false;
	LEVEL[0] = 1;
	LEVEL[1] = 1;
	LEVEL[2] = 1;
	LEVEL[3] = 1;
	LEVEL[4] = 0;
	LEVEL[5] = 0;
	LEVEL[6] = 1;
	LEVEL[7] = 0;
	LEVEL[8] = 0;
	LEVEL[9] = 0;
	QApplication a(argc, argv);
	QCommandLineParser parser;
	parser.addHelpOption();
	parser.addPositionalArgument("directory", "Folder to search", "[directory]");
	parser.process(a);
	const QStringList arguments = parser.positionalArguments();
	if (arguments.size() > 1 ||
	    (!arguments.isEmpty() && !QFileInfo(arguments.first()).isDir())) {
		std::cerr << "Expected one existing directory.\n";
		return 1;
	}
	MainWindow w;
	w.setWindowTitle("Searchmonkey II (Qt 6)");
	if (!arguments.isEmpty()) {
		const QString directory = QFileInfo(arguments.first()).absoluteFilePath();
		w.getUi()->quickDirectoryLineEdit->setText(directory);
		w.getUi()->directoryLineEdit->setText(directory);
	}
	w.show();
	return a.exec();
}

#else

int main() {
	qDebug()  << "Qt Concurrent is not yet supported on this platform.";
	std::cerr << "Qt Concurrent is not yet supported on this platform.";
}

#endif
