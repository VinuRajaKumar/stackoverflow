#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>


class TestWidget: public QWidget
{
    Q_OBJECT
private:
    QTableWidget *testTable;
    QVBoxLayout *mainLayout;
    QPushButton *button;
public:
    TestWidget(QWidget *parent=nullptr) : QWidget(parent)
    {
        mainLayout = new QVBoxLayout(this);
        testTable = new QTableWidget;

        testTable = new QTableWidget(this);
        testTable->setObjectName("testTable");
        testTable->setFixedWidth(400);
        testTable->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum);
        testTable->setColumnCount(4);
        testTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        testTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        QTableWidgetItem *itemC1 = new QTableWidgetItem("Column 1");
        testTable->setHorizontalHeaderItem(0, itemC1);
        QTableWidgetItem *itemC2 = new QTableWidgetItem("Column 2");
        testTable->setHorizontalHeaderItem(1, itemC2);
        QTableWidgetItem *itemC3 = new QTableWidgetItem("Column 3");
        testTable->setHorizontalHeaderItem(2, itemC3);
        QTableWidgetItem *itemC4 = new QTableWidgetItem("Column 4");
        testTable->setHorizontalHeaderItem(3, itemC4);
        testTable->setColumnWidth(0,100);
        testTable->setColumnWidth(1,100);
        testTable->setColumnWidth(2,100);
        testTable->setColumnWidth(3,100);
        testTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        testTable->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::AnyKeyPressed);
        testTable->setProperty("showDropIndicator", QVariant(false));
        testTable->setDragDropOverwriteMode(false);
        testTable->setSelectionMode(QAbstractItemView::SingleSelection);
        testTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        testTable->setShowGrid(true);
        testTable->setGridStyle(Qt::SolidLine);
        testTable->setSortingEnabled(false);
        testTable->setCornerButtonEnabled(false);
        testTable->horizontalHeader()->setHighlightSections(false);
        testTable->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        testTable->verticalHeader()->setVisible(false);
        testTable->setAlternatingRowColors(true);

        button = new QPushButton("Group");
        connect(button, SIGNAL(clicked(bool)), this, SLOT(buttonClicked(bool)));
        mainLayout->addWidget(testTable);
        mainLayout->addWidget(button);
        this->setLayout(mainLayout);
    }

    void addRow(QString c1, QString c2, QString c3, QString c4)
    {
        int row = testTable->rowCount();
        testTable->insertRow(row);

        QTableWidgetItem *c1Item = new QTableWidgetItem(c1);
        QTableWidgetItem *c2Item = new QTableWidgetItem(c2);
        QTableWidgetItem *c3Item = new QTableWidgetItem(c3);
        QTableWidgetItem *c4Item = new QTableWidgetItem(c4);
        c1Item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        c2Item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        c3Item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        c4Item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        testTable->setItem(row, 0, c1Item);
        testTable->setItem(row, 1, c2Item);
        testTable->setItem(row, 2, c3Item);
        testTable->setItem(row, 3, c4Item);
    }

    void updateCell(int rowNumber, int columnNumber, QString textString)
    {
        if(rowNumber>=testTable->rowCount() || columnNumber>=testTable->columnCount()) return;
        testTable->item(rowNumber, columnNumber)->setText(textString);
    }

    void groupCells(int rowNumber, int span)
    {
        if(rowNumber>=testTable->rowCount()) return;
        testTable->setSpan(rowNumber,1,1,span);
    }

    void ungroupCells(int rowNumber)
    {
        if(rowNumber>=testTable->rowCount()) return;
        testTable->setSpan(rowNumber,1,1,1);
    }

public slots:
    void buttonClicked(bool event)
    {
        Q_UNUSED(event)
        if(button->text()=="Group")
        {
            groupCells(1,2);
            button->setText("Ungroup");
        }
        else
        {
            ungroupCells(1);
            button->setText("Group");
        }
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TestWidget wid;
    wid.addRow("0,0", "0,1", "0,2", "0,3");
    wid.addRow("1,0", "1,1", "1,2", "1,3");
    wid.addRow("2,0", "2,1", "2,2", "2,3");
    wid.addRow("3,0", "3,1", "3,2", "3,3");
    wid.show();

    return a.exec();
}

#include "main.moc"

