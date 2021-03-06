#include "matrix.h"

Matrix::Matrix()
{
	nrows = 0;
	ncols = 0;
}

Matrix::Matrix(int length)
{
	zeros(length,1);
}

Matrix::Matrix(int length, char ind)
{
	if(ind == 'c')
		zeros(length,1);
	else
		zeros(1,length);
}

Matrix::Matrix(int m, int n)
{
	zeros(m,n);
}

Matrix::~Matrix()
{
	mat.clear();
}

void Matrix::initiate_array(double* M, int m, int n)
{
	mat = vector<double>(m*n); 
	nrows = m;
	ncols = n;

	for( int i=0 ; i<nrows*ncols ; i++ )
		mat[i] = M[i];
}


void Matrix::initiate_vector(vector<double> M, int m, int n)
{
	mat = M;
	nrows = m;
	ncols = n;
}

void Matrix::initiate_vector_vector(vector< vector<double> > M)
{
	nrows = M.size();
	ncols = M[0].size();

	mat = vector<double>(nrows*ncols);
	for(int i = 0 ; i < nrows ; i++)
	{
		assert( M[i].size() == ncols );
		for(int j = 0 ; j < ncols ; j++)
			at(i,j) = M[i][j];
	}
}

void Matrix::zeros(int m, int n)
{
	nrows = m;
	ncols = n;
	mat = vector<double>( m*n, 0.0 );
}

void Matrix::zeros(int m)
{
	zeros(m,1);
}

void Matrix::ones(int m, int n)
{
	nrows = m;
	ncols = n;
	mat = vector<double>( m*n, 1.0 );
}

void Matrix::eye(int m)
{
	nrows = m;
	ncols = m;
	mat = vector<double>( m*m, 0.0 );

	for( int i=0 ; i<m ; i++ )
		at(i,i) = 1.0;	
}

void Matrix::jay(int n)
{
	nrows = 2*n;
	ncols = 2*n;
	mat = vector<double>( 4*n*n, 0.0 );
	for( int i=0 ; i<n ; i++ )
	{
		at(i, n+i) = 1.0;
		at(n+i, i) = -1.0;
	}
}

void Matrix::rand(int m, int n)
{
	nrows = m;
	ncols = n;
	mat = vector<double>( m*n, 0.0 );

	for( int i=0 ; i<nrows ; i++ )
		for(int j=0 ; j<ncols ; j++)
			at(i,j) = (double) std::rand() / RAND_MAX;
}

void Matrix::rand(int m)
{
	rand(m,1);
}

void Matrix::clear()
{
	nrows = 0;
	ncols = 0;
	mat.clear();
}

int Matrix::get_num_rows()
{
	return nrows;
}

int Matrix::get_num_cols()
{
	return ncols;
}

void Matrix::get_size(int* m, int* n)
{
	(*m) = nrows;
	(*n) = ncols;
}

int Matrix::length()
{
	if(nrows > ncols)
		return nrows;
	else
		return ncols;
}

double Matrix::get_element(int m, int n)
{
	assert( ( m<nrows ) && ( n<ncols ) );
	return mat[m*ncols + n];
}

vector<double> Matrix::get_matrix()
{
	return mat;
}

vector<double>* Matrix::get_matrix_ptr()
{
	return &mat;
}

Matrix Matrix::get_row(int m)
{
	assert( m<nrows );
	Matrix result;
	result.nrows = 1;
	result.ncols = ncols;
	for(int i = 0 ; i < ncols ; i++)
		(result.mat).push_back( mat[ m*ncols + i ] );
	return result;
}

Matrix Matrix::get_col(int n)
{
	assert( n<ncols );
	Matrix result;
	result.nrows = nrows;
	result.ncols = 1;
	for(int i = 0 ; i < nrows ; i++)
		(result.mat).push_back( mat[ i*ncols + n ] );
	return result;
}

