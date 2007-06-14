/*-----------------------------------------------------------------------------

  File	      : primitives3d.h

  Description : This CImg plug-in defines functions to create common 3D meshes.

  Copyright  : David Tschumperle - http://www.greyc.ensicaen.fr/~dtschump/

  This software is governed by the CeCILL  license under French law and
  abiding by the rules of distribution of free software.  You can  use,
  modify and/ or redistribute the software under the terms of the CeCILL
  license as circulated by CEA, CNRS and INRIA at the following URL
  "http://www.cecill.info".

  As a counterpart to the access to the source code and  rights to copy,
  modify and redistribute granted by the license, users are provided only
  with a limited warranty  and the software's author,  the holder of the
  economic rights,  and the successive licensors  have only  limited
  liability.

  In this respect, the user's attention is drawn to the risks associated
  with loading,  using,  modifying and/or developing or reproducing the
  software by the user in light of its specific status of free software,
  that may mean  that it is complicated to manipulate,	and  that  also
  therefore means  that it is reserved for developers  and  experienced
  professionals having in-depth computer knowledge. Users are therefore
  encouraged to load and test the software's suitability as regards their
  requirements in conditions enabling the security of their systems and/or
  data to be ensured and,  more generally, to use and operate it in the
  same conditions as regards security.

  The fact that you are presently reading this means that you have had
  knowledge of the CeCILL license and that you accept its terms.

  ------------------------------------------------------------------------------*/

#ifndef cimg_plugin_primitives3d
#define cimg_plugin_primitives3d

//! Get a centered cube of size 1.
template<typename tf> static CImg cube(CImgList<tf>& primitives) {
  CImgList<T> points;
  primitives.assign();
  const T a = (T)0.5f;
  points.insert(CImg<T>::vector(-a,-a,-a));
  points.insert(CImg<T>::vector(a,-a,-a));
  points.insert(CImg<T>::vector(a,a,-a));
  points.insert(CImg<T>::vector(-a,a,-a));
  points.insert(CImg<T>::vector(-a,-a,a));
  points.insert(CImg<T>::vector(a,-a,a));
  points.insert(CImg<T>::vector(a,a,a));
  points.insert(CImg<T>::vector(-a,a,a));

  primitives.insert(CImg<tf>::vector(0,3,2,1));
  primitives.insert(CImg<tf>::vector(4,5,6,7));
  primitives.insert(CImg<tf>::vector(0,1,5,4));
  primitives.insert(CImg<tf>::vector(3,7,6,2));
  primitives.insert(CImg<tf>::vector(0,4,7,3));
  primitives.insert(CImg<tf>::vector(1,2,6,5));
  return points.get_append('x');
}

//! Get a triangulation of a unit cone of height 1.
template<typename tf> static CImg cone(CImgList<tf>& primitives, const unsigned int subdivisions=16) {
  CImgList<T> points;
  primitives.assign();
  points.insert(CImg<T>::vector(0,0,0.5f));
  points.insert(CImg<T>::vector(0,0,-0.5f));
  points.insert(CImg<T>::vector(0.5f,0,-0.5f));
  const float delta = 360.0f/subdivisions;
  for (float i = 0.0f; i<360.0f; i+=delta) {
    const float angle = i*cimg::PI/180;
    points.insert(CImg<T>::vector(0.5f*std::cos(angle),0.5f*std::sin(angle),-0.5f));
    primitives.insert(CImg<tf>::vector(0,points.size-2,points.size-1));
    primitives.insert(CImg<tf>::vector(1,points.size-1,points.size-2));
  }
  primitives.insert(CImg<tf>::vector(0,points.size-1,2));
  primitives.insert(CImg<tf>::vector(1,2,points.size-1));
  return points.get_append('x');
}


//! Get a triangulation of a unit cylinder of height 1.
template<typename tf> static CImg cylinder(CImgList<tf>& primitives, const unsigned int subdivisions=16) {
  CImgList<T> points;
  primitives.assign();
  points.insert(CImg<T>::vector(0,0,0.5f));
  points.insert(CImg<T>::vector(0,0,-0.5f));
  points.insert(CImg<T>::vector(0.5f,0,0.5f));
  points.insert(CImg<T>::vector(0.5f,0,-0.5f));
  const float delta = 360.0f/subdivisions;
  for (float i = 0.0f; i<360.0f; i+=delta) {
    const float angle = i*cimg::PI/180;
    points.insert(CImg<T>::vector(0.5f*std::cos(angle),0.5f*std::sin(angle),0.5f));
    points.insert(CImg<T>::vector(0.5f*std::cos(angle),0.5f*std::sin(angle),-0.5f));
    primitives.insert(CImg<tf>::vector(1,points.size-1,points.size-3));
    primitives.insert(CImg<tf>::vector(0,points.size-4,points.size-2));
    primitives.insert(CImg<tf>::vector(points.size-1,points.size-2,points.size-4,points.size-3));
  }
  primitives.insert(CImg<tf>::vector(1,3,points.size-1));
  primitives.insert(CImg<tf>::vector(2,0,points.size-2));
  primitives.insert(CImg<tf>::vector(3,2,points.size-2,points.size-1));
  return points.get_append('x');
}

