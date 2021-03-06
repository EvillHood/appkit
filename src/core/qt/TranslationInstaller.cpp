/** @file
 * @brief      Helper function to install translations to application
 *
 *
 * $Id: $
 */

#include "qt/TranslationInstaller.h"

#include "qt/Strings.h"

#include <QCoreApplication>
#include <QDir>
#include <QLibraryInfo>
#include <QTranslator>

namespace qt
{

namespace
{

QStringList installTranslation(const QString& name, const QString& path)
{
    auto translator = new QTranslator(qApp); // NOLINT

    QStringList result;
    if (translator->load(name, path))
    {
        qApp->installTranslator(translator);
        result << QDir::toNativeSeparators(QString("%1/%2").arg(path, name));
    }
    return result;
}

} // namespace

QStringList installUserTranslation(
    const QString& name, const QString& path, const QLocale& locale)
{
    return installTranslation(QString("%1_%2").arg(name, locale.name()), path);
}

QStringList installSystemTranslation(const QString& name, const QLocale& locale)
{
    return installTranslation(
        QString("%1_%2").arg(name, locale.name()),
        QLibraryInfo::location(QLibraryInfo::TranslationsPath));
}

QStringList installUserTranslations(const QString& path, const QLocale& locale)
{
    QStringList result;
    QDir translationsDir(path);
    QString localeName(locale.name().split("_").first());
    static const QString nameFilter("*_%1*");

    const auto& files = translationsDir.entryList(
        QStringList() << nameFilter.arg(localeName)
                      << nameFilter.arg(locale.name()),
        QDir::Files);
    for (const auto& file: files)
    {
        result << installTranslation(file, path);
    }
    return result;
}

} // namespace qt
