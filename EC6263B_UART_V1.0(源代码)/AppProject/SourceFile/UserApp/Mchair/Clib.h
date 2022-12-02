/****************************************************************
    Copyright(c) 2007-2008, XIAMEN COMFORT SCIENCE & TECHNOLOGY GROUP CO., LTD
    
    模块名称(Filename):       Clib.h  
    项目名称(Projectname):       
    版本号(Version):	      
    创建日期(Date):           2008-7-15        
    作者(Author):             FS
    功能描述(Description):    用于外部调用 库函数及延时函数
    其他说明(Others):         
                         RamSet(Uchar *, Uchar , Uchar) —— 对内存空间付值
                         Uchar IsZeroTrue(Uchar * , Uchar) —— 判断数据是否等于0
                         Uchar IsSameTrue(Uchar * , Uchar , Uchar) —— 判断数据是否等于某值
    修改记录(History):
****************************************************************/

#ifndef		_CLIBRARY_H
#define		_CLIBRARY_H

extern	 void	 RamSet(Uchar *, Uchar , Uchar );
extern	 Uchar	 IsZeroTrue(Uchar * , Uchar );
extern	 Uchar	 IsSameTrue(Uchar * , Uchar , Uchar );
extern	 void	 Delay5us(void);
extern	 void	 Delay5ms(void);
extern	 void	 Delay50ms(void);
extern	 void	 Delay200ms(void);
extern	 void	 Delay500ms(void);

#endif
