#ifndef _ZIP_MEM_H_
#define _ZIP_MEM_H_


/*
��������: ѹ���ڴ�,ѹ��������ݴ����mem_outptr��ָ��Ŀռ�
����˵��:
mem_inptr: ��ѹ�����ڴ�ָ�룬���û��ṩ����ռ�
mem_insize: ��ѹ�����ڴ泤��
mem_outptr: ѹ������ڴ�ָ��, ���û��ṩ����ռ�
����ֵ:
ѹ������ڴ泤��
*/
int zipmem( char * mem_inptr, int mem_insize, char * mem_outptr );

/*
��������: ��ѹ��, ��ѹ��������ݴ����mem_outptr��ָ��Ŀռ�
����˵��:
mem_inptr: ѹ������ڴ�ָ�룬���û��ṩ����ռ�
mem_insize: ѹ������ڴ泤��
mem_outptr: ��ѹ������ڴ�ָ��, ���û��ṩ����ռ�
����ֵ:
��ѹ�����ڴ泤��
*/
int unzipmem( char * mem_inptr, int mem_insize, char * mem_outptr );

#endif 