# Alpine Qt 6 Trial

Local branch `alpine-qt6`, based on SourceForge KDE commit `adc5c93` (v2.0.0).
This is an adaptation of the existing application, not a replacement search engine.

## Build and Check

Use the host's Qt 6.10.3. Required modules are Widgets, Concurrent and Core5Compat.
Core5Compat preserves the existing QRegExp search semantics. Only its development
headers were missing here; `qt6-qt5compat-dev=6.10.3-r0` was added without upgrading Qt.

```sh
mkdir -p build
cd build
/usr/lib/qt6/bin/qmake ../searchmonkey_2_0.pro
nice -n 10 make -j1
cd ..
sh tests/smoke.sh
```

The smoke check uses temporary data/settings and validates file rows, hit counts,
selection preview, UTF-8 content, empty results, filename-only search, and the
size/date signal connections. It writes `build/smoke.png` for visual inspection.
It is not a full audit of the legacy application. Qt's diagnostics still report
some pre-existing unused/removed UI objects; they are not silently suppressed.

## Changes

Ported removed Qt APIs and includes, replaced the removed directory completer
model, retained the creation-time fallback, made a comparison const-correct,
and adjusted old C++ template lookup. Size/date text-change handlers use the
Qt 6 signal names. Original line endings and search algorithms are preserved.

Normal input and preview text now use the active application's text palette,
not hard-coded black. Quick/Advanced validation and light/dark preview checks
pass; warning and match-highlight colors are unchanged. After a live theme
change, existing text adopts the new color on input refresh/preview reselection.

One optional directory argument preselects both Quick and Advanced search paths;
invalid directories or multiple arguments are rejected. No argument still uses
the original startup behavior.

## Installed Trial

- Binary: `~/.local/bin/searchmonkey-II`.
- Start menu: `~/.local/share/applications/searchmonkey-II.desktop`.
- Icon: `~/.local/share/icons/hicolor/96x96/apps/searchmonkey-II.png`.
- Launcher working directory: `~/.local/share/searchmonkey-II`, keeping the old
  relative `.smrc` preset file out of project directories when launched there.
- Original window geometry/MRU settings: `~/.config/Project Searchmonkey/Searchmonkey.conf`.
- Mugi-grep and its context-menu action are unchanged. No file-manager restart.

The supported layout is a file table above a selection preview. The original
source disables horizontal layout controls; this port does not re-enable them.
Search is plain-text/code and filenames; PDF/Office text extraction is not added.

## Why Not III Here

III v0.4.1's Linux tarball is a glibc executable. On this Alpine host, even with
existing gcompat, it fails before startup with missing `fcntl64` and `__res_init`.
No host compatibility shims or WebKit security workarounds were added.
Its frontend groups text matches by file, rather than offering II's compact
file-results table. Its source is at `~/dev/searchmonkey-III` for reference;
no Rust/WebKit build or installation was attempted.

## Removal

Remove the binary, desktop file and icon listed above. Keep the source and the
two settings locations if wanted. No system Qt rollback is necessary; the small
development-header package may be removed separately if no longer useful.
