#!/usr/bin/env bash
set -e
mkdir -p fonts
curl -L --fail -o fonts/SourceHanSansHWSC-Regular.otf https://raw.githubusercontent.com/adobe-fonts/source-han-sans/release/OTF/SimplifiedChineseHW/SourceHanSansHWSC-Regular.otf
curl -L --fail -o fonts/SourceHanSansHWSC-Bold.otf https://raw.githubusercontent.com/adobe-fonts/source-han-sans/release/OTF/SimplifiedChineseHW/SourceHanSansHWSC-Bold.otf
curl -L --fail -o fonts/Inconsolata-Regular.ttf https://raw.githubusercontent.com/google/fonts/main/ofl/inconsolata/static/Inconsolata-Regular.ttf
curl -L --fail -o fonts/Inconsolata-Bold.ttf https://raw.githubusercontent.com/google/fonts/main/ofl/inconsolata/static/Inconsolata-Bold.ttf
