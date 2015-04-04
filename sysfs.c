/*
	A simple sysfs interface
*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sysfs.h>
#include <linux/string.h>
#include <linux/kobject.h>


static int x;
static int y;


static size_t my_show(struct kobject *kobj,struct kobj_attribute *attr,const char *buf)
{
	printk(KERN_ALERT"\n show method x value is %d \n",x);
	return 1;
}

static size_t my_store(struct kobject *kobj,struct kobj_attribute *attr,const char *buf,size_t count)
{
	x=100;
	printk(KERN_ALERT"\n store method x value is %d \n",x);
	return count;
}

static struct kobj_attribute my_attribute = __ATTR(start,0666,my_show,my_store);

static struct attribute *attrs[]= {
	&my_attribute.attr,
	NULL,
};

static struct attribute_group attr_group = {
	.attrs=attrs,
};


static struct kobject *my_kobj;

static int __init jk_init(void)
{
	int ret;

	my_kobj=kobject_create_and_add("kobject_example",kernel_kobj);
	if(!my_kobj)
		return -ENOMEM;
	
	ret=sysfs_create_group(my_kobj,&attr_group);
	if(ret)
		kobject_put(my_kobj);
	
	printk("\n sysfs  created \n");

	return ret;
}

static void __exit jk_exit(void)
{
	printk("\n EXIT module \n");
	kobject_put(my_kobj);
}


module_init(jk_init);
module_exit(jk_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("JAGADEESH PAGADALA");
MODULES_DESCRIPTION("A simple sysfs interface"):