//! Get a triangulation of a unit torus of mean diameter 1.
template<typename tf> static CImg torus(CImgList<tf>& primitives, const float inner_radius=0.25f,
					const unsigned int subdivisions1=16, const unsigned int subdivisions2=8) {
  CImgList<T> points;
  primitives.assign();

  for (unsigned int v=0; v<subdivisions1; v++)
    for (unsigned int u=0; u<subdivisions2; u++) {
      const float
	alpha = (float)(u*2*cimg::PI/subdivisions2),
	beta = (float)(v*2*cimg::PI/subdivisions1),
	x = (float)((0.5f+inner_radius*std::cos(alpha))*std::cos(beta)),
	y = (float)((0.5f+inner_radius*std::cos(alpha))*std::sin(beta)),
	z = (float)(inner_radius*std::sin(alpha));
      points.insert(CImg<>::vector(x,y,z));
    }

  for (unsigned int vv=0; vv<subdivisions1; vv++)
    for (unsigned int uu=0; uu<subdivisions2; uu++) {
      const int nv = (vv+1)%subdivisions1, nu = (uu+1)%subdivisions2;
      primitives.insert(CImg<unsigned int>::vector(subdivisions2*vv+nu,subdivisions2*vv+uu,subdivisions2*nv+uu));
      primitives.insert(CImg<unsigned int>::vector(subdivisions2*vv+nu,subdivisions2*nv+uu,subdivisions2*nv+nu));
    }

  return points.get_append('x');
}

//! Get a triangulation of a centered sphere of radius 1
template<typename tf> static CImg sphere(CImgList<tf>& primitives, const unsigned int subdivisions=3) {

  // Create initial icosahedron
  CImgList<T> points;
  primitives.assign();
  const T tmp = (T)(1+std::sqrt(5.0f))/2.0f, a = (T)(1.0f/std::sqrt(1+tmp*tmp)), b = tmp*a;
  points.insert(CImg<T>::vector(b,a,0));
  points.insert(CImg<T>::vector(-b,a,0));
  points.insert(CImg<T>::vector(-b,-a,0));
  points.insert(CImg<T>::vector(b,-a,0));
  points.insert(CImg<T>::vector(a,0,b));
  points.insert(CImg<T>::vector(a,0,-b));
  points.insert(CImg<T>::vector(-a,0,-b));
  points.insert(CImg<T>::vector(-a,0,b));
  points.insert(CImg<T>::vector(0,b,a));
  points.insert(CImg<T>::vector(0,-b,a));
  points.insert(CImg<T>::vector(0,-b,-a));
  points.insert(CImg<T>::vector(0,b,-a));
  primitives.insert(CImg<tf>::vector(4,8,7));
  primitives.insert(CImg<tf>::vector(4,7,9));
  primitives.insert(CImg<tf>::vector(5,6,11));
  primitives.insert(CImg<tf>::vector(5,10,6));
  primitives.insert(CImg<tf>::vector(0,4,3));
  primitives.insert(CImg<tf>::vector(0,3,5));
  primitives.insert(CImg<tf>::vector(2,7,1));
  primitives.insert(CImg<tf>::vector(2,1,6));
  primitives.insert(CImg<tf>::vector(8,0,11));
  primitives.insert(CImg<tf>::vector(8,11,1));
  primitives.insert(CImg<tf>::vector(9,10,3));
  primitives.insert(CImg<tf>::vector(9,2,10));
  primitives.insert(CImg<tf>::vector(8,4,0));
  primitives.insert(CImg<tf>::vector(11,0,5));
  primitives.insert(CImg<tf>::vector(4,9,3));
  primitives.insert(CImg<tf>::vector(5,3,10));
  primitives.insert(CImg<tf>::vector(7,8,1));
  primitives.insert(CImg<tf>::vector(6,1,11));
  primitives.insert(CImg<tf>::vector(7,2,9));
  primitives.insert(CImg<tf>::vector(6,10,2));

  // Recurse subdivisions
  for (unsigned int i=0; i<subdivisions; i++) {
    const unsigned int L = primitives.size;
    for (unsigned int l=0; l<L; l++) {
      const unsigned int
	p0 = (unsigned int)primitives(0,0), p1 = (unsigned int)primitives(0,1), p2 = (unsigned int)primitives(0,2),
	N = points.size;
      const float
	x0 = points(p0,0), y0 = points(p0,1), z0 = points(p0,2),
	x1 = points(p1,0), y1 = points(p1,1), z1 = points(p1,2),
	x2 = points(p2,0), y2 = points(p2,1), z2 = points(p2,2),
	nx0 = (x0+x1)/2, ny0 = (y0+y1)/2, nz0 = (z0+z1)/2, nn0 = std::sqrt(nx0*nx0+ny0*ny0+nz0*nz0),
	nx1 = (x0+x2)/2, ny1 = (y0+y2)/2, nz1 = (z0+z2)/2, nn1 = std::sqrt(nx1*nx1+ny1*ny1+nz1*nz1),
	nx2 = (x1+x2)/2, ny2 = (y1+y2)/2, nz2 = (z1+z2)/2, nn2 = std::sqrt(nx2*nx2+ny2*ny2+nz2*nz2);
      points.insert(CImg<>::vector(nx0/nn0,ny0/nn0,nz0/nn0));
      points.insert(CImg<>::vector(nx1/nn1,ny1/nn1,nz1/nn1));
      points.insert(CImg<>::vector(nx2/nn2,ny2/nn2,nz2/nn2));
      primitives.remove(0);
      primitives.insert(CImg<unsigned int>::vector(p0,N,N+1));
      primitives.insert(CImg<unsigned int>::vector(N,p1,N+2));
      primitives.insert(CImg<unsigned int>::vector(N+1,N+2,p2));
      primitives.insert(CImg<unsigned int>::vector(N+1,N,N+2));
    }
  }
  return points.get_append('x');
}

// End of plug-in
#endif

