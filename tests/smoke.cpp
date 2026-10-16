#include "mainwindow.h"
#include "settings.h"
#include "tabresults.h"
#include "ui_settings.h"
#include "ui_tabresults.h"
#include <QApplication>
#include <QFile>
#include <QStandardItemModel>
#include <QTemporaryDir>
#include <QTextEdit>
#include <cassert>
#include <cstdio>

bool ABORT_COUNTING_HITS = false;
bool LEVEL[10] = {};

int main(int argc, char **argv) {
    QTemporaryDir temporary;
    assert(temporary.isValid());
    qputenv("HOME", temporary.path().toUtf8());
    qputenv("XDG_CONFIG_HOME", (temporary.path() + "/config").toUtf8());
    QApplication app(argc, argv);
    assert(QDir::setCurrent(temporary.path()));
    for (const auto &entry : {qMakePair("alpha file.txt", "needle caf\xc3\xa9\nneedle again\n"),
                              qMakePair("beta.txt", "one needle\n"),
                              qMakePair("quiet.log", "nothing here\n")}) {
        QFile file(entry.first);
        assert(file.open(QIODevice::WriteOnly));
        assert(file.write(entry.second) == qint64(qstrlen(entry.second)));
    }
    MainWindow window;
    auto *ui = window.getUi();
    window.getSui()->ui()->tabCheckBox->setChecked(false);
    ui->quickDirectoryLineEdit->setText(temporary.path());
    ui->quickFileLineEdit->setText("*.txt");
    ui->quickContentLineEdit->setText("needle");
    window.find();
    auto *tab = qobject_cast<TabResults *>(ui->resultsTabWidget->currentWidget());
    assert(tab && tab->getModelPtr()->rowCount() == 2);
    auto *model = tab->getModelPtr();
    assert(model->columnCount() == 5);
    int hits = 0;
    for (int row = 0; row < model->rowCount(); ++row)
        hits += model->index(row, 2).data().toInt();
    assert(hits == 3);
    auto *view = tab->tui()->proxyViewV;
    view->selectionModel()->select(view->model()->index(0, 0),
        QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
    assert(tab->tui()->lineDisplayV->toPlainText().contains("needle"));
    window.resize(1200, 800);
    window.show();
    app.processEvents();
    assert(argc == 2 && window.grab().save(QString::fromLocal8Bit(argv[1])));
    ui->quickContentLineEdit->setText(QString::fromUtf8("caf\xc3\xa9"));
    window.find();
    assert(tab->getModelPtr()->rowCount() == 1);
    ui->quickContentLineEdit->setText("not-present");
    window.find();
    assert(tab->getModelPtr()->rowCount() == 0);
    ui->quickContentLineEdit->clear();
    window.find();
    assert(tab->getModelPtr()->rowCount() == 2);
    ui->sizeComboBox->setCurrentIndex(1);
    assert(ui->sizeLineEdit->isEnabled());
    ui->dateTimeComboBox->setCurrentIndex(1);
    assert(ui->dateTimeEdit->isEnabled());
    std::puts("PASS: file rows, hit counts, preview, no matches and filename-only search");
}
