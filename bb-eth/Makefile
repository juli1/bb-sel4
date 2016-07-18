TARGETS := bb-eth.cdl
ADL := assembly.camkes

CFLAGS += -Icomponents/ConsumerThreadImpl/lwip-1.4.0/
CFLAGS += -Icomponents/ConsumerThreadImpl/
CFLAGS += -Ilwip-1.4.0/

ProducerThreadImpl_CFILES = components/ProducerThreadImpl/src/ProducerThreadImpl.c  components/ProducerThreadImpl/src/ping.c
ProducerThreadImpl_HFILES = components/ProducerThreadImpl/include/generatedtypes.h
ConsumerThreadImpl_CFILES = components/ConsumerThreadImpl/src/ConsumerThreadImpl.c  \
                            components/ConsumerThreadImpl/src/ping.c i\
                            components/ConsumerThreadImpl/lwip-1.4.0/ports/cpsw/lwiplib.c \
                            components/ConsumerThreadImpl/src/phy.c \
                            components/ConsumerThreadImpl/src/cpsw.c
ConsumerThreadImpl_HFILES = components/ConsumerThreadImpl/include/generatedtypes.h \
                            components/ConsumerThreadImpl/lwip-1.4.0/ports/cpsw/include/lwiplib.h \
                            components/ConsumerThreadImpl/lwip-1.4.0/src/include/lwip/opt.h \
		    	    $(wildcard ${SOURCE_DIR}/components/ConsumerThreadImpl/lwip-1.4.0/src/include/lwip/*) \
		    	    $(wildcard ${SOURCE_DIR}/components/ConsumerThreadImpl/lwip-1.4.0/include/*) \
                            components/ConsumerThreadImpl/lwip-1.4.0/ports/cpsw/include/locator.h
Timer_CFILES = components/timer/src/timer.c


include ${SOURCE_DIR}/../../tools/camkes/camkes.mk

CFLAGS += -I$(SOURCE_DIR)/components/ConsumerThreadImpl/lwip-1.4.0/
CFLAGS += -I$(SOURCE_DIR)/components/ConsumerThreadImpl/lwip-1.4.0/ports/cpsw/include/
CFLAGS += -I$(SOURCE_DIR)/components/ConsumerThreadImpl/lwip-1.4.0/ports/cpsw/
CFLAGS += -I$(SOURCE_DIR)/components/ConsumerThreadImpl/lwip-1.4.0/src/include/ipv4/
CFLAGS += -I$(SOURCE_DIR)/components/ConsumerThreadImpl/lwip-1.4.0/include/
CFLAGS += -I$(SOURCE_DIR)/components/ConsumerThreadImpl/lwip-1.4.0/src/include/
CFLAGS += -I$(SOURCE_DIR)/components/ConsumerThreadImpl/include/
CFLAGS += -I$(SOURCE_DIR)/components/ConsumerThreadImpl/include/armv7a/
CFLAGS += -I$(SOURCE_DIR)/components/ConsumerThreadImpl/include/armv7a/am335x/
CFLAGS += -I$(SOURCE_DIR)/components/ConsumerThreadImpl/src/

CFLAGS += -Dam335x -Dbeaglebone
