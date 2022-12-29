//#include <linux/grupoc.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/list.h>
#include <linux/time.h>
#include <linux/signal.h>
#include <asm/cputime.h>

int k = 5;
// Tiempo maximo de proceso = 1 minuto
int time = 15000;

int num_mantenimiento = 0;
int num_administracion = 0;
int num_anulacion = 0;
int num_reserva = 0;
int num_consulta = 0;
int num_pago = 0;

void contar_proceso(struct task_struct *p) 
{
    // Check the name of the process and update the corresponding count
    if (strncmp(p->comm, "mantenimiento", strlen("mantenimiento")) == 0) {
        num_mantenimiento++;
    } else if (strncmp(p->comm, "administracion", strlen("administracion")) == 0) {
        num_administracion++;
    } else if (strncmp(p->comm, "pago", strlen("pago")) == 0) {
        num_pago++;
    } else if (strncmp(p->comm, "anulacion", strlen("anulacion")) == 0) {
        num_anulacion++;
    } else if (strncmp(p->comm, "reserva", strlen("reserva")) == 0) {
        num_reserva++;
    } else if (strncmp(p->comm, "consulta", strlen("consulta")) == 0) {
        num_consulta++;
    }
}
// Llamada desde exec.c para colocar un proceso
void colocar_proceso(struct task_struct *p, int tipo)
{

    int procesos = 0;
    contar_proceso(p);
    procesos = num_administracion + num_anulacion + num_consulta + num_mantenimiento + num_reserva + num_pago;

    printk(KERN_ALERT "numero_procesos: %d", procesos);	

    if (procesos > k)
    {

	    printk(KERN_ALERT "Cola llena, buscando proceso a eliminar\n");

        if (num_consulta > 0) {
            if (tipo < 5) {
                struct task_struct *aux;

                for_each_process(aux) {
                    if (strncmp(aux->comm, "consulta", strlen("consulta")) == 0) {
                        printk(KERN_ALERT "Eliminando proceso %s %d", aux->comm, aux->pid);
						if (kill_pid(find_vpid(aux->pid),SIGKILL,0) != 0) {
							// Error al eliminar el proceso
							printk(KERN_ALERT "Error al eliminar proceso consulta\n");
						}
                        //num_consulta--;
                        break;
                    }
                }
            	return;
            }
        } else if (num_anulacion > 0 || num_reserva > 0) {
            if (tipo < 4) {
                struct task_struct *aux;

                for_each_process(aux) {
                    if (strncmp(aux->comm, "anulacion", strlen("anulacion")) == 0) {
                        printk(KERN_ALERT "Eliminando proceso %s %d", aux->comm, aux->pid);
						if (kill_pid(find_vpid(aux->pid),SIGKILL,0) != 0) {
						    // Error al eliminar el proceso
					        printk(KERN_ALERT "Error al eliminar proceso de anulacion\n");
					    }
					    break;
                    } 
                    else if (strncmp(aux->comm, "reserva", strlen("reserva"))) {
				        printk(KERN_ALERT "Eliminando proceso %s %d", aux->comm, aux->pid);
				        if (kill_pid(find_vpid(aux->pid),SIGKILL,0) != 0) {
							// Error al eliminar el proceso
							printk(KERN_ALERT "Error al eliminar proceso de reserva\n");
						}
				        break;
			        }
                        break;
                }
            }
            	return;
	    }
        else if (num_pago > 0) {
            if (tipo < 3) {
                struct task_struct *aux;

                for_each_process(aux) {
                    if (strncmp(aux->comm, "pago", strlen("pago")) == 0) {
                        printk(KERN_ALERT "Eliminando proceso %s %d", aux->comm, aux->pid);
						if (kill_pid(find_vpid(aux->pid),SIGKILL,0) != 0) {
							// Error al eliminar el proceso
							printk(KERN_ALERT "Error al eliminar proceso pago\n");
						}
                        //num_pago--;
                        break;
                    }
                }
            	return;
	        }
        } else if (num_administracion > 0) {
            if (tipo < 2) {
                struct task_struct *aux;

                for_each_process(aux) {
                    if (strncmp(aux->comm, "administracion", strlen("administracion")) == 0) {
                        printk(KERN_ALERT "Eliminando proceso %s %d", aux->comm, aux->pid);
						if (kill_pid(find_vpid(aux->pid),SIGKILL,0) != 0) {
							// Error al eliminar el proceso
							printk(KERN_ALERT "Error al eliminar proceso administracion\n");
						}
                        //num_administracion--;
                        break;
                    }
                }
		        return;
            }
        }
        printk(KERN_ALERT "No se pudo meter en la cola :(\n");
        
        if (strncmp(p->comm, "mantenimiento", strlen("mantenimiento")) == 0)    	
        {
            if (kill_pid(find_vpid(p->pid),SIGKILL,0) != 0) {
                // Error al eliminar el proceso
                printk(KERN_ALERT "Error al eliminar proceso mantenimiento\n");
            }
            //num_mantenimiento++;
            return;
        }
        //else if (strcmp(proceso->comm, "administracion") == 0)
        else if (strncmp(p->comm, "administracion", strlen("administracion")) == 0)	
        {
            if (kill_pid(find_vpid(p->pid),SIGKILL,0) != 0) {
                // Error al eliminar el proceso
                printk(KERN_ALERT "Error al eliminar proceso administracion\n");
            }
            //num_administracion++;
            return;
        }
        else if (strncmp(p->comm, "pago", strlen("pago")) == 0)	
        {
            if (kill_pid(find_vpid(p->pid),SIGKILL,0) != 0) {
                // Error al eliminar el proceso
                printk(KERN_ALERT "Error al eliminar proceso pago\n");
            }
            //num_pago++;
            return;
        }
        else if (strncmp(p->comm, "reserva", strlen("reserva")) == 0)	
        {
            if (kill_pid(find_vpid(p->pid),SIGKILL,0) != 0) {
                // Error al eliminar el proceso
                printk(KERN_ALERT "Error al eliminar proceso reserva\n");
            }
            //num_reserva++;
            return;
        }
        else if (strncmp(p->comm, "anulacion", strlen("anulacion")) == 0)	
        {
            if (kill_pid(find_vpid(p->pid),SIGKILL,0) != 0) {
                // Error al eliminar el proceso
                printk(KERN_ALERT "Error al eliminar proceso anulacion\n");
            }
            //num_anulacion++;
            return;
        }
        else if (strncmp(p->comm, "consulta", strlen("consulta")) == 0)	
        {
            if (kill_pid(find_vpid(p->pid),SIGKILL,0) != 0) {
                // Error al eliminar el proceso
                printk(KERN_ALERT "Error al eliminar proceso consulta\n");
            }
            //num_consulta++;
            return;
        }

	    return;
    }

    return;
}

