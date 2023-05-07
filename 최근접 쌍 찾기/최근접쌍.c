#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 100000

typedef struct {
    double x;
    double y;
} Point;

int n;
Point points[MAX_N];

int cmpX(const void* a, const void* b) {
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    return (p1->x > p2->x) - (p1->x < p2->x);
}


int cmpY(const void* a, const void* b) {
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    return (p1->y > p2->y) - (p1->y < p2->y);
}


double dist(Point p1, Point p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

double closestPair(int l, int r, Point Px[], Point Py[]) {
    if (r - l + 1 <= 3) {
        
        double minDist = 1e20;
        for (int i = l; i <= r; i++) {
            for (int j = i + 1; j <= r; j++) {
                double d = dist(Px[i], Px[j]);
                if (d < minDist) {
                    minDist = d;
                }
            }
        }
        return minDist;
    }

    int mid = (l + r) / 2;
    Point midPoint = Px[mid];

    Point Pyl[mid - l + 1], Pyr[r - mid];
    int li = 0, ri = 0;
    for (int i = l; i <= r; i++) {
        if (Py[i].x < midPoint.x) {
            Pyl[li++] = Py[i];
        }
        else {
            Pyr[ri++] = Py[i];
        }
    }

    double dl = closestPair(l, mid, Px, Pyl);
    double dr = closestPair(mid + 1, r, Px + mid + 1, Pyr);
    double d = fmin(dl, dr);

    Point strip[r - l + 1];
    int stripSize = 0;
    for (int i = l; i <= r; i++) {
        if (fabs(Py[i].x - midPoint.x) < d) {
            strip[stripSize++] = Py[i];
        }
    }

    for (int i = 0; i < stripSize; i++) {
        for (int j = i + 1; j < stripSize; j++) {
            if (strip[j].y - strip[i].y >= d) {
                break;
            }
            double distStrip = dist(strip[i], strip[j]);
            if (distStrip < d) {
                d = distStrip;
            }
        }
    }

    return d