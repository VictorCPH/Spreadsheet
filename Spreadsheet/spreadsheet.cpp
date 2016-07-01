#include "cell.h"
#include "spreadsheet.h"
#include <QFile>
#include <QMessageBox>
#include <QApplication>
#include <QClipboard>
#include <QFontDialog>
#include <QHeaderView>
#include <QColorDialog>
#include <QPalette>
#include <QTextCodec>
#include <QBrush>
#include <QDebug>

Spreadsheet::Spreadsheet(QWidget *parent)
    : QTableWidget(parent)
{
    autoRecalc = true;
    isCopy = false;
    setItemPrototype(new Cell);
    setSelectionMode(ContiguousSelection);

    connect(this, SIGNAL(itemChanged(QTableWidgetItem*)),
            this, SLOT(somethingChanged()));

    clear();
}

void Spreadsheet::clear()
{
    setRowCount(0);      //完全清空所有项，包括标题
    setColumnCount(0);
    setRowCount(RowCount);
    setColumnCount(ColumnCount);

    for (int i = 0; i < ColumnCount; ++i) {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(QString(QChar('A' + i)));
        setHorizontalHeaderItem(i, item);
    }

    setCurrentCell(0,0);  //光标移到A1
}

Cell* Spreadsheet::cell(int row, int column) const
{
    return static_cast<Cell *>(item(row, column));
}

QString Spreadsheet::text(int row, int column) const//返回单元格文本
{
    Cell *c = cell(row, column);
    if (c) {
        return c->text();
    }
    else {
        return "";
    }
}

QString Spreadsheet::formula(int row, int column) const
{
    Cell *c = cell(row, column);
    if (c) {
        return c->formula();
    }
    else {
        return "";
    }
}

void Spreadsheet::setFormula(int row, int column, const QString &formula)
{
    Cell *c = cell(row, column);
    if (!c) {
        c = new Cell;
        setItem(row, column, c);
    }

    c->setFormula(formula);
}

QString Spreadsheet::currentLocation() const
{
    return QChar('A' + currentColumn())
                 + QString::number(currentRow() + 1);
}

QString Spreadsheet::currentFormula() const
{
    return formula(currentRow(), currentColumn());
}

void Spreadsheet::somethingChanged()
{
    if (autoRecalc)
        recalculate();
    emit modified();
}

bool Spreadsheet::writeFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Spreadsheet"),
                             tr("Cannt write file %1:\n%2.")
                             .arg(file.fileName()
                             .arg(file.errorString())));
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_3);//........

    out << quint32(MagicNumber);

    QApplication::setOverrideCursor(Qt::WaitCursor);
    for (int row = 0; row < RowCount; ++row) {
        for (int column = 0; column < ColumnCount; column++) {
            QString str = formula(row, column);

            if (cell(row, column) != 0) {               //如果单元格被创建过
                Cell *c = cell(row, column);

                out << quint16(row) << quint16(column)   //行列号
                    << quint16(c->textAlignment())        //对齐方式
                    << quint16(columnWidth(column))     //列宽
                    << quint16(rowHeight(row))          //行高
                    << quint16(c->font().pointSize())    //字体点大小
                    << quint16(c->font().weight());       //字体加粗

                if (c->font().underline() == true)        //字体下划线
                    out << quint16(1);
                else
                    out << quint16(0);

                if (c->font().strikeOut() == true)        //字体删除线
                    out << quint16(1);
                else
                    out << quint16(0);

                if (c->font().italic() == true)          //字体斜体
                    out << quint16(1);
                else
                    out << quint16(0);

                if (c->background().style() == Qt::NoBrush)   //背景风格（透明程度）
                    out << quint16(0);
                else
                    out << quint16(1);

                out << c->font().family()                 //字体族
                    << c->foreground().color().name()     //字体颜色
                    << c->backgroundColor().name()        //背景颜色
                    << str;                               //内容
            }
        }
    }
    QApplication::restoreOverrideCursor();
    return true;
}

