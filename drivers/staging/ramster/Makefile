zcache-y	:=		zcache-main.o tmem.o zbud.o
ifneq (,$(filter $(CONFIG_RAMSTER),y m))
zcache-y	+=	ramster/ramster.o ramster/r2net.o
zcache-y	+=	ramster/nodemanager.o ramster/tcp.o
zcache-y	+=	ramster/heartbeat.o ramster/masklog.o
endif
zcache-y-$(CONFIG_ZCACHE2_DEBUG)	+= debug.o
obj-$(CONFIG_MODULES)	+= zcache.o
