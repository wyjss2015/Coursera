function [C, sigma] = dataset3Params(X, y, Xval, yval)
%EX6PARAMS returns your choice of C and sigma for Part 3 of the exercise
%where you select the optimal (C, sigma) learning parameters to use for SVM
%with RBF kernel
%   [C, sigma] = EX6PARAMS(X, y, Xval, yval) returns your choice of C and 
%   sigma. You should complete this function to return the optimal C and 
%   sigma based on a cross-validation set.
%

% You need to return the following variables correctly.
C = 1;
sigma = 0.3;

% ====================== YOUR CODE HERE ======================
% Instructions: Fill in this function to return the optimal C and sigma
%               learning parameters found using the cross validation set.
%               You can use svmPredict to predict the labels on the cross
%               validation set. For example, 
%                   predictions = svmPredict(model, Xval);
%               will return the predictions on the cross validation set.
%
%  Note: You can compute the prediction error using 
%        mean(double(predictions ~= yval))
%
list_C = [0.01 0.03 0.1 0.3 1 3 10 30];
list_sigma = [0.01 0.03 0.1 0.3 1 3 10 30];
min_error = 1.0;
for i = 1:length(list_C)
	for j = 1:length(list_sigma)
		temp_C = list_C(i);
		temp_sigma = list_sigma(j);
		model = svmTrain(X, y, temp_C, @(x1, x2) gaussianKernel(x1, x2, temp_sigma));
		predictions = svmPredict(model, Xval);
		temp_error = mean(double(predictions ~= yval));
		if temp_error < min_error
			min_error = temp_error;
			C = temp_C;
			sigma = temp_sigma;
		end
	end
end






% =========================================================================

end
