#include <vector>
#include <utility>

// Define a structure to represent a 2D point
struct Point {
    float x;
    float y;

    Point(float _x, float _y) : x(_x), y(_y) {}
};

// Define a structure to represent a polygon
typedef std::vector<Point> Polygon;

// Function to compute the intersection of two line segments
Point computeIntersection(const Point& p1, const Point& p2, const Point& q1, const Point& q2) {
    // Compute the intersection point
    // For simplicity, we assume line segments are not parallel and intersect
    // This function should handle cases where lines are parallel or collinear in a real implementation
    float px = ((p1.x * p2.y - p1.y * p2.x) * (q1.x - q2.x) - (p1.x - p2.x) * (q1.x * q2.y - q1.y * q2.x)) /
               ((p1.x - p2.x) * (q1.y - q2.y) - (p1.y - p2.y) * (q1.x - q2.x));
    float py = ((p1.x * p2.y - p1.y * p2.x) * (q1.y - q2.y) - (p1.y - p2.y) * (q1.x * q2.y - q1.y * q2.x)) /
               ((p1.x - p2.x) * (q1.y - q2.y) - (p1.y - p2.y) * (q1.x - q2.x));

    return Point(px, py);
}

// Function to clip a subject polygon against a clip polygon
Polygon clipPolygon(const Polygon& subjectPolygon, const Polygon& clipPolygon) {
    // Initialize the clipped polygon as the subject polygon
    Polygon clippedPolygon = subjectPolygon;

    // Clip against each edge of the clip polygon
    for (int i = 0; i < clipPolygon.size(); ++i) {
        Point edgeStart = clipPolygon[i];
        Point edgeEnd = clipPolygon[(i + 1) % clipPolygon.size()];

        // Initialize an empty list to store the new vertices of the clipped polygon
        Polygon newPolygon;

        // Loop through each consecutive pair of vertices in the clipped polygon
        for (int j = 0; j < clippedPolygon.size(); ++j) {
            Point p1 = clippedPolygon[j];
            Point p2 = clippedPolygon[(j + 1) % clippedPolygon.size()];

            // Compute the intersection of the current edge with the clip edge
            Point intersection = computeIntersection(p1, p2, edgeStart, edgeEnd);

            // If the intersection point is inside the clip edge, add it to the new polygon
            if ((p1.x - edgeStart.x) * (p2.x - edgeStart.x) <= 0 && (p1.y - edgeStart.y) * (p2.y - edgeStart.y) <= 0) {
                newPolygon.push_back(intersection);
            }

            // If the current vertex is inside the clip edge, add it to the new polygon
            if ((p1.x - edgeStart.x) * (p2.x - edgeStart.x) <= 0 && (p1.y - edgeStart.y) * (p2.y - edgeStart.y) <= 0) {
                newPolygon.push_back(p1);
            }
        }

        // Update the clipped polygon with the new vertices
        clippedPolygon = newPolygon;
    }

    return clippedPolygon;
}
