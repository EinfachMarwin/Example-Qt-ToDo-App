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

    private slots:
        void saveSettings();
    void reloadApplication();
    void closeSettings();

private:
    void changeLanguage(const QString& language);
    void saveLanguageSetting(const QString& language);
    QPushButton* createButton(const QString& text);
    QComboBox* createLanguageDropdown();

    QPushButton* applyButton;
    QPushButton* okButton;
    QPushButton* cancelButton;
    QComboBox* languageDropdown;
};

#endif //SETTINGSWINDOW_H