// Llamada desde scheduler_tick en core.c para comprobar el tiempo que lleva vivo un proceso
void actualizar_procesos() {
	
	struct task_struct *aux;

	printk(KERN_ALERT "num_administracion: %d | num_anulacion: %d | num_consulta: %d | num_mantenimiento: %d | num_pago: %d | num_reserva: %d \n", num_administracion, num_anulacion, num_consulta, num_mantenimiento, num_pago, num_reserva);    

	

    for_each_process(aux) {
        if (strncmp(aux->comm, "administracion", strlen("administracion")) == 0) {
            cputime_t utime = aux->utime;
            cputime_t stime = aux->stime;

            // Calculamos el tiempo total de CPU utilizado por el proceso
            cputime_t total_time = utime + stime;

            if (total_time > time) {
                printk(KERN_ALERT "Time out :(\n");
				if (kill_pid(find_vpid(aux->pid),SIGKILL,0) != 0) {
					// Error al eliminar el proceso
					printk(KERN_ALERT "Error al eliminar proceso administracion\n");
				}
            }

        } else if (strncmp(aux->comm, "mantenimiento", strlen("mantenimiento")) == 0) {
            cputime_t utime = aux->utime;
            cputime_t stime = aux->stime;

            // Calculamos el tiempo total de CPU utilizado por el proceso
            cputime_t total_time = utime + stime;

            if (total_time > time) {
                printk(KERN_ALERT "Time out :(\n");
				if (kill_pid(find_vpid(aux->pid),SIGKILL,0) != 0) {
					// Error al eliminar el proceso
					printk(KERN_ALERT "Error al eliminar proceso mantenimiento\n");
				}
            }
        } else if (strncmp(aux->comm, "pago", strlen("pago")) == 0) {
            cputime_t utime = aux->utime;
            cputime_t stime = aux->stime;

            // Calculamos el tiempo total de CPU utilizado por el proceso
            cputime_t total_time = utime + stime;

            if (total_time > time) {
                printk(KERN_ALERT "Time out :(\n");
				if (kill_pid(find_vpid(aux->pid),SIGKILL,0) != 0) {
					// Error al eliminar el proceso
					printk(KERN_ALERT "Error al eliminar proceso pago\n");
				}
            }
        } else if (strncmp(aux->comm, "reserva", strlen("reserva")) == 0) {
            cputime_t utime = aux->utime;
            cputime_t stime = aux->stime;

            // Calculamos el tiempo total de CPU utilizado por el proceso
            cputime_t total_time = utime + stime;

            if (total_time > time) {
                printk(KERN_ALERT "Time out :(\n");
				if (kill_pid(find_vpid(aux->pid),SIGKILL,0) != 0) {
					// Error al eliminar el proceso
					printk(KERN_ALERT "Error al eliminar proceso reserva\n");
				}
            }
        } else if (strncmp(aux->comm, "anulacion", strlen("anulacion")) == 0) {
            cputime_t utime = aux->utime;
            cputime_t stime = aux->stime;

            // Calculamos el tiempo total de CPU utilizado por el proceso
            cputime_t total_time = utime + stime;

            if (total_time > time) {
                printk(KERN_ALERT "Time out :(\n");
				if (kill_pid(find_vpid(aux->pid),SIGKILL,0) != 0) {
					// Error al eliminar el proceso
					printk(KERN_ALERT "Error al eliminar proceso anulacion\n");
				}
            }
        } else if (strncmp(aux->comm, "consulta", strlen("consulta")) == 0) {
            cputime_t utime = aux->utime;
            cputime_t stime = aux->stime;

            // Calculamos el tiempo total de CPU utilizado por el proceso
            cputime_t total_time = utime + stime;

            if (total_time > time) {
                printk(KERN_ALERT "Time out :(\n");
				if (kill_pid(find_vpid(aux->pid),SIGKILL,0) != 0) {
					// Error al eliminar el proceso
					printk(KERN_ALERT "Error al eliminar proceso consulta\n");
				}
            }
        }
    }
}

