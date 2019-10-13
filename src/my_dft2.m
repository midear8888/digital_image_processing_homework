function F_uv = my_dft2(f_xy)
    %MY_DFF2 Computes the discrete fourier transform.
    % Virtually identical to the MATLAB built-in function.
    % Note: only support grayscale images by now.
    %
    % Inputs:
    %   - f_xy: 2 dimensional array, typically an image in the 
    %           spatial domain
    %
    % Outputs：
    %   - F_uv：discrete fourier transform of f_xy, yielding an 
    %           image existing in the frequency domain
    %
    % Usage：
    %   - F_uv = dfft2(f_xy)
    %
    % Created by Xingyi Li on Oct. 4, 2019.
    % Copyright © 2019 Huazhong University of Science and Technology. 
    % All rights reserved.

    % Convert to grayscale image
    if ndims(f_xy) == 3
        f_xy = rgb2gray(f_xy);
    end
    % Switch integer to double
    f_xy = double(f_xy);
    % Get the size of the image
    [nrows, ncols] = size(f_xy);

    % Vectorized implementation of column-wise FT
    vy = (0:nrows-1)' * (0:nrows-1);
    M_vy = exp(-1i*2*pi*vy/nrows);
    F_xv = M_vy * f_xy;

    % Vectorized implementation of row-wise FT
    ux = (0:ncols-1)' * (0:ncols-1);
    M_ux = exp(-1i*2*pi*ux/ncols);
    F_uv = F_xv * M_ux;
end