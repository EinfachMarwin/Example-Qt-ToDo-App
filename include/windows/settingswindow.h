//
// Created by Marwin Nowak on 26.11.23.
//

#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget* parent = nullptr);
    ~SettingsWindow() override;

    int loadDefaultDeadlineSetting();
    void saveDefaultDeadlineSetting(int defaultDeadline);

    private slots:
        void saveSettings();
        void reloadApplication();
        void closeSettings();

private:
    QPushButton* createButton(const QString& text);

    QPushButton* applyButton;
    QPushButton* okButton;
    QPushButton* cancelButton;
    QComboBox* defaultDeadlineDropdown;
};

#endif // SETTINGSWINDOW_H