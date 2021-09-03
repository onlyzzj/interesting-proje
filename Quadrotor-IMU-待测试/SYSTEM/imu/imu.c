#include <math.h>   
#include "imu.h"
#include "math.h"
#include "mpu6050.h"
#include "hmc5883l.h"
//GY86的陀螺仪、加速度计、磁力计X、Y、Z轴正方向一致（X,Y,Z组成右手坐标系），旋转的正方向可用右手螺旋定则判定
//单位四元数与欧拉角(有奇异点)、旋转矩阵(它不可以把右手坐标系改变成左手坐标系或反之)是等价的.





float q[4];                      //四元数中的四个元(四元数是由四个元构成的数)
float a_x,a_y,a_z,m_x,m_y,m_z;
float Roll,Pitch,Yaw;




void Data_Change(void)
{
  a_x=(float)acc.x;
	a_y=(float)acc.y;
	a_z=(float)acc.z;
	m_x=(float)mag.x;
	m_y=(float)mag.y;
	m_z=(float)mag.z;
}







//机体坐标系、地理坐标系是笛卡尔坐标系(右手坐标系)
void IMU_Init(void)
{
	float Roll_Init,Pitch_Init,Yaw_Init;


	MPU6050_Data_Read();
	MPU6050_Data_Compose();
	HMC5883L_Data_Read();
	HMC5883L_Data_Compose();	
	MPU6050_Acc_Gram(acc.x,acc.y,acc.z);                 //加速度计数据由16位ADC值转为g. 

	
	
	//以GY-86坐标轴的X轴正方向为机头，Y轴正方向为机左翼，Z轴正方向垂直于飞机向上
	//(欧拉角转化为四元数)和(四元数转化为欧拉角)跟轴向的定义有关,陀螺仪也好、加速度计也好、磁力计也好,它们的轴向都要满足右手定理.
	//如何确定旋转角度的正方向,用右手握住坐标轴,拇指指向轴向的正方向,四个指头弯曲的方向就是旋转角度的正方向.在初始化四元数时,计算出的初始化欧拉角的正方向也要满足这个条件.	
	//(Roll_Init、Pitch_Init、Yaw_Init)初始化欧拉角的单位是弧度
	Roll_Init=atan2(Acc_gram_y,Acc_gram_z);                                                                                                                                                 //横滚角     
	Pitch_Init=-asin(Acc_gram_x);                                                                                                                                                           //俯仰角
	Yaw_Init=atan2(mag.x*cos(Pitch_Init)+mag.z*sin(Pitch_Init),mag.x*sin(Roll_Init)*sin(Pitch_Init)+mag.y*cos(Roll_Init)-mag.z*sin(Roll_Init)*cos(Pitch_Init)); //等价于atan2(mag.x,mag.y)   //航向角
				            
       	
	
	
	//(欧拉角转化为四元数)将初始化欧拉角转换成初始化四元数.
	//(右手坐标系)在笛卡尔坐标系下,按照Z、Y、X顺序旋转,Qzyx=Qz*Qy*Qx.注意sin(?)的位置的不同,可以确定绕X、Y、Z轴转动是Pitch还是Roll还是Yaw.
	//(Roll_Init、Pitch_Init、Yaw_Init)初始化欧拉角的单位是弧度
	q[0]=cos(0.5f*Yaw_Init)*cos(0.5f*Pitch_Init)*cos(0.5f*Roll_Init)+sin(0.5f*Yaw_Init)*sin(0.5f*Pitch_Init)*sin(0.5f*Roll_Init);          //W
	q[1]=cos(0.5f*Yaw_Init)*cos(0.5f*Pitch_Init)*sin(0.5f*Roll_Init)-sin(0.5f*Yaw_Init)*sin(0.5f*Pitch_Init)*cos(0.5f*Roll_Init);          //X   绕X轴旋转是Roll
	q[2]=cos(0.5f*Yaw_Init)*sin(0.5f*Pitch_Init)*cos(0.5f*Roll_Init)+sin(0.5f*Yaw_Init)*cos(0.5f*Pitch_Init)*sin(0.5f*Roll_Init);          //Y   绕Y轴旋转是Pitch
	q[3]=sin(0.5f*Yaw_Init)*cos(0.5f*Pitch_Init)*cos(0.5f*Roll_Init)-cos(0.5f*Yaw_Init)*sin(0.5f*Pitch_Init)*sin(0.5f*Roll_Init);          //Z   绕Z轴旋转是Yaw	 
}





