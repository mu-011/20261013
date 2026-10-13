#include <iostream>
#include "Board.h"

int main()
{
	Board board;
	Stone current = BLACK;

	while (true)
	{
		board.printf();

        std::cout << (current == BLACK ? "•‚Ì”Ô‚Å‚·\n" : "”’‚Ì”Ô‚Å‚·\n");

        int x, y;
        std::cout << "x y ‚ð“ü—Í‚µ‚Ä‚­‚¾‚³‚¢F";
        std::cin >> x >> y;

        if (!board.placeStone(x, y, current)) 
        {
            std::cout << "‚»‚±‚É‚Í’u‚¯‚Ü‚¹‚ñI\n";
        }
        else 
        {
            //Žè”ÔŒð‘ã
            current = (current == BLACK ? WHITE : BLACK);
        }
    }

    return 0;
}