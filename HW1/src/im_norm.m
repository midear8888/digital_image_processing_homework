function I_norm = im_norm(I)
    %IM_NORM Normalizes the input image I.
    %
    % Inputs:
    %   - I: 2 dimensional array, typically an image in the spatial domain
    %
    % Outputs：
    %   - I_norm: normalized image
    %
    % Usage：
    %   - I_norm = im_norm(I)
    %
    % Created by Xingyi Li on Oct. 12, 2019.
    % Copyright © 2019 Huazhong University of Science and Technology. 
    % All rights reserved.
    
    I = double(I);
    I_max = max(I, [], 'all');
    I_min = min(I, [], 'all');
    I_norm = (I - I_min)/(I_max-I_min);
end