//加速度计数据(acc_x,acc_y,acc_z)由ADC值直接代入
//陀螺仪数据(gyro_x,gyro_y,gyro_z)由ADC值转为弧度/每秒代入 
//磁力计数据(mag_x,mag_y,mag_z)由ADC值直接代入
void IMU_Update(float acc_x,float acc_y,float acc_z,float gyro_x,float gyro_y,float gyro_z,float mag_x,float mag_y,float mag_z) 
{
	float ax,ay,az,hx,hy,hz,bx,by,bz,vx,vy,vz,wx,wy,wz,ex,ey,ez,exInt,eyInt,ezInt;
	float acc_norm,mag_norm,q_norm;
	
	
	
	
	
	//通过加速度计(测量)的重力数据,计算出重力(模为1)在机体坐标系X、Y、Z轴上的分量.                                                                         (机体坐标系)
	acc_norm=sqrt(acc_x*acc_x+acc_y*acc_y+acc_z*acc_z);       
	acc_x=acc_x/acc_norm;
	acc_y=acc_y/acc_norm;
	acc_z=acc_z/acc_norm;





	//通过磁力计(测量)的磁场数据,计算出磁场(模为1)在机体坐标系X、Y、Z轴上的分量.                                                                           (机体坐标系)
	mag_norm=sqrt(mag_x*mag_x+mag_y*mag_y+mag_z*mag_z);          
	mag_x=mag_x/mag_norm;
	mag_y=mag_y/mag_norm;
	mag_z=mag_z/mag_norm;  




//地理坐标系(东北天):    1.重力永远是(0,0,1)单位是G.    2.磁场永远是(0,cos(x),sin(x))单位是Guess.
	


//	//利用从机体坐标系转换到地理坐标系的四元数旋转矩阵公式,把重力(模为1)在机体坐标系X、Y、Z轴上的分量转化为在地理坐标系X、Y、Z轴上的分量.                    (地理坐标系)
//	nx=acc_x*(q[0]*q[0]+q[1]*q[1]-q[2]*q[2]-q[3]*q[3])+acc_y*2*(q[1]*q[2]-q[0]*q[3])+acc_z*2*(q[1]*q[3]+q[0]*q[2]);
//	ny=acc_x*2*(q[1]*q[2]+q[0]*q[3])+acc_y*(q[0]*q[0]-q[1]*q[1]+q[2]*q[2]-q[3]*q[3])+acc_z*2*(q[2]*q[3]-q[0]*q[1]);
//	nz=acc_x*2*(q[1]*q[3]-q[0]*q[2])+acc_y*2*(q[2]*q[3]+q[0]*q[1])+acc_z*(q[0]*q[0]-q[1]*q[1]-q[2]*q[2]+q[3]*q[3]); 
	
	
	
	ax=0;
	ay=0;
	az=1;






	//利用从机体坐标系转换到地理坐标系的四元数旋转矩阵公式,把磁场(模为1)在机体坐标系X、Y、Z轴上的分量转化为在地理坐标系X、Y、Z轴上的分量.                      (地理坐标系)
	hx=mag_x*(q[0]*q[0]+q[1]*q[1]-q[2]*q[2]-q[3]*q[3])+mag_y*2*(q[1]*q[2]-q[0]*q[3])+mag_z*2*(q[1]*q[3]+q[0]*q[2]);
	hy=mag_x*2*(q[1]*q[2]+q[0]*q[3])+mag_y*(q[0]*q[0]-q[1]*q[1]+q[2]*q[2]-q[3]*q[3])+mag_z*2*(q[2]*q[3]-q[0]*q[1]);
	hz=mag_x*2*(q[1]*q[3]-q[0]*q[2])+mag_y*2*(q[2]*q[3]+q[0]*q[1])+mag_z*(q[0]*q[0]-q[1]*q[1]-q[2]*q[2]+q[3]*q[3]); 
	
	
	
	
	bx=0;                                                                          //X轴正方向为正东               
	by=sqrt(hx*hx+hy*hy);                                                          //Y轴正方向为正北
	bz=hz;                                                                         //Z轴正方向为天





	//利用从地理坐标系转换到机体坐标系的四元数旋转矩阵公式,把重力(模为1)在地理坐标系X、Y、Z轴上的分量转化为在机体坐标系X、Y、Z轴上的分量,从而(推算)重力数据,该重力数据利用(陀螺仪更新的四元数)得出.(机体坐标系)	
	vx=ax*(q[0]*q[0]+q[1]*q[1]-q[2]*q[2]-q[3]*q[3])+ay*2*(q[1]*q[2]+q[0]*q[3])+az*2*(q[1]*q[3]-q[0]*q[2]);
	vy=ax*2*(q[1]*q[2]-q[0]*q[3])+ay*(q[0]*q[0]-q[1]*q[1]+q[2]*q[2]-q[3]*q[3])+az*2*(q[2]*q[3]+q[0]*q[1]);
	vz=ax*2*(q[1]*q[3]+q[0]*q[2])+ay*2*(q[2]*q[3]-q[0]*q[1])+az*(q[0]*q[0]-q[1]*q[1]-q[2]*q[2]+q[3]*q[3]); 






	//利用从地理坐标系转换到机体坐标系的四元数旋转矩阵公式,把磁场(模为1)在地理坐标系X、Y、Z轴上的分量转化为在机体坐标系X、Y、Z轴上的分量,从而(推算)磁场数据,该磁场数据利用(陀螺仪更新的四元数)得出.(机体坐标系)
	wx=bx*(q[0]*q[0]+q[1]*q[1]-q[2]*q[2]-q[3]*q[3])+by*2*(q[1]*q[2]+q[0]*q[3])+bz*2*(q[1]*q[3]-q[0]*q[2]);
	wy=bx*2*(q[1]*q[2]-q[0]*q[3])+by*(q[0]*q[0]-q[1]*q[1]+q[2]*q[2]-q[3]*q[3])+bz*2*(q[2]*q[3]+q[0]*q[1]);
	wz=bx*2*(q[1]*q[3]+q[0]*q[2])+by*2*(q[2]*q[3]-q[0]*q[1])+bz*(q[0]*q[0]-q[1]*q[1]-q[2]*q[2]+q[3]*q[3]); 





	//(四元数叉乘公式)把加速度计(测量)的重力分量和利用(陀螺仪更新的四元数)(推算)的重力分量做叉积,把磁力计(测量)的磁场分量和利用(陀螺仪更新的四元数)(推算)的磁场分量做叉积,算出(加速度计、磁力计)与(陀螺仪)的误差,拿来修正陀螺仪.(机体坐标系)                                                                     (机体坐标系)
	ex=(acc_y*vz-acc_z*vy)+(mag_y*wz-mag_z*wy);
	ey=(acc_z*vx-acc_x*vz)+(mag_z*wx-mag_x*wz);
	ez=(acc_x*vy-acc_y*vx)+(mag_x*wy-mag_y*wx);





	//积分增益(Ki)                  
	exInt=exInt+ex*Ki;
	eyInt=eyInt+ey*Ki;
	ezInt=ezInt+ez*Ki;





	//比例增益(Kp)                 
	gyro_x=gyro_x+Kp*ex+exInt;
	gyro_y=gyro_y+Kp*ey+eyInt;
	gyro_z=gyro_z+Kp*ez+ezInt;






	//四元数微分方程的一阶龙格-库塔法公式-----更新四元数(只用了陀螺仪,所以产生了陀螺仪积分误差)
	q[0]=q[0]+(-q[1]*gyro_x-q[2]*gyro_y-q[3]*gyro_z)*halfT;
	q[1]=q[1]+(q[0]*gyro_x-q[3]*gyro_y+q[2]*gyro_z)*halfT;
	q[2]=q[2]+(q[3]*gyro_x+q[0]*gyro_y-q[1]*gyro_z)*halfT;
	q[3]=q[3]+(-q[2]*gyro_x+q[1]*gyro_y+q[0]*gyro_z)*halfT;  






	//化为单位四元数,表示旋转矩阵的四元数必须是单位四元数.
	q_norm=sqrt(q[0]*q[0]+q[1]*q[1]+q[2]*q[2]+q[3]*q[3]);
	q[0]=q[0]/q_norm;
	q[1]=q[1]/q_norm;
	q[2]=q[2]/q_norm;
	q[3]=q[3]/q_norm;




	//(右手坐标系)在笛卡尔坐标系下,按照Z、Y、X顺序旋转,Qzyx=Qz*Qy*Qx.注意sin(?)的位置的不同,可以确定绕X、Y、Z轴转动是Pitch还是Roll还是Yaw.
	//(四元数转化为欧拉角)
	Roll=atan2(2*q[2]*q[3]+2*q[0]*q[1],q[0]*q[0]+q[3]*q[3]-q[1]*q[1]-q[2]*q[2])*57.3f;            //横滚角     绕X轴转动    表示机左翼与水平线的夹角          范围:-180到+180
	Pitch=asin(2*q[0]*q[2]-2*q[1]*q[3])*57.3f;                                                    //俯仰角     绕Y轴旋转	   表示机头正方向与水平线的夹角      范围:-90到+90
	Yaw=atan2(2*q[1]*q[2]+2*q[0]*q[3],q[0]*q[0]+q[1]*q[1]-q[2]*q[2]-q[3]*q[3])*57.3f;             //航向角     绕Z轴转动	   表示机头正方向与正北方的夹角      范围:-180到180
}














