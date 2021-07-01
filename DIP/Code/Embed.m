function [stego_I,emD] = Embed(origin_I,Data,PK,Z)
% 函数说明：根据峰值点和零值点嵌入信息
% 输入：origin_I（原始图像）,Data（秘密数据）,PK（峰值点）,Z（零值点）
% 输出：stego_I（载密图像）,emD（嵌入的秘密信息）

[m,n] = size(origin_I); %统计图像的行列数
num = numel(Data); %秘密信息个数
stego_I = origin_I;
%% 根据峰值点PK和零值点Z嵌入信息
t = 0; %计数，嵌入信息的个数
for i=1:m
    for j=1:n
        if t >= num %秘密信息已嵌完
            break;
        end
        if stego_I(i,j)>PK && stego_I(i,j)<Z %将峰值点PK和零值点Z之间的像素向右平移
            stego_I(i,j) = stego_I(i,j) + 1;
        elseif stego_I(i,j)==PK
            t = t+1;
            stego_I(i,j) = stego_I(i,j) + Data(t);
        end
    end
end
%% 统计嵌入的秘密信息
emD = Data(1:t);
end