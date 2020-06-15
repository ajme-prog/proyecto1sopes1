
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/hugetlb.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>



#define BUFSIZE  150


struct sysinfo datos;  //struct para manejar la informacion del usuario
//esto con insmod


static int escribirarchivo(struct seq_file *arch, void *v) {
si_meminfo(&datos);
long memoriatotal=(datos.totalram *4);
long memorialibre=(datos.freeram *4);

seq_printf(arch,"----------------------------------------------------\n");
seq_printf(arch,"| Laboratorio Sistemas Operativos 1                |\n");
seq_printf(arch,"| Escuela de vacaciones Junio 2020                 |\n");
seq_printf(arch,"| Alan Joel Morataya Escobar                       |\n");
seq_printf(arch,"| 201700944                                        |\n");
seq_printf(arch,"| Julio Estuardo Gomez Alonzo                      |\n");
seq_printf(arch,"| 201504042                                        |\n");
seq_printf(arch,"|                                                  |\n");
seq_printf(arch,"|                Proyecto 1                        |\n");
seq_printf(arch,"|                MEMORIA RAM                       |\n");
seq_printf(arch,"|                                                  |\n");
seq_printf(arch,"|                                                  |\n");
seq_printf(arch,"----------------------------------------------------\n");
seq_printf(arch,"Sistema Operativo: Ubuntu 18.04\n");
seq_printf(arch,"Memoria total: \t %8lu MB \n",memoriatotal/1024); //falta pasarlo a megas
seq_printf(arch,"Memoria libre: \t %8lu MB \n",memorialibre/1024);
seq_printf(arch,"Memoria en uso: \t %ld  %%\n",((memoriatotal-memorialibre)*100)/memoriatotal);
return 0;

}


static int hello_proc_open(struct inode *inode, struct  file *file) {
  return single_open(file, escribirarchivo, NULL);
}

static const struct file_operations hello_proc_fops = {
  
  .open = hello_proc_open,
  .read = seq_read
};

static int inicio(void)
{
    //al cargar imprimimos el carnet
     proc_create("memo_201700944_201504042", 0, NULL, &hello_proc_fops);
        printk(KERN_INFO "Carnet:  201700944\n");
  printk(KERN_INFO "Carnet:  201504042\n");

        
        return 0;
}

//esto con rmmod
static void salir(void)
{
    //al salir imprimo el nombre del curso
     remove_proc_entry("memo_201700944_201504042", NULL);

        printk(KERN_INFO "Curso: Sistemas Operativos 1\n");
 // return 0;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alan201700944");
MODULE_DESCRIPTION("Modulo para mostrar la informacion de la RAM");


module_init(inicio);
module_exit(salir);

//MODULESUPPORTEDDEVICE("eltiodelavara");