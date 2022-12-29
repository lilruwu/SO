#ifndef _GRUPO_H
#define _GRUPO_H

#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/list.h>
#include <linux/time.h>
#include <linux/signal.h>
#include <asm/cputime.h>

extern int k;
extern int time;

extern int num_mantenimiento;
extern int num_administracion;
extern int num_anulacion;
extern int num_reserva;
extern int num_consulta;
extern int num_pago;

void contar_proceso(struct task_struct *p);
void colocar_proceso(struct task_struct *p, int tipo);
void actualizar_procesos(void);
void restar_contandor(struct task_struct *p);

#endif
