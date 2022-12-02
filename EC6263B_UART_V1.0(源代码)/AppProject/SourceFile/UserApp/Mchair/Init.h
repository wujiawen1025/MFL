/****************************************************************
    Copyright(c) 2007-2008, XIAMEN COMFORT SCIENCE & TECHNOLOGY GROUP CO., LTD
    
    模块名称(Filename):       INIT.h  
    项目名称(Projectname):       
    版本号(Version):	      
    创建日期(Date):           2008-7-15        
    作者(Author):             FS
    功能描述(Description):    用于外部调用 初始化 函数
    其他说明(Others):         包括时钟、端口、通讯、存储空间、中断     
    修改记录(History):
****************************************************************/

#ifndef		_INIT_H
#define		_INIT_H

extern		void		Init_SysTick(void);
extern		void		Init_RTC(void);
extern		void		Init_FTM(void);
extern		void		Init_Port(void);
extern		void		Init_Serial(void);
extern		void		Init_Ram(void);
extern		void		Init_System(void);

extern		void		Init_AD(void);

#endif

