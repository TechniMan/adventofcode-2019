#include "../util.hpp"

const char UP ='U';
const char DOWN = 'D';
const char LEFT = 'L';
const char RIGHT = 'R';

struct Point {
    int x;
    int y;
    Point(): x(0), y(0) { }
    Point(int _x, int _y): x(_x), y(_y) { }
    Point operator-(const Point& rhs) const { return Point(x - rhs.x, y - rhs.y); }
} typedef Vector;
const Point PointZero = Point();
int ManhattanDistance(const Point a, const Point b) {
    return abs((b.x - a.x) + (b.y - a.y));
}
struct Line {
    Point start;
    Point end;
    Line(Point s, Point e): start(s), end(e) { }
    bool Intersects(Line l, Point* outPoint) const {
        const Vector s1 = end - start;
        const Vector s2 = l.end - l.start;
        const float det = (-s2.x * s1.y + s1.x * s2.y);
        const float s = (-s1.y * (start.x - l.start.x) + s1.x * (start.y - l.start.y)) / det;
        const float t = ( s2.x * (start.y - l.start.y) - s2.y * (start.x - l.start.x)) / det;
        if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
            if (outPoint != nullptr) {
                outPoint->x = start.x + (t * s1.x);
                outPoint->y = start.y + (t * s1.y);
            }
            return true;
        }
        return false;
    }
};

int main(int argc, char ** args) {
    // read data
    std::ifstream file("example1input.txt");
    const std::vector<std::string> wire1Route = readCSVLine(file);
    const std::vector<std::string> wire2Route = readCSVLine(file);
    file.close();

    // interpret wire 1's route as lines
    std::vector<Line> wire1Lines;
    Point currentPos = Point(0, 0);
    for (size_t m = 0; m < wire1Route.size(); m++)
    {
        std::string move = wire1Route.at(m);
        char dir = move[0];
        int dist = std::stoi(move.substr(1));
        Point nextPos = currentPos;
        switch (dir) {
            case UP:
                nextPos.y += dist;
                break;
            case DOWN:
                nextPos.y -= dist;
                break;
            case LEFT:
                nextPos.x -= dist;
                break;
            case RIGHT:
                nextPos.x += dist;
                break;
            default:
                std::cout << "Erroneous direction: " << dir << std::endl;
                return -1;
        }
        wire1Lines.push_back(Line(currentPos, nextPos));
        currentPos = nextPos;
    }

    // check each of wire 2's lines against all of wire 1's lines for intersections
    currentPos = Point();
    int bestDistance = INT32_MAX;
    for (size_t l2 = 0; l2 < wire2Route.size(); l2++)
    {
        std::string move = wire2Route.at(l2);
        char dir = move[0];
        int dist = std::stoi(move.substr(1));
        Point nextPos = currentPos;
        switch (dir) {
            case UP:
                nextPos.y += dist;
                break;
            case DOWN:
                nextPos.y -= dist;
                break;
            case LEFT:
                nextPos.x -= dist;
                break;
            case RIGHT:
                nextPos.x += dist;
                break;
            default:
                std::cout << "Erroneous direction: " << dir << std::endl;
                return -1;
        }
        Line line = Line(currentPos, nextPos);

        for (size_t l1 = 0; l1 < wire1Lines.size(); l1++)
        {
            Line line1 = wire1Lines.at(l1);

            // check for intersection
            Point* intersection = new Point();
            if (line.Intersects(line1, intersection)) {
                // check distance from start to the intersection against previous best distance
                int distance = ManhattanDistance(PointZero, *intersection);
                // if closer, replace best distance
                if (distance > 0 && distance < bestDistance) {
                    bestDistance = distance;
                }
            }
        }

        currentPos = nextPos;
    }

    std::cout << "Closest intersection: " << std::to_string(bestDistance) << std::endl;
    std::cout << "This is ";
    if (bestDistance != 159) { std::cout << "not "; }
    std::cout << "159." << std::endl;

    return 0;
}
