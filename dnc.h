/*
 *      dnc.h
 *      Justin Paik (jpaik03)
 *      11 December, 2025
 *      Divide & Conquer Convex Hull Algorithm
 *
 *      Contains function declarations for the divide and conquer convex hull
 *      algorithm.
 */

#ifndef DNC_H
#define DNC_H

#include <vector>

#include "en47_vis_txt.h"

using namespace std;

typedef vector<my_point> Points;

/* Function Declarations */
Points dnc(Points &pts);

#endif
