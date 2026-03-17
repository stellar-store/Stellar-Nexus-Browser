#include "browserpage.h"
#include <QSettings>
#include <QDateTime>
#include <QVBoxLayout>

// ──────────────────────────────────────────────────────────────────
// NexusWebPage
// ──────────────────────────────────────────────────────────────────
NexusWebPage::NexusWebPage(QWebEngineProfile *profile, QObject *parent)
    : QWebEnginePage(profile, parent) {}

QWebEnginePage* NexusWebPage::createWindow(WebWindowType) {
    emit newWindowRequested(QUrl());
    return nullptr; // We handle it via signal
}

// ──────────────────────────────────────────────────────────────────
// BrowserPage
// ──────────────────────────────────────────────────────────────────
BrowserPage::BrowserPage(QWidget *parent) : QWidget(parent) {
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);

    auto *profile = QWebEngineProfile::defaultProfile();
    auto *page    = new NexusWebPage(profile, this);

    m_view = new QWebEngineView(this);
    m_view->setPage(page);
    m_layout->addWidget(m_view);

    // Enable downloads
    connect(profile, &QWebEngineProfile::downloadRequested,
            this, &BrowserPage::downloadRequested);

    connect(page, &NexusWebPage::newWindowRequested,
            this, &BrowserPage::newTabRequested);

    connect(m_view, &QWebEngineView::urlChanged,   this, &BrowserPage::urlChanged);
    connect(m_view, &QWebEngineView::titleChanged,  this, &BrowserPage::titleChanged);
    connect(m_view, &QWebEngineView::loadProgress,  this, &BrowserPage::loadProgress);
    connect(m_view, &QWebEngineView::loadFinished,  this, &BrowserPage::loadFinished);
    connect(m_view, &QWebEngineView::iconChanged,   this, &BrowserPage::iconChanged);
}

void BrowserPage::load(const QUrl &url) {
    if (url.toString() == "nexus://home") {
        m_isHome = true;
        showHomePage();
        emit urlChanged(url);
        emit titleChanged("Home");
    } else {
        m_isHome = false;
        m_view->load(url);
    }
}

void BrowserPage::back()    { m_view->back(); }
void BrowserPage::forward() { m_view->forward(); }
void BrowserPage::reload()  {
    if (m_isHome) { showHomePage(); return; }
    m_view->reload();
}

bool BrowserPage::canGoBack()    const { return m_view->history()->canGoBack(); }
bool BrowserPage::canGoForward() const { return m_view->history()->canGoForward(); }
QUrl BrowserPage::url()          const { return m_isHome ? QUrl("nexus://home") : m_view->url(); }
QString BrowserPage::title()     const { return m_isHome ? "Home" : m_view->title(); }

