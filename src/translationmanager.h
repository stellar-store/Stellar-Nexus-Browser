#pragma once
#include <QString>
#include <QMap>

class TranslationManager {
public:
    static TranslationManager& instance();

    void setLanguage(const QString &lang);
    QString currentLanguage() const;

    // UI Strings
    QString tr(const char *context, const char *text);

private:
    TranslationManager();
    QString m_currentLanguage = "English";

    QMap<QString, QMap<QString, QString>> m_translations;
    void initTranslations();
};

#define TRANSLATE(context, text) TranslationManager::instance().tr(context, text)
