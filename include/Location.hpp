#pragma once

class Location
{
public:
    Location() = default;
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
    bool operator!=(const Location& rhs) const
    {
        return (*this == rhs) == false;
    }
public:
    int x;
    int y;
};