#include "mainwindow.h"
#include "finddialog.h"
#include "gotocelldialog.h"
#include "sortdialog.h"
#include "spreadsheet.h"
#include "uploaddialog.h"
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QTableWidgetSelectionRange>
#include <QSettings>
#include <QIcon>
#include <QCloseEvent>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>

QStringList MainWindow::recentFiles;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    spreadsheet = new Spreadsheet;
    setCentralWidget(spreadsheet);

    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();

    readSettings();

    findDialog = 0;

    setWindowIcon(QIcon(":/images/icon.png"));
    setCurrentFile("");
    setAttribute(Qt::WA_DeleteOnClose);
}


void MainWindow::createActions()//创建并设置动作
{
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/images/new.png"));//设置图标
    newAction->setShortcut(QKeySequence::New);//设置快捷键
    newAction->setStatusTip(tr("Create a new spreadsheet file"));//设置状态提示
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));//连接动作的信号与槽

    openAction = new QAction(tr("&Open"), this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open a spreadsheet file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/images/save.png"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save a spreadsheet file"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAction = new QAction(tr("Save &As"), this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("Save as a spreadsheet file"));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    printAction = new QAction(tr("&Print"), this);
    printAction->setShortcut(QKeySequence::Print);
    printAction->setIcon(QIcon(":/images/printer.png"));
    printAction->setStatusTip(tr("Print a spreadsheet file"));
    connect(printAction, SIGNAL(triggered()), this, SLOT(print()));


    for(int i = 0; i < MaxRecentFiles; ++i) {
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
    }

    closeAction = new QAction(tr("&Close"), this);
    closeAction->setShortcut(QKeySequence::Close);
    closeAction->setStatusTip(tr("Close the window"));
    connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    cutAction = new QAction(tr("&Cut"), this);
    cutAction->setIcon(QIcon(":/images/cut.ico"));
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("Cut the selected cells"));
    connect(cutAction, SIGNAL(triggered()), spreadsheet, SLOT(cut()));

    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setIcon(QIcon(":/images/copy.ico"));
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip(tr("Copy the selected cells"));
    connect(copyAction, SIGNAL(triggered()), spreadsheet, SLOT(copy()));

    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setIcon(QIcon(":/images/paste.png"));
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("Paste the selected cells"));
    connect(pasteAction, SIGNAL(triggered()), spreadsheet, SLOT(paste()));

    deleteAction = new QAction(tr("&Delete"), this);
    deleteAction->setShortcut(QKeySequence::Delete);
    deleteAction->setStatusTip(tr("Delete the selected cells"));
    connect(deleteAction, SIGNAL(triggered()), spreadsheet, SLOT(del()));


    findAction = new QAction(tr("&Find"), this);
    findAction->setIcon(QIcon(":/images/find.png"));
    findAction->setShortcut(QKeySequence::Find);
    findAction->setStatusTip(tr("Find the contents of the specified"));
    connect(findAction, SIGNAL(triggered()), this, SLOT(find()));

    goToCellAction = new QAction(tr("&Go to Cell"), this);
    goToCellAction->setIcon(QIcon(":/images/gotocell.ico"));
    goToCellAction->setShortcut(tr("Ctrl+G"));
    goToCellAction->setStatusTip(tr("Go to the specified cell"));
    connect(goToCellAction, SIGNAL(triggered()), this, SLOT(goToCell()));

    selectRowAction = new QAction(tr("&Row"),this);
    selectRowAction->setStatusTip(tr("select the row"));
    connect(selectRowAction, SIGNAL(triggered()), spreadsheet, SLOT(selectCurrentRow()));

    selectColumnAction = new QAction(tr("&Column"),this);
    selectColumnAction->setStatusTip(tr("select the column"));
    connect(selectColumnAction, SIGNAL(triggered()), spreadsheet, SLOT(selectCurrentColumn()));

    selectAllAction = new QAction(tr("&All"), this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    selectAllAction->setStatusTip(tr("Select all the cells in the spreadsheet"));
    connect(selectAllAction, SIGNAL(triggered()), spreadsheet, SLOT(selectAll()));

    recalculateAction = new QAction(tr("&Recalculate"), this);
    recalculateAction->setShortcut(tr("F9"));
    recalculateAction->setStatusTip(tr("Recalculate the selected cells"));
    connect(recalculateAction, SIGNAL(triggered()), spreadsheet, SLOT(recalculate()));

    sortAction = new QAction(tr("&Sort"), this);
    sortAction->setIcon(QIcon(":/images/sort.png"));
    sortAction->setStatusTip(tr("Sort the selected cells"));
    connect(sortAction, SIGNAL(triggered()), this, SLOT(sort()));

    fontAction = new QAction(tr("&font"), this);
    fontAction->setIcon(QIcon(":/images/font.png"));
    fontAction->setStatusTip(tr("font select"));
    connect(fontAction, SIGNAL(triggered()), spreadsheet, SLOT(setfont()));

    colorAction = new QAction(tr("color"), this);
    colorAction->setIcon(QIcon(":/images/color.png"));
    colorAction->setStatusTip(tr("color"));
    connect(colorAction, SIGNAL(triggered()), spreadsheet, SLOT(setColor()));

    alignLeftAction = new QAction(tr("&alignLeft"), this);
    alignLeftAction->setIcon(QIcon(":/images/alignLeft.png"));
    alignLeftAction->setStatusTip(tr("alignLeft"));
    connect(alignLeftAction, SIGNAL(triggered()), spreadsheet, SLOT(setAlignLeft()));

    alignRightAction = new QAction(tr("&alignRight"), this);
    alignRightAction->setIcon(QIcon(":/images/alignRight.png"));
    alignRightAction->setStatusTip(tr("alignRight"));
    connect(alignRightAction, SIGNAL(triggered()), spreadsheet, SLOT(setAlignRight()));

    alignHCenterAction = new QAction(tr("&alignHCenter"), this);
    alignHCenterAction->setIcon(QIcon(":/images/alignHCenter.png"));
    alignHCenterAction->setStatusTip(tr("alignHCenter"));
    connect(alignHCenterAction, SIGNAL(triggered()), spreadsheet, SLOT(setAlignHCenter()));

    backgroundColorAction = new QAction(tr("&backgroundColor"), this);
    backgroundColorAction->setIcon(QIcon(":/images/backgroundColor.png"));
    backgroundColorAction->setStatusTip(tr("backgroundColor"));
    connect(backgroundColorAction, SIGNAL(triggered()), spreadsheet, SLOT(setBackgroundColor()));

    showGridAction = new QAction(tr("&Show Grid"), this);
    showGridAction->setCheckable(true);
    showGridAction->setIcon(QIcon(":/images/showGrid.png"));
    showGridAction->setChecked(spreadsheet->showGrid());
    showGridAction->setStatusTip(tr("Show or hide the spreadsheet's grid"));
    connect(showGridAction, SIGNAL(toggled(bool)), spreadsheet, SLOT(setShowGrid(bool)));

    autoRecalculateAction = new QAction(tr("&Auto-Recalculate"), this);
    autoRecalculateAction->setCheckable(true);
    autoRecalculateAction->setIcon(QIcon(":/images/autoRecalculate.png"));
    autoRecalculateAction->setChecked(spreadsheet->autoRecalculate());
    autoRecalculateAction->setStatusTip(tr("Auto-Recalculate the spreadsheet's cell"));
    connect(autoRecalculateAction, SIGNAL(toggled(bool)), spreadsheet, SLOT(setAutoRecalculate(bool)));

    uploadAction = new QAction(tr("&Upload"), this);
    uploadAction->setStatusTip(tr("Upload file"));
    connect(uploadAction, SIGNAL(triggered()), this, SLOT(upload()));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the Spreadsheet's About box"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

}

