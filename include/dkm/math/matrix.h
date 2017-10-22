/**
 * matrix.h
 *
 * Contains template classes for working with matrices and vectors.
 */

#ifndef _DKM_MATRIX_H_
#define _DKM_MATRIX_H_

#include <cmath>

#include <string>
#include <sstream>

// darkma773r namespace
namespace dkm {

/**
Namespace containing commonly used matrix and vector operations.
Unless otherwise noted, all functions in this namespace operate
at an element level, meaning that any size parameter refers to
the number of elements and not the number of bytes used to
represent those elements. For consistency, any function that
writes data to an external array returns the number of elements
written to that array.
*/
namespace MatrixUtil {
 
/**
Copies size elements from src to dest. Returns the number
of elements written to dest.
*/
template<typename T>
size_t copy(const T* src, T* dest, size_t size) {
    for (int i=0; i<size; ++i) {
        dest[i] = src[i];
    }
    return size;
}

/**
Sets size number of elements in dest to val. Returns the number
of elements written to dest.
*/
template<typename T>
size_t set(T* dest, T val, size_t size) {
    for (int i=0; i<size; ++i) {
        dest[i] = val;
    }
    return size;
}

/**
Adds size number of elements from A and B together and places
the results dest. Returns the number of elements written to dest.
*/
template<typename T>
size_t add(const T* a, const T* b, T* dest, size_t size) {
    for (int i=0; i<size; ++i) {
        dest[i] = a[i] + b[i];
    }
    return size;
}

/**
Subtracts size number of elements of B from A and places the
results in dest. Returns the number of elements written to
dest.
*/
template<typename T>
size_t subtract(const T* a, const T* b, T* dest, size_t size) {
    for (int i=0; i<size; ++i) {
        dest[i] = a[i] - b[i];
    }
    return size;
}

/**
Multiplies size number of elements in A by val and places the
results in dest. Returns the number of elements written to dest.
*/
template<typename T>
size_t scalarMultiply(const T* a, T val, T* dest, size_t size) {
    for (int i=0; i<size; ++i) {
        dest[i] = a[i] * val;
    }
    return size;
}

/**
Treats the src array as a matrix with rows number of rows and cols
number of columns and writes the transposed matrix to dest. The dest
array will then contain a matrix with cols number of rows and rows
number of columns. The caller is responsible for making sure that dest
is large enough to contain at least rows*cols number of elements. The function
returns the number of elements written to dest, which is equal to rows*cols.
*/
template<typename T>
size_t transpose(const T* src, size_t rows, size_t cols, T* dest) {
    for (int i=0; i<rows; ++i) {
        for (int j=0; j<cols; ++j) {
            dest[j*rows + i] = src[i*cols + j];
        }
    }
    return rows * cols;
}

/**
Multiplies two matrices represented as arrays. The number of
rows for the B matrix is understood to be equal to the
number of columns of the A matrix. The dimensions of the output
matrix is equal to aRows x bCols. The caller is responsible
for ensuring that the out array is large enough to contain the
result of the multiplication operation, meaning it must be
able to contain at least aRows*bCols elements. The function returns the number
of elements written to the out array, which is aRows*bCols in
normal situations but will be zero if any of the given matrix
dimensions are invalid (i.e. less than 1).
*/
template<typename T>
size_t matrixMultiply(const T* a, size_t aRows, size_t aCols,
                      const T* b, size_t bCols,
                      T* out) {
    if (aRows < 1 || aCols < 1 || bCols < 1) {
        return 0; // invalid dimensions
    }

    for (int i=0; i<aRows; ++i) {
        for (int j=0; j<bCols; ++j) {
            T val = static_cast<T>(0);
            for (int m=0; m<aCols; ++m) {
                val = val + a[i*aCols + m] * b[m*bCols + j];
            }
            out[i*bCols + j] = val;
        }
    }
    return aRows * bCols;
}

/**
Creates an identity matrix in dest of size dimension x dimension.
Returns the number of elements written into dest.  
*/
template<typename T>
size_t identity(size_t dimension, T* dest){
	for (int i=0; i<dimension; i++){
		for (int j=0; j<dimension; j++){
			dest[(i*dimension) + j] = (i == j)? static_cast<T>(1) : static_cast<T>(0);
		}
	}
	return dimension * dimension;
}

/**
Returns the magnitude of the vector in the vec array with size number of
elements.
*/
template<typename T>
double vectorMagnitude(const T* vec, size_t size) {
    double mag = 0.0;
    for (int i=0; i<size; ++i) {
        mag = mag + (vec[i] * vec[i]);
    }
    return sqrt(mag);
}

/**
Returns true if the given vector is normalized with the given
epsilon range.
*/
template<typename T>
bool isVectorNormalized(const T* vec, size_t size, double epsilon) {
    T total = static_cast<T>(0);
    for (int i=0; i<size; i++) {
        total = total + (vec[i] * vec[i]);
    }
    return std::abs(1.0 - total) < epsilon;
}

/**
The default value to use when calling isVectorNormalized
*/
const double DEFAULT_NORMALIZED_EPSILON = 1e-6;

/**
Returns true if the given vector is normalized within the
DefaultNormalizedDelta range.
*/
template<typename T>
bool isVectorNormalized(const T* vec, size_t size) {
    return isVectorNormalized(vec, size, DEFAULT_NORMALIZED_EPSILON);
}

/**
Normalizes the vector with size number of elements found in
the src array and places the results in dest. Returns the
number of elements written to dest. If the vector cannot be
normalized (i.e., it's magnitude is zero), zero is returned.
*/
template<typename T>
size_t vectorNormalize(const T* src, size_t size, T* dest) {
    double mag = vectorMagnitude(src, size);
    if (mag > 0.0) {
        for (int i=0; i<size; ++i) {
            dest[i] = src[i] / mag;
        }
        return size;
    }
    return 0;
}

/**
Returns the dot product of the vectors with size elements
found in arrays A and B.
*/
template<typename T>
double vectorDotProduct(const T* a, const T* b, size_t size) {
    double dot = 0.0;
    for (int i=0; i<size; ++i) {
        dot = dot + (a[i] * b[i]);
    }
    return dot;
}

/**
Calculates the cross product of the vectors with 3 elements
found in the arrays A and B and places the result in dest.
Since the cross product is only defined on vectors with 3 elements,
this method accepts no size parameter. Retuns the number of
elements written to dest, which will always be 3.
*/
template<typename T>
size_t vectorCrossProduct(const T* a, const T* b, T* dest) {
    dest[0] = a[1]*b[2] - a[2]*b[1];
    dest[1] = a[2]*b[0] - a[0]*b[2];
    dest[2] = a[0]*b[1] - a[1]*b[0];

    return 3;
}

/**
Returns a string representation of a matrix with rows number of rows
and cols number of columns from the src array.
*/
template<typename T>
std::string toString(const T* src, size_t rows, size_t cols) {
    int size = rows * cols;

    std::stringstream ss;
    ss << std::fixed;
    ss.precision(2);

    ss << "[";

    for (int i=0; i<size; ++i) {
        if (i > 0 && i % cols == 0) {
            ss << "\n ";
        }
        ss << " " << src[i];
        if (i < size - 1) {
            ss << ",";
        }
    }
    ss << " ]";

    return ss.str();
}

} // end namespace MatrixUtil

/**
Base type for classes that contain an internal array of elements.
Since all data is kept in the internal array, the default copy
constructor and assignment operators are used where possible.
The template uses the "Curiously Recurring Template Pattern", aka
CRTP (see http://en.wikipedia.org/wiki/Curiously_recurring_template_pattern)
*/
template<unsigned int SizeArg, typename T, typename DerivedType>
class _ElementArrayBase {

