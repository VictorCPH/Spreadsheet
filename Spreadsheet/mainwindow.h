#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QLabel;
class FindDialog;
class Spreadsheet;
class Uploaddialog;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void newFile();//新建文件
    void open();//打开文件
    bool save();//保存
    bool saveAs();//另存为
    void sort();//排序
    void print();//设置打印属性
    void closeAllWindows();//关闭所有表格
    //.......
    void find();//查询操作
    void goToCell();//到达指定单元格
    void upload();//上传文件
    void about();//程序介绍
    void openRecentFile();//打开最近文件
    void updateStatusBar();//更新状态栏
    void spreadsheetModified();//标记表格是否改动

private:
    void createActions();
    void createMenus();//创建菜单栏
    void createContextMenu();//创建上下文菜单
    void createToolBars();//创建工具栏
    void createStatusBar();//创建状态栏
    void readSettings();//读取设置信息
    void writeSettings();//保存存储设置
    bool okToContinue();//根据文件是否修改，判断是否能继续下面动作
    bool loadFile(const QString &fileName);//载入文件
    bool saveFile(const QString &fileName);//保存文件
    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();
    QString strippedName(const QString &fullFileName);

    Spreadsheet *spreadsheet;

    FindDialog *findDialog;
    Uploaddialog *uploadDialog;
    QLabel *locationLabel;
    QLabel *formulaLabel;


    static QStringList recentFiles;
    QString curFile;

    enum { MaxRecentFiles = 5 };

    QAction *recentFileActions[MaxRecentFiles];
    QAction *separatorAction;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *selectSubMenu;
    QMenu *toolsMenu;
    QMenu *optionsMenu;
    QMenu *uploadMenu;
    QMenu *helpMenu;
    QMenu *formatMenu;
    QMenu *alignmentSubMenu;
    //.....
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *formatToolBar;
    QToolBar *optionsToolBar;

    QAction *uploadAction;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *deleteAction;
    QAction *selectAction;
    QAction *selectRowAction;
    QAction *selectColumnAction;
    QAction *recalculateAction;
    QAction *sortAction;
    QAction *closeAction;
    QAction *findAction;
    QAction *goToCellAction;
    QAction *selectAllAction;
    QAction *showGridAction;
    QAction *autoRecalculateAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
    QAction *printAction;

    QAction *fontAction;
    QAction *colorAction;
    QAction *alignLeftAction;
    QAction *alignRightAction;
    QAction *alignHCenterAction;
    QAction *backgroundColorAction;
};

#endif // MAINWINDOW_H
