#include <iostream>
#include <string>
#include <limits>
#include <SFML/Graphics.hpp>
#include "Properties.hpp"
#include "Engine.hpp"
#include "Board.hpp"
#include "DigitalTree.hpp"


using namespace std;
using namespace sf;

int main()
{
    //const char _temp[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";"ppppPPPP/7Q/8/8/8/8/8/8" r3k2r/8/8/8/8/8/8/KB6 
    Board board = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    Engine engine(board);
    Vector2f start_pos, end_pos;
    unsigned int counter = 0;
    ContextSettings settings;
    settings.stencilBits = 100;
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, Style::Close | Style::Titlebar);
    while(window.isOpen())
    {
        Event window_event;
        while(window.pollEvent(window_event))
        {
            switch(window_event.type)
            {
                case Event::Closed:
                    window.close();
                case Event::MouseButtonPressed:
                {

                    Vector2f mouse_click_pos = window.mapPixelToCoords(Mouse::getPosition(window));
                    mouse_click_pos.x = int(mouse_click_pos.x / 100);
                    mouse_click_pos.y = int(mouse_click_pos.y / 100);
                    if(counter % 2)
                    {
                        end_pos = mouse_click_pos;
                        engine.MakeMove(start_pos, end_pos);
                        engine.DeSelectSquare();
                        engine.DeHighlightLegalMoves();
                    }
                    else
                    {
                        start_pos = mouse_click_pos;
                        engine.SelectSquare(start_pos);
                        engine.HighlightLegalMoves(start_pos);
                    }
                    counter++;
                }
                default:
                    break;
            }
        }
        if(engine.TurnSwapped())
            engine.CheckEndConditions();
        if(engine.PawnNeedsPromotion())
        {
            unsigned short id;
            cin>>id;
            engine.PromotePawn(id);
        }
        if(!engine.GameRunning())
        {
            window.close();
            cout<<"Game over: "<<engine.GetGameResult()<<'\n';
        }


        window.clear();
        board.Draw(window);
        window.display();
    }
    return 0;
}