    typedef _ElementArrayBase<SizeArg, T, DerivedType> ThisType;

protected:
    // internal data array
    T mData[SizeArg];

    /**
    Protected constructor for use in derived classes. If
    elements is NULL, every element in the internal array
    is set to the zero representation of type T. Otherwise,
    the data from elements is copied into the internal array.
    */
    _ElementArrayBase(const T* elements = NULL) {
        if (elements != NULL) {
            MatrixUtil::copy(elements, mData, SizeArg);
        } else {
            MatrixUtil::set(mData, static_cast<T>(0), SizeArg);
        }
    }

public:
    virtual ~_ElementArrayBase() { }

    /**
    Returns a pointer to the internal element array.
    */
    T* data() {
        return mData;
    }
    const T* data() const {
        return mData;
    }

    /**
    Returns the size of the internal array.
    */
    size_t size() const {
        return SizeArg;
    }

    /**
    Copies the entirety of the internal array to dest. The caller is responsible
    for making sure that dest is large enough to contain the copied data.
    */
    void copyTo(T* dest) const {
        MatrixUtil::copy(mData, dest, SizeArg);
    }

    /**
    Copies data from src into the internal array.
    */
    void copyFrom(const T* src) {
        MatrixUtil::copy(src, mData, SizeArg);
    }

