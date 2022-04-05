#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>


class TestWidget: public QWidget
{
    Q_OBJECT
private:
    QLabel *label;
    QVBoxLayout *mainLayout;
    QList<QPushButton*> mButtonList;
public:
    TestWidget(QWidget *parent=nullptr) : QWidget(parent)
    {
        mainLayout = new QVBoxLayout(this);
        label = new QLabel;
        mainLayout->addWidget(label);
        this->setLayout(mainLayout);
    }

    void addButton(QString buttonName)
    {
        QPushButton *button = new QPushButton(buttonName);
        QObject::connect(button, SIGNAL(clicked(bool)), this, SLOT(buttonClicked(bool)));        
        mButtonList.append(button);
        mainLayout->addWidget(button);
    }

public slots:
    void buttonClicked(bool event)
    {
        Q_UNUSED(event)
        static_cast<QPushButton*>(QObject::sender())->setFocus();
        for (int i = 0; i < mButtonList.size(); ++i)
        {
            if (mButtonList.at(i) == sender())
            {
                label->setText(QString(mButtonList.at(i)->text()));
                break;
            }
        }
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TestWidget wid;
    wid.addButton("First Button");
    wid.addButton("Second Button");
    wid.addButton("Third Button");
    wid.addButton("Fourth Button");
    wid.show();

    return a.exec();
}

#include "main.moc"

