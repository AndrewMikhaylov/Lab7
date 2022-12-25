
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>
MODULE_AUTHOR("Andrew Mikhaylov");
MODULE_DESCRIPTION("Lab 6");
MODULE_LICENSE("GPL");
static unsigned int hello_times = 1;
module_param(hello_times, uint, S_IRUGO);
MODULE_PARM_DESC(hello_times, "Number of times Hello, World! Will be printed");
struct event_list {
	struct list_head list;
	ktime_t event_time;
};

static struct list_head event_list_head;

static LIST_HEAD(event_list_head);

void new_event(int);

static int __init hello_init(void)
{
	if (hello_times == 0 || (hello_times >= 5 && hello_times <= 10)) {
	printk(KERN_WARNING "Parameter is 0 or between 5and10");
	}
	
	BUG_ON(hello_times > 10);
	
	int i;
	for (i = 0; i < hello_times; i++) {
		
		printk(KERN_EMERG "Hello, World!\n");
		new_event(i);
	}
	return 0;
}

static void __exit hello_exit(void) {
	struct event_list *md, *tmp;
	list_for_each_entry_safe(md, tmp, &event_list_head, list) {
		printk(KERN_EMERG "Time: %lld\n", md->event_time);
		list_del(&md->list);
	kfree(md);
	}
}

void new_event(int i) {
	struct event_list *element = NULL;
	element = kmalloc(sizeof(struct event_list), GFP_KERNEL);
	
	if(i==5){
		BUG();
	}
	
	element->event_time = ktime_get();
	list_add_tail(&element->list, &event_list_head); // Attention
}

module_init(hello_init);
module_exit(hello_exit);