    /**
    Same as add() but assigns the answer to the caller. This can be used to 
    avoid unneccessary copying of array data.
    */
    void addAssign(const DerivedType &other) {
        MatrixUtil::add(mData, other.mData, mData, SizeArg);
    }
    /**
    Adds the elements from the argument and the caller and returns a new object
    with the results.
    */
    DerivedType add(const DerivedType &other) const {
        DerivedType result(mData);
        MatrixUtil::add(mData, other.mData, result.data(), SizeArg);
        return result;
    }
    /**
    Alias for add()
    */
    DerivedType operator+(const DerivedType &other) const {
        return add(other);
    }
    /**
    Alias for addAssign()
    */
    DerivedType& operator+=(const DerivedType &other) {
        addAssign(other);
        return *static_cast<DerivedType*>(this);
    }

    /**
    Same as subtract() but assigns the answer to the caller. This can be used to 
    avoid unneccessary copying of array data.
    */
    void subtractAssign(const DerivedType &other) {
        MatrixUtil::subtract(mData, other.mData, mData, SizeArg);
    }
    /**
    Adds the elements of the argument from the caller and returns a new element-based object
    with the results.
    */
    DerivedType subtract(const DerivedType &other) const {
        DerivedType result(mData);
        MatrixUtil::subtract(mData, other.mData, result.mData, SizeArg);
        return result;
    }
    /**
    Alias for Subtract()
    */
    DerivedType operator-(const DerivedType &other) const {
        return subtract(other);
    }
    /**
    Alias for subtractAssign()
    */
    DerivedType& operator-=(const DerivedType &other) {
        subtractAssign(other);
        return *static_cast<DerivedType*>(this);
    }

    /**
    Same as scalarMultiply() but assigns the answer to the caller. This can be 
    used to avoid unneccessary copying of array data.
    */
    void scalarMultiplyAssign(T val) {
        MatrixUtil::scalarMultiply(mData, val, mData, SizeArg);
    }
    /**
    Multiplies every element of the internal array by val and returns a new element-based object
    with the results.
    */
    DerivedType scalarMultiply(T val) const {
        DerivedType result(mData);
        MatrixUtil::scalarMultiply(mData, val, result.mData, SizeArg);
        return result;
    }
    /**
    Alias for scalarMultiply()
    */
    DerivedType operator*(T val) const {
        return scalarMultiply(val);
    }
    /**
    Alias for scalarMultiplyAssign()
    */
    DerivedType& operator*=(T val) {
        scalarMultiplyAssign(val);
        return *static_cast<DerivedType*>(this);
    }
};

// forward-declare Vector class
template<unsigned int SizeArg, typename T = double>
class Vector;

// Template class representing a RowsArg x ColsArg matrix of type T.
template<unsigned int RowsArg, unsigned int ColsArg, typename T = double>
class Matrix : public _ElementArrayBase<RowsArg * ColsArg, T, Matrix<RowsArg, ColsArg, T> > {

    typedef Matrix<RowsArg, ColsArg, T> ThisType;
    typedef _ElementArrayBase<RowsArg * ColsArg, T, ThisType> SuperType;

public:
    Matrix(const T* elements = NULL) : SuperType(elements) { }

    virtual ~Matrix() { }

    /**
    Returns the number of rows in this Matrix.
    */
    size_t rows() const {
        return RowsArg;
    }

    /**
    Returns the number of columns in this Matrix.
    */
    size_t cols() const {
        return ColsArg;
    }

