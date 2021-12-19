import xml_parser as parser
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np


import os


class surface_gen:
    def __init__(self,xml_file):
        self._par = parser.xml_parser(xml_file)
        return

    def set_x_label(self,x_label):
        self._x_label = x_label
        return

    def set_y_label(self,y_label):
        self._y_label = y_label
        return

    def set_z_label(self,z_label):
        self._z_label = z_label
        return

    def set_title(self,title):
        self._title = title
        return

    def plot(self,clip_last_rows=None):
        xy = self._par.abscissa()
        if self._par.type() == parser.xml_type.SURFACE_ST:
            z = self._par.ordinate()
            hf = plt.figure()
            ha = hf.add_subplot(111, projection='3d')
            # `plot_surface` expects `x` and `y` data to be 2D
            X, Y = np.meshgrid(xy[0], xy[1])
            ha.plot_surface(X, Y, z, rstride=1, cstride=1,
                            cmap='viridis', edgecolor='none')
            ha.set_title(self._title)
            ha.set_xlabel(self._x_label)
            ha.set_ylabel(self._y_label)
            ha.set_zlabel(self._z_label)
            # plt.savefig("")
            plt.show()
        elif self._par.type() == parser.xml_type.SURFACE_SS:
            z = self._par.ordinate(clip_last_rows)
            if not clip_last_rows is None:
                xy[1] = xy[1][:-clip_last_rows]
            hf = plt.figure()
            ha = hf.add_subplot(111, projection='3d')
            # `plot_surface` expects `x` and `y` data to be 2D
            Y, X = np.meshgrid(xy[1], xy[0])
            ha.plot_surface(X, Y, z, rstride=1, cstride=1,
                            cmap='viridis', edgecolor='none')
            ha.set_title(self._title)
            ha.set_xlabel(self._x_label)
            ha.set_ylabel(self._y_label)
            ha.set_zlabel(self._z_label)
            # plt.savefig("")
            plt.show()
            return
        else:
            return


path = os.getcwd()
files_path = "\\".join(path.split("\\")[:-1]) + "\\xmls"
file_crv = files_path+"\\Black_Scholes.xml"


srf = surface_gen(file_crv)
srf.set_x_label('Spot')
srf.set_y_label('Time to mat')
srf.set_z_label('Call Option Price')
srf.set_title('BS PDE (Euler Device explicit Scheme)')
srf.plot()