%% Centroid
mnistdata_upload_modified


%% Case 0
[row_0,col_0] = size(test0);
success_0 = 0;
failed_0 = 0;
for i = 1:row_0
    z = double(test0(i,:));
    dist = zeros(10,1);
    for k=1:10
        dist(k) = norm( z - T(k,:) );
    end
    [min_val,min_i] = min(dist);
    if min_i == 1
        success_0=success_0+1;
    else 
        failed_0=failed_0+1;
    end
end

SuccessRate_0 = success_0/row_0

%% Case 1
[row_1,col_1] = size(test1);
success_1 = 0;
failed_1 = 0;
for i = 1:row_1
    z = double(test1(i,:));
    dist = zeros(10,1);
    for k=1:10
        dist(k) = norm( z - T(k,:) );
    end
    [min_val,min_i] = min(dist);
    if min_i == 2
        success_1=success_1+1;
    else 
        failed_1=failed_1+1;
    end
end

SuccessRate_1 = success_1/row_1

%% Case 2
[row_2,col_2] = size(test2);
success_2 = 0;
failed_2 = 0;
for i = 1:row_2
    z = double(test2(i,:));
    dist = zeros(10,1);
    for k=1:10
        dist(k) = norm( z - T(k,:) );
    end
    [min_val,min_i] = min(dist);
    if min_i == 3
        success_2=success_2+1;
    else 
        failed_2=failed_2+1;
    end
end

SuccessRate_2 = success_2/row_2

%% Case 3
[row_3,col_3] = size(test3);
success_3 = 0;
failed_3 = 0;
for i = 1:row_3
    z = double(test3(i,:));
    dist = zeros(10,1);
    for k=1:10
        dist(k) = norm( z - T(k,:) );
    end
    [min_val,min_i] = min(dist);
    if min_i == 4
        success_3=success_3+1;
    else 
        failed_3=failed_3+1;
    end
end

SuccessRate_3 = success_3/row_3

%% Case 4
[row_4,col_4] = size(test4);
success_4 = 0;
failed_4 = 0;
for i = 1:row_4
    z = double(test4(i,:));
    dist = zeros(10,1);
    for k=1:10
        dist(k) = norm( z - T(k,:) );
    end
    [min_val,min_i] = min(dist);
    if min_i == 5
        success_4=success_4+1;
    else 
        failed_4=failed_4+1;
    end
end

SuccessRate_4 = success_4/row_4

%% Case 5
[row_5,col_5] = size(test5);
success_5 = 0;
failed_5 = 0;
for i = 1:row_5
    z = double(test5(i,:));
    dist = zeros(10,1);
    for k=1:10
        dist(k) = norm( z - T(k,:) );
    end
    [min_val,min_i] = min(dist);
    if min_i == 6
        success_5=success_5+1;
    else 
        failed_5=failed_5+1;
    end
end

SuccessRate_5 = success_5/row_5

%% Case 6
[row_6,col_6] = size(test6);
success_6 = 0;
failed_6 = 0;
for i = 1:row_6
    z = double(test6(i,:));
    dist = zeros(10,1);
    for k=1:10
        dist(k) = norm( z - T(k,:) );
    end
    [min_val,min_i] = min(dist);
    if min_i == 7
        success_6=success_6+1;
    else 
        failed_6=failed_6+1;
    end
end

SuccessRate_6 = success_6/row_6

%% Case 7
[row_7,col_7] = size(test7);
success_7 = 0;
failed_7 = 0;
for i = 1:row_7
    z = double(test7(i,:));
    dist = zeros(10,1);
    for k=1:10
        dist(k) = norm( z - T(k,:) );
    end
    [min_val,min_i] = min(dist);
    if min_i == 8
        success_7=success_7+1;
    else 
        failed_7=failed_7+1;
    end
end

SuccessRate_7 = success_7/row_7

%% Case 8
[row_8,col_8] = size(test8);
success_8 = 0;
failed_8 = 0;
for i = 1:row_8
    z = double(test8(i,:));
    dist = zeros(10,1);
    for k=1:10
        dist(k) = norm( z - T(k,:) );
    end
    [min_val,min_i] = min(dist);
    if min_i == 9
        success_8=success_8+1;
    else 
        failed_8=failed_8+1;
    end
end

SuccessRate_8 = success_8/row_8

%% Case 9
[row_9,col_9] = size(test9);
success_9 = 0;
failed_9 = 0;
for i = 1:row_9
    z = double(test9(i,:));
    dist = zeros(10,1);
    for k=1:10
        dist(k) = norm( z - T(k,:) );
    end
    [min_val,min_i] = min(dist);
    if min_i == 10
        success_9=success_9+1;
    else 
        failed_9=failed_9+1;
    end
end

SuccessRate_9 = success_9/row_9