    /**
    Returns a new Matrix representing the transposition of the calling Matrix.
    */
    Matrix<ColsArg, RowsArg, T> transpose() const {
        Matrix<ColsArg, RowsArg, T> result;
        MatrixUtil::transpose(this->mData, RowsArg, ColsArg, result.data());
        return result;
    }

    /**
    Same as Matrix version of Multiply() but assigns the answer to the caller. This is useful in 
    order to avoid unneccessary copying of array data. This function only accepts square matrices 
    with the same number of columns as the caller. Otherwise, the resulting Matrix size would be 
    incompatible with the caller.
    */
    void multiplyAssign(const Matrix<ColsArg, ColsArg, T>& other) {
        T temp[RowsArg*ColsArg];
        MatrixUtil::matrixMultiply(this->mData, RowsArg, ColsArg,
                                   other.data(), ColsArg,
                                   temp);
        MatrixUtil::copy(temp, this->mData, RowsArg*ColsArg);
    }
    /**
    Multiplies the calling Matrix with the argument and returns a new Matrix with the result.
    Matrix multiplication is only defined where the second matrix has the same number of
    rows as the first matrix.
    */
    template<unsigned int OtherColsArg>
    Matrix<RowsArg, OtherColsArg, T> multiply(const Matrix<ColsArg, OtherColsArg, T> &other) const {
        Matrix<RowsArg, OtherColsArg, T> result;
        MatrixUtil::matrixMultiply(this->mData, RowsArg, ColsArg,
                                   other.data(), OtherColsArg,
                                   result.data());
        return result;
    }

    /**
    Treats the given vector as a column matrix and performs a matrix multiplication.
    */
    Vector<RowsArg, T> transformVector(const Vector<ColsArg, T>& other) {
        Vector<RowsArg, T> result;
        MatrixUtil::matrixMultiply(this->mData, RowsArg, ColsArg,
                                   other.data(), 1,
                                   result.data());
        return result;
    }

    // make sure the multiplication operator from the base class is still visible
    using SuperType::operator*;

    /**
    Alias for the Matrix version of Multiply()
    */
    template<unsigned int OtherColsArg>
    Matrix<RowsArg, OtherColsArg, T> operator*(const Matrix<ColsArg, OtherColsArg, T> &rh) {
        return multiply(rh);
    }

    // make sure the multiplication equals operator from the base class is still visible
    using SuperType::operator*=;

    /**
    Alias for the Matrix version of multiplyAssign()
    */
    ThisType& operator*=(const Matrix<ColsArg, ColsArg, T>& other) {
        multiplyAssign(other);
        return *this;
    }

    /**
    Array index operator allowing the Matrix to be used directly as a 2 dimensional array.
    Callers are resposible for staying within the bounds of the array.
    */
    T* operator[](size_t rowIdx) {
        return this->mData + (rowIdx * ColsArg);
    }
    const T* operator[](size_t rowIdx) const {
        return this->mData + (rowIdx * ColsArg);
    }

    /**
    Returns a string representation of the Matrix.
    */
    std::string toString() const {
        return MatrixUtil::toString(this->mData, RowsArg, ColsArg);
    }

    /**
    Returns a matrix I that when multiplied by a matrix A of this type
    returns the same matrix, i.e. A*I = A. The returned matrix has dimensions
    ColsArg x ColsArg. 
    */
    static Matrix<ColsArg, ColsArg, T> identity(){
	    Matrix<ColsArg, ColsArg, T> result;
	    MatrixUtil::identity(ColsArg, result.data());
	    return result;
    }
};

/**
Global function allowing scalar multiplication to occur when the scalar comes
before the Matrix.
*/
template<unsigned int RowsArg, unsigned int ColsArg, typename T>
Matrix<RowsArg, ColsArg, T> operator*(T scalar, const Matrix<RowsArg, ColsArg, T> &mat) {
    return mat * scalar;
}

/**
Base class for different vector types, allowing reuse of common vector code.
*/
template<unsigned int SizeArg, typename T, typename DerivedType>
class _VectorBase : public _ElementArrayBase<SizeArg, T, DerivedType> {

