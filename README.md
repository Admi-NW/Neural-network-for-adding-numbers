# Neural-network-for-adding-numbers
Simple neural network for adding numbers using standart C++ libraries 

Adding numbers is a simple linear problem, so i would use identity activation func f(x) = x.
The identity activation function simply outputs the input, which makes it a weighted sum of the inputs 
in backpropagation, bcs f'(x) = 1 (to use linear activation func i shouldn't use activation func ;D)
But to use this neural network for another simple tasks I reccomend u to add new activation function

In C++ code I have used four libraries: <iostream>, <vector>, <random>, <sstream> - for advanced string interaction.
I've created my own Matrix class and implemented neural network from scratch using it.
