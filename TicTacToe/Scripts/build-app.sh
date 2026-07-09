#!/bin/sh

set -eu

SCRIPT_DIR=$( cd "$( dirname "$0" )" && pwd )
PROJECT_DIR=$( cd "$SCRIPT_DIR/.." && pwd )
APP_DIR="$PROJECT_DIR/build/TicTacToe.app"
CONTENTS_DIR="$APP_DIR/Contents"
MACOS_DIR="$CONTENTS_DIR/MacOS"
EXECUTABLE_PATH="$PROJECT_DIR/.build/release/TicTacToe"

cd "$PROJECT_DIR"
swift build -c release --product TicTacToe

rm -rf "$APP_DIR"
mkdir -p "$MACOS_DIR"
cp "$EXECUTABLE_PATH" "$MACOS_DIR/TicTacToe"

cat > "$CONTENTS_DIR/Info.plist" <<'PLIST'
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "https://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>CFBundleExecutable</key>
    <string>TicTacToe</string>
    <key>CFBundleIdentifier</key>
    <string>local.tictactoe.swiftui</string>
    <key>CFBundleName</key>
    <string>TicTacToe</string>
    <key>CFBundleDisplayName</key>
    <string>TicTacToe</string>
    <key>CFBundlePackageType</key>
    <string>APPL</string>
    <key>CFBundleShortVersionString</key>
    <string>1.0</string>
    <key>CFBundleVersion</key>
    <string>1</string>
    <key>LSMinimumSystemVersion</key>
    <string>13.0</string>
    <key>NSHighResolutionCapable</key>
    <true/>
</dict>
</plist>
PLIST

echo "Built $APP_DIR"