    typedef _VectorBase<SizeArg, T, DerivedType> ThisType;
    typedef _ElementArrayBase<SizeArg, T, DerivedType> SuperType;

public:
    _VectorBase(const T* elements = NULL) : SuperType(elements) { }

    virtual ~_VectorBase() { }

    /**
    Returns the magnitude of the Vector as a double.
    */
    double magnitude() const {
        return MatrixUtil::vectorMagnitude(this->mData, SizeArg);
    }

    /**
    Returns true if this Vector is normalized within the MatrixUtil::DefaultNormalizedDelta range.
    */
    bool isNormalized() const {
        return MatrixUtil::isVectorNormalized(this->mData, SizeArg);
    }

    /**
    Returns true if this Vector is normalized within the given delta range.
    */
    bool isNormalized(double delta) const {
        return MatrixUtil::isVectorNormalized(this->mData, SizeArg, delta);
    }

    /**
    Normalizes the calling vector. The vector will have the same direction as
    before but with a magnitude of 1. Returns false if normalization failed,
    (i.e., the Vector had a magnitude of 0). Otherwise, returns true.
    */
    bool normalize() {
        return MatrixUtil::vectorNormalize(this->mData, SizeArg, this->mData) != 0;
    }

    /**
    Returns the dot product of this vector and the calling vector. The dot product has the following
    properties:
    if positive => the angle between the two vectors is less than 90 degrees
    if negative => the angle between the two vectors is more than 90 degrees
    if zero => the two vectors are perpendicular
    */
    double dot(const ThisType& other) const {
        return MatrixUtil::vectorDotProduct(this->mData, other.mData, SizeArg);
    }

    /**
    Array index operator, allowing the Vector to be treated as a single-dimensional array.
    Callers are responsible for making sure they do not exceed the length of the array.
    */
    T& operator[](int idx) {
        return this->mData[idx];
    }
    const T operator[](int idx) const {
        return this->mData[idx];
    }

    /**
    Returns a string representation of the Vector.
    */
    std::string toString() const {
        return MatrixUtil::toString(this->mData, 1, SizeArg);
    }
};

// Primary vector template.
template<unsigned int SizeArg, typename T>
class Vector : public _VectorBase<SizeArg, T, Vector<SizeArg, T> > {

    typedef _VectorBase<SizeArg, T, Vector<SizeArg, T> > SuperType;

public:
    Vector(const T* elements = NULL) : SuperType(elements) { }

    virtual ~Vector() { }
};

// Global function allowing scalar Vector multiplication to occur when
// the scalar comes before the Vector.
template<unsigned int SizeArg, typename T>
Vector<SizeArg, T> operator*(T scalar, const Vector<SizeArg, T> &vec) {
    return vec * scalar;
}

// Vector specialization with size 2.
template<typename T>
class Vector<2, T> : public _VectorBase<2, T, Vector<2, T> > {

    typedef Vector<2, T> ThisType;
    typedef _VectorBase<2, T, ThisType> SuperType;

public:
    // Alias for element 0 in the internal array
    T& x;
    // Alias for element 1 in the internal array
    T& y;

    Vector(const T* elements = NULL) :
        SuperType(elements),
        x(this->mData[0]),
        y(this->mData[1]) { }

    Vector(T xValue, T yValue) :
        SuperType(),
        x(this->mData[0]),
        y(this->mData[1]) {

        this->x = xValue;
        this->y = yValue;
    }

    // We need to override the default copy constructor
    // since we have internal reference elements.
    Vector(const ThisType& other) :
        SuperType(other.mData),
        x(this->mData[0]),
        y(this->mData[1]) { }

    virtual ~Vector() { }

    // We need to override the default assignment operator
    // since we have internal reference elements.
    ThisType& operator=(const ThisType& other) {
        MatrixUtil::copy(other.mData, this->mData, 2);
        return *this;
    }

    // Returns a unit vector representing the X axis.
    static ThisType xAxis() {
        return ThisType(static_cast<T>(1), static_cast<T>(0));
    }

    // Returns a unit vector representing the Y axis.
    static ThisType yAxis() {
        return ThisType(static_cast<T>(0), static_cast<T>(1));
    }
};


// Vector specialization with 3 elements.
template<typename T>
class Vector<3, T> : public _VectorBase<3, T, Vector<3, T> > {

