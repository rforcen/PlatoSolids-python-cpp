from cpp.PlatoSolids import tetrahedron, cube, icosahedron, octahedron, dodecahedron, sphere, normal, polygon


def traverse(coords, faces):
    print('traverse')
    for face in faces:
        for ix_coord in face:
            print(coords[ix_coord], end=', ')
        print()
    print()


def test_funcs():
    for func in [tetrahedron, cube, icosahedron, octahedron, dodecahedron, sphere]:
        coords, faces, textures, normals = func()
        print(f'func:{func.__name__}\n\ncoords: {coords}\n\nfaces:{faces}\n\ntextures:{textures}\n\nnormals:{normals}')
        traverse(coords, faces)


def test_normal():
    n = normal([[0, 0, 1.732051],
                [1.632993, 0, -0.5773503],
                [-0.8164966, 1.414214, -0.5773503]])
    print(n)

def test_polygon():
    pc = polygon(10)
    print(pc)

test_polygon()