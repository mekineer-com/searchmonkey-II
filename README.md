# Searchmonkey II for Qt 6

A Qt 6 adaptation of Searchmonkey II, tested on Alpine Linux. Search for files
and text, with a file-results table above a preview of the selected match.

This is a community fork of the [Searchmonkey project's KDE/Qt branch](https://sourceforge.net/p/searchmonkey/KDE/ci/master/tree/),
not a rewrite. Original authors include Adam Cottrell and Shawn OBrien; their
credits and GPLv3 license are preserved. The Qt 6 adaptation is maintained by
mekineer-com.

## Build

Requires a C++ compiler, make, Qt 6 qmake, Widgets, Concurrent and Core5Compat.
On Alpine, the Qt development packages are `qt6-qtbase-dev` and
`qt6-qt5compat-dev`; the build toolchain is available through `build-base`.

```sh
mkdir -p build
cd build
/usr/lib/qt6/bin/qmake ../searchmonkey_2_0.pro
make -j1
```

The executable is `build/searchmonkey`. It accepts an optional directory to
preselect for searching. See [ALPINE.md](ALPINE.md) for the tested environment,
checks and user-local desktop installation details.

## Scope

The port preserves the existing search algorithms and QRegExp behavior through
Core5Compat. It covers filenames and plain-text/code content, not PDF or Office
document extraction.

The supported layout is a file table above a preview. The original horizontal
layout controls remain disabled. Some legacy UI connection warnings remain;
Ctrl+Q did not close the tested window, while ordinary window-manager close
and Alt+F4 worked. This is a tested port, not a full audit of the old application.

The GPLv3 text is included in [COPYING](COPYING) and the application's
[license dialog source](license/license.ui).
