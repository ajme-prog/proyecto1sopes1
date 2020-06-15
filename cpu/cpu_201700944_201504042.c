
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/hugetlb.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include<linux/sched.h>
#include <linux/sched/signal.h>

#define BUFSIZE 150

//struct task_struct datos;  //struct para manejar la informacion del usuario
//esto con insmod

struct task_struct *task ;
 struct task_struct *child;
     struct list_head *list;

static int escribirarchivo(struct seq_file *archivo, void *v) {
 

seq_printf(archivo, "----------------------------------------------------\n");
seq_printf(archivo, "|                                                  |\n");
seq_printf(archivo, "| Alan Joel Morataya Escobar                       |\n");
seq_printf(archivo, "| 201700944                                        |\n");
seq_printf(archivo, "| Julio Estuardo Gomez Alonzo                      |\n");
seq_printf(archivo, "| 201504042                                        |\n");
seq_printf(archivo, "|                                                  |\n");
seq_printf(archivo, "|                Proyecto 1                        |\n");
seq_printf(archivo, "|                   CPU                            |\n");
seq_printf(archivo, "|                                                  |\n");
seq_printf(archivo, "----------------------------------------------------\n");

seq_printf(archivo, "--------------LISTA DE PROCESOS --------------------\n");

 for_each_process( task ) {
     seq_printf(archivo,"\nPID: %d\n", task->pid);
     seq_printf(archivo,"NOMBRE: %s\n",task->comm);
     seq_printf(archivo, "ESTADO: %li\n", task->state);


     list_for_each(list, &task->children)
     {

       child = list_entry(list, struct task_struct, sibling);
       seq_printf(archivo,"\tNOMBRE DEL HIJO: %s  PID:%d    ESTADO: %li\n", child->comm, child->pid,child->state);
            
       }


        }

return 0;

}
/*
 int escribir2(struct seq_file *archivo) {
   
for_each_process(task) {
     seq_printf(archivo,"\nPID: %d\n", task->pid);
     seq_printf(archivo,"NOMBRE: %s\n",task->comm);
     seq_printf(archivo, "ESTADO: %li\n", task->state);


     struct task_struct *child;
     struct list_head *list;
     list_for_each(list, &task->children)
     {


       child = list_entry(list, struct task_struct, sibling);
       seq_printf(archivo,"\tNOMBRE DEL HIJO: %s  PID:%d    ESTADO: %li\n", child->comm, child->pid,child->state);
            
       }


        }
        return 0;
}

*/
static int hello_proc_open(struct inode *inode, struct  file *file) {
 //  seq_printf(file,"--------------LISTA DE PROCESOS --------------------\n");
  return single_open(file, escribirarchivo, NULL);
}

static const struct file_operations hello_proc_fops = {
  
  .open = hello_proc_open,
  .read = seq_read
};

static int inicio(void)
{
    //al cargar imprimimos el carnet
     proc_create("cpu_201700944_201504042", 0, NULL, &hello_proc_fops);
        printk(KERN_INFO "Nombre:  Alan Joel Morataya Escobar\n");
        printk(KERN_INFO "Nombre:  Julio Estuardo Gomez Alonzo\n");
        return 0;
}

//esto con rmmod
static void salir(void)
{
    //al salir imprimo el nombre del curso
     remove_proc_entry("cpu_201700944_201504042", NULL);

        printk(KERN_INFO "Curso: Sistemas Operativos 1\n");
 // return 0;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alan201700944");
MODULE_DESCRIPTION("Modulo para mostrar la informacion del CPU");


module_init(inicio);
module_exit(salir);

//MODULESUPPORTEDDEVICE("eltiodelavara");