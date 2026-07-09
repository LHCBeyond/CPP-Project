// swift-tools-version: 6.0

import PackageDescription

let package = Package(
    name: "TicTacToe",
    platforms: [
        .macOS( .v13 )
    ],
    products: [
        .executable(
            name: "TicTacToe",
            targets: [ "TicTacToeApp" ]
        ),
        .executable(
            name: "TicTacToeCoreCheck",
            targets: [ "TicTacToeCoreCheck" ]
        )
    ],
    targets: [
        .target(
            name: "TicTacToeCore",
            publicHeadersPath: "include",
            cxxSettings: [
                .unsafeFlags( [ "-std=c++17" ] )
            ]
        ),
        .executableTarget(
            name: "TicTacToeApp",
            dependencies: [ "TicTacToeCore" ]
        ),
        .executableTarget(
            name: "TicTacToeCoreCheck",
            dependencies: [ "TicTacToeCore" ],
            path: "Tests/TicTacToeCoreCheck",
            cxxSettings: [
                .unsafeFlags( [ "-std=c++17" ] )
            ]
        )
    ]
)
