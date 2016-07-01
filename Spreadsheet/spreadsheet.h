#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QTableWidget>

class Cell;
class SpreadsheetCompare;

class Spreadsheet : public QTableWidget
{
    Q_OBJECT

public:
    Spreadsheet(QWidget *parent = 0);

    bool autoRecalculate() const { return autoRecalc;}//设置是否自动计算
    QString currentLocation() const;//返回当前单元格位置
    QString currentFormula() const;//返回当前单元格的内容
    QTableWidgetSelectionRange selectedRange() const;//返回当前鼠标所选中的区域范围
    void clear();
    bool readFile(const QString &fileName);//按照保存时的格式读取恢复单元格内容信息，包括文本，字体，背景，对齐等
    bool writeFile(const QString &fileName);//把文件输出到磁盘上，保存格式如下：
                                            //以一个随机的32位数(下面定义的MagicNumber)作为文件开始,紧跟一个quint16的行号，
                                            //一个quint16的列号，对齐方式，列宽，行号，字体点大小，加粗，下划线，删除线，斜体，
                                            //背景风格，字体族，字体颜色，背景颜色，内容。然后下一个单元格信息，以此类推

    void sort(const SpreadsheetCompare &compare);//排序
    QString formula(int row, int column) const;//获得某单元格的公式

public slots:

    void cut();//剪切
    void copy();//复制
    void paste();//粘贴
    void del();//删除
    void selectCurrentRow();//选中某一行
    void selectCurrentColumn();//选中某一列
    void recalculate();//计算单元格中公式
    void setAutoRecalculate(bool recalc);//设置是否为自动计算
    void findNext(const QString &str, Qt::CaseSensitivity cs);//向后查找
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);//向前查找
    void setfont();//设置字体格式
    void setColor();//设置字体颜色
    void setAlignLeft();//左对齐
    void setAlignRight();//右对齐
    void setAlignHCenter();//居中
    void setAlign(Qt::Alignment a);//设置对齐方式
    void setBackgroundColor();//设置背景色
signals:
    void modified();//若表格被修改，设置标记位为真
    void findFail();//查找失败，显示提示信息

private slots:
    void somethingChanged();//若单元格发生改变，则更新对应内容

private:
    enum { MagicNumber = 0x7F51C883, RowCount = 999, ColumnCount = 26};// MagicNumber文件起始标记，行数设为999行，列数设为26列，A~Z

    Cell* cell(int row, int column) const;//返回指向某个单元格的指针
    QString text(int row, int column) const;//获取某个单元格的内容
    bool isCopy;//判断是否已经copy了
    void setFormula(int row, int column, const QString &formula);//设置某个单元格内容
    bool autoRecalc;//设置是否为自动计算
};

class SpreadsheetCompare
{
public:
    bool operator()(const QStringList &row1,
                    const QStringList &row2) const;
    enum { KeyCount = 3 };
    int keys[KeyCount];//以三个键值，作为标准排序
    bool ascending[KeyCount];//设置为升序还是降序
};

#endif // SPREADSHEET_H

