#ifndef PROPERTYEDITWIDGET_H
#define PROPERTYEDITWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QCheckBox>
#include <QSharedPointer>
#include <QToolButton>
#include <QMetaProperty>
#include <QVariant>

namespace Ui {
    class PropertyEditWidget;
}

class PropertyEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PropertyEditWidget(QWidget *parent = 0);
    ~PropertyEditWidget();

    bool setProperty(QMetaProperty property, QObject* object);
    bool writeProperty();

private:
    Ui::PropertyEditWidget *ui;
    QMetaProperty m_property;
    QObject* m_object;

    QLineEdit* m_lineEdit;
    QSpinBox* m_spinBox;
    QDoubleSpinBox* m_doubleSpinBox;
    QCheckBox* m_checkBox;
    QToolButton* m_toolButton;

    QStringList m_fileExtensions;
    QString m_fileDirectory;

private slots:
    void getStringFromFile();
};

#endif // PROPERTYEDITWIDGET_H