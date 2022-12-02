/****************************************************************
    Copyright(c) 2007-2008, XIAMEN COMFORT SCIENCE & TECHNOLOGY GROUP CO., LTD
    
    ģ������(Filename):       Clib.h  
    ��Ŀ����(Projectname):       
    �汾��(Version):	      
    ��������(Date):           2008-7-15        
    ����(Author):             FS
    ��������(Description):    �����ⲿ���� �⺯������ʱ����
    ����˵��(Others):         
                         RamSet(Uchar *, Uchar , Uchar) ���� ���ڴ�ռ丶ֵ
                         Uchar IsZeroTrue(Uchar * , Uchar) ���� �ж������Ƿ����0
                         Uchar IsSameTrue(Uchar * , Uchar , Uchar) ���� �ж������Ƿ����ĳֵ
    �޸ļ�¼(History):
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
