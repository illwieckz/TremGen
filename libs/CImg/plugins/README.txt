-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

    ____ ___                   ____  _                       ___
   / ___|_ _|_ __ ___   __ _  |  _ \| |_   _  __ _          |_ _|_ __  ___
  | |    | || '_ ` _ \ / _` | | |_) | | | | |/ _` |  _____   | || '_ \/ __|
  | |___ | || | | | | | (_| | |  __/| | |_| | (_| | |_____|  | || | | \__ \
   \____|___|_| |_| |_|\__, | |_|   |_|\__,_|\__, |         |___|_| |_|___/
                       |___/                 |___/


                         Description of CImg Plug-Ins

-------------------------------------------------------------------------------

*******************************************************************************

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

                            -- Integral Line --

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

# Files
#-------

  - plugins/integral_line.h

# Description
#-------------

  Implementation of functions that retrieve integral lines from vector fields
  using different types of interpolation.

# Author
#--------

  David Tschumperle (http://www.greyc.ensicaen.fr/~dtschump/)

# Institutions
#-------------

 IMAGE Team / GREYC (CNRS UMR 6072), Caen / FRANCE
 Home page of the team :  http://www.greyc.ensicaen.fr/EquipeImage/

# Date
#-----

 March 2007.

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

*******************************************************************************

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

                            -- Primitives3D --

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

# Files
#-------

  - plugins/primitives3d.h

# Description
#-------------

  Implementation of several functions that create triangulations of classical
  3D shapes, such as spheres, cubes, pyramids, and so on...

# Author
#--------

  David Tschumperle (http://www.greyc.ensicaen.fr/~dtschump/)

# Institutions
#-------------

 IMAGE Team / GREYC (CNRS UMR 6072), Caen / FRANCE
 Home page of the team :  http://www.greyc.ensicaen.fr/EquipeImage/

# Date
#-----

  July 2006.

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

*******************************************************************************

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

                     -- GREYCstoration4Integration --

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

# Files
#-------

  - plugins/greycstoration4integration.h
  - examples/greycstoration4integration.cpp

# Description
#-------------

  Implementation of the GREYCstoration algorithm for image denoising.
  This version is adapted for an easy integration in third parties
  software, since it is non-blocking and returns a progression indice
  that can be used in progress bars.

# References
#------------

  [1] Fast Anisotropic Smoothing of Multi-Valued Images using
      Curvature-Preserving PDE's. (D. Tschumperle).
      GREYC, CNRS UMR 6072, Equipe Image, 6 Bd du Marechal Juin,
      14050 Caen Cedex.

# Author
#--------

  David Tschumperle (http://www.greyc.ensicaen.fr/~dtschump/)

# Institutions
#-------------

 IMAGE Team / GREYC (CNRS UMR 6072), Caen / FRANCE
 Home page of the team :  http://www.greyc.ensicaen.fr/EquipeImage/

# Date
#-----

  May 2006.

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

*******************************************************************************

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

                     -- NL Means and Noise Analysis --

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

# Files
#-------

  - plugins/nlmeans.h
  - plugins/noise_analysis.h
  - examples/nlmeans.cpp

# Description
#-------------

  Non-Local Means algorithm

  Implementation of the Non-Local Means algorithm as described in [1] and [2].
  The variance of the noise can be automatically estimated using the method
  inspired from [3].

# References
#------------

  [1] Buades, A.; Coll, B.; Morel, J.-M.: A non-local algorithm for image
      denoising. IEEE Computer Society Conference on Computer Vision and Pattern
      Recognition, 2005. CVPR 2005. Vol 2,  20-25 June 2005 Page(s):60 - 65

  [2] Buades, A. Coll, B. and Morel, J.: A review of image denoising algorithms,
      with a new one. Multiscale Modeling and Simulation: A SIAM
      Interdisciplinary Journal 4 (2004) 490-530

  [3] Gasser, T. Sroka,L. Jennen Steinmetz,C. Residual variance and residual
      pattern nonlinear regression. Biometrika 73 (1986) 625-659

# Author
#--------

  Jérôme Boulanger (http://www.irisa.fr/vista/Equipe/People/Jerome.Boulanger.html)

  with

  - Charles Kervrann
  - Patrick Bouthemy

  thanks to

  ACI IMPBio (MODYNCELL5D Project)

# Institutions
#-------------

 VISTA / IRISA-INRIA, Rennes / FRANCE
 Home page of the team :  http://www.irisa.fr/vista/

 and

 MIA / INRA, Unité de Jouy-en-Josas / FRANCE

# Date
#-----

  May 2006.

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

*******************************************************************************

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

                     -- Plug in for Matlab mex files  --

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

# Files
#-------

  - plugins/cimgmatlab.h
  - examples/cannyderiche.cpp
  - examples/cannyderiche.m

# Description
#-------------

  Implement a CImg<T> constructor from a matlab array, a CImg<T> assignment
  operator from a matlab array and a method that exports a CImg<T> object to
  a Matlab array.

  For a bit more, http://www.itu.dk/people/francois/cimgmatlab.html

# References
#------------

  Well,... Matlab documentations and the header files provided with Matlab!

# Author
#--------

  François Lauze (http://www.itu.dk/people/francois/index.html)


# Institution
#-------------

The IT University of Copenhagen, Image Group.

# Date
#------

 May 2006.

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

*******************************************************************************

