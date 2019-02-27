#include <iostream>
#include "ui.hpp"

void UI::display_field(int** field, int field_size)
{
    for(int row = 0; row < field_size; row++)
    {
        for(int column = 0; column < field_size; column++)
        {
            std::cout << field[row][column];
        }
        
        std::cout << std::endl;
    }
    
}