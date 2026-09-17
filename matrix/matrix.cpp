#include<iostream> 
#include<vector>
#include<random>
#include<cmath>

struct Matrix {

	int rows ; 
	int cols ; 
	std::vector<std::vector<double>>data ;


};

void addMatrix(Matrix a, Matrix b ) ; 
void multiplyMatrix(Matrix a, Matrix b ) ; 
Matrix transposeMatrix(Matrix a ) ; 
Matrix randomNumberInitiator() ; 

// non-lineriaty 

double sigmoid(double x) ; 
double relu(double x ) ; 
Matrix applySigmoid(Matrix m ) ; 
Matrix applyRelu(Matrix m ) ; 

// scalar function 


double sigmoid (double x ) {
	
	double exp = std::exp(-x) ; 

	return 1/ ( 1 + exp )  ; 



}

// scalar function 
double relu( double x) {

	if (x < 0 ) {
	
		return 0 ; 
	
	} else {
	
		return x ; 
		
	
	}


} 

// takes a matrix appliesSigmoid 
// to all the elements 
// returns  a new matrix with the sigmoid applied 


Matrix applySigmoid ( Matrix m ) {
	Matrix result ; 
	result.rows = m.rows ;
	result.cols = m.cols ; 
	result.data = std::vector<std::vector<double>>(result.rows, std::vector<double>(result.cols, 0.0)) ; 
	for (int i =0 ; i < result.rows ; i++) {
		for (int j =0 ; j < result.cols ; j++) {
			
			result.data[i][j] = sigmoid(m.data[i][j]) ; 
			
			
		
		}
		
	
	}

	return result ; 

}


// takes a matrix 
// appliesRelu to all the elements 
// and returns the resultant matrix 
Matrix applyRelu ( Matrix m ) {            
        Matrix result ;                       
        result.rows = m.rows ;                
        result.cols = m.cols ;                
        result.data = std::vector<std::vector<double>>(result.rows, std::vector<double>(result.cols,0.0)) ; 
	for (int i =0 ; i < result.rows ; i++) {
                for (int j =0 ; j < result.cols ; j++) {
                        
                        result.data[i][j] = relu(m.data[i][j]) ;



                }


        }

	return result ; 
}


// randoNumber generation 
// this function generates a random matrix with values from -0.1 - 0.1 



Matrix randomNumberInitiator() {

	std::random_device rd ; // seed source 
	std::mt19937 gen(rd()) ; // gen produces raw numbers. rd seeds gen.
	std::uniform_real_distribution<double>dist(-0.1, 0.1) ;	//for small floats, dist shapes them into the range we want . 
			       // double x = dist(gen) ;you need to call dist(gen) to get a number 
	
	Matrix randMatrix ; 
	randMatrix.rows = 3 ; 
	randMatrix.cols = 3 ;
	randMatrix.data = std::vector<std::vector<double>>(randMatrix.rows,std::vector<double>(randMatrix.cols,0.0)) ;

	for(int i =0 ; i < randMatrix.rows ;i++ ) {
		for(int j =0; j < randMatrix.cols; j++) {
			
			randMatrix.data[i][j] = dist(gen) ; 
			
			
		
		
		}
	
	
	}
	
	
	return randMatrix ; 





}

// to transposeMatrix means to turn rows into columns and columns into rows 
 
Matrix transposeMatrix (Matrix a ) {

	Matrix transposedMatrix ;
        transposedMatrix.rows = a.cols ; 
	transposedMatrix.cols = a.rows ; 
	transposedMatrix.data = std::vector<std::vector<double>>(transposedMatrix.rows, std::vector<double>(transposedMatrix.cols,0.0)) ; 
	
	for(int i =0 ; i < a.cols; i++ ) {
		for(int j =0 ; j < a.rows; j++) {
		
			transposedMatrix.data[i][j] = a.data[j][i] ;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               } 
	
	}	

	return transposedMatrix ; 
		





}


// to multiply  a matrix, cols of the first matrix = rows of the second matrix 
void multiplyMatrix(Matrix a, Matrix b) {
	// m*n , n*p 
	// resulting array should be 
 	if ( a.cols != b.rows ) {
		return ; 
	}

	Matrix c ; 
	c.rows = a.rows ; 
	c.cols = b.cols ; 
	c.data = std::vector<std::vector<double>>(c.rows, std::vector<double>(c.cols,0.0)); 
	for (int i = 0 ; i < a.rows ; i++) {
		for (int j =0; j < b.cols ; j++) {
				int sum = 0 ; 
			for (int k = 0 ; k < a.cols ; k++) {
			 	sum = sum + a.data[i][k]* b.data[k][j]; 
			
			}
		
				c.data[i][j] = sum ; 
						
				std::cout<<c.data[i][j]<<" " ; 	
		
		}
		std::cout<<"\n" ; 
	
	
	}





}

