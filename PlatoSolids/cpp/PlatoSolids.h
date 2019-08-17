
#include <stdlib.h>
#include <vector>
#include <tuple>
#include <math.h>

using std::vector;
using std::tuple;

typedef vector<float>Coord;
typedef Coord Normal;
typedef vector<int> Face;
typedef vector<vector<int>> Faces;
typedef vector<vector<float>> Textures;
typedef vector<vector<float>> Coords;
typedef Coords Normals;
typedef tuple<Coords, Faces, Textures, Normals> Mesh;

class PlatoSolids {
public:

    static Textures textPolygon(int n) {  // generate texture polygon coords [u,v] x n
      vector<vector<float>>c;
      float pi2n = 6.28318530718f / n, r = 0.5f, xoffset = 0.5f, yoffset = xoffset;
      for (int i = 0; i < n; i++) {
        float a = n - i - n / 2.0f;
        c.push_back( vector<float> {r * sin(a * pi2n) + xoffset, r * cos(a * pi2n) + yoffset} );
      }
      return c;
    }

    static Textures gen_textures(Faces&faces) {
        return textPolygon(faces[0].size());
    }

    static Normal calc_normal(const Coord&p, const Coord&p1, const Coord&p2) {  // to norm
      float xa = p1[0] - p[0], ya = p1[1] - p[1], za = p1[2] - p[2];
      float xb = p2[0] - p[0], yb = p2[1] - p[1], zb = p2[2] - p[2];
      float nx = ya * zb - za * yb, ny = za * xb - xa * zb, nz = xa * yb - ya * xb;
      return normalise(nx, ny, nz);
    }

    static vector<float> normalise(float x, float y, float z) {  // Normalise a vector
      float length = x * x + y * y + z * z;
      if (length > 0) {
        length = sqrt(length);
        x /= length, y /= length, z /= length;
      } else {
        x = y = z = 0;
      }

      return vector<float>{x,y,z};
    }

    static Normal calc_normal(const Face &face, const Coords &coords) {
        return calc_normal(coords[face[0]], coords[face[1]], coords[face[2]]);
    }

    static Normals calc_normals(const Faces &faces, const Coords &coords) {
        Normals ns;
        for (auto face:faces) ns.push_back( calc_normal(face, coords) );
        return ns;
    }



public:
    static  Mesh tetrahedron() {
        Faces faces = {{0, 1, 2}, {0, 2, 3}, {0, 3, 1}, {1, 3, 2}};
        Coords coords = {
          {0, 0, 1.732051f},
          {1.632993f, 0, -0.5773503f},
          {-0.8164966f, 1.414214f, -0.5773503f},
          {-0.8164966f, -1.414214f, -0.5773503f}
        };
        Textures textures=gen_textures(faces);

        return Mesh(coords, faces, textures, calc_normals(faces, coords));
    };

    static Mesh cube() {
        const float sz=1;
        Faces faces =  {{0, 1, 2, 3},     {4, 5, 6, 7},   {8, 9, 10, 11},
                        {12, 13, 14, 15}, {16, 17, 18, 19}, {20, 21, 22, 23}};

        Coords coords= {
              {-sz, -sz, sz},  {sz, -sz, sz},  {sz, sz, sz},  {-sz, sz, sz},   // FRONT
              {-sz, -sz, -sz}, {-sz, sz, -sz}, {sz, sz, -sz}, {sz, -sz, -sz},  // BACK
              {-sz, -sz, -sz}, {-sz, -sz, sz}, {-sz, sz, sz}, {-sz, sz, -sz},  // LEFT
              {sz, -sz, -sz},  {sz, sz, -sz},  {sz, sz, sz},  {sz, -sz, sz},   // RIGHT
              {-sz, sz, -sz},  {-sz, sz, sz},  {sz, sz, sz},  {sz, sz, -sz},   // TOP
              {-sz, -sz, -sz}, {sz, -sz, -sz}, {sz, -sz, sz}, {-sz, -sz, sz}   // BOTTOM
        };

        return Mesh(coords, faces, gen_textures(faces), calc_normals(faces, coords));
    }

    static Mesh octahedron() {

        Faces faces = {{0, 1, 2}, {0, 2, 3}, {0, 3, 4}, {0, 4, 1},
                              {1, 4, 5}, {1, 5, 2}, {2, 5, 3}, {3, 5, 4}};
        Coords coords = {{0, 0, 1.414f},  {1.414f, 0, 0},
                              {0, 1.414f, 0},  {-1.414f, 0, 0},
                              {0, -1.414f, 0}, {0, 0, -1.414f}};

        return Mesh(coords, faces, gen_textures(faces), calc_normals(faces, coords));
    }

