/*****************************************************************
 * cimgmatlab.h
 * -------------
 *
 * cimgmatlab.h is a "plugin" for the CImg library that allows
 * to convert CImg<T> images from/to matlab arrays, so that CImg
 * can be used to write matlab mex files.
 * How to use it:
 * file cimgmatlab.h must be in a directory that the
 * compiler can locate.
 * Prior to include CImg.h, mex.h must be included first, else it
 * will result in a compiler error.
 * after the inclusion of mex.h, one must define the macro
 * cimg_plugin as "cimgmatlab.h" or <cimgmatlab.h> or similar
 *
 * // my fantastic mex file source code
 * #include <mex.h>
 * ...
 * #define cimg_plugin	<cimgmatlab.h>
 * #include <CImg.h>
 * ...
 *
 *
 * Copyright: Francois Lauze, The IT University of Copenhagen.
 * Licence: the Gnu General Public License
 *	    http://www.gnu.org/copyleft/gpl.html
 *
 *****************************************************************/


#if !defined mex_h
#error the file mex.h must be included!
#endif

#if !defined cimg_version
#error cimgmatlab.h requires that CImg.h is included
#endif




// begin of included methods
// They are just added as member functions / constructor
// for the CImg<T> class.


 private:
    // internally used to transfer Matlab array values to CImg<> objects,
    // check wether the array type is a "numerical" one (including logical)
    static int isNumericalClassID(mxClassID id) {
		// all these constants are defined in matrix.h included by mex.h
	switch (id) {
	case mxLOGICAL_CLASS:
	case mxDOUBLE_CLASS:
	case mxSINGLE_CLASS:
	case mxINT8_CLASS:
	case mxUINT8_CLASS:
	case mxINT16_CLASS:
	case mxUINT16_CLASS:
	case mxINT32_CLASS:
	case mxUINT32_CLASS:
	case mxINT64_CLASS:
	case mxUINT64_CLASS:
	    return 1;
	default:
	    return 0;
	}
    }


    // driving routine that will copy the content of
    // a MatLab array to this->data
    // The type names used are defined in tmwtypes.h
    void makeImageFromMatlabData(const mxArray *matlabArray, mxClassID classID) {
	if (classID == mxLOGICAL_CLASS) {
	    // logical type works a bit differently than the numerical types
	    mxLogical *mdata = mxGetLogicals(matlabArray);
	    cpMatlabData((const mxLogical *)mdata);
	} else {
	    void *mdata = mxGetPr(matlabArray);
	    switch (classID) {
	    case mxDOUBLE_CLASS:
		cpMatlabData((const real64_T *)mdata);
		break;
	    case mxSINGLE_CLASS:
		cpMatlabData((const real32_T *)mdata);
		break;
	    case mxINT8_CLASS:
		cpMatlabData((const int8_T *)mdata);
		break;
	    case mxUINT8_CLASS:
		cpMatlabData((const uint8_T *)mdata);
		break;
	    case mxINT16_CLASS:
		cpMatlabData((const int16_T *)mdata);
		break;
	    case mxUINT16_CLASS:
		cpMatlabData((const uint16_T *)mdata);
		break;
	    case mxINT32_CLASS:
		cpMatlabData((const int32_T *)mdata);
		break;
	    case mxUINT32_CLASS:
		cpMatlabData((const uint32_T *)mdata);
		break;
	    case mxINT64_CLASS:
		cpMatlabData((const int64_T *)mdata);
		break;
	    case mxUINT64_CLASS:
		cpMatlabData((const uint64_T *)mdata);
		break;
	    }
	}
    }

    // the actual memory copy and base type conversion
    // is then performed by this routine that handles the
    // annoying x-y problem of MatLab when dealing with images:
    // we switch line and column storage: Matlab A(x,y)
    // becones CImg img(y,x)
    template <typename t> void cpMatlabData(const t* mdata) {
	cimg_mapXYZV(*this, x, y, z, v) {
	    (*this)(x, y, z, v) = (T)(mdata[((v*depth + z)*width+x)*height+y]);
	}
    }

