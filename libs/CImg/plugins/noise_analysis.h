/*-----------------------------------------------------------------------------------------

  File	      : noise_analysis.h

  Description : CImg plugin that estimates noise standard deviation.

  Copyright   : Jerome Boulanger - http://www.irisa.fr/vista/Equipe/People/Jerome.Boulanger.html

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

------------------------------------------------------------------------------------------*/

#ifndef cimg_plugin_noise_analysis
#define cimg_plugin_noise_analysis

//! Estimate the variance of the image using robust method
/*
  \param method = 0 : Least Median of Square,
		  1 : Least Trimmed of Square,
		  2 : Least Mean of Square.
   The variance is the square of the standard deviation.
*/
double variance_estimation(const int method=1){
  CImg<double> buf = (*this);
  int n = size();
  switch(method){
  case 0:{ // Least Median of Squares
    buf.sort();
    double med_i = buf[(int)(.5*(float)n)];
    for (int j=0;j<n;j++)
      buf[j] = fabs(buf[j]-med_i);
    buf.sort();
    double sig = 1.4828 * buf[(int)(.5*(float)n)];
    return sig*sig;
  }
  case 1:{ // Least trimmed of Squares
    for (int k=0;k<n;k++)
      buf[k] = buf[k]*buf[k];
    buf.sort();
    double a=0;
    for (int j=0;j<(int)(.5*n);j++)
      a += buf[j];
    double sig = 2.6477 * std::sqrt(a/(int)(.5*n));
    return sig*sig;
  }
  default:{ // Least mean square
    double a=0, b=0;
    for (int k=0;k<n;k++){
      a += buf[k];
      b += buf[k]*buf[k];
    }
    a /= (double) n;
    b /= (double) n;
    b -= a*a;
    return b;
  }
  }
}


//! Compute somme pseudo-residuals
/*
  The pseudo residual r_i of the image Y_i are so thar E[r_i^2] = E[Y_i^2].
  This is the 2D pseudo-implementation.
*/
CImg <float> get_pseudo_residuals(){
  CImg<float> residu(dimx(),dimy(),dimz(),dim);
  if (!is_empty()){
    cimg_forXYZV(*this,x,y,z,v){
      double t2=0;
      if (x==0) t2 += (*this)(x+1,y,z,v);
      else t2 += (*this)(x-1,y,z,v);
      if ((unsigned int)x==(unsigned int)(dimx()-1)) t2 += (*this)(x-1,y,z,v);
      else t2 +=(*this)(x+1,y,z,v);
      if (y==0) t2 += (*this)(x,y+1,z,v);
      else t2 += (*this)(x,y-1,z,v);
      if ((unsigned int)y==(unsigned int)(dimy()-1)) t2 += (*this)(x,y-1,z,v);
      else t2 += (*this)(x,y+1,z,v);
      residu(x,y,z,v)=(float)
	(0.223606798*(4.*(double)(*this)(x,y,z,v)-t2));
    }
  }
  return residu;
}


//! Estimate the noise variance
/*
  \param method = 0 : Least Median of Square,
		  1 : Least Trimmed of Square,
		  2 : Least Mean of Square.
   Robustly estimatate the variance of a the noise using the pseudo-residuals.
   \see variance_estimation()
*/
double noise_variance(const int method=0){
  return (*this).get_pseudo_residuals().variance_estimation(method);
}

#endif
