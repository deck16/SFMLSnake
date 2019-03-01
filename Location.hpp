#pragma once

class Location
{
public:
    Location(int _x, int _y)
        :
        x(_x), y(_y)
    {}
    Location operator+(const Location& rhs) const
    {
        return {x+rhs.x, y+rhs.y};
    }
    Location& operator+=(const Location& rhs)
    {
        return *this = *this+rhs;
    }
    bool operator==(const Location& rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
public:
    int x;
    int y;
};