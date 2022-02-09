#include "../src/includes.hpp"
#include <gtest/gtest.h>

TEST( ExpectedOutput, ZeroOneNorth )
{
    // move to (0,1,NORTH)
    ToyRobot toy_robot( 5, 5 );
    toy_robot.process_command( "PLACE 0,0,NORTH" );
    toy_robot.process_command( "MOVE" );
    EXPECT_EQ( toy_robot.get_state(), "OUTPUT: 0,1,NORTH" );
}

TEST( ExpectedOutput, ZeroZeroWest )
{
    // face towards (0,0,NORTH)
    ToyRobot toy_robot( 5, 5 );
    toy_robot.process_command( "PLACE 0,0,NORTH" );
    toy_robot.process_command( "LEFT" );
    EXPECT_EQ( toy_robot.get_state(), "OUTPUT: 0,0,WEST" );
}

TEST( ExpectedOutput, ThreeThreeNorth )
{
    // move to (3,3,NORTH)
    ToyRobot toy_robot( 5, 5 );
    toy_robot.process_command( "PLACE 1,2,EAST" );
    toy_robot.process_command( "MOVE" );
    toy_robot.process_command( "MOVE" );
    toy_robot.process_command( "LEFT" );
    toy_robot.process_command( "MOVE" );
    EXPECT_EQ( toy_robot.get_state(), "OUTPUT: 3,3,NORTH" );
}

TEST( ExpectedOutput, FullRotationRight )
{
    // perform a full clockwise rotation
    ToyRobot toy_robot( 5, 5 );
    toy_robot.process_command( "PLACE 0,0,NORTH" );
    EXPECT_EQ( toy_robot.get_state(), "OUTPUT: 0,0,NORTH" );
    toy_robot.process_command( "RIGHT" );
    EXPECT_EQ( toy_robot.get_state(), "OUTPUT: 0,0,EAST" );
    toy_robot.process_command( "RIGHT" );
    EXPECT_EQ( toy_robot.get_state(), "OUTPUT: 0,0,SOUTH" );
    toy_robot.process_command( "RIGHT" );
    EXPECT_EQ( toy_robot.get_state(), "OUTPUT: 0,0,WEST" );
    toy_robot.process_command( "RIGHT" );
    EXPECT_EQ( toy_robot.get_state(), "OUTPUT: 0,0,NORTH" );
}

TEST( ExpectedOutput, FullRotationLeft )
{
    // perform a full counter-clockwise rotation
    ToyRobot toy_robot( 5, 5 );
    toy_robot.process_command( "PLACE 0,0,NORTH" );
    EXPECT_EQ( toy_robot.get_state(), "OUTPUT: 0,0,NORTH" );
    toy_robot.process_command( "LEFT" );
    EXPECT_EQ( toy_robot.get_state(), "OUTPUT: 0,0,WEST" );
    toy_robot.process_command( "LEFT" );
    EXPECT_EQ( toy_robot.get_state(), "OUTPUT: 0,0,SOUTH" );
    toy_robot.process_command( "LEFT" );
    EXPECT_EQ( toy_robot.get_state(), "OUTPUT: 0,0,EAST" );
    toy_robot.process_command( "LEFT" );
    EXPECT_EQ( toy_robot.get_state(), "OUTPUT: 0,0,NORTH" );
}