    static Mesh dodecahedron() {
         Faces faces = {
          {0, 1, 4, 7, 2},      {0, 2, 6, 9, 3},      {0, 3, 8, 5, 1},
          {1, 5, 11, 10, 4},    {2, 7, 13, 12, 6},    {3, 9, 15, 14, 8},
          {4, 10, 16, 13, 7},   {5, 8, 14, 17, 11},   {6, 12, 18, 15, 9},
          {10, 11, 17, 19, 16}, {12, 13, 16, 19, 18}, {14, 15, 18, 19, 17}};
         Coords coords = {{0, 0, 1.07047},
                           {0.713644, 0, 0.797878},                   {-0.356822, 0.618, 0.797878},
                           {-0.356822, -0.618, 0.797878},             {0.797878, 0.618034, 0.356822},
                           {0.797878, -0.618, 0.356822},              {-0.934172, 0.381966, 0.356822},
                           {0.136294, 1., 0.356822},                  {0.136294, -1., 0.356822},
                           {-0.934172, -0.381966, 0.356822},          {0.934172, 0.381966, -0.356822},
                           {0.934172, -0.381966, -0.356822},          {-0.797878, 0.618, -0.356822},
                           {-0.136294, 1., -0.356822},                {-0.136294, -1., -0.356822},
                           {-0.797878, -0.618034, -0.356822},         {0.356822, 0.618, -0.797878},
                           {0.356822, -0.618, -0.797878},             {-0.713644, 0, -0.797878},
                           {0, 0, -1.07047}};

         return Mesh(coords, faces, gen_textures(faces), calc_normals(faces, coords));
    }

    static Mesh icosahedron() {
          const float X = .525731112119133606, Z = .850650808352039932;

          Faces faces = {{0, 4, 1},  {0, 9, 4},  {9, 5, 4},  {4, 5, 8},
                           {4, 8, 1},  {8, 10, 1}, {8, 3, 10}, {5, 3, 8},
                           {5, 2, 3},  {2, 7, 3},  {7, 10, 3}, {7, 6, 10},
                           {7, 11, 6}, {11, 0, 6}, {0, 1, 6},  {6, 1, 10},
                           {9, 0, 11}, {9, 11, 2}, {9, 2, 5},  {7, 2, 11}};
          Coords coords = {{-X, 0.0, Z}, {X, 0.0, Z},   {-X, 0.0, -Z},
                           {X, 0.0, -Z}, {0.0, Z, X},   {0.0, Z, -X},
                           {0.0, -Z, X}, {0.0, -Z, -X}, {Z, X, 0.0},
                           {-Z, X, 0.0}, {Z, -X, 0.0},  {-Z, -X, 0.0}};


          return Mesh(coords, faces, gen_textures(faces), calc_normals(faces, coords));
    }

    static Mesh sphere(int sec=20) {
          const float rad=1;

          const float pi=M_PI, pi2=pi*2;
          Coords coords;
          Faces faces;
          Textures textures;


          float du = 1. / sec, dv = 1. / sec;

          for (int r = 0; r <= sec; r++) {
            float   v = r * dv,       // [0,1]
                    theta1 = v * pi,  // [0,PI]
                    xt = -sin(theta1), yt = cos(theta1), zt = 0,
                    xn = xt, yn = yt, zn = zt;

            for (int c = 0; c <= sec; c++) {
              float u = c * du,              // [0,1]
                    theta2 = u * pi2,        // [0,2PI]
                    x = xn, y = yn, z = zn,  // xyz=n
                    cosRY = cos(theta2),  sinRY = sin(theta2);  // xyz.rotateY

              xt = (x * cosRY) + (z * sinRY);
              zt = (x * -sinRY) + (z * cosRY);
              x = xt;
              z = zt;

              x *= rad, y *= rad, z *= rad;  // xyz*=rad

              coords.push_back(vector<float>{x,y,z}); // coords
              textures.push_back(vector<float>{u,v}); // texture coords (u,v)
            }
          }

          // Add faces
          for (int r = 0, cl=sec+1; r < sec; r++)
            for (int c = 0, off=r*cl; c < sec; c++)
              faces.push_back( vector<int>{ off + c, off + c + 1, off + (c + 1 + cl), off + (c + 0 + cl) } );

          return Mesh(coords, faces, textures, calc_normals(faces, coords));
    }

    static Mesh chrysanthemum(void) {
    const float scale=0.1;
      int N = 3000;
      float u, r, p4, p8,
            x, y, z;
      Coords coords;

      for (int i = 0; i < N; i++) {
        u = i * 21.0 * M_PI / N;
        p4 = sin(17 * u / 3);
        p8 = sin(2 * cos(3 * u) - 28 * u);
        r = 5 * (1 + sin(11 * u / 5)) -
            4 * p4 * p4 * p4 * p4 * p8 * p8 * p8 * p8 * p8 * p8 * p8 * p8;
        x = r * cos(u);
        y = r * sin(u);
        z = (r / 20 + .2) * sin(r * (M_PI * 2) / 7);
        coords.push_back({x*scale, y*scale, z*scale});
      }

      return Mesh(coords, {}, {}, {});
    }

};