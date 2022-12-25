ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m := hello.o
ccflags-y += -g # add debugging info
else
# normal makefile
	KDIR ?= $$HOME/repos/linux-stable
default:
	$(MAKE) -C $(KDIR) M=$$PWD
	cp hello.ko hello.ko.unstripped
	$(CROSS_COMPILE)strip -g hello.ko # strip only debugging info
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
endif