void MainWindow::createMenus()//创建菜单并把动作添加到菜单上
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(printAction);
    separatorAction = fileMenu->addSeparator();
    for (int i = 0; i < MaxRecentFiles; ++i)
        fileMenu->addAction(recentFileActions[i]);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAction);
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);

    selectSubMenu = editMenu->addMenu(tr("&select"));
    selectSubMenu->addAction(selectRowAction);
    selectSubMenu->addAction(selectColumnAction);
    selectSubMenu->addAction(selectAllAction);

    editMenu->addSeparator();
    editMenu->addAction(findAction);
    editMenu->addAction(goToCellAction);

    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(recalculateAction);
    toolsMenu->addAction(sortAction);

    formatMenu = menuBar()->addMenu(tr("format"));
    formatMenu->addAction(fontAction);
    formatMenu->addAction(colorAction);
    alignmentSubMenu = formatMenu->addMenu(tr("&alignment"));
    alignmentSubMenu->addAction(alignLeftAction);
    alignmentSubMenu->addAction(alignHCenterAction);
    alignmentSubMenu->addAction(alignRightAction);
    formatMenu->addAction(backgroundColorAction);

    optionsMenu = menuBar()->addMenu(tr("&Options"));
    optionsMenu->addAction(showGridAction);
    optionsMenu->addAction(autoRecalculateAction);

    menuBar()->addSeparator();

    uploadMenu = menuBar()->addMenu(tr("&Upload"));
    uploadMenu->addAction(uploadAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

}


