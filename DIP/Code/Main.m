clear %释放系统内存
clc   %清除命名窗口数据

%% 产生稳定随机数
num = 1000;
seed = 0; %设置种子,保证产生稳定的随机数
rand('seed',seed); 
Data = round(rand(1,num)*1);%随机产生01比特，作为嵌入的数据
%Data=randi([0 1],100);%随机产生01比特，作为嵌入的数据
%% 读入Lena图像并生成直方图
origin_I = double(imread('Lena.tiff')); %读入Lena图像
hist_ori_I = tabulate(origin_I(:)); %对Lena图像各个像素值进行统计
subplot(111); %创建画板
bar(hist_ori_I(:,2),0.1); %绘制hist_ori_I的直方图
% 2是择矩阵hist_ori_I第二列的数值，0.1表示横坐标的宽度
title('原始直方图'); %设置标题 
%% 寻找峰值点
[m,n] = size(hist_ori_I); %提取矩阵hist_ori_I的行值和列值
PK = 0;
num_PK = 0; %记录峰值点像素的个数，即最大嵌入数据个数
for i=1:m   
    if num_PK < hist_ori_I(i,2)       
        PK = hist_ori_I(i,1);
        num_PK = hist_ori_I(i,2);
    end    
end
%% 寻找零值点
% 当零点和峰值点不相邻时，将零点和峰值点之间的图像像素右移一个单位
for i=PK+1:m
    if hist_ori_I(i,2)==0 %找峰值点PK后面的第一个零点 
        Z = hist_ori_I(i,1);
        break;
    end
end
%% 嵌入函数  
[stego_I,emD] = Embed(origin_I,Data,PK,Z);
hist_stego_I = tabulate(stego_I(:)); %对Lena图像各个像素值进行统计
figure; %重新打开一个窗口
subplot(111); %创建画板
bar(hist_stego_I(:,2),0.1); %绘制hist_stego_I的直方图
title('载密直方图'); %设置标题 
%% 提取函数 
[recover_I,exD] = Extract(stego_I,num,PK,Z);
%% 图像对比
figure;
subplot(221);imshow(origin_I,[]);title('原始图像');
subplot(222);imshow(stego_I,[]);title('载密图像');
subplot(223);imshow(recover_I,[]);title('恢复图像');
%% 判断结果是否正确
isequal(emD,exD)
isequal(origin_I,recover_I)
psnrvalue = PSNR(origin_I,stego_I) %求PSNR值