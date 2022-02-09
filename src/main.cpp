#include "includes.hpp"

int main()
{
    ToyRobot toy_robot( 5, 5 );

    std::cout << "----------------" << std::endl;
    while ( true )
    {
        std::cout << "> ";
        std::string response;
        std::getline( std::cin, response );

        if ( utility::str_compare( "EXIT", response ) ) break;
        toy_robot.process_command( response );
    }

    return 0;
}