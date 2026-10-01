function getSelectedCgiExtension() {
    var selector = document.getElementById('cgi-selector');
    if (selector && (selector.value === '.php' || selector.value === '.py')) {
        return selector.value;
    }

    if (typeof localStorage !== 'undefined') {
        var stored = localStorage.getItem('cgi-extension');
        if (stored === '.php' || stored === '.py') {
            return stored;
        }
    }

    return '.php';
}

function setSelectedCgiExtension(extension) {
    if (typeof localStorage !== 'undefined') {
        localStorage.setItem('cgi-extension', extension);
    }
}

function updateCGI() {
    var extension = getSelectedCgiExtension();
    var selector = document.getElementById('cgi-selector');

    if (selector) {
        selector.value = extension;
    }

    var targets = document.querySelectorAll('[data-cgi-php][data-cgi-py]');
    for (var i = 0; i < targets.length; ++i) {
        var target = targets[i];
        var nextPath = extension === '.py' ? target.getAttribute('data-cgi-py') : target.getAttribute('data-cgi-php');

        if (!nextPath)
            continue;

        if (target.tagName === 'FORM') {
            target.action = nextPath;
        } else {
            target.setAttribute('href', nextPath);
        }
    }

    setSelectedCgiExtension(extension);
}

document.addEventListener('DOMContentLoaded', function() {
    var selector = document.getElementById('cgi-selector');
    if (selector) {
        selector.value = getSelectedCgiExtension();
        selector.addEventListener('change', function() {
            updateCGI();
        });
    }

    updateCGI();
});