Matrix Matrix::get_submat(int r1, int r2, int c1, int c2)
{
	assert( (r1 < r2) && (c1 < c2) && (r2 <= nrows) && (c2 <= ncols) );
	Matrix result;
	result.zeros(r2-r1,c2-c1);
	for(int i = 0 ; i < (r2-r1) ; i++ )
	{
		for(int j = 0 ; j < (c2-c1) ; j++ )
			result.at( i , j ) = this->at( r1 + i , c1 + j );
	}
	return result;
}

void Matrix::set_row(int pos, Matrix row)
{
	assert( (pos < nrows) && (row.ncols == ncols) );
	for(int i = 0 ; i < ncols ; i++)
		this->at(pos,i) = row.at(0,i);
}

void Matrix::set_col(int pos, Matrix col)
{
	assert( (pos < ncols) && (col.nrows == nrows) );
	for(int i = 0 ; i < nrows ; i++)
		this->at(i,pos) = col.at(i,0);
}

void Matrix::set_submat(int r, int c, Matrix M)
{
	assert( (r+M.nrows <= nrows) && (c+M.ncols <= ncols)  );
	for(int i = 0 ; i < M.nrows ; i++)
	{
		for(int j = 0 ; j < M.ncols ; j++)
			this->at(r+i,c+j) = M.at(i,j);
	}
}

double& Matrix::operator()(int m, int n)
{
	return mat[m*ncols + n];
}

double& Matrix::operator()(int pos)
{
	assert( (nrows == 1) || (ncols == 1) );
	return mat[pos];	
}

double& Matrix::at( int m, int n )
{
	return mat[m*ncols + n];
}

double& Matrix::at(int pos)
{
	assert( (nrows == 1) || (ncols == 1) );
	return mat[pos];
}

void Matrix::add_row(Matrix M)
{
	assert( ( (M.nrows == 1) && (M.ncols == ncols) ) || ((nrows == 0) && (ncols == 0)) );
	if( (M.nrows == 1) && (M.ncols == ncols) )
	{
		nrows++;
		for(int i = 0 ; i < ncols ; i++)
			mat.push_back( M.at(0,i) );
	}
	else
	{
		assert( M.nrows == 1 );
		nrows = 1;
		ncols = M.ncols;
		for(int i = 0 ; i < M.ncols ; i++)
			mat.push_back( M.at(0,i) );
	}
}

void Matrix::add_col(Matrix M)
{
	if((nrows == 0) && (ncols == 0))
	{
		assert( M.ncols == 1 );
		ncols = 1;
		nrows = M.nrows;
		for(int i = 0 ; i < nrows ; i++)
			mat.push_back(M.at(i,0));
	}
	else
	{
		(*this) = this->tr();
		this->add_row( M.tr() );
		(*this) = this->tr();
	}
}

void Matrix::append(Matrix M, char ind)
{
	if(ind == 'r')
	{
		assert( ncols == M.ncols );
		mat.insert( mat.end() , (M.mat).begin() , (M.mat).end() );
		nrows += M.nrows;
	}
	else
	{
		assert( nrows == M.nrows );
		(*this) = this->tr();
		this->append( M.tr() , 'r' );
		(*this) = this->tr();
	}
}

double Matrix::max(int* idx)
{
	assert(nrows == 1 || ncols == 1);
	double res = at(0);
	(*idx) = 0;
	for(int i=1 ; i<length() ; i++)
	{
		if(at(i) > res)
		{
			res = at(i);
			(*idx) = i;
		}
	}
	return res;
}

double Matrix::min(int* idx)
{
	assert(nrows == 1 || ncols == 1);
	double res = at(0);
	(*idx) = 0;
	for(int i=1 ; i<length() ; i++)
	{
		if(at(i) < res)
		{
			res = at(i);
			(*idx) = i;
		}
	}
	return res;
}

void Matrix::operator=(Matrix M)
{
	M.get_size(&nrows,&ncols);
	mat = M.mat;
}

Matrix Matrix::operator+(Matrix M)
{
	assert( (nrows == M.nrows) && (ncols == M.ncols) );
	Matrix result(nrows,ncols);
	for(int i=0 ; i<nrows ; i++)
		for(int j=0 ; j<ncols ; j++)
			result.at(i,j) = at(i,j) + M.at(i,j);
	return result;
}