void MainWindow::createContextMenu()//创建上下文菜单并把动作添加上去
{
    spreadsheet->addAction(cutAction);
    spreadsheet->addAction(copyAction);
    spreadsheet->addAction(pasteAction);
    spreadsheet->addAction(selectRowAction);
    spreadsheet->addAction(selectColumnAction);
    spreadsheet->addAction(selectAllAction);
    spreadsheet->addAction(findAction);
    spreadsheet->addAction(sortAction);
    spreadsheet->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createToolBars()//创建工具栏并把动作添加到工具栏上
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);
    fileToolBar->addAction(printAction);

    editToolBar = addToolBar(tr("&Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addSeparator();
    editToolBar->addAction(findAction);
    editToolBar->addAction(goToCellAction);
    editToolBar->addAction(sortAction);

    addToolBarBreak();
    formatToolBar = addToolBar(tr("Format"));
    formatToolBar->addAction(fontAction);
    formatToolBar->addAction(colorAction);
    formatToolBar->addAction(alignLeftAction);
    formatToolBar->addAction(alignHCenterAction);
    formatToolBar->addAction(alignRightAction);
    formatToolBar->addAction(backgroundColorAction);

    optionsToolBar = addToolBar(tr("Options"));
    optionsToolBar->addAction(showGridAction);
    optionsToolBar->addAction(autoRecalculateAction);
}

void MainWindow::createStatusBar()
{
    locationLabel = new QLabel("W999");
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);

    statusBar()->addWidget(locationLabel);
    statusBar()->addWidget(formulaLabel, 1);

    connect(spreadsheet, SIGNAL(currentCellChanged(int, int, int, int)),
            this, SLOT(updateStatusBar()));
    connect(spreadsheet, SIGNAL(modified()), this, SLOT(spreadsheetModified()));
    updateStatusBar();

}

void MainWindow::updateStatusBar()
{
    locationLabel->setText(spreadsheet->currentLocation());
    formulaLabel->setText(spreadsheet->currentFormula());
}

void MainWindow::spreadsheetModified()
{
    setWindowModified(true);
    updateStatusBar();
}

void MainWindow::newFile()
{
    MainWindow *mainWin = new MainWindow;
    mainWin->show();

}

