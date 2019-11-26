% 1. Histogram equalization
I = imread('image.jpg');
I_gray = rgb2gray(I);
% Self-implemented function my_histeq
[I_eq, I_eq_pdf] = my_histeq(I_gray);
% MATLAB built-in function histeq
matlab_ans = histeq(I_gray);

figure(3);
subaxis(2, 3, 1, 'Spacing', 0.02, 'Padding', 0.03, 'Margin', 0)
imshow(I_gray)
title('Original grayscale image')

subaxis(2, 3, 2, 'Spacing', 0.02, 'Padding', 0.03, 'Margin', 0)
imshow(matlab_ans)
title('MATLAB histeq')

subaxis(2, 3, 3, 'Spacing', 0.02, 'Padding', 0.03, 'Margin', 0)
imshow(I_eq)
title('My histeq')

subaxis(2, 3, 4, 'Spacing', 0.02, 'Padding', 0.03, 'Margin', 0)
bar(my_imhist(I_gray))
title('Histogram of original grayscale image')

subaxis(2, 3, 5, 'Spacing', 0.02, 'Padding', 0.03, 'Margin', 0)
bar(my_imhist(matlab_ans))
title('Histogram of MATLAB histeq')

subaxis(2, 3, 6, 'Spacing', 0.02, 'Padding', 0.03, 'Margin', 0)
bar(my_imhist(I_eq))
title('Histogram of my histeq')

figure(4), imshow(I_eq);

% 2. Homomorphic filtering
% Define some tunable parameters which profoundly affect the performance
% of homomorphic filtering technique that can result in remarkable effects
% as long as these parameters are tuned well
rH = 2; rL = 0.1; c = 0.5; D0 = 10000;

% Apply homomorphic filtering technique to image
I_homo = homo_filter(I, rH, rL, c, D0);

figure(5),
subaxis(2, 3, 1, 'Spacing', 0.02, 'Padding', 0.03, 'Margin', 0)
imshow(I_gray)
title('Original grayscale image')

subaxis(2, 3, 2, 'Spacing', 0.02, 'Padding', 0.03, 'Margin', 0)
imshow(matlab_ans)
title('MATLAB histeq')

subaxis(2, 3, 3, 'Spacing', 0.02, 'Padding', 0.03, 'Margin', 0)
imshow(I_homo, [])
title('Homomorphic filtering')

subaxis(2, 3, 4, 'Spacing', 0.02, 'Padding', 0.03, 'Margin', 0)
bar(my_imhist(I_gray))
title('Histogram of original grayscale image')

subaxis(2, 3, 5, 'Spacing', 0.02, 'Padding', 0.03, 'Margin', 0)
bar(my_imhist(matlab_ans))
title('Histogram of MATLAB histeq')

subaxis(2, 3, 6, 'Spacing', 0.02, 'Padding', 0.03, 'Margin', 0)
bar(my_imhist(I_homo))
title('Histogram of homomorphic filtering')

figure(6), imshow(I_homo);