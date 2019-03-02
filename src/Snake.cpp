#include "Snake.hpp"

Snake::Snake(Board& brd, const Location& loc)
    :
    brd(brd)
{
    segments.emplace_back(Segment{loc, colHead});
    Grow();
    Grow();
}

void Snake::Draw()
{
    for (auto& seg : segments)
    {
        seg.Draw(brd);
    }
}

void Snake::MoveBy(const Location& delta)
{
    for (int i=segments.size()-1; i > 0; i--)
    {
        segments[i].Follow(segments[i-1]);
    }
    segments[0].MoveBy(delta);
}

void Snake::Grow()
{
    segments.emplace_back(Segment{segments[segments.size()-1].GetLoc(), colBody});
}

Location Snake::GetNextHeadLocation(const Location& delta) const
{
    Location l = segments[0].GetLoc() + delta;
    return l;
}

bool Snake::IsOutsideBoard() const
{
    return
        segments[0].GetLoc().x < 0 ||
        segments[0].GetLoc().x >= brd.width ||
        segments[0].GetLoc().y < 0 ||
        segments[0].GetLoc().y >= brd.height;
}

bool Snake::IsInTile() const
{
    for (int i=segments.size()-1; i > 0; i--)
    {
        if (segments[0].GetLoc() == segments[i].GetLoc())
        {
            return true;
        }
    }
    return false;
}

bool Snake::IsOverlappingWith(const Location& loc) const
{
    for (auto& seg : segments)
    {
        if (seg.GetLoc() == loc)
        {
            return true;
        }
    }
    return false;
}
void Snake::CheckAndEatGoal(std::mt19937& rng, Goal& goal)
{
    if (segments[0].GetLoc() == goal.GetLoc())
    {
        //TODO increase score
        Grow();
        SpawnGoal(rng, goal);
    }
}

void Snake::SpawnGoal(std::mt19937& rng, Goal& goal) const
{
    std::uniform_int_distribution<int> xDist(0, brd.width);
    std::uniform_int_distribution<int> yDist(0, brd.height);

    Location loc = {xDist(rng), yDist(rng)};
    while(IsOverlappingWith(loc))
    {
        loc = {xDist(rng), yDist(rng)};
    }
    goal.Spawn(loc);
}
/* Segment */
Snake::Segment::Segment(const Location& loc, sf::Color c)
    :
    loc(loc),
    c(c)
{}

void Snake::Segment::Draw(Board& brd)
{
    brd.DrawCell(loc, c);
}

void Snake::Segment::MoveBy(const Location& delta)
{
    loc += delta;
}

void Snake::Segment::Follow(const Segment& seg)
{
    loc = seg.GetLoc();
}

Location Snake::Segment::GetLoc() const
{
    return loc;
}