void Matrix::operator+=(Matrix M)
{
	assert( (nrows == M.nrows) && (ncols == M.ncols) );
	for(int i=0 ; i<nrows ; i++)
		for(int j=0 ; j<ncols ; j++)
			at(i,j) += M.at(i,j);
}

Matrix Matrix::operator-(Matrix M)
{
	assert( (nrows == M.nrows) && (ncols == M.ncols) );
	Matrix result(nrows,ncols);
	for(int i=0 ; i<nrows ; i++)
		for(int j=0 ; j<ncols ; j++)
			result.at(i,j) = at(i,j) - M.at(i,j);
	return result;
}

void Matrix::operator-=(Matrix M)
{
	assert( (nrows == M.nrows) && (ncols == M.ncols) );
	for(int i=0 ; i<nrows ; i++)
		for(int j=0 ; j<ncols ; j++)
			at(i,j) -= M.at(i,j);
}

Matrix Matrix::operator*(Matrix M)
{
	assert(ncols == M.nrows);
	Matrix result;
	result.nrows = nrows;
	result.ncols = M.ncols;
	double temp;
	for(int i = 0 ; i < nrows ; i++)
	{
		for(int j = 0 ; j < M.ncols ; j++)
		{
			temp = 0;
			for(int k = 0 ; k < ncols ; k++)
			{
				temp += mat[ i*ncols+k ]*M.mat[k*M.ncols + j];
			}
			(result.mat).push_back(temp);
		}
	}
	return result;
}

/*
Matrix Matrix::operator*(Matrix M)
{
	assert( ncols == M.nrows );
	double* mat1 = new double[nrows*ncols];
	double* mat2 = new double[M.nrows*M.ncols];
	int m = nrows;
	int n = M.ncols;
	int k = ncols;

	for(int i=0 ; i<ncols ; i++)
		for(int j=0 ; j<nrows ; j++)
			mat1[ i*nrows + j ] = at(j,i);

	for(int i=0 ; i<M.ncols ; i++)
		for(int j=0 ; j<M.nrows ; j++)
			mat2[ i*M.nrows + j ] = M.at(j,i);
	
	double* prod = new double[m*n];

	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, 1.0, mat1, k, mat2 , n, 0.0, prod, n);

	Matrix result(m,n);
	
	for(int i=0 ; i<m ; i++)
		for(int j=0 ; j<n ; j++)
			result.at(i,j) = prod[ i*n+j ];

	delete[] mat1;
	delete[] mat2;
	delete[] prod;

	return result;
}
*/

Matrix Matrix::operator+( double c )
{
	Matrix result;
	result.initiate_vector( mat, nrows, ncols );
	for( int i=0 ; i<nrows ; i++ )
		for( int j=0 ; j<ncols ; j++ )
			result.at(i,j) += c;
	return result;	
}

void Matrix::operator+=( double c )
{
	for( int i=0 ; i<nrows ; i++ )
		for( int j=0 ; j<ncols ; j++ )
			at(i,j) += c;
}

Matrix Matrix::operator-( double c )
{
	Matrix result;
	result.initiate_vector( mat, nrows, ncols );
	for( int i=0 ; i<nrows ; i++ )
		for( int j=0 ; j<ncols ; j++ )
			result.at(i,j) -= c;
	return result;	
}

void Matrix::operator-=( double c )
{
	for( int i=0 ; i<nrows ; i++ )
		for( int j=0 ; j<ncols ; j++ )
			at(i,j) -= c;
}

Matrix Matrix::operator*( double c )
{
	Matrix result;
	result.initiate_vector( mat, nrows, ncols );
	for( int i=0 ; i<nrows ; i++ )
		for( int j=0 ; j<ncols ; j++ )
			result.at(i,j) *= c;
	return result;	
}

void Matrix::operator*=( double c )
{
	for( int i=0 ; i<nrows ; i++ )
		for( int j=0 ; j<ncols ; j++ )
			at(i,j) *= c;
}

