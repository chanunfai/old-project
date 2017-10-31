
% Matlab script to illustrate the application of SVD
% for image compression 

load durer % Albrecht Durer (1471-1528)'s Melencolia 
figure(1) 
colormap(gray(128)); 
image(X)
X0 = X; 
axis image
axis off
title('Melencolia, Durer (1514)') 

load detail % the detail of the magic square 
figure(2) 
colormap(gray(64)); 
image(X)
axis image
axis off
title('Magic Sqaure')

% ---- PCA (image compression) 

[m,n] = size(X); 
[U,S,V] = svd(X,0);
sigma = diag(S); 

r1 = 1; 
X1 = sigma(1)*U(:,1)*V(:,1)'; 
cr1 = (m+n)*r1/(m*n);  % compression ratio

r2 = 20; 
X2 = U(:,1:r2)*S(1:r2,1:r2)*V(:,1:r2)'; 
cr2 = (m+n)*r2/(m*n);  

r3 = 60; 
X3 = U(:,1:r3)*S(1:r3,1:r3)*V(:,1:r3)'; 
cr3 = (m+n)*r3/(m*n);  

figure(3)
subplot(2,2,1) 
colormap(gray(64)); 
image(X)
axis image
axis off
title('original'); 

subplot(2,2,2) 
colormap(gray(64)); 
image(X1)
axis image
axis off
title('rank = 1, cr = 0.0055'); 

subplot(2,2,3) 
colormap(gray(64)); 
image(X2)
axis image
axis off
title('rank = 20, cr = 0.1096'); 

subplot(2,2,4) 
colormap(gray(64)); 
image(X3)
axis image
axis off
title('rank = 60, cr = 0.3289'); 
