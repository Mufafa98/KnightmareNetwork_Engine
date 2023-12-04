#include "Board.hpp"

void Board::MovePiece(const Vector2f &start_pos, const Vector2f &end_pos)
{
    const unsigned short start_x = start_pos.x;
    const unsigned short start_y = start_pos.y;
    const unsigned short end_x = end_pos.x;
    const unsigned short end_y = end_pos.y; 
    if(board[end_y][end_x])
    {
        if((board[end_y][end_x] & 7) != Piece::EnPassantTrace)
            sound[1].play();//capture
        else if((board[start_y][start_x] & 7) == 6)
            sound[1].play();//capture
        else 
            sound[0].play();//move
    }
    else
        sound[0].play();//move

    board[end_y][end_x] = board[start_y][start_x];
    board[start_y][start_x] = 0;

    UpdateBoard();
}

void Board::SelectSquare(const Vector2f &pos)
{
    selected_square.setFillColor(SELECTED_SQ_COLOR);
    selected_square.setPosition(Vector2f(pos.x * SQUARE_SIZE, pos.y * SQUARE_SIZE));
}

void Board::DeSelectSquare()
{
    selected_square.setFillColor(Color::Transparent);
}

void Board::HighlightSquare(const unsigned short x, const unsigned short y)
{
    highlighted_square[y][x].setFillColor(LEGAL_MOVE);
}

void Board::DeHighlightSquare()
{
    for(unsigned short i = 0; i < 8; i++)
        for(unsigned short j =  0; j < 8; j++)
            highlighted_square[i][j].setFillColor(Color::Transparent);
}

void Board::SetEnPassantTrace(const Vector2f &pos, const unsigned short side)
{
    board[(unsigned short)pos.y][(unsigned short)pos.x] = Piece::EnPassantTrace + side;
}

void Board::RemoveEnPassantTrace(unsigned short side)
{
    for(unsigned short i = 0; i < 8; i++)
        for(unsigned short j = 0; j < 8; j++)
            if(board[i][j] == Piece::EnPassantTrace + side)
                board[i][j] = 0;

}

void Board::UpdateBoard()
{
    for(unsigned short i = 0;i < 8; i ++)
        for(unsigned short j = 0; j < 8 ; j++)
            if(board[i][j] != 0 && board[i][j] != Piece::EnPassantTrace + Piece::White && board[i][j] != Piece::EnPassantTrace + Piece::Black)
            {
                pieces[i][j].setTexture(&pieces_texture.at(board[i][j]));
                pieces[i][j].setPosition(Vector2f(j * SQUARE_SIZE, i * SQUARE_SIZE));
                pieces[i][j].setSize(Vector2f(SQUARE_SIZE, SQUARE_SIZE));
            }
            else
                pieces[i][j] = RectangleShape();
    selected_square.setFillColor(Color::Transparent);
}