void addMatrix (Matrix a, Matrix b) {

	Matrix c ; 
	c.rows = 2 ;
	c.cols = 2 ; 
	c.data = {{0,0}, {0,0}}; 	





	// adding the matrices
	 
	std::cout<<"A + B = \n ";	
	for (int i =0; i < c.rows; i++ ) { 
		for (int j=0; j < c.cols; j++) {
			// adding and restoring 
			c.data[i][j] = a.data[i][j] + b.data[i][j]  ; 
		       	std::cout<<c.data[i][j]<<" "; 
		}
		std::cout<<"\n" ; 
	
	}






} 



int main() {
	
	Matrix a ; 
	a.rows = 2; 
	a.cols = 2 ; 
	a.data = {{1,2},{3,4}} ; //initializing a matrix 
	
	Matrix b ; 
	b.rows = 2 ; 
	b.cols = 2 ;
	b.data = {{5,6},{7,8}}; 
	std::cout<<"\n" ; 

	multiplyMatrix(a,b) ; 
	
	Matrix c ; 
	c.rows = 2 ; 
	c.cols = 3 ; 
	c.data = {{1,2,3},{4,5,6}}; 
	
	// calling transposeMatrix func 
	
	Matrix transposedMatrix ;
	
	transposedMatrix.rows = c.cols ; 
	transposedMatrix.cols = c.rows ; 
	transposedMatrix.data = std::vector<std::vector<double>>(c.cols,std::vector<double>(c.rows,0.0)); // inititalizinng the matrix to zeroes   
	transposedMatrix  = transposeMatrix(c) ; 
	
	for (int i =0 ; i < transposedMatrix.rows ; i++) {
		for(int j =0; j < transposedMatrix.cols; j++) {
			std::cout<< transposedMatrix.data[i][j]<<" " ; 
			
		
		}
		
		std::cout<<"\n" ; 

	} 

	// random matrix for neural weights at the beginining 	
         
   	  Matrix randomMatrix  ; 
	  randomMatrix.rows = 3 ; 
	  randomMatrix.cols = 3 ; 
	  randomMatrix.data = std::vector<std::vector<double>>(randomMatrix.rows,std::vector<double>(randomMatrix.cols,0.0)) ; 
	  randomMatrix = randomNumberInitiator() ; 
	  
	  std::cout<<"Randomised Matrix \n\n" ;  
	  
	  for (int i =0 ; i < randomMatrix.rows; i++) {
                for(int j =0; j < randomMatrix.cols; j++) {
                        std::cout<< randomMatrix.data[i][j]<<" " ;


                }

                std::cout<<"\n" ;

        }
	 
	  std::cout<<"\n" ; 
	  Matrix d ; 
	  d.rows = 2 ; 
	  d.cols = 3 ; 
	  d.data = {{-2,-1,0}, 
	  	    {1,2,3}} ;

	  Matrix appliedSigmoidResult ; 
	  appliedSigmoidResult.rows  = d.rows ; 
	  appliedSigmoidResult.cols = d.cols ; 
	  appliedSigmoidResult.data = std::vector< std::vector<double>>(appliedSigmoidResult.rows, std::vector<double> (appliedSigmoidResult.cols,0.0)) ;	
	  appliedSigmoidResult=  applySigmoid(d) ; 
	  
	  std::cout<<"\nappliedSigmoidResult: \n\n" ;  

	  for (int i = 0 ; i < d.rows; i++) {
	  	for(int j = 0 ; j < d.cols; j++) {
			std::cout<< appliedSigmoidResult.data[i][j]<<" " ; 
			
		
		
		}
		std::cout<<"\n" ; 
	  	
	  
	  }
	
	  Matrix appliedReluResult ; 
	  appliedReluResult.rows = d.rows ;
	  appliedReluResult.cols = d.cols ; 
	  appliedReluResult.data = std::vector<std::vector<double>>(appliedReluResult.rows, std::vector<double>(appliedReluResult.cols, 0.0)) ; 

	  std::cout<<"appliedReluResult\n\n" ; 
	  appliedReluResult = applyRelu(d) ; 
	  for (int i =0; i < d.rows; i++) {
	  	for(int j = 0 ; j < d.cols ; j++ ) {
			
			std::cout<<appliedReluResult.data[i][j]<<" " ; 
		
		
		}


		std::cout<<"\n" ; 
	  
	  
	  }







}