void BrowserPage::showHomePage() {
    QSettings s("StellarNexusBrowser", "Stellar");
    bool dark   = s.value("theme/dark", true).toBool();
    QString acc = s.value("theme/accent", "#4FC3F7").toString();

    QString bg    = dark ? "#0D1117" : "#F0F4F8";
    QString bg2   = dark ? "#161B22" : "#FFFFFF";
    QString bg3   = dark ? "#1C2330" : "#E8EDF3";
    QString text  = dark ? "#E6EDF3" : "#1A2332";
    QString muted = dark ? "#8B949E" : "#656D76";
    QString bdr   = dark ? "#30363D" : "#D0D7DE";

    // Get current time
    QString timeStr = QDateTime::currentDateTime().toString("hh:mm");
    QString dateStr = QDateTime::currentDateTime().toString("dddd, MMMM d");

    QString searchEngine = s.value("search/engine", "https://duckduckgo.com/?q=").toString();
    QString engineName = "DuckDuckGo";
    if (searchEngine.contains("google")) engineName = "Google";
    else if (searchEngine.contains("bing")) engineName = "Bing";
    else if (searchEngine.contains("startpage")) engineName = "Startpage";

    QString html = QString(R"HTML(<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Home</title>
<style>
  @import url('https://fonts.googleapis.com/css2?family=Space+Mono:wght@400;700&display=swap');

  * { margin:0; padding:0; box-sizing:border-box; }

  :root {
    --bg: %1;
    --bg2: %2;
    --bg3: %3;
    --text: %4;
    --muted: %5;
    --accent: %6;
    --border: %7;
  }

  body {
    background: var(--bg);
    color: var(--text);
    font-family: 'Space Mono', 'JetBrains Mono', monospace;
    min-height: 100vh;
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    overflow: hidden;
  }

  /* Animated grid background */
  body::before {
    content: '';
    position: fixed;
    inset: 0;
    background-image:
      linear-gradient(rgba(79,195,247,0.03) 1px, transparent 1px),
      linear-gradient(90deg, rgba(79,195,247,0.03) 1px, transparent 1px);
    background-size: 40px 40px;
    pointer-events: none;
    z-index: 0;
  }

  /* Radial glow */
  body::after {
    content: '';
    position: fixed;
    top: 30%;
    left: 50%;
    transform: translate(-50%, -50%);
    width: 600px;
    height: 600px;
    background: radial-gradient(ellipse, rgba(79,195,247,0.06) 0%, transparent 70%);
    pointer-events: none;
    z-index: 0;
  }

  .container {
    position: relative;
    z-index: 1;
    text-align: center;
    width: 100%;
    max-width: 680px;
    padding: 40px 24px;
    display: flex;
    flex-direction: column;
    align-items: center;
    gap: 32px;
    animation: fadeUp 0.6s ease forwards;
  }

  @keyframes fadeUp {
    from { opacity:0; transform: translateY(20px); }
    to   { opacity:1; transform: translateY(0); }
  }

  .clock {
    font-size: 72px;
    font-weight: 700;
    color: var(--text);
    letter-spacing: -2px;
    line-height: 1;
    text-shadow: 0 0 40px rgba(79,195,247,0.3);
  }

  .clock span { color: var(--accent); }

  .date {
    font-size: 14px;
    color: var(--muted);
    letter-spacing: 3px;
    text-transform: uppercase;
    margin-top: -20px;
  }

  /* Logo / wordmark */
  .logo {
    display: flex;
    align-items: center;
    gap: 12px;
    margin-bottom: -12px;
  }

  .logo-mark {
    width: 40px;
    height: 40px;
    border: 2px solid var(--accent);
    border-radius: 10px;
    display: flex;
    align-items: center;
    justify-content: center;
    font-size: 20px;
    color: var(--accent);
    box-shadow: 0 0 20px rgba(79,195,247,0.2);
  }

  .logo-text {
    font-size: 22px;
    font-weight: 700;
    color: var(--text);
    letter-spacing: 4px;
    text-transform: uppercase;
  }

  /* Search bar */
  .search-wrapper {
    width: 100%;
    position: relative;
  }

  .search-bar {
    width: 100%;
    padding: 16px 54px 16px 22px;
    font-family: inherit;
    font-size: 15px;
    background: var(--bg2);
    border: 1px solid var(--border);
    border-radius: 14px;
    color: var(--text);
    outline: none;
    transition: border-color 0.2s, box-shadow 0.2s;
    letter-spacing: 0.3px;
  }

  .search-bar::placeholder { color: var(--muted); }

  .search-bar:focus {
    border-color: var(--accent);
    box-shadow: 0 0 0 3px rgba(79,195,247,0.12), 0 4px 20px rgba(0,0,0,0.3);
  }

  .search-icon {
    position: absolute;
    right: 16px;
    top: 50%;
    transform: translateY(-50%);
    font-size: 18px;
    color: var(--muted);
    cursor: pointer;
    transition: color 0.2s;
    user-select: none;
  }

  .search-icon:hover { color: var(--accent); }

  /* Suggestions dropdown */
  .suggestions-dropdown {
    position: absolute;
    top: 100%;
    left: 0;
    right: 0;
    background: var(--bg2);
    border: 1px solid var(--accent);
    border-top: none;
    border-radius: 0 0 12px 12px;
    max-height: 300px;
    overflow-y: auto;
    display: none;
    z-index: 1000;
    box-shadow: 0 4px 20px rgba(0,0,0,0.3);
  }

  .suggestions-dropdown.active { display: block; }

  .suggestion-item {
    padding: 12px 16px;
    cursor: pointer;
    border-bottom: 1px solid var(--border);
    font-size: 14px;
    color: var(--text);
    transition: background 0.15s;
    display: flex;
    align-items: center;
    gap: 8px;
  }

  .suggestion-item:last-child { border-bottom: none; }

  .suggestion-item:hover,
  .suggestion-item.selected {
    background: var(--bg3);
    color: var(--accent);
  }

  .suggestion-icon {
    color: var(--muted);
    font-size: 12px;
    min-width: 16px;
  }

  .search-engine-label {
    font-size: 11px;
    color: var(--muted);
    margin-top: 8px;
    letter-spacing: 1px;
  }

  /* Quick links */
  .quick-links {
    display: grid;
    grid-template-columns: repeat(4, 1fr);
    gap: 12px;
    width: 100%;
  }

  .quick-link {
    display: flex;
    flex-direction: column;
    align-items: center;
    gap: 8px;
    padding: 16px 8px;
    background: var(--bg2);
    border: 1px solid var(--border);
    border-radius: 12px;
    cursor: pointer;
    text-decoration: none;
    color: var(--text);
    transition: all 0.2s;
    font-family: inherit;
    font-size: 11px;
    letter-spacing: 1px;
    text-transform: uppercase;
  }

  .quick-link:hover {
    border-color: var(--accent);
    background: var(--bg3);
    transform: translateY(-2px);
    box-shadow: 0 8px 24px rgba(0,0,0,0.3);
  }

  .quick-link .icon {
    font-size: 22px;
    line-height: 1;
  }

  .quick-link .label {
    color: var(--muted);
  }

  /* Status bar at bottom */
  .status-bar {
    position: fixed;
    bottom: 0;
    left: 0;
    right: 0;
    height: 28px;
    background: var(--bg2);
    border-top: 1px solid var(--border);
    display: flex;
    align-items: center;
    padding: 0 16px;
    gap: 20px;
    z-index: 2;
  }

  .status-item {
    font-size: 10px;
    color: var(--muted);
    letter-spacing: 1px;
    text-transform: uppercase;
  }

  .status-dot {
    display: inline-block;
    width: 6px;
    height: 6px;
    border-radius: 50%;
    background: var(--accent);
    margin-right: 6px;
    animation: pulse 2s infinite;
  }

  @keyframes pulse {
    0%, 100% { opacity:1; }
    50% { opacity:0.3; }
  }
</style>
</head>
<body>
<div class="container">
  <div class="logo">
    <div class="logo-mark">⬡</div>
    <div class="logo-text">Stellar Nexus</div>
  </div>

  <div class="clock">%8<span>:</span>%9</div>
  <div class="date">%10</div>

  <div class="search-wrapper">
    <input class="search-bar" id="search" type="text" placeholder="Search or enter address…" autofocus>
    <div class="search-icon" onclick="doSearch()">&#9040;</div>
    <div class="suggestions-dropdown" id="suggestionsDropdown"></div>
  </div>
  <div class="search-engine-label">searching with %11</div>

  <div class="quick-links">
    <a class="quick-link" href="https://gbonachea.github.io/">
      <span class="icon">&#8997;</span>
      <span class="label">GBonachea</span>
    </a>
    <a class="quick-link" href="https://stellar-store.github.io/">
      <span class="icon">&#9651;</span>
      <span class="label">Stellar Store</span>
    </a>
    <a class="quick-link" href="https://br-cybec.github.io/">
      <span class="icon">&#9672;</span>
      <span class="label">B&R</span>
    </a>
    <a class="quick-link" href="https://wikipedia.org">
      <span class="icon">&#9673;</span>
      <span class="label">Wikipedia</span>
    </a>
  </div>
</div>

<div class="status-bar">
  <div class="status-item"><span class="status-dot"></span>Stellar Browser</div>
  <div class="status-item">v1.0.0</div>
  <div class="status-item">Secure · Private · Fast</div>
</div>

<script>
  document.addEventListener('DOMContentLoaded', function() {
    let selectedIndex = -1;
    let abortController = null;

    const searchInput = document.getElementById('search');
    const suggestionsDiv = document.getElementById('suggestionsDropdown');

    // Sugerencias locales como fallback
    const localSuggestions = {
    'git': ['GitHub', 'Git Documentation'],
    'how': ['How to Center a Div', 'How to Learn JavaScript'],
    'best': ['Best JavaScript Practices', 'Best CSS Frameworks'],
    'python': ['Python Official', 'Python Documentation'],
    'java': ['Java Documentation', 'JavaScript'],
    'web': ['Web Development', 'WebGL'],
    'api': ['REST API', 'GraphQL API'],
    'react': ['React Documentation', 'React Router'],
    'node': ['Node.js', 'NodeJS Package Manager'],
    'css': ['CSS Documentation', 'CSS Grid'],
    'html': ['HTML Documentation', 'HTML Tutorials'],
    'stack': ['Stack Overflow', 'Stackshare']
  };

  // Mostrar/ocultar sugerencias al escribir
  searchInput.addEventListener('input', function() {
    const query = this.value.trim();
    
    if (query.length === 0) {
      suggestionsDiv.classList.remove('active');
      selectedIndex = -1;
      return;
    }

    // Cancelar petición anterior si existe
    if (abortController) {
      abortController.abort();
    }
    abortController = new AbortController();

    // Mostrar indicador de carga
    suggestionsDiv.innerHTML = '<div class="suggestion-item" style="color: var(--muted);">Buscando...</div>';
    suggestionsDiv.classList.add('active');

    // Petición a Wikipedia API (soporta CORS)
    fetch(`https://en.wikipedia.org/w/api.php?action=opensearch&search=${encodeURIComponent(query)}&limit=8&namespace=0&format=json&origin=*`, {
      signal: abortController.signal
    })
      .then(response => response.json())
      .then(data => {
        if (!data || !data[1] || data[1].length === 0) {
          throw new Error('No suggestions');
        }

        // Wikipedia devuelve [query, [titles], [descriptions], [urls]]
        // Mostrar sugerencias
        suggestionsDiv.innerHTML = data[1].slice(0, 8).map((s, idx) => 
          `<div class="suggestion-item" data-index="${idx}" data-text="${s.replace(/"/g, '&quot;').replace(/&/g, '&amp;')}">
            <span class="suggestion-icon">🔍</span>
            <span>${s}</span>
          </div>`
        ).join('');
        
        selectedIndex = -1;
      })
      .catch(error => {
        // Ignorar errores por AbortError
        if (error.name === 'AbortError') {
          return;
        }

        // Si falla Wikipedia, usar sugerencias locales
        const queryLower = query.toLowerCase();
        let suggestions = [];

        // Buscar en sugerencias locales
        for (const [key, values] of Object.entries(localSuggestions)) {
          if (key.includes(queryLower) || queryLower.includes(key)) {
            suggestions.push(...values);
          }
        }

        // Si no hay sugerencias locales, mostrar la búsqueda actual
        if (suggestions.length === 0) {
          suggestions = [query];
        }

        suggestionsDiv.innerHTML = suggestions.slice(0, 8).map((s, idx) => 
          `<div class="suggestion-item" data-index="${idx}" data-text="${s.replace(/"/g, '&quot;').replace(/&/g, '&amp;')}">
            <span class="suggestion-icon">🔍</span>
            <span>${s}</span>
          </div>`
        ).join('');
        
        selectedIndex = -1;
      });
  });

  // Navegación con teclado
  searchInput.addEventListener('keydown', function(e) {
    const items = suggestionsDiv.querySelectorAll('.suggestion-item');
    
    if (e.key === 'ArrowDown') {
      e.preventDefault();
      selectedIndex = Math.min(selectedIndex + 1, items.length - 1);
      updateSelection(items);
    } else if (e.key === 'ArrowUp') {
      e.preventDefault();
      selectedIndex = Math.max(selectedIndex - 1, -1);
      updateSelection(items);
    } else if (e.key === 'Enter') {
      if (selectedIndex >= 0 && items[selectedIndex]) {
        e.preventDefault();
        selectSuggestion(items[selectedIndex].textContent.trim());
      } else {
        doSearch();
      }
    } else if (e.key === 'Escape') {
      suggestionsDiv.classList.remove('active');
      selectedIndex = -1;
      if (abortController) {
        abortController.abort();
      }
    }
  });

  function updateSelection(items) {
    items.forEach((item, idx) => {
      if (idx === selectedIndex) {
        item.classList.add('selected');
        item.scrollIntoView({ block: 'nearest' });
      } else {
        item.classList.remove('selected');
      }
    });
  }

  // Manejar clic en sugerencias con delegación de eventos
  suggestionsDiv.addEventListener('click', function(e) {
    const suggestionItem = e.target.closest('.suggestion-item');
    if (suggestionItem) {
      const text = suggestionItem.getAttribute('data-text');
      if (text) {
        selectSuggestion(text);
      }
    }
  });

  function selectSuggestion(text) {
    searchInput.value = text;
    suggestionsDiv.classList.remove('active');
    selectedIndex = -1;
    if (abortController) {
      abortController.abort();
    }
    doSearch();
  }

  // Cerrar dropdown al hacer click afuera
  document.addEventListener('click', function(e) {
    if (e.target !== searchInput && !suggestionsDiv.contains(e.target)) {
      suggestionsDiv.classList.remove('active');
      selectedIndex = -1;
      if (abortController) {
        abortController.abort();
      }
    }
  });

  function doSearch() {
    var q = document.getElementById('search').value.trim();
    if (!q) return;
    if (q.startsWith('http://') || q.startsWith('https://') ||
        (q.includes('.') && !q.includes(' '))) {
      window.location.href = q.startsWith('http') ? q : 'https://' + q;
    } else {
      window.location.href = '%12' + encodeURIComponent(q);
    }
  }

    // Live clock update
    function updateClock() {
      var now = new Date();
      var h = String(now.getHours()).padStart(2,'0');
      var m = String(now.getMinutes()).padStart(2,'0');
      document.querySelector('.clock').innerHTML = h + '<span>:</span>' + m;
    }
    setInterval(updateClock, 10000);
  });
</script>
</body>
</html>
)HTML").arg(bg, bg2, bg3, text, muted, acc, bdr,
        timeStr.left(2), timeStr.right(2),
        dateStr, engineName,
        searchEngine);

    m_view->setHtml(html, QUrl("nexus://home"));
}

