#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphicsview.h"
#include "levelmanager.h"
#include <QDockWidget>
#include "gameobjecteditwidget.h"
#include "causeandeffecteditwidget.h"
#include "gameobjectfilewidget.h"
#include <QToolBar>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;

    void initializeMenus();

    GraphicsView *m_gameGraphicsView;
    GraphicsView *m_editorGraphicsView;

    QMenu* m_editorViewMenu;
    QMenu* m_playGameMenu;
    QMenu* m_createGameMenu;
    QMenu* m_levelMenu;
    QMenu* m_objectMenu;
    QMenu* m_helpMenu;

    QDockWidget* m_levelManagerDock;
    LevelManager *m_levelManager;

    QDockWidget *m_gameObjectEditorDock;
    GameObjectEditWidget *m_gameObjectEditorView;

    QDockWidget *m_causeAndEffectEditDock;
    CauseAndEffectEditWidget *m_causeAndEffectEditWidget;

    GameObjectFileWidget *m_fileBrowserWidget;
    QDockWidget *m_fileBrowserDock;

    QToolBar* m_previewControlBar;

signals:

public slots:
    void refreshGameList();

private slots:
    void startScreenEditGame();
    void startScreenPlayGame();
    void startScreenFileSelected();

    void switchToStartScreen();
    void switchToGameScreen();
    void switchToGameEditorScreen();

    void launchLevelManager();
    void gameObjectSelectionChanged(bool);

    void pauseByFocus();
    void pauseGame(bool);

    void showLevelManager(bool show) {m_levelManagerDock->setVisible(show);}
    void showObjectEditor(bool show) {m_gameObjectEditorDock->setVisible(show); m_causeAndEffectEditDock->setVisible(show);}
    void showFileBrowser(bool show) {m_fileBrowserDock->setVisible(show);}

    void launchAboutDialog();
};

#endif // MAINWINDOW_H
