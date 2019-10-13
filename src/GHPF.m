function H = GHPF(I, rH, rL, c, D0)
    %GHPF Gaussian high-pass filter.
    %
    % Inputs:
    %   - I: 2 dimensional array, typically an image in the spatial domain
    %   - rH: high values
    %   - rL: low values
    %   - c: affects the exponential in H. It is like a tug of war between
    %           D0 and c, working in different ranges. 
    %   - D0: size of the gaussian filter, affects more/less frequencies
    %
    % Outputs：
    %   - H: gaussian high-pass filter of the input image I
    %
    % Usage：
    %   - H = GHPF(I, rH, rL, c, D0)
    %
    % Created by Xingyi Li on Oct. 12, 2019.
    % Copyright © 2019 Huazhong University of Science and Technology. 
    % All rights reserved.
    
    % Convert to grayscale image
    if ndims(I) == 3
        I = rgb2gray(I);
    end
    [M, N] = size(I);

    % Record the midpoint of the image
    m = floor(M/2);
    n = floor(N/2);
    
    H = zeros(M, N);
    % Calculate gaussian high-pass filter H(u,v)
    for u = 1:M
        for v = 1:N
            D2_uv = (u-m)^2+(v-n)^2;
            H(u,v) = (rH-rL)*(1-exp(-c*(D2_uv/(D0^2))))+rL;
        end
    end
end