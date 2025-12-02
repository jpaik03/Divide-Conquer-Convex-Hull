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
void saveToSVG(string outputFile, vector<Point> &points, vector<Point> &hull);
void printPoints(vector<Point> &points);

/* Define constants */
const double SVG_W = 1491.0;
const double SVG_H = 803.0;
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
        saveToSVG("output.svg", points, points);
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

void saveToSVG(string outputFile, vector<Point> &points, vector<Point> &hull)
{
        if (points.empty()) {
                return;
        }

        /* Open output file */
        ofstream svg(outputFile);

        /* Find range of the data */
        double minX = points[0].x(), maxX = points[0].x();
        double minY = points[0].y(), maxY = points[0].y();

        Point p;
        for (unsigned i = 0; i < points.size(); i++) {
                p = points[i];
                if (p.x() < minX) {
                        minX = p.x();
                }
                if (p.x() > maxX) {
                        maxX = p.x();
                }
                if (p.y() < minY) {
                        minY = p.y();      
                } if (p.y() > maxY) {
                        maxY = p.y();
                }
        }
        
        /* Prevent zero division edge case */
        double rangeX = maxX - minX;
        if (rangeX == 0) {
                rangeX = 1.0;
        }
        double rangeY = maxY - minY;
        if (rangeY == 0) {
                rangeY = 1.0;
        }

        double scaleX = (SVG_W - 2 * SVG_M) / rangeX;
        double scaleY = (SVG_H - 2 * SVG_M) / rangeY;

        /* SVG header */
        svg << "<svg xmlns=\"http://www.w3.org/2000/svg\" "
            << "width=\"" << SVG_W << "\" height=\"" << SVG_H
            << "\" viewBox=\"0 0 " << SVG_W << " " << SVG_H << "\">\n"
            << "<rect width=\"100%\" height=\"100%\" fill=\"white\"/>\n";

        /* Draw convex hull */
        if (!hull.empty()) {
                svg << "<polygon points=\"";
                for (unsigned i = 0; i < hull.size(); i++) {
                        // Apply scale
                        double sx = SVG_M + (hull[i].x() - minX) * scaleX;
                        double sy = (SVG_H - SVG_M) - (hull[i].y() - minY) * scaleY;
                        
                        svg << sx << "," << sy << " ";
                }
                svg << "\" fill=\"rgba(0,0,255,0.1)\" stroke=\"blue\" stroke-width=\"2\"/>\n";
        }

        /* Draw every point */
        for (unsigned i = 0; i < points.size(); i++) {
                double sx = SVG_M + (points[i].x() - minX) * scaleX;
                double sy = (SVG_H - SVG_M) - (points[i].y() - minY) * scaleY;

                svg << "<circle cx=\"" << sx << "\" cy=\"" << sy 
                << "\" r=\"3\" fill=\"black\" />\n";
        }

        svg << "</svg>";
        svg.close();
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