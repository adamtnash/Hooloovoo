#ifndef GAMEFILEDIALOG_H
#define GAMEFILEDIALOG_H

#include <QDialog>
#include "filepreviewwidget.h"

namespace Ui {
    class GameFileDialog;
}

class GameFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameFileDialog(QWidget *parent = 0);
    ~GameFileDialog();

    enum AcceptMode { Select, Load, Save, Create };

    QString getFileName();
    QStringList getAllAvailableFiles();

    void setAcceptMode(AcceptMode mode);
    void setFileType(FileManager::FileType type);

private:
    Ui::GameFileDialog *ui;

    FilePreviewWidget* m_previewWidget;
    FileManager::FileType m_type;
    QStringList m_extensions;
    QString m_directory;

    void setupPreviewWidget();

private slots:
    void fileSelectionChanged();
    void importFiles();
};

#endif // GAMEFILEDIALOG_H
