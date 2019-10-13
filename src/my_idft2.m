function f_xy = my_idft2(F_uv)
    %MY_IDFF2 Computes the inverse discrete fourier transform.
    % Virtually identical to the MATLAB built-in function.
    % Note: only support grayscale images by now.
    %
    % Inputs:
    %   - F_uv: 2 dimensional array, typically an image in the
    %           frequency domain
    %
    % Outputs：
    %   - f_xy：inverse discrete fourier transform of F_uv,
    %           yielding an image existing in the spatial domain
    %
    % Usage：
    %   - f_xy = idfft2(F_uv)
    %
    % Created by Xingyi Li on Oct. 4, 2019.
    % Copyright © 2019 Huazhong University of Science and Technology. 
    % All rights reserved.
    
    % Convert to grayscale image
    if ndims(F_uv) == 3
        F_uv = rgb2gray(F_uv);
    end

    % Get the size of the F_uv
    [nrows, ncols] = size(F_uv);

    % Vectorized implementation of column-wise IFT
    vy = (0:nrows-1)' * (0:nrows-1);
    M_vy = exp(1i*2*pi*vy/nrows);
    f_uy = M_vy * F_uv;

    % Vectorized implementation of row-wise IFT
    ux = (0:ncols-1)' * (0:ncols-1);
    M_ux = exp(1i*2*pi*ux/ncols);
    f_xy = real(f_uy * M_ux / (ncols*nrows));
end