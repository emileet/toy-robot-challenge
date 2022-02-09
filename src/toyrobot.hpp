#pragma once

enum e_ToyFacing : int8_t
{
    INVALID = -1,
    NORTH,
    EAST,
    SOUTH,
    WEST
};

class ToyRobot
{
public:
    /**
     * Default Constructor for ToyRobot
     */
    ToyRobot()
    {
        // boundary for a 5x5 table
        m_x_bounds = m_y_bounds = { 0, 4 };

        // initial state of Toy Robot
        m_placed = false;
        m_pos.x = m_pos.y = 0;
        m_facing = e_ToyFacing::INVALID;
    }

    /**
     * Parameterised Constructor for ToyRobot
     *
     * @param x x-value for table size
     * @param y y-value for table size
     */
    ToyRobot( const int& x, const int& y )
    {
        // allows specification of table size
        m_x_bounds = { 0, x - 1 };
        m_y_bounds = { 0, y - 1 };

        // initial state of Toy Robot
        m_placed = false;
        m_pos.x = m_pos.y = 0;
        m_facing = e_ToyFacing::INVALID;
    }

    /**
     * Process user commands given to the Toy Robot
     *
     * @param cmd input string provided by the user
     * @return true if valid command, false if invalid command
     */
    const bool process_command( std::string_view cmd )
    {
        std::vector< std::string > split_cmd = utility::str_split( cmd, ' ' );
        if ( utility::str_compare( "PLACE", split_cmd[ 0 ] ) )
        {
            // check if the place command has the correct number of args
            if ( split_cmd.size() < 2 )
            {
                std::cout << "SYSTEM: invalid 'PLACE' command, " << split_cmd.size() - 1 << " args provided!" << std::endl;
                return false;
            }

            // split the 2nd item in split_cmd to retrieve state info delimited with a comma (,)
            split_cmd = utility::str_split( split_cmd[ 1 ], ',' );
            if ( split_cmd.size() < 3 )
            {
                std::cout << "SYSTEM: invalid 'PLACE' command, " << split_cmd.size() << " args provided!" << std::endl;
                return false;
            }

            // check if x-coord and y-coord are numbers
            if ( !utility::is_number( split_cmd[ 0 ] ) || !utility::is_number( split_cmd[ 1 ] ) )
            {
                std::cout << "SYSTEM: invalid 'PLACE' command, non-number provided to coords!" << std::endl;
                return false;
            }

            // check if a valid value is provided for the x-coord
            const int new_x = std::stoi( split_cmd[ 0 ] );
            if ( new_x < m_x_bounds.x || new_x > m_x_bounds.y )
            {
                std::cout << "SYSTEM: invalid 'PLACE' command, x-value outside of bounds!" << std::endl;
                return false;
            }

            // check if a valid value is provided for the y-coord
            const int new_y = std::stoi( split_cmd[ 1 ] );
            if ( new_y < m_y_bounds.x || new_y > m_y_bounds.y )
            {
                std::cout << "SYSTEM: invalid 'PLACE' command, y-value outside of bounds!" << std::endl;
                return false;
            }

            // check if a valid facing is provided
            const e_ToyFacing new_facing = str_to_facing( split_cmd[ 2 ] );
            if ( new_facing == e_ToyFacing::INVALID )
            {
                std::cout << "SYSTEM: invalid 'PLACE' command, invalid facing!" << std::endl;
                return false;
            }

            // set the new state of the Toy Robot
            m_pos.x = new_x;
            m_pos.y = new_y;
            m_facing = new_facing;

            return m_placed = true;
        }

        // if the toy hasn't been placed, we should ignore all other commands
        if ( !m_placed )
        {
            std::cout << "SYSTEM: Toy Robot has not been placed on the table!" << std::endl;
            return false;
        }
        else if ( utility::str_compare( "RIGHT", split_cmd[ 0 ] ) )
        {
            // increment the facing value, if it's over the maximum (WEST) flip the value back around (to NORTH)
            e_ToyFacing new_facing = static_cast< e_ToyFacing >( static_cast< int8_t >( m_facing ) + 1 );
            m_facing = new_facing > e_ToyFacing::WEST ? e_ToyFacing::NORTH : new_facing;
            return true;
        }
        else if ( utility::str_compare( "LEFT", split_cmd[ 0 ] ) )
        {
            // decrement the facing value, if it's under the minimum (NORTH) flip the value back around (to WEST)
            e_ToyFacing new_facing = static_cast< e_ToyFacing >( static_cast< int8_t >( m_facing ) - 1 );
            m_facing = new_facing < e_ToyFacing::NORTH ? e_ToyFacing::WEST : new_facing;
            return true;
        }
        else if ( utility::str_compare( "MOVE", split_cmd[ 0 ] ) )
        {
            switch ( m_facing )
            {
            case e_ToyFacing::NORTH:
                // prevent moves that will cause the robot to go outside the bounds
                if ( m_pos.y + 1 > m_y_bounds.y ) return false;
                ++m_pos.y;
                break;
            case e_ToyFacing::EAST:
                if ( m_pos.x + 1 > m_x_bounds.y ) return false;
                ++m_pos.x;
                break;
            case e_ToyFacing::SOUTH:
                if ( m_pos.y - 1 < m_y_bounds.x ) return false;
                --m_pos.y;
                break;
            case e_ToyFacing::WEST:
                if ( m_pos.x - 1 < m_x_bounds.x ) return false;
                --m_pos.x;
                break;
            }

            return true;
        }
        else if ( utility::str_compare( "REPORT", split_cmd[ 0 ] ) )
        {
            std::cout << get_state() << std::endl;
            return true;
        }

        std::cout << "SYSTEM: unrecognised command provided!" << std::endl;
        return false;
    }

    /**
     * Retrieve the current state of the Toy Robot
     *
     * @return the current state (current position and facing) of the Toy Robot
     */
    const std::string get_state() const
    {
        std::stringstream ss;
        if ( !m_placed ) ss << "SYSTEM: Toy Robot has not been placed on the table!";
        else
        {
            ss << "OUTPUT: " << m_pos.x << "," << m_pos.y << "," << get_facing_str();
        }

        return ss.str();
    }

private:
    /**
     * Convert a string facing value to an int8_t/char
     *
     * @param str value to be converted
     * @return an int8_t/char facing value
     */
    const e_ToyFacing str_to_facing( std::string_view str ) const
    {
        if ( utility::str_compare( "NORTH", str ) ) return e_ToyFacing::NORTH;
        if ( utility::str_compare( "EAST", str ) ) return e_ToyFacing::EAST;
        if ( utility::str_compare( "SOUTH", str ) ) return e_ToyFacing::SOUTH;
        if ( utility::str_compare( "WEST", str ) ) return e_ToyFacing::WEST;

        return e_ToyFacing::INVALID;
    }

    /**
     * Retrieve current facing as a string value
     *
     * @return the current facing as a string
     */
    const std::string get_facing_str() const
    {
        switch ( m_facing )
        {
        case e_ToyFacing::NORTH:
            return "NORTH";
        case e_ToyFacing::EAST:
            return "EAST";
        case e_ToyFacing::SOUTH:
            return "SOUTH";
        case e_ToyFacing::WEST:
            return "WEST";
        }

        return "UNKNOWN";
    }

private:
    // minimum and maximum bounds for the table
    vec2_t m_x_bounds, m_y_bounds;
    // whether the toy robot has been placed
    bool m_placed;
    // the toy robot's current position
    vec2_t m_pos;
    // the toy robot's current facing
    e_ToyFacing m_facing;
};