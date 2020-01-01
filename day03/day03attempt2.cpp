#include "../util.hpp"

struct Point {
    int x, y;
    Point(): x(0), y(0) { }
    Point(int _x, int _y): x(_x), y(_y) { }
    size_t Hash(void) const { return (size_t)(((long)x << 32) + y); }
    Point operator-(const Point& rhs) const { return Point(x - rhs.x, y - rhs.y); }
    bool operator==(const Point& rhs) const { return (x == rhs.x) && (y == rhs.y); }
    bool operator!=(const Point& rhs) const { return x != rhs.x || y != rhs.y; }
    bool operator<(const Point& rhs) const { return Hash() < rhs.Hash(); }
};
// true if a is before b
bool EquatePoints(const Point& a, const Point& b) { return a.Hash() < b.Hash(); }
const Point PointZero = Point();
int ManhattanDistance(const Point a, const Point b) {
    return abs(b.x - a.x) + abs(b.y - a.y);
}
class PointHasher {
public:
    size_t operator()(const Point& p) const {
        return p.Hash();
    }
};
class PointComparer {
private:
    PointHasher hash;
public:
    // true if a is before b
    size_t operator()(const Point& a, const Point& b) const {
        return hash(a) < hash(b);
    }
};

const char UP = 'U';
const char DOWN = 'D';
const char LEFT = 'L';
const char RIGHT = 'R';

std::unordered_set<Point, PointHasher> getPointsFromMoves(const std::vector<std::string>& moves) {
    std::unordered_set<Point, PointHasher> points;
    Point currentPos = Point(0, 0);
    for (size_t m = 0; m < moves.size(); m++)
    {
        std::string move = moves.at(m);
        char dir = move[0];
        int dist = std::stoi(move.substr(1));
        switch (dir) {
            case UP:
                for (int i = 0; i < dist; i++) {
                    currentPos.y++;
                    points.emplace(currentPos);
                }
                break;

            case DOWN:
                for (int i = 0; i < dist; i++) {
                    currentPos.y--;
                    points.emplace(currentPos);
                }
                break;

            case LEFT:
                for (int i = 0; i < dist; i++) {
                    currentPos.x--;
                    points.emplace(currentPos);
                }
                break;

            case RIGHT:
                for (int i = 0; i < dist; i++) {
                    currentPos.x++;
                    points.emplace(currentPos);
                }
                break;
        }
    }

    return points;
}

int main(int argc, char ** args) {
    // read data
    std::ifstream file("example1input.txt");
    const std::vector<std::string> wire1Moves = readCSVLine(file);
    const std::vector<std::string> wire2Moves = readCSVLine(file);
    file.close();

    // build a map of the points that are on wire 1's path
    auto wire1Points = getPointsFromMoves(wire1Moves);
    std::set<Point, PointComparer> wire1Ordered(wire1Points.begin(), wire1Points.end());
    auto wire2Points = getPointsFromMoves(wire2Moves);
    std::set<Point, PointComparer> wire2Ordered(wire2Points.begin(), wire2Points.end());

    // check whether wires cross any of the same points
    std::vector<Point> intersections(2048);
    auto it = std::set_intersection(wire1Ordered.begin(), wire1Ordered.end(),
                                    wire2Ordered.begin(), wire2Ordered.end(),
                                    intersections.begin(), EquatePoints);
    intersections.resize(it - intersections.begin());
    
    int shortestDistance = INT32_MAX;
    int shortestSumSteps = INT32_MAX;
    for (auto i : intersections) {
        // closest to origin
        int dist = ManhattanDistance(PointZero, i);
        if (dist < shortestDistance) shortestDistance = dist;

        // sum steps
        int wire1Steps = abs(std::distance(wire1Points.begin(), wire1Points.find(i)));
        int wire2Steps = abs(std::distance(wire2Points.begin(), wire2Points.find(i)));
        int sum = wire1Steps + wire2Steps;
        if (sum < shortestSumSteps) shortestSumSteps = sum;
    }

    std::cout << "Closest intersection : " << std::to_string(shortestDistance) << std::endl;
    std::cout << "Wire 1's steps       : " << std::to_string(wire1Points.size()) << std::endl;
    std::cout << "Wire 2's steps       : " << std::to_string(wire2Points.size()) << std::endl;
    std::cout << "Sum of steps         : " << std::to_string(wire1Points.size() + wire2Points.size()) << std::endl;
    std::cout << "Shortest sum of steps: " << std::to_string(shortestSumSteps) << std::endl;
    return 0;
}