bool Spreadsheet::readFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Spreadsheet"),
                             tr("Cannot read file %1:\n%2")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_3);

    quint32 magic;
    in >> magic;
    if (magic != MagicNumber) {
        QMessageBox::warning(this, tr("Spreadsheet"),
                             tr("The file is not a Spreadsheet file."));
        return false;
    }

    clear();

    quint16 row;
    quint16 column;
    quint16 alignment;
    quint16 fontPointSize;
    quint16 fontWeight;
    quint16 fontItalic;
    quint16 fontUnderline;
    quint16 fontStrikeOut;
    quint16 width;
    quint16 height;
    quint16 backgroundStyle;
    QString fontfamily;
    QString color;
    QString backgroundcolor;
    QString str;
    bool Italic;
    bool underline;
    bool strikeout;

    QApplication::setOverrideCursor(Qt::WaitCursor);
    while (!in.atEnd()) {
        in >> row >> column   //行列号
           >> alignment       //对齐方式
           >> width     //列宽
           >> height    //行高
           >> fontPointSize //字体点大小
           >> fontWeight    //字体加粗
           >> fontUnderline  //字体下划线
           >> fontStrikeOut  //字体删除线
           >> fontItalic;   //字体斜体

        if (fontUnderline == 1)
            underline  = true;
        else
            underline = false;

        if (fontStrikeOut == 1)
            strikeout = true;
        else
            strikeout = false;

        if (fontItalic == 1)
            Italic = true;
        else
            Italic = false;

        in >> backgroundStyle
           >> fontfamily           //字体族
           >> color                 //字体颜色
           >> backgroundcolor       //背景颜色
           >> str;                  //内容
        Cell * c = cell(row, column);
        if (!c) {
            c = new Cell;
            setItem(row, column, c);
        }
        setFormula(row, column, str);
        setColumnWidth(column, width);
        setRowHeight(row, height);

        QFont font(fontfamily, fontPointSize, fontWeight, Italic);
        font.setUnderline(underline);
        font.setStrikeOut(strikeout);
        c->setFont(font);
        c->setTextAlignment(alignment | Qt::AlignVCenter);

        QBrush brush;
        brush.setColor(QColor(color));
        c->setForeground(brush);
        if (backgroundStyle == 0)
            brush.setStyle(Qt::NoBrush);
        else
            brush.setStyle(Qt::SolidPattern);
        brush.setColor(backgroundcolor);
        c->setBackground(brush);

    }
    QApplication::restoreOverrideCursor();
    return true;
}

void Spreadsheet::cut()
{
    copy();
    del();
}

void Spreadsheet::copy()
{
    QTableWidgetSelectionRange range = selectedRange();

    QByteArray byteArray;
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_3);

    out << quint16(range.rowCount()) << quint16(range.columnCount());//记录区域范围，粘贴时用于检测

    QApplication::setOverrideCursor(Qt::WaitCursor);
    for (int row = 0; row < range.rowCount(); ++row) {
        for (int column = 0; column < range.columnCount(); column++) {
            QString str = formula(range.topRow() + row, range.leftColumn() + column);
            Cell *c = cell(range.topRow() + row, range.leftColumn() + column);
            if (!c) {
                c = new Cell;
                setItem(range.topRow() + row, range.leftColumn() + column, c);
            }

            out << quint16(c->textAlignment())        //对齐方式
                << quint16(columnWidth(range.leftColumn() + column)) //列宽
                << quint16(rowHeight(range.topRow() + row))          //行高
                << quint16(c->font().pointSize())    //字体点大小
                << quint16(c->font().weight());       //字体加粗

            if (c->font().underline() == true)        //字体下划线
               out << quint16(1);
            else
               out << quint16(0);

            if (c->font().strikeOut() == true)        //字体删除线
               out << quint16(1);
            else
               out << quint16(0);

            if (c->font().italic() == true)          //字体斜体
               out << quint16(1);
            else
               out << quint16(0);

            if (c->background().style() == Qt::NoBrush)   //背景风格（透明程度）
                out << quint16(0);
            else
                out << quint16(1);

            out << c->font().family()                 //字体族
                << c->foreground().color().name()     //字体颜色
                << c->backgroundColor().name()        //背景颜色
                << str;                               //内容
        }
    }
    QApplication::restoreOverrideCursor();

    QTextCodec *codec = QTextCodec::codecForName("Latin-1");
    QString str = codec->toUnicode(byteArray);
    QApplication::clipboard()->setText(str);

    isCopy = true;
}

QTableWidgetSelectionRange Spreadsheet::selectedRange() const
{
    QList<QTableWidgetSelectionRange> ranges = selectedRanges();
    if (ranges.isEmpty())
        return QTableWidgetSelectionRange();
    return ranges.first();
}

