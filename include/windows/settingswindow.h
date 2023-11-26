//
// Created by Marwin Nowak on 26.11.23.
//

#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWindow>

class SettingsWindow : public QWindow {
    Q_OBJECT

public:
    explicit SettingsWindow(QWindow *parent = nullptr);
    ~SettingsWindow() override;
};

#endif //SETTINGSWINDOW_H
