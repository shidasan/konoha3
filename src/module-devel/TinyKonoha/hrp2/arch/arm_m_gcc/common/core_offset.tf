$ ======================================================================
$
$   TOPPERS/HRP Kernel
$       Toyohashi Open Platform for Embedded Real-Time Systems/
$       High Reliable system Profile Kernel
$
$   Copyright (C) 2011-2012 by Embedded and Real-Time Systems Laboratory
$               Graduate School of Information Science, Nagoya Univ., JAPAN
$  
$   �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
$   �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
$   �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
$   (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
$       ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
$       ����������˴ޤޤ�Ƥ��뤳�ȡ�
$   (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
$       �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
$       �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
$       ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
$   (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
$       �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
$       �ȡ�
$     (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
$         �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
$     (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
$         ��𤹤뤳�ȡ�
$   (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
$       ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
$       �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
$       ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
$       ���դ��뤳�ȡ�
$  
$   �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
$   ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
$   ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
$   �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
$   ����Ǥ�����ʤ���
$
$ =====================================================================

$
$       ���ե��åȥե����������ѥƥ�ץ졼�ȥե������ARM-M�ѡ�
$

$
$  ���ե��å��ͤΥޥ������������
$
$DEFINE("TCB_p_tinib", offsetof_TCB_p_tinib)$
$DEFINE("TCB_texptn", offsetof_TCB_texptn)$
$DEFINE("TCB_pc", offsetof_TCB_pc)$

$DEFINE("TINIB_exinf", offsetof_TINIB_exinf)$
$DEFINE("TINIB_task", offsetof_TINIB_task)$

$
$  �ӥåȥ��ե��å������Υޥ������������
$
$DEFINE_BIT("TCB_enatex", sizeof_TCB, "B")$

$DEFINE("TINIB_sstksz", offsetof_TINIB_TSKINICTXB_sstksz)$
$DEFINE("TINIB_sstk_bottom", offsetof_TINIB_TSKINICTXB_sstk_bottom)$
$DEFINE("TINIB_ustksz", offsetof_TINIB_TSKINICTXB_stksz)$
$DEFINE("TINIB_ustk_bottom", offsetof_TINIB_TSKINICTXB_stk_bottom)$
$DEFINE("TINIB_start_ustk", offsetof_TINIB_TSKINICTXB_start_ustk)$
$DEFINE("TINIB_atrsz_ustk", offsetof_TINIB_TSKINICTXB_atrsz_ustk)$

$DEFINE("TINIB_p_dominib", offsetof_TINIB_p_dominib)$
$DEFINE("TINIB_texrtn", offsetof_TINIB_texrtn)$
$DEFINE("TCB_svclevel", offsetof_TCB_svclevel)$
$DEFINE_BIT("TCB_waifbd", sizeof_TCB, "B")$
$DEFINE("TCB_ssp", offsetof_TCB_ssp)$
$DEFINE("TCB_usp", offsetof_TCB_usp)$
$DEFINE("TCB_priv_mode", offsetof_TCB_priv_mode)$

$DEFINE("DOMINIB_p_dominib_info", offsetof_DOMINIB_p_dominib_info)$
$DEFINE("DOMINIB_domptn", offsetof_DOMINIB_domptn)$
$DEFINE("DOMINIB_start_rom", offsetof_DOMINIB_start_rom)$
$DEFINE("DOMINIB_atrsz_rom", offsetof_DOMINIB_atrsz_rom)$
$DEFINE("DOMINIB_start_ram", offsetof_DOMINIB_start_ram)$
$DEFINE("DOMINIB_atrsz_ram", offsetof_DOMINIB_atrsz_ram)$
$DEFINE("DOMINIB_start_srpw", offsetof_DOMINIB_start_srpw)$
$DEFINE("DOMINIB_atrsz_srpw", offsetof_DOMINIB_atrsz_srpw)$
$DEFINE("DOMINIB_start_mem", offsetof_DOMINIB_start_mem)$
$DEFINE("DOMINIB_atrsz_mem", offsetof_DOMINIB_atrsz_mem)$

