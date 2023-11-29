#include "Board.hpp"

void Board::MakeMove(unsigned short col_start, unsigned short row_start, unsigned short col_end, unsigned short row_end)
{
    swap(board[row_start][col_start], board[row_end][col_end]);
    swap(pieces[row_start][col_start], pieces[row_end][col_end]);
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
    for(int i = 0; i < 8; i++)
        for(int j =  0; j < 8; j++)
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
    for(int i = 0;i < 8; i ++)
    {
        for(int j = 0; j < 8 ; j++)
        {
            // cout<<bitset<5>(board[i][j])<<' ';
            if(board[i][j] != 0)
            {
                pieces[i][j].setTexture(&pieces_texture.at(board[i][j]));
                pieces[i][j].setPosition(Vector2f(j * SQUARE_SIZE, i * SQUARE_SIZE));
                pieces[i][j].setSize(Vector2f(SQUARE_SIZE, SQUARE_SIZE));
            }
        }
               
        // cout<<'\n';
    }
    if(!board_background_texture.loadFromFile("assets/Board.png"))
    {
        perror("LoadFromFile");
        exit(errno);
    }
    board_background.setTexture(&board_background_texture);
    board_background.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
}

void Board::Draw(RenderWindow &window) 
{
    window.draw(board_background);
    for(int i = 0; i < 8; i++)
        for(int j =  0; j < 8; j++)
            window.draw(pieces[i][j]);
}