Matrix Matrix::operator/( double c )
{
	Matrix result;
	result.initiate_vector( mat, nrows, ncols );
	for( int i=0 ; i<nrows ; i++ )
		for( int j=0 ; j<ncols ; j++ )
			result.at(i,j) /= c;
	return result;	
}

void Matrix::operator/=( double c )
{
	for( int i=0 ; i<nrows ; i++ )
		for( int j=0 ; j<ncols ; j++ )
			at(i,j) /= c;
}

double Matrix::inner(Matrix* vec)
{
	assert( (nrows == vec->nrows) && (ncols == vec->ncols) && ( (nrows == 1) || (ncols ==1) ) );
	double res =0.;
	for(int i=0 ; i<length() ; i++)
	{
		res += at(i)*vec->at(i);
	}
	return res;
}

double Matrix::bilinear(Matrix* vec)
{
	assert( (nrows == vec->nrows) && (ncols == vec->ncols) && ( (nrows == 1) || (ncols ==1) ) && (length()%2 == 0) );
	Matrix J;
	J.jay(length()/2);
	Matrix res = tr() * J * (*vec);
	return res(0,0);
}

Matrix Matrix::scalar(double c)
{
	Matrix result;
	result.initiate_vector( mat, nrows, ncols );
	for( int i=0 ; i<nrows ; i++ )
		for( int j=0 ; j<ncols ; j++ )
			result.at(i,j) *= c;
	return result;	
}

Matrix Matrix::tr()
{
	Matrix result;
	result.zeros( ncols, nrows );
	for(int i = 0 ; i < ncols ; i++)
		for(int j = 0 ; j < nrows ; j++)
			result.at(i,j) = at(j,i);
	return result;
}

double Matrix::trace()
{
	int min = ( nrows < ncols ) ? nrows : ncols;
	
	double res = 0;
	for(int i=0 ; i<min ; i++)
		res += at(i,i);
	return res;
}

double Matrix::norm2()
{
	double n = 0;
	for(int i = 0 ; i < mat.size() ; i++)
		n += mat[i]*mat[i];
	return sqrt(n);
}

double Matrix::frobenius()
{
	return sqrt( (this->tr() * (*this)).trace() );
}

void Matrix::linspace(double min, double max,int n)
{
	vector<double> result;
	double temp;

	for(int i = 0 ; i <= n-2 ; i++)
	{
		temp = min + i*(max-min)/(floor((double)n) - 1) ;
		result.push_back( temp );
	}
	result.push_back(max);
	initiate_vector(result,result.size(),1);
}

void Matrix::svd(vector< vector<double> >* U_mat, vector<double>* S_vec, vector< vector<double> >* V_mat)
{
	double* A = new double[nrows*ncols];

	// matrix must be stored column wise
	for(int i = 0 ; i < ncols ; i++)
	{
		for(int j = 0 ; j < nrows ; j++)
			A[ i*nrows + j ] = mat[j*ncols + i];
	}

	char JOBU = 'S';
	char JOBVT = 'S';
	__CLPK_integer M = nrows;
	__CLPK_integer N = ncols;
	__CLPK_integer LDA = nrows;
	int min;
	if(nrows > ncols)
		min = ncols;
	else
		min = nrows;
	double* S = new double[min];
	double* U = new double[nrows * min];
	__CLPK_integer LDU = nrows;

	double* VT = new double[min * ncols];
	__CLPK_integer LDVT = min;

	double work_size;
	__CLPK_integer LWORK = -1;
	__CLPK_integer INFO;

	dgesvd_(&JOBU,&JOBVT,&M,&N,A,&LDA,S,U,&LDU,VT,&LDVT,&work_size,&LWORK,&INFO);
	LWORK = static_cast<int>(work_size);
	double* WORK = new double[LWORK];
	
	dgesvd_(&JOBU,&JOBVT,&M,&N,A,&LDA,S,U,&LDU,VT,&LDVT,WORK,&LWORK,&INFO);

	assert(INFO == 0);

	delete[] A;
	delete[] WORK;

	vector<double> temp;
	for(int i = 0 ; i < min ; i++)
	{
		temp.clear();
		for(int j = 0 ; j < nrows ; j++)
			temp.push_back( U[i*min + j] );
		U_mat->push_back(temp);
	}

	for(int i = 0 ; i < min ; i++)
		S_vec->push_back( S[i] );

/*
	for(int i = 0 ; i < ncols ; i++)
	{
		temp.clear();
		for(int j = 0 ; j < min ; j++)
			temp.push_back( VT[i*min + j] );
		V_mat->push_back(temp);
	}
*/
	for(int i = 0 ; i < min ; i++)
	{
		temp.clear();
		for(int j = 0 ; j < ncols ; j++)
			temp.push_back( VT[j*min + i] );
		V_mat->push_back( temp );
	}

	delete[] S;
	delete[] U;
	delete[] VT;
}