void BrowserPage::toggleTranslate() {
    if (m_isHome) return;  // No translate on home page
    
    // JavaScript code to load and toggle Google Translate
    QString script = R"JS(
        (function() {
            // Check if Google Translate Element already exists
            if (window.translateElementGoogleElement !== undefined) {
                // If exists, toggle visibility of the translate bar
                var bar = document.querySelector(".goog-te-banner-frame.skiptranslate");
                if (bar) {
                    bar.style.display = bar.style.display === "none" ? "block" : "none";
                }
                return;
            }
            
            // Load Google Translate Element
            var script = document.createElement('script');
            script.type = 'text/javascript';
            script.async = true;
            script.src = 'https://translate.google.com/translate_a/element.js?cb=googleTranslateElementInit';
            document.head.appendChild(script);
            
            // Define callback function
            window.googleTranslateElementInit = function() {
                new google.translate.TranslateElement({
                    pageLanguage: 'en',
                    layout: google.translate.TranslateElement.FloatPosition.TOP_LEFT,
                    autoDisplay: true
                }, 'google_translate_element');
            };
            
            // Create container for the translate widget
            var container = document.getElementById('google_translate_element');
            if (!container) {
                container = document.createElement('div');
                container.id = 'google_translate_element';
                container.style.cssText = 'position: fixed; top: 60px; right: 10px; z-index: 999999; background: white; padding: 10px; border-radius: 4px; box-shadow: 0 2px 8px rgba(0,0,0,0.15);';
                document.body.appendChild(container);
            }
        })();
    )JS";
    
    m_view->page()->runJavaScript(script);
}
