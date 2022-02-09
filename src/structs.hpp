#pragma once

struct vec2_t
{
    int x, y;

    vec2_t()
    {
        x = y = 0;
    }

    vec2_t( const int& in_x, const int& in_y )
    {
        x = in_x;
        y = in_y;
    }
};