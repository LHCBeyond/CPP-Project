import SwiftUI
import TicTacToeCore

@main
struct TicTacToeApp: App
{
    var body: some Scene
    {
        WindowGroup
        {
            ContentView()
                .frame( minWidth: 420, minHeight: 560 )
        }
        .windowResizability( .contentSize )
    }
}

final class TicTacToeViewModel: ObservableObject
{
    enum Mode: Int32, CaseIterable, Identifiable
    {
        case random = 1
        case minimax = 2
        case minimaxVsMinimax = 3

        var id: Int32
        {
            rawValue
        }

        var title: String
        {
            switch self
            {
            case .random:
                return "Random"
            case .minimax:
                return "Minimax"
            case .minimaxVsMinimax:
                return "AI vs AI"
            }
        }
    }

    @Published var board: [ String ] = Array( repeating: "", count: 9 )
    @Published var statusText = "Your turn"
    @Published var selectedMode: Mode = .minimax
    @Published var isAutoPlaying = false

    private var game: OpaquePointer?

    init()
    {
        game = ticTacToeCreateGame()
        resetGame()
    }

    deinit
    {
        ticTacToeDestroyGame( game )
    }

    var isMinimaxVsMinimax: Bool
    {
        selectedMode == .minimaxVsMinimax
    }

    var canStep: Bool
    {
        isMinimaxVsMinimax && statusText == "AI thinking"
    }

    func resetGame()
    {
        ticTacToeResetGame( game, selectedMode.rawValue )
        isAutoPlaying = false
        refreshFromCore()
    }

    func selectMode( _ mode: Mode )
    {
        selectedMode = mode
        resetGame()
    }

    func playerMove( at index: Int )
    {
        if isMinimaxVsMinimax
        {
            return
        }

        ticTacToePlayerMove( game, Int32( index ) )
        refreshFromCore()
    }

    func stepMinimaxVsMinimax()
    {
        if !isMinimaxVsMinimax
        {
            return
        }

        ticTacToeStepMinimaxVsMinimax( game )
        refreshFromCore()
    }

    func toggleAutoPlay()
    {
        if !isMinimaxVsMinimax
        {
            return
        }

        isAutoPlaying.toggle()
    }

    func stopAutoPlayIfFinished()
    {
        if statusText != "AI thinking"
        {
            isAutoPlaying = false
        }
    }

    private func refreshFromCore()
    {
        var updatedBoard: [ String ] = []

        for index in 0 ..< 9
        {
            let value = ticTacToeCellAt( game, Int32( index ) )

            if value == 88
            {
                updatedBoard.append( "X" )
            }
            else if value == 79
            {
                updatedBoard.append( "O" )
            }
            else
            {
                updatedBoard.append( "" )
            }
        }

        board = updatedBoard
        statusText = statusDescription()
    }

    private func statusDescription() -> String
    {
        let status = ticTacToeStatus( game )

        switch status
        {
        case 1:
            return "You win"
        case 2:
            return "Computer wins"
        case 3:
            return "Tie"
        case 4:
            return "Minimax X wins"
        case 5:
            return "Minimax O wins"
        default:
            if isMinimaxVsMinimax
            {
                return "AI thinking"
            }

            return "Your turn"
        }
    }
}

struct ContentView: View
{
    @StateObject private var viewModel = TicTacToeViewModel()

    private let columns =
    [
        GridItem( .fixed( 104 ), spacing: 10 ),
        GridItem( .fixed( 104 ), spacing: 10 ),
        GridItem( .fixed( 104 ), spacing: 10 )
    ]

    var body: some View
    {
        VStack( spacing: 22 )
        {
            header
            modePicker
            board
            controls
        }
        .padding( 28 )
        .background( Color( nsColor: .windowBackgroundColor ) )
        .onReceive(
            Timer.publish( every: 0.45, on: .main, in: .common ).autoconnect()
        )
        { _ in
            if viewModel.isAutoPlaying
            {
                viewModel.stepMinimaxVsMinimax()
                viewModel.stopAutoPlayIfFinished()
            }
        }
    }

    private var header: some View
    {
        VStack( spacing: 6 )
        {
            Text( "Tic Tac Toe" )
                .font( .system( size: 34, weight: .bold, design: .rounded ) )

            Text( viewModel.statusText )
                .font( .system( size: 17, weight: .semibold ) )
                .foregroundStyle( statusColor )
                .frame( height: 24 )
        }
    }

    private var modePicker: some View
    {
        Picker( "Mode", selection: Binding(
            get:
            {
                viewModel.selectedMode
            },
            set:
            { mode in
                viewModel.selectMode( mode )
            }
        ) )
        {
            ForEach( TicTacToeViewModel.Mode.allCases )
            { mode in
                Text( mode.title )
                    .tag( mode )
            }
        }
        .pickerStyle( .segmented )
        .frame( width: 330 )
    }

    private var board: some View
    {
        LazyVGrid( columns: columns, spacing: 10 )
        {
            ForEach( 0 ..< 9, id: \.self )
            { index in
                Button
                {
                    viewModel.playerMove( at: index )
                }
                label:
                {
                    Text( viewModel.board[ index ] )
                        .font( .system( size: 58, weight: .bold, design: .rounded ) )
                        .foregroundStyle( markerColor( viewModel.board[ index ] ) )
                        .frame( width: 104, height: 104 )
                        .contentShape( Rectangle() )
                }
                .buttonStyle( BoardCellButtonStyle( isFilled: !viewModel.board[ index ].isEmpty ) )
                .disabled( viewModel.isMinimaxVsMinimax || !viewModel.board[ index ].isEmpty )
            }
        }
        .frame( width: 332, height: 332 )
    }

    private var controls: some View
    {
        HStack( spacing: 12 )
        {
            Button( "New Game" )
            {
                viewModel.resetGame()
            }
            .keyboardShortcut( "n", modifiers: .command )

            if viewModel.isMinimaxVsMinimax
            {
                Button( "Step" )
                {
                    viewModel.stepMinimaxVsMinimax()
                }
                .disabled( !viewModel.canStep )

                Button( viewModel.isAutoPlaying ? "Pause" : "Auto" )
                {
                    viewModel.toggleAutoPlay()
                }
                .disabled( !viewModel.canStep )
            }
        }
        .controlSize( .large )
    }

    private var statusColor: Color
    {
        switch viewModel.statusText
        {
        case "You win", "Minimax X wins":
            return .green
        case "Computer wins", "Minimax O wins":
            return .red
        case "Tie":
            return .orange
        default:
            return .secondary
        }
    }

    private func markerColor( _ marker: String ) -> Color
    {
        if marker == "X"
        {
            return .blue
        }

        if marker == "O"
        {
            return .pink
        }

        return .primary
    }
}

struct BoardCellButtonStyle: ButtonStyle
{
    let isFilled: Bool

    func makeBody( configuration: Configuration ) -> some View
    {
        configuration.label
            .background(
                RoundedRectangle( cornerRadius: 8 )
                    .fill( Color( nsColor: .controlBackgroundColor ) )
            )
            .overlay(
                RoundedRectangle( cornerRadius: 8 )
                    .stroke(
                        isFilled ? Color.secondary.opacity( 0.35 ) : Color.accentColor.opacity( 0.45 ),
                        lineWidth: configuration.isPressed ? 3 : 2
                    )
            )
            .scaleEffect( configuration.isPressed ? 0.97 : 1 )
    }
}
