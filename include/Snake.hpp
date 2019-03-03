#pragma once
#include <vector>
#include <random>
#include "Board.hpp"
#include "Goal.hpp"
class Snake
{
private:
    class Segment
    {
    public:
        Segment(const Location& loc, sf::Color c);
        void Draw(Board& brd);
        void MoveBy(const Location& delta);
        void Follow(const Segment& seg);
        Location GetLoc() const;
    private:
        Location loc;
        sf::Color c;
    };
public:
    Snake(Board& brd, const Location& loc);
    void Draw();
    void MoveBy(const Location& delta);
    void Grow();
    Location GetNextHeadLocation(const Location& delta) const;
    Location GetLoc() const;
    bool IsOutsideBoard() const;
    bool IsInTile() const;
    bool IsOverlappingWith(const Location& loc) const;
    bool CheckAndEatGoal(std::mt19937& rng, Goal& goal);
private:
    std::vector<Segment> segments;
    sf::Color colHead = sf::Color::Yellow;
    sf::Color colBody = sf::Color::Green;
    Board& brd;
private:
    void SpawnGoal(std::mt19937&rng, Goal& goal) const;
};