//
// Created by Marwin Nowak on 26.11.23.
//

#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QVBoxLayout>

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget* parent = nullptr);
    ~SettingsWindow() override;
};

#endif //SETTINGSWINDOW_H
