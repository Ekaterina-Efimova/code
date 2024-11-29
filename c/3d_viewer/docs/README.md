# 3DViewer v2.0

## Introduction

Introduction
In this project you will implement a program for viewing 3D wireframe models (3D Viewer) in the C programming language. The models themselves must be loaded from .obj files and be viewable on screen with the ability to rotate, scale and translate

## Information

Information
A wireframe model is a model of an object in 3D graphics, which is a set of vertices and edges that defines the shape of the displayed polyhedral object in three-dimensional space.

Structured programming reminder
Structured programming based on two main principles:

The principle of divide and conquer (decomposition) - the principle of solving complex problems by decomposing them into many smaller subproblems, that are easier to understand and solve. Besides, there is no code duplication when solving subproblems and the solutions themselves are reused if necessary;
The principle of hierarchical ordering - the principle of organising the components of a problem into hierarchical tree structures with new details added at each level (from the top level with a single entry point, to the lower levels with specific data structures and implementations). That is, there should be no calculations and no input/output operations on the same level.

Thus, using a structured style results in the program being built like a puff pastry pie from top to bottom. Errors are generated at the lower levels and thrown up to the top, where they are displayed to the user.

.Obj file format for representing the definition of 3D objects
.Obj file is a geometry definition file format first developed by Wavefront Technologies. The file format is open and accepted by many 3D graphics application vendors.
The .obj file format is a simple data format that represents only three-dimensional geometry, specifically the position of each vertex, the UV of each texture coordinate vertex, vertex normals and the faces that define each polygon as a list of vertices and texture vertices. Obj coordinates have no units, but Obj files can contain scale information in a readable comment line.
In this project you only need to implement support for vertex and face lists. Everything else is optional.

Affine transformations
This section describes basic affine transformations (translation, rotation, scaling) in the plane, using two-dimensional objects (images) as an example. Similarly, affine transformations can also be used for three-dimensional space.
An affine transformation is a mapping in a plane or in space onto itself, in which parallel lines become parallel lines, intersecting lines become intersecting lines, and oblique lines become oblique lines.
A transformation in a plane is called affine if it is mutually unambiguous and the image of any line is a line. A transformation (mapping) is called mutually unambiguous (bijective) if it transforms different points into different points, and each point is transformed into a point.
In algebraic terms, an affine transformation is a transformation of the form f(x) = M x + v, where M is some invertible matrix and v is some value.
Properties of affine transformations:

A composition of affine transformations is an affine transformation too
The inverse of an affine transformation is an affine transformation too
The ratio of areas is conserved.
The ratio of lengths of line segments is conserved.


Translation
Translation matrix in uniform two-dimensional coordinates

1 0 a
0 1 b
0 0 1


where a and b are the values on x and y by which the source point should be moved. Thus, to move a point, you must multiply the translation matrix by it.

x1     1 0 a     x 
y1  =  0 1 b    y
1      0 0 1     1


where x and y are the original coordinates of the point and x1 and y1 are the resulting coordinates of the new point after translation.

Rotation
Clockwise rotation matrix in uniform two-dimensional coordinates

cos(a)  sin(a) 0
-sin(a) cos(a) 0
0       0      1


where a is the rotation angle in two-dimensional space. To get the coordinates of the new point it is necessary to multiply the rotation matrix by the original point in the same way as the translation matrix

x1     cos(a)  sin(a) 0     x 
y1  =  -sin(a) cos(a) 0    y
1      0       0      1     1



Scaling
Scaling matrix in uniform two-dimensional coordinates

a 0 0
0 b 0
0 0 1


where a and b are the scaling factors for the OX and OY axes respectively. Obtaining coordinates of a new point is similar to the cases described above.