//前提:地理坐标系和机体坐标系通过旋转能完全重合
//A************************************************************从机体坐标系转换到地理坐标系的四元数旋转矩阵公式**************************************************************//
//	          |(q[0]*q[0]+q[1]*q[1]-q[2]*q[2]-q[3]*q[3])           2*(q[1]*q[2]-q[0]*q[3])                         2*(q[1]*q[3]+q[0]*q[2])              |
//	          |        2*(q[1]*q[2]+q[0]*q[3])            (q[0]*q[0]-q[1]*q[1]+q[2]*q[2]-q[3]*q[3])                2*(q[2]*q[3]-q[0]*q[1])              |
//	          |        2*(q[1]*q[3]-q[0]*q[2])                     2*(q[2]*q[3]+q[0]*q[1])                (q[0]*q[0]-q[1]*q[1]-q[2]*q[2]+q[3]*q[3])     |







//B************************************************************从地理坐标系转换到机体坐标系的四元数旋转矩阵公式**************************************************************//
//	          |(q[0]*q[0]+q[1]*q[1]-q[2]*q[2]-q[3]*q[3])           2*(q[1]*q[2]+q[0]*q[3])                         2*(q[1]*q[3]-q[0]*q[2])              |
//	          |        2*(q[1]*q[2]-q[0]*q[3])            (q[0]*q[0]-q[1]*q[1]+q[2]*q[2]-q[3]*q[3])                2*(q[2]*q[3]+q[0]*q[1])              |
//	          |        2*(q[1]*q[3]+q[0]*q[2])                     2*(q[2]*q[3]-q[0]*q[1])                (q[0]*q[0]-q[1]*q[1]-q[2]*q[2]+q[3]*q[3])     |





//B是A的转置矩阵


