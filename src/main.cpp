#include <iostream>
#include <limits>
#include <SFML/Graphics.hpp>
#include "Properties.hpp"
#include "Board.hpp"
#include "Engine.hpp"

using namespace std;
using namespace sf;

int main()
{
    Board board = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    //Engine engine = Engine(&board);

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

                default:
                    break;
            }
        }
        window.clear();
        board.Draw(window);
        window.display();
    }
    return 0;
}