void Matrix::svd(Matrix* U_mat, Matrix* S_vec, Matrix* V_mat)
{
	double* A = new double[nrows*ncols];

	// matrix must be stored column wise
	for(int i = 0 ; i < ncols ; i++)
	{
		for(int j = 0 ; j < nrows ; j++)
			A[ i*nrows + j ] = mat[j*ncols + i];
	}

	char JOBU = 'S';
	char JOBVT = 'S';
	__CLPK_integer M = nrows;
	__CLPK_integer N = ncols;
	__CLPK_integer LDA = nrows;
	int min;
	if(nrows > ncols)
		min = ncols;
	else
		min = nrows;
	double* S = new double[min];
	double* U = new double[nrows * min];
	__CLPK_integer LDU = nrows;

	double* VT = new double[min * ncols];
	__CLPK_integer LDVT = min;

	double work_size;
	__CLPK_integer LWORK = -1;
	__CLPK_integer INFO;

	dgesvd_(&JOBU,&JOBVT,&M,&N,A,&LDA,S,U,&LDU,VT,&LDVT,&work_size,&LWORK,&INFO);
	LWORK = static_cast<int>(work_size);
	double* WORK = new double[LWORK];
	
	dgesvd_(&JOBU,&JOBVT,&M,&N,A,&LDA,S,U,&LDU,VT,&LDVT,WORK,&LWORK,&INFO);

	assert(INFO == 0);

	delete[] A;
	delete[] WORK;

	U_mat->clear();
	U_mat->zeros(nrows,min);
	for(int i = 0 ; i < min ; i++)
	{
		for(int j = 0 ; j < nrows ; j++)
			 U_mat->at(j,i) = U[i*nrows + j];
	}

	S_vec->clear();
	S_vec->zeros(min,1);
	for(int i = 0 ; i < min ; i++)
		S_vec->at(i) = S[i];

	V_mat->clear();
	V_mat->zeros(min,ncols);
	for(int i = 0 ; i < min ; i++)
	{
		for(int j = 0 ; j < ncols ; j++)
			V_mat->at(i,j) = VT[j*min + i];
	}
	(*V_mat) = V_mat->tr();

	delete[] S;
	delete[] U;
	delete[] VT;
}


Matrix Matrix::inv()
{
	assert( nrows == ncols );
	Matrix result;
	double* A = new double[ nrows*nrows ];
	// matrix must be stored column wise
	for(int i = 0 ; i < ncols ; i++)
	{
		for(int j = 0 ; j < nrows ; j++)
			A[ i*nrows + j ] = mat[j*ncols + i];
	}

	__CLPK_integer N = nrows;
	__CLPK_integer LDA = nrows;
	__CLPK_integer* IPIV = new __CLPK_integer[ nrows+1 ];
	double work_size;
	__CLPK_integer LWORK = -1;
	__CLPK_integer INFO;

	dgetrf_(&N,&N,A,&LDA,IPIV,&INFO);
	assert(INFO == 0);

	dgetri_(&N,A,&LDA,IPIV,&work_size,&LWORK,&INFO);

	LWORK = static_cast<int>(work_size);
	double* WORK = new double[LWORK];

	dgetri_(&N,A,&LDA,IPIV,WORK,&LWORK,&INFO);

	assert(INFO == 0);

	delete[] WORK;

	result.zeros(nrows,nrows);
	for(int i = 0 ; i < nrows ; i++)
	{
		for(int j = 0 ; j < ncols ; j++)
			result.at(i,j) = A[ j*nrows + i ];
	}

	delete[] A;
	delete[] IPIV;
	return result;
}

