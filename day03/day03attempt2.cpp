#include "../util.hpp"

struct Point {
    int x, y;
    Point(): x(0), y(0) { }
    Point(int _x, int _y): x(_x), y(_y) { }
    Point operator-(const Point& rhs) const { return Point(x - rhs.x, y - rhs.y); }
    bool operator==(const Point& rhs) const { return (x == rhs.x) && (y == rhs.y); }
} typedef Vector;
// is a less than b
const Point PointZero = Point();
int ManhattanDistance(const Point a, const Point b) {
    return abs(b.x - a.x) + abs(b.y - a.y);
}
//bool LessThan(const Point& a, const Point& b) { return ; }

const char UP = 'U';
const char DOWN = 'D';
const char LEFT = 'L';
const char RIGHT = 'R';

std::vector<Point> getPointsFromMoves(const std::vector<std::string>& moves) {
    std::vector<Point> points;
    Point currentPos = Point(0, 0);
    for (size_t m = 0; m < moves.size(); m++)
    {
        std::string move = moves.at(m);
        char dir = move[0];
        int dist = std::stoi(move.substr(1));
        switch (dir) {
            case UP:
                for (size_t i = 0; i < dist; i++) {
                    currentPos.y++;
                    points.push_back(currentPos);
                }
                break;

            case DOWN:
                for (size_t i = 0; i < dist; i++) {
                    currentPos.y--;
                    points.push_back(currentPos);
                }
                break;

            case LEFT:
                for (size_t i = 0; i < dist; i++) {
                    currentPos.x--;
                    points.push_back(currentPos);
                }
                break;

            case RIGHT:
                for (size_t i = 0; i < dist; i++) {
                    currentPos.x++;
                    points.push_back(currentPos);
                }
                break;
        }
    }

    return points;
}

int main(int argc, char ** args) {
    // read data
    std::ifstream file("input.txt");
    const std::vector<std::string> wire1Moves = readCSVLine(file);
    const std::vector<std::string> wire2Moves = readCSVLine(file);
    file.close();

    // build a map of the points that are on wire 1's path
    auto wire1Points = getPointsFromMoves(wire1Moves);
    auto wire2Points = getPointsFromMoves(wire2Moves);

    // check whether wires cross any of the same points
    int shortestDistance = INT32_MAX;
    for (Point wire1Point : wire1Points) {
        for (Point wire2Point : wire2Points) {
            if (wire1Point == wire2Point) {
                int dist = ManhattanDistance(PointZero, wire2Point);
                if (dist < shortestDistance && dist != 0) shortestDistance = dist;
            }
        }
    }

    std::cout << "Closest intersection: " << std::to_string(shortestDistance) << std::endl;
    return 0;
}
