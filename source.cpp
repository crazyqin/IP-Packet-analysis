#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main()
{
	int count = 0;
	FILE *fp;


	int frame_long[1];
	int frame_true_long;

	unsigned char ip_ver_long;
	int ip_ver;
	int ip_headlength;

	unsigned char ip_total_long[2];
	int ip_total_true_long;

	unsigned char ip_src_ip[4];
	unsigned char ip_dst_ip[4];

	unsigned char mf_df;
	int mf;
	int df;

	unsigned char proto;

	unsigned char ttl;


	char file[20];
	printf("请输入读入文件名:");
	scanf("%s",file);

	char filew[20];
	printf("请输入输出文件名:");
	scanf("%s",filew);

	if ((fp=fopen(file,"rb"))==NULL)
	{
		printf("cannot open this file\n");
		return 0;
	}


FILE *fpw;
fpw=fopen(filew,"a+");
fprintf(fpw,"序号  帧长   IP版本  首部长  DF  MF  协议类型   TTL   数据报长    源地址    目标地址\n");


	int size ;
	 fseek(fp,0,SEEK_END);
 size = ftell(fp);          

//跳过文件头
	fseek(fp,24L,0);

	while(size!=ftell(fp))
	{
		count++;

//得到帧长度
	fseek(fp,12L,1);
	fread (frame_long,4,1,fp);
	frame_true_long =frame_long[0];

//跳过MAC
	fseek(fp,12L,1);

//08 00 判断 

	if (fgetc(fp)!=8)
	{
		fseek(fp,frame_true_long-13,1);
		continue;
	}

	if (fgetc(fp)!=0)
	{
		fseek(fp,frame_true_long-14,1);
		continue;
	}



//IP版本 头大小
	ip_ver_long=fgetc(fp);
	ip_ver=ip_ver_long>>4;
	ip_headlength=(ip_ver_long&(15))*4;

//区分服务
	fseek(fp,1L,1);

//总长度
	char str1[256];
	fread (ip_total_long,2,1,fp);
	int temp;
	temp=ip_total_long[1];
	ip_total_long[1]=ip_total_long[0];
	ip_total_long[0]=temp;
	sprintf(str1, "%d",*ip_total_long);
	//ip_total_true_long=;
//	fseek(fp,2L,1);

//标识
	fseek(fp,2L,1);


	/*

	标志

	*/

	//标志位
	mf_df=fgetc(fp);
	df=(mf_df>>7)&1;
	mf=(mf_df>>6)&1;

//跳过片偏移量
		fseek(fp,1L,1);

//生存时间
		ttl=fgetc(fp);

//协议
		proto=fgetc(fp);



//源地址
	fseek(fp,2L,1);
	fread (ip_src_ip,4,1,fp);


//目的地址
	fread (ip_dst_ip,4,1,fp);





//跳过选择字段+填充位+数据
	fseek(fp,-34,1);


	fseek(fp,frame_true_long,1);


//输出
	/*
	printf("%d\n",count);
	printf("帧长:%d\n",frame_true_long);
	printf("IP版本:%d 首部长：%d\n",ip_ver,ip_headlength);
	printf("DF:%d\n",df);
	printf("MF:%d\n",mf);

	switch (proto)
		{
		case 1: printf("协议:ICMP\n"); break;
		case 2: printf("协议:IGMP\n");break;
		case 6: printf("协议:TCP\n");break;
		case 17:printf("协议:UDP\n");break;
		case 88:printf("协议:IGRP\n"); break;
		case 89:printf("协议:OSPF\n"); break;
		default: printf("协议:未知\n");break;
		}
	printf("TTL:%d\n",ttl);
	printf("数据报长度:%s\n",str1);
	printf("源地址:%d.%d.%d.%d\n",ip_src_ip[0],ip_src_ip[1],ip_src_ip[2],ip_src_ip[3]);
	printf("目标地址:%d.%d.%d.%d\n",ip_dst_ip[0],ip_dst_ip[1],ip_dst_ip[2],ip_dst_ip[3]);
	printf("\n");
*/


fprintf(fpw,"%d      ",count);
fprintf(fpw,"%d      ",frame_true_long);
fprintf(fpw,"%d      %d     ",ip_ver,ip_headlength);
fprintf(fpw,"%d   ",df);
fprintf(fpw,"%d     ",mf);
	switch (proto)
		{
		case 1: fprintf(fpw,"ICMP       "); break;
		case 2: fprintf(fpw,"IGMP       ");break;
		case 6: fprintf(fpw,"TCP       ");break;
		case 17:fprintf(fpw,"UDP       ");break;
		case 88:fprintf(fpw,"IGRP       "); break;
		case 89:fprintf(fpw,"OSPF       "); break;
		default:fprintf(fpw,"未知       ");break;
		}
fprintf(fpw,"%d       ",ttl);
fprintf(fpw,"%s    ",str1);
fprintf(fpw,"%d.%d.%d.%d  ",ip_src_ip[0],ip_src_ip[1],ip_src_ip[2],ip_src_ip[3]);
fprintf(fpw,"%d.%d.%d.%d\n",ip_dst_ip[0],ip_dst_ip[1],ip_dst_ip[2],ip_dst_ip[3]);


	};


//结束
printf("输出成功\n");
system("pause");

	fclose(fp);
	fclose(fpw);
	return 0;


}