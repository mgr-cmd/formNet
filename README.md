# FormNet 

A football match predictor built from scratch . 



Computes team form and feeds into neural network to predict match outcomes. 
The neural network is built from scratch in C++ . 


Curious about the workings of neural networks, this project builds every
piece : matrix operations, forward pass, backpropagation, training . 

 
# Tech Stack 


- Go : data pipeline, feature engineering, CLI 
- C++ - matrix library, neural network 
- Data - EPL 23/24 season, 380 matches 


# Progress 

- Load CSV data into structure `Match` objects, Go 
- Compute form features : avg goals, win rate, points per game, Go 
- Random weight initialization, C++   
- 



## Data Pipeline, Go 
 
Reads raw CSV from 'football-data.co.uk', parses unstructured rows into 
structured 'Match' structures, and extract numeric features for the last 5
matches of any team.

# Matrix Library, C++ 

- Matrix struct with rows,cols, and 2D data 
- Addition 
- Transpose 
- Multiplication
- Random initialization, using std::random_device and std:: mt19937 

# How to Run 


## Go (data-pipeline) 

```bash 

go run match.go 




				  
Suggestions and feedback welcome. 
				  