// Llamada desde do_exit en exit.c para restar 1 a los contadores
void restar_contandor(struct task_struct *aux) {
    if (strncmp(aux->comm, "administracion", strlen("administracion")) == 0) {
	    //if (num_administracion != 0) {
	        num_administracion--;
	        printk(KERN_ALERT "Eliminado un proceso administracion\n");
	    //}        
	    return;
    } else if (strncmp(aux->comm, "mantenimiento", strlen("mantenimiento")) == 0) {
        //if (num_mantenimiento != 0) {
	        num_mantenimiento--;
	        printk(KERN_ALERT "Eliminado un proceso mantenimiento\n");
	    //}
	    return;
    } else if (strncmp(aux->comm, "pago", strlen("pago")) == 0) {
        //if (num_pago != 0) {    
            num_pago--;
		    printk(KERN_ALERT "Eliminado un proceso pago\n");
        //}
        return;
    } else if (strncmp(aux->comm, "reserva", strlen("reserva")) == 0) {
        //if (num_reserva != 0) {    
            num_reserva--;
		    printk(KERN_ALERT "Eliminado un proceso reserva\n");
        //}
        return;
    } else if (strncmp(aux->comm, "anulacion", strlen("anulacion")) == 0) {
        //if (num_anulacion != 0) {
            num_anulacion--;
		    printk(KERN_ALERT "Eliminado un proceso anulacion\n");
        //}
        return;
    } else if (strncmp(aux->comm, "consulta", strlen("consulta")) == 0) {
        //if (num_consulta != 0) {
            num_consulta--;
		    printk(KERN_ALERT "Eliminado un proceso consulta\n");
        //}
		return;
    }
	return;
}