    typedef Vector<3, T> ThisType;
    typedef _VectorBase<3, T, ThisType> SuperType;

public:
    // Alias for element 0 in the internal array
    T& x;

    // Alias for element 1 in the internal array
    T& y;

    // Alias for element 2 in the internal array
    T& z;

    Vector(const T* elements = NULL) :
        SuperType(elements),
        x(this->mData[0]),
        y(this->mData[1]),
        z(this->mData[2]) { }

    Vector(T xValue, T yValue, T zValue) :
        SuperType(),
        x(this->mData[0]),
        y(this->mData[1]),
        z(this->mData[2]) {

        this->x = xValue;
        this->y = yValue;
        this->z = zValue;
    }

    // We need to override the default copy constructor
    // since we have internal reference elements.
    Vector(const ThisType& other) :
        SuperType(other.mData),
        x(this->mData[0]),
        y(this->mData[1]),
        z(this->mData[2]) { }

    virtual ~Vector() { }

    ThisType cross(const ThisType& other) const {
        ThisType result;
        MatrixUtil::vectorCrossProduct(this->mData, other.mData, result.data());
        return result;
    }

    // We need to override the default assignment operator
    // since we have internal reference elements.
    ThisType& operator=(const ThisType& other) {
        MatrixUtil::copy(other.mData, this->mData, 3);
        return *this;
    }

    // Returns a unit vector representing the X axis.
    static ThisType xAxis() {
        return ThisType(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));
    }

    // Returns a unit vector representing the Y axis.
    static ThisType yAxis() {
        return ThisType(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));
    }

    // Returns a unit vector representing the Z axis.
    static ThisType zAxis() {
        return ThisType(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
    }
};


// Vector specialization with 4 elements.
template<typename T>
class Vector<4, T> : public _VectorBase<4, T, Vector<4, T> > {

    typedef Vector<4, T> ThisType;
    typedef _VectorBase<4, T, ThisType > SuperType;

public:
    // Alias for element 0 in the internal array
    T& x;
    // Alias for element 1 in the internal array
    T& y;
    // Alias for element 2 in the internal array
    T& z;
    // Alias for element 3 in the internal array
    T& w;

    Vector(const T* elements = NULL) :
        SuperType(elements),
        x(this->mData[0]),
        y(this->mData[1]),
        z(this->mData[2]),
        w(this->mData[3]) { }

    Vector(T xValue, T yValue, T zValue, T wValue) :
        SuperType(),
        x(this->mData[0]),
        y(this->mData[1]),
        z(this->mData[2]),
        w(this->mData[3]) {

        this->x = xValue;
        this->y = yValue;
        this->z = zValue;
        this->w = wValue;
    }

    // We need to override the default copy constructor
    // since we have internal reference elements.
    Vector(const ThisType& other) :
        SuperType(other.mData),
        x(this->mData[0]),
        y(this->mData[1]),
        z(this->mData[2]),
        w(this->mData[3]) { }

    virtual ~Vector() { }

    // We need to override the default assignment operator
    // since we have internal reference elements.
    ThisType& operator=(const ThisType& other) {
        MatrixUtil::copy(other.mData, this->mData, 4);
        return *this;
    }

    // Returns a unit vector representing the X axis.
    static ThisType xAxis() {
        return ThisType(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
    }

    // Returns a unit vector representing the Y axis.
    static ThisType yAxis() {
        return ThisType(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));
    }

    // Returns a unit vector representing the Z axis.
    static ThisType zAxis() {
        return ThisType(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));
    }

    // Returns a unit vector representing the W axis.
    static ThisType wAxis() {
        return ThisType(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
    }
};

// create some useful typedefs
typedef Matrix<4, 4, double> Mat4x4d;
typedef Matrix<4, 4, float> Mat4x4f;

typedef Vector<2, double> Vec2d;
typedef Vector<2, float> Vec2f;

typedef Vector<3, double> Vec3d;
typedef Vector<3, float> Vec3f;

typedef Vector<4, double> Vec4d;
typedef Vector<4, float> Vec4f;

} // end dkm namespace

#endif