TEST( ExpectedOutput, FullTraversal )
{
    ToyRobot toy_robot( 5, 5 );
    EXPECT_EQ( toy_robot.process_command( "PLACE 0,0,NORTH" ), true );

    // (0,0,NORTH) to (0,4,NORTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true );  // (0,1,NORTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true );  // (0,2,NORTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true );  // (0,3,NORTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true );  // (0,4,NORTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), false ); // (0,5,NORTH) IGNORED
    EXPECT_EQ( toy_robot.get_state(), "OUTPUT: 0,4,NORTH" );

    // (0,4,NORTH) to (1,4,SOUTH)
    EXPECT_EQ( toy_robot.process_command( "RIGHT" ), true ); // (0,4,EAST)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true );  // (1,4,EAST)
    EXPECT_EQ( toy_robot.process_command( "RIGHT" ), true ); // (1,4,SOUTH)
    EXPECT_EQ( toy_robot.get_state(), "OUTPUT: 1,4,SOUTH" );

    // (1,4,SOUTH) to (1,0,SOUTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true );  // (1,3,SOUTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true );  // (1,2,SOUTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true );  // (1,1,SOUTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true );  // (1,0,SOUTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), false ); // (1,-1,SOUTH) IGNORED
    EXPECT_EQ( toy_robot.get_state(), "OUTPUT: 1,0,SOUTH" );

    // (1,0,SOUTH) to (2,0,NORTH)
    EXPECT_EQ( toy_robot.process_command( "LEFT" ), true ); // (1,0,EAST)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true ); // (2,0,EAST)
    EXPECT_EQ( toy_robot.process_command( "LEFT" ), true ); // (2,0,NORTH)
    EXPECT_EQ( toy_robot.get_state(), "OUTPUT: 2,0,NORTH" );

    // (2,0,NORTH) to (2,4,NORTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true );  // (2,1,NORTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true );  // (2,2,NORTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true );  // (2,3,NORTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true );  // (2,4,NORTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), false ); // (2,5,NORTH) IGNORED
    EXPECT_EQ( toy_robot.get_state(), "OUTPUT: 2,4,NORTH" );

    // (2,4,NORTH) to (3,4,SOUTH)
    EXPECT_EQ( toy_robot.process_command( "RIGHT" ), true ); // (2,4,EAST)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true );  // (3,4,EAST)
    EXPECT_EQ( toy_robot.process_command( "RIGHT" ), true ); // (3,4,SOUTH)
    EXPECT_EQ( toy_robot.get_state(), "OUTPUT: 3,4,SOUTH" );

    // (3,4,SOUTH) to (3,0,SOUTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true );  // (3,3,SOUTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true );  // (3,2,SOUTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true );  // (3,1,SOUTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true );  // (3,0,SOUTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), false ); // (3,-1,SOUTH) IGNORED
    EXPECT_EQ( toy_robot.get_state(), "OUTPUT: 3,0,SOUTH" );

    // (3,0,SOUTH) to (4,0,NORTH)
    EXPECT_EQ( toy_robot.process_command( "LEFT" ), true ); // (3,0,EAST)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true ); // (4,0,EAST)
    EXPECT_EQ( toy_robot.process_command( "LEFT" ), true ); // (4,0,NORTH)
    EXPECT_EQ( toy_robot.get_state(), "OUTPUT: 4,0,NORTH" );

    // (4,0,NORTH) to (4,4,NORTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true );  // (4,1,NORTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true );  // (4,2,NORTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true );  // (4,3,NORTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), true );  // (4,4,NORTH)
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), false ); // (4,5,NORTH) IGNORED
    EXPECT_EQ( toy_robot.get_state(), "OUTPUT: 4,4,NORTH" );
}

TEST( IgnoredCommand, IgnoredMove )
{
    ToyRobot toy_robot( 5, 5 );

    // attempt to move to (0,-1,SOUTH)
    EXPECT_EQ( toy_robot.process_command( "PLACE 0,0,SOUTH" ), true );
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), false );

    // attempt to move to (-1,0,WEST)
    EXPECT_EQ( toy_robot.process_command( "PLACE 0,0,WEST" ), true );
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), false );

    // attempt to move to (4,5,NORTH)
    EXPECT_EQ( toy_robot.process_command( "PLACE 4,4,NORTH" ), true );
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), false );

    // attempt to move to (5,4,EAST)
    EXPECT_EQ( toy_robot.process_command( "PLACE 4,4,EAST" ), true );
    EXPECT_EQ( toy_robot.process_command( "MOVE" ), false );
}

TEST( IgnoredCommand, IgnoredPlace )
{
    ToyRobot toy_robot( 5, 5 );
    // attempt to place at (0,5,EAST)
    EXPECT_EQ( toy_robot.process_command( "PLACE 0,5,EAST" ), false );
    // attempt to place at (5,0,EAST)
    EXPECT_EQ( toy_robot.process_command( "PLACE 5,0,EAST" ), false );
    // attempt to place at (5,5,EAST)
    EXPECT_EQ( toy_robot.process_command( "PLACE 5,5,EAST" ), false );
    // attempt to place at (123,0,EAST)
    EXPECT_EQ( toy_robot.process_command( "PLACE 123,0,EAST" ), false );
    // attempt to place at (0,-123,EAST)
    EXPECT_EQ( toy_robot.process_command( "PLACE 0,-123,EAST" ), false );
    // attempt to place at (123,-123,EAST)
    EXPECT_EQ( toy_robot.process_command( "PLACE 123,-123,EAST" ), false );
}

int main( int argc, char** argv )
{
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}