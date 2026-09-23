#include<iostream> 
#include<vector>
#include<random>
#include<cmath>
#include<string> 
struct Matrix {

	int rows ; 
	int cols ; 
	std::vector<std::vector<double>>data ;


};

/* 
**/ 

struct Layer {
	
	Matrix weights ;  //  how important is the ip 
	Matrix biases ; // the baseline value 
	std::string activation ; // if activation is relu or sigmoid   



}; 


Matrix addMatrix(Matrix a, Matrix b ) ; 
Matrix multiplyMatrix(Matrix a, Matrix b ) ; 
Matrix transposeMatrix(Matrix a ) ; 
Matrix randomNumberInitiator() ;
void view(Matrix m) ; 


// non-linearity  



double sigmoid(double x) ; 
double relu(double x ) ; 
Matrix applySigmoid(Matrix m ) ; 
Matrix applyRelu(Matrix m ) ; 
Matrix forwardLayer(Layer l, Matrix b) ; // takes a layer and a matrix 

void view(Matrix m ) { // helper function to help see the matrixes at each stages 
		       // to understand the effects of all the functions 
	
	std::cout<<"\n" ; 	
	for(int i = 0 ; i < m.rows;  i++ ) {
		for(int j =0 ; j < m.cols; j++) {
		
			std::cout<<" " << m.data[i][j] <<" " ; 
		
		} 
		std::cout<<"\n" ; 
	
	
	}
	
	std::cout<<"\n" ; 
	





}


Matrix forwardLayer(Layer l, Matrix b ) {

	// take the input matrix 
	// multiply the input by the transpose of the weights ; 
	// add the biases to z ; 
	// apply activation based on the layers activation string 
	std::cout<<"Insided forwardLayer\n" ; 
	Matrix transposedWeights = transposeMatrix(l.weights);
	std::cout<<"\nTransposedWeights : \n\n" ; 
	view(transposedWeights) ; 
	Matrix z  = multiplyMatrix( b,transposedWeights) ;
        std::cout<<"\n z  : inputmatrix * transposedWeights \n" ; 
	view(z) ; 
        
	
	// add the biases to z  
	 
	Matrix transposedBias = transposeMatrix(l.biases);
        std::cout<<"\n biases : \n" ; 	
	view(l.biases) ; 
	std::cout<<"\nTransposedBiass : \n" ;
	view(transposedBias) ; 	

	z = addMatrix(transposedBias, z) ; 
	std::cout<<"\n z = ( transposedBias + z)   \n";
	view(z) ; 
	

	if (l.activation == "relu") {
	      
		std::cout<<"\napplying Relu\n" ; 
	      	z = applyRelu(z) ; 
	
	} 
	
	if (l.activation == "sigmoid"){
		
		std::cout<<"\napplyingSigmoid....\n" ; 
		z = applySigmoid(z) ;
	
	}	
	
	return z ; 	




} 

// squashes a number between 0 and 1 ; 

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
	for(int i =0 ;  i < result.rows ; i++) {	
                for (int j =0 ; j < result.cols ; j++) {
                        
                        result.data[i][j] = relu(m.data[i][j]) ;



                }


        }

	return result ; 
}


// randoNumber generation 
// this function generates a random matrix with values from -0.1 - 0.1 



