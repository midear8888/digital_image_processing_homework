function [I_eq, I_eq_pmf] = my_histeq(I)
    %MY_HISTEQ Performs histogram equalization.
    % Histogram equalization is a technique for adjusting image 
    % intensities to enhance contrast.
    % This is a self-implemented version of histogram equalization, 
    % rendering subtle differences between my_histeq and MATLAB 
    % built-in function histeq, actually, it's said that MATLAB histeq
    % is not a pure implementation of histogram equalization algorithm,
    % but an improved version.
    % Note: only support grayscale images by now.
    %
    % Inputs:
    %   - I: 2 dimensional array, typically an image in the 
    %           spatial domain
    %
    % Outputs：
    %   - I_eq: result image of histogram equalization
    %   - I_eq_pmf: possibility density function (or statistical result) of
    %               the result image
    %
    % Usage：
    %   - [I_eq, I_eq_pmf] = my_histeq(I)
    %
    % Created by Xingyi Li on Oct. 4, 2019.
    % Copyright © 2019 Huazhong University of Science and Technology. 
    % All rights reserved.
    
    % Convert to grayscale image
    if ndims(I) == 3
        I = rgb2gray(I);
    end
    [m, n] = size(I);
    % Compute the histogram of I
    pmf = my_imhist(I);
    % Compute cumulative distribution function
    cdf = cumsum(pmf);

    % Obtain the mapping relationship
    s = round(cdf*255);
    
    % Apply the result to image
    I_eq = I;
    for i = 0:255
        I_eq(I==i) = s(i+1);
    end
    
    I_eq_pmf = zeros(1, 256);
    % Compute the histogram
    for k = 0:255     
        I_eq_pmf(k+1) = length(find(I_eq==k))/(m*n);
    end
end

