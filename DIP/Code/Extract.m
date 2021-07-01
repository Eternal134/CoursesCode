function [recover_I,exD] = Extract(stego_I,num,PK,Z)
% 函数说明：在载密图像中提取信息
% 输入：stego_I（载密图像）,num（秘密数据个数）,PK（峰值点）,Z（零值点）
% 输出：recover_I（回复图像）,exD（提取的秘密数据）

[m,n] = size(stego_I); %统计图像的行列数
recover_I = stego_I;
exD = zeros();
%% 根据峰值点PK和零值点Z提取信息
t = 0; %计数，提取信息的个数
for i=1:m
    for j=1:n
        if t >= num %秘密信息已提取结束
            break;
        end
        if recover_I(i,j)>PK+1 && recover_I(i,j)<=Z %将峰值点PK+1和零值点Z之间的像素向左平移
            recover_I(i,j) = recover_I(i,j) - 1;
        elseif recover_I(i,j)==PK %提取0
            recover_I(i,j) = recover_I(i,j);
            t = t+1;
            exD(t) = 0;
        elseif recover_I(i,j)==PK+1 %提取1
            recover_I(i,j) = recover_I(i,j)-1;
            t = t+1;
            exD(t) = 1;   
        end
    end
end