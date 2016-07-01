#ifndef CELL_H
#define CELL_H

#include <QTableWidgetItem>

class Cell : public QTableWidgetItem
{
public:
    Cell();

    QTableWidgetItem* clone() const;   //重载clone函数，使得每次创建QTableWidgetItem时，实际创建的是Cell
    void setData(int role, const QVariant &value); //重载setData,使得当缓存为dirty时，更新单元格
    QVariant data(int role) const;   //重载data函数，当为显示模式时计算结果的值，当为编辑模式时显示公式，若数据结果错误时显示####，表示无效
    void setFormula(const QString &formula);//设置单元格中公式
    QString formula() const;//获得单元格中公式
    void setDirty();//单元格设置为dirty

private:
    QVariant value() const;//按照公式计算结果，若以等号开始则认为是公式，若为double,则会省略小数点后多余的0，否则当作一般字符串直接显示

    //递归下降解析表达式，计算结果
    QVariant evalExpression(const QString &str, int &pos) const;
    QVariant evalTerm(const QString &str, int &pos) const;
    QVariant evalFactor(const QString &str, int &pos) const;

    //下面两个变量设置为mutable, 是为了能在声明为const的函数中可以对其修改
    mutable QVariant cachedValue;//单元格的值缓存为QVariant类型
    mutable bool cacheIsDirty;//如果值不是最新的，则设为true

};

#endif // CELL_H