Matrix randomNumberInitiator(int r, int c) {

	std::random_device rd ; // seed source 
	std::mt19937 gen(rd()) ; // gen produces raw numbers. rd seeds gen.
	std::uniform_real_distribution<double>dist(-0.1, 0.1) ;	//for small floats, dist shapes them into the range we want . 
			       // double x = dist(gen) ;you need to call dist(gen) to get a number 
	
	Matrix randMatrix ; 
	randMatrix.rows = r ; 
	randMatrix.cols = c  ;
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

Matrix multiplyMatrix(Matrix a, Matrix b) {
	// m*n , n*p 
	// resulting array should be 
	if ( a.cols != b.rows ) {
		return {} ; // returns an empty vector  
	}

	Matrix c ; 
	c.rows = a.rows ; 
	c.cols = b.cols ; 
	c.data = std::vector<std::vector<double>>(c.rows, std::vector<double>(c.cols,0.0)); 
	
	for (int i = 0 ; i < a.rows ; i++) {
		for (int j =0; j < b.cols ; j++) {
				double sum = 0 ; 
			for (int k = 0 ; k < a.cols ; k++) {
			 	sum = sum + a.data[i][k]* b.data[k][j]; 
			
			
			}
		
				c.data[i][j] = sum ; 
		
		}
	} 

	return c ;  



}

Matrix addMatrix (Matrix a, Matrix b) {

	Matrix c ; 
	c.rows = 1 ;
	c.cols =4 ; 
	c.data = std::vector< std::vector<double>>(c.rows, std::vector<double>(c.cols,0.0)) ; 




	// adding the matrices
	 
	for (int i =0; i < c.rows; i++ ) { 
		for (int j=0; j < c.cols; j++) {
			// adding and restoring  
			
			c.data[i][j] = a.data[i][j] + b.data[i][j]  ; 
		
		}
		std::cout<<"\n" ; 
	
	}


	return c ; 



} 



int main() {
	
	Matrix a ; 
	a.rows = 2; 
	a.cols = 2 ; 
	a.data = {{1,2},{3,4}} ; //initializing a matrix 
	std::cout<<"matrix a \n " ; 
	view(a) ; 
	Matrix b ; 
	b.rows = 2 ; 
	b.cols = 2 ;
	b.data = {{5,6},{7,8}}; 
	std::cout<<"matrix b\n" ; 
	view(b) ; 
	std::cout<<"\n" ; 
	
	std::cout<<"a*b:\n\n" ; 
	view(multiplyMatrix(a,b)) ; 
	
	Matrix c ; 
	c.rows = 2 ; 
	c.cols = 3 ; 
	c.data = {{1,2,3},{4,5,6}}; 
	std::cout<<"matrix c : \n  " ; 
	view(c) ;  
	// calling transposeMatrix func 
	
	Matrix transposedMatrix ;
	
	transposedMatrix.rows = c.cols ; 
	transposedMatrix.cols = c.rows ; 
	transposedMatrix.data = std::vector<std::vector<double>>(c.cols,std::vector<double>(c.rows,0.0)); // inititalizinng the matrix to zeroes   
	transposedMatrix  = transposeMatrix(c) ; 
	
	std::cout<<"\n tranposedMatrix\n\n :" ; 

	view(transposedMatrix) ; 	
		
		



	// random matrix for neural weights at the beginining 	
         
   	  Matrix randomMatrix = randomNumberInitiator(randomMatrix.rows, randomMatrix.cols) ;  
	  
	  std::cout<<"Randomised Matrix: \n\n" ;  
	  view(randomMatrix) ; 
	  
	 
	  std::cout<<"\n" ; 
	  Matrix d ; 
	  d.rows = 2 ; 
	  d.cols = 3 ; 
	  d.data = {{-2,-1,0}, 
	  	    {1,2,3}} ;
	  std::cout<<"Matrix d :\n" ; 
	  view(d) ; 

	  Matrix appliedSigmoidResult ; 
	  appliedSigmoidResult.rows  = d.rows ; 
	  appliedSigmoidResult.cols = d.cols ; 
	  appliedSigmoidResult.data = std::vector< std::vector<double>>(appliedSigmoidResult.rows, std::vector<double> (appliedSigmoidResult.cols,0.0)) ;	
	  appliedSigmoidResult=  applySigmoid(d) ; 
	  std::cout<<"\nappliedSigmoidResult: \n\n" ;  
	  
	  view(appliedSigmoidResult) ; 
		
	
	  Matrix appliedReluResult ; 
	  appliedReluResult.rows = d.rows ;
	  appliedReluResult.cols = d.cols ; 
	  appliedReluResult.data = std::vector<std::vector<double>>(appliedReluResult.rows, std::vector<double>(appliedReluResult.cols, 0.0)) ; 

	  std::cout<<"\nappliedReluResult\n\n" ; 
	  appliedReluResult = applyRelu(d) ; 
	  std::cout<<"appliedReluResult\n" ; 
		std::cout<<"\n" ; 
	  
	  

	// creating the first layer 
		  
 	  Matrix input ; 
	  input.rows = 1 ; 
	  input.cols = 3 ; 
	  input.data = {{1.0, 2.0, 3.0}} ; 	  
	  std::cout<<"First Layer input matrix or data for the first layer : \n" ; 
	  view(input) ; 

	  Layer firstLayer ;  
          
	  firstLayer.weights.rows = 4 ; 
	  firstLayer.weights.cols= 3 ;   
	  firstLayer.weights = randomNumberInitiator(firstLayer.weights.rows, firstLayer.weights.cols)  ; 
	  std::cout<<"\n Weights for first Layer!!\n"; 
	  view(firstLayer.weights) ;   
	  	
	 firstLayer.biases.rows = 4 ; 
	 firstLayer.biases.cols= 1 ; 
	 firstLayer.biases = randomNumberInitiator(firstLayer.biases.rows, firstLayer.biases.cols) ; 
	 std::cout<<"\nBiases!\n" ;
	 view(firstLayer.biases) ; 
	
         firstLayer.activation = "sigmoid" ; 

	  Matrix result  = forwardLayer(firstLayer, input) ; 
	  
	  std::cout<<"\nResultFromForward Layer\n" ;  
	  
	  view(result) ; 
	



}
