% Read image
img = imread('image.jpg');
% Switch to grayscale image
img_gray = rgb2gray(img);

% 1. Histogram of the input image
% Compute and display the histogram of the input image using
% self-implemented function my_imhist, and make a comparison with MATLAB
% built-in function histogram
figure(1);
subplot(1, 2, 1), bar(my_imhist(img_gray), 'g')
title('My imhist')
xlabel('Grayscale Value')
ylabel('Probability')

subplot(1, 2, 2), histogram(img_gray, 256, 'Normalization', 'probability')
title('MATLAB built-in histogram')
xlabel('Grayscale Value')
ylabel('Probability')

% 2. Discrete fourier transform
% Utilize self-implemented dft2 function to compute the discrete
% fourier transform of the input image without the help of MATLAB
% built-in function

% MATLAB built-in fft2
F = fftshift(fft2(img_gray));
F_mag = abs(F);
F_phase = angle(F)*180/pi;

% MATLAB built-in ifft2
f = ifft2(fftshift(F));

% Self-implemented dft2
img_dft2 = fftshift(my_dft2(img_gray));
magnitude = abs(img_dft2);
phase = angle(img_dft2)*180/pi;

% Self-implemented idft2
img_idft2 = my_idft2(fftshift(img_dft2));

% Using subaxis from File Exchange to reduce the margins
figure(2);
subaxis(2, 4, 1, 'Spacing', 0.02, 'Padding', 0.01, 'Margin', 0), ...
    imshow(img_gray), title('Original grayscale image');
subaxis(2, 4, 2, 'Spacing', 0.02, 'Padding', 0.01, 'Margin', 0), ...
    imshow(log(F_mag+1), []), title('MATLAB fft2 magnitude spectrum');
subaxis(2, 4, 3, 'Spacing', 0.02, 'Padding', 0.01, 'Margin', 0), ...
    imshow(F_phase, []), title('MATLAB fft2 phase spectrum');
subaxis(2, 4, 4, 'Spacing', 0.02, 'Padding', 0.01, 'Margin', 0), ...
    imshow(f, []), title('MATLAB ifft2');
subaxis(2, 4, 5, 'Spacing', 0.02, 'Padding', 0.01, 'Margin', 0), ...
    imshow(img_gray), title('Original grayscale image');
subaxis(2, 4, 6, 'Spacing', 0.02, 'Padding', 0.01, 'Margin', 0), ...
    imshow(log(magnitude+1), []), title('My dft2 magnitude spectrum');
subaxis(2, 4, 7, 'Spacing', 0.02, 'Padding', 0.01, 'Margin', 0), ...
    imshow(phase, []), title('My dft2 phase spectrum');
subaxis(2, 4, 8, 'Spacing', 0.02, 'Padding', 0.01, 'Margin', 0), ...
    imshow(img_idft2, []), title('My idft2');


