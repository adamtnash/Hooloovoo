#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <QWidget>

namespace Ui {
    class LevelManager;
}

class LevelManager : public QWidget
{
    Q_OBJECT

public:
    explicit LevelManager(QWidget *parent = 0);
    ~LevelManager();

private:
    Ui::LevelManager *ui;

public slots:
    void update();

private slots:
    void renameSelectedLevel();
    void addLevel();
    void removeSelectedLevel();
    void setSelectedAsStartLevel();
    void editSelected();
    void reloadCurrentLevel();
    void saveCurrentLevel();

    void changeGameResolution();
    void changeLevelSize();
    void changeLevelGravity();
    void changeLevelColor();
};

#endif // LEVELMANAGER_H
