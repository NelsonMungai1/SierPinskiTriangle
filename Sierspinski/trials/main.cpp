#include <iostream>
#include "polygon.cpp" // Include the implementation of the Greiner-Hormann clipping algorithm

int main() {
    // Define the subject polygon
    Polygon subjectPolygon = {{-1, -1}, {2, -1}, {1, 2}, {-1, 1}};

    // Define the clip polygon
    Polygon clipPolygon = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    // Clip the subject polygon against the clip polygon
    // Clip the subject polygon against the clip polygon
    Polygon clippedPolygon = clipPolygon(subjectPolygon, clipPolygon);


    // Print the vertices of the clipped polygon
    std::cout << "Clipped Polygon Vertices:" << std::endl;
    for (const auto& vertex : clippedPolygon) {
        std::cout << "(" << vertex.x << ", " << vertex.y << ")" << std::endl;
    }

    return 0;
}