Board::Board(const String FEN_board)
{
    for(unsigned short side : {Piece::White, Piece::Black})
    {
        string first;
        if(side == Piece::White)
            first = "w";
        else
            first = "b";
        for(unsigned short type : {Piece::King, Piece::Queen, Piece::Bishop, Piece::Knight, Piece::Rook, Piece::Pawn})
        {
            string second;
            switch (type)
            {
                case Piece::King:
                    second = "K.png";
                    break;
                case Piece::Queen:
                    second = "Q.png";
                    break;
                case Piece::Bishop:
                    second = "B.png";
                    break;
                case Piece::Knight:
                    second = "N.png";
                    break;
                case Piece::Rook:
                    second = "R.png";
                    break;
                case Piece::Pawn:
                    second = "P.png";
                    break;
                default:
                    break;
            }
            pieces_texture[side + type] = Texture();
            pieces_texture[side + type].loadFromFile(string("assets/pieces/" + first + second));
            pieces_texture[side + type].setSmooth(true);
        }
    }

    pieces_texture.insert(pair(Piece::Black + Piece::Pawn, Texture()));
    unsigned short x_pos = 0;
    unsigned short y_pos = 0;
    for(unsigned short i = 0; i < 8; i++)
        for(unsigned short j = 0; j < 8; j++)
            board[i][j] = 0;
    for(size_t i = 0; i < FEN_board.getSize(); i++)
    {
        switch (FEN_board[i])
        {
            case 'K':
            {
                board[y_pos][x_pos] = Piece::White + Piece::King;
                x_pos++;
                break;
            }
            case 'Q':
            {
                board[y_pos][x_pos] = Piece::White + Piece::Queen;
                x_pos++;
                break;
            }
            case 'B':
            {
                board[y_pos][x_pos] = Piece::White + Piece::Bishop;
                x_pos++;
                break;
            }
            case 'N':
            {
                board[y_pos][x_pos] = Piece::White + Piece::Knight;
                x_pos++;
                break;
            }
            case 'R':
            {
                board[y_pos][x_pos] = Piece::White + Piece::Rook;
                x_pos++;
                break;
            }
            case 'P':
            {
                board[y_pos][x_pos] = Piece::White + Piece::Pawn;
                x_pos++;
                break;
            }
            case 'k':
            {
                board[y_pos][x_pos] = Piece::Black + Piece::King;
                x_pos++;
                break;
            }
            case 'q':
            {
                board[y_pos][x_pos] = Piece::Black + Piece::Queen;
                x_pos++;
                break;
            }
            case 'b':
            {
                board[y_pos][x_pos] = Piece::Black + Piece::Bishop;
                x_pos++;
                break;
            }
            case 'n':
            {
                board[y_pos][x_pos] = Piece::Black + Piece::Knight;
                x_pos++;
                break;
            }
            case 'r':
            {
                board[y_pos][x_pos] = Piece::Black + Piece::Rook;
                x_pos++;
                break;
            }
            case 'p':
            {
                board[y_pos][x_pos] = Piece::Black + Piece::Pawn;
                x_pos++;
                break;
            }
            default:
            {
                if(FEN_board[i] >= '0' && FEN_board[i] <= '9')
                    x_pos += FEN_board[i] - '0';
                break;
            }
        }
        if(x_pos >= 8)
        {
            x_pos = 0;
            y_pos++;
        }
    }
    for(unsigned short i = 0;i < 8; i ++)
    {
        for(unsigned short j = 0; j < 8 ; j++)
        {
            if(board[i][j] != 0 && board[i][j] != Piece::EnPassantTrace + Piece::White && board[i][j] != Piece::EnPassantTrace + Piece::Black)
            {
                pieces[i][j].setTexture(&pieces_texture.at(board[i][j]));
                pieces[i][j].setPosition(Vector2f(j * SQUARE_SIZE, i * SQUARE_SIZE));
                pieces[i][j].setSize(Vector2f(SQUARE_SIZE, SQUARE_SIZE));
            }
            highlighted_square[i][j].setPosition(Vector2f(j * SQUARE_SIZE, i * SQUARE_SIZE));
            highlighted_square[i][j].setSize(Vector2f(SQUARE_SIZE, SQUARE_SIZE));
            highlighted_square[i][j].setFillColor(Color::Transparent);
        }
    }
    if(!board_background_texture.loadFromFile("assets/Board.png"))
    {
        perror("LoadFromFile");
        exit(errno);
    }
    if(!buffer[0].loadFromFile("assets/sounds/Move.mp3"))
    {
        perror("LoadFromFile");
        exit(errno);
    }
    sound[0].setBuffer(buffer[0]);
    if(!buffer[1].loadFromFile("assets/sounds/Capture.mp3"))
    {
        perror("LoadFromFile");
        exit(errno);
    }
    sound[1].setBuffer(buffer[1]);
    board_background.setTexture(&board_background_texture);
    board_background.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    selected_square.setSize(Vector2f(SQUARE_SIZE, SQUARE_SIZE));
    selected_square.setFillColor(Color::Transparent);
}

void Board::Draw(RenderWindow &window) 
{
    window.draw(board_background);
    window.draw(selected_square);
    for(unsigned short i = 0; i < 8; i++)
        for(unsigned short j =  0; j < 8; j++)
        {
            window.draw(highlighted_square[i][j]);
            window.draw(pieces[i][j]);
        }
            
}