void Spreadsheet::paste()
{
    if (!isCopy) {
        return;
    }

    QTableWidgetSelectionRange range = selectedRange();

    QDataStream in(QApplication::clipboard()->text().toLatin1());
    in.setVersion(QDataStream::Qt_4_3);

    quint16 numRows;
    quint16 numColumns;
    in >> numRows >> numColumns;
    if (range.rowCount() * range.columnCount() != 1
            && (range.rowCount() != numRows
                ||range.columnCount() != numColumns)) {
        QMessageBox::information(this, tr("Spreadsheet"),
                tr("The information cannot be pasted because the copy"
                   " and paste areas aren't the same size"));
        return;
    }

    quint16 alignment;
    quint16 fontPointSize;
    quint16 fontWeight;
    quint16 fontItalic;
    quint16 fontUnderline;
    quint16 fontStrikeOut;
    quint16 width;
    quint16 height;
    quint16 backgroundStyle;
    QString fontfamily;
    QString color;
    QString backgroundcolor;
    QString str;
    bool Italic;
    bool underline;
    bool strikeout;

    QApplication::setOverrideCursor(Qt::WaitCursor);

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numColumns; ++j) {
            int row = range.topRow() + i;
            int column = range.leftColumn() + j;
            if (row < RowCount && column < ColumnCount) {
                in >> alignment       //对齐方式
                   >> width     //列宽
                   >> height    //行高
                   >> fontPointSize //字体点大小
                   >> fontWeight    //字体加粗
                   >> fontUnderline  //字体下划线
                   >> fontStrikeOut  //字体删除线
                   >> fontItalic;   //字体斜体

                if (fontUnderline == 1)
                    underline  = true;
                else
                    underline = false;

                if (fontStrikeOut == 1)
                    strikeout = true;
                else
                    strikeout = false;

                if (fontItalic == 1)
                    Italic = true;
                else
                    Italic = false;

                in >> backgroundStyle       //背景风格
                   >> fontfamily            //字体族
                   >> color                 //字体颜色
                   >> backgroundcolor       //背景颜色
                   >> str;                  //内容
                Cell * c = cell(row, column);
                if (!c) {
                    c = new Cell;
                    setItem(row, column, c);
                }
                setFormula(row, column, str);
                setColumnWidth(column, width);
                setRowHeight(row, height);

                QFont font(fontfamily, fontPointSize, fontWeight, Italic);
                font.setUnderline(underline);
                font.setStrikeOut(strikeout);
                c->setFont(font);
                c->setTextAlignment(alignment | Qt::AlignVCenter);

                QBrush brush;
                brush.setColor(QColor(color));
                c->setForeground(brush);
                if (backgroundStyle == 0)
                    brush.setStyle(Qt::NoBrush);
                else
                    brush.setStyle(Qt::SolidPattern);
                brush.setColor(backgroundcolor);
                c->setBackground(brush);
            }
        }
    }
    QApplication::restoreOverrideCursor();
    somethingChanged();
}

void Spreadsheet::del()
{
    QList<QTableWidgetItem *> items = selectedItems();
    if (!items.isEmpty()) {
        foreach (QTableWidgetItem *item, items) {
            delete item;
            somethingChanged();
        }
    }
}

void Spreadsheet::selectCurrentRow()
{
    selectRow(currentRow());
}

void Spreadsheet::selectCurrentColumn()
{
    selectColumn(currentColumn());
}

void Spreadsheet::findNext(const QString &str, Qt::CaseSensitivity cs)
{
    int row = currentRow();
    int column = currentColumn() + 1;

    while (row < RowCount) {
        while (column < ColumnCount) {
            if (text(row, column).contains(str, cs)) {
                clearSelection();
                setCurrentCell(row, column);
                activateWindow();
                return;
            }
            ++column;
        }
        column = 0;
        ++row;
    }
    emit findFail();
}

void Spreadsheet::findPrevious(const QString &str, Qt::CaseSensitivity cs)
{
    int row = currentRow();
    int column = currentColumn() - 1;

    while (row >=0 ) {
        while (column >= 0) {
            if (text(row, column).contains(str, cs)) {
                clearSelection();
                setCurrentCell(row, column);
                activateWindow();
                return;
            }
            --column;
        }
        column = ColumnCount - 1;
        --row;
    }
    emit findFail();
}

void Spreadsheet::recalculate()
{
    for (int row = 0; row < RowCount; ++row) {
        for (int column = 0; column < ColumnCount; ++column) {
            if (cell(row, column))
                cell(row, column)->setDirty();
        }
    }
    viewport()->update();
}

void Spreadsheet::setAutoRecalculate(bool recalc)
{
    autoRecalc = recalc;
    if (autoRecalc)
        recalculate();
}

void Spreadsheet::sort(const SpreadsheetCompare &compare)
{
    QList<QStringList> rows;
    QTableWidgetSelectionRange range = selectedRange();
    int i;

    for (i = 0; i < range.rowCount(); ++i) {
        QStringList row;
        for (int j = 0; j < range.columnCount(); ++j)
            row.append(formula(range.topRow() + i,
                               range.leftColumn() + j));
        rows.append(row);
    }

    qStableSort(rows.begin(), rows.end(), compare);    //.......

    for (i = 0; i < range.rowCount(); ++i) {
        for (int j = 0; j < range.columnCount(); ++j)
            setFormula(range.topRow() + i, range.leftColumn() + j,
                       rows[i][j]);
    }

    clearSelection();
    somethingChanged();
}