/*
          On exit, LU will have the factors L and U from the factorization
          A = P*L*U; the unit diagonal elements of L are not stored.
*/

void Matrix::lu(Matrix* LU, int* pivot)
{
	double* A = new double[ nrows*nrows ];
	// matrix must be stored column wise
	for(int i = 0 ; i < ncols ; i++)
	{
		for(int j = 0 ; j < nrows ; j++)
			A[ i*nrows + j ] = mat[j*ncols + i];
	}

	__CLPK_integer N = nrows;
	__CLPK_integer M = ncols;
	__CLPK_integer LDA = nrows;
	__CLPK_integer* IPIV = new __CLPK_integer[ nrows+1 ];
	__CLPK_integer INFO;

	dgetrf_(&N,&N,A,&LDA,IPIV,&INFO);
	assert(INFO == 0);

	LU->zeros(nrows,ncols);
	for(int i=0 ; i<nrows ; i++ )
		for(int j=0 ; j<ncols ; j++)
			LU->at(i,j) = A[j*nrows + i];

	pivot = new int[nrows+1];
	for(int i=0 ; i<nrows+1 ; i++)
		pivot[i] = IPIV[i];

	delete[] A;
	delete[] IPIV;
}

double Matrix::det()
{
	assert(nrows == ncols);

	int* pivot;
	Matrix LU;

	lu(&LU,pivot);

	double det = 1.0;

	for(int i=0 ; i<nrows ; i++)
		det *= LU.at(i,i);

	delete[] pivot;
	return det;
}

void Matrix::eig(Matrix* eigval)
{
	assert(nrows == ncols);
	double* A = new double[ nrows*nrows ];
	// matrix must be stored column wise
	for(int i = 0 ; i < ncols ; i++)
	{
		for(int j = 0 ; j < nrows ; j++)
			A[ i*nrows + j ] = mat[j*ncols + i];
	}
	
	char JOBVL = 'N';
	char JOBVR = 'N';

	__CLPK_integer N = nrows;
	__CLPK_integer LDA = nrows;
	double* WR = new double[nrows];
	double* WI = new double[nrows];
	double* VL;
	__CLPK_integer LDVL = 1;
	double* VR;
	__CLPK_integer LDVR = 1;

	double work_size;
	__CLPK_integer LWORK = -1;
	__CLPK_integer INFO;

	dgeev_(&JOBVL,&JOBVR,&N,A,&LDA,WR,WI,VL,&LDVL,VR,&LDVR,&work_size,&LWORK,&INFO);
	LWORK = static_cast<int>(work_size);
	double* WORK = new double[LWORK];
	
	dgeev_(&JOBVL,&JOBVR,&N,A,&LDA,WR,WI,VL,&LDVL,VR,&LDVR,WORK,&LWORK,&INFO);
	assert(INFO == 0);

	delete[] WORK;

	eigval->zeros(nrows,2);
	for(int i=0 ; i<nrows ; i++)
		eigval->at(i,0) = WR[i];
	for(int i=0 ; i<nrows ; i++)
		eigval->at(i,1) = WI[i];

	delete[] A;
	delete[] WR;
	delete[] WI;
}

