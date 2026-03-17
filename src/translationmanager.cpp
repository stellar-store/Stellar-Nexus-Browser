#include "translationmanager.h"

TranslationManager::TranslationManager() {
    initTranslations();
}

TranslationManager& TranslationManager::instance() {
    static TranslationManager mgr;
    return mgr;
}

void TranslationManager::setLanguage(const QString &lang) {
    if (lang == "English" || lang == "Español" || lang == "Português") {
        m_currentLanguage = lang;
    }
}

QString TranslationManager::currentLanguage() const {
    return m_currentLanguage;
}

QString TranslationManager::tr(const char *context, const char *text) {
    Q_UNUSED(context);
    QString key(text);

    if (m_translations.contains(m_currentLanguage)) {
        if (m_translations[m_currentLanguage].contains(key)) {
            return m_translations[m_currentLanguage][key];
        }
    }
    return QString::fromUtf8(text);
}

void TranslationManager::initTranslations() {
    // English translations (default)
    QMap<QString, QString> en;
    en["Settings"] = "Settings";
    en["General"] = "General";
    en["Appearance"] = "Appearance";
    en["Privacy"] = "Privacy";
    en["History"] = "History";
    en["Favorites"] = "Favorites";
    en["Language"] = "Language";
    en["About"] = "About";
    en["Search Engine"] = "Search Engine";
    en["Home Page"] = "Home Page";
    en["Theme"] = "Theme";
    en["Dark mode"] = "Dark mode";
    en["Accent Color"] = "Accent Color";
    en["Choose Color…"] = "Choose Color…";
    en["Enable JavaScript"] = "Enable JavaScript";
    en["Accept Cookies"] = "Accept Cookies";
    en["Some settings require restarting tabs to take effect."] = "Some settings require restarting tabs to take effect.";
    en["Manage your browsing history settings"] = "Manage your browsing history settings";
    en["Keep history for 90 days"] = "Keep history for 90 days";
    en["Clear History"] = "Clear History";
    en["Saved Favorites"] = "Saved Favorites";
    en["Remove"] = "Remove";
    en["Application Language"] = "Application Language";
    en["Select your preferred language:"] = "Select your preferred language:";
    en["Note: Language changes will take effect immediately."] = "Note: Language changes will take effect immediately.";
    en["Stellar Nexus Browser"] = "Stellar NexusBrowser";
    en["Version 1.0.0"] = "Version 1.0.0";
    en["Cancel"] = "Cancel";
    en["Save"] = "Save";
    en["Cancel and discard changes"] = "Cancel and discard changes";
    en["Save settings and close"] = "Save settings and close";
    m_translations["English"] = en;

    // Spanish translations
    QMap<QString, QString> es;
    es["Settings"] = "Configuración";
    es["General"] = "General";
    es["Appearance"] = "Apariencia";
    es["Privacy"] = "Privacidad";
    es["History"] = "Historial";
    es["Favorites"] = "Favoritos";
    es["Language"] = "Idioma";
    es["About"] = "Acerca de";
    es["Search Engine"] = "Motor de Búsqueda";
    es["Home Page"] = "Página de Inicio";
    es["Theme"] = "Tema";
    es["Dark mode"] = "Modo oscuro";
    es["Accent Color"] = "Color de Acento";
    es["Choose Color…"] = "Elegir Color…";
    es["Enable JavaScript"] = "Habilitar JavaScript";
    es["Accept Cookies"] = "Aceptar Cookies";
    es["Some settings require restarting tabs to take effect."] = "Algunos ajustes requieren reiniciar las pestañas para tomar efecto.";
    es["Manage your browsing history settings"] = "Administre su configuración de historial de navegación";
    es["Keep history for 90 days"] = "Mantener historial por 90 días";
    es["Clear History"] = "Limpiar Historial";
    es["Saved Favorites"] = "Favoritos Guardados";
    es["Remove"] = "Eliminar";
    es["Application Language"] = "Idioma de la Aplicación";
    es["Select your preferred language:"] = "Seleccione su idioma preferido:";
    es["Note: Language changes will take effect immediately."] = "Nota: Los cambios de idioma tendrán efecto inmediatamente.";
    es["Stellar Browser"] = "Navegador Stellar";
    es["Version 1.0.0"] = "Versión 1.0.0";
    es["Cancel"] = "Cancelar";
    es["Save"] = "Guardar";
    es["Cancel and discard changes"] = "Cancelar y descartar cambios";
    es["Save settings and close"] = "Guardar configuración y cerrar";
    m_translations["Español"] = es;

    // Portuguese translations
    QMap<QString, QString> pt;
    pt["Settings"] = "Configurações";
    pt["General"] = "Geral";
    pt["Appearance"] = "Aparência";
    pt["Privacy"] = "Privacidade";
    pt["History"] = "Histórico";
    pt["Favorites"] = "Favoritos";
    pt["Language"] = "Idioma";
    pt["About"] = "Sobre";
    pt["Search Engine"] = "Mecanismo de Pesquisa";
    pt["Home Page"] = "Página Inicial";
    pt["Theme"] = "Tema";
    pt["Dark mode"] = "Modo escuro";
    pt["Accent Color"] = "Cor de Destaque";
    pt["Choose Color…"] = "Escolher Cor…";
    pt["Enable JavaScript"] = "Habilitar JavaScript";
    pt["Accept Cookies"] = "Aceitar Cookies";
    pt["Some settings require restarting tabs to take effect."] = "Algumas configurações requerem reiniciar as guias para entrar em vigor.";
    pt["Manage your browsing history settings"] = "Gerencie as configurações do seu histórico de navegação";
    pt["Keep history for 90 days"] = "Manter histórico por 90 dias";
    pt["Clear History"] = "Limpar Histórico";
    pt["Saved Favorites"] = "Favoritos Salvos";
    pt["Remove"] = "Remover";
    pt["Application Language"] = "Idioma da Aplicação";
    pt["Select your preferred language:"] = "Selecione seu idioma preferido:";
    pt["Note: Language changes will take effect immediately."] = "Nota: As alterações de idioma terão efeito imediatamente.";
    pt["Stellar Browser"] = "Navegador Stellar";
    pt["Version 1.0.0"] = "Versão 1.0.0";
    pt["Cancel"] = "Cancelar";
    pt["Save"] = "Guardar";
    pt["Cancel and discard changes"] = "Cancelar e descartar alterações";
    pt["Save settings and close"] = "Salvar configurações e fechar";
    m_translations["Português"] = pt;
}