public:

    // Consruct a CImg<T> object from a MatLab mxArray.
    // The Matlab array must be AT MOST 4-dimensional.
    // the boolean argument vdata is employed in the
    // case the the input mxArray has dimension 3,
    // say M x N x K.
    // In that case, if vdata is true, the last dimension
    // is assumed to be "vectorial" and the resulting CImg<T>
    // object has dimension N x M x 1 x K. Otherwise, the
    // resulting object has dimension N x M x K x 1.
    // When Matlab array has dimension 2 or 4, vdata
    // has no effects.	// We do not use shared memory mechanisms.
	CImg(const mxArray *matlabArray, bool vdata = false) : is_shared(false) {
	int nbdims = mxGetNumberOfDimensions(matlabArray);
	mxClassID classID = mxGetClassID(matlabArray);
	if (nbdims > 4 || !isNumericalClassID(classID)) {
	    data=NULL; width=height=depth=dim=0;
#if cimg_debug>1
	    cimg::warn(1,"Matlab array is more than 4D"
		       " or/and not numerical, returning null image.");
#endif
	} else {
	    const mwSize *dims = mxGetDimensions(matlabArray);
	    depth = dim = 1;
	    width = (unsigned int)dims[1]; height = (unsigned int)dims[0];
	    if (nbdims == 4) {
		depth = (unsigned int)dims[2];
		dim = (unsigned int)dims[3];
	    } else if (nbdims == 3) {
		if (vdata) dim = (unsigned int)dims[2];
		else depth = (unsigned int)dims[2];
	    }
	    data = new T[size()];
	    makeImageFromMatlabData(matlabArray, classID);
	}
    }



    // operator=(). Copy  mxMarray data mArray into the current image
    // Works as the previous constructor, but without the vdata stuff.
    // don't know if it is of any use...
    CImg & operator=(const mxArray *matlabArray) {
	int nbdims = mxGetNumberOfDimensions(matlabArray);
	int classID = mxGetClassID(matlabArray);
	if (nbdims > 4 || !isNumericalClassID(classID)) {
	    delete [] data; data = NULL; width=height=depth=dim=0;
#if cimg_debug>1
	    cimg::warn(1,"Matlab array is more than 4D "
		       "or/and not numerical, returning null image.");
#endif
	} else {
	    const size_t *dims = mxGetDimensions(matlabArray);
	    depth = dim = 1;
	    width = (unsigned int)dims[1]; height = (unsigned int)dims[0];
	    if (nbdims > 2) depth = (unsigned int)dims[2];
	    if (nbdims > 3) dim = (unsigned int)dims[3];
	    delete [] data;
	    data = new T[size()];
	    makeImageFromMatlabData(matlabArray, classID);
	}
    }

 private:
    // private routines used for transfering a CImg<T> to a mxArray
    // here also, we have to exchange the x and y dims so we get the
    // expected matlab array
    template <typename c>
	void populate_maltlab_array(c *mdata) const {
	cimg_mapXYZV(*this, x, y, z, v)
	    mdata[((v*depth + z)*width+x)*height+y] = (c)(*this)(x, y, z, v);
    }
    // the specialized version for "logical" entries
    void populate_maltlab_array(mxLogical *mdata) const {
	cimg_mapXYZV(*this, x, y, z, v)
	    mdata[((v*depth + z)*width+x)*height+y] = (mxLogical)((*this)(x, y, z, v)!=0);
    }


 public:
    // export a CImg image to a matlab array.
    mxArray *toMatlab(mxClassID classID = mxDOUBLE_CLASS, bool squeeze = false) const {
	if (!isNumericalClassID(classID)) {
#if cimg_debug>1
	    cimg::warn(1,"Invalid Matlab Class Id Specified.");
#endif
	    return NULL;
	}
	mwSize dims[4];
	dims[0] = height;
	dims[1] = width;
	dims[2] = depth;
	dims[3] = dim;
	if (squeeze && depth == 1) {
	    dims[2] = dim;
	    dims[3] = 1;
	}
	mxArray *matlabArray = mxCreateNumericArray(4,dims,classID,mxREAL);
	if (classID == mxLOGICAL_CLASS) {
	    mxLogical *mdata = mxGetLogicals(matlabArray);
	    populate_maltlab_array(mdata);
	} else {
	    void *mdata = mxGetPr(matlabArray);
	    switch (classID) {
	    case mxDOUBLE_CLASS:
		populate_maltlab_array((real64_T *)mdata);
		break;
	    case mxSINGLE_CLASS:
		populate_maltlab_array((real32_T *)mdata);
		break;
	    case mxINT8_CLASS:
		populate_maltlab_array((int8_T *)mdata);
		break;
	    case mxUINT8_CLASS:
		populate_maltlab_array((uint8_T *)mdata);
		break;
	    case mxINT16_CLASS:
		populate_maltlab_array((int16_T *)mdata);
		break;
	    case mxUINT16_CLASS:
		populate_maltlab_array((uint16_T *)mdata);
		break;
	    case mxINT32_CLASS:
		populate_maltlab_array((int32_T *)mdata);
		break;
	    case mxUINT32_CLASS:
		populate_maltlab_array((uint32_T *)mdata);
		break;
			case mxINT64_CLASS:
		populate_maltlab_array((int64_T *)mdata);
		break;
			case mxUINT64_CLASS:
		populate_maltlab_array((uint64_T *)mdata);
		break;
	    }
	}
	return matlabArray;
    }

// end of cimgmatlab.h