bool MainWindow::okToContinue()//对于修改过的文件，提示用户是否保存
{
    if (isWindowModified()) {
        int r = QMessageBox::warning(this, tr("Spreadsheet"),
                tr("The document has been modified.\n"
                   "Do you want to save your changes?"),
                   QMessageBox::Yes | QMessageBox::No
                   | QMessageBox::Cancel);
        if (r == QMessageBox::Yes)
            return save();
        else if (r == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void MainWindow::open()
{
    if (okToContinue()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                           tr("Open Spreadsheet"), ".",
                           tr("Spreadsheet files(*.sp)\n"));
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}


bool MainWindow::loadFile(const QString &fileName)
{
    if (!spreadsheet->readFile(fileName)) {
        statusBar()->showMessage(tr("Loading canceled"), 2000);//在状态栏上显示提示信息2s
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
    return true;

}

bool MainWindow::save()
{
    if (curFile.isEmpty())
        return saveAs();
    else
        return saveFile(curFile);
}

bool MainWindow::saveFile(const QString &fileName)
{
    if (!spreadsheet->writeFile(fileName)) {
        statusBar()->showMessage(tr("Saving canceled"), 2000);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                       tr("Save Spreadsheet"), ".",
                       tr("Spreadsheet files (*.sp)\n"));
    if(fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

void MainWindow::print()
{
    QTableWidgetSelectionRange range = spreadsheet->selectedRange();
    QString str;

    for (int i = 0; i < range.rowCount(); ++i) {
        if (i > 0)
            str += "\n";
        for (int j = 0; j < range.columnCount(); j++) {
            if (j > 0)
                str += "\t";
            str += spreadsheet->formula(range.topRow() + i, range.leftColumn() + j);
        }
    }

    QPrinter printer;
    QPrintDialog *printDialog = new QPrintDialog(&printer, this);
    if (printDialog->exec()) {
        QTextDocument textDocument;
        textDocument.setHtml(str);
        textDocument.print(&printer);
    }
    delete printDialog;

}

void MainWindow::closeAllWindows()
{
    foreach (QWidget *win, QApplication::topLevelWidgets()) {
        if (MainWindow *mainWin = qobject_cast<MainWindow*>(win))
            mainWin->close();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (okToContinue()) {
        writeSettings();
        event->accept();
    }
    else {
        event->ignore();
    }

}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);

    QString showName = tr("Untitled");//默认文件名
    if (!curFile.isEmpty()) {
        showName = strippedName(curFile);
        recentFiles.removeAll(curFile);
        recentFiles.prepend(curFile);
        foreach (QWidget *win, QApplication::topLevelWidgets()) {
            if (MainWindow *mainWin = qobject_cast<MainWindow *>(win))//转换失败将返回0
                mainWin->updateRecentFileActions();
        }
    }

    setWindowTitle(tr("%1[*] - %2").arg(showName)
                                   .arg(tr("Spreadsheet")));

}


QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::updateRecentFileActions()
{
    QMutableStringListIterator i(recentFiles);

    while (i.hasNext()) {
        if (!QFile::exists(i.next()))
            i.remove();
    }

    for (int j = 0; j < MaxRecentFiles; ++j) {
        if (j < recentFiles.count()) {
            QString text = tr("&%1 %2").arg(j+1)
                           .arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
        }
        else {
            recentFileActions[j]->setVisible(false);
        }

    }
    separatorAction->setVisible(!MainWindow::recentFiles.isEmpty());
}

void MainWindow::openRecentFile()
{
    if (okToContinue()) {
        QAction *action = qobject_cast<QAction *>(sender());
        if (action)
            loadFile(action->data().toString());
    }
}

void MainWindow::find()
{
    if (!findDialog) {
        findDialog = new FindDialog(this);
        connect(findDialog, SIGNAL(findNext(QString,Qt::CaseSensitivity)),
                spreadsheet, SLOT(findNext(QString,Qt::CaseSensitivity)));

        connect(findDialog, SIGNAL(findPrevious(QString,Qt::CaseSensitivity)),
                spreadsheet, SLOT(findPrevious(QString,Qt::CaseSensitivity)));

        connect(spreadsheet, SIGNAL(findFail()), findDialog, SLOT(findFail()));
    }

    findDialog->lineEditClear();
    findDialog->show();
    findDialog->raise();
    findDialog->activateWindow();

}

void MainWindow::goToCell()
{
    gotocelldialog * dialog = new gotocelldialog(this);
    if (dialog->exec()) {
        QString str = dialog->lineEdit->text().toUpper();
        spreadsheet->setCurrentCell(str.mid(1).toInt() - 1,
                                    str[0].unicode() - 'A');
    }
    delete dialog;
}

void MainWindow::sort()
{
    SortDialog dialog(this);
    QTableWidgetSelectionRange range = spreadsheet->selectedRange();
    dialog.setColumnRange('A' + range.leftColumn(),
                          'A' + range.rightColumn());

    if (dialog.exec()) {
        SpreadsheetCompare compare;
        compare.keys[0] =
                dialog.primaryCloumnCombo->currentIndex();
        compare.keys[1] =
                dialog.secondaryColumnCombo->currentIndex() - 1;
        compare.keys[2] =
                dialog.tertiaryCloumnCombo->currentIndex() - 1;
        compare.ascending[0] =
                (dialog.primaryOrdercombo->currentIndex() == 0);
        compare.ascending[1] =
                (dialog.secondaryOrderCombo->currentIndex() == 0);
        compare.ascending[2] =
                (dialog.tertiaryOrderCombo->currentIndex() == 0);
        spreadsheet->sort(compare);
    }
}

void MainWindow::upload()
{
    uploadDialog = new Uploaddialog();
    uploadDialog->show();
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Spreadsheet"),
                       tr("<h2>Spreadsheet 1.0</h2>"
                          "<p>Copyright; 2015.12 Software"
                          "<p>Spreadsheet is a small application "
                          "for practice"
                          "<p>by Chen PengHui"));
}


void MainWindow::writeSettings()
{
    QSettings settings("Personal Practice", "Spreadsheet");

    settings.setValue("geometry", saveGeometry());
    settings.setValue("recentFiles", MainWindow::recentFiles);
    settings.setValue("showGird", showGridAction->isChecked());
    settings.setValue("autoReclc", autoRecalculateAction->isChecked());
}

void MainWindow::readSettings()
{
    QSettings settings("Personal Practice", "Spreadsheet");

    restoreGeometry(settings.value("geometry").toByteArray());

    recentFiles = settings.value("recentFiles").toStringList();

    foreach (QWidget *win, QApplication::topLevelWidgets()) {
        if (MainWindow *mainWin = qobject_cast<MainWindow *>(win))
            mainWin->updateRecentFileActions();
    }

    bool showGird = settings.value("showGird", true).toBool();
    showGridAction->setChecked(showGird);

    bool autoRecalc = settings.value("autoRecalc", true).toBool();
    autoRecalculateAction->setChecked(autoRecalc);
}




