bool SpreadsheetCompare::operator()(const QStringList &row1,
                                    const QStringList &row2) const
{
    for (int i = 0; i < KeyCount; ++i) {
        int column = keys[i];
        if (column != -1) {
            if (row1[column] != row2[column]) {
                if (ascending[i]) {
                    return row1[column] < row2[column];
                }
                else
                    return row1[column] > row2[column];
            }
        }
    }
    return false;
}

void Spreadsheet::setfont()
{
    QTableWidgetSelectionRange range = selectedRange();

    Cell *c = cell(range.topRow(), range.leftColumn());//找到选中区域的第一个单元格
    if (!c) {
        c = new Cell;
        setItem(range.topRow(), range.leftColumn(), c);
    }

    bool ok;
    QFont font = QFontDialog::getFont(              //获得设置的字体
                &ok,
                QFont(c->font()), // 初始字体为第一个单元格的字体
                this);

    //刷新选中区域的单元格的字体
    if (ok){
        for (int i = 0; i < range.rowCount(); ++i) {
            for (int j = 0; j < range.columnCount(); ++j) {
                Cell *c = cell(range.topRow() + i, range.leftColumn() + j);        //找到当前单元格
                if (!c) {
                    c = new Cell;
                    setItem(range.topRow() + i, range.leftColumn() + j, c);
                }
                c->setFont(font);// font被设置为用户选择的字体
            }
            resizeRowToContents(range.topRow() + i);   //行高自适应大小
        }
    }
}

void Spreadsheet::setColor()
{
    QTableWidgetSelectionRange range = selectedRange();

    Cell *c = cell(range.topRow(), range.leftColumn());//找到选中区域的第一个单元格
    if (!c) {
        c = new Cell;
        setItem(range.topRow(), range.leftColumn(), c);
    }

    QBrush brush;
    //获取调色板设置的颜色
    const QColor &color = QColorDialog::getColor(c->foreground().color(),//初始颜色为第一个单元格的颜色
                                                 this);

    //刷新选中区域的单元格的颜色
    if (color.isValid()){
        for (int i = 0; i < range.rowCount(); ++i) {
            for (int j = 0; j < range.columnCount(); ++j) {
                Cell *c = cell(range.topRow() + i, range.leftColumn() + j);        //找到当前单元格
                if (!c) {
                    c = new Cell;
                    setItem(range.topRow() + i, range.leftColumn() + j, c);
                }
                brush.setColor(color);// color被设置为用户选择的颜色
                c->setForeground(brush);
            }
        }
    }

}

void Spreadsheet::setAlign(Qt::Alignment a)
{
    QTableWidgetSelectionRange range = selectedRange();

    //刷新选中区域的单元格的对齐方式
    for (int i = 0; i < range.rowCount(); ++i) {
       for (int j = 0; j < range.columnCount(); ++j) {
           Cell *c = cell(range.topRow() + i, range.leftColumn() + j);        //找到当前单元格
           if (!c) {
               c = new Cell;
               setItem(range.topRow() + i, range.leftColumn() + j, c);
           }
           c->setTextAlignment(Qt::AlignVCenter | a);
       }
    }
}

void Spreadsheet::setAlignLeft()
{
    setAlign(Qt::AlignLeft);
}

void Spreadsheet::setAlignRight()
{
    setAlign(Qt::AlignRight);
}

void Spreadsheet::setAlignHCenter()
{
    setAlign(Qt::AlignHCenter);
}

void Spreadsheet::setBackgroundColor()
{
    QTableWidgetSelectionRange range = selectedRange();

    Cell *c = cell(range.topRow(), range.leftColumn());//找到选中区域的第一个单元格
    if (!c) {
        c = new Cell;
        setItem(range.topRow(), range.leftColumn(), c);
    }

    //获取调色板设置的颜色
    const QColor &color = QColorDialog::getColor(c->background().color(),//初始颜色为黄色
                                                 this);

    //刷新选中区域的单元格的颜色
    if (color.isValid()){
        for (int i = 0; i < range.rowCount(); ++i) {
            for (int j = 0; j < range.columnCount(); ++j) {
                Cell *c = cell(range.topRow() + i, range.leftColumn() + j);        //找到当前单元格
                if (!c) {
                    c = new Cell;
                    setItem(range.topRow() + i, range.leftColumn() + j, c);
                }
                c->setBackgroundColor(color);// color被设置为用户选择的颜色
            }
        }
    }

}