void Matrix::eig(Matrix* eigval, Matrix* eigvecR, Matrix* eigvecI)
{
	assert(nrows == ncols);
	double* A = new double[ nrows*nrows ];
	// matrix must be stored column wise
	for(int i = 0 ; i < ncols ; i++)
	{
		for(int j = 0 ; j < nrows ; j++)
			A[ i*nrows + j ] = mat[j*ncols + i];
	}
	
	char JOBVL = 'N';
	char JOBVR = 'V';

	__CLPK_integer N = nrows;
	__CLPK_integer LDA = nrows;
	double* WR = new double[nrows];
	double* WI = new double[nrows];
	double* VL;
	__CLPK_integer LDVL = 1;
	double* VR = new double[nrows*ncols];
	__CLPK_integer LDVR = nrows;

	double work_size;
	__CLPK_integer LWORK = -1;
	__CLPK_integer INFO;

	dgeev_(&JOBVL,&JOBVR,&N,A,&LDA,WR,WI,VL,&LDVL,VR,&LDVR,&work_size,&LWORK,&INFO);
	LWORK = static_cast<int>(work_size);
	double* WORK = new double[LWORK];
	
	dgeev_(&JOBVL,&JOBVR,&N,A,&LDA,WR,WI,VL,&LDVL,VR,&LDVR,WORK,&LWORK,&INFO);
	assert(INFO == 0);

	delete[] WORK;

	eigval->zeros(nrows,2);
	for(int i=0 ; i<nrows ; i++)
		eigval->at(i,0) = WR[i];
	for(int i=0 ; i<nrows ; i++)
		eigval->at(i,1) = WI[i];
	
	eigvecR->zeros(nrows,ncols);
	eigvecI->zeros(nrows,ncols);
	for(int i=0 ; i<nrows ; i++)
	{
		if(eigval->at(i,1) == 0)
		{
			for(int j=0 ; j<nrows ; j++)
			{
				eigvecR->at(j,i) = VR[ i*nrows + j ];
				eigvecI->at(j,i) = 0;
			}
		}
		else
		{
			for(int j=0 ; j<nrows ; j++)
			{
				eigvecR->at(j,i) = VR[ i*nrows + j ];
				eigvecI->at(j,i) = VR[ (i+1)*nrows + j ];
				eigvecR->at(j,i+1) = VR[ i*nrows + j ];
				eigvecI->at(j,i+1) = -VR[ (i+1)*nrows + j ];
			}
			i++;
		}
	}

	delete[] VR;
	delete[] A;
	delete[] WR;
	delete[] WI;
}

void Matrix::eig_sym(Matrix* eigval)
{
	assert(nrows == ncols);
	double* A = new double[ nrows*nrows ];
	// matrix must be stored column wise
	for(int i = 0 ; i < ncols ; i++)
	{
		for(int j = 0 ; j < nrows ; j++)
			A[ i*nrows + j ] = mat[j*ncols + i];
	}

	char JOBZ = 'N';
	char UPLO = 'U';

	__CLPK_integer N = nrows;
	__CLPK_integer LDA = nrows;
	double* W = new double[nrows];

	double work_size;
	__CLPK_integer LWORK = -1;
	__CLPK_integer INFO;

	dsyev_(&JOBZ,&UPLO,&N,A,&LDA,W,&work_size,&LWORK,&INFO);
	LWORK = static_cast<int>(work_size);
	double* WORK = new double[LWORK];

	dsyev_(&JOBZ,&UPLO,&N,A,&LDA,W,WORK,&LWORK,&INFO);
	assert(INFO == 0);

	delete[] WORK;

	eigval->zeros(nrows,1);
	for(int i=0 ; i<nrows ; i++)
		eigval->at(i) = W[i];

	delete[] A;
	delete[] W;
}

