import sys

from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import (QApplication, QMainWindow)
from rendererGL import RendererGL
from cpp.PlatoSolids import tetrahedron, cube, icosahedron, octahedron, dodecahedron, sphere, chrysanthemum
import random
import strobe_colors


class PlatoSolids_widget(RendererGL):
    coords = None
    faces = None
    textures = None
    normals = None

    scale = 0.25
    win = None
    needs_compile = True
    gl_compiled_list = 1

    def __init__(self, mesh, win):
        super(PlatoSolids_widget, self).__init__()

        self.win = win

        self.coords, self.faces, self.textures, self.normals = mesh  # mesh expand (coords, faces, textures, normals)

        self.setFocusPolicy(Qt.StrongFocus)  # accepts key events

    def init(self, gl):
        gl.glCullFace(gl.GL_FRONT)

    def draw(self, gl):

        def get_color():
            return random.choice(strobe_colors.strobe_colors)

        def set_random_color(gl):
            gl.glColor3ubv(get_color())

        def draw_lines_raw(gl):
            set_random_color(gl)
            gl.glBegin(gl.GL_LINE_STRIP)
            for c in self.coords:
                gl.glVertex3fv(c)
            gl.glEnd()

        def draw_points(gl):
            gl.glPointSize(6)
            gl.glBegin(gl.GL_POINTS)
            for c in self.coords:
                gl.glVertex3fv(c)
            gl.glEnd()

        def draw_lines(gl):
            gl.glLineWidth(2)
            gl.glColor4f(1, 1, 1, 0.1)

            for face in self.faces:
                gl.glBegin(gl.GL_LINE_STRIP)
                for ic in face: gl.glVertex3fv(self.coords[ic])
                gl.glEnd()

        def draw_faces(gl):
            for face in self.faces:  # traverse faces
                gl.glBegin(gl.GL_POLYGON)
                gl.glColor3ubv(get_color())

                for ix_texture, ix_coord in enumerate(face):
                    gl.glTexCoord2fv(self.textures[ix_texture])
                    gl.glVertex3fv(self.coords[ix_coord])

                gl.glEnd()

        def draw_mesh(gl):
            if self.faces != []:
                draw_faces(gl)
                draw_lines(gl)
                draw_points(gl)
            else:
                draw_lines_raw(gl)

        def compile(gl):
            if self.needs_compile:
                gl.glNewList(self.gl_compiled_list, gl.GL_COMPILE)
                draw_mesh(gl)
                gl.glEndList()
                self.needs_compile = False

        def draw_list(gl):
            compile(gl)
            gl.glCallList(self.gl_compiled_list)

        gl.glScalef(self.scale, self.scale, self.scale)

        draw_list(gl)


class Main(QMainWindow):
    def __init__(self, mesh, *args):
        super(Main, self).__init__(*args)

        self.setWindowTitle('Plato Solids')
        self.setCentralWidget(PlatoSolids_widget(mesh, self))
        self.show()


if __name__ == '__main__':
    funcs = [tetrahedron, cube, icosahedron, octahedron, dodecahedron, sphere, chrysanthemum]

    app = QApplication(sys.argv)
    Main(funcs[5]())
    app.exec_()
