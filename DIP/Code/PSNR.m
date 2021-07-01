function psnrvalue = PSNR(origin_I,stego_I)
% 得到原始图像origin_I和载密图像stego_I的PSNR值
I1 = double(origin_I);
I2 = double(stego_I);
E = I1-I2;
MSE = mean2(E.*E);
if MSE == 0
    psnrvalue = -1;
else
    psnrvalue = 10*log10(255*255/MSE);
end