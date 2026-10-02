(function () {
  'use strict';

  // A deliberately small Markdown reader. Source HTML and links stay plain text;
  // all rendered content is built with DOM nodes, never with innerHTML.
  function appendInline(parent, source, depth) {
    depth = depth || 0;
    if (depth > 8) {
      parent.appendChild(document.createTextNode(source));
      return;
    }

    var buffer = '';
    function flush() {
      if (buffer) parent.appendChild(document.createTextNode(buffer));
      buffer = '';
    }

    for (var i = 0; i < source.length;) {
      var character = source[i];
      if (character === '\\' && /[\\`*_{}\[\]()#+.!>-]/.test(source[i + 1] || '')) {
        buffer += source[i + 1];
        i += 2;
        continue;
      }

      var markers = character === '*' ? ['***', '**', '*'] :
        character === '_' ? ['___', '__', '_'] :
        character === '`' ? ['`'] : [];
      var matched = false;
      for (var m = 0; m < markers.length; m++) {
        var marker = markers[m];
        if (source.slice(i, i + marker.length) !== marker) continue;
        // Keep identifiers such as Emmanuel_Lau intact.
        if (character === '_' && /[\p{L}\p{N}]/u.test(source[i - 1] || '')) continue;
        var start = i + marker.length;
        var end = source.indexOf(marker, start);
        while (end !== -1 && source[end - 1] === '\\') {
          end = source.indexOf(marker, end + marker.length);
        }
        if (end <= start || (character !== '`' &&
            (/\s/.test(source[start]) || /\s/.test(source[end - 1])))) continue;

        flush();
        var node = document.createElement(character === '`' ? 'code' :
          marker.length >= 2 ? 'strong' : 'em');
        var content = source.slice(start, end);
        if (character === '`') {
          node.textContent = content;
        } else if (marker.length === 3) {
          var emphasis = document.createElement('em');
          appendInline(emphasis, content, depth + 1);
          node.appendChild(emphasis);
        } else {
          appendInline(node, content, depth + 1);
        }
        parent.appendChild(node);
        i = end + marker.length;
        matched = true;
        break;
      }
      if (!matched) {
        buffer += character;
        i++;
      }
    }
    flush();
  }

  function appendParagraph(parent, lines) {
    var paragraph = document.createElement('p');
    lines.forEach(function (line, index) {
      var hardBreak = /(?:\\| {2,})$/.test(line);
      appendInline(paragraph, hardBreak ? line.replace(/(?:\\| {2,})$/, '') : line);
      if (index < lines.length - 1) {
        paragraph.appendChild(hardBreak ? document.createElement('br') : document.createTextNode('\n'));
      }
    });
    parent.appendChild(paragraph);
  }

  function isRule(line) {
    return /^ {0,3}(?:(?:\*\s*){3,}|(?:-\s*){3,}|(?:_\s*){3,})$/.test(line);
  }

  function listMatch(line) {
    return /^ {0,3}([-+*]|\d+[.)])[ \t]+(.*)$/.exec(line);
  }

  function startsBlock(line) {
    return /^ {0,3}(?:#{1,6}[ \t]+|>|```|~~~)/.test(line) || isRule(line) || !!listMatch(line);
  }

  function renderBlocks(lines, depth) {
    var fragment = document.createDocumentFragment();
    depth = depth || 0;
    if (depth > 12) {
      appendParagraph(fragment, lines);
      return fragment;
    }

    for (var i = 0; i < lines.length;) {
      var line = lines[i];
      if (!line.trim()) {
        i++;
        continue;
      }

      var fence = /^ {0,3}(`{3,}|~{3,})/.exec(line);
      if (fence) {
        var codeLines = [];
        var fenceEnd = new RegExp('^ {0,3}' + fence[1][0] + '{' + fence[1].length + ',}\\s*$');
        i++;
        while (i < lines.length && !fenceEnd.test(lines[i])) codeLines.push(lines[i++]);
        if (i < lines.length) i++;
        var pre = document.createElement('pre');
        var code = document.createElement('code');
        code.textContent = codeLines.join('\n');
        pre.appendChild(code);
        fragment.appendChild(pre);
        continue;
      }

      var heading = /^ {0,3}(#{1,6})[ \t]+(.+?)\s*$/.exec(line);
      if (heading) {
        var title = document.createElement('h' + heading[1].length);
        appendInline(title, heading[2].replace(/[ \t]+#+[ \t]*$/, ''));
        fragment.appendChild(title);
        i++;
        continue;
      }
      if (isRule(line)) {
        fragment.appendChild(document.createElement('hr'));
        i++;
        continue;
      }

      if (/^ {0,3}>/.test(line)) {
        var quoteLines = [];
        while (i < lines.length && /^ {0,3}>/.test(lines[i])) {
          quoteLines.push(lines[i++].replace(/^ {0,3}>[ \t]?/, ''));
        }
        var quote = document.createElement('blockquote');
        quote.appendChild(renderBlocks(quoteLines, depth + 1));
        fragment.appendChild(quote);
        continue;
      }

      var item = listMatch(line);
      if (item) {
        var ordered = /^\d/.test(item[1]);
        var list = document.createElement(ordered ? 'ol' : 'ul');
        if (ordered) list.start = parseInt(item[1], 10);
        while (i < lines.length) {
          item = listMatch(lines[i]);
          if (!item || /^\d/.test(item[1]) !== ordered || isRule(lines[i])) break;
          var entry = document.createElement('li');
          appendInline(entry, item[2]);
          list.appendChild(entry);
          i++;
        }
        fragment.appendChild(list);
        continue;
      }

      var paragraphLines = [line];
      i++;
      while (i < lines.length && lines[i].trim() && !startsBlock(lines[i])) {
        paragraphLines.push(lines[i++]);
      }
      appendParagraph(fragment, paragraphLines);
    }
    return fragment;
  }

  function bilingual(node, chinese, english) {
    node.appendChild(document.createTextNode(chinese + ' '));
    var translation = document.createElement('span');
    translation.className = 'en';
    translation.lang = 'en';
    translation.textContent = english;
    node.appendChild(translation);
    return node;
  }

  function prepareReader(details) {
    var body = details.querySelector('.markdown-body');
    if (!body) return;
    var state = 'idle';

    async function load() {
      if (state === 'loading' || state === 'loaded') return;
      state = 'loading';
      body.setAttribute('aria-busy', 'true');
      var status = bilingual(document.createElement('p'), '正在加载读书笔记…', 'Loading reading notes…');
      status.className = 'reading-status';
      status.setAttribute('role', 'status');
      body.replaceChildren(status);

      var controller = new AbortController();
      var timeout = window.setTimeout(function () { controller.abort(); }, 15000);
      try {
        var response = await fetch(details.dataset.source, { cache: 'no-cache', signal: controller.signal });
        if (!response.ok) throw new Error('Unable to load reading notes: ' + response.status);
        var markdown = await response.text();
        body.replaceChildren(renderBlocks(markdown.replace(/^\uFEFF/, '').replace(/\r\n?/g, '\n').split('\n')));
        state = 'loaded';
      } catch (error) {
        state = 'error';
        var message = bilingual(document.createElement('p'),
          '暂时无法加载，请重试或下载 Markdown 文件阅读。',
          'Could not load the notes. Please retry or download the Markdown file.');
        message.className = 'reading-status reading-error';
        message.setAttribute('role', 'alert');
        var retry = bilingual(document.createElement('button'), '重试', 'Retry');
        retry.type = 'button';
        retry.className = 'reading-retry';
        retry.addEventListener('click', load);
        body.replaceChildren(message, retry);
      } finally {
        window.clearTimeout(timeout);
        body.setAttribute('aria-busy', 'false');
      }
    }

    details.addEventListener('toggle', function () {
      if (details.open) load();
    });
    if (details.open) load();
  }

  function initialize() {
    document.querySelectorAll('details.book-notes[data-source]').forEach(prepareReader);
  }
  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', initialize, { once: true });
  } else {
    initialize();
  }
})();
