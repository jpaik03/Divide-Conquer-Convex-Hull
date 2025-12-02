/*
 *      project.cpp
 *      Justin Paik (jpaik03)
 *      11 December, 2025
 *      Divide & Conquer Convex Hull Algorithm
 *
 *      The main driver for dnc_ch. Uses CGAL for geometry logic. Visual output
 *      will be handled via SVG generation.
 *      TODO: Further description
 */

/* Standard c++ Includes */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

/* CGAL Includes */
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/point_generators_2.h>

using namespace std;

/* CGAL Typedefs */
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_2 Point;

/* Function declarations */
void readInput(string inputFile, vector<Point> &points);
void sortPoints(vector<Point> &points);
void saveToSVG(string outputFile, vector<Point> &points);
void printPoints(vector<Point> &points);

/* Define constants */
const double SVG_W = 800.0;
const double SVG_H = 600.0;
const double SVG_M = 50.0;


int main(int argc, char *argv[])
{
        vector<Point> points;
        
        if (argc == 2) {
                readInput(argv[1], points);
        } else {
                cerr << "Usage: ./dnc_ch inputFile\n";
                exit(EXIT_FAILURE);
        }

        // TODO: Algorithm Implementation
        sortPoints(points);

        cout << "Points:\n";
        printPoints(points);
        cout << points.size() << " points read from file.\n";

        /* Visualization */
        saveToSVG("output.svg", points);
        cout << "Graph saved to output.svg\n";

        return 0;
}

/******** readInput ********
 *
 * Populates a vector of Points using Points read in from a given file.
 *
 * Parameters:
 *      string inputFile:       Filename of a file containing Points.
 *      vector<Point> &points:  Address to a vector of Points.
 * Returns:
 *      None.
 * Expects:
 *      inputFile is a valid filename.
 * Notes:
 *      Throws an error if inputFile fails to open.
 ************************/
void readInput(string inputFile, vector<Point> &points)
{
        /* Open input file and verify it opened correctly */
        ifstream infile(inputFile);
        if (infile.fail()) {
                cerr << "Error: could not open file " << inputFile << ".\n";
                exit(EXIT_FAILURE);
        }

        /* Read in points */
        double x, y;
        while (infile >> x >> y) {
                points.push_back(Point(x, y));
        }

        infile.close();
}

/******** sortPoints ********
 *
 * Sorts a vector of Points by ascending x-coordinate, breaking ties by
 * ascending y-coordinate.
 *
 * Parameters:
 *      vector<Point> &points:  Address to a vector of Points.
 * Returns:
 *      None.
 * Expects:
 *      None.
 * Notes:
 *      None.
 ************************/
void sortPoints(vector<Point> &points)
{
        sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
                /* Sort by ascending x-coordinate */
                if (a.x() != b.x()) {
                        return a.x() < b.x();
                }
                /* Break ties by sort by ascending y-coordinate */
                return a.y() < b.y();
        });
}

void saveToSVG(string outputFile, vector<Point> &points)
{
        
}

/******** printPoints ********
 *
 * Prints every Point in a vector of Points.
 *
 * Parameters:
 *      vector<Point> &points:  Address to a vector of Points.
 * Returns:
 *      None.
 * Expects:
 *      None.
 * Notes:
 *      This is for testing purposes only.
 ************************/
void printPoints(vector<Point> &points)
{
        Point p;
        for (unsigned i = 0; i < points.size(); i++) {
                p = points[i];
                cout << "(" << p.x() << ", " << p.y() << ")\n";
        }
}