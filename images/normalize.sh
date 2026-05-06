#!/usr/bin/env bash
# Normalize cub3D XPM assets:
#   walls   -> 64x64,   indexed 256 colors
#   enemies -> 64x64,   indexed 256 colors, magenta (#FF00FF) chroma key on transparent areas
#   guns    -> 512x512, indexed 256 colors, magenta chroma key, sprite kept bottom-centered
#
# Originals are preserved. Outputs go to images/processed/<category>/<name>.xpm
# Run from anywhere; uses script's own location as base.

set -euo pipefail

BASE="$(cd "$(dirname "$0")" && pwd)"
OUT="$BASE/processed"
MAGENTA="#FF00FF"

echo "→ Output dir: $OUT"
rm -rf "$OUT"
mkdir -p "$OUT/wall" "$OUT/enemies" "$OUT/guns"

normalize() {
    local src="$1" dst="$2" size="$3" gravity="${4:-center}" colors="${5:-256}"
    magick "$src" \
        -background "$MAGENTA" -alpha remove -alpha off \
        -resize "${size}>" \
        -gravity "$gravity" -extent "$size" \
        -colors "$colors" -type Palette \
        "$dst"
    local bytes=$(stat -c%s "$dst")
    printf "  %-22s %8d bytes\n" "$(basename "$dst")" "$bytes"
}

echo
echo "[walls] -> 64x64 indexed"
for f in "$BASE"/wall/*.xpm; do
    [ -f "$f" ] || continue
    normalize "$f" "$OUT/wall/$(basename "$f")" "64x64" "center"
done

echo
echo "[enemies] -> 64x64 indexed (magenta chroma key)"
for f in "$BASE"/enemies/*.xpm; do
    [ -f "$f" ] || continue
    normalize "$f" "$OUT/enemies/$(basename "$f")" "64x64" "south"
done

echo
echo "[guns] -> 512x512 indexed 64 colors (magenta chroma key, kept bottom-center)"
for f in "$BASE"/guns/*.xpm; do
    [ -f "$f" ] || continue
    normalize "$f" "$OUT/guns/$(basename "$f")" "512x512" "south" "64"
done

echo
echo "✓ Done. Inspect $OUT before replacing originals."
echo "  To replace: cp -r $OUT/* $BASE/  (then rm -rf $OUT)"
