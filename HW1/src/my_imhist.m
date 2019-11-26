function pmf = my_imhist(I)
    %MY_IMHIST Computes and display the histogram of the input image I.
    % Virtually identical to the MATLAB built-in functions.
    % Note: only support grayscale images by now.
    %
    % Inputs:
    %   - I: 2 dimensional array, typically an image in the 
    %           spatial domain
    %
    % Outputs：
    %   - pmf：probability density function of I
    %
    % Usage：
    %   - my_imhist(I)
    %   - pmf = my_imhist(I)
    %
    % Created by Xingyi Li on Oct. 3, 2019.
    % Copyright © 2019 Huazhong University of Science and Technology. 
    % All rights reserved.
    
    % Convert to grayscale image
    if ndims(I) == 3
        I = rgb2gray(I);
    end
    
    [m, n] = size(I);
    pmf = zeros(1,256);
    % Compute the histogram
    for k = 0:255     
        pmf(k+1) = length(find(I==k))/(m*n);
    end
end