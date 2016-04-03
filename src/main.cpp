#include <iostream>
#include <fstream>

#include "vec3.h"

int main() {
    int nx = 200;
    int ny = 100;

    std::ofstream out("out.ppm");

    out << "P3\n" << nx << " " << ny << "\n255\n";

    for(int j = ny - 1; j >= 0; j-- ) {
        for(int i = 0; i < nx; i++) {
            vec3 color(float(i) / float(nx), float(j) / float(nx), 0.2);

            int ir = int(255.99 * color.r());
            int ig = int(255.99 * color.g());
            int ib = int(255.99 * color.b());

            out << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}