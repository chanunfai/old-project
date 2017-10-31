% The MNIST databse of handwritten digits --
% Yann LeCun -- NYU 
% Corinna Cortes -- Google 
% Chris J. C. Burges -- Microsoft Research  

load mnistdata;

% Visualize a selected train/test digit   

figure(1) 
n = 10; 
for i = 1:n*n 

   digit = train8(i,:);
   %digit = test8(i,:);

   digitImage = reshape(digit,28,28);

   subplot(n,n,i); 
   image(rot90(flipud(digitImage),-1)); 
   colormap(gray(256)); 
   axis square tight off; 

end 

% Visualize the average train digits   

T(1,:) = mean(train0); 
T(2,:) = mean(train1); 
T(3,:) = mean(train2); 
T(4,:) = mean(train3); 
T(5,:) = mean(train4); 
T(6,:) = mean(train5); 
T(7,:) = mean(train6); 
T(8,:) = mean(train7); 
T(9,:) = mean(train8); 
T(10,:) = mean(train9); 

for i = 1:10 
    digitImage_mean(:,:,i) = reshape(T(i,:),28,28);
end 

figure(2) 
for i = 1:10 
    subplot(2,5,i) 
    image(rot90(flipud(digitImage_mean(:,:,i)),-1)); 
    colormap(gray(256)); 
    axis square tight off; 
end

% A simple to identify a test digit is to compare its 
% pixels to those in each row of T and determine which row
% most closely resembles the test digit

% A more sophisticated approach is the PCA, which attempts
% to identify characteristic properties of each digit, based
% on trhe training data, and the compare these properties with 
% those of the test digit in order to make an identification

% More approaches can be found at
% http://yann.lecun.com/exdb/mnist/ 

