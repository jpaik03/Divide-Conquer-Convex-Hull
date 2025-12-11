/*
 *      project.cpp
 *      Justin Paik (jpaik03)
 *      11 December, 2025
 *      Divide & Conquer Convex Hull Algorithm
 *
 *      The main driver for dnc_ch. Reads in a list of points and runs the 
 *      divide and conquer convex hull algorithm on them. Uses Professor
 *      Souvaine's LEDA library (en47_vis_txt.h) for geometry and visualization.
 */

/* Standard c++ Includes */
#include <iostream>
#include <fstream>
#include <vector>
#include "assert.h"

/* Professor Souvaine's LEDA library */
#include "en47_vis_txt.h"

#include "dnc.h"

using namespace std;

typedef vector<my_point> Points;

/* Function declarations */
void readInput(string inputFile, Points &pts);
void printPoints(Points &pts);
void display(const Points &pts, const Points &hull);

int main(int argc, char *argv[])
{
        Points pts;
        
        if (argc == 2) {
                readInput(argv[1], pts);
        } else {
                cerr << "Usage: ./dnc_ch inputFile\n";
                exit(EXIT_FAILURE);
        }

        cout << "Points:\n";
        printPoints(pts);
        cout << pts.size() << " total points.\n";
        
        /* Run algorithm and display convex hull */
        display(pts, {});
        Points hull = dnc(pts);
        cout << hull.size() << " points in hull.\n";
        
        /* Final Display */
        en47_close();
        display(pts, hull);
        
        /* Close on mouse click */
        en47_mouse_wait();
        en47_close();

        return 0;
}

/******** readInput ********
 *
 * Populates a vector of Points using data from a given file.
 *
 * Parameters:
 *      string inputFile:       Filename of a file containing Points.
 *      Points &pts:  Address to a vector of Points.
 * Returns:
 *      None.
 * Expects:
 *      inputFile is a valid filename.
 * Notes:
 *      Throws an error if inputFile fails to open.
 ************************/
void readInput(string inputFile, Points &pts)
{
        /* Open input file and verify it opened correctly */
        ifstream infile(inputFile);
        if (infile.fail()) {
                cerr << "Error: could not open file " << inputFile << ".\n";
                exit(EXIT_FAILURE);
        }

        /* Read in points */
        int x, y;
        int id = 0;
        my_point p;
        while (infile >> x >> y) {
                p.x = x;
                p.y = y;
                p.ID = id;
                pts.push_back(p);
                id++;
        }

        infile.close();
}

/******** display ********
 *
 * Uses en47 functions to draw the window, points, and hull.
 *
 * Parameters:
 *      Points &pts:  Address to a vector of Points.
 *      Points &hull: Address to a vector of Points representing the hull.
 * Returns:
 *      None.
 * Expects:
 *      None.
 * Notes:
 *      None.
 ************************/
void display(const Points &pts, const Points &hull)
{
        if (pts.empty()) return;

        /* Calculate window size */
        int minX = pts[0].x, maxX = pts[0].x;
        int minY = pts[0].y, maxY = pts[0].y;
        int mar = 10;
        my_point p;
        for (size_t i = 0; i < pts.size(); i++) {
                p = pts[i];
                if (p.x < minX) minX = p.x;
                if (p.x > maxX) maxX = p.x;
                if (p.y < minY) minY = p.y;
                if (p.y > maxY) maxY = p.y;
        }
        
        /* Display */
        en47_display(minX - mar, maxX + mar, minY - mar, maxY + mar);
        
        /* Draw input points */
        for (size_t i = 0; i < pts.size(); i++) {
                p = pts[i];
                en47_draw_point(p.x, p.y, BLACK);
        }

        /* Draw hull lines */
        if (!hull.empty()) {
                for (size_t i = 0; i < hull.size(); i++) {
                        /* Wrap around to connect the last point to the first */
                        const my_point &p1 = hull[i];
                        const my_point &p2 = hull[(i + 1) % hull.size()];
                        en47_draw_segment(p1.x, p1.y, p2.x, p2.y, BLUE);
                }
        }
}

/******** printPoints ********
 *
 * Prints every my_point in a vector of Points.
 *
 * Parameters:
 *      Points &pts:  Address to a vector of Points.
 * Returns:
 *      None.
 * Expects:
 *      pts is not empty.
 * Notes:
 *      Throws a CRE if pts is empty.
 *      This is for testing purposes only.
 ************************/
void printPoints(Points &pts)
{
        if (pts.empty()) {
                cerr << "No points given.\n";
                assert(!pts.empty());
        }

        my_point p;
        for (size_t i = 0; i < pts.size(); i++) {
                p = pts[i];
                cout << "(" << p.x << ", " << p.y << ")\n";
        }
}
