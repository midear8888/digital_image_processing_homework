function I_homo = homo_filter(I, rH, rL, c, D0)
    %HOMO_FILTER Performs homomorphic filtering.
    % Homomorphic filtering is a generalized technique for 
    % signal and image processing, involving a nonlinear mapping
    % to a different domain in which linear filter techniques are 
    % applied, followed by mapping back to the original domain.
    % Gaussian high-pass filter is adopted to simultaneously 
    % normalize the brightness across an image and increase contrast,
    % which can be written as follows:
    % H(u,v) = (rH-rL)*[1-exp(-c*(D(u,v)^2/D0^2))]+rL
    % Note: only support grayscale images by now.
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
    %   - I_homo：image enhanced by homomorphic filtering
    %
    % Usage：
    %   - I_homo = homo_filter(I, rH, rL, c, D0)
    %
    % Created by Xingyi Li on Oct. 3, 2019.
    % Copyright © 2019 Huazhong University of Science and Technology. 
    % All rights reserved.
    
    % Convert to grayscale image
    if ndims(I) == 3
        I = rgb2gray(I);
    end
    I = double(I);
    
    % Apply log function, turning the multiplicative components into additive
    % components
    ln_I = log(I+1);
    % Perform self-implemented function my_dft2
    F = my_dft2(ln_I);
    H = GHPF(I, rH, rL, c, D0);
    
    % Apply gaussian high-pass filter
    HF = H.*F;
    % Inverse fourier transform
    ln_hf = my_idft2(HF);
    % Perform exponential function for the sake of image retrieval
    intermediate = exp(ln_hf)-1;
    % Normalization
    intermediate = im_norm(intermediate);
    % Image retrieval
    I_homo = uint8(round(intermediate*255));
end