void Matrix::eig_sym(Matrix* eigval, Matrix* eigvec)
{
	assert(nrows == ncols);
	double* A = new double[ nrows*nrows ];
	// matrix must be stored column wise
	for(int i = 0 ; i < ncols ; i++)
	{
		for(int j = 0 ; j < nrows ; j++)
			A[ i*nrows + j ] = mat[j*ncols + i];
	}

	char JOBZ = 'V';
	char UPLO = 'U';

	__CLPK_integer N = nrows;
	__CLPK_integer LDA = nrows;
	double* W = new double[nrows];

	double work_size;
	__CLPK_integer LWORK = -1;
	__CLPK_integer INFO;

	dsyev_(&JOBZ,&UPLO,&N,A,&LDA,W,&work_size,&LWORK,&INFO);
	LWORK = static_cast<int>(work_size);
	double* WORK = new double[LWORK];

	dsyev_(&JOBZ,&UPLO,&N,A,&LDA,W,WORK,&LWORK,&INFO);
	assert(INFO == 0);

	delete[] WORK;

	eigval->zeros(nrows,1);
	for(int i=0 ; i<nrows ; i++)
		eigval->at(i) = W[i];

	eigvec->zeros(nrows,ncols);
	for(int i=0 ; i<nrows ; i++)
		for(int j=0 ; j<nrows ; j++)
			eigvec->at(j,i) = A[ i*nrows + j ];
	delete[] A;
	delete[] W;
}

void Matrix::operator()()
{
	cout << "---------------------";
	int col_size = ncols;
	int print_col_size = 7;
	int complete = col_size / print_col_size;
	int rem = col_size - complete*print_col_size;

	for(int i=0 ; i<complete ; i++)
	{
		int col_offset = i*print_col_size;
		cout << endl << "  Columns " << col_offset << " through " << col_offset+print_col_size-1 << endl << endl;
		for(int j=0 ; j< nrows ; j++)
		{
			for(int k=0 ; k<print_col_size ; k++)
			{
				cout.width(11);
				cout << std::setprecision(4) << at(j,col_offset+k);
			}
			cout << endl;
		}
	}
	if(rem != 0)
	{
		int col_offset = complete*print_col_size;
		cout << endl << "  Columns " << col_offset << " through " << col_offset+rem-1 << endl << endl;
		for(int j=0 ; j<nrows ; j++)
		{
			for(int k=0 ; k<rem ; k++)
			{
				cout.width(11);
				cout << std::setprecision(4) << at(j,col_offset+k);
			}
			cout << endl;
		}
	}
	cout << "---------------------" << endl;
}

ostream& operator<<(ostream& os,Matrix& M)
{
	cout << "---------------------";
	int col_size = M.ncols;
	int print_col_size = 7;
	int complete = col_size / print_col_size;
	int rem = col_size - complete*print_col_size;

	for(int i=0 ; i<complete ; i++)
	{
		int col_offset = i*print_col_size;
		cout << endl << "  Columns " << col_offset << " through " << col_offset+print_col_size-1 << endl << endl;
		for(int j=0 ; j<M.nrows ; j++)
		{
			for(int k=0 ; k<print_col_size ; k++)
			{
				cout.width(11);
				cout << std::setprecision(4) << M.at(j,col_offset+k);
			}
			cout << endl;
		}
	}
	if(rem != 0)
	{
		int col_offset = complete*print_col_size;
		cout << endl << "  Columns " << col_offset << " through " << col_offset+rem-1 << endl << endl;
		for(int j=0 ; j<M.nrows ; j++)
		{
			for(int k=0 ; k<rem ; k++)
			{
				cout.width(11);
				cout << std::setprecision(4) << M.at(j,col_offset+k);
			}
			cout << endl;
		}
	}
	cout << "---------------------";
	return os;
}

void Matrix::print()
{
	cout << "---------------------" << endl;
	for(int i = 0 ; i < nrows ; i++)
	{
		for(int j = 0 ; j < ncols ; j++)
		{
			cout.width(17);
			cout << std::setprecision(10) << mat[i*ncols + j];
		}
		cout << endl;
	}
	cout << "---------------------";
}

void Matrix::save(char* path)
{
	ofstream file;
	file.open(path);

	for(int i = 0 ; i < nrows ; i++)
	{
		for(int j = 0 ; j < ncols ; j++)
			file << std::setprecision(16) << mat[i*ncols + j] << " ";
		file << endl;
	}
	file.close();	
}

void Matrix::open(int m, int n, char* path)
{
	ifstream file;
	file.open(path);

	this->zeros(m,n);

	for(int i=0 ; i<nrows ; i++)
	{
		for(int j=0 ; j<ncols ; j++)
			file >> this->at(i,j);
	}
	file.close();
}
