# OpenGL_Ellipsoid

* img src - Wolfram Alpha (https://mathworld.wolfram.com/RegularIcosahedron.html)
<p>
<img src = "https://raw.githubusercontent.com/anikkcah/OpenGL_Ellipsoid/master/icosahedron.jpg" width="900" height="500" hspace="15">
</p>


## NOTE :
I did the OpenGL project as an assignment for Computer Graphics present in the curriculum of M.Tech in CSE (Machine Intelligence) coursework.
We were given task for constructing 3D geometrical shapes.
I had the task of making a 3D Ellipsoid.
It was only required to run the OpenGL project and generate output, without emphasis on the inner mathematical foundation.

## KEY POINTS :
- Here I present the intuition behind the preferred approach.
- I have converted an Icosahedron to a Ellipsoid.
{ Intuition for this came when the professor mentioned that any 2D or 3D structure can be formed from the triangle primitive. }
- Try changing the subdivisionDepth from 1 to 4 and viceversa. observe the output (smoothness of the ellipsoid improves)


## Mathematical Basis

An icosahedron is a polyhedron with 20 triangular faces, 12 vertices and 30 edges.
Vertices of a unit icosahedron can be placed on 3 orthogonal rectangles.

Golden Ratio (phi) plays a crucial role in coordinates of icosahedron's vertices.
The approximate value is 1.618

### Normalization Factor :
Vertices need to be normalized to a unit vector, ensuring they are on unit sphere.
Given the golden ratio,
Key Normalization ensures unit length.
X = 1/sqrt(1+(phi)^2) = .525731112119133606
Z = (phi)/sqrt(1+(phi)^2) = .850650808352039932


---- X and Z are used to define positions of vertices in 3D space.
---- The positions are chosen (coordinates) such that they form a unit icosahedron ( you can use the origami structure for plotting the points of icosahedron ),
     which can be subdivided into smaller triangles to approximate a sphere or an ellipsoid when the 'subdivisionDepth' is increased.


using these values coordinates are derived.
Coordinates are used to construct the icosahedron and their normalization ensures that all the vertices lie on the unit sphere's surface.

using these specific values for X and Z the code ensures that the icosahedron is mathematically accurate and forms the basis for the smooth ellipsoid created through recursive subdivision.


### Visualization :
The vertices are then connected to form 20 triangular faces of icosahedron.
By recursively subdividing these triangles, the surface is refined, transforming into a smoother sphere or ellipsoid.
 
## ICOSAHEDRON TRIANGULAR FACE INDICES :
Manually connect these vertices to form 20 equilateral triangles. Each triangle is represented by three indices, corresponding to the vertex